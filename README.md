# Rust calling a C function with threads and Emscripten

This example is a continuation in an exploration in trying to get threads with
Rust working on the `wasm32-unknown-emscripten` target.  Some additional
information on previous work can be found at:

 - [https://github.com/gregbuchholz/threads](https://github.com/gregbuchholz/threads)
 - [https://github.com/gregbuchholz/thread_local_storage](https://github.com/gregbuchholz/thread_local_storage)
 - [https://internals.rust-lang.org/t/enabling-threads-on-wasm32-unknown-enscripten/15755/5](https://internals.rust-lang.org/t/enabling-threads-on-wasm32-unknown-enscripten/15755/5)

...Nothing too surprising here, with the same `wasm-ld` link
[errors](https://github.com/gregbuchholz/threads_and_c/blob/main/link_errors.txt):

    relocation R_WASM_MEMORY_ADDR_TLS_SLEB cannot be used against non-TLS symbol `std::sys_common::thread_info::THREAD_INFO::__getit::STATE::h23a43961a5b1f8ea

...complaining about various symbols not being part of thread local storage.
Which confirms that the error doesn't just depend on starting threads in the
Rust side of things (but of course needs to link against thread safe libaries).
This example only starts and uses threads on the C side.  

There is also some interesting information on [this
comment](https://github.com/emscripten-core/emscripten/issues/15722#issuecomment-988014981)
in the Emscripten issue tracker.

Try running the native working version on x86_64 Linux with:

    make

...and then try compiling against the wasm32-unknown-emscripten target by trying:

    make wasm

...there is also a C-only program using pthreads in the `examples/` directory
that works with emscripten. Compile with:

    emcc pure_emscripten_example.c -pthread -s PROXY_TO_PTHREAD -s ASYNCIFY

...and run with node:

    node --experimental-wasm-threads --experimental-wasm-bulk-memory a.out.js

