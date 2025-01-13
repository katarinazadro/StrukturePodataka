#include <stdio.h>
#include <stdlib.h>
#include <time.h>



typedef struct Node* position;

typedef struct Node {
    int broj;
    position left;  
    position right; 
} Node;

position create_element(int n_broj) {
    position new_element = (position)malloc(sizeof(Node));
    if (new_element == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        return NULL;
    }

    new_element->broj = n_broj;
    new_element->left = NULL;  
    new_element->right = NULL; 

    return new_element;
}

int inorder(position root){
    if(root){
        inorder(root->left);
        printf("%d ", root->broj);
        inorder(root->right);
    }
    return EXIT_SUCCESS;
}

int preorder(position root){
    if(root){
        printf("%d ", root->broj);
        preorder(root->left);
        preorder(root->right);
    }
    return EXIT_SUCCESS;
}

int postorder(position root){
    if(root){
         postorder(root->left);
        postorder(root->right);
        printf("%d ", root->broj);
       
    }
    return EXIT_SUCCESS;
}
void levelOrder(position root) {
    if (root == NULL) return;

    position queue[100];  // Red za čuvanje čvorova
    int front = 0, rear = 0;
    int level = 1;  // Počinjemo od nivoa 1

    // Dodajemo korijen u red
    queue[rear++] = root;

    while (front < rear) {
        int nodesAtCurrentLevel = rear - front;  // Broj čvorova na trenutnom nivou
        printf("Na %d. levelu su: ", level);

        // Ispisujemo sve čvorove na trenutnom nivou
        for (int i = 0; i < nodesAtCurrentLevel; i++) {
            position node = queue[front++];  // Uzimamo prvi element iz reda
            printf("%d ", node->broj);  // Ispisujemo broj čvora

            // Dodajemo djecu trenutnog čvora u red
            if (node->left != NULL) {
                queue[rear++] = node->left;
            }
            if (node->right != NULL) {
                queue[rear++] = node->right;
            }
        }
        printf("\n");
        level++;  // Povećavamo nivo
    }
}
position insert(position root, int value){
    if(root == NULL) return create_element(value);
    if(value < root->broj){
        root->left = insert(root->left, value);
     }

      else if(value > root->broj){
        root->right = insert(root->right,value);
     }
     return root;
}

position search(position root, int value){
    if(root == NULL || root->broj == value){
        return root;
    }
    if(value < root->broj){
        return search(root->left, value);
    }
   else {
        return search(root->right, value);
    }

    return NULL;
}

position deleteNode(position root, int value){
    if(root == NULL){
        return root;
    }
     if(value < root->broj){
        root->left = deleteNode(root->left, value);
     }

     else if(value > root->broj){
        root->right = deleteNode(root->right, value);
     }

     else{
        if(root->left == NULL){
            position temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            position temp = root->left;
            free(root);
            return temp;
        }

        position temp = root->right;
        while(temp->left!=NULL){
            temp = temp->left;
        }

            root->broj= temp->broj;

            root->right = deleteNode(root->right, temp->broj);
        }

        return root;
     }
    
    


int main() {
   
    srand(time(NULL));  
    position root = NULL;  // Početno stablo je prazno
    
   
    for (int i = 0; i < 10; i++) {
        int random_value = rand() % 100 + 1;  
        printf("Dodajem broj: %d\n", random_value);
        root = insert(root, random_value); 
    }
    
    
    
    printf("In-order ispis: ");
    inorder(root);
    printf("\n");
    
   
    printf("Pre-order ispis: ");
    preorder(root);
    printf("\n");
    
    
    printf("Post-order ispis: ");
    postorder(root);
    printf("\n");

    printf("Level-order ispis: ");
    levelOrder(root);
    printf("\n");

    // Pretraga
    int value_to_search = 7;
    position result = search(root, value_to_search);
    if (result) {
        printf("Čvor sa vrijednocu %d je pronađen u stablu.\n", value_to_search);
    } else {
        printf("Čvor sa vrijednocu %d nije pronađen u stablu.\n", value_to_search);
    }

    // Brisanje čvora
    int value_to_delete = 7;
    root = deleteNode(root, value_to_delete);
    printf("Stablo nakon brisanja čvora sa vrijednocu %d:\n", value_to_delete);
    
   
   printf("In-order ispis nakon brisanja: ");
    inorder(root);
    printf("\n");
    
    return EXIT_SUCCESS; 
}