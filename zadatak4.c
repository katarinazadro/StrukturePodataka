#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct element* position;
typedef struct element{
    int coeff;
    int exp;
    position next;
}element;

int main(){
 position* polynomials = NULL;
 int brojac_polinoma = 0;

 position sum = create_element(0,0);
 position product = create_element(0,0);

 read_file("polinomi.txt", &polynomials, &brojac_polinoma);

 add_polynomials(polynomials, brojac_polinoma,sum);
 multiply_polynomials(polynomials, brojac_polinoma, product);

 printf("Suma polinoma:\n");
 print_poly(sum);

 printf("Produkt polinoma:\n");
 print_poly(product);

 free(sum);
 free(product);

 for(int i = 0; i < brojac_polinoma; i++){
    free(polynomials[i]);
 }
 free(polynomials);


    return 0;
}

position create_element(int coeff, int exp){
    position new = (position)malloc(sizeof(element));
    if(new == NULL){
        printf("Greska pri alokaciji.\n");
        return NULL;
    }

    new->coeff = coeff;
    new->exp = exp;
    new->next = NULL;

    return new;
}
position* read_file(char* filename, position** polynomials, int* brojac){

FILE* fp = fopen(filename,"r");
if(!fp){
    printf("Greska pri alokaciji.\n");
    return NULL;
}

char buffer[1024];
int c,e,numBytes;


while(fgets(buffer, sizeof(buffer), fp) != NULL){
    position head = create_element(0,0);
    char* line = buffer;

    while(strlen > 0){
        int status = sscanf(line, " %d %d %d", &c, &e, &numBytes);
        if(status == 2){
            position q = create_element(c,e);
            insert_sorted(head, q);
        }
        else{
            printf("Datoteka nije validna.\n");
            fclose(fp);
            return NULL;
        }
        line += numBytes;
    }

    (*brojac++);
    position* temp = realloc(*polynomials, (*brojac)* sizeof(position));
    if(!temp){
        printf("Neuspjesna alokacija memorije.\n");
        fclose(fp);
        return NULL;
    }

    *polynomials = temp;
    (*polynomials)[(*brojac) - 1] = head;
}

fclose(fp);
return *polynomials;
}

void print_poly(position head){
    position temp = head->next;
    while(temp){
        print("%dx%d", temp->coeff, temp->exp);
        if(temp->next){
            printf("+");
        }
        temp = temp->next;
    }
    printf("\n");
}

void delete_after(position temp){
    if(temp == NULL || temp->next == NULL){
        return;
    }

    position to_delete = temp->next;
    temp->next = to_delete->next;
    free(to_delete);
}

int insert_sorted(position head, position new){
    position temp = head;

while(temp->next && (temp->next->exp < new->exp)){
    temp = temp->next;
}

if(temp->next == NULL || temp->next->exp != new->exp){
    insert_after(temp,new);
}
else{
    int resultcoeff = temp->next->coeff + new->coeff;
    if(resultcoeff == 0){
        delete_after(temp);
        free(new);
    }
    else{
        temp->next->coeff = resultcoeff;
        free(new);
    }
}

return 0;
}

void insert_after(position curr, position new){
    while(curr != NULL && new != NULL){
        new->next = curr->next;
        curr->next = new;
    }
}

void free_poly(position head){
    while(head!=NULL){
        position temp = head;
        head = head->next;
        free(temp);
    }
}

void add_polynomials(position* polynomial, int count,position result){
    for(int i = 0; i < count; i++){
        position p = polynomial[i]->next;
        while(p!=NULL){
            insert_sorted(result, create_element(p->coeff, p->exp));
            p = p->next;
        }
    }
}

void multiply_polynomials(position* polynomial, int count,position result){
    if(count == 0)return;

    position temp_result = create_element(0,0);
    insert_sorted(temp_result, create_element(1,0));

    for(int i = 0; i < count; i++){
        position inter = create_element(0,0);
        position p1 = temp_result->next;

        while(p1!=NULL){
            position p2 = polynomial[i]->next;
            while(p2!=NULL){
                int new_coeff = p1->coeff * p2->coeff;
                int new_exp = p1->exp + p2->exp;

                insert_sorted(inter, create_element(new_coeff, new_exp));
                p2 = p2->next;
            }
            p1= p1->next;
        }

        while(temp_result->next!=NULL){

            delete_after(temp_result);
        }
        temp_result->next = inter->next;
        free(inter);
    }

    result->next = temp_result->next;
    free(temp_result);
}