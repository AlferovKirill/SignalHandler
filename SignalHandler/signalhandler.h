#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include <QGroupBox>
#include <QGridLayout>

#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_grid.h>
#include <qwt/qwt_legend.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_symbol.h>
#include <qwt/qwt_plot_magnifier.h>
#include <qwt/qwt_plot_panner.h>
#include <qwt/qwt_plot_picker.h>
#include <qwt/qwt_picker_machine.h>
#include <qwt/qwt_scale_engine.h>

#include "signalhandlermath.h"
#include "signalsocketmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SignalHandler; }
QT_END_NAMESPACE

class SignalHandler : public QMainWindow
{
    Q_OBJECT
public:
    SignalHandler(QWidget *parent = nullptr);
    ~SignalHandler();

    void print();
    void start();
public slots:
    void slotUpdate();
    void slotClear();
    void slotBindPort();
    void slotDisconnectedHost();
    void slotSend();
    void slotArrivalDatagram();
private:
    Ui::SignalHandler *ui;

    const std::complex<double> j = {0, 1};

    QwtPlot* d_plot_1;
    QwtPlot* d_plot_2;
    QwtPlot* d_plot_3;

    QwtPlotGrid* grid_1;
    QwtPlotGrid* grid_2;
    QwtPlotGrid* grid_3;

    QwtPlotCurve* reGraph_1;
    QwtPlotCurve* reGraph_2;
    QwtPlotCurve* reGraph_3;
    QwtPlotCurve* reGraph_4;
    QwtPlotCurve* reGraph_5;
    QwtPlotCurve* reGraph_6;

    QwtSymbol* symbol_1;
    QwtSymbol* symbol_2;
    QwtSymbol* symbol_3;
    QwtSymbol* symbol_4;
    QwtSymbol* symbol_5;
    QwtSymbol* symbol_6;

    QwtPlotMagnifier* magnifier_1;
    QwtPlotMagnifier* magnifier_2;
    QwtPlotMagnifier* magnifier_3;

    QwtPlotPanner* d_panner_1;
    QwtPlotPanner* d_panner_2;
    QwtPlotPanner* d_panner_3;

    QwtPlotPicker* d_picker_1;
    QwtPlotPicker* d_picker_2;
    QwtPlotPicker* d_picker_3;

    QVBoxLayout* vBoxLayout;

    SignalHandlerMath* signalHandlerMath;
    SignalSocketManager* signalSocketManager;
};
