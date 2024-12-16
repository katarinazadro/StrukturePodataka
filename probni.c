#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 100

// Struktura za direktorij
typedef struct Direktorij* direktorij;
typedef struct Direktorij {
    char naziv[MAX_NAZIV];           // Naziv direktorija
    direktorij lijevo;               // Lijevo podstablo (manji naziv)
    direktorij desno;                // Desno podstablo (veći naziv)
    direktorij roditelj;             // Pokazivač na roditeljski direktorij
} Direktorij;

// Deklaracija funkcije pronadjiPodDirektorij
direktorij pronadjiPodDirektorij(direktorij trenutni, const char* naziv);

// Funkcija za kreiranje novog direktorija
direktorij kreirajDirektorij(const char* naziv, direktorij roditelj) {
    direktorij novi = (direktorij)malloc(sizeof(Direktorij));
    if (novi == NULL) {
        printf("Greska pri alociranju memorije!\n");
        exit(1);
    }

    strcpy(novi->naziv, naziv);
    novi->lijevo = NULL;
    novi->desno = NULL;
    novi->roditelj = roditelj;

    return novi;
}

// Funkcija za dodavanje pod-direktorija u stablo (BST)
void dodajPodDirektorij(direktorij trenutni, const char* naziv) {
    // Provjeri da li direktorij već postoji
    if (pronadjiPodDirektorij(trenutni, naziv) != NULL) {
        printf("Direktorij '%s' već postoji.\n", naziv);
        return; // Ako postoji, izlazi bez dodavanja novog direktorija
    }

    direktorij novi = kreirajDirektorij(naziv, trenutni);

    direktorij temp = trenutni;
    direktorij prethodni = NULL;

    // Dodavanje novog direktorija u binarno stablo
    while (temp != NULL) {
        prethodni = temp;
        if (strcmp(novi->naziv, temp->naziv) < 0) {
            temp = temp->lijevo;
        } else {
            temp = temp->desno;
        }
    }

    // Dodajemo novi čvor u lijevo ili desno
    if (strcmp(novi->naziv, prethodni->naziv) < 0) {
        prethodni->lijevo = novi;
    } else {
        prethodni->desno = novi;
    }
}

// Funkcija za pretragu pod-direktorija u stablu
direktorij pronadjiPodDirektorij(direktorij trenutni, const char* naziv) {
    direktorij temp = trenutni;

    while (temp != NULL) {
        if (strcmp(temp->naziv, naziv) == 0) {
            return temp;  // Pod-direktorij je pronađen
        }
        if (strcmp(temp->naziv, naziv) < 0) {
            temp = temp->desno;
        } else {
            temp = temp->lijevo;
        }
    }

    return NULL;  // Ako nije pronađen direktorij
}

// Funkcija za ispis pod-direktorija u stablu
// Funkcija za ispis pod-direktorija u stablu
void ispisDirektorija(direktorij trenutni) {
    if (trenutni == NULL) return;

    // Ispis lijevog podstabla
    if (trenutni->lijevo != NULL) {
        ispisDirektorija(trenutni->lijevo);
    }

    // Ispis trenutnog direktorija ako to nije trenutni direktorij
    if (trenutni->roditelj != NULL) {  // Provjeravamo je li direktorij roditelj
        printf("%s\n", trenutni->naziv);  // Ispisujemo samo pod-direktorije
    }

    // Ispis desnog podstabla
    if (trenutni->desno != NULL) {
        ispisDirektorija(trenutni->desno);
    }
}
// Funkcija za povratak u roditeljski direktorij
direktorij cdUp(direktorij trenutni) {
    if (trenutni->roditelj != NULL) {
        return trenutni->roditelj;  // Vraća korisnika u roditeljski direktorij
    }
    return trenutni;  // Ako nema roditelja, ostaje u trenutnom direktoriju
}

// Funkcija za unos komandi u programu
void unosKomande(direktorij* trenutni) {
    int izbor;
    char naziv[MAX_NAZIV];

    while (1) {
        // Prikazivanje menija
        printf("\nMeni:\n");
        printf("1. md [naziv]\n");
        printf("2. cd [naziv]\n");
        printf("3. cd..\n");
        printf("4. dir\n");
        printf("5. Izlaz\n");
        printf("Unesite izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1:  // Kreiranje novog direktorija
                printf("Unesite naziv direktorija: ");
                scanf("%s", naziv);

                // Dodaj pod-direktorij
                dodajPodDirektorij(*trenutni, naziv);
                break;

            case 2:  // Ulazak u pod-direktorij
                printf("Unesite naziv pod-direktorija: ");
                scanf("%s", naziv);

                // Pronalaženje pod-direktorija
                direktorij podDirektorij = pronadjiPodDirektorij(*trenutni, naziv);
                if (podDirektorij != NULL) {
                    *trenutni = podDirektorij;  // Ulazak u pod-direktorij
                    printf("Ušli ste u direktorij '%s'.\n", naziv);
                } else {
                    printf("Pod-direktorij '%s' ne postoji.\n", naziv);
                }
                break;

            case 3:  // Povratak u roditeljski direktorij
                *trenutni = cdUp(*trenutni);
                printf("Vratili ste se u roditeljski direktorij.\n");
                break;

            case 4:  // Ispis pod-direktorija
                printf("Ispis sadržaja direktorija '%s':\n", (*trenutni)->naziv);
                ispisDirektorija(*trenutni);
                break;

            case 5:  // Izlaz iz programa
                printf("Izlaz iz programa.\n");
                return;

            default:
                printf("Nepoznata komanda!\n");
        }
    }
}

int main() {
    // Kreiranje root direktorija
    direktorij root = (direktorij)malloc(sizeof(Direktorij));
    strcpy(root->naziv, "root");
    root->lijevo = NULL;
    root->desno = NULL;
    root->roditelj = NULL;

    direktorij trenutni = root;  // Trenutni direktorij je root

    // Pokretanje menija
    unosKomande(&trenutni);

    // Oslobađanje memorije
    free(root);
    return 0;
}