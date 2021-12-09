#ifndef _SSSP_HPP_
#define _SSSP_HPP_
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
#define INF 10000

///Map类--有向图
class Map{  
protected:
    int VertexNum;   //顶点数
    int **Origin;   //原图
    int **Dist;     //最短路径长度数组
    int **Path;     //最短路径寻路数组
    char *Sign;
    ///
    void FindPath(int Start,int End);  //递归寻路
    void AddEdge(int Start,int End,int Distance);  //添加有向边
    void Floyd();   //SSSP-弗洛伊德
public:
    Map(int VertexNum);
    bool Init(int EdgeNum);
    void MinimalPath(char start, char end);  //搜索最短路径
    int **GetDist();    //返回最短路径数组地址
    int **GetOrigin();   //返回原图地址
    char *GetSign();
    ///////////////////////////////////////
    void CheckDist();  
    void CheckPath();
    
};

///AOE类--AOE网
class AOE:public Map{  
private:
    int Source,Destination;  //AOE网起点/终点
    int SourceNum;   //AOE网顶点数
    int *Topologic;  //拓扑排序数组
    int *Indegree;  //入度记录数组
    int *Visited;  //访问标记数组
    int *VE,*VL,*E,*L;  //最早开始时间/最晚开始时间
    bool Topological_Sort();  //拓扑排序+VE计算
    void VL_Count();   //VL计算
    void _init(int** _origin,int** _dist,int _source);
public:
    AOE(int VertexNum,char* Sign,char _start,char _end);   
    void Init(int** _origin,int** _dist);  //初始化
    void Critical_Path();   //关键路径搜索
    /////////////////////////////////////
    void CheckTopo();   //查看拓扑排序
    void CheckVE();
    void CheckVL();
    
};


#endif