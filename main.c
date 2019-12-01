#include <stdio.h>
#include <math.h>
#include <stdbool.h>
// test
#define MAX 1000
#define abeceda 26

int nacitanie(char p_text[]);
void vypis(char p_text[], int pocet_znakov);
int uprava(char p_text[], char u_text[], int pocet_znakov);
void vypis_upravene(char u_text[], int pocet_znakov_upravene);
void vypis_slovo(char p_text[], int pocet_znakov);
int f_eow(char p_text[], int pozicia);
void histogram(char u_text[], int pocet_znakov_upravene);
void c_sifra(char u_text[], int pocet_znakov_upravene);


int main()
{

	char riadiaci_znak, p_text[MAX], u_text[MAX];
	int pocet_znakov = 0, pocet_znakov_upravene = 0;
	p_text[0] = '\0'; 
	u_text[0] = '\0'; 
	bool nacitaj = true; 

	riadiaci_znak = getchar(); 
	printf("\n");

	while (nacitaj == true)
	{

		switch (riadiaci_znak)
		{
		case 'n':
		{
			pocet_znakov = nacitanie(p_text);
			break;
		}
		case 'v':
		{
			vypis(p_text, pocet_znakov);
			break;
		}
		case 'u':
		{
			pocet_znakov_upravene = uprava(p_text, u_text, pocet_znakov);
			break;
		}
		case 's':
		{
			vypis_upravene(u_text, pocet_znakov_upravene);
			break;
		}
		case 'd':
		{
			vypis_slovo(p_text, pocet_znakov);
			break;
		}
		case 'h':
		{
			histogram(u_text, pocet_znakov_upravene);
			break;
		}
		case 'c':
		{
			c_sifra(u_text, pocet_znakov_upravene);
			break;
		}
		case 'k':
		{
			nacitaj = false;
			break;

		}
		default:
			break;
		}
		printf("\n");
		riadiaci_znak = getchar();
	}
	return 0;
}

int nacitanie(char p_text[])
{
	FILE* fr;
	int i = 0, pocet_znakov = 0;

	if ((fr = fopen("sifra.txt", "r")) == NULL)
	{
		printf("Spravu sa nepodarilo nacitat");
		return 0;
	}

	char znak;

	while ((znak = fgetc(fr)) != EOF) 
	{
		p_text[i] = znak;
		i++;
		pocet_znakov++;
		if (pocet_znakov == 1000) 
		{
			break;
		}
	}
	if (fclose(fr) == EOF)
	{
		printf("Chyba pri zatvarani suboru");
	}
	return pocet_znakov;
}

void vypis(char p_text[], int pocet_znakov)
{
	if (p_text[0] == '\0')
	{
		printf("Sprava nie je nacitana");
		return;
	}
	else
	{
		int i = 0;
		for (i = 0; i < pocet_znakov; i++)
		{
			printf("%c", p_text[i]);
		}
	}
	return;
}

int uprava(char p_text[], char u_text[], int pocet_znakov)
{
	int i = 0, j = 0, pocet_znakov_upravene = 0;

	if (p_text[0] == '\0')
	{
		printf("Sprava nie je nacitana");
		return 0;
	}
	else
	{
		for (i = 0; i < pocet_znakov; i++)
		{
			if ((p_text[i] >= 'A') && (p_text[i] <= 'Z'))
			{
				u_text[j] = p_text[i];
				j++;
			}
			else if ((p_text[i] >= 'a') && (p_text[i] <= 'z'))
			{
				u_text[j] = p_text[i] - 32;
				j++;
			}
		}
	}
	pocet_znakov_upravene = j;

	return pocet_znakov_upravene;
}

void vypis_upravene(char u_text[], int pocet_znakov_upravene)
{
	if (u_text[0] == '\0') { printf("Nie je k dispozicii upravena sprava\n"); return; }
	int i;
	for (i = 0; i < pocet_znakov_upravene; i++)
	{
		printf("%c", u_text[i]);
	}
	return;
}

void vypis_slovo(char p_text[], int pocet_znakov)
{
	if (p_text[0] == '\0')
	{
		printf("Sprava nie je nacitana");
		return;
	}
	else
	{
		int index = 0, i = 0, k, j = 0;
		scanf("%d", &k);
		if ((1 <= k) && (k <= 25))
		{
			while (index <= ((pocet_znakov)-k))
			{
				
				for (i = index; i < (index + k); i++)
				{

					if (f_eow(p_text, i) == 0) 
					{
						continue;
					}
					else {
						break;
					}
				}
				
				if (((i - index) == k) && ((f_eow(p_text, i) == 1) || (i > (pocet_znakov - 1))))
				{
					for (j = (i - k); j < i; j++)
					{
						printf("%c", p_text[j]);
					}
					printf("\n");
					index = i + 1;
				}
				else if ((i - index) < k) {
					index = i + 1;
				}
				else {
					
					while ((i < (pocet_znakov - 1)) && (f_eow(p_text, i) == 0))
					{
						i++;
					}
					if (i == (pocet_znakov - 1))
					{
						break;
					}
					else
					{
						index = i + 1;
					}
				}
			}
		}
		else {
			return;
		}
	}
	return;	
}

int f_eow(char p_text[], int pozicia)
{
	
	if ((p_text[pozicia] == ' ') || (p_text[pozicia] == '\n') || (p_text[pozicia] == '\t')
		|| (p_text[pozicia] == '\v') || (p_text[pozicia] == '\f') || (p_text[pozicia] == '\r'))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void histogram(char u_text[], int pocet_znakov_upravene)
{
	if (u_text[0] == '\0')
	{
		printf("Nie je k dispizicii upravena spava\n");
		return;
	}
	else
	{
		int i, usporiadane_znaky[abeceda], riadok;
		char znak;
		double vh, vyska, frekvencia_vyskytu[abeceda], pzu_d = pocet_znakov_upravene, uz_d[abeceda], max = 0.0;
		

		for (i = 0; i < abeceda; i++) 
		{
			usporiadane_znaky[i] = 0;
		}
		
		for (i = 0; i < pocet_znakov_upravene; i++)
		{
			znak = u_text[i];
			usporiadane_znaky[znak - 'A']++;
		}
		for (i = 0; i < abeceda; i++) 
		{
			uz_d[i] = usporiadane_znaky[i];
			frekvencia_vyskytu[i] = ((uz_d[i] / pzu_d) * 100);
			if (frekvencia_vyskytu[i] > max)
			{
				max = frekvencia_vyskytu[i];
			}
		}
		vh = (max / 10); 
		vh = modf(vh, &vyska); 
		if (vh > 0) { vyska++; }
		for (riadok = (int)vyska; riadok >= 1; riadok--)
		{
			for (i = 0; i < abeceda; i++)
			{
				if (((frekvencia_vyskytu[i] / 10) > ((double)riadok - 1))
					|| ((frekvencia_vyskytu[i] / 10) == ((double)riadok)))
				{
					printf("*");
				}
				else
				{
					printf(" ");
				}
			}
			printf("\n");
		}
		for (i = 0; i < abeceda; i++)
		{
			printf("%c", 'A' + i);
		}

	}
	return;
}

void c_sifra(char u_text[], int pocet_znakov_upravene)
{
	if (u_text[0] == '\0') 
	{
		printf("Nie je k dispozicii upravena sprava");
	}
	else {
		int n;
		scanf("%d", &n); 
		if ((1 <= n) && (n <= 25)) {
			int i;
			char znak;

			for (i = 0; i < pocet_znakov_upravene; i++)
			{
				znak = u_text[i];
				znak = znak - n;
				if (znak < 'A') 
				{
					znak = znak + 'Z' - 'A'; 
				}
				printf("%c", znak);
			}
		}
		else {
			return;
		}
	}
	return;
}