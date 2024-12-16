#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 100

typedef struct Direktorij* direktorij;
typedef struct Direktorij {
    char naziv[MAX_NAZIV];           // Naziv direktorija
    direktorij lijevo;               // Lijevo podstablo (manji naziv)
    direktorij desno;                // Desno podstablo (veci naziv)
    direktorij roditelj;             // Pokazivac na roditeljski direktorij
} Direktorij;

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

// Funkcija za dodavanje pod-direktorija u stablo
void dodajPodDirektorij(direktorij trenutni, const char* naziv) {
    direktorij novi = kreirajDirektorij(naziv, trenutni);

    direktorij temp = trenutni;
    direktorij prethodni = NULL;

    while (temp != NULL) {
        prethodni = temp;
        if (strcmp(novi->naziv, temp->naziv) < 0) {
            temp = temp->lijevo;
        } else {
            temp = temp->desno;
        }
    }


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
            return temp;
        }
        if (strcmp(naziv, temp->naziv) < 0) {
            temp = temp->lijevo;
        } else {
            temp = temp->desno;
        }
    }

    return NULL;  // Ako nije pronadjen direktorij
}

// Funkcija za ispis pod-direktorija u trenutnom direktoriju
void ispisDirektorija(direktorij trenutni) {
    if (trenutni == NULL) return;

    // Ispis samo trenutnih pod-direktorija
    if (trenutni->lijevo != NULL) {
        printf("%s\n", trenutni->lijevo->naziv);
        ispisDirektorija(trenutni->lijevo);
    }
    if (trenutni->desno != NULL) {
        printf("%s\n", trenutni->desno->naziv);
        ispisDirektorija(trenutni->desno);
    }
}

// Funkcija za povratak u roditeljski direktorij
direktorij cdUp(direktorij trenutni) {
    if (trenutni->roditelj != NULL) {
        return trenutni->roditelj;  
    }
    return trenutni;  // Ako nema roditelja, ostaje u trenutnom direktoriju
}

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

                // Provjeriti ako direktorij vec postoji
                if (pronadjiPodDirektorij(*trenutni, naziv) != NULL) {
                    printf("Direktorij '%s' vec postoji.\n", naziv);
                    return;
                }

                // Dodaj pod-direktorij u trenutni direktorij
                dodajPodDirektorij(*trenutni, naziv);
                printf("Direktorij '%s' uspjesno kreiran.\n", naziv);
                break;

            case 2:  // Ulazak u pod-direktorij
                printf("Unesite naziv pod-direktorija: ");
                scanf("%s", naziv);

                // Pronalazenje pod-direktorija
                direktorij podDirektorij = pronadjiPodDirektorij(*trenutni, naziv);
                if (podDirektorij != NULL) {
                    *trenutni = podDirektorij;  // Ulazak u pod-direktorij
                    printf("Usli ste u direktorij '%s'.\n", naziv);
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

    
    unosKomande(&trenutni);

    // Oslobadanje memoriju
    free(root);  
    return 0;
}
