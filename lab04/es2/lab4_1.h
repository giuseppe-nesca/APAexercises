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
}studenti;
//extern int mark;
void selettore(studenti *studente, int N);
