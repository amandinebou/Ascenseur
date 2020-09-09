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
    PersonList *temp = personInside;
    while (temp -> person != NULL) {
        compteur++;
        temp = temp -> next;
    }
    return compteur;
}

PersonList* enterElevator(Elevator*e, PersonList *waitinglist) {
  //vérifie qu'il reste de la place dans l'ascenseur
  int placesDispo = (e -> capacity) - occupation(e);
  PersonList *temp = waitinglist;
  while (placesDispo > 0 && waitinglist != NULL) {
      Person *passager = temp -> person;
      (e -> persons) = insert(passager, e -> persons);
      temp = temp -> next;
  }

  //si scr = currenFloor : ajoutés e*persons
  //supprimé wainting list

}

PersonList* exitElevator(Elevator *e) {
  PersonList* personInside = (PersonList*)malloc(sizeof(PersonList));
  personInside = e -> persons;
  if (personInside != NULL) {
      PersonList *precedent = personInside;
      PersonList *suivant = precedent;
      if (precedent -> next == NULL && ((precedent -> person) -> dest = e -> currentFloor)) {
        return NULL;
      }
      while (precedent -> next != NULL) {
          //vérification que la personne veut descendre
          if ((precedent -> person) -> dest == e -> currentFloor) {
            //suppression de la personne qui quitte l'ascenseur
            precedent -> next = suivant -> next;
            return personInside;
          }
      }
  } else {
      return NULL;
  }
}


void stepElevator(Building *b) {

}