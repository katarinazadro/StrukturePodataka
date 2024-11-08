int InsertSorted(Position head, Position nE){
    Position temp = head;

    while(temp->next && temp->next->exp < nE->exp){
        temp = temp->next;
    
    }

if(temp->next == NULL || temp->next->exp !=nE->exp){
    InsertAfter(temp, nE);
}
else{
    int resultCoeffient = temp->next->coeff + nE->coeff;
    if(resultCoeff == 0){
        DeleteAfter(temp);
        free(nE); //jer smo za njega alocirali memoriju ,a nije unesen , obrisano je 
    }
    else{
        temp->next->coeff = resultCoeff,
        free(nE);
    }
}
}

//CITANJE IZ DATOTEKE
//MAX_LINE JE 1024

fgets(buffer, MAX_LINE, file);
while(strlen(buffer) > 0){ //dok ne dodjemo do kraja
int status = sscanf(buffer, " %d %d %n", &c, &e, &numBytes); //%n koliko je sscanf procitao bajtova , ugradjen u sscnaf, numBytes kaze koliko je procitano znakova 
//treba nam razmak da popunimo prazninu, poslije svaka dva broja je prazno

buffer = buffer + numBytes;

}