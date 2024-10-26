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


person head = {.fname = "", .lname = "", .birth_year = 0, .next = NULL};    // prazna lista
    return 0;

}

// funkcija za izradu osobe
position create_person(char* fname, char* lname, int* year){
    position new_person = NULL;
 new_person = (position)malloc(sizeof(person)); //alokacija potrebne memorije za novu osobu
 if(new_person == NULL){
    printf("Greska pri alokaciji memorije.\n");
    return NULL;
 }
 strcpy(new_person->fname,fname);
 strcpy(new_person->lname,lname);
 new_person->birth_year = *year; 
 new_person->next = NULL;

 return new_person;
}

int prepend_list(position head, char* fname, char* lname, int *year){

    position new_person = create_person(fname,lname,year);
    if(new_person == NULL){
        printf("Greska.\n");
        return -1;
    }
    insert_after(head, new_person);
    return 0;

}

void insert_after(position prev, position new){

    if(prev != NULL && new != NULL){
        new->next = prev->next;
        prev->next = new;
    }

}

int print_list(position first){
    position temp = first;

    while(temp != NULL){
        printf("%s %s %d\n", temp->fname, temp->lname,temp->birth_year);
        temp = temp->next;
    }

    return 0;
}

int append_list(position head, char* fname, char* lname, int* year){
    position new_person = create_person(fname,lname,year);
    if(new_person == NULL){
        printf("Greska.\n");
        return -1;
    }

    position last = find_last(head);
    last->next = new_person;

    return 0;
}

position find_last(position head){
    position temp = head;

    while(temp->next !=NULL){
        temp = temp->next;

    }

    return temp;

}

position find_by_last(position first, char* lname){
    position temp = first;

while(temp!=NULL){
    if(strcmp(temp->lname, lname) == 0){
        return temp;
    }

    temp = temp->next;
}

return NULL;

}

position delete(position head, position wanted){
    position temp = head;

    if(head == wanted){
        head = head->next;

        free(wanted);
        return head;
    }

    position previous = find_previous(head, wanted);
    if(previous == NULL){
        head->next = wanted->next;

        free(wanted);
    }


}

position find_previous(position head, position wanted){
    position temp = head;

    while(temp->next!=NULL){
        if(temp->next == wanted){
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}