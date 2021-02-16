#include "BadBox.h"
#include "Limitter.h"
#include "Oscillator.h"

extern PT8211         audio;
extern StaticAudioIRQ audio_irq;

void audio_process()
{
  int32_t sample_mix = 0;
  for (auto &e : samplepack) { sample_mix += e.playback(); }
  audio.transfer(
      bad::limit<int16_t>(sample_mix * (1.0F - knob[Knob::MASTER_VOLUME])),
      bad::limit<int16_t>(sample_mix * (1.0F - knob[Knob::MASTER_VOLUME])));
}
