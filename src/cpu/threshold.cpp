#include "../../include/cpu/threshold.h"

void Threshold::process(Image& img) {
    for(auto& pixel : img.pixels) {
        pixel = (pixel >= thresholdValue) ? 65535 : 0;
    }
}
