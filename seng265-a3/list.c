/*
 * linkedlist.c
 *
 * Based on the implementation approach described in "The Practice 
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"


Patient *new_patient(char *name, int birth_year, int priority) {
    assert( name != NULL);

    Patient *temp = (Patient *)emalloc(sizeof(Patient));

    temp->name       = strdup(name);
    temp->birth_year = birth_year;
    temp->priority   = priority;
    temp->next       = NULL;

    return temp;
}


Patient *add_front(Patient *list, Patient *new) {
    new->next = list;
    return new;
}


Patient *add_end(Patient *list, Patient *new) {
    Patient *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}


Patient *add_with_priority(Patient *list, Patient *new) {
	if (list == NULL || new->priority < list->priority) {
		return add_front(list, new); //add to front if list is NULL or priority of front is lower than the new patient
	} else {
		Patient *curr = list;
		while (curr->next != NULL && new->priority >= curr->next->priority) {
			curr = curr->next; //if the list is not null, and the priority of the currently searched patient is less than the new patient, iterate through until found
		}
		new->next = curr->next;
		curr->next = new;
		return list; //add the new patient to the list and return
	}
    /* TODO: You have to implement this method to add patients with the
        correct priority in the list. Recall that a patient with higher
        priority must come before patients with lower priority. Also
        recall that a patient with the same priority as other patients
        must come after those patients, and before patients with lower
        priority.
        In the emergency room, higher priority means a smaller number 
        than lower priority. For instance, a patient with priority 1  
        has a higher priority than a patient with priority 2. */
}


Patient *peek_front(Patient *list) {
    return list;
}


Patient *remove_front(Patient *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}


void apply(Patient *list,
           void (*fn)(Patient *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}
