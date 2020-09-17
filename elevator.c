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
      free(passager);
  }
  return waitinglist;
}

PersonList* exitElevator(Elevator *e) {
  //personnes présentent dans l'ascenseur
  PersonList* personInside = (PersonList*)malloc(sizeof(PersonList));
  personInside = e -> persons;
  if (personInside != NULL) {
      //si le premier dans l'ascenseur doit sortir
      if ((personInside -> person) -> dest == e -> currentFloor) {
          Person *p = personInside -> person;
          personInside = personInside -> next;
          free(p);
      }
      PersonList *precedent = (PersonList*)malloc(sizeof(PersonList));
      PersonList *personne = (PersonList*)malloc(sizeof(PersonList));
      precedent = personInside;
      personne = personInside -> next;
      while (personne != NULL) {
          //vérification que la personne veut descendre
          if ((personne -> person) -> dest == e -> currentFloor) {
              Person *p = 
            //suppression de la personne qui quitte l'ascenseur
            precedent -> next = personne -> next;
          }
          precedent = personne;
          personne = personne -> next;
          
      }
      return personInside;
  } else {
      return NULL;
  }
}


void stepElevator(Building *b) {
    Elevator* e = (Elevator*)malloc(sizeof(Elevator));
    e = b -> elevator;
    //si l'étage actuel est la destination de l'ascenseur : on fait entrer et descendre les personnes de cet étage
    if (e -> currentFloor == e -> targetFloor) {
        e -> persons = exitElevator(e);
        e -> persons = enterElevator(e, (b -> waitingLists)[ e-> currentFloor]);
    } else {
        //sinon on incrémente ou décrémente l'étage de l'ascenseur pour aller dans la direction de la destination
        if ((e -> targetFloor) - (e -> currentFloor > 0)) {
            e -> currentFloor ++;
        } else {         
            e -> currentFloor --;
        }
    }
}
