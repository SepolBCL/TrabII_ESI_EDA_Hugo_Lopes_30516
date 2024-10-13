 /**
 * @file main.c
 * @brief  Programa principal.
 * @author Hugo Lopes_30516
 *
 * Este programa controla o fluxo principal do programa, que envolve:
 * - Leitura de um grafo de um arquivo.
 * - Criação de um novo grafo.
 * - Inserção e eliminação de vértices e adjacências.
 * - Salva e carrega do grafo em um ficheiro.
 * - Realização de operações de busca e contagem de caminhos.
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


#include <locale.h> // Biblioteca para configuração do locale

int main()
{
    setlocale(LC_ALL, "Portuguese"); 

    bool res;
    int totV, totA;

    // Lê o grafo de um arquivo
    Node2* ini = readFile("matriz.txt", &totV, &totA, &res);
    if (!res) printf("Erro ao ler a matriz\n\n");
    else printf("Dados carregados em memória com sucesso\n\n");

    // Cria um novo grafo
    Graph* novo = CreateGraph(&totV, &res);
    if (!res) printf("Erro ao criar o grafo\n\n");
    else printf("Grafo carregado com sucesso\n\n");

    // Inserir vértices e adjacências a partir da estrutura inicial lida
    novo = ins_vert_adj(novo, ini, &totV, &totA, &res);
    if (!res) printf("Erro ao inserir vértices e adjacências\n\n");
    else printf("Grafo inicial\n\n");

    // Mostra o grafo após a criação inicial
    ShowGraph2(novo);
/*
    // Elimina adjacências específicas entre vértices
    novo = DeleteAdjGraph(novo, 1, 1, &res);
    if (!res) printf("Erro ao eliminar adjacência\n");

    novo = DeleteAdjGraph(novo, 1, 2, &res);
    if (!res) printf("Erro ao eliminar adjacência\n");

    printf("Grafo após eliminar adjacências\n\n");
    // Mostra o grafo após eliminar adjacências
    ShowGraph2(novo);

    // Elimina vértices do grafo
    novo = DeleteVertGraph(novo, 1, &res);
    if (!res) printf("Erro ao eliminar o vértice\n");

    novo = DeleteVertGraph(novo, 2, &res);
    if (!res) printf("Erro ao eliminar o vértice\n");

    // Mostrar o grafo após eliminar vértices
    printf("Grafo após eliminar vértices\n\n");
    ShowGraph2(novo);

    // Insere novos vértices no grafo
    Graph* new_vert = CreateVertice(10, &res);
    if (!res) printf("Erro ao criar vértice\n");
    novo = InsertVertGraph(novo, new_vert, &res);
    if (!res) printf("Erro ao inserir vértice\n");

    new_vert = CreateVertice(15, &res);
    if (!res) printf("Erro ao criar vértice\n");
    novo = InsertVertGraph(novo, new_vert, &res);
    if (!res) printf("Erro ao inserir vértice\n");

    new_vert = CreateVertice(20, &res);
    if (!res) printf("Erro ao criar vértice\n");
    novo = InsertVertGraph(novo, new_vert, &res);
    if (!res) printf("Erro ao inserir vértice\n");

    // Mostra o grafo após inserir novos vértices
    printf("Grafo após inserir novos vértices\n\n");
    ShowGraph2(novo);

    // Insere novas adjacências no grafo
    novo = InsertAdjaGraph(novo, 10, 20, 9999, &res);
    if (!res) printf("Erro ao inserir adjacência\n");

    novo = InsertAdjaGraph(novo, 15, 20, 5555, &res);
    if (!res) printf("Erro ao inserir adjacência \n");

    novo = InsertAdjaGraph(novo, 5, 20, 6666, &res);
    if (!res) printf("Erro ao inserir adjacência (5, 20) com peso 6666\n");

    // Mostra o grafo após inserir novas adjacências
    printf("Grafo após inserir novas adjacências\n\n");
    ShowGraph2(novo);

    // Salva o grafo em um ficheiro binário
    int result = SaveGraph(novo, "graph.bin");
    if (result == 1) {
        printf("Grafo salvo com sucesso!\n\n");
    }
    else {
        printf("Erro ao salvar o grafo: %d\n\n", result);
    }

    // Carrega o grafo de um ficheiro binário
    Graph* nono = LoadGraphB("graph.bin", &res);
    if (res) {
        printf("Grafo carregado com sucesso!\n\n");
        // Mostra o grafo carregado
        ShowGraph2(novo);
    }
    else {
        printf("Erro ao carregar o grafo.\n");
    }

    // Faz reset aos vértices visitados
    ResetVerticesVisitados(novo);

    // Verifica se existe um caminho entre dois vértices
    bool existe = DepthFirstSearchRec(novo, 0, 3);
    printf("Existe ligação entre %d e %d: %s\n", 0, 3, (existe ? "Sim" : "Não"));

    // Faz reset aos vértices visitados
    ResetVerticesVisitados(novo);

    // Conta o número de caminhos entre dois vértices
    int pathCount = CountPathsVertices(novo, 0, 3, 0);
    printf("Número de caminhos entre %d e %d: %d\n", 0, 3, pathCount);
*/
    // Faz reset aos vértices visitados
    ResetVerticesVisitados(novo);
   
    // Encontrar o caminho mais pesado entre dois vértices
    Best melhorCaminho = BestPath(novo,totA , 0);
    ShowAllPath(melhorCaminho, totA, 0);

    // Apaga o grafo
    novo = DestroyGraph(novo, &res);
    if (!res) printf("Erro ao eliminar o grafo\n");

    return 0;
}
