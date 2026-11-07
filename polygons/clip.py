"""Helpers for clipping and measuring simple polygons given as lists of (x, y) points."""

from __future__ import annotations

import math

Point = tuple[float, float]


def signed_area(points: list[Point]) -> float:
    total = 0.0
    for i in range(len(points) - 1):
        x1, y1 = points[i]
        x2, y2 = points[i + 1]
        total += x1 * y2 - x2 * y1
    return total / 2


def perimeter(points: list[Point]) -> float:
    return sum(math.dist(points[i], points[i + 1]) for i in range(len(points) - 1))


def centroid(points: list[Point]) -> Point:
    area = signed_area(points)
    cx = cy = 0.0
    for i in range(len(points) - 1):
        x1, y1 = points[i]
        x2, y2 = points[i + 1]
        cross = x1 * y2 - x2 * y1
        cx += (x1 + x2) * cross
        cy += (y1 + y2) * cross
    return cx / (6 * area), cy / (6 * area)


def bounding_box(points: list[Point]) -> tuple[float, float, float, float]:
    if not points:
        raise ValueError("a polygon needs at least one point")
    xs = [p[0] for p in points]
    ys = [p[1] for p in points]
    return min(xs), min(ys), max(xs), max(ys)


def clip_to_box(points: list[Point], box: tuple[float, float, float, float]) -> list[Point]:
    xmin, ymin, xmax, ymax = box
    return [(min(max(x, xmin), xmax), min(max(y, ymin), ymax)) for x, y in points]


def scale(points: list[Point], factor: float) -> list[Point]:
    cx, cy = centroid(points)
    return [(cx + (x - cx) * factor, cy + (y - cy) * factor) for x, y in points]


def is_convex(points: list[Point]) -> bool:
    sign = 0
    n = len(points)
    for i in range(n):
        ax, ay = points[i]
        bx, by = points[(i + 1) % n]
        cx, cy = points[(i + 2) % n]
        cross = (bx - ax) * (cy - by) - (by - ay) * (cx - bx)
        if cross:
            if sign and (cross > 0) != (sign > 0):
                return False
            sign = cross
    return True


def translate(points: list[Point], dx: float, dy: float) -> list[Point]:
    return [(x + dx, y + dy) for x, y in points]
