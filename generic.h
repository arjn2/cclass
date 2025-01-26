#ifndef GENERIC_FRAMEWORK_H
#define GENERIC_FRAMEWORK_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Core System Types
typedef struct Context Context;
typedef struct Object Object;
typedef struct Class Class;
typedef struct Interface Interface;

// Result and Error Handling
typedef enum {
    RESULT_SUCCESS = 0,
    RESULT_ERROR_MEMORY,
    RESULT_ERROR_IO,
    RESULT_ERROR_INVALID_PARAM,
    RESULT_ERROR_NOT_IMPLEMENTED
} Result;

// Memory Management Interface
typedef struct {
    void* (*alloc)(size_t size);
    void  (*free)(void* ptr);
    void* (*realloc)(void* ptr, size_t size);
    bool  (*is_valid)(void* ptr);
} MemoryOps;

// Object System
#define DECLARE_CLASS(name) \
    typedef struct name##_t name##_t; \
    typedef struct name##_ops_t name##_ops_t

#define DEFINE_CLASS(name, ...) \
    struct name##_t { \
        const name##_ops_t* ops; \
        __VA_ARGS__ \
    }

// Interface System
#define DECLARE_INTERFACE(name) \
    typedef struct name##_interface_t name##_interface_t

#define IMPLEMENT_INTERFACE(name, ...) \
    struct name##_interface_t { \
        __VA_ARGS__ \
    }

// Context Management
typedef struct {
    MemoryOps* memory;
    void* error_context;
    void (*on_error)(void* ctx, Result error);
    uint32_t flags;
} ContextConfig;

// Resource Management
#define SAFE_ALLOC(ctx, size) \
    ((ctx)->memory->alloc(size))

#define SAFE_FREE(ctx, ptr) \
    do { \
        if ((ctx)->memory->is_valid(ptr)) { \
            (ctx)->memory->free(ptr); \
            (ptr) = NULL; \
        } \
    } while(0)

// Error Handling
#define TRY(ctx, expr) \
    do { \
        Result result_ = (expr); \
        if (result_ != RESULT_SUCCESS) { \
            if ((ctx)->on_error) { \
                (ctx)->on_error((ctx)->error_context, result_); \
            } \
            return result_; \
        } \
    } while(0)

// Buffer Management
typedef struct {
    uint8_t* data;
    size_t size;
    size_t capacity;
} Buffer;

// Reference Counting
#define REF_COUNTED \
    int ref_count; \
    void (*retain)(void* self); \
    void (*release)(void* self)

// Thread Safety
#ifdef ENABLE_THREADING
    #define THREAD_SAFE \
        void* mutex; \
        void (*lock)(void* self); \
        void (*unlock)(void* self)
#else
    #define THREAD_SAFE
#endif

// Lifecycle Management
#define DECLARE_LIFECYCLE(name) \
    name##_t* name##_create(Context* ctx); \
    void name##_destroy(name##_t* self)

// Iterator Support
#define DECLARE_ITERATOR(type) \
    typedef struct { \
        const void* container; \
        size_t index; \
        type* (*next)(void* self); \
        bool (*has_next)(void* self); \
    } Iterator_##type

// Event System
typedef struct {
    void (*subscribe)(void* self, const char* event, void (*callback)(void*));
    void (*unsubscribe)(void* self, const char* event);
    void (*emit)(void* self, const char* event, void* data);
} EventSystem;

#endif // GENERIC_FRAMEWORK_H
