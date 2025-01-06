#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct person* position;
typedef struct person{
    char fname[32];
    char lname[32];
    int birth_year;
    position next;
}person;

position create_person(char* fname, char* lname, int year);
int append_list(position head, char* fname,char* lname, int year);
int prepend_list(position head, char* fname, char* lname , int year);
position find_last(position head);
position find_by_last(position first, char* lname);
int printf_list(position first);
position find_previous(position head, position wanted);
position delete(position head, position wanted);
int main(){

person head = {.fname = "", .lname = "", .birth_year = 0, .next = NULL};
int izbor;
char fname[32], lname[32];
int year;

position first = &head;

while(1){
    printf("\nMeni:\n");
        printf("1. Dodaj osobu na kraj\n");
        printf("2. Dodaj osobu na pocetak\n");
        printf("3. Prikazi sve osobe\n");
        printf("4. Pronađi osobu po prezimenu\n");
        printf("5. Obriši osobu\n");
        printf("6. Izlaz\n");
        printf("Unesite izbor: ");
        scanf("%d", &izbor);
        getchar();

        switch(izbor){
            case 1:
            printf("Uneiste ime, prezime i godinu rodjenja osobe koju zelite unijeti :");
            scanf("%s %s %d", first->fname,first->lname,first->birth_year);
            append_list(first, fname, lname , year);
            break;

            case 2:
            printf("Uneiste ime, prezime i godinu rodjenja osobe koju zelite unijeti :");
            scanf("%s %s %d", first->fname,first->lname,first->birth_year);
            prepend_list(first, fname, lname , year);
            break;

            case 3:
            printf("Ispis svih osoba :\n");
            print_list(first);
            break;

            case 4:
            printf("Unesite prezime osobe koju zelite pronaci: ");
            scanf("%s", fname);
            position found_person = find_by_last(first, lname);
            if(found_person!=NULL){
                printf("Osoba pronadjena : %s %s. Godina rodjenja : %d", found_person->fname, found_person->lname, found_person->year);
                
            }
            else {
                printf("Osoba nije pronadjena.\n");

            }
            break;

            case 5:
            printf("Unesite prezime osobe koju zelize obrisati:\n");
            scanf("%s", fname);
            position found_person = find_by_last(first, lname);
            if(found_person!=NULL){
                first = delete(first, found_person);
                printf("Osoba %s %s obrisana.\n", found_person->fname, found_person->lname);
              

            }
            break;

            case 6:
                printf("Izlaz iz programa.\n");
                return 0;

                default :
                printf("Nepoznata opcija.\n");

        }
    
}

    return 0;
}

position create_person(char* fname, char* lname, int year){
    position new_person = NULL;
    new_person = (position)malloc(sizeof(person));
    if(new_person==NULL){
        printf("Greska pri alokaciji memorije.\n");
        return NULL;
    }
    strcpy(new_person->fname,fname);
    strcpy(new_person->lname,lname);
    new_person->birth_year = year;
    new_person->next = NULL;

    return new_person;
}

int prepend_list(position head, char* fname, char* lname, int year){
    position new_person = NULL;
    new_person = create_person(fname,lname,year);
    if(new_person==NULL){
        printf("Greska.\n");
        return -1;
    }

    new_person->next = head->next;
    head->next = new_person;

    return 0;

}

int append_list(position head, char* fname, char* lname, int year){
    position new_person = NULL;
    new_person = create_person(fname,lname,year);
    if(new_person==NULL){
        printf("Greska.\n");
        return -1;
    }

    position last = find_last(head);
    last->next = new_person;
    return 0;
}

position find_last(position head){
    position temp = head;

    while(temp->next!=NULL){
        temp = temp->next;
       
    }

    return temp;
}

int print_list(position first){
    position temp = first;
    while(temp!=NULL){
    printf("%s %s %d\n\n", temp->fname,temp->lname, temp->birth_year);
    temp = temp->next;
    }
    return 0;
}

position delete(position head, position wanted){
    if(head == wanted){
        free(wanted);
        return head;
    }

    position previous = find_previous(head,wanted);
    if(previous != NULL){
        previous->next = wanted->next;
        free(wanted);
    } 
    return head;


}

position find_previous(position head, position wanted){
    position temp = head;
    while(temp!=NULL){
        if(temp->next == wanted){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

position find_by_last(position head, char* lname){
    position temp = head;
    while(temp!=NULL){
        if(strcmp(temp->lname, lname) == 0){
        return temp;
        }
        temp = temp->next;
    }
    return NULL;
}