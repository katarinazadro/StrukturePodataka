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

int main(){

person head = {.fname = "", .lname = "", .birth_year = 0, .next = NULL};

return 0;
}

position create_person(char* fname, char* lname, int *year){
    position new_person = NULL;
    new_person = (position)malloc(sizeof(person));
    if(new_person == NULL){
        printf("Memorija nije uspjesno alocirana.\n");
        return NULL;
    }

    strcpy(new_person->fname,fname);
    strcpy(new_person->lname, lname);
    new_person->birth_year = *year;
    new_person->next = NULL;

    return new_person;
}

int prepend_list(position head, char* fname, char* lname, int* year){
    position new_person = NULL;
    new_person = create_person(fname,lname,year);
    if(new_person == NULL){
        printf("Greska.\n");
        return -1;
    }
    insert_after(head, new_person);
    return 0;
}

void insert_after(position prev, position new){
    if(prev != NULL && new != NULL){ //osiguravamo da postoje
        new->next = prev->next;
        prev->next = new;
    }
}

int print_list(position first){
    position temp = first;

    while(temp != NULL){
        printf("%s %s %d", temp->fname, temp->lname, temp->birth_year);
          temp = temp->next;
    }
  

    return 0;
}

int append_list(position head, char* fname, char* lname, int* year){
    position new_person = NULL;
    new_person = create_perosn(fname, lname,year);
        if(new_person == NULL){
            printf("Greska.\n");
            return -1;
        }
    position last = NULL;
        last = find_last(head);

        last->next = new_person;

        return 0;
    }

    position find_last(position head){
        position temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        return temp;
    }

    position find_by_last(position first, char* lname){
        position temp = first;
        while(temp != NULL){
            if(strcmp(temp->lname, lname) == 0){
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    position delete(position head, position wanted){
        if(head == wanted){
            head = head->next;
            free(wanted);
            return head;
        }
        position previous = NULL;
         previous = find_previous(head, wanted);
        if(previous!=NULL){
        previous->next = head->next;

        free(wanted);
        }
        return head;
    }

    position find_previous(position head, position wanted){
        position temp = head;
        while(temp->next != NULL){
            if(temp->next == wanted){
                return temp;
            }

            temp = temp->next;
        }

        return NULL;
    }

int insert_before(position* head, position target, char* fname, char* lname, int* year){ //ili naci prethodnika i isto kao pod a) find_previous + insert_after
    //koristimo *head kako bi ga mogli mijenjati u funkciji
    if(*head == NULL|| target == NULL){
        printf("Lista je prazna.\n");
        return -1;
    }
    //slucaj ako su head i target isti
if(*head == target){
    position new_person = create_person(fname,lname,year);
    if(new_person == NULL){
        printf("Greska.\n");
        return -1;
    }
    new_person->next = *head;
    *head = new_person; //azuriranje head-a
    return 0;
}
//pretrazivanje liste za pronalazak cvora
    position temp = *head;

    while(temp != NULL && temp->next != target){
        temp = temp->next;
    }

    if(temp == NULL){
        printf("Element nije pronaden u listi\n");
        return -1;
    }

    position q = create_person(fname, lname, year);
    if(q == NULL){
        printf("Greska pri alokaciji memorije.\n");
        return -1;
    }

    q->next = target;
    temp->next = q; //povezuje prethodni cvor sa novim cvorom
    
    return 0;
}


void print_in_file(position first){
    FILE *fp = NULL;
    fp = fopen("lista.txt", "w");
    if(fp == NULL){
        printf("Neuspjesno.\n");
        return;
    }

    position temp = first; //temp na prvi cvor liste

    fprintf(fp, "IME\tPREZIME\t\tGODINA RODJENJA\n");
    while(temp !=NULL){
        fprintf(fp,"%s %s %d\n",temp->fname, temp->lname,temp->birth_year);
        temp = temp->next; //prelazak na sljedeci cvor
    }
    fclose(fp);
}

void read_file(position* head, FILE* fp){
    fp = fopen("lista.txt", "r");
    if(fp == NULL){
        printf("Datoteka se ne moze otvoriti.\n");
        return;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp); //preskakanje zaglavlja

    char name[32], lname[32];
    int year;
    position last = NULL;

    while(fscanf(fp, "%s %s %d", name, lname, &year) == 3){
        position q = create_person(name,lname,year); //poziva se funkcija da alocira novi cvor i postavi vrijednos na osnovu procitanih podataka
        if(q == NULL){
            printf("Neuspjesna alokacija memorije.\n");
            fclose(fp);

            return;
        }
        if(*head == NULL){
            *head = q;
        }
        else{
            last->next = q;
        }
        last = q;
    }
    fclose(fp);
}

void insert_after(position head,char* fname, char* lname, int year){
    position new_person = NULL;
    new_person = create_person(fname,lname,year);
}