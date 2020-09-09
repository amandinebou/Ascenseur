#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

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
    PersonList *temp = list;
    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    temp -> next = newPerson;
    return list;
}



/*int main() {    //test des méthodes
    Person *p = createPerson(0, 2);
    Person *q = createPerson(1, 2);
    Person *t = createPerson(1, 3);
    printf("src = %d et dest = %d\n", p -> src, p -> dest);
    PersonList *list = NULL;
    list = insert(p, list);
    list = insert(q, list);
    list = insert(t, list);
    PersonList *temp = list;
    
    while (temp -> next != NULL) {
        printf("%d %d\n", (temp -> person) ->src, (temp -> person) -> dest);
        temp = temp -> next;
    }
    printf("%d %d\n", (temp -> person) ->src, (temp -> person) -> dest);
    return 0;
} */