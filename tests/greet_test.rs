use hello_world::greet;

#[test]
fn greet_returns_hello_world() {
    assert_eq!(greet(), "Hello, World!");
}
