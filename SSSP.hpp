#ifndef _SSSP_HPP_
#define _SSSP_HPP_
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
typedef struct Node{
    int Sign;
    int Distance;
    Node* next;
    Node(){}
    Node(int Sign,int Distance,Node* Next){
        this->Sign=Sign;
        this->Distance=Distance;
        this->next=Next;
    }
}VNode,*Vertex;

class Map{
private:
    Vertex* Direct_Dist;
    int *Minimal_Dist;
    int *Pre_Vertex;
    int *Visited;
    int VertexNum;
    char *Vertexes;
public:void
    Map(int VertexNum);
    bool Init(int EdgeNum);
    //~Map();
    void PathSearch();
};

#endif