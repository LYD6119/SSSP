#include "SSSP.hpp"

Map::Map(int VertexNum) {
    this -> VertexNum = VertexNum;
    Direct_Dist = new Vertex[VertexNum + 1]; 
    Minimal_Dist = new int[VertexNum];
    Pre_Vertex = new int[VertexNum];
    Visited = new int[VertexNum];
}

bool Map::Init(int EdgeNum){
    //邻接表初始化
    char _vertexes[VertexNum + 1];
    for (int i = 0; i < VertexNum; i ++) {
        cin>>_vertexes[i];
        Direct_Dist[i] = new VNode(i,0,NULL);
        Minimal_Dist[i] = INT_MAX;
        Pre_Vertex[i] = -1;
        Visited[i] = 0;
    }
    Vertexes=_vertexes;
    
    //邻接表构建
    for (int i = 0; i < EdgeNum; i++) {
        int start,end, distance;
        cin>>start>>end>>distance;   //读取有向边的起点、终点、权值
        Vertex temp = Direct_Dist[start] -> next;
        Vertex _vertex = new VNode(end,distance,temp);
        Direct_Dist[start] -> next = _vertex;
    }
    cout<<"Initialize success."<<endl;
    return true;
}

void Map::PathSeavoidrch(){
    char _start, _end;
    cin>>_start>>_end;
    int Start = 0, End = 0;
    for(int i = 0; i < VertexNum; i ++){    //找到起点/终点标号
        if(Vertexes[i] == _start)  Start=i;
        if(Vertexes[i] == _end)  End=i;
    }
    Vertex ptr = Direct_Dist[Start];
    while(ptr != NULL){   //初始化最小路径数组
        Minimal_Dist[ ptr->Sign ] = ptr->Distance;
        if(ptr->Distance != INT_MAX && ptr->Distance != 0)  //初始化Pre数组
            Pre_Vertex[ptr->Sign] = Start;
        ptr = ptr->next;
    }
    Visited[Start] = 1;
    while(true){
        int temp = -1, minPath = INT_MAX;
        for(int i = 0; i < VertexNum; i ++){     //取出当前最短路径组中的最小元
            ptr = Direct_Dist[i];
            while(ptr!=NULL){
                if(Visited[ ptr->Sign ] != 1 && Minimal_Dist[ ptr->Sign ] <= minPath){
                    temp= ptr->Sign;
                    minPath = Minimal_Dist[ ptr->Sign ];
                }
                ptr = ptr->next;
            }
        }
        //最短路径为无穷，停止搜索
        if(minPath == INT_MAX)  break;
        Visited[temp] = 1;   //标记为已探索
        ptr = Direct_Dist[temp];   //更新搜索连通项起点
        while(ptr != NULL){   //搜索连通项，更新最短路径
            if(Visited[ ptr->Sign ] != 1 && ptr->Distance + minPath < Minimal_Dist[ ptr->Sign ]){
                Minimal_Dist[ ptr->Sign ] = ptr->Distance + minPath;
                Pre_Vertex[ ptr->Sign ] = temp;
            }
            ptr = ptr->next;
        }
    }
    //最短路径输出
    if(Minimal_Dist[End] != INT_MAX)
        cout<<"Minimal_Dist is:"<<Minimal_Dist[End]<<endl;
    int pre = Pre_Vertex[End];
    cout<<End;
    while(pre != -1){
        cout<<" <- "<<pre;
        pre=Pre_Vertex[pre];
    }

}