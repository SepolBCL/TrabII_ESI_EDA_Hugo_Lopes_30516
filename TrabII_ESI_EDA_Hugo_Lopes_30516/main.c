 /**
 * @file main.c
 * @brief  Programa principal.
 * @author Hugo Lopes_30516
 *
 * Este programa controla o fluxo principal do programa, que envolve:
 * - Leitura de um grafo de um arquivo.
 * - Cria��o de um novo grafo.
 * - Inser��o e elimina��o de v�rtices e adjac�ncias.
 * - Salva e carrega do grafo em um ficheiro.
 * - Realiza��o de opera��es de busca e contagem de caminhos.
 * - Destruindo o grafo.
 *
 * @return Retorna 0 se o programa for executado com sucesso.
 */


//#pragma comment (lib, ".\\MyLib\\MyLib.lib")
//#include "C:\Users\Lenovo\Desktop\TrabII_ESI_EDA_Hugo_Lopes_30516\MyLib\MyLib\Graph.h"
//#include "C:\Users\Lenovo\Desktop\TrabII_ESI_EDA_Hugo_Lopes_30516\MyLib\MyLib\Vertices.h"
//#include "C:\Users\Lenovo\Desktop\TrabII_ESI_EDA_Hugo_Lopes_30516\MyLib\MyLib\VerticesAdjacent.h"
//#include "C:\Users\Lenovo\Desktop\TrabII_ESI_EDA_Hugo_Lopes_30516\MyLib\MyLib\IN.h"

#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include <stdbool.h>
#include"VerticesAdjacent.h"
#include"Vertices.h"
#include"Graph.h"
#include"IN.h"


#include <locale.h> // Biblioteca para configura��o do locale

int main()
{
    setlocale(LC_ALL, "Portuguese"); 

    bool res;
    int totV, totA;

    // L� o grafo de um arquivo
    Node2* ini = readFile("matriz.txt", &totV, &totA, &res);
    if (!res) printf("Erro ao ler a matriz\n\n");
    else printf("Dados carregados em mem�ria com sucesso\n\n");

    // Cria um novo grafo
    Graph* novo = CreateGraph(&totV, &res);
    if (!res) printf("Erro ao criar o grafo\n\n");
    else printf("Grafo carregado com sucesso\n\n");

    // Inserir v�rtices e adjac�ncias a partir da estrutura inicial lida
    novo = ins_vert_adj(novo, ini, &totV, &totA, &res);
    if (!res) printf("Erro ao inserir v�rtices e adjac�ncias\n\n");
    else printf("Grafo inicial\n\n");

    // Mostra o grafo ap�s a cria��o inicial
    ShowGraph2(novo);
/*
    // Elimina adjac�ncias espec�ficas entre v�rtices
    novo = DeleteAdjGraph(novo, 1, 1, &res);
    if (!res) printf("Erro ao eliminar adjac�ncia\n");

    novo = DeleteAdjGraph(novo, 1, 2, &res);
    if (!res) printf("Erro ao eliminar adjac�ncia\n");

    printf("Grafo ap�s eliminar adjac�ncias\n\n");
    // Mostra o grafo ap�s eliminar adjac�ncias
    ShowGraph2(novo);

    // Elimina v�rtices do grafo
    novo = DeleteVertGraph(novo, 1, &res);
    if (!res) printf("Erro ao eliminar o v�rtice\n");

    novo = DeleteVertGraph(novo, 2, &res);
    if (!res) printf("Erro ao eliminar o v�rtice\n");

    // Mostrar o grafo ap�s eliminar v�rtices
    printf("Grafo ap�s eliminar v�rtices\n\n");
    ShowGraph2(novo);

    // Insere novos v�rtices no grafo
    Graph* new_vert = CreateVertice(10, &res);
    if (!res) printf("Erro ao criar v�rtice\n");
    novo = InsertVertGraph(novo, new_vert, &res);
    if (!res) printf("Erro ao inserir v�rtice\n");

    new_vert = CreateVertice(15, &res);
    if (!res) printf("Erro ao criar v�rtice\n");
    novo = InsertVertGraph(novo, new_vert, &res);
    if (!res) printf("Erro ao inserir v�rtice\n");

    new_vert = CreateVertice(20, &res);
    if (!res) printf("Erro ao criar v�rtice\n");
    novo = InsertVertGraph(novo, new_vert, &res);
    if (!res) printf("Erro ao inserir v�rtice\n");

    // Mostra o grafo ap�s inserir novos v�rtices
    printf("Grafo ap�s inserir novos v�rtices\n\n");
    ShowGraph2(novo);

    // Insere novas adjac�ncias no grafo
    novo = InsertAdjaGraph(novo, 10, 20, 9999, &res);
    if (!res) printf("Erro ao inserir adjac�ncia\n");

    novo = InsertAdjaGraph(novo, 15, 20, 5555, &res);
    if (!res) printf("Erro ao inserir adjac�ncia \n");

    novo = InsertAdjaGraph(novo, 5, 20, 6666, &res);
    if (!res) printf("Erro ao inserir adjac�ncia (5, 20) com peso 6666\n");

    // Mostra o grafo ap�s inserir novas adjac�ncias
    printf("Grafo ap�s inserir novas adjac�ncias\n\n");
    ShowGraph2(novo);

    // Salva o grafo em um ficheiro bin�rio
    int result = SaveGraph(novo, "graph.bin");
    if (result == 1) {
        printf("Grafo salvo com sucesso!\n\n");
    }
    else {
        printf("Erro ao salvar o grafo: %d\n\n", result);
    }

    // Carrega o grafo de um ficheiro bin�rio
    Graph* nono = LoadGraphB("graph.bin", &res);
    if (res) {
        printf("Grafo carregado com sucesso!\n\n");
        // Mostra o grafo carregado
        ShowGraph2(novo);
    }
    else {
        printf("Erro ao carregar o grafo.\n");
    }

    // Faz reset aos v�rtices visitados
    ResetVerticesVisitados(novo);

    // Verifica se existe um caminho entre dois v�rtices
    bool existe = DepthFirstSearchRec(novo, 0, 3);
    printf("Existe liga��o entre %d e %d: %s\n", 0, 3, (existe ? "Sim" : "N�o"));

    // Faz reset aos v�rtices visitados
    ResetVerticesVisitados(novo);

    // Conta o n�mero de caminhos entre dois v�rtices
    int pathCount = CountPathsVertices(novo, 0, 3, 0);
    printf("N�mero de caminhos entre %d e %d: %d\n", 0, 3, pathCount);
*/
    // Faz reset aos v�rtices visitados
    ResetVerticesVisitados(novo);
   
    // Encontrar o caminho mais pesado entre dois v�rtices
    Best melhorCaminho = BestPath(novo,totA , 0);
    ShowAllPath(melhorCaminho, totA, 0);

    // Apaga o grafo
    novo = DestroyGraph(novo, &res);
    if (!res) printf("Erro ao eliminar o grafo\n");

    return 0;
}
