#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Grad* grad;
typedef struct Grad {
    char naziv[50];
    int broj_stanovnika;
    grad left;
    grad right;
} Grad;

typedef struct Drzava* drzava;
typedef struct Drzava {
    char naziv[50];
    drzava next;
    grad gradovi;
} Drzava;


drzava create_drzava(char* naziv);
grad create_grad(char* naziv, int broj_stanovnika);
grad insert_grad(grad root, char* naziv, int broj_stanovnika);
drzava insert_drzava(drzava head, char* naziv);
void ucitaj_gradovi(char* filename, grad* root);
void ucitaj_drzava(char* filename, drzava* head);
void inorder_grad(grad root);
void ispis_drzava(drzava head);
void pretrazi_gradovedrzave(drzava head, char* naziv_drzave, int broj_stanovnika);
void pretraga_gradova_stablo(grad root, int broj_stanovnika);



drzava create_drzava(char* naziv) {
    drzava new = (drzava)malloc(sizeof(Drzava));
    if (new == NULL) {
        printf("Greška pri alokaciji memorije za državu.\n");
        return NULL;
    }
    strcpy(new->naziv, naziv);
    new->next = NULL;
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
    new->left = NULL;
    new->right = NULL;
    return new;
}


grad insert_grad(grad root, char* naziv, int broj_stanovnika) {
    if (root == NULL) return create_grad(naziv, broj_stanovnika);

    if (broj_stanovnika < root->broj_stanovnika || 
        (broj_stanovnika == root->broj_stanovnika && strcmp(naziv, root->naziv) < 0)) {
        root->left = insert_grad(root->left, naziv, broj_stanovnika);
    } else {
        root->right = insert_grad(root->right, naziv, broj_stanovnika);
    }

    return root;
}


drzava insert_drzava(drzava head, char* naziv) {
    drzava new = create_drzava(naziv);
    if (head == NULL || strcmp(naziv, head->naziv) < 0) {
        new->next = head;
        return new;
    }

    drzava temp = head;
    while (temp->next != NULL && strcmp(naziv, temp->next->naziv) > 0) {
        temp = temp->next;
    }

    new->next = temp->next;
    temp->next = new;

    return head;
}


void ucitaj_gradovi(char* filename, grad* root) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Greška pri otvaranju datoteke gradova: %s\n", filename);
        return;
    }

    char naziv[50];
    int broj_stanovnika;

    while (fscanf(fp, "%s %d\n", naziv, &broj_stanovnika) == 2) {
        *root = insert_grad(*root, naziv, broj_stanovnika);
    }

    fclose(fp);
}


void ucitaj_drzava(char* filename, drzava* head) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Greška pri otvaranju datoteke država: %s\n", filename);
        return;
    }

    char naziv[50];
    char datoteka_grad[50];

    while (fscanf(fp, "%s %s\n", naziv, datoteka_grad) == 2) {
        *head = insert_drzava(*head, naziv);

        drzava temp = *head;
        while (temp != NULL && strcmp(temp->naziv, naziv) != 0) {
            temp = temp->next;
        }

        if (temp != NULL) {
            ucitaj_gradovi(datoteka_grad, &(temp->gradovi));
        }
    }

    fclose(fp);
}


void inorder_grad(grad root) {
    if (root) {
        inorder_grad(root->left);
        printf("%s (%d stanovnika)\n", root->naziv, root->broj_stanovnika);
        inorder_grad(root->right);
    }
}


void ispis_drzava(drzava head) {
    while (head) {
        printf("Država: %s\n", head->naziv);
        printf("Gradovi:\n");
        inorder_grad(head->gradovi);
        head = head->next;
    }
}


void pretrazi_gradovedrzave(drzava head, char* naziv_drzave, int broj_stanovnika) {
    while (head != NULL && strcmp(head->naziv, naziv_drzave) != 0) {
        head = head->next;
    }

    if (head == NULL) {
        printf("Država %s nije pronađena.\n", naziv_drzave);
        return;
    }

    printf("Gradovi u državi %s sa više od %d stanovnika:\n", naziv_drzave, broj_stanovnika);
    pretraga_gradova_stablo(head->gradovi, broj_stanovnika);
}


void pretraga_gradova_stablo(grad root, int broj_stanovnika) {
    if (root == NULL) return;

    if (root->broj_stanovnika > broj_stanovnika) {
        printf("%s sa %d stanovnika\n", root->naziv, root->broj_stanovnika);
    }

    pretraga_gradova_stablo(root->left, broj_stanovnika);
    pretraga_gradova_stablo(root->right, broj_stanovnika);
}


int main() {
    drzava head = NULL;
    ucitaj_drzava("drzave.txt", &head);

    printf("Države i gradovi:\n");
    ispis_drzava(head);

    char drzava_ime[50];
    int broj_stanovnika;

    printf("\nUnesite ime države za pretragu: ");
    scanf("%s", drzava_ime);

    printf("Unesite minimalan broj stanovnika: ");
    scanf("%d", &broj_stanovnika);

    pretrazi_gradovedrzave(head, drzava_ime, broj_stanovnika);

    return 0;
}
