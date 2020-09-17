#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "elevator.h"

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons) {
    Elevator *elevator = (Elevator*)malloc(sizeof(Elevator));
    elevator -> capacity = capacity;
    elevator -> currentFloor = currentFloor;
    elevator -> persons = persons;
    return elevator;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists) {
    Building *building = (Building*)malloc(sizeof(Building));
    building -> nbFloor = nbFloor;
    building -> elevator = elevator;
    building -> waitingLists = waitingLists;
    return building;
}

//compte le nombre de personnes dans l'ascenseur
int occupation(Elevator *e) {
    PersonList* personInside = (PersonList*)malloc(sizeof(PersonList));
    personInside = e -> persons;
    int compteur = 0;
    if (personInside == NULL) {
        return 0;
    }
    PersonList *temp = (PersonList*)malloc(sizeof(PersonList));
    temp = personInside;
    while (temp -> person != NULL) {
        compteur++;
        temp = temp -> next;
    }
    free (temp);
    return compteur;
}

PersonList* enterElevator(Elevator*e, PersonList *waitinglist) {
  //vérifie qu'il reste de la place dans l'ascenseur
  int placesDispo = (e -> capacity) - occupation(e);
  PersonList *temp = (PersonList*)malloc(sizeof(PersonList));
  temp = waitinglist;
  while (placesDispo > 0 && waitinglist != NULL) {
      Person* passager = (Person*)malloc(sizeof(Person));
      passager = temp -> person;
      (e -> persons) = insert(passager, e -> persons);
      temp = temp -> next;
      waitinglist = temp;
  }
  free (temp);
  return waitinglist;
}

PersonList* exitElevator(Elevator *e) {
  PersonList* personInside = (PersonList*)malloc(sizeof(PersonList));
  personInside = e -> persons;
  if (personInside != NULL) {
      PersonList *precedent = (PersonList*)malloc(sizeof(PersonList));
      PersonList *suivant = (PersonList*)malloc(sizeof(PersonList));
      precedent = personInside;
      suivant = precedent;
      while ((precedent -> person) -> dest == e -> currentFloor && suivant != NULL) {
        precedent = suivant;
        suivant = suivant -> next;
      }
      while (precedent -> next != NULL) {
          suivant = precedent -> next;
          //vérification que la personne veut descendre
          if ((suivant -> person) -> dest == e -> currentFloor) {
            //suppression de la personne qui quitte l'ascenseur
            precedent -> next = suivant -> next;
          }
          precedent = precedent -> next;
      }
      free (precedent);
      free (suivant);
      return personInside;
  } else {
      return NULL;
  }
}


void stepElevator(Building *b) {
    /*Elevator* e = (Elevator*)malloc(sizeof(Elevator));
    e = b -> elevator;
    if (e -> currentFloor == e -> targetFloor) {
        e -> persons = exitElevator(e);
        e -> persons = enterElevator(e, (b -> waitingLists)[ e-> currentFloor]);
    } else {
        if (e -> targetFloor - e -> currentFloor > 0) {
            e -> currentFloor ++;
        } else {         
            e -> currentFloor --;
        }
    }*/
}