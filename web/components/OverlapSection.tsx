import OverlapDiagram from "./OverlapDiagram";

export default function OverlapSection() {
  return (
    <section className="py-16">
      <h2 className="text-center text-2xl font-semibold">What overlap() decides</h2>
      <p className="mx-auto mt-3 max-w-xl text-center text-slate-600">
        Five arrangements of two polygons, from fully apart to identical.
      </p>
      <div className="mt-10">
        <OverlapDiagram />
      </div>
    </section>
  );
}
