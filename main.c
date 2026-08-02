#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"


int main()
{
    ListaRegioes *lista = criarListaVazia();
    carregarDeArquivo(lista, "dados.txt");

    int opcao;
    do {
        printf("\n        MENU PRINCIPAL       \n");
        printf("1 - Regioes\n");
        printf("2 - Vinicolas\n");
        printf("3 - Relatorios e buscas gerais\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: menuRegioes(lista); break;
            case 2: menuVinicolas(lista); break;
            case 3: menuRelatorios(lista); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}

