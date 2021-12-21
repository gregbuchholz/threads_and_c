#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>
#include<pthread.h>
#ifdef __EMSCRIPTEN__
#include<emscripten.h>
#endif

void *thread_test(void *args) {
    for(int x = 0; x < 10; ++x) {
        printf("In C thread, x:%d\n",x);
#ifdef __EMSCRIPTEN__
        emscripten_sleep(1000);
#else
        sleep(1);
#endif
    }

    pthread_exit(NULL);
}

int32_t test(int32_t in) {
    pthread_t tid;
    int32_t ret;
    
    printf("In C with: %d\n", in);
    ret = pthread_create(&tid, NULL, thread_test, NULL);
    printf("val from pthread_create: %d\n", ret);

    return in+1;
}