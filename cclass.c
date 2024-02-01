#include "class.h"
#include <stdio.h>

int main() {
    int c = 0;

    // Declare a "Animal" class with variable attributes
    DEFINE_CLASS(Animal, int height; double weight;);

    // Declare an object of the "Animal" class and initialize it
    INITIALIZE_CLASS(Animal, an, 10, 3.14);

    // Access and print object attributes
    printf("Height: %d\n", an.height);
    printf("Weight: %f\n", an.weight);

    // Perform the operation
    c = an.height + (int)an.weight;

    // Print the result
    printf("Result: %d\n", c);

    // Declare a "Person" class with variable attributes
    DEFINE_CLASS(Person, char name[50]; int age; float height;);

    // Declare an object of the "Person" class and initialize it
    INITIALIZE_CLASS(Person, person, {'J', 'o', 'h', 'n'}, 25, 5.9);

    // Access and print object attributes
    printf("Name: %s\n", person.name);
    printf("Age: %d\n", person.age);
    printf("Height: %f\n", person.height);

    return 0;
}

