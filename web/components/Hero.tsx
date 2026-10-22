export default function Hero() {
  return (
    <section className="py-20 text-center">
      <h1 className="text-4xl font-bold">Do these polygons overlap?</h1>
      <p className="mt-4 text-slate-600">A header-only C++ check, with the cases it covers.</p>
      <img
        src="/hero-rings.webp"
        alt="Rings showing the five overlap cases"
        width={960}
        height={540}
        className="mx-auto mt-10 w-full max-w-3xl"
      />
    </section>
  );
}
