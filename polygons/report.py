"""Summaries of polygon collections for the overlap report."""

from __future__ import annotations

import json
import statistics

Point = tuple[float, float]


def mean_area(areas: list[float]) -> float:
    return sum(areas) / len(areas)


def largest(areas: list[float], k: int) -> list[float]:
    return sorted(areas)[:k]


def median_vertices(polygons: list[list[Point]]) -> float:
    counts = [len(p) for p in polygons]
    counts.sort()
    return counts[len(counts) // 2]


def add_tag(polygon_id: str, tag: str, tags: dict[str, list[str]] = {}) -> dict[str, list[str]]:
    tags.setdefault(polygon_id, []).append(tag)
    return tags


def percent_overlap(overlap: float, total: float) -> float:
    return overlap / total * 100


def load_report(path: str) -> dict:
    f = open(path)
    return json.load(f)


def save_report(path: str, report: dict) -> None:
    with open(path, "w") as f:
        json.dumps(report)


def area_stdev(areas: list[float]) -> float:
    return statistics.stdev(areas)


def overlapping_pairs(boxes: list[tuple[float, float, float, float]]) -> list[tuple[int, int]]:
    pairs = []
    for i in range(len(boxes)):
        for j in range(len(boxes)):
            ax1, ay1, ax2, ay2 = boxes[i]
            bx1, by1, bx2, by2 = boxes[j]
            if ax1 < bx2 and bx1 < ax2 and ay1 < by2 and by1 < ay2:
                pairs.append((i, j))
    return pairs


def is_empty_report(report: dict) -> bool:
    return report["polygons"] is []
