#include "class.h"
#include <stdio.h>
#include <string.h>
int main() {
	//-------------------Animal Class-------------
	
    int c = 0;
	
    // Declare class Animal
    DEFINE_CLASS(Animal, int height; double weight;);

    // Declare 'an' object
    
    
   	INITIALIZE_CLASS(Animal, an, 10, 3.14);//
   	//Animal an={10,3.14,"koi"};
    
    // Access and print attributes
    printf("Height:%d\n",an.height);
    printf("Weight:%f\n",an.weight);
    c = an.height + (int)an.weight;
    printf("Res:%d\n",c);


	//----------------------Person Class---------------------------//
    // Declare class Person
    DEFINE_CLASS(Person, char name[5]; int age; float height;);

    // Declare a person object
    Person person={"John", 25, 5.9}; //object allocation 2nd way
    
    
    // Access and print object attributes
    printf("Name:%s\n",person.name);
    printf("Age:%d\n",person.age);
    printf("Height:%f\n",person.height);
    
    
    
	//--------------------Tree Class---------------------------------//
    //Declare class Tree
    DEFINE_CLASS(Tree, char name[9]; int width; float height;);
    
    //Declare a tr object
    /*Tree tr={.name="mango",.width=40,.height=621.65};//note this may not supported in old compilers ,also cannot change order of variables

	printf("NAME:%s\n",tr.name);
	printf("width:%d\n",tr.width);
	printf("height%d\n",tr.height);
*/

	//--------------------Car Class---------------------------------
	//Declare class Car
	DEFINE_CLASS(Car,char* name;const char *type;int year;char brand[6];);
	
	//Declare car object //3rd way initialization
	Car cr;
	cr.name=strdup("mustang");
	cr.type="sport";
	cr.year=1994;
	strcpy(cr.brand,"ford"); //require <string.h>
	
	printf("Name:%s\n",cr.name);
	printf("year:%d\n",cr.year);
	printf("brand:%s\n",cr.brand);
    
    
    //-------------------PC Class-----------------
    DEFINE_CLASS(PC,const char *name;int year;);
    PC p2={"dell",2006};
    
    printf("name:%s\n",p2.name);
    printf("year:%d\n",p2.year);
    p2.year=2003;//this way override values
    printf("year:%d\n",p2.year);
    
    
	//-------------------Dress Class-------------
	DEFINE_CLASS(DRESS,const char*type;);
	DRESS dr;
	DEFINE_CLASS(DRESS2,DRESS dr;int price;);
	DRESS2 dr2;
	dr2.dr.type="overcoat"; //accessing parent class attributes and reassigning them
	dr2.price=10000;
	
	printf("dr2 price:%d\n",dr2.price);
    
    return 0;
}

