#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include <ncurses.h>

#include "person.h"

Person* createPerson(int src, int dest) {
    Person *personne = (Person*)malloc(sizeof(Person));
    personne -> src = src;
    personne -> dest = dest;
    return personne;
}

PersonList* insert(Person *p, PersonList *list) {
    //ajoute une personne à une liste d'attente
    PersonList *newPerson = (PersonList*)malloc(sizeof(PersonList));
    newPerson -> person = p;
    newPerson -> next = NULL;
    if (list == NULL)
    {
        return newPerson;
    }
    /* Insertion de l'élément à la fin de la liste : on la parcourt à l'aide d'un pointeur temporaire */
    PersonList *temp = (PersonList*)malloc(sizeof(PersonList));
    temp = list;
    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    temp -> next = newPerson;
    return list;
}