#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        printf("Erro ao alocar memória para estrada.\n");
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d", &estrada->T) != 1 || estrada->T < 3 || estrada->T > 1000000) {
        printf("Erro ao ler o comprimento da estrada ou valor fora do intervalo permitido.\n");
        free(estrada);
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d", &estrada->N) != 1 || estrada->N < 2 || estrada->N > 10000) {
        printf("Erro ao ler o número de cidades ou valor fora do intervalo permitido.\n");
        free(estrada);
        fclose(file);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        printf("Erro ao alocar memória para cidades.\n");
        free(estrada);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < estrada->N; ++i) {
        if (fscanf(file, "%d %255s", &estrada->C[i].Posicao, estrada->C[i].Nome) != 2) {
            printf("Erro ao ler a posição ou nome da cidade na linha %d.\n", i + 1);
            free(estrada->C);
            free(estrada);
            fclose(file);
            return NULL;
        }

        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {
            printf("Posição da cidade fora do intervalo permitido na linha %d: %d.\n", i + 1, estrada->C[i].Posicao);
            free(estrada->C);
            free(estrada);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        printf("Erro ao carregar a estrada.\n");
        return -1.0;
    }

    double menorVizinhanca = (double)estrada->T;
    
    for (int i = 0; i < estrada->N; ++i) {
        int left = (i == 0) ? estrada->C[i].Posicao : (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2;
        int right = (i == estrada->N - 1) ? (estrada->T - estrada->C[i].Posicao) : (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2;
        double vizinhanca = (double)(left + right);

        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        printf("Erro ao carregar a estrada.\n");
        return NULL;
    }

    double menorVizinhanca = (double)estrada->T;
    int cidadeIndex = -1;

    for (int i = 0; i < estrada->N; ++i) {
        int left = (i == 0) ? estrada->C[i].Posicao : (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2;
        int right = (i == estrada->N - 1) ? (estrada->T - estrada->C[i].Posicao) : (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2;
        double vizinhanca = (double)(left + right);

        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            cidadeIndex = i;
        }
    }

    char *cidadeNome = NULL;
    if (cidadeIndex != -1) {
        cidadeNome = (char *)malloc((strlen(estrada->C[cidadeIndex].Nome) + 1) * sizeof(char));
        if (cidadeNome) {
            strcpy(cidadeNome, estrada->C[cidadeIndex].Nome);
        }
    }

    free(estrada->C);
    free(estrada);
    return cidadeNome;
}