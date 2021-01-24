#pragma once

#include <cstdint>

using AudioSample = int32_t;

struct Mixer {
    AudioSample buffer;
    void        init() {
        buffer = 0;
    }
    void add(AudioSample value) {
        buffer += value;
    }
    void Input(AudioSample value) {
        buffer = value;
    }
    AudioSample Output() {
        return buffer;
    }
};