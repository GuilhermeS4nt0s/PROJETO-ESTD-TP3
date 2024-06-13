#include <stdio.h>
#include <stdlib.h>
#include "cidades.h"

int main() {
    const char *nomeArquivo = "teste01.txt";
    
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        printf("Erro ao carregar a estrada.\n");
        return 1;
    }
    
    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    if (menorVizinhanca < 0) {
        printf("Erro ao calcular a menor vizinhanca.\n");
    } else {
        printf("Menor vizinhanca: %.2f\n", menorVizinhanca);
    }

    char *cidade = cidadeMenorVizinhanca(nomeArquivo);
    if (cidade == NULL) {
        printf("Erro ao encontrar a cidade com a menor vizinhanca.\n");
    } else {
        printf("Cidade com a menor vizinhanca: %s\n", cidade);
        free(cidade); // Liberar memória alocada
    }

    free(estrada->C);
    free(estrada);
    return 0;
}
