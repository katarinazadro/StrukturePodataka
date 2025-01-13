#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Grad* grad;
typedef struct Grad {
    char naziv[50];
    int broj_stanovnika;
    grad next; 
} Grad;


typedef struct Drzava* drzava;
typedef struct Drzava {
    char naziv[50];
    drzava left;  
    drzava right; 
    grad gradovi; 
} Drzava;

drzava create_drzava(char* naziv);
grad create_grad(char* naziv, int broj_stanovnika);
grad insert_grad(grad head, char* naziv, int broj_stanovnika);
drzava insert_drzava(drzava root, char* naziv);
void ucitaj_gradovi(char* filename, grad* head);
void ucitaj_drzava(char* filename, drzava* root);
void ispis_gradova(grad head);
void inorder_drzava(drzava root);
void pretraga_gradova_drzave(drzava root, char* naziv_drzave, int broj_stanovnika);


drzava create_drzava(char* naziv) {
    drzava new = (drzava)malloc(sizeof(Drzava));
    if (new == NULL) {
        printf("Greška pri alokaciji memorije za državu.\n");
        return NULL;
    }
    strcpy(new->naziv, naziv);
    new->left = NULL;
    new->right = NULL;
    new->gradovi = NULL;
    return new;
}

grad create_grad(char* naziv, int broj_stanovnika) {
    grad new = (grad)malloc(sizeof(Grad));
    if (new == NULL) {
        printf("Greška pri alokaciji memorije za grad.\n");
        return NULL;
    }
    strcpy(new->naziv, naziv);
    new->broj_stanovnika = broj_stanovnika;
    new->next = NULL;
    return new;
}


grad insert_grad(grad head, char* naziv, int broj_stanovnika) {
    grad new = create_grad(naziv, broj_stanovnika);
    if (head == NULL || head->broj_stanovnika > broj_stanovnika ||
        (head->broj_stanovnika == broj_stanovnika && strcmp(head->naziv, naziv) > 0)) {
        new->next = head;
        return new;
    }

    grad temp = head;
    while (temp->next != NULL && (temp->next->broj_stanovnika < broj_stanovnika ||
           (temp->next->broj_stanovnika == broj_stanovnika && strcmp(temp->next->naziv, naziv) < 0))) {
        temp = temp->next;
    }
    new->next = temp->next;
    temp->next = new;
    return head;
}

drzava insert_drzava(drzava root, char* naziv) {
    if (root == NULL) {
        return create_drzava(naziv);
    }
    if (strcmp(naziv, root->naziv) < 0) {
        root->left = insert_drzava(root->left, naziv);
    } else if (strcmp(naziv, root->naziv) > 0) {
        root->right = insert_drzava(root->right, naziv);
    }
    return root;
}

void ucitaj_gradovi(char* filename, grad* head) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Greška pri otvaranju datoteke gradova: %s\n", filename);
        return;
    }

    char naziv[50];
    int broj_stanovnika;

    while (fscanf(fp, "%s %d\n", naziv, &broj_stanovnika) == 2) {
        *head = insert_grad(*head, naziv, broj_stanovnika);
    }

    fclose(fp);
}


void ucitaj_drzava(char* filename, drzava* root) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Greška pri otvaranju datoteke država: %s\n", filename);
        return;
    }

    char naziv[50];
    char datoteka_grad[50];

    while (fscanf(fp, "%s %s\n", naziv, datoteka_grad) == 2) {
        *root = insert_drzava(*root, naziv);

        drzava temp = *root;
        while (temp != NULL && strcmp(temp->naziv, naziv) != 0) {
            if (strcmp(naziv, temp->naziv) < 0) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        if (temp != NULL) {
            ucitaj_gradovi(datoteka_grad, &(temp->gradovi));
        }
    }

    fclose(fp);
}

void ispis_gradova(grad head) {
    while (head != NULL) {
        printf("%s (%d stanovnika)\n", head->naziv, head->broj_stanovnika);
        head = head->next;
    }
}


void inorder_drzava(drzava root) {
    if (root == NULL) {
        return;
    }
    inorder_drzava(root->left);
    printf("Država: %s\n", root->naziv);
    printf("Gradovi:\n");
    ispis_gradova(root->gradovi);
    inorder_drzava(root->right);
}


void pretraga_gradova_drzave(drzava root, char* naziv_drzave, int broj_stanovnika) {
    while (root != NULL && strcmp(root->naziv, naziv_drzave) != 0) {
        if (strcmp(naziv_drzave, root->naziv) < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    if (root == NULL) {
        printf("Država %s nije pronađena.\n", naziv_drzave);
        return;
    }

    printf("Gradovi u državi %s sa više od %d stanovnika:\n", naziv_drzave, broj_stanovnika);
    grad temp = root->gradovi;
    while (temp != NULL) {
        if (temp->broj_stanovnika > broj_stanovnika) {
            printf("%s sa %d stanovnika\n", temp->naziv, temp->broj_stanovnika);
        }
        temp = temp->next;
    }
}


int main() {
    drzava root = NULL;
    ucitaj_drzava("drzave.txt", &root);

    printf("Države i gradovi:\n");
    inorder_drzava(root);

    char drzava_ime[50];
    int broj_stanovnika;

    printf("\nUnesite ime države za pretragu: ");
    scanf("%s", drzava_ime);

    printf("Unesite  broj stanovnika: ");
    scanf("%d", &broj_stanovnika);

    pretraga_gradova_drzave(root, drzava_ime, broj_stanovnika);

    return 0;
}
