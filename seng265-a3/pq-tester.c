#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "emalloc.h"

#define MAX_LINE_LEN 5000

void inccounter(Patient *p, void *arg) {
    /* DO NOT CHANGE THIS FUNCTION. */
    int *ip = (int *)arg;
    (*ip)++;
}


void print_word(Patient *p, void *arg) {
    /* DO NOT CHANGE THIS FUNCTION. */
    char *fmt = (char *)arg;
    printf(fmt, p->name, p->birth_year, p->priority);
}


void dump(Patient *list) {
    /* DO NOT CHANGE THIS FUNCTION. */
    int len = 0;

    apply(list, inccounter, &len);    
    printf("Number of patients: %d\n", len);

    apply(list, print_word, "%s,%d,%d\n");
}

Patient *tokenize_line(char *line) {
	char *token = strtok(line, ",\n"); //gets the first token to figure out if this is an enqueue or dequeue statement 
	if (strcmp(token, "enqueue") == 0){ //if enqueue statement, grabs all other tokens from the line and uses them to create a new patient
		char *patientName = strtok(NULL, ",\n");
		int patientBirthdate = atoi(strtok(NULL, ",\n"));
		int patientPrio = atoi(strtok(NULL, ",\n"));
		return new_patient(patientName, patientBirthdate, patientPrio); //returns new patient
	} else {
		return NULL; //returns NULL if this is a dequeue statement
	}
    /* TODO: You have to implement this function to tokenize a line
        and either:
        1) return a valid Patient pointer if the line command is enqueue
        2) return NULL if the line command is dequeue
    */
	
}

Patient *read_lines(Patient *list) {
	char str[50];
	while(fgets(str, 50 , stdin) != NULL){ //gets the list of patients and tokenize one line at a time from stdin
		Patient *newPatient = tokenize_line(str);
		if (newPatient != NULL){ //if the patient is enqueue, adds with priority to list, dequeues if otherwise (only other case)
			list = add_with_priority(list, newPatient);
		} else {
			list = remove_front(list);
		}
	}
	return list;
    /* TODO: You have to implement this function to tokenize all lines
        from the stdin. You HAVE TO use the tokenize_line function
        as an auxiliary function to parse each line.
        If tokenize_line returns a valid Patient pointer, add the
        patient to the list with the correct priority.
        Otherwise, dequeue the first patient from the list.
        At the end of the function, return the list to the caller.       
    */
	
}

void deallocate_memory(Patient *list) {
    /* TODO: You have to implement this function to deallocate (free) 
        memory from the list before the program ends
    */
	Patient *curr; //makes a generic current patient for iterating through the list
	
	while (list != NULL){ //while the list is not empty, iterates through each patient in the list and free them, deallocate all memory associated with the list
		curr = list;
		list = list->next;
		free(curr);
	}
    }  


int main(int argc, char *argv[]) {
    /* DO NOT CHANGE THE MAIN FUNCTION. YOU HAVE TO IMPLEMENT YOUR
        CODE TO FOLLOW THE SEQUENCE OF INSTRUCTIONS BELOW. */
    Patient *list = NULL;

    if (argc != 1) {
            printf("Usage: %s\n", argv[0]);
            printf("Should receive no parameters\n");
            printf("Read from the stdin instead\n");
            exit(1);
    }

    list = read_lines(list);

    dump(list);
    
    deallocate_memory(list);

    exit(0); 
}
