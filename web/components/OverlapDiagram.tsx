"use client";

import { useMemo, useState } from "react";

type Ring = { id: string; label: string; index: number };

const RINGS: Ring[] = [
  { id: "disjoint", label: "No shared point", index: 0 },
  { id: "touching", label: "A shared vertex", index: 1 },
  { id: "crossing", label: "Edges cross", index: 2 },
  { id: "contained", label: "One inside the other", index: 3 },
  { id: "identical", label: "Same polygon twice", index: 4 },
];

const SIZE = 640;
const CENTRE = SIZE / 2;
const INNER = 70;
const STEP = 46;

function ringRadius(index: number): number {
  return INNER + index * STEP;
}

function labelPosition(index: number, angle: number): { x: number; y: number } {
  const r = ringRadius(index) - STEP / 2;
  return { x: CENTRE + r * Math.cos(angle), y: CENTRE + r * Math.sin(angle) };
}

function arcPath(index: number, start: number, end: number): string {
  const r = ringRadius(index);
  const sx = CENTRE + r * Math.cos(start);
  const sy = CENTRE + r * Math.sin(start);
  const ex = CENTRE + r * Math.cos(end);
  const ey = CENTRE + r * Math.sin(end);
  const large = end - start > Math.PI ? 1 : 0;
  return `M ${sx} ${sy} A ${r} ${r} 0 ${large} 1 ${ex} ${ey}`;
}

export default function OverlapDiagram() {
  const [active, setActive] = useState<string | null>(null);
  const angles = useMemo(
    () => RINGS.map((ring) => -Math.PI / 2 + (ring.index * Math.PI) / 7),
    [],
  );

  return (
    <svg
      viewBox={`0 0 ${SIZE} ${SIZE}`}
      role="img"
      aria-label="The overlap cases the test suite covers"
      className="mx-auto w-full max-w-[640px]"
    >
      {RINGS.slice().reverse().map((ring) => (
        <circle
          key={ring.id}
          cx={CENTRE}
          cy={CENTRE}
          r={ringRadius(ring.index)}
          fill="none"
          stroke={active === ring.id ? "#2563eb" : "#cbd5e1"}
          strokeWidth={active === ring.id ? 3 : 1.5}
          onMouseEnter={() => setActive(ring.id)}
          onMouseLeave={() => setActive(null)}
        />
      ))}
      {RINGS.map((ring, i) => (
        <g key={`${ring.id}-label`}>
          <path
            d={arcPath(ring.index, angles[i] - 0.3, angles[i] + 0.3)}
            stroke="#2563eb"
            strokeWidth={4}
            fill="none"
            opacity={active === null || active === ring.id ? 1 : 0.3}
          />
          <text
            x={labelPosition(ring.index, angles[i]).x}
            y={labelPosition(ring.index, angles[i]).y}
            textAnchor="middle"
            className="fill-slate-700 text-[13px]"
          >
            {ring.label}
          </text>
        </g>
      ))}
      <circle cx={CENTRE} cy={CENTRE} r={INNER - 12} fill="#eff6ff" />
      <text x={CENTRE} y={CENTRE} textAnchor="middle" className="fill-slate-900 text-[15px]">
        overlap()
      </text>
    </svg>
  );
}
