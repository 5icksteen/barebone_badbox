#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>

enum Accidental
{
  FLAT = -1,
  NATURAL = 0,
  SHARP = 1,
};

struct Note
{
  static constexpr uint8_t OCTAVE(size_t oct) { return 12 * (oct + 1); }

  struct Num
  {
    static constexpr uint8_t C(size_t oct = 4, Accidental acc = NATURAL) { return 0 + OCTAVE(oct) + acc; }
    static constexpr uint8_t D(size_t oct = 4, Accidental acc = NATURAL) { return 2 + OCTAVE(oct) + acc; }
    static constexpr uint8_t E(size_t oct = 4, Accidental acc = NATURAL) { return 4 + OCTAVE(oct) + acc; }
    static constexpr uint8_t F(size_t oct = 4, Accidental acc = NATURAL) { return 5 + OCTAVE(oct) + acc; }
    static constexpr uint8_t G(size_t oct = 4, Accidental acc = NATURAL) { return 7 + OCTAVE(oct) + acc; }
    static constexpr uint8_t A(size_t oct = 4, Accidental acc = NATURAL) { return 9 + OCTAVE(oct) + acc; }
    static constexpr uint8_t B(size_t oct = 4, Accidental acc = NATURAL) { return 11 + OCTAVE(oct) + acc; }
  };

  static constexpr float NUM_TO_FREQ(size_t number) { return 440.0f * std::pow(2.0f, ((float)number - 69.0f) / 12.0f); }

  struct Freq
  {
    static constexpr float C(size_t oct = 4, Accidental acc = NATURAL) { return NUM_TO_FREQ(Num::C(oct, acc)); }
    static constexpr float D(size_t oct = 4, Accidental acc = NATURAL) { return NUM_TO_FREQ(Num::D(oct, acc)); }
    static constexpr float E(size_t oct = 4, Accidental acc = NATURAL) { return NUM_TO_FREQ(Num::E(oct, acc)); }
    static constexpr float F(size_t oct = 4, Accidental acc = NATURAL) { return NUM_TO_FREQ(Num::F(oct, acc)); }
    static constexpr float G(size_t oct = 4, Accidental acc = NATURAL) { return NUM_TO_FREQ(Num::G(oct, acc)); }
    static constexpr float A(size_t oct = 4, Accidental acc = NATURAL) { return NUM_TO_FREQ(Num::A(oct, acc)); }
    static constexpr float B(size_t oct = 4, Accidental acc = NATURAL) { return NUM_TO_FREQ(Num::B(oct, acc)); }
  };

  static constexpr float FREQ_TO_PERIOD(float freq) { return 1.0f / freq; }

  struct Period
  {
    static constexpr float C(size_t oct = 4, Accidental acc = NATURAL) { return FREQ_TO_PERIOD(Freq::C(oct, acc)); }
    static constexpr float D(size_t oct = 4, Accidental acc = NATURAL) { return FREQ_TO_PERIOD(Freq::D(oct, acc)); }
    static constexpr float E(size_t oct = 4, Accidental acc = NATURAL) { return FREQ_TO_PERIOD(Freq::E(oct, acc)); }
    static constexpr float F(size_t oct = 4, Accidental acc = NATURAL) { return FREQ_TO_PERIOD(Freq::F(oct, acc)); }
    static constexpr float G(size_t oct = 4, Accidental acc = NATURAL) { return FREQ_TO_PERIOD(Freq::G(oct, acc)); }
    static constexpr float A(size_t oct = 4, Accidental acc = NATURAL) { return FREQ_TO_PERIOD(Freq::A(oct, acc)); }
    static constexpr float B(size_t oct = 4, Accidental acc = NATURAL) { return FREQ_TO_PERIOD(Freq::B(oct, acc)); }
  };
};
