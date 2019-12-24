//
//  grafos.c
//  Laboratorio 2
//
//  Created by Jose Ignacio Campos Padilla on 07-12-19.
//  Copyright © 2019 Jose Ignacio Campos Padilla. All rights reserved.
//
// Analisis de algoritmo y estructura de datos

//1. Encontrar la ruta más corta entre dos puntos de entrega y mostrarla por pantalla junto a su distancia.
//2. Encontrar una ruta que permita pasar por todos los puntos de entrega junto a la distancia total recorrida. En caso de que no sea posible, debe indicarle al usuario en la salida correspondiente.
//3. Listar todos los puntos de entrega, ordenados de mayor a menor de acuerdo a la cantidad de conexiones que tengan.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int stack[MAX];
int top = -1;

typedef struct grafo
{
    int vertices;
    int** matriz;
} Grafo;

//stack functions

void push(int item) {
   stack[++top] = item;
}

int pop() {
   return stack[top--];
}

int peek() {
   return stack[top];
}

bool isStackEmpty() {
   return top == -1;
}

typedef struct vertice {
   int label;
   bool visited;
    int numAristas;
} Vertice;

//vertex count
int vertexCount = 0;

//array of vertices
Vertice* Vertices[MAX];


void displayVertex(int vertexIndex) {
   printf("%c ",Vertices[vertexIndex]->label);
}

//get the adjacent unvisited vertex
int getAdjUnvisitedVertex(int vertexIndex, int** adjMatrix) {
   int i;

   for(i = 0; i < vertexCount; i++) {
      if(adjMatrix[vertexIndex][i] == 1 && Vertices[i]->visited == false) {
         return i;
      }
   }

   return -1;
}


void addVertice(int label, int numAristas) {
    Vertice* vertex = (Vertice*) malloc(sizeof(Vertice));
    vertex->label = label;
    vertex->visited = false;
    vertex->numAristas = numAristas;
    
    Vertices[vertexCount++] = vertex;
}

/*
void depthFirstSearch(int** matriz) {
   int i;

   //mark first node as visited
   Vertices[0]->visited = true;

   //display the vertex
   displayVertex(0);

   //push vertex index in stack
   push(0);

   while(!isStackEmpty()) {
      //get the unvisited vertex of vertex which is at top of the stack
      int unvisitedVertex = getAdjUnvisitedVertex(peek(), matriz);

      //no adjacent vertex found
      if(unvisitedVertex == -1) {
         pop();
      } else {
         Vertices[unvisitedVertex]->visited = true;
         displayVertex(unvisitedVertex);
         push(unvisitedVertex);
      }
   }

   //stack is empty, search is complete, reset the visited flag
   for(i = 0;i < vertexCount;i++) {
      Vertices[i]->visited = false;
   }
}
*/
 
/*          ADJACENCY MATRIX                            */
int source,E,visited[MAX];

int DFS(int i, int** G, int V)
{
    int peso = 0;
    
    int j;
    visited[i] = 1;
    printf("%d-",i + 1);
    for(j = 0; j < V ; j++)
    {
        if(G[i][j] > 0 && visited[j] == 0){
            peso += G[i][j];
             peso += DFS(j, G, V);
        }
            
           
    }
    
    return peso;
}

void DFSIterativo(int** matrizAdy, int V){
    int i, j;
    //visited[0] = 1;
    
    //printf(" %d->", 1);
    
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            
            if (matrizAdy[i][j] > 0 && visited[i] == 0)
            {
                
                visited[i] = 1;
                printf("%d-> ", i + 1);
                //i = j;
                //continue;
            }
            
        }
    }
    
    
}

void dijkstra(int** G, int n, int startnode)
{

    //int MAX = 100;
    int INFINITY = 100;
    
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, i, j;
    int nextnode = -1;

    for(i = 0; i < n; i++)
        for(j = 0; j < n ; j++)
            if(G[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = G[i][j];


    for(i = 0; i < n; i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }

    distance[startnode]=0;
    visited[startnode]=1;
    count=1;

    while(count < (n - 1))
    {
        mindistance=INFINITY;

        //nextnode gives the node at minimum distance
        for(i = 0; i < n; i++)
            if(distance[i] < mindistance && !visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }

            
        // verifica si existe una mejor ruta a travez de nextnode
            visited[nextnode] = 1;
            for(i = 0; i < n; i++)
                if(!visited[i])
                    if(mindistance + cost[nextnode][i] < distance[i])
                    {
                        distance[i] = mindistance + cost[nextnode][i];
                        pred[i] = nextnode;
                    }
        count++;
    }

    //imprime la ruta y la distancia de cada nodo
    for(i = n - 1; i < n; i++)
    {
        if(i != startnode)
        {

            printf("\nRuta mas corta: %d",(i + 1));

            j = i;
            do
            {
                j = pred[j];
                printf("-%d", (j + 1));
                
            } while (j != startnode);
            
            printf("\nDistancia %d", distance[i]);
        }
        
    }
         printf("\n");
    
}

// crea matriz y la inicializa
int** crearMatriz(int size) {
    int** matriz = (int**)malloc(sizeof(int*)*size);
    int i,j;
    for(i = 0; i < size; i++){
        matriz[i] = (int*)malloc(sizeof(int)*size);
    }
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            matriz[i][j]=0;
        }
    }
    return matriz;
}

// crea matriz y la inicializa con 1 las adyaciencias
int** crearMatrizAdy(int size, int** matrizLargo){
    int** matriz = (int**)malloc(sizeof(int*)*size);
    int i,j;
    for(i = 0; i < size; i++){
        matriz[i] = (int*)malloc(sizeof(int)*size);
    }
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            matriz[i][j] = 0;
            
            if (matriz[i][j] != matrizLargo[i][j])
            {
                matriz[i][j] = 1;
                
            }
        }
    }
    return matriz;
}

void printMatriz(int **matriz,int size){
    int i,j;
    printf("\n");
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** leerGrafo(FILE* f,int size){

    int** matrizAdyacencia = crearMatriz(size);
    //printMatriz(matrizAdyacencia, size);
    char aux;

    int i,indiceColumna,dist;
    for(i = 0; i < size; i++){ //leer las lineas
        
        //addVertice(i);
        
        while(feof(f) == 0){ // dentro de este bucle lee los vecinos del nodo
            fscanf(f,"%d,%d%c",&indiceColumna,&dist,&aux);
            matrizAdyacencia[i][indiceColumna - 1] = dist;
            
            if(aux == '\n'){ // cuando el caracter %c es un salto de linea salgo del while
                break;
            }
        }
        aux = 0;

    }
    return matrizAdyacencia;
}

int* obtenerAristas(int size, int** grafo)
{
    int* cantArray = (int*) malloc(sizeof(int));
    
    for (int i = 0; i < size; i++) {
        int cant = 0;
        for (int j = 0; j < size; j++) {
            
            if (grafo[i][j] > 0)
                cant += 1;
            
        }
        
        addVertice(i, cant);
        cantArray[i] = cant;
    }
    
    return cantArray;
}


void Ordenado(int n){
    
    int i, j;
    Vertice* tmp;


    for ( i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (Vertices[i]->numAristas < Vertices[j]->numAristas)
            {
                tmp = Vertices[i];
                Vertices[i] = Vertices[j];
                Vertices[j] = tmp;
            }
        }
    }

     printf("\nPuntos Ordenados: ");
    for(i = 0; i < n; i++)
    {
        printf("%d  ", ++Vertices[i]->label);
    }
    
    printf("\n\n");
    
}


int main(){
    FILE* f = fopen("/Users/josigna.cp/Projects/Laboratorio 2/Laboratorio 2/grafo.in","r");
    int size, ptoInicio, ptoFin;
    fscanf(f,"%d",&size);
    
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    
    grafo->vertices = size;
    grafo->matriz = leerGrafo(f, grafo->vertices);
    
    printMatriz(grafo->matriz,size);
    
    int salir;
    
    do {
        printf("Ingrese punto de inicio: \n");
        scanf ("%d",&ptoInicio);
        
        printf("Ingrese punto de destino: \n");
        scanf ("%d",&ptoFin);
        
        //dijkstra(grafo->matriz, 7, 0);
        dijkstra(grafo->matriz, ptoFin, --ptoInicio);
        
        
        printf("Ingrese 1 para buscar otra ruta o 2 para salir: ");
        scanf("%d", &salir);
    } while (salir != 2);
    


    int peso = DFS(0, grafo->matriz, size);
    printf("\nDistancia %d \n", peso);
  
    
    obtenerAristas(size, grafo->matriz);
    Ordenado(size);
    
    printf("\n");
    
    return 0;
}
