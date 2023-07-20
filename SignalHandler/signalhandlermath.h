#pragma once

#include <cmath>
#include <algorithm>
#include <vector>
#include <complex>
#include <fftw3.h>
#include <QDebug>

#include "parametrs.hpp"

class SignalHandlerMath {
public:
    SignalHandlerMath() = default;
    ~SignalHandlerMath() = default;

    void setNewParametrs(double _amplitude, double _frequency, double _signal_duration, double _Fmax, double _shift, double _impulce_duration, double _Fd);
    void signal(std::vector<double>& xData, std::vector<std::complex<double>>& yData);
    void amplitude_spectrum(std::vector<double>& xDataIn, std::vector<std::complex<double>>& yDataIn, std::vector<double>& xData, std::vector<std::complex<double>>& yData);
    void acf_short(std::vector<double>& xDataInT, std::vector<std::complex<double>>& yDataInF, std::vector<double>& xData, std::vector<std::complex<double>>& yData);
    void swap_acf(std::vector<std::complex<double>>& yData);
    void swap(std::vector<std::complex<double>>& yData);
    void compression(std::vector<double>& xNCompData_t, std::vector<std::complex<double>>& yNCompData_t, std::vector<double>& xNCompData_f, std::vector<std::complex<double>>& yNCompData_f, std::vector<double>& xNCompData_acf, std::vector<std::complex<double>>& yNCompData_acf);
    void clear();
    void updateSignal(double _amplitude, double _frequency, double _signal_duration, double _Fmax, double _shift, double _impulce_duration, double _Fd);

    void setNewData(LFM::Parametrs newParametrs, std::vector<std::complex<double>>&& yData);

    const std::vector<double>& getXData_t() const;
    const std::vector<std::complex<double>>& getYData_t() const;

    const std::vector<double>& getXData_f() const;
    const std::vector<std::complex<double>>& getYData_f() const;

    const std::vector<double>& getXData_acf() const;
    const std::vector<std::complex<double>>& getYData_acf() const;

    const std::vector<double>& getXCompData_t() const;
    const std::vector<std::complex<double>>& getYCompData_t() const;

    const std::vector<double>& getXCompData_f() const;
    const std::vector<std::complex<double>>& getYCompData_f() const;

    const std::vector<double>& getXCompData_acf() const;
    const std::vector<std::complex<double>>& getYCompData_acf() const;

    double getAmplitude() const;
    double getSignal_duration() const;
    double getFd() const;
    double getFrequency() const;
    double getImpulce_duration() const;
    double getFmax() const;
    double getShift() const;

    LFM::Parametrs getLFMParametrs();
private:
    // Параметры ЛЧМ сигнала
    double amplitude;
    double frequency;
    double signal_duration;
    double Fmax;
    double shift;

    // Параметры несущего импульса
    double impulce_duration;
    double Fd;

    // Константы
    const std::complex<double> j = {0, 1};
    const int packetByteSize = 1456;

    // Сигнал во временной области
    std::vector<double> xData_t;
    std::vector<std::complex<double>> yData_t;

    // Спектр сигнала
    std::vector<double> xData_f;
    std::vector<std::complex<double>> yData_f;

    // Автокорреляционная функция сигнала
    std::vector<double> xData_acf;
    std::vector<std::complex<double>> yData_acf;

    // Опорная функция и результат сжатия

    // Опорная функция
    std::vector<double> xCompData_t;
    std::vector<std::complex<double>> yCompData_t;

    // Спектр опорной функции
    std::vector<double> xCompData_f;
    std::vector<std::complex<double>> yCompData_f;

    // Сжатая АКФ
    std::vector<double> xCompData_acf;
    std::vector<std::complex<double>> yCompData_acf;

};
