#ifndef _LISTA_H
#define _LISTA_H
#define MAX 1000

typedef struct vinicolas {
    char nomeVin[MAX];
    char produtos[MAX];
    char municipio[MAX];
    int anoFund;
  
    struct vinicolas *ant; // encadeamento das vinicolas
    struct vinicolas *prox;
    
} Vinicolas; 

typedef struct regioes {

    char nomeReg[MAX];
    char estado[MAX];
    struct regioes *anterior; // encadeamento das regioes
    struct regioes *proximo;

    Vinicolas *init; // descritor para a lista secundaria, dentro da regiao
    Vinicolas *final;
    int quantVin; // quantidade de vinicolas na regiao
}Regioes;

typedef struct listaregioes { // descritor de regioes
    Regioes *inicio;
    Regioes *fim;
    int quant; 
}ListaRegioes;

ListaRegioes *criarListaVazia ();
Regioes *criarRegiao (char *c, char *n);
void inserirInicio (ListaRegioes* l, char *c, char *n);
Regioes *buscaPorNomeReg (ListaRegioes *l, char *n);
void alteraDadosReg (ListaRegioes *l, char *nomeAntigo);
void removerReg(ListaRegioes *l, char* nome);
void listarRegioes (ListaRegioes* l);
int contaQuantReg (ListaRegioes *l);
Vinicolas *criarVin(char *n, char *p, char *m, int ano);
void inserirVinInicio(Regioes* r, char *n, char *p, char *m, int ano);
Vinicolas *buscaPorNomeVin (Regioes *r, char *n);
void alteraDadosVin (Regioes *r, char *nomeAntigo);
void removerVin(Regioes *r, char *nome);
void listarVin (Regioes* r);
int contaQuantVin (Regioes *l);
void buscaGeral (ListaRegioes *r, char *nome);
void contaVinPorReg (ListaRegioes *r);
Regioes *menorQuantVin(ListaRegioes *l);
void filtrarVinPorMunicipio(Regioes *r, char *nome);
void contarVinPorMunicipio(Regioes *r, char *nome);
void carregarDeArquivo(ListaRegioes *l, char *caminho);
void menuRegioes(ListaRegioes *l);
void menuVinicolas(ListaRegioes *l);
void menuRelatorios(ListaRegioes *l);


#endif