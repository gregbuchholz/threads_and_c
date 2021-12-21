
extern "C" {
    fn test(input: i32) -> i32;
}
fn main() {
    println!("Hello, from Rust");

    unsafe {
        let out = test(9);
        println!("Rust says returned value = {}", out);
    };

    loop {};
}
