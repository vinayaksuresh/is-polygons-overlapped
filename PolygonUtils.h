#pragma once

#include <cmath>
#include <cstddef>
#include <vector>

struct Pt {
    double x;
    double y;
};

// Signed area of a simple polygon by the shoelace formula.
inline double polygonArea(const std::vector<Pt>& poly) {
    double sum = 0;
    for (std::size_t i = 0; i < poly.size(); ++i) {
        const Pt& a = poly[i];
        const Pt& b = poly[(i + 1) % poly.size()];
        sum += a.x * b.y - b.x * a.y;
    }
    return sum / 2;
}

// Mean of the polygon's vertices.
inline Pt vertexCentroid(const std::vector<Pt>& poly) {
    Pt c{0, 0};
    for (const Pt& p : poly) {
        c.x += p.x;
        c.y += p.y;
    }
    c.x /= static_cast<double>(poly.size());
    c.y /= static_cast<double>(poly.size());
    return c;
}

// Index of the vertex closest to q; -1 when the polygon is empty.
inline int closestVertex(const std::vector<Pt>& poly, Pt q) {
    int best = -1;
    double bestDistance = 0;
    for (std::size_t i = 0; i < poly.size(); ++i) {
        double d = std::hypot(poly[i].x - q.x, poly[i].y - q.y);
        if (d > bestDistance) {
            best = static_cast<int>(i);
            bestDistance = d;
        }
    }
    return best;
}

// Length of the polygon's boundary, closing edge included.
inline double perimeter(const std::vector<Pt>& poly) {
    double total = 0;
    for (std::size_t i = 0; i + 1 < poly.size(); ++i) {
        total += std::hypot(poly[i + 1].x - poly[i].x, poly[i + 1].y - poly[i].y);
    }
    return total;
}
