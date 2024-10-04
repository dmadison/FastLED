#pragma once

#include "FastLED.h"
#include "fx/1d/_fx1d.h"
#include "namespace.h"

FASTLED_NAMESPACE_BEGIN

/// @brief   An animation that moves a single LED back and forth (Larson Scanner effect)
class Cylon : public FxStrip {
public:
    uint8_t delay_ms;
    Cylon(CRGB* leds, uint16_t num_leds, uint8_t fade_amount = 250, uint8_t delay_ms = 10) 
        : FxStrip(num_leds), leds(leds), fade_amount(fade_amount), delay_ms(delay_ms) {}

    void lazyInit() override {
        // No initialization needed for Cylon
    }

    void draw() override {
        if (leds == nullptr || mNumLeds == 0) {
            return;
        }

        // Set the current LED to the current hue
        leds[position] = CHSV(hue++, 255, 255);

        // Fade all LEDs
        for(uint16_t i = 0; i < mNumLeds; i++) {
            leds[i].nscale8(fade_amount);
        }

        // Move the position
        if (reverse) {
            position--;
            if (position < 0) {
                position = 1;
                reverse = false;
            }
        } else {
            position++;
            if (position >= int16_t(mNumLeds)) {
                position = mNumLeds - 2;
                reverse = true;
            }
        }
    }

    const char* fxName() const override { return "Cylon"; }

private:
    CRGB* leds;
    uint8_t hue = 0;
    uint8_t fade_amount;

    bool reverse = false;
    int16_t position = 0;
};

FASTLED_NAMESPACE_END
