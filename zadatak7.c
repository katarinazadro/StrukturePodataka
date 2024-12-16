#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 100

// Definicija strukture za direktorij (dvostruko vezana lista)
typedef struct Direktorij* direktorij;
typedef struct Direktorij {
    char naziv[MAX_NAZIV];   
    direktorij sljedeci;     
    direktorij prethodni;    
    direktorij roditelj;     
} Direktorij;

// Funkcija za kreiranje novog direktorija
direktorij kreirajDirektorij(const char* naziv, direktorij roditelj) {
    direktorij novi = (direktorij)malloc(sizeof(Direktorij));
    if (novi == NULL) {
        printf("Greska pri alociranju memorije!\n");
        exit(1);
    }

    strcpy(novi->naziv, naziv);
    novi->sljedeci = NULL;
    novi->prethodni = NULL;
    novi->roditelj = roditelj;

    return novi;
}

// Funkcija za dodavanje pod-direktorija u listu
void dodajPodDirektorij(direktorij trenutni, const char* naziv) {
    direktorij novi = kreirajDirektorij(naziv, trenutni);

    // Ako trenutni direktorij nije NULL, dodaj novi direktorij na kraj liste
    if (trenutni != NULL) {
        direktorij temp = trenutni;
        while (temp->sljedeci != NULL) {
            temp = temp->sljedeci;  // Prelazimo do kraja liste
        }
        temp->sljedeci = novi;   // Dodajemo novi direktorij na kraj
        novi->prethodni = temp;  // Postavljamo prethodni direktorij
    } else {
        trenutni = novi;  // Ako je lista prazna, novi postaje prvi direktorij
    }
}

// Funkcija za pretragu pod-direktorija u listi
direktorij pronadjiPodDirektorij(direktorij trenutni, const char* naziv) {
    direktorij temp = trenutni->sljedeci;  
    while (temp != NULL) {
        if (strcmp(temp->naziv, naziv) == 0) {
            return temp;  
        }
        temp = temp->sljedeci;  // Nastavljamo dalje kroz listu
    }
    return NULL; 
}

// Funkcija za ispis poddirektorija
void ispisDirektorija(direktorij trenutni) {
    direktorij temp = trenutni->sljedeci;  
    if (temp == NULL) {
        printf("Direktorij je prazan.\n");
    }
    while (temp != NULL) {
        printf("%s\n", temp->naziv);  // Ispisujemo naziv poddirektorija
        temp = temp->sljedeci;  
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
        printf("1. md [naziv] - Kreira novi direktorij\n");
        printf("2. cd [naziv] - Ulazi u pod-direktorij\n");
        printf("3. cd.. - Povratak u roditeljski direktorij\n");
        printf("4. dir - Ispis sadržaja direktorija\n");
        printf("5. Izlaz - Završava program\n");
        printf("Unesite izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1:  // Kreiranje novog direktorija
                printf("Unesite naziv direktorija: ");
                scanf("%s", naziv);

                // Provjeriti ako direktorij c postoji
                if (pronadjiPodDirektorij(*trenutni, naziv) != NULL) {
                    printf("Direktorij '%s' vec postoji.\n", naziv);
                    break;
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
                printf("Ispis sadrzaja direktorija '%s':\n", (*trenutni)->naziv);
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
    root->sljedeci = NULL; 
    root->prethodni = NULL;
    root->roditelj = NULL;

    direktorij trenutni = root;  // Trenutni direktorij je root

    
    unosKomande(&trenutni);


    free(root);
    return 0;
}