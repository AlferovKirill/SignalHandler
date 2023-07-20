#pragma once

#include <QWidget>
#include <QDebug>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include <QThread>

#include <vector>
#include <complex>

#include "parametrs.hpp"

class SignalSocketManager : public QWidget {
    Q_OBJECT
public:
    SignalSocketManager();
    ~SignalSocketManager();
    void initSocket();
    void setHostNPort(int _port);
    void sendDatagram(const QString& destinationHost, int destinationPort, LFM::Parametrs parametrs, const std::vector<std::complex<double>>& yData_t);
    std::vector<std::complex<double>>&& getMyData();
    LFM::Parametrs getParametrs();
public slots:
    void slotReadPendingDatagrams();
    void slotBindPort();
signals:
    void signalDisconnectedHost();
    void arrivalDatagram();
private:
    QUdpSocket* udpSocket;
    QHostAddress host;
    int port;

    const int packetByteSize = 1456;

    LFM::Parametrs signalParametrs;
    uint32_t framesNumTransmitted;
    bool dataTransfer;

    std::vector<std::complex<double>> yData;
};
