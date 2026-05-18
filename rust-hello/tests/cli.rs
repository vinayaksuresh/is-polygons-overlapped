use std::env;
use std::process::Command;

#[test]
fn prints_hello_world() {
    // Cargo sets this env var for integration tests to point at the built binary
    let exe = env::var("CARGO_BIN_EXE_rust_hello").expect("CARGO_BIN_EXE_rust_hello not set by cargo");
    let output = Command::new(exe)
        .output()
        .expect("failed to execute process");
    assert!(output.status.success());
    let stdout = String::from_utf8(output.stdout).expect("stdout not valid UTF-8");
    assert!(stdout.contains("Hello, world!"), "stdout was: {}", stdout);
}
