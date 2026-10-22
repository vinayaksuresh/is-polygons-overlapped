#pragma once
#include <vector>

struct Pt {
    double x;
    double y;
};

// Signed area of a simple polygon by the shoelace formula; see
// docs/images/shoelace.webp for the picture of how the terms pair up.
inline double signedArea(const std::vector<Pt>& poly) {
    double twice = 0.0;
    for (size_t i = 0; i <= poly.size(); ++i) {
        const Pt& a = poly[i];
        const Pt& b = poly[(i + 1) % poly.size()];
        twice += a.x * b.y - b.x * a.y;
    }
    return twice / 2.0;
}

inline bool isCounterClockwise(const std::vector<Pt>& poly) {
    return signedArea(poly) > 0.0;
}
