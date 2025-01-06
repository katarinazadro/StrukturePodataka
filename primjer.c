#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person* position;
typedef struct person {
    char fname[32];
    char lname[32];
    int birth_year;
    position next;
} person;

// Funkcija za kreiranje novog osobe
position create_person(char* fname, char* lname, int year) {
    position new_person = (position)malloc(sizeof(person));
    if (new_person == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        return NULL;
    }

    strcpy(new_person->fname, fname);
    strcpy(new_person->lname, lname);
    new_person->birth_year = year;
    new_person->next = NULL;

    return new_person;
}

// Funkcija za dodavanje osobe na početak liste (prepend)
int prepend_list(position* head, char* fname, char* lname, int year) {
    position new_person = create_person(fname, lname, year);
    if (new_person == NULL) {
        printf("Greska.\n");
        return -1;
    }

    new_person->next = *head;  // Novi element postavljamo ispred trenutnog head-a
    *head = new_person;         // Ažuriramo glavu liste

    return 0;
}

// Funkcija za umetanje novog elementa posle postojećeg elementa
void insert_after(position prev, position new) {
    if (prev != NULL && new != NULL) {
        new->next = prev->next;
        prev->next = new;
    }
}

// Funkcija za ispis liste
int print_list(position first) {
    position temp = first;

    while (temp != NULL) {
        printf("%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }

    return 0;
}

// Funkcija za dodavanje osobe na kraj liste (append)
int append_list(position* head, char* fname, char* lname, int year) {
    position new_person = create_person(fname, lname, year);
    if (new_person == NULL) {
        printf("Greska.\n");
        return -1;
    }

    if (*head == NULL) {  // Ako je lista prazna, novi element postavljamo kao head
        *head = new_person;
    } else {
        position last = *head;
        while (last->next != NULL) {  // Nalazimo poslednji element
            last = last->next;
        }
        last->next = new_person;  // Dodajemo na kraj
    }

    return 0;
}

// Funkcija za pronalaženje poslednjeg elementa u listi
position find_last(position head) {
    position temp = head;

    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }

    return temp;
}

// Funkcija za pronalaženje osobe po prezimenu
position find_by_last(position first, char* lname) {
    position temp = first;
    while (temp != NULL) {
        if (strcmp(temp->lname, lname) == 0) {
            return temp;  // Vraćamo osobu sa odgovarajućim prezimenom
        }
        temp = temp->next;
    }
    return NULL;  // Ako nismo našli, vraćamo NULL
}

// Funkcija za brisanje osobe sa liste
position delete(position* head, position wanted) {
    if (*head == wanted) {
        position temp = *head;
        *head = (*head)->next;  // Ažuriramo glavu liste
        free(temp);  // Oslobađamo memoriju
        return *head;
    }

    position previous = find_previous(*head, wanted);
    if (previous != NULL) {
        previous->next = wanted->next;
        free(wanted);  // Oslobađamo memoriju
    }

    return *head;
}

// Funkcija za pronalaženje prethodnog elementa
position find_previous(position head, position wanted) {
    position temp = head;

    while (temp != NULL) {
        if (temp->next == wanted) {
            return temp;  // Vraćamo prethodni element
        }
        temp = temp->next;
    }

    return NULL;  // Ako nismo našli prethodni element
}

int main() {
    position head = NULL;  // Početna glava liste je NULL

    // Dodavanje osoba u listu
    append_list(&head, "John", "Doe", 1980);
    append_list(&head, "Jane", "Smith", 1990);
    prepend_list(&head, "Alice", "Johnson", 1975);

    // Ispisivanje liste
    print_list(head);

    // Pronalaženje osobe po prezimenu
    position person = find_by_last(head, "Smith");
    if (person != NULL) {
        printf("Pronadjena osoba: %s %s %d\n", person->fname, person->lname, person->birth_year);
    }

    // Brisanje osobe iz liste
    head = delete(&head, person);

    // Ispisivanje liste nakon brisanja
    printf("Lista nakon brisanja:\n");
    print_list(head);

    return 0;
}
