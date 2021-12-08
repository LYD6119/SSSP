#ifndef _SSSP_HPP_
#define _SSSP_HPP_
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
#define INF 10000

class Map{
protected:
    int VertexNum;   //顶点数
    int EdgeNum;
    int **Origin;
    int **Dist;
    int **Path;
    int *Visited;
    char *Vertexes;
    ///
public:
    Map(int VertexNum);
    bool Init(int EdgeNum);
    void AddEdge(int Start,int End,int Distance);
    void Floyd();
    int **GetDist();
    int **GetOrigin();

    void Check();
};

class AOE:public Map{
private:
    int Source,Destination;
    int SourceNum;
    int EdgeNum;
    int *Topologic, *Indegree, *Visited;
    int *VE,*VL,*E,*L;
public:
    AOE(int VertexNum,int _start,int _end);
    void Init(int** _origin,int** _dist,int _source);
    bool Topological_Sort();
    void VL_Count();
    void Find_Imp();
};


#endif