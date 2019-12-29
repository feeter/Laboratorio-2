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


typedef struct grafo
{
    int vertices;
    int** matriz;
} Grafo;

typedef struct vertice {
   int label;
   bool visited;
    int numAristas;
} Vertice;

//Contador de vertices
int vertexCount = 0;

//arreglo de los vertices
Vertice* Vertices[MAX];

// agrega vertices al arreglo y los cuenta a medida que se van ingresando
void addVertice(int label, int numAristas) {
    Vertice* vertex = (Vertice*) malloc(sizeof(Vertice));
    vertex->label = label;
    vertex->visited = false;
    vertex->numAristas = numAristas;
    
    Vertices[vertexCount++] = vertex;
}


// arreglo de los nodos visitados
int visited[MAX];

// Busqueda en profundidad o en ingles: depthFirstSearch
int DFS(int i, int** G, int V, FILE* fp)
{
    int peso = 0;
    
    int j;
    visited[i] = 1;
    //printf("%d-",i + 1);
    fprintf(fp, "%d-",i + 1);
    
    for(j = 0; j < V ; j++)
    {
        if(G[i][j] > 0 && visited[j] == 0){
            peso += G[i][j];
            peso += DFS(j, G, V, fp);
        }
            
           
    }
    
    return peso;
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

        // nextnode entrega la distancia minima del nodo
        for(i = 0; i < n; i++)
        {
            if(distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        }

            
        // verifica si existe una mejor ruta a travez de nextnode
        visited[nextnode] = 1;
        for(i = 0; i < n; i++)
        {
            if(!visited[i])
            {
                if(mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
            }
            
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
         printf("\n\n");
    
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
        
        while(feof(f) == 0){ // adentro de este bucle lee los vecinos del nodo
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


void Ordenado(int n, FILE* fp){
    
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

     //printf("\nPuntos Ordenados: ");
    fprintf (fp, "Puntos Ordenados: ");
    
    for(i = 0; i < n; i++)
    {
        //printf("%d  ", ++Vertices[i]->label);
        fprintf (fp, "%d-", ++Vertices[i]->label);
    }
    
    //printf("\n\n");
    fprintf (fp, "\n");
    
}


int main(){
    FILE* f = fopen("/Users/josigna.cp/Documents/USACH/Materias/Semestre 2/ANÁLISIS DE ALGORITMOS Y ESTRUCTURA DE DATOS/Laboratorio 2/entregas2.in","r");
    int size, ptoInicio, ptoFin;
    fscanf(f,"%d",&size);
    
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    
    grafo->vertices = size;
    grafo->matriz = leerGrafo(f, grafo->vertices);
    
    //printMatriz(grafo->matriz,size);
    
    int salir = 1;
    
    do {
        printf("Ingrese punto de inicio: \n");
        scanf ("%d",&ptoInicio);
        
        printf("Ingrese punto de destino: \n");
        scanf ("%d",&ptoFin);
        
        if (ptoInicio > ptoFin || ptoInicio == ptoFin)
        {
            printf("Advertencia: Favor ingresar punto de inicio menor al punto de fin y que sean diferentes. \n ");
            
        }
        else
        {
            //dijkstra(grafo->matriz, 7, 0);
            dijkstra(grafo->matriz, ptoFin, --ptoInicio);
            
            
            printf("Ingrese 1 para buscar otra ruta o 2 para salir: ");
            scanf("%d", &salir);
        }
        
        
    } while (salir != 2);
    

    FILE* fp = fopen("resultados.out","w");

    fprintf(fp, "Ruta: ");
    
    int peso = DFS(0, grafo->matriz, size, fp);
    //printf("\nDistancia %d \n", peso);
    fprintf(fp, " Distancia %d \n", peso);
    
    
    obtenerAristas(size, grafo->matriz);
    Ordenado(size, fp);
    
    return 0;
}
