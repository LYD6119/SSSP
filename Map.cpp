#include "SSSP.hpp"

Map::Map(int VertexNum) {
    this -> VertexNum = VertexNum;
    Origin=new int*[VertexNum];
    Dist=new int*[VertexNum];
    Path=new int*[VertexNum];
    Visited = new int[VertexNum];
    for(int i=0;i<VertexNum;i++){
        Origin[i]=new int[VertexNum];
        Dist[i]=new int[VertexNum];
        Path[i]=new int[VertexNum];
        for(int j=0;j<VertexNum;j++){
            Origin[i][j] = Dist[i][j] = (i==j)?0:INF;
            Path[i][j] = -1;
        }
        Visited[i] = 0;
    }
    Vertexes = new char[VertexNum + 1];
}

bool Map::Init(int EdgeNum){
    this->EdgeNum=EdgeNum;
    //数组初始化
    for (int i = 0; i < VertexNum; i ++) {
        cin>>Vertexes[i];
    }
    //邻接矩阵构建
    for (int i = 0; i < EdgeNum; i++) {
        int _start,_end, _distance;
        cin>>_start>>_end>>_distance;   //读取有向边的起点、终点、权值
        AddEdge(_start,_end,_distance);
    }
    cout<<"Initialize success."<<endl;
    return true;
}

void Map::AddEdge(int _start,int _end,int _distance){
    Origin[_start][_end] = Dist[_start][_end] = _distance;
}

void Map::Floyd(){
    Check();
    for(int k=0;k<VertexNum;k++){
        for(int i=0;i<VertexNum;i++){
            for(int j=0;j<VertexNum;j++){
                if(Dist[i][j] > Dist[i][k] + Dist[k][j]){
                    Dist[i][j] = Dist[i][k] + Dist[k][j];
                    Path[i][j] = k;
                }
            }
        }
    }
    cout<<"After Floyd"<<endl;
    Check();
}

int** Map::GetDist(){
    return Dist;
}

int** Map::GetOrigin(){
    return Origin;
}

void Map::Check(){
    for(int i=0;i<VertexNum;i++){
        for(int j=0;j<VertexNum;j++){
            cout<<(Dist[i][j]==INF?-1:Dist[i][j])<<"\t";
        }cout<<endl;
    }cout<<endl;
}



