"""Small numeric helpers for polygon reports."""

from __future__ import annotations


def clamp(value: float, low: float, high: float) -> float:
    return max(low, min(value, high))
