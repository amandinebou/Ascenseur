#ifndef PERSON_H
#define PERSON_H

typedef struct _Person {
    int src;    //provenance
    int dest;   //destination
} Person;

typedef struct _PersonList {
    Person *person;
    struct _PersonList *next;
} PersonList;

Person* createPerson(int src, int dest);
PersonList* insert(Person *p, PersonList *list);

#endif
