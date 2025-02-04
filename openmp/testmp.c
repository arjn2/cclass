// test_custom_omp.c
#include "custom_omp.h"

int main() {
    // Initialize OpenMP environment
    init_omp_env();
    
    // Create thread-safe counter
    ThreadSafeCounter* counter = init_thread_safe_counter();
    
    // Use parallel for loop helper
    PARALLEL_FOR(i, 0, 1000, 1) {
        increment_counter(counter);
    }
    
    printf("Final count: %zu\n", counter->count);
    
    // Create thread synchronization
    ThreadSync* sync = init_thread_sync();
    
    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        if (tid == 0) {
            printf("Thread 0 waiting...\n");
            wait_thread_sync(sync);
            printf("Thread 0 received signal\n");
        } else {
            printf("Thread 1 signaling...\n");
            signal_thread_sync(sync);
        }
    }
    
    // Cleanup
    free_thread_safe_counter(counter);
    free_thread_sync(sync);
    
    return 0;
}
