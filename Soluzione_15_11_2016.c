#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30

typedef enum{false, true} bool;

typedef struct {
    int numero_serie;
} dati_articolo;

typedef struct articolo {
    dati_articolo dati;
    struct articolo *next;
} articolo;

typedef struct {
    char cognome[N];
    char nome[N];
    int numero_tessera;
    articolo *lista_articoli;
} dati_cliente;

typedef struct cliente {
    dati_cliente dati;
    struct cliente *next;
} cliente;

typedef struct {
    char nome[N];
    struct cliente *lista_clienti;
} dati_reparto;

typedef struct reparto {
    dati_reparto dati;
    struct reparto *next;
} reparto;

bool crea_lista_articoli(articolo **articoli, dati_articolo dati){
    printf("Inserimentoawdawdawaw\n");
    articolo *p = (articolo *)malloc(sizeof(articolo));

    if (p == NULL)
      return false;

    printf("Inserimento\n");

    p->dati = dati;
    p->next = NULL;

    *articoli = p;

    return true;
}

bool inserimento_lista_articolo(articolo **articoli, dati_articolo dati){

    if(*articoli == NULL)
      return crea_lista_articoli(articoli, dati);

    articolo *p = (articolo *)malloc(sizeof(articolo));
    p->dati = dati;
    p->next = NULL;

    p->next = *articoli;
    *articoli = p;

    return true;
}

bool crea_lista_clienti(cliente **clienti, dati_cliente dati){
    cliente *p = (cliente *)malloc(sizeof(cliente));

    if (p == NULL)
      return false;

    p->dati = dati;
    p->next = NULL;

    *clienti = p;

    return true;
}

bool inserimento_lista_clienti(cliente **clienti, dati_cliente dati){

    if(*clienti == NULL)
      return crea_lista_clienti(clienti, dati);

    cliente *p = NULL;

    for(p=*clienti; p->next != NULL; p=p->next);

    if (p==NULL)
      return false;

    cliente *q = (cliente *)malloc(sizeof(cliente));
    q->dati = dati;
    q->next = NULL;

    p->next = q;
    return true;

}

bool crea_lista_reparti(reparto **reparti, dati_reparto dati){

    reparto *p = (reparto *)malloc(sizeof(reparto));

    if (p == NULL)
      return false;

    p->dati = dati;
    p->next = NULL;

    *reparti = p;

    return true;
}

bool inserimento_lista_reparti(reparto **reparti, dati_reparto dati){

    if (*reparti == NULL)
      return crea_lista_reparti(reparti, dati);

    reparto *current = NULL;
    reparto *successive = *reparti;

    while (successive != NULL && strcmp(successive->dati.nome, dati.nome)<0){
        current = successive;
        successive = successive->next;
    }

    reparto *p = (reparto *)malloc(sizeof(reparto));
    p->dati = dati;
    p->next = NULL;

    if (p == NULL)
        return false;

    if (current == NULL){
        p->next = *reparti;
        *reparti = p;
        return true;
    }

    if (successive == NULL){
        current->next = p;
        return true;
    }

    p->next = successive;
    current->next = p;
    return true;
}

void inserimento_reparto(reparto **reparti){
    dati_reparto dati;
    dati.lista_clienti = NULL;

    printf("Inserimento Reparto...\nNome Reparto: ");
    scanf("%s", dati.nome);

    inserimento_lista_reparti(reparti,dati);
}

void inserimento_cliente(reparto **reparti){

    dati_reparto dati_r;
    dati_cliente dati_c;

    dati_r.lista_clienti = NULL;

    printf("Inserimento cliente...\nNome Reparto: ");
    scanf("%s", dati_r.nome);

    printf("Cognome: ");
    scanf("%s", dati_c.cognome);
    printf("Nome: ");
    scanf("%s", dati_c.nome);
    printf("Numero Tessera Punti: ");
    scanf("%d", &dati_c.numero_tessera);

    int n=0;

    printf("Quanti articoli vuoi inserire? (3 Max): ");
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        dati_articolo dati_a;
        printf("Numero Di Serie: ");
        scanf("%d",&dati_a.numero_serie);

        inserimento_lista_articolo(&(dati_c.lista_articoli), dati_a);
    }

    reparto *p = NULL;

    for(p=*reparti; p!=NULL && strcmp(p->dati.nome,dati_r.nome)!=0; p=p->next);

    if (p==NULL){ // Non presente in lista
        inserimento_lista_clienti(&(dati_r.lista_clienti),dati_c);
        inserimento_lista_reparti(reparti, dati_r);
    } else { // Presente in lista
        inserimento_lista_clienti(&(p->dati.lista_clienti),dati_c);
    }

}

bool stampa_numero_clienti(reparto **reparti){

    if (*reparti == NULL)
      return false;

    for(reparto *p=*reparti; p!=NULL; p=p->next){
        int n=0;
        for(cliente *q=p->dati.lista_clienti; q!=NULL; q=q->next){
            printf("TEST: %s\n", q->dati.cognome);
            n++;
        }
        printf("Nel reparto %s ci sono %d clienti!\n",p->dati.nome,n);
    }

    return true;
}

bool cancella_cliente(reparto **reparti, char nome_rep[]){

    if (*reparti == NULL)
      return false;

    reparto *p = NULL;

    for(p=*reparti; p!=NULL && strcmp(p->dati.nome,nome_rep)!=0; p=p->next);

    if (p==NULL){
        printf("Nessun reparto presente con il nome %s\n", nome_rep);
        return false;
    } else {
        cliente *q = p->dati.lista_clienti;
        p->dati.lista_clienti = q->next;
        q->next = NULL;

        printf("Cognome: %s\nNome: %s\nNumero Tessera Punti: %d\n",q->dati.cognome,q->dati.nome,q->dati.numero_tessera);

        free(q);
    }

    return true;
}

void rimozione_cliente(reparto **reparti){

    char nome_rep[N];

    printf("Rimozione cliente...\nNome Reparto: ");
    scanf("%s",nome_rep);

    cancella_cliente(reparti, nome_rep);

}

int main(){

    reparto *reparti = NULL;
    int scelta = 0;

    do {
      printf("0.Inserimento Reparto\n1.Inserimento Cliente\n2.Clienti Coda\n3.Rimozione Coda Cliente\n4.Esci\n: ");
      scanf("%d", &scelta);
      switch (scelta) {
        case 0:
            inserimento_reparto(&reparti);
            break;
        case 1:
            inserimento_cliente(&reparti);
            break;
        case 2:
            stampa_numero_clienti(&reparti);
            break;
        case 3:
            rimozione_cliente(&reparti);
            break;
        case 4:
            printf("\nArrivederci!");
            break;
        default:
            printf("Comando non valido!\n");
            break;
      }
    } while(scelta!=4);

    return 0;
}
