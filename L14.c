#include <stdlib.h>
#include <stdio.h>

// CONSIDERAR UM PROCESSADOR DE CICLO UNICO E UMA CACHE BASE (RV32)
// Políticas de Write-Back e Write-Allocate, LRU

// 1 - indicar a decomposicao do endereco em tag, index e offset [1 ponto]
// Tamanho endereço : 32 bits
// Dimensao total da cache : 2kB
// Vias : 1
// Linhas : 256

// 2 - indicar o mapeamento dos seguintes pontos na cache [1 ponto]
// Seja M uma matriz NxM, onde &(M[0][0]) = 0x10000100, N = 8, M = 16
// M[0][12] , M[7][5] (qual linha? qual offset?)

// Considere agora a seguinte Cache:
// Vias : 2
// Linhas : 32
// Dimensão Linha : 8B

// 3 - determinar hit rate da funcao 'Square' (simulacao/teoricamente) [1 ponto]
// 4 - alterar o codigo C de forma a reduzir o miss rate [1 ponto]
// 5 - Qual a configuracao da cache origina um melhor desempenho? [1 pontos]

/*******************************************************************************
 * Definicao de constantes e macros
*******************************************************************************/
// Constantes
#define N 128

/*******************************************************************************
 * Declaracao de variaveis globais
*******************************************************************************/
int vect1[N] = {50, 60, 30, 50, 40, 60, 100, 80, 90, 80, 10, 90, 60, 70, 50, 00, 40, 30, 60, 100, 40, 70, 60, 80, 40, 90, 20, 90, 60, 100, 70, 90, 00, 00, 90, 60, 20, 00, 40, 80, 100, 10, 30, 40, 00, 60, 30, 100, 20, 80, 50, 30, 90, 30, 100, 40, 50, 30, 00, 80, 50, 90, 90, 60, 100, 30, 100, 20, 90, 100, 40, 100, 40, 40, 100, 00, 60, 30, 100, 60, 70, 10, 90, 80, 00, 80, 50, 90, 70, 20, 90, 90, 10, 40, 50, 10, 30, 40, 00, 100, 20, 60, 40, 10, 80, 30, 60, 10, 20, 30, 10, 80, 100, 10, 60, 60, 10, 70, 70, 90, 10, 40, 40, 70, 70, 00, 90, 30};
int vect2[N] = {20, 80, 50, 80, 50, 70, 90, 20, 20, 100, 60, 20, 50, 100, 90, 20, 50, 80, 80, 100, 50, 00, 70, 80, 10, 40, 70, 40, 00, 90, 10, 70, 50, 20, 00, 100, 40, 40, 10, 100, 30, 90, 20, 00, 20, 00, 100, 00, 40, 30, 10, 30, 20, 00, 80, 60, 90, 20, 40, 60, 50, 60, 70, 00, 00, 90, 40, 80, 40, 10, 40, 60, 30, 00, 00, 80, 80, 30, 90, 30, 20, 80, 20, 70, 80, 100, 100, 80, 60, 40, 90, 80, 30, 10, 80, 80, 70, 100, 50, 100, 60, 70, 50, 10, 50, 70, 80, 00, 20, 80, 40, 40, 70, 10, 40, 100, 40, 20, 50, 10, 90, 70, 30, 90, 90, 00, 80, 00};

/*******************************************************************************
 * Declaracao de funcoes
*******************************************************************************/
void Square(int *, int *);

/*******************************************************************************
 * Square
*******************************************************************************/
void Square(register int *A, register int *B)
{
    // a keyword register pede ao compilador para alocar as variaveis em registos
    register int i, j, idx, os = 2;
    
    for (i = 0; i < os; i++) {
        for (j = 0; j < N; j += os) {
            B[j+i] = A[j+i]*A[j+i];
        }
    }
    
}

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    Square(vect1, vect2);
    return EXIT_SUCCESS;
}