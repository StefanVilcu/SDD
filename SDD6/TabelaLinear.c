#include<stdio.h>
#include<malloc.h>

typedef struct{
	int anFabricatie;
	char* marca;
	float pret;
}masina;

typedef struct {
	masina** vect;
	int nrElem;
}hashT;

int functieHash(hashT tabela, char cheie[20]) {
	return cheie[0] % tabela.nrElem;
}

void inserareHash(hashT tabela, masina* m)
{
	int poz = functieHash(tabela, m->marca);
	if (tabela.vect[poz] == NULL)
	{
		tabela.vect[poz] = m;
	}
	else
	{
		int index = 1;
		while (poz + index < tabela.nrElem)
		{
			if (tabela.vect[poz + index] == NULL)
			{
				poz = poz + index;
				tabela.vect[poz] = m;
				break;
			}
			else
			{
				index++;
			}
		}
	}
}

void traversareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			printf("\nPozitia = %d", i);
			printf("\nAn fabricatie = %d, Marca = %s, Pretul = %5.2f", tabela.vect[i]->anFabricatie, tabela.vect[i]->marca, tabela.vect[i]->pret);
		}
	}
}

void dezalocare(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			free(tabela.vect[i]->marca);
			free(tabela.vect[i]);
		}
	}
	free(tabela.vect);
}

void stergereDupaMarca(hashT tabela, char marca[20])
{
	int poz = functieHash(tabela, marca);
	
		if (strcmp(tabela.vect[poz]->marca, marca) == 0)
		{
			free(tabela.vect[poz]->marca);
			free(tabela.vect[poz]);
			tabela.vect[poz] = NULL;
		}
		else
		{
			while (strcmp(tabela.vect[poz]->marca, marca) != 0)
			{
				poz++;
			}
			free(tabela.vect[poz]->marca);
			free(tabela.vect[poz]);
			tabela.vect[poz] = NULL;
		}
}

void tabelaToVector(float min,float max, hashT tabela, masina vector[20]) // to redo
{
	
	int index= 0;
	int i = 0;
	while (i < tabela.nrElem) {
		if (tabela.vect[i] != NULL && tabela.vect[i]->pret < max && tabela.vect[i]->pret > min)
		{
			vector[index].anFabricatie = tabela.vect[i]->anFabricatie;
			vector[index].pret = tabela.vect[i]->pret;
			strcpy(vector->marca, tabela.vect[i]->marca);
			index++;
		}
		else
		{
			while (tabela.vect[i] == NULL)
				i++;
		}
	}
}

void main()
{
	hashT tabela;
	tabela.nrElem = 31;
	tabela.vect = (masina**)malloc(tabela.nrElem * sizeof(masina*));
	for (int i = 0; i < tabela.nrElem; i++)
	{
		tabela.vect[i] = NULL;
	}

	FILE* f = fopen("fisier.txt", "r");
	char buffer[20];
	masina* m;
	int nrMasini;

	fscanf(f, "%d", &nrMasini);

	for (int i = 0; i < nrMasini; i++)
	{
		m = (masina*)malloc(sizeof(masina));
		fscanf(f, "%d", &m->anFabricatie);
		fscanf(f, "%s", buffer);
		m->marca = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(m->marca, buffer);
		fscanf(f, "%f", &m->pret); //la citirea din fisier nu se specifica formatul 5.2f, doar %f

		inserareHash(tabela, m);
	}
	fclose(f);

	traversareHash(tabela);

	stergereDupaMarca(tabela, "Dacia");

	printf("\n\nTabela dupa stergere\n");

	traversareHash(tabela);

	printf("\n\nVector\n");

	masina vector[10];
	tabelaToVector(10000, 20000, tabela, &vector);

	for (int i = 0; i < 4; i++)
	{
		printf("\nElementul %d din vector este masina %s", i, vector[i].marca);
	}

	dezalocare(tabela);

}
