#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#define INFINTY 100000;

typedef struct edge{
	int startVertex;
	int endVertex;
	int weight;
}Edge;

void createEdges(int w[5][5]);
int bellman(int start);
void relax(int start, int end, int weight);
void printDistance(int start);
void printEdges();

int vertexNum;
Edge* edges;
int edgeLength;
int* distance;

int main(void) {
	int workable = 0;

	int weight[5][5] = { {0, 6, 0, 7, 0},
						 {0, 0, 5, 8, -4},
						 {0, -2, 0, 0, 0},
						 {0, 0, -3, 9, 0},
						 {2, 0, 7, 0, 0}};

	vertexNum = 5;
	createEdges(weight);
	printEdges();

	workable = bellman(0);

	if (workable > 0) {
		printDistance(0);
	}
}

void createEdges(int w[5][5]) {
	int count = 0;

	Edge *tempEdge = (Edge*)malloc(sizeof(Edge)*vertexNum*vertexNum);

	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < vertexNum; j++) {
			if (w[i][j] != 0) {
				tempEdge[count].startVertex = i;
				tempEdge[count].endVertex = j;
				tempEdge[count].weight = w[i][j];
				count++;
			}	
		}
	}

	edges = (Edge*)malloc(sizeof(Edge)*count);

	for (int i = 0; i < count; i++) {
		edges[i] = tempEdge[i];
	}

	distance = (int*)malloc(sizeof(int)*vertexNum);
	edgeLength = count;

}

int bellman(int start) {

	for (int i = 0; i < vertexNum; i++) {
		distance[i] = INFINTY;
	}

	distance[start] = 0;

	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < edgeLength; j++) {
			relax(edges[j].startVertex, edges[j].endVertex, edges[j].weight);
		}
	}

	for (int i = 0; i < edgeLength; i++) {
		if (distance[edges[i].endVertex] > distance[edges[i].startVertex] + edges[i].weight) {
			return 0;
		}
	}

	return 1;
}

void relax(int start, int end, int weight) {
	if (distance[end] > distance[start] + weight) {
		distance[end] = distance[start] + weight;
	}
}

void printDistance(int start) {

	printf("!] Print Distance\n");

	for (int i = 0; i < vertexNum; i++) {
		printf("%d->%d = %d\n", start, i, distance[i]);
	}

	printf("\n");
}

void printEdges() {

	printf("!] Print Edges. \n");

	for (int i = 0; i < edgeLength; i++) {
		printf("%dth Edge = %d -(%d)->%d\n", i, edges[i].startVertex, edges[i].weight, edges[i].endVertex);
	}

	printf("\n");
}