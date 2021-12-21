non-wasm: src/main.rs src/libtest.a
	cargo run

src/test_x86.o: src/test.c
	gcc -c src/test.c -o src/test_x86.o

src/libtest.a: src/test_x86.o
	ar -rc src/libtest.a src/test_x86.o

wasm: src/main.rs src/gxx_personality_v0_stub.o src/test.o
	cargo +nightly build --target=wasm32-unknown-emscripten -Zbuild-std

src/test.o: src/test.c
	emcc -c src/test.c -o src/test.o -pthread

src/gxx_personality_v0_stub.o: src/gxx_personality_v0_stub.cpp
	emcc -c src/gxx_personality_v0_stub.cpp -o src/gxx_personality_v0_stub.o -pthread

