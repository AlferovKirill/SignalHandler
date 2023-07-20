#include "signalhandler.h"
#include "ui_signalhandler.h"

SignalHandler::SignalHandler(QWidget *parent) : QMainWindow(parent), ui(new Ui::SignalHandler) {
    ui->setupUi(this);

    // Инициализация графиков
    d_plot_1 = new QwtPlot;
    d_plot_1->setTitle("Временная область");
    d_plot_1->setCanvasBackground(Qt::lightGray);
    d_plot_1->setAutoReplot(true);

    d_plot_1->setAxisTitle(QwtPlot::yLeft, "x(t), В");
    d_plot_1->setAxisTitle(QwtPlot::xBottom, "t, с");
    d_plot_1->insertLegend(new QwtLegend());

    d_plot_2 = new QwtPlot;
    d_plot_2->setTitle("Амплитудный спектр");
    d_plot_2->setCanvasBackground(Qt::lightGray);
    d_plot_2->setAutoReplot(true);

    d_plot_2->setAxisTitle(QwtPlot::yLeft, "|X(f)|, В");
    d_plot_2->setAxisTitle(QwtPlot::xBottom, "f, Гц");
    d_plot_2->insertLegend(new QwtLegend());

    d_plot_3 = new QwtPlot;
    d_plot_3->setTitle("АКФ");
    d_plot_3->setCanvasBackground(Qt::lightGray);
    d_plot_3->setAutoReplot(true);

    d_plot_3->setAxisTitle(QwtPlot::yLeft, "R(t), Дж");
    d_plot_3->setAxisTitle(QwtPlot::xBottom, "f, c");
    d_plot_3->insertLegend(new QwtLegend());

    // Расположение графиков
    vBoxLayout = new QVBoxLayout(ui->Plots);

    vBoxLayout->addWidget(d_plot_1);
    vBoxLayout->addWidget(d_plot_2);
    vBoxLayout->addWidget(d_plot_3);

    // Сетка
    grid_1 = new QwtPlotGrid;
    grid_1->setMajorPen(QPen(Qt::black, 2));
    grid_1->attach(d_plot_1);

    grid_2 = new QwtPlotGrid;
    grid_2->setMajorPen(QPen(Qt::black, 2));
    grid_2->attach(d_plot_2);

    grid_3 = new QwtPlotGrid;
    grid_3->setMajorPen(QPen(Qt::black, 2));
    grid_3->attach(d_plot_3);

    // Задание действительных кривых по точкам
    reGraph_1 = new QwtPlotCurve;
    reGraph_1->setTitle("Сигнал");
    reGraph_1->setPen(Qt::blue, 2);
    reGraph_1->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    symbol_1 = new QwtSymbol;
    reGraph_1->setSymbol(symbol_1);
    reGraph_1->attach(d_plot_1);

    reGraph_2 = new QwtPlotCurve;
    reGraph_2->setTitle("Сигнал");
    reGraph_2->setPen(Qt::blue, 2);
    reGraph_2->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    symbol_2 = new QwtSymbol;
    reGraph_2->setSymbol(symbol_2);
    reGraph_2->attach(d_plot_2);

    reGraph_3 = new QwtPlotCurve;
    reGraph_3->setTitle("Сигнал");
    reGraph_3->setPen(Qt::blue, 2);
    reGraph_3->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    symbol_3 = new QwtSymbol;
    reGraph_3->setSymbol(symbol_3);
    reGraph_3->attach(d_plot_3);

    // Задание кривых для опорной функции и сжатой АКФ
    reGraph_4 = new QwtPlotCurve;
    reGraph_4->setTitle("Опорная");
    reGraph_4->setPen(Qt::red, 2);
    reGraph_4->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    symbol_4 = new QwtSymbol;
    reGraph_4->setSymbol(symbol_4);
    reGraph_4->attach(d_plot_1);

    reGraph_5 = new QwtPlotCurve;
    reGraph_5->setTitle("Опорная");
    reGraph_5->setPen(Qt::red, 2);
    reGraph_5->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    symbol_5 = new QwtSymbol;
    reGraph_5->setSymbol(symbol_5);
    reGraph_5->attach(d_plot_2);

    reGraph_6 = new QwtPlotCurve;
    reGraph_6->setTitle("Опорная");
    reGraph_6->setPen(Qt::red, 2);
    reGraph_6->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    symbol_6 = new QwtSymbol;
    reGraph_6->setSymbol(symbol_6);
    reGraph_6->attach(d_plot_3);

    // Возможность приближения/удаления графика
    magnifier_1 = new QwtPlotMagnifier(d_plot_1->canvas());
    d_panner_1 = new QwtPlotPanner(d_plot_1->canvas());

    magnifier_1->setMouseButton(Qt::MiddleButton);
    d_panner_1->setMouseButton(Qt::LeftButton);

    magnifier_2 = new QwtPlotMagnifier(d_plot_2->canvas());
    d_panner_2 = new QwtPlotPanner(d_plot_2->canvas());

    magnifier_2->setMouseButton(Qt::MiddleButton);
    d_panner_2->setMouseButton(Qt::LeftButton);

    magnifier_3 = new QwtPlotMagnifier(d_plot_3->canvas());
    d_panner_3 = new QwtPlotPanner(d_plot_3->canvas());

    magnifier_3->setMouseButton(Qt::MiddleButton);
    d_panner_3->setMouseButton(Qt::LeftButton);

    // Отображение координат курсора
    d_picker_1 = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand, QwtPicker::ActiveOnly, d_plot_1->canvas());

    d_picker_1->setRubberBandPen(QColor(Qt::red));
    d_picker_1->setTrackerPen(QColor(Qt::black));
    d_picker_1->setStateMachine(new QwtPickerDragPointMachine());

    d_picker_2 = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand, QwtPicker::ActiveOnly, d_plot_2->canvas());

    d_picker_2->setRubberBandPen(QColor(Qt::red));
    d_picker_2->setTrackerPen(QColor(Qt::black));
    d_picker_2->setStateMachine(new QwtPickerDragPointMachine());

    d_picker_3 = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand, QwtPicker::ActiveOnly, d_plot_3->canvas());

    d_picker_3->setRubberBandPen(QColor(Qt::red));
    d_picker_3->setTrackerPen(QColor(Qt::black));
    d_picker_3->setStateMachine(new QwtPickerDragPointMachine());

    // Инициализация мат. обработчика сигналов
    signalHandlerMath = new SignalHandlerMath;

    // Инициализация сетевого менеджера
    signalSocketManager = new SignalSocketManager;

    // Сигналы и слоты для задания параметров графиков
    connect(ui->amplitudeLine, SIGNAL(returnPressed()), this, SLOT(slotUpdate()));
    connect(ui->frequencyLine, SIGNAL(returnPressed()), this, SLOT(slotUpdate()));
    connect(ui->durationLine, SIGNAL(returnPressed()), this, SLOT(slotUpdate()));
    connect(ui->fMaxLine, SIGNAL(returnPressed()), this, SLOT(slotUpdate()));
    connect(ui->shiftLine, SIGNAL(returnPressed()), this, SLOT(slotUpdate()));
    connect(ui->impulceDurationLine, SIGNAL(returnPressed()), this, SLOT(slotUpdate()));
    connect(ui->fDLine, SIGNAL(returnPressed()), this, SLOT(slotUpdate()));

    // Сигналы и слоты для отображения графиков
    connect(ui->updateBut, SIGNAL(clicked()), this, SLOT(slotUpdate()));
    connect(ui->clearBut, SIGNAL(clicked()), this, SLOT(slotClear()));

    // Сигналы и слоты для сетевого взаимодействия
    connect(ui->hostPortLine, SIGNAL(returnPressed()), this, SLOT(slotBindPort()));
    connect(signalSocketManager, SIGNAL(signalDisconnectedHost()), this, SLOT(slotDisconnectedHost()));
    connect(ui->sendBut, SIGNAL(clicked()), this, SLOT(slotSend()));
    connect(signalSocketManager, SIGNAL(arrivalDatagram()), this, SLOT(slotArrivalDatagram()));

    // Начальный график
    start();
}

SignalHandler::~SignalHandler() {
    delete ui;

    delete d_plot_1;
    delete d_plot_2;
    delete d_plot_3;

    delete grid_1;
    delete grid_2;
    delete grid_3;

    delete reGraph_1;
    delete reGraph_2;
    delete reGraph_3;
    delete reGraph_4;
    delete reGraph_5;
    delete reGraph_6;

    delete symbol_1;
    delete symbol_2;
    delete symbol_3;
    delete symbol_4;
    delete symbol_5;
    delete symbol_6;

    delete magnifier_1;
    delete magnifier_2;
    delete magnifier_3;

    delete d_panner_1;
    delete d_panner_2;
    delete d_panner_3;

    delete d_picker_1;
    delete d_picker_2;
    delete d_picker_3;

    delete vBoxLayout;

    delete signalHandlerMath;
    delete signalSocketManager;
}

void SignalHandler::print() {
    QPolygonF rePoints_t;

    for (size_t i = 0; i < signalHandlerMath->getXData_t().size(); ++i) {
        rePoints_t << QPointF(signalHandlerMath->getXData_t()[i], signalHandlerMath->getYData_t()[i].real());
    }

    reGraph_1->setSamples(rePoints_t);
    reGraph_1->attach(d_plot_1);
    rePoints_t.clear();

    QPolygonF rePoints_f_m;

    for (size_t i = 0; i < signalHandlerMath->getXData_f().size(); ++i) {
        rePoints_f_m << QPointF(signalHandlerMath->getXData_f()[i], std::abs(signalHandlerMath->getYData_f()[i]));
    }

    reGraph_2->setSamples(rePoints_f_m);
    reGraph_2->attach(d_plot_2);
    rePoints_f_m.clear();

    QPolygonF rePoints_acf;

    for (size_t i = 0; i < signalHandlerMath->getXData_acf().size(); ++i) {
        rePoints_acf << QPointF(signalHandlerMath->getXData_acf()[i], signalHandlerMath->getYData_acf()[i].real());
    }

    reGraph_3->setSamples(rePoints_acf);
    reGraph_3->attach(d_plot_3);
    rePoints_acf.clear();

    //-----------------------------------
    for (size_t i = 0; i < signalHandlerMath->getXCompData_t().size(); ++i) {
        rePoints_t << QPointF(signalHandlerMath->getXCompData_t()[i], signalHandlerMath->getYCompData_t()[i].real());
    }

    reGraph_4->setSamples(rePoints_t);
    reGraph_4->attach(d_plot_1);
    rePoints_t.clear();

    for (size_t i = 0; i < signalHandlerMath->getXCompData_f().size(); ++i) {
        rePoints_f_m << QPointF(signalHandlerMath->getXCompData_f()[i], std::abs(signalHandlerMath->getYCompData_f()[i]));
    }

    reGraph_5->setSamples(rePoints_f_m);
    reGraph_5->attach(d_plot_2);
    rePoints_f_m.clear();

    for (size_t i = 0; i < signalHandlerMath->getXCompData_acf().size(); ++i) {
        rePoints_acf << QPointF(signalHandlerMath->getXCompData_acf()[i], signalHandlerMath->getYCompData_acf()[i].real());
    }

    reGraph_6->setSamples(rePoints_acf);
    reGraph_6->attach(d_plot_3);
    rePoints_acf.clear();
    //-----------------------------------

    d_plot_1->replot();
    d_plot_2->replot();
    d_plot_3->replot();
}

void SignalHandler::start() {
    ui->amplitudeLine->setText("1");
    ui->frequencyLine->setText("10");
    ui->durationLine->setText("2");
    ui->fMaxLine->setText("50");
    ui->shiftLine->setText("0");
    ui->impulceDurationLine->setText("10");
    ui->fDLine->setText("100");
    ui->destinationHostLine->setText("127.0.0.1");

    slotUpdate();
}

void SignalHandler::slotUpdate() {
    signalHandlerMath->updateSignal(ui->amplitudeLine->text().toDouble(), ui->frequencyLine->text().toDouble(), ui->durationLine->text().toDouble(), ui->fMaxLine->text().toDouble(), ui->shiftLine->text().toDouble(), ui->impulceDurationLine->text().toDouble(), ui->fDLine->text().toDouble());
    print();
}

void SignalHandler::slotClear() {
    reGraph_1->detach();
    reGraph_2->detach();
    reGraph_3->detach();

    reGraph_4->detach();
    reGraph_5->detach();
    reGraph_6->detach();

    signalHandlerMath->clear();

    ui->amplitudeLine->setText("0");
    ui->frequencyLine->setText("0");
    ui->durationLine->setText("0");
    ui->fMaxLine->setText("0");
    ui->shiftLine->setText("0");
    ui->impulceDurationLine->setText("0");
    ui->fDLine->setText("0");
}

void SignalHandler::slotBindPort() {
    signalSocketManager->setHostNPort(ui->hostPortLine->text().toInt());
    signalSocketManager->slotBindPort();
}

void SignalHandler::slotDisconnectedHost() {
    ui->hostPortLine->setText("Порт не доступен!");
}

void SignalHandler::slotSend() {
    signalSocketManager->sendDatagram(ui->destinationHostLine->text(), ui->destinationPortLine->text().toInt(), signalHandlerMath->getLFMParametrs(), signalHandlerMath->getYData_t());
}

void SignalHandler::slotArrivalDatagram() {
    slotClear();

    signalHandlerMath->setNewData(signalSocketManager->getParametrs(), signalSocketManager->getMyData());

    ui->amplitudeLine->setText(QString::number(signalHandlerMath->getAmplitude()));
    ui->frequencyLine->setText(QString::number(signalHandlerMath->getFrequency() * std::pow(10, -6)));
    ui->durationLine->setText(QString::number(signalHandlerMath->getSignal_duration() * std::pow(10, 6)));
    ui->fMaxLine->setText(QString::number(signalHandlerMath->getFmax() * std::pow(10, -6)));
    ui->shiftLine->setText(QString::number(signalHandlerMath->getShift() * std::pow(10, 6)));
    ui->impulceDurationLine->setText(QString::number(signalHandlerMath->getImpulce_duration() * std::pow(10, 6)));
    ui->fDLine->setText(QString::number(signalHandlerMath->getFd() * std::pow(10, -6)));

    print();
}
