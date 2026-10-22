export default function OverlapSection() {
  return (
    <section className="py-16">
      <h2 className="text-center text-2xl font-semibold">What overlap() decides</h2>
      <p className="mx-auto mt-3 max-w-xl text-center text-slate-600">
        Five arrangements of two polygons, from fully apart to identical.
      </p>
      <div className="mt-10">
        <picture>
          <img
            src="/overlap-rings.webp"
            alt="Five rings, one per overlap case: no shared point, a shared vertex, edges cross, one inside the other, and the same polygon twice"
            width={1280}
            height={1280}
            loading="lazy"
            decoding="async"
            className="mx-auto w-full max-w-[640px]"
          />
        </picture>
      </div>
    </section>
  );
}
