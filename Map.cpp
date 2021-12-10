#include "SSSP.hpp"

Map::Map(int VertexNum) {
    this -> VertexNum = VertexNum;
    Origin = new int* [VertexNum];
    Dist = new int* [VertexNum];
    Path = new int* [VertexNum];
    for(int i = 0; i < VertexNum; i++){
        Origin[i] = new int [VertexNum + 1];
        Dist[i] = new int [VertexNum + 1];
        Path[i] = new int [VertexNum + 1];
        for(int j = 0; j <= VertexNum; j++){
            Origin[i][j] = Dist[i][j] = (i==j) ? 0 : INF ;
            Path[i][j] = -1;
        }
    }
    Sign = new char [VertexNum + 1];
}

bool Map::Init(int EdgeNum){
    //读取顶点标号
    cout<<">> Vertex Sign:"<<endl;
    for(int i=0;i<VertexNum;i++){
        cin>>Sign[i];
    }
    //邻接矩阵构建
    for (int i = 0; i < EdgeNum; i++) {
        int _start, _end, _distance;
        cin>>_start>>_end>>_distance;   //读取有向边的起点、终点、路径长度
        if(_end >= VertexNum  || _distance >= INF ){
            cout<<">> Initialize failed.Check your map!"<<endl;
            return false;
        }
        AddEdge(_start, _end, _distance);
    }
    Floyd();  //Running with Floyd
    cout<<">> Initialize success."<<endl;
    return true;
}

void Map::AddEdge(int _start,int _end,int _distance){   //添加有向边
    Origin[_start][_end] = Dist[_start][_end] = _distance;
}

void Map::Floyd(){   //多源最短路径算法
    for(int k = 0; k < VertexNum; k++){
        for(int i = 0; i < VertexNum; i++){
            for(int j = 0; j < VertexNum; j++){
                if(Dist[i][j] > Dist[i][k] + Dist[k][j]){
                    Dist[i][j] = Dist[i][k] + Dist[k][j];  //更新最短距离
                    Path[i][j] = k;     //记录中间节点
                }
            }
        }
    }
}

bool Map::MinimalPath(char start, char end){   //搜索最短路径
    int _start = -1, _end = -1;
    for(int i = 0; i < VertexNum; i ++){    //找到起点/终点标号
        if(Sign[i] == start)  _start=i;
        if(Sign[i] == end)  _end=i;
    }
    if(_start == -1 || _end == -1){
        cout<<">> No such vertex!"<<endl;
        return false;
    }
    if(Dist[_start][_end] >= INF){
        cout<<">> Couldn't find this path!"<<endl;
        return false;
    }
    cout<< ">> Minimal distance: " <<Dist[_start][_end]<<endl;  //输出最短路径
    cout<< ">> Shortest Path: ";
    FindPath(_start,_end);
    cout<< "--("<< Dist[Path[_start][_end]][_end]<<")-->" << Sign[_end] <<endl;
    return true;
}

void Map::FindPath(int _start,int _end){
    if(Path[_start][_end] == -1){
        cout<< Sign[_start];
    }else{
        int tempEnd = Path[_start][_end];
        int tempStart = Path[_start][tempEnd];
        FindPath(_start, tempEnd);   //递归寻找前节点
        cout<< "--("
            << ((tempStart == -1) ? Dist[_start][tempEnd] : Dist[tempStart][tempEnd])
            <<")-->"<< Sign[Path[_start][_end]];
    }
}


int** Map::GetDist(){
    return Dist;
}

int** Map::GetOrigin(){
    return Origin;
}

char* Map::GetSign(){
    return Sign;
}

void Map::CheckDist(){   //遍历最短路径数组
    cout<<">> Distance:"<<endl;
    for(int i = 0; i < VertexNum; i++){
        for(int j = 0; j < VertexNum; j++){
            cout<<(Dist[i][j] >= INF ? -1 : Dist[i][j])<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void Map::CheckPath(){   //遍历中间节点数组
    cout<<">> Path:"<<endl;
    for(int i = 0; i < VertexNum; i++){
        for(int j = 0; j < VertexNum; j++){
            cout<<Path[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


