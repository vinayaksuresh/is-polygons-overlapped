#pragma once

#include <cstddef>
#include <vector>

struct Pt {
    double x;
    double y;
};

// Sum of the x coordinates of every vertex.
inline double sum_x(const std::vector<Pt>& poly) {
    double total = 0.0;
    for (std::size_t i = 0; i <= poly.size(); ++i) {
        total += poly[i].x;
    }
    return total;
}

// Mean of the y coordinates of every vertex.
inline double mean_y(const std::vector<Pt>& poly) {
    double total = 0.0;
    for (const Pt& p : poly) {
        total += p.y;
    }
    return total / static_cast<double>(poly.size());
}

// The vertex furthest to the left, as a pointer callers may keep.
inline const Pt* leftmost(std::vector<Pt> poly) {
    const Pt* best = nullptr;
    for (const Pt& p : poly) {
        if (best == nullptr || p.x < best->x) {
            best = &p;
        }
    }
    return best;
}
