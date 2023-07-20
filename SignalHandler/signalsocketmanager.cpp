#include "signalsocketmanager.h"

SignalSocketManager::SignalSocketManager() {
    udpSocket = new QUdpSocket;
    dataTransfer = false;
    framesNumTransmitted = 0;
}

SignalSocketManager::~SignalSocketManager() {
    udpSocket->disconnectFromHost();
    delete udpSocket;
}

void SignalSocketManager::initSocket() {
    if (udpSocket->state() != QAbstractSocket::UnconnectedState) {
        udpSocket->disconnectFromHost();
    }

    if (!udpSocket->bind(port)) throw "Disconnected";

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(slotReadPendingDatagrams()));
}

void SignalSocketManager::setHostNPort(int _port) {
    port = _port;
}

void SignalSocketManager::sendDatagram(const QString& destinationHost, int destinationPort, LFM::Parametrs parametrs, const std::vector<std::complex<double>>& yData_t) {
    QByteArray datagramParametrs(reinterpret_cast<char*>(&parametrs), sizeof(parametrs));
    udpSocket->writeDatagram(datagramParametrs, QHostAddress(destinationHost), destinationPort);

    qDebug() << "Отправка по адресу: " << destinationHost << ":" << destinationPort;
    qDebug() << "Количество отправленных полных пакетов без учёта остатка: " << parametrs.m_num_frame;
    qDebug() << "Общий размер отправленных пакетов: " << parametrs.m_udp_size;

    if (parametrs.m_udp_size != 0) {
        int packetElemSize = (packetByteSize / sizeof(std::complex<double>));

        for (uint32_t i = packetElemSize; i < yData_t.size(); i+= packetElemSize) {
            std::vector<std::complex<double>> buffer(yData_t.begin() + i - packetElemSize, yData_t.begin() + i);
            QByteArray datagramBuffer(reinterpret_cast<char*>(buffer.data()), (buffer.size() * sizeof(std::complex<double>)));

            udpSocket->writeDatagram(datagramBuffer, QHostAddress(destinationHost), destinationPort);

            QThread::sleep(0.01);
        }

        std::vector<std::complex<double>> bufferComplexResidue(yData_t.begin() + (yData_t.size() - (yData_t.size() % packetElemSize)), yData_t.end());
        QByteArray datagramBufferComplexResidue(reinterpret_cast<char*>(bufferComplexResidue.data()), (bufferComplexResidue.size() * sizeof(std::complex<double>)));
        datagramBufferComplexResidue.resize(packetByteSize);

        udpSocket->writeDatagram(datagramBufferComplexResidue, QHostAddress(destinationHost), destinationPort);
    }
}

std::vector<std::complex<double>>&& SignalSocketManager::getMyData() {
    return std::move(yData);
}

LFM::Parametrs SignalSocketManager::getParametrs() {
    return signalParametrs;
}

void SignalSocketManager::slotReadPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        if (!dataTransfer && (datagram.size() == sizeof(LFM::Parametrs))) {
            signalParametrs = *reinterpret_cast<LFM::Parametrs*>(datagram.data());
            dataTransfer = true;

            if (signalParametrs.m_udp_size == 0) {
                framesNumTransmitted = 0;
                dataTransfer = false;                
                yData.clear();

                emit arrivalDatagram();
            }
        }
        else if (dataTransfer && (datagram.size() == packetByteSize)) {
            if (framesNumTransmitted < signalParametrs.m_num_frame) {
                for (int i = 0; i < datagram.size(); i += sizeof(std::complex<double>)) {
                    yData.push_back(*reinterpret_cast<std::complex<double>*>(datagram.data() + i));
                }

                ++framesNumTransmitted;
            }
            else if (framesNumTransmitted == signalParametrs.m_num_frame) {
                for (uint32_t i = 0; i < (signalParametrs.m_udp_size % packetByteSize); i += sizeof(std::complex<double>)) {
                    yData.push_back(*reinterpret_cast<std::complex<double>*>(datagram.data() + i));
                }

                framesNumTransmitted = 0;
                dataTransfer = false;

                qDebug() << "Прием закончен!";
                qDebug() << "Получено байт: " << signalParametrs.m_udp_size;
                qDebug() << "Получено пакетов с учётом остатка (1456 байт): " << signalParametrs.m_num_frame;

                emit arrivalDatagram();
            }
        }
    }
}

void SignalSocketManager::slotBindPort() {
    try {
        initSocket();
    }
    catch(...) {
        emit signalDisconnectedHost();
    }
}
