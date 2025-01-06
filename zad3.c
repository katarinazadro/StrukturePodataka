#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct person* position;
typedef struct person{
    char fname[32];
    char lname[32];
    int birth_year;
    position next;
} person;

position create_person(char* fname, char* lname, int year);
int append_list(position head, char* fname, char* lname, int year);
int prepend_list(position head, char* fname, char* lname, int year);
position find_last(position head);
position find_by_last(position first, char* lname);
int printf_list(position first);
position find_previous(position head, position wanted);
position delete(position head, position wanted);
void print_int_file(position first);
void read_file(position first);
int insert_element_after(position head, char* lname, char* new_fname, char* new_lname, int new_year);
int insert_element_before(position head, char* lname, char* new_fname, char* new_lname, int new_year);

int main() {

    person head = {.fname = "", .lname = "", .birth_year = 0, .next = NULL};
    position first = &head;

    int izbor;
    char fname[32], lname[32];
    int birth_year;
    char new_fname[32], new_lname[32];
    int new_year;
    position found_person;

    while (1) {
        printf("\nMeni:\n");
        printf("1. Dodaj osobu na kraj\n");
        printf("2. Dodaj osobu na pocetak\n");
        printf("3. Prikazi sve osobe\n");
        printf("4. Pronađi osobu po prezimenu\n");
        printf("5. Obriši osobu\n");
        printf("6. Izlaz\n");
        printf("7. Upisivanje liste u datoteku\n");
        printf("8. Čitanje liste iz datoteke\n");
        printf("9. Dodaj osobu nakon određene osobe\n");
        printf("10. Dodaj osobu prije određene osobe\n");
        printf("Izbor: ");
        scanf("%d", &izbor);
        getchar();

        switch (izbor) {
            case 1:
                printf("Unesite ime, prezime i godinu rodjenja: ");
                scanf("%s %s %d", fname, lname, &birth_year);
                append_list(first, fname, lname, birth_year);
                break;

            case 2:
                printf("Unesite ime, prezime i godinu rodjenja: ");
                scanf("%s %s %d", fname, lname, &birth_year);
                prepend_list(first, fname, lname, birth_year);
                break;

            case 3:
                printf("\nLista svih osoba:\n");
                printf_list(first);
                break;

            case 4:
                printf("Unesite ime i prezime osobe koju zelite naci:");
                scanf("%s", lname);
                found_person = find_by_last(first, lname);
                if (found_person != NULL) {
                    printf("Osoba pronadjena: %s %s, godina rodjenja : %d\n", found_person->fname, found_person->lname, found_person->birth_year);
                }
                else {
                    printf("Osoba nije pronadjena.\n");
                }
                break;

            case 5:
                printf("Unesite prezime osobe koju zelite obrisati:");
                scanf("%s", lname);
                found_person = find_by_last(first, lname);
                if (found_person != NULL) {
                    first = delete(first, found_person);
                    printf("Osoba %s %s je obrisana.\n", found_person->fname, found_person->lname);
                }
                break;

            case 6:
                printf("Izlaz iz programa.\n");
                return 0;

            case 7:
                print_int_file(first);
                break;

            case 8:
                read_file(first);
                break;

            case 9:
                printf("Unesite prezime osobe nakon koje zelite dodati novu osobu: ");
                scanf("%s", lname);
                printf("Unesite ime, prezime i godinu rodjenja nove osobe: ");
                scanf("%s %s %d", new_fname, new_lname, &new_year);
                insert_element_after(first, lname, new_fname, new_lname, new_year);
                break;

            case 10:
                printf("Unesite prezime osobe ispred koje zelite dodati novu osobu: ");
                scanf("%s", lname);
                printf("Unesite ime, prezime i godinu rodjenja nove osobe: ");
                scanf("%s %s %d", new_fname, new_lname, &new_year);
                insert_element_before(first, lname, new_fname, new_lname, new_year);
                break;

            default:
                printf("Nepoznata opcija.\n");
        }

    }

    return 0;
}

// Funkcije za rad sa listom
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

int append_list(position head, char* fname, char* lname, int year) {
    position new_person = create_person(fname, lname, year);
    if (new_person == NULL) {
        printf("Greska.\n");
        return -1;
    }

    position last_person = find_last(head);
    last_person->next = new_person;
    return 0;
}

int prepend_list(position head, char* fname, char* lname, int year) {
    position new_person = create_person(fname, lname, year);
    if (new_person == NULL) {
        printf("Greska.\n");
        return -1;
    }
    new_person->next = head->next;
    head->next = new_person;
    return 0;
}

position find_last(position head) {
    position temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

position find_by_last(position first, char* lname) {
    position temp = first;
    while (temp != NULL) {
        if (strcmp(temp->lname, lname) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int printf_list(position first) {
    position temp = first->next;  // Preskakanje dummy head čvora
    while (temp != NULL) {
        printf("%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }
    return 0;
}

position delete(position head, position wanted) {
    if (head == wanted) {
        head = head->next;
        free(wanted);
        return head;
    }

    position previous = find_previous(head, wanted);
    if (previous != NULL) {
        previous->next = wanted->next;
        free(wanted);
    }
    return head;
}

position find_previous(position head, position wanted) {
    position temp = head;
    while (temp != NULL) {
        if (temp->next == wanted) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int insert_element_after(position head, char* lname, char* new_fname, char* new_lname, int new_year) {
    position target = find_by_last(head, lname);
    if (target == NULL) {
        printf("Osoba sa prezimenom '%s' nije pronadjena.\n", lname);
        return -1;
    }

    position new_person = create_person(new_fname, new_lname, new_year);
    if (new_person == NULL) {
        return -1;
    }

    // Umetanje novog elementa nakon pronađene osobe
    new_person->next = target->next;
    target->next = new_person;

    return 0;
}

int insert_element_before(position head, char* lname, char* new_fname, char* new_lname, int new_year) {
    position temp = head;
    // Prolazimo kroz listu dok ne pronađemo osobu s određenim prezimenom
    while (temp != NULL && temp->next != NULL) {
        if (strcmp(temp->next->lname, lname) == 0) {
            position new_person = create_person(new_fname, new_lname, new_year);
            if (new_person == NULL) {
                return -1;
            }

            // Umetanje novog elementa prije pronađene osobe
            new_person->next = temp->next;
            temp->next = new_person;

            return 0;
        }
        temp = temp->next;
    }

    printf("Osoba sa prezimenom '%s' nije pronadjena.\n", lname);
    return -1;
}

void print_int_file(position first) {
    FILE *fp = fopen("lista.txt", "w");
    if (fp == NULL) {
        printf("Datoteka se ne moze otvoriti.\n");
        return;
    }

    position temp = first->next;  // Skip dummy head node
    fprintf(fp, "IME PREZIME GODINA\n");

    while (temp != NULL) {
        fprintf(fp, "%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }

    fclose(fp);
}

void read_file(position first) {
    FILE *fp = fopen("lista.txt", "r");
    if (fp == NULL) {
        printf("Datoteka se ne moze otvoriti.\n");
        return;
    }

    char fname[32], lname[32];
    int birth_year;
    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);  // Skip the header line

    while (fscanf(fp, "%s %s %d", fname, lname, &birth_year) == 3) {
        append_list(first, fname, lname, birth_year);
    }

    fclose(fp);
}
