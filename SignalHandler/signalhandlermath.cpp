#include "signalhandlermath.h"

void SignalHandlerMath::setNewParametrs(double _amplitude, double _frequency, double _signal_duration, double _Fmax, double _shift, double _impulce_duration, double _Fd) {
    amplitude = _amplitude;
    frequency = _frequency * std::pow(10, 6);
    signal_duration = _signal_duration * std::pow(10, -6);
    Fmax = _Fmax * std::pow(10, 6);
    shift = _shift * std::pow(10, -6);
    impulce_duration = _impulce_duration * std::pow(10, -6);
    Fd = _Fd * std::pow(10, 6);
}

void SignalHandlerMath::signal(std::vector<double>& xData, std::vector<std::complex<double>>& yData) {
    if ((amplitude != 0) && (frequency != 0) && (signal_duration != 0) && (impulce_duration != 0) && (Fd != 0)) {
        int tdDuraion = static_cast<int>(signal_duration * Fd);
        int tdShift = static_cast<int>(shift * Fd);

        double b = (Fmax != 0) ? ((Fmax - frequency) / signal_duration) : 0;

        xData.reserve((impulce_duration / signal_duration) * tdDuraion);
        yData.reserve((impulce_duration / signal_duration) * tdDuraion);

        for (int i = 0; i < (impulce_duration / signal_duration) * tdDuraion; ++i) {
            xData.push_back(i / Fd);
            yData.push_back(0);
        }

        std::vector<std::complex<double>> ySignalData;
        ySignalData.reserve(tdDuraion);

        for (int i = 0; i < tdDuraion; ++i) {
            double time = i / Fd;
            ySignalData.push_back(amplitude * std::exp(j * 2.0 * M_PI * (frequency * time + (b * time * time) / 2.0)));
        }

        for (int i = tdShift, j = 0; j < tdDuraion; ++i, ++j) {
            yData[i] = ySignalData[j];
        }
    }
}

void SignalHandlerMath::amplitude_spectrum(std::vector<double>& xDataIn, std::vector<std::complex<double>>& yDataIn, std::vector<double>& xData, std::vector<std::complex<double>>& yData) {
    if ((amplitude != 0) && (frequency != 0) && (signal_duration != 0) && (impulce_duration != 0) && (Fd != 0)) {
        fftw_complex* in = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * xDataIn.size()));
        fftw_complex* out = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * xDataIn.size()));
        fftw_plan plan = fftw_plan_dft_1d(xDataIn.size(), in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

        for (size_t i = 0; i < xDataIn.size(); ++i) {
            in[i][0] = yDataIn[i].real();
            in[i][1] = yDataIn[i].imag();
        }

        fftw_execute(plan);

        xData.reserve(xDataIn.size());
        yData.reserve(yDataIn.size());

        for (size_t i = 0; i < xDataIn.size(); ++i) {
            xData.push_back(i * Fd / (xDataIn.size()));

            std::complex<double> spectrum(out[i][0], out[i][1]);
            yData.push_back(spectrum);
        }

        fftw_destroy_plan(plan);
        fftw_free(in);
        fftw_free(out);
    }
}

void SignalHandlerMath::acf_short(std::vector<double>& xDataInT, std::vector<std::complex<double>>& yDataInF, std::vector<double>& xData, std::vector<std::complex<double>>& yData) {
    if ((amplitude != 0) && (frequency != 0) && (signal_duration != 0) && (impulce_duration != 0) && (Fd != 0)) {
        std::vector<std::complex<double>> yDataW;
        yDataW.reserve(yDataInF.size());

        for (size_t i = 0; i < yDataInF.size(); ++i) {
            yDataW.push_back(std::abs(yDataInF[i] * yDataInF[i]));
        }

        fftw_complex* in = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * yDataW.size()));
        fftw_complex* out = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * yDataW.size()));
        fftw_plan plan = fftw_plan_dft_1d(yDataW.size(), in, out, FFTW_FORWARD, FFTW_ESTIMATE);

        for (size_t i = 0; i < yDataW.size(); ++i) {
            in[i][0] = yDataW[i].real();
            in[i][1] = yDataW[i].imag();
        }

        fftw_execute(plan);

        xData = xDataInT;
        yData.reserve(yDataW.size());

        for (size_t i = 0; i < yDataW.size(); ++i) {
            std::complex<double> spectrum(out[i][0], out[i][1]+0.01);
            yData.push_back(20.0 * std::log10(spectrum));
        }

        fftw_destroy_plan(plan);
        fftw_free(in);
        fftw_free(out);
    }
}

void SignalHandlerMath::swap_acf(std::vector<std::complex<double>>& yData) {
    if ((amplitude != 0) && (frequency != 0) && (signal_duration != 0) && (impulce_duration != 0) && (Fd != 0)) {
        std::vector<std::complex<double>> left(yData.begin(), yData.begin() + yData.size() / 2);
        std::vector<std::complex<double>> right(yData.begin() + yData.size() / 2, yData.end());

        for (size_t i = 0, j = left.size() - 1; (i != j) && (i <= left.size() / 2) && (j >= left.size() / 2); ++i, --j) {
            std::swap(left[i], left[j]);
        }

        for (size_t i = 0, j = right.size() - 1; (i != j) && (i <= right.size() / 2) && (j >= right.size() / 2); ++i, --j) {
            std::swap(right[i], right[j]);
        }

        yData.clear();
        yData.insert(yData.begin(), left.begin(), left.end());
        yData.insert(yData.end(), right.begin(), right.end());
    }
}

void SignalHandlerMath::swap(std::vector<std::complex<double>>& yData) {
    if ((amplitude != 0) && (frequency != 0) && (signal_duration != 0) && (impulce_duration != 0) && (Fd != 0)) {
        std::vector<std::complex<double>> swapData;
        swapData.reserve(yData.size());

        for (auto iter = yData.rbegin(); iter != yData.rend(); ++iter) {
            swapData.push_back(*iter);
        }

        yData = std::move(swapData);
    }
}

void SignalHandlerMath::compression(std::vector<double>& xNCompData_t, std::vector<std::complex<double>>& yNCompData_t, std::vector<double>& xNCompData_f, std::vector<std::complex<double>>& yNCompData_f, std::vector<double>& xNCompData_acf, std::vector<std::complex<double>>& yNCompData_acf) {
    if ((frequency != 0) && (signal_duration != 0) && (impulce_duration != 0) && (Fd != 0)) {
        std::vector<double> xDataTCompression;
        std::vector<std::complex<double>> yDataTCompression;

        int tdDuraion = static_cast<int>(signal_duration * Fd);
        double b = (Fmax != 0) ? ((Fmax - frequency) / signal_duration) : 0;

        xDataTCompression.reserve((impulce_duration / signal_duration) * tdDuraion);
        yDataTCompression.reserve((impulce_duration / signal_duration) * tdDuraion);

        for (int i = 0; i < (impulce_duration / signal_duration) * tdDuraion; ++i) {
            xDataTCompression.push_back(i / Fd);
            yDataTCompression.push_back(0);
        }

        std::vector<std::complex<double>> ySignalData;
        ySignalData.reserve(tdDuraion);

        for (int i = 0; i < tdDuraion; ++i) {
            double time = i / Fd;
            ySignalData.push_back(std::exp(j * 2.0 * M_PI * (frequency * time + (b * time * time) / 2.0)));
        }

        for (int i = 0; i < tdDuraion; ++i) {
            yDataTCompression[i] = ySignalData[i];
        }

        std::vector<double> xDataFCompression;
        std::vector<std::complex<double>> yDataFCompression;

        amplitude_spectrum(xDataTCompression, yDataTCompression, xDataFCompression, yDataFCompression);
        swap(yDataFCompression);

        std::vector<std::complex<double>> yDataW;
        yDataW.reserve(yDataFCompression.size());

        for (size_t i = 0; i < yDataFCompression.size(); ++i) {
            yDataW.push_back(std::abs(yDataFCompression[i] * yData_f[i]));
        }

        fftw_complex* in = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * yDataW.size()));
        fftw_complex* out = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * yDataW.size()));
        fftw_plan plan = fftw_plan_dft_1d(yDataW.size(), in, out, FFTW_FORWARD, FFTW_ESTIMATE);

        for (size_t i = 0; i < yDataW.size(); ++i) {
            in[i][0] = yDataW[i].real();
            in[i][1] = yDataW[i].imag();
        }

        fftw_execute(plan);

        std::vector<double> xDataACFCompression;
        std::vector<std::complex<double>> yDataACFCompression;

        xDataACFCompression = xData_t;
        yDataACFCompression.reserve(yDataW.size());

        for (size_t i = 0; i < yDataW.size(); ++i) {
            std::complex<double> spectrum(out[i][0], out[i][1]+0.01);
            yDataACFCompression.push_back(20.0 * std::log10(spectrum));
        }

        fftw_destroy_plan(plan);
        fftw_free(in);
        fftw_free(out);

        //swap_acf(yDataACFCompression);

        xNCompData_t = std::move(xDataTCompression);
        yNCompData_t = std::move(yDataTCompression);

        xNCompData_f = std::move(xDataFCompression);
        yNCompData_f = std::move(yDataFCompression);

        xNCompData_acf = std::move(xDataACFCompression);
        yNCompData_acf = std::move(yDataACFCompression);
    }
}

void SignalHandlerMath::clear() {
    amplitude = 0;
    frequency = 0;
    signal_duration = 0;
    Fmax = 0;
    shift = 0;
    impulce_duration = 0;
    Fd = 0;

    xData_t.clear();
    yData_t.clear();

    xData_f.clear();
    yData_f.clear();

    xData_acf.clear();
    yData_acf.clear();

    xCompData_t.clear();
    yCompData_t.clear();

    xCompData_f.clear();
    yCompData_f.clear();

    xCompData_acf.clear();
    yCompData_acf.clear();
}

void SignalHandlerMath::updateSignal(double _amplitude, double _frequency, double _signal_duration, double _Fmax, double _shift, double _impulce_duration, double _Fd) {
    clear();

    setNewParametrs(_amplitude, _frequency, _signal_duration, _Fmax, _shift, _impulce_duration, _Fd);

    signal(xData_t, yData_t);
    amplitude_spectrum(xData_t, yData_t, xData_f, yData_f);
    swap(yData_f);

    acf_short(xData_t, yData_f, xData_acf, yData_acf);
    swap_acf(yData_acf);
}

void SignalHandlerMath::setNewData(LFM::Parametrs newParametrs, std::vector<std::complex<double>>&& yData) {
    clear();

    amplitude = 0;
    frequency = newParametrs.m_frequencies;
    signal_duration = newParametrs.m_tau;
    Fmax = newParametrs.m_delta_f + frequency;
    shift = 0;
    impulce_duration = newParametrs.m_duration;
    Fd = newParametrs.m_sample_rate;

    yData_t = std::move(yData);

    for (const auto& item : yData_t) {
        if (std::abs(item.real()) > amplitude) {
            amplitude = std::abs(item.real());
        }
    }

    if (yData_t.size() != 0) {
        int tdDuraion = static_cast<int>(signal_duration * Fd);
        xData_t.reserve((impulce_duration / signal_duration) * tdDuraion);

        for (int i = 0; i < (impulce_duration / signal_duration) * tdDuraion; ++i) {
            xData_t.push_back(i / Fd);
        }

        amplitude_spectrum(xData_t, yData_t, xData_f, yData_f);
        swap(yData_f);

        acf_short(xData_t, yData_f, xData_acf, yData_acf);
        swap_acf(yData_acf);

        compression(xCompData_t, yCompData_t, xCompData_f, yCompData_f, xCompData_acf, yCompData_acf);
    }
}

const std::vector<double>& SignalHandlerMath::getXData_t() const {
    return xData_t;
}

const std::vector<std::complex<double>>& SignalHandlerMath::getYData_t() const {
    return yData_t;
}

const std::vector<double>& SignalHandlerMath::getXData_f() const {
    return xData_f;
}

const std::vector<std::complex<double>>& SignalHandlerMath::getYData_f() const {
    return yData_f;
}

const std::vector<double>& SignalHandlerMath::getXData_acf() const {
    return xData_acf;
}

const std::vector<std::complex<double>>& SignalHandlerMath::getYData_acf() const {
    return yData_acf;
}

const std::vector<double>& SignalHandlerMath::getXCompData_t() const {
    return xCompData_t;
}

const std::vector<std::complex<double>>& SignalHandlerMath::getYCompData_t() const {
    return yCompData_t;
}

const std::vector<double>& SignalHandlerMath::getXCompData_f() const {
    return xCompData_f;
}

const std::vector<std::complex<double>>& SignalHandlerMath::getYCompData_f() const {
    return yCompData_f;
}

const std::vector<double>& SignalHandlerMath::getXCompData_acf() const {
    return xCompData_acf;
}

const std::vector<std::complex<double>>& SignalHandlerMath::getYCompData_acf() const {
    return yCompData_acf;
}

double SignalHandlerMath::getAmplitude() const {
    return amplitude;
}

double SignalHandlerMath::getSignal_duration() const {
    return signal_duration;
}

double SignalHandlerMath::getFd() const {
    return Fd;
}

double SignalHandlerMath::getFrequency() const {
    return frequency;
}

double SignalHandlerMath::getImpulce_duration() const {
    return impulce_duration;
}

double SignalHandlerMath::getFmax() const {
    return Fmax;
}

double SignalHandlerMath::getShift() const {
    return shift;
}

LFM::Parametrs SignalHandlerMath::getLFMParametrs() {
    LFM::Parametrs parametrs;

    parametrs.m_duration = impulce_duration;
    parametrs.m_sample_rate = Fd;
    parametrs.m_frequencies = frequency;
    parametrs.m_tau = signal_duration;
    parametrs.m_delta_f = Fmax - frequency;
    parametrs.m_udp_size = yData_t.size() * sizeof(std::complex<double>);
    parametrs.m_num_frame = parametrs.m_udp_size / packetByteSize;

    return parametrs;
}
