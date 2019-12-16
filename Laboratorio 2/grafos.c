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

typedef struct grafo
{
    int vertices;
    int** matriz;
} Grafo;

void dijkstra(int** G, int n, int startnode)
{

    int MAX = 100;
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

    //initialize pred[],distance[] and visited[]
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

            //check if a better path exists through nextnode
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

    //print the path and distance of each node
    for(i = 0; i < n; i++)
    {
        if(i != startnode)
        {
            printf("\nDistancia de nodo %d es %d", i + 1, distance[i]);
            printf("\nRuta: %d",(i + 1));

            j = i;
            do
            {
                j = pred[j];
                printf("-%d", (j + 1));
                
            } while (j != startnode);
        }
        
    }
         printf("\n");
    
}

// crea matriz y la inicializa
int** crearMatriz(int size){
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

int** CREAR_MATRIZ(int n) {
    int **matriz = (int **) malloc(sizeof(int *) * n);
    int i, j;

    if(matriz) {
        for(i = 0; i < n; i++) {
            matriz[i] = (int *) calloc(n, sizeof(int));

            if(!matriz[i]) {
                for(j = 0; j < i; j++) {
                    free(matriz[i]);
                }

                free(matriz);
                return NULL;
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



//void MOSTRAR(grafo G) {
//    int i, j;
//
//    printf("Grafo:\n");
//
//    for(i = 0; i < G.vertices; i++) {
//        for(j = 0; j < G.vertices; j++) {
//            printf("%2d ", G.matriz[i][j]);
//        }
//
//        printf("\n");
//    }
//
//    printf("\n");
//}

//grafo ANULAR_GRAFO(grafo G) {
//    int i;
//
//    for(i = 0; i < G.vertices; i++) {
//        free(G.matriz[i]);
//    }
//
//    free(G.matriz);
//    G.matriz = NULL;
//    G.vertices = 0;
//    return G;
//}


//grafo LEER_GRAFO(char *nombreArchivo) {
//    int i, j, peso;
//
//    FILE *archivo = fopen(nombreArchivo, "r");
//    grafo G;
//
//    if(!archivo) {
//        G.matriz = NULL;
//        G.vertices = 0;
//        return G;
//    }
//
//    fscanf(archivo, "%d %d", &G.esDirigido, &G.vertices);
//    G.matriz = CREAR_MATRIZ(G.vertices);
//
//    if(!G.matriz) {
//        fclose(archivo);
//        G.vertices = 0;
//        return G;
//    }
//
//    while(fscanf(archivo,"%d %d %d", &i, &j, &peso) == 3) {
//        G.matriz[i][j] = peso;
//
//        if(!G.esDirigido) {
//            G.matriz[j][i] = peso;
//        }
//    }
//
//    fclose(archivo);
//    return G;
//}


//
int** leerGrafo(FILE* f,int size){

    int** matrizAdyacencia = crearMatriz(size);
    printMatriz(matrizAdyacencia, size);
    char aux;

    int i,indiceColumna,dist;
    for(i = 0; i < size; i++){ //leer las lineas
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



int main(){
    FILE* f = fopen("/Users/josigna.cp/Projects/Laboratorio 2/Laboratorio 2/grafo.in","r");
    int size;
    fscanf(f,"%d",&size);
    
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    
    grafo->vertices = size;
    
    grafo->matriz = leerGrafo(f, grafo->vertices);
    
    printMatriz(grafo->matriz,size);
    
    dijkstra(grafo->matriz, 7, 0);
    
    
    return 0;
}
