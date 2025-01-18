#ifndef CLASS_H
#define CLASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro for creating struct-based "classes"
#define CLASS(name) \
    typedef struct name name; \
    struct name

// Safer object creation without pointers
#define NEW(type) \
    (type){0}

// Method definition macro using value semantics
#define METHOD(type, name) \
    type name(type self)

// Immutable struct approach
#define IMMUTABLE_CLASS(name) \
    typedef const struct name name; \
    struct name

// Safe string handling
#define STRING_COPY(dest, src) \
    strncpy(dest, src, sizeof(dest) - 1)

// Error handling macro
#define VALIDATE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Error: %s\n", message); \
            exit(1); \
        } \
    } while(0)

// Example Implementation
CLASS(Person) {
    char name[50];
    int age;
};

// Constructor-like method
METHOD(Person, create_person) {
    Person p = {0};
    STRING_COPY(p.name, self.name);
    p.age = self.age;
    return p;
}

// Validation method
METHOD(Person, validate) {
    VALIDATE(strlen(self.name) > 0, "Name cannot be empty");
    VALIDATE(self.age > 0 && self.age < 120, "Invalid age");
    return self;
}

// Example usage
int main() {
    Person input = {"John Doe", 30};
    Person validated_person = create_person(input).validate();
    
    printf("Name: %s, Age: %d\n", 
           validated_person.name, 
           validated_person.age);
    
    return 0;
}

#endif // CLASS_H
