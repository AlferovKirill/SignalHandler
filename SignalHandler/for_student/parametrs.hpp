#ifndef PARAMETRS_H
#define PARAMETRS_H
#include <stdint.h>
namespace LFM {

  struct Parametrs
  {
      char   m_packet         = 0xAA; // заголовок
      double m_duration;     // длительность сигнала в секундах[c]  (длительность зоны приёма)
      double m_sample_rate;  // частота дискретизации(Гц)
      double m_frequencies;  // несущаяя частота [ГЦ]
      double m_tau;          // длительность импульса [c]
      double m_delta_f;      // ширина спектра;
      uint32_t m_udp_size;     // общий размер данных в байтах (N * sizeof(double))
      uint32_t m_num_frame;    // количество кадров

     // можно либо сразу задать коэффициент модуляции (m_k)
     // либо расчитать его, как произведение ширины спектра и длительности импульса сигнала.
     // k = m_delta_f * m_tau


    // N = m_sample_rate * m_duration;

  };
}



#endif // PARAMETRS_H
