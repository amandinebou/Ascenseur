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
    if (personInside == NULL) {
        return 0;
    }
    int compteur = 0;
    //pointeur temporaire pour parcourir la liste
    PersonList *temp = (PersonList*)malloc(sizeof(PersonList));
    temp = personInside;
    while (temp -> person != NULL) {
        compteur++;
        temp = temp -> next;
    }
    return compteur;
}

PersonList* enterElevator(Elevator*e, PersonList *waitinglist) {
  //vérifie qu'il reste de la place dans l'ascenseur
  int placesDispo = (e -> capacity) - occupation(e);
  //tant qu'il y a de la place dans l'ascenseur on ajoute des personnes
  while (placesDispo > 0 && waitinglist != NULL) {
      Person* passager = (Person*)malloc(sizeof(Person));
      passager = waitinglist -> person;
      (e -> persons) = insert(passager, e -> persons);
      //on retire les personnes de la liste d'attente
      waitinglist = waitinglist -> next;
      placesDispo--;
  }
  return waitinglist;
}

PersonList* exitElevator(Elevator *e) {
  //personnes présentent dans l'ascenseur
  PersonList* personInside = (PersonList*)malloc(sizeof(PersonList));
  personInside = e -> persons;
  //on supprime les premiers qui veulent sortir
  while (personInside != NULL && (personInside -> person) -> dest == e -> currentFloor) {
      personInside = personInside -> next;
  }
  //on regarde les suivants
  if (personInside != NULL) {
      PersonList *precedent = (PersonList*)malloc(sizeof(PersonList));
      PersonList *personne = (PersonList*)malloc(sizeof(PersonList));
      //on retient la position précédente de la personne regardée pour faire un saut dans la liste chainee
      precedent = personInside;
      personne = precedent -> next;
      while (personne != NULL) {
          //on élimine ceux qui veulent descendre et qui sont collées 
          while (personne != NULL && (personne -> person) -> dest == e -> currentFloor) {
              personne = personne -> next;
              precedent -> next = personne;
          }
          if (personne != NULL) {
            precedent = personne;
            personne = personne -> next;
          }
      }
  }
  return personInside;
}


void stepElevator(Building *b) {
    Elevator* e = (Elevator*)malloc(sizeof(Elevator));
    e = b -> elevator;
    //si l'étage actuel est la destination de l'ascenseur : on fait entrer et descendre les personnes de cet étage
    if (e -> targetFloor == e -> currentFloor) {
        e -> persons = exitElevator(e);
        (b -> waitingLists)[ e-> currentFloor] = enterElevator(e, (b -> waitingLists)[ e-> currentFloor]);
    } else {
        //sinon on incrémente ou décrémente l'étage de l'ascenseur pour aller dans la direction de la destination
        if ((e -> targetFloor) - (e -> currentFloor > 0)) {
            (e -> currentFloor)++;
        } else {         
            (e -> currentFloor)--;
        }
    }
}
