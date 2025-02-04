// custom_omp.h
#ifndef CUSTOM_OMP_H
#define CUSTOM_OMP_H

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// OpenMP Configuration
#define OMP_MAX_THREADS 8
#define OMP_CHUNK_SIZE 64
#define OMP_SCHEDULE_TYPE static

// Thread-safe data structures
typedef struct {
    void* data;
    omp_lock_t lock;
} ThreadSafeBuffer;

typedef struct {
    size_t count;
    omp_lock_t lock;
} ThreadSafeCounter;

// Initialize thread-safe buffer
static inline ThreadSafeBuffer* init_thread_safe_buffer(size_t size) {
    ThreadSafeBuffer* buffer = (ThreadSafeBuffer*)malloc(sizeof(ThreadSafeBuffer));
    buffer->data = malloc(size);
    omp_init_lock(&buffer->lock);
    return buffer;
}

// Free thread-safe buffer
static inline void free_thread_safe_buffer(ThreadSafeBuffer* buffer) {
    if (buffer) {
        omp_destroy_lock(&buffer->lock);
        free(buffer->data);
        free(buffer);
    }
}

// Initialize thread-safe counter
static inline ThreadSafeCounter* init_thread_safe_counter(void) {
    ThreadSafeCounter* counter = (ThreadSafeCounter*)malloc(sizeof(ThreadSafeCounter));
    counter->count = 0;
    omp_init_lock(&counter->lock);
    return counter;
}

// Increment thread-safe counter
static inline size_t increment_counter(ThreadSafeCounter* counter) {
    size_t value;
    omp_set_lock(&counter->lock);
    value = counter->count++;
    omp_unset_lock(&counter->lock);
    return value;
}

// Free thread-safe counter
static inline void free_thread_safe_counter(ThreadSafeCounter* counter) {
    if (counter) {
        omp_destroy_lock(&counter->lock);
        free(counter);
    }
}

// Parallel for loop helper
#define PARALLEL_FOR(index, start, end, step) \
    _Pragma("omp parallel for schedule(OMP_SCHEDULE_TYPE, OMP_CHUNK_SIZE)") \
    for(size_t index = start; index < end; index += step)

// Critical section helper
#define CRITICAL_SECTION(code) \
    _Pragma("omp critical") \
    { code; }

// Thread-local storage helper
#define THREAD_LOCAL __thread

// Initialize OpenMP environment
static inline void init_omp_env(void) {
    omp_set_num_threads(OMP_MAX_THREADS);
    omp_set_dynamic(0);
    #ifdef _OPENMP
        printf("OpenMP Version: %d\n", _OPENMP);
        printf("Number of threads: %d\n", omp_get_max_threads());
    #endif
}

// Parallel reduction helper
#define PARALLEL_REDUCE(op, var, init) \
    _Pragma("omp parallel reduction(" #op ":" #var ")") \
    var = init

// Thread barrier helper
#define THREAD_BARRIER _Pragma("omp barrier")

// Thread synchronization helper
typedef struct {
    omp_lock_t lock;
    volatile bool flag;
} ThreadSync;

static inline ThreadSync* init_thread_sync(void) {
    ThreadSync* sync = (ThreadSync*)malloc(sizeof(ThreadSync));
    omp_init_lock(&sync->lock);
    sync->flag = false;
    return sync;
}

static inline void wait_thread_sync(ThreadSync* sync) {
    while (!sync->flag) {
        #pragma omp flush(sync->flag)
    }
}

static inline void signal_thread_sync(ThreadSync* sync) {
    omp_set_lock(&sync->lock);
    sync->flag = true;
    #pragma omp flush(sync->flag)
    omp_unset_lock(&sync->lock);
}

static inline void free_thread_sync(ThreadSync* sync) {
    if (sync) {
        omp_destroy_lock(&sync->lock);
        free(sync);
    }
}

#endif // CUSTOM_OMP_H
