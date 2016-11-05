typedef struct Data
{
	int gg, mm, aaaa;
}data;
typedef struct Studenti
{
	char matricola[8];
	char* nome;
	char* cognome;
	data dat;
	char sesso;
	int flag;
}studenti;

studenti *acquisizione(char nomefile[]);
