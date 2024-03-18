#include <stdio.h>
#include <malloc.h>

typedef struct {
    int zi, luna, an;
} dataReceptionare;

typedef struct {
    dataReceptionare data;
    int prioritate;
    char* aplicatie;
    float durata;
} notificare;

typedef struct nodStiva {
    struct nodStiva* next;
    notificare inf;
} nodStiva;

void push(nodStiva** varf, notificare notif) {
    nodStiva* temp = (nodStiva*)malloc(sizeof(nodStiva));
    temp->next = NULL;
    temp->inf.data.zi = notif.data.zi;
    temp->inf.data.luna = notif.data.luna;
    temp->inf.data.an = notif.data.an;
    temp->inf.prioritate = notif.prioritate;
    temp->inf.durata = notif.durata;
    temp->inf.aplicatie = (char*)malloc((strlen(notif.aplicatie) + 1) * sizeof(char));
    strcpy(temp->inf.aplicatie, notif.aplicatie);
   
    if (*varf == NULL)
    {
        *varf = temp;
    }
    else 
    {
        temp->next = *varf;
        *varf = temp;
    }
}

int pop(nodStiva** varf, notificare* val)
{
    if (*varf == NULL)
        return -1;
    else
    {
        (*val).data.zi = (*varf)->inf.data.zi;
        (*val).data.luna = (*varf)->inf.data.luna;
        (*val).data.an = (*varf)->inf.data.an;
        (*val).prioritate = (*varf)->inf.prioritate;
        (*val).aplicatie = (char*)malloc((strlen((*varf)->inf.aplicatie) + 1) *
            sizeof(char));
        strcpy((*val).aplicatie, (*varf)->inf.aplicatie);
        (*val).durata = (*varf)->inf.durata;
        nodStiva* temp = *varf;
        *varf = (*varf)->next;
        free(temp->inf.aplicatie);
        free(temp);
        return 0;
    }
}


void parcurgereStiva(nodStiva** varf, int nrNotif)
{
    nodStiva *temp = varf; 
    int i = nrNotif;
    while (i > 0)
    {
        printf("\nData de %d/%d/%d\nNivel de prioritate %d\nDurata %5.2f\nAplicatia %s\n",
            temp->inf.data.zi, temp->inf.data.luna,
            temp->inf.data.an, temp->inf.prioritate,
            temp->inf.durata, temp->inf.aplicatie);

        temp = temp->next;
        i--;
    }
}

void conversieStivaLaVector(nodStiva* varf, notificare* vect, int* nr)
{
    notificare notif;
    while (pop(&varf, &notif) == 0)
    {
        vect[*nr] = notif;
        (*nr)++;
    }
}

void main() {
    nodStiva* varf = NULL;
    notificare notif;
    FILE* f = fopen("fisier.txt", "r");
    int nrNotif;
    fscanf(f, "%d", &nrNotif);
    char buffer[20];
    notificare vector[10];

    for (int i = 0; i < nrNotif; i++) {
        fscanf(f, "%d", &notif.data.zi);
        fscanf(f, "%d", &notif.data.luna);
        fscanf(f, "%d", &notif.data.an);
        fscanf(f, "%d", &notif.prioritate);
        fscanf(f, "%f", &notif.durata);
        fscanf(f, "%s", buffer);
        notif.aplicatie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(notif.aplicatie, buffer);
        push(&varf, notif);
    }
    fclose(f);

    notificare notif2;
    //parcurgereStiva(varf, nrNotif);
    
    int nrElementeVector = 0;
    conversieStivaLaVector(varf, vector, &nrElementeVector);
    
    for (int i = 0; i < nrNotif; i++) {
        printf("\nData de %d/%d/%d\nNivel de prioritate %d\nDurata %5.2f\nAplicatia %s\n",
            vector[i].data.zi, vector[i].data.luna,
            vector[i].data.an, vector[i].prioritate,
            vector[i].durata, vector[i].aplicatie);
    }

    // CU MENTIUNEA CA LA VECTOR NU FUNCTIONEAZA COMPLET, TRY AGAIN 

    // Dezalocare NU MERGE IN ACELASI TIMP CU TRECEREA LA VECTOR 
  /*  while (varf != NULL) {
        nodStiva* temp = varf;
        varf = varf->next;
        free(temp->inf.aplicatie);
        free(temp);
    }*/

}
