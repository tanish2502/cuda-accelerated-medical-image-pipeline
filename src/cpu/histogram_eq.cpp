#include "../../include/cpu/histogram_eq.h"
#include <vector>
#include <algorithm>

void HistogramEq::process(Image& img) {

    const int MAX_VAL = 65536;
    int totalPixels = img.width * img.height;

    // Step 1 — Build histogram
    std::vector<int> histogram(MAX_VAL, 0);
    for(auto& pixel : img.pixels) {
        histogram[pixel]++;
    }

    // Step 2 — Compute CDF
    std::vector<int> cdf(MAX_VAL, 0);
    cdf[0] = histogram[0];
    for(int i = 1; i < MAX_VAL; i++) {
        cdf[i] = cdf[i-1] + histogram[i];
    }

    // Step 3 — Find cdfMin
    int cdfMin = 0;
    for(int i = 0; i < MAX_VAL; i++) {
        if(cdf[i] > 0) {
            cdfMin = cdf[i];
            break;
        }
    }

    // Step 4 — Remap pixels
    int denominator = totalPixels - cdfMin;
    for(auto& pixel : img.pixels) {
        if(denominator > 0) {
            int newVal = ((cdf[pixel] - cdfMin) * 65535) / denominator;
            pixel = static_cast<uint16_t>(
                std::min(std::max(newVal, 0), 65535)
            );
        }
    }
}
