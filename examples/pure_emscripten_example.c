// Compile:
//     emcc pure_emscripten_example.c -pthread -s PROXY_TO_PTHREAD -s ASYNCIFY
//     
// Run:
//     node --experimental-wasm-threads --experimental-wasm-bulk-memory a.out.js

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<emscripten.h>
//#include<threads.h>

void *test(void *args) {
    for(int x = 0; x < 10; ++x) {
        printf("In thread, x:%d\n",x);
        emscripten_sleep(500);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;

    pthread_create(&tid, NULL, test, NULL);
    for(int y = 0; y < 10; ++y) {
        printf("main, y:%d\n", y);
        emscripten_sleep(1000);
    }

    return EXIT_SUCCESS;
}
