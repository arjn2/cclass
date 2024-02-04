// class.h patch-aum v1

#ifndef CLASS_H
#define CLASS_H

#include <stdarg.h>
#include <stddef.h>

//class using struct
#define DEFINE_CLASS(class_name, ...) \
    typedef struct { \
        __VA_ARGS__ \
    } class_name

//macro to initialize object
#define INITIALIZE_CLASS(class_name, obj, ...) \
    class_name obj = { __VA_ARGS__ }

#endif // CLASS_H

