#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#define MAX 1000



// criar lista vazia
ListaRegioes *criarListaVazia ()
{
    ListaRegioes *l = (ListaRegioes*) malloc (sizeof(ListaRegioes));
    if (l == NULL) {
        return NULL; // falha de alocaÃ§Ã£o
    }

    l->quant = 0;
    l->inicio = NULL;
    l->fim = NULL;
    return l;
}

Regioes *criarRegiao (char *c, char *n) // recebe o nome e estado da regiao
{
    Regioes *r = (Regioes*) malloc (sizeof(Regioes)); // aloca espaÃ§o pra regiao 
    if (r == NULL) 
    {
        return NULL; // falha de alocaÃ§Ã£o
    }

    strcpy(r->nomeReg, n);
    strcpy(r->estado, c);
    r->anterior = NULL;
    r->proximo = NULL;
    r->init = NULL;
    r->final = NULL;
    r->quantVin = 0;
    return r; // retorna a regiao 
} 

void inserirInicio (ListaRegioes* l, char *c, char *n){ 
    Regioes *r = criarRegiao(c, n); // cria a regiao com os parametros

    if (r==NULL)
    {
        return;
    }

    if (l->quant == 0){ // se a lista for vazia 
        l->inicio = r;
        l->fim = r;
        
    } else {
    
    r->proximo = l->inicio; // se nao for vazia
    l->inicio->anterior = r;
    l->inicio = r;
    }

    l->quant++;
}

Regioes *buscaPorNomeReg (ListaRegioes *l, char *n)
{
    if (l->quant==0) // se a lista for vazia
    {
        printf ("Lista Vazia!\n");
        return NULL;
    }
    Regioes *aux = l->inicio; // aux para percorrer
    while (aux != NULL)
    {
       if( strcmp (aux->nomeReg,n)==0) // nome igual ao que estamos procurando
        {
            printf ("RegiÃ£o %s encontrada!\n", n); // se achar
            return aux;
        }
        aux = aux->proximo;
    }
    printf ("RegiÃ£o %s nao encontrada!\n", n); // percorreu tudo e nao achou 
    return NULL;
}

void alteraDadosReg (ListaRegioes *l, char *nomeAntigo)
{
    if (l->quant==0) // lista vazia 
    {
        printf ("Lista Vazia!\n");
        return;
    }
    Regioes *aux = buscaPorNomeReg(l,nomeAntigo); // encontrar a regiao alvo
    if (aux!=NULL) // se a busca tiver sucesso 
    {
        char nomeNovo[MAX];
        char estadoNovo[MAX];

        printf("Digite o novo nome: ");
            scanf(" %[^\n]", nomeNovo); // lemos o novo nome

            printf("Digite o novo estado: ");
            scanf(" %[^\n]", estadoNovo); // lemos o novo estado 

            strcpy(aux->nomeReg, nomeNovo); // atualizamos os campos
            strcpy(aux->estado, estadoNovo);

    } else { // se nÃ£o for encontrado
    return;
    }
}

void removerReg(ListaRegioes *l, char* nome)
{
    if (l->quant==0) // lista vazia
    {
        printf ("Lista Vazia!\n");
        return;
    }
    
    Regioes *aux = buscaPorNomeReg(l,nome); // buscar a regiÃ£o
    
    if (aux == NULL) // se a busca nÃ£o encontrar
    {
        return;
    }

    if (l->quant == 1) 
    {
        l->inicio = NULL;
        l->fim = NULL;
    }

    else if (aux == l->inicio) // se o elemento for o inicio da lista
    {

        l->inicio = l->inicio->proximo; // inicio vira o segundo
        l->inicio->anterior = NULL; 

    } 
    else if (aux == l->fim) // se for o fim da lista
    {
        l->fim = l->fim->anterior; // fim vira o penultimo
        l->fim->proximo = NULL; 
    }
    else // se tiver no meio da lista
    {
    aux->anterior->proximo = aux->proximo; 
    aux->proximo->anterior = aux->anterior; // ("pulamos" o aux na lista, arrumando os ponteiros)
    }
    
    Vinicolas *auxVin = aux->init; // liberaÃ§Ã£o das vinicolas da regiao
    while (auxVin != NULL) 
    {
        Vinicolas *prox = auxVin->prox; // guardamos o prox 

        free(auxVin);

        auxVin = prox;
    }

    printf("RegiÃ£o %s removida.\n", nome);

    free (aux); // liberamos a memoria do aux
    l->quant--; 
}

void listarRegioes (ListaRegioes* l){

    if (l->quant==0) // se a lista for vazia
    {
        printf ("Lista Vazia!\n");
        return;
    }
    Regioes *aux = l->inicio; // aux pra percorrer ate o fim
    while (aux!=NULL)
    {
            printf ("Nome: %s\n", aux->nomeReg);
            printf ("Estado: %s\n\n", aux->estado);

        aux = aux->proximo;
    }
    printf ("Lista finalizada!\n\n");
}

int contaQuantReg (ListaRegioes *l)
{
    return l->quant;
}

Vinicolas *criarVin(char *n, char *p, char *m, int ano)
{   
    Vinicolas *novo = (Vinicolas*) malloc (sizeof(Vinicolas)); // alocaÃ§Ã£o de memoria para a vinicola
     
    if (novo == NULL) 
    {
        return NULL; 
    }

    strcpy(novo->nomeVin, n);
    strcpy(novo->produtos, p);
    strcpy(novo->municipio, m);
    novo->anoFund = ano;   
    novo->ant = NULL;
    novo->prox = NULL;

    return novo;
}

void inserirVinInicio(Regioes* r, char *n, char *p, char *m, int ano){

    Vinicolas *novo = criarVin(n, p, m, ano); // criamos a vinicola

    if (novo == NULL)
    {
        return;
    }

    if (r->quantVin == 0){ // lista vazia
        r->init = novo;
        r->final = novo;
        
    } else {
    
    novo->prox = r->init; // inserimos no inicio
    r->init->ant = novo;
    r->init = novo;
    }

    r->quantVin++;

}

Vinicolas *buscaPorNomeVin (Regioes *r, char *n)
{
    if (r->quantVin==0) // lista vazia
    {
        printf ("Nenhuma vinicola na regiao!\n");
        return NULL;
    }

    Vinicolas *aux = r->init; // aux para percorrer

    while (aux != NULL)
    {
       if( strcmp (aux->nomeVin,n)==0) // comparamos o nome com o alvo
        {
            printf ("Vinicola %s encontrada!\n", n);
            return aux;
        }
        aux = aux->prox;
    }
    printf ("Vinicola %s nao encontrada!\n", n); // se saiu do laÃ§o a vinicola n foi encontrada
    return NULL;
}

void alteraDadosVin (Regioes *r, char *nomeAntigo)
{
    if (r->quantVin==0) // lista vazia
    {
        printf ("Nenhuma vinicola na regiao!\n");
        return;
    }
    Vinicolas *aux = buscaPorNomeVin(r,nomeAntigo); // buscamos a vinicola pelo nome

    if (aux!=NULL)
    {
        char nomeNovo[MAX];
        char produtosNovos[MAX];
        char muniNovo[MAX];
        int anoNovo;


            printf("Digite o novo nome: ");
            scanf(" %[^\n]", nomeNovo);

            printf("Digite os novos produtos: ");
            scanf(" %[^\n]", produtosNovos);
        
            printf("Digite o novo municipio: ");
            scanf(" %[^\n]", muniNovo);

            printf("Digite o novo ano: ");
            scanf(" %d", &anoNovo);

            strcpy(aux->nomeVin, nomeNovo);
            strcpy(aux->produtos, produtosNovos);
            strcpy(aux->municipio, muniNovo);
            aux->anoFund = anoNovo;

    } else {
    return;
    }
}

void removerVin(Regioes *r, char* nome)
{
    if (r->quantVin==0)
    {
        printf ("Nenhuma vinicola na regiÃ£o!\n"); // lista vazia
        return;
    }
    
    Vinicolas *aux = buscaPorNomeVin(r,nome); 
    
    if (aux == NULL) // nao achou a vinicola na regiao
    {
        return;
    }

    if (r->quantVin == 1) // uma vinicola
    {
        r->init = NULL;
        r->final = NULL;
    }

    else if (aux == r->init) // vinicola no inicio
    {

        r->init = r->init->prox;
        r->init->ant = NULL;

    } 
    else if (aux == r->final) // vinicola no final 
    {
        r->final = r->final->ant;
        r->final->prox = NULL;
    }
    else  // vinicola no meio
    {
    aux->ant->prox = aux->prox;
    aux->prox->ant = aux->ant;
    }

    printf ("Vinicola %s removida com sucesso.\n", nome);
    free (aux); // liberamos a vinicola
    r->quantVin--;
}

void listarVin (Regioes* r){

    if (r->quantVin==0)
    {
        printf ("Nao ha vinicolas!\n");
        return;
    }
    Vinicolas *aux = r->init;
    while (aux!=NULL)
    {
            printf ("Nome da vinicula: %s\n", aux->nomeVin);
            printf ("Produtos: %s\n", aux->produtos);
            printf ("Municipio: %s\n", aux->municipio);
            printf ("Ano de fundacao: %d\n\n", aux->anoFund);
        aux = aux->prox;
    }
    printf ("Lista finalizada!\n\n");
}

int contaQuantVin (Regioes *l)
{
    return l->quantVin;
}

void buscaGeral (ListaRegioes *r, char *nome){
 
    if (r == NULL) {
        return;
    }

    Regioes *aux = r->inicio; 
    

    while (aux != NULL){ // percorrer toda a lista de regioes 
       Vinicolas *v = buscaPorNomeVin(aux, nome); // buscar dentro de cada regiao
        
        if (v != NULL)
        {
            printf ("Vinicola %s encontrada na regiao %s\n", nome, aux->nomeReg);
            return;
        } 
         aux = aux->proximo;
        
    }
    
        printf ("Vinicola nao encontrada em nenhuma regiao.\n");
        return;
    }

void contaVinPorReg (ListaRegioes *r){

    if (r == NULL) {
        return;
    }

    Regioes *auxReg = r->inicio;
    int contadorVin = 0;

    while (auxReg != NULL){ 

        Vinicolas *auxVin = auxReg->init;

        while (auxVin != NULL) {
            
            contadorVin++;
            auxVin = auxVin->prox;
            
        }
        printf ("Regiao %s : %d Vinicolas\n", auxReg->nomeReg,contadorVin);
        auxReg = auxReg->proximo;
        contadorVin = 0;
    }
    
    return;

}


Regioes *menorQuantVin(ListaRegioes *l)
{
    if (l == NULL || l->quant == 0) {
        return NULL;
    }

    Regioes *aux = l->inicio;
    Regioes *menor = NULL;
    int menorCont = -1;

    while (aux != NULL) {
        
        Vinicolas *auxVin = aux->init;
        int contador = 0;

        while (auxVin != NULL) {
            contador++;
            auxVin = auxVin->prox;
        }

        
        if (menor == NULL || contador < menorCont) {
            menor = aux;
            menorCont = contador;
        }

        aux = aux->proximo;
    }

    printf("Regiao com menos vinicolas: %s (%d vinicola(s))\n", menor->nomeReg, menorCont);
    return menor;
}

void filtrarVinPorMunicipio(Regioes *r, char *nome)
{
    if (r == NULL) {
        return;
    }

    Vinicolas *aux = r->init;
    int testeVazio = 0;

    while (aux != NULL) {
        if (strcmp(aux->municipio, nome) == 0) {
            printf("Nome da Vinicola: %s\n", aux->nomeVin);
            testeVazio = 1;
        }
        aux = aux->prox;
    }

    if (testeVazio == 0) {
        printf("Nenhuma vinicola encontrada no municipio %s.\n", nome);
    }
    return;
}

void contarVinPorMunicipio(Regioes *r, char *nome)
{
    if (r == NULL)
    {
        return;
    }
    Vinicolas *aux = r->init;
    int contador=0;

    while (aux != NULL) {
        if (strcmp(aux->municipio, nome) == 0) {
            contador++;
        }
        aux = aux->prox;
    }

    if (contador == 0) {
        printf("Nenhuma vinicola no municipio %s.\n", nome);
    }
    else {
        printf ("Numero de Vinicolas no municipio: %d\n",contador);
    }
    return;
}

void carregarDeArquivo(ListaRegioes *l, char *caminho) // recebe lista de regioes e o arquivo
{
    FILE *arq = fopen(caminho, "r"); // abrir o arquivo para leitura

    if (arq == NULL) {
        printf("Arquivo %s nao encontrado.\n", caminho); 
        return;
    }

    char linha[MAX]; // guardar cada linha do arquivo
    Regioes *regiaoAtual = NULL; // guarda ultima regiao inserida

    while (fgets(linha, MAX, arq) != NULL) { // le o arquivo linha por linha atÃ© o final
        linha[strcspn(linha, "\n")] = '\0'; //remove a quebra de linha 

        if (linha[0] == 'R') { // linha que comeÃ§a com R Ã© regiao
            char nome[MAX], estado[MAX]; 
            sscanf(linha, "R;%[^;];%[^;]", nome, estado); // captura ate encontrar ;
            inserirInicio(l, estado, nome); // insere a regiao
            regiaoAtual = l->inicio; // ultima regiao inserida
        }
        else if (linha[0] == 'V' && regiaoAtual != NULL) { // linha comeÃ§a com v e jÃ¡ existe alguma regiao
            char nome[MAX], produtos[MAX], municipio[MAX];
            int ano;
            sscanf(linha, "V;%[^;];%[^;];%[^;];%d", nome, produtos, municipio, &ano);
            inserirVinInicio(regiaoAtual, nome, produtos, municipio, ano);
        }
    }

    fclose(arq);
}

void liberarLista(ListaRegioes *l)
{
    if (l == NULL) {
        return;
    }
    printf("Liberando lista... \n");
    Regioes *aux = l->inicio;
    while (aux != NULL) {
        Regioes *prox = aux->proximo;  
        removerReg(l, aux->nomeReg);
        aux = prox;
    }
    free(l); 
}

void menuRegioes(ListaRegioes *l)
{


    int opcao;
    char nome[MAX], estado[MAX];


    do  {
        printf ("\n     Regioes     \n");
        printf ("1 - Inserir\n");
        printf ("2 - Buscar\n");
        printf ("3 - Alterar\n");
        printf ("4 - Remover\n");
        printf ("5 - Listar\n");
        printf ("6 - Quantidade\n");
        printf ("0 - Voltar\n");
        printf ("Opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {

            case 1:

                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("Estado: ");
                scanf(" %[^\n]", estado);
                inserirInicio(l, estado, nome);

                break;

            case 2:

                printf("Nome: ");
                scanf(" %[^\n]", nome);
                buscaPorNomeReg(l, nome);

                break;

            case 3:
            
                printf("Nome da regiao a alterar: ");
                scanf(" %[^\n]", nome);
                alteraDadosReg(l, nome);

                break;

            case 4: 

                printf("Nome: ");
                scanf(" %[^\n]", nome);

                removerReg(l, nome);
                
                break;
            

            case 5:

                listarRegioes(l);

                break;


            case 6:

                printf("Quantidade de regioes: %d\n", contaQuantReg(l));

                break;

            case 0:

                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);
}

void menuVinicolas(ListaRegioes *l)
{
    char nomeReg[MAX];
    printf("\nNome da regiao: ");
    scanf(" %[^\n]", nomeReg);

    Regioes *r = buscaPorNomeReg(l, nomeReg);

    if (r == NULL) {
        return;
    }

    int opcao;
    char nome[MAX], produtos[MAX], municipio[MAX];
    int ano;

    do {
        printf("\n       Vinicolas de %s     \n", r->nomeReg);

        printf("1 - Inserir\n");
        printf("2 - Buscar\n");
        printf("3 - Alterar\n");
        printf("4 - Remover\n");
        printf("5 - Listar\n");
        printf("6 - Quantidade\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:

                printf("Nome: ");
                scanf(" %[^\n]", nome);

                printf("Produtos: ");
                scanf(" %[^\n]", produtos);

                printf("Municipio: ");
                scanf(" %[^\n]", municipio);

                printf("Ano de fundacao: ");
                scanf("%d", &ano);

                inserirVinInicio(r, nome, produtos, municipio, ano);

                break;

            case 2:

                printf("Nome: ");
                scanf(" %[^\n]", nome);
                buscaPorNomeVin(r, nome);

                break;

            case 3:

                printf("Nome da vinicola a alterar: ");
                scanf(" %[^\n]", nome);
                alteraDadosVin(r, nome);

                break;


            case 4: 

                printf("Nome: ");
                scanf(" %[^\n]", nome);
                removerVin(r, nome);
                
                break;
            

            case 5:

                listarVin(r);

                break;

            case 6:

                printf("Quantidade de vinicolas: %d\n", contaQuantVin(r));

                break;

            case 0:

                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);
}

void menuRelatorios(ListaRegioes *l)
{
    int opcao;
    char nome[MAX], nomeReg[MAX];

    do {
        printf("\n      Relatorios      \n");
        printf("1 - Buscar vinicola em qualquer regiao\n");
        printf("2 - Quantidade de vinicolas por regiao\n");
        printf("3 - Regiao com menos vinicolas\n");
        printf("4 - Filtrar vinicolas por municipio\n");
        printf("5 - Contar vinicolas por municipio\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome da vinicola: ");
                scanf(" %[^\n]", nome);
                buscaGeral(l, nome);
                break;

            case 2:
                contaVinPorReg(l);
                break;

            case 3:
                menorQuantVin(l);
                break;

            case 4: {
                printf("Regiao: ");
                scanf(" %[^\n]", nomeReg);
                Regioes *r = buscaPorNomeReg(l, nomeReg);
                if (r != NULL) {
                    printf("Municipio: ");
                    scanf(" %[^\n]", nome);
                    filtrarVinPorMunicipio(r, nome);
                }
                break;
            }

            case 5: {
                printf("Regiao: ");
                scanf(" %[^\n]", nomeReg);
                Regioes *r = buscaPorNomeReg(l, nomeReg);
                if (r != NULL) {
                    printf("Municipio: ");
                    scanf(" %[^\n]", nome);
                    contarVinPorMunicipio(r, nome);
                }
                break;
            }

            case 0:
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);
}



