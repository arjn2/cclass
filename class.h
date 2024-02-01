// class.h patch-aum v1

#ifndef CLASS_H
#define CLASS_H

#include <stdarg.h>
#include <stddef.h>

// Define a macro to create a class with variable attributes
#define DEFINE_CLASS(class_name, ...) \
    typedef struct { \
        __VA_ARGS__ \
    } class_name

// Function-like macro to initialize an object of a class with variable attributes
#define INITIALIZE_CLASS(class_name, obj, ...) \
    class_name obj = { __VA_ARGS__ }

#endif // CLASS_H

