#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct person* position; //position je tip koji predstavlja pokazivac na person
typedef struct person{
    char fname[32];
    char lname[32];
    int birth_year;
    position next;
}person;

int main(){

person head = {.fname ="",.lname ="", birth_year = 0, .next = NULL}
//head kao dummy element
//.fname = "" znaci da nema imena kada se lista kreira
//birth_year = 0 znaci a godina nije unesena 
//.next = NULL to znaci da lista trenuetno ne sadrz druge cvorove
//head sluzi kao referenca za olaksavanje operacija
//head se koristi kao polazisna tocka za sve operacije - referentna tocka, pocetna tocka liste


    return 0;
}

position create_person(char* fname, char* lname, int* year);//vraca pokazivac na novu osobu , zato position
position new_person = NULL; //moramo je alocirati, pokazuje na novo alociranu memoriju za osobu

new_person = (position*)malloc(sizeof(person));
//alocira se memorija velicine strukture person , a rezultat se pretvara u tip position
if(new_person == NULL){
    printf("Neupsjesno alocirana memorija.\n");
    return NULL; //NULL jer je pointer

    strcpy(new_person->fname, fname);
    //kopira sadrza stringa fname u fname novog cvora
    strcpy(new_person->lname, lname);
   new_person->birth_year = *year;
   //*year kakoo bi se dobila stvarna vrijednost godine koja je unesena 
   //trebamo staviti *year kako bi dereferencirali pokazivac na godinu, trebamo dobiti vrijednost na toj adresi, a ako stavimo samo year dobit mi prosljedjujemo adresu jer smo u fuknciji stavili int *year

   new_person->next = NULL; //next pokazivac se postavlja na NULL, sto znaci da novi cvor ne pokazuje ni na jedan drugi cvor

   return new_person; //vraca informacije o osobi

}

//dodavanje novog elementa na pocetak liste
int prepend_list(position head, char* fname, char* lname, int* year){
    //prima position head - pokazivac na prvi element
    position new_person = NULL;

    new_person = create_person(fname,lname,year);
    //stvara se novi cvor s proslijedjenim imenom,prezimeom i godinom rodjenja
    if(new_person == NULL){
        printf("Nesupjesno alocirana memorija.\n");
        return -1; //oznaka za gresku
    }

    insert_after(head,new_person);
    //ako je nova osoba uspjesno stvorena poziva se funkcija koja umece new_person nakon head. To znaci da ce nova osoba postati prvi element liste, a head ostaje kao dummy element
}

void insert_after(position prev, position new){ //void jer ne vraca nkkavu vrijednost, njen cilj je samo promijeniti listu bez potrebe za nekom informacijom
    if(prev!=NULL && new!=NULL){//ovim se osigurava da se ne pokusa umetnuti element nakon nepostojeceg elementa
        new->next = prev->next;
        prev->next = new;
    }
}

//funkcija za ispis liste
int print_list(position first){
    //funkcija prima pokazivac na prvi cvor u listi, to moze biti headcvor ili prvi stvarni cvor u listi
    position temp = first; //temp sluzi ta iteraciju kroz listu

    while(temp!=NULL){
        //ispisuje sve cvorove dok ne dodje do kraja
        printf("%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;
    }

    return 0;
}

//funkcija za dodavanje na kraj

int append_list(position head, char* fname, char* lname, int* year){

    position new_person = create_person(fname, lname, year);
    if(new_person == NULL){
        printf("Greska.\n");
        return -1;
    }
    position_last = find_last(head);
     //poziva se funkcija koja pronalazi posljednji cvor u listi
     //iterira kroz listu dok ne dosegne cvor ciji je next jednak nula
    last->next = new_person; //postavlja last->next na new_person, time se novi cvor dodaje na kraj liste
    return 0;
}

position find_last(position head){
    //prima pokazivac na prvi cvor u listi
    position temp = head;
    //deklarira i inicijalizira privremeni pokazivač temp koji će se koristiti za iteraciju kroz listu 
    //Inicijalizira se na head, što predstavlja prvi čvor.

    while(temp > next!= NULL){
        //petlja se nastavlja sve dok postoji sljedeci cvor
        temp = temp-next;
    }

    return temp;
}