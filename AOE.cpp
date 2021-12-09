#include"SSSP.hpp"

AOE::AOE(int VertexNum,char *_sign,char start,char end):Map(VertexNum){
    Topologic = new int[VertexNum];
    Indegree = new int[VertexNum];
    Visited = new int[VertexNum];
    VE = new int[VertexNum];
    VL = new int[VertexNum];
    Sign = _sign;
    //E = new int[VertexNum];
    //L = new int[VertexNum];
    for(int i = 0; i < VertexNum; i++){   //初始化
        Topologic[i] = -1;
        Indegree [i] = Visited[i] = 0;
        VE[i] = VL[i] = 0;
        //E[i] = L[i] = 0;
    }
    for(int i = 0; i < VertexNum; i ++){    //找到起点/终点标号
        if(Sign[i] == start)  Source = i;
        if(Sign[i] == end)  Destination = i;
    }
    SourceNum = 0;
}

void AOE::Init(int** _origin,int** _dist){
    _init(_origin,_dist,Source);
}

void AOE::_init(int** _origin,int** _dist,int _source){ 
    Visited[_source] = 1;
    SourceNum++;   //计算顶点数
    if(_source == Destination)  return;
    for(int i = 0;i < VertexNum ;i++){
        if(i!=_source && _origin[_source][i] < INF && _dist[i][Destination] < INF){
            //若从该点到目的地有路径则加入AOE网络
            if(Visited[i] == 0)  //如果该点未访问则递归该顶点搜索
                _init(_origin, _dist, i); 
            AddEdge(_source, i, _origin[_source][i]);   //添加有向边
            Indegree[i]++;  //更新顶点入度
        } 
    }
}


bool AOE::Topological_Sort(){   //拓扑排序
    if(Dist[Source][Destination] >= INF) return false;
    int Stack[VertexNum + 2];
    int top = 0, indic = 0;
    for(int i = 0; i < VertexNum; i++){
        if(Indegree[i]==0 && Visited[i] == 1){   //入度为0的点入栈
            Stack[++top] = i;
            Indegree[i]--;
        }
    }
    while(top!=0){
        int v = Stack[top--];
        Topologic[indic++] = v;
        for(int i = 0;i<VertexNum;i++){  //更新VE
            if(Dist[v][i] < INF && v != i){
                Indegree[i]--;
                if(VE[v] + Dist[v][i] > VE[i])
                    VE[i] = VE[v] + Dist[v][i];
            }
        }
        for(int i=0;i<VertexNum;i++){
            if(Indegree[i] == 0 && Visited[i] == 1){   //扫描入度为0的点入栈
                Stack[++top] = i; 
                Indegree[i] = -1;
            }
        }
    }
    if(indic != SourceNum ) return false;
    return true;
}


void AOE::CheckTopo(){
    cout<<"Topologic sort: ";
    for(int i = 0; i < VertexNum; i++){
        if(Topologic[i] != -1)  cout<< Sign[Topologic[i]] <<" ";
    }
    cout<<endl;
}

void AOE::VL_Count(){    //计算VL数组
    VL[Topologic[SourceNum-1]] = VE[Topologic[SourceNum-1]];
    for(int i = SourceNum - 2; i > 0; i--){
        int v = Topologic[i];
        for(int i = 0;i < VertexNum; i++){
            if(Dist[v][i] < INF){
                int temp = VL[i] - Dist[v][i];
                if(VL[v] = -1) VL[v] = temp;
                else if(temp < VL[v])  VL[v] = temp;
            }
        }
    }
}

void AOE::Critical_Path(){   //寻找关键路径
    if(! Topological_Sort()){
        cout<<"Topological sort failed. Check your AOE network."<<endl;
        return;
    }
    VL_Count();
    CheckTopo();
    CheckVE();
    CheckVL();
    cout<<"Critical path: "<<endl;
    for(int i=0;i<SourceNum;i++){
        int v=Topologic[i];
        for(int j = 0; j < VertexNum; j++){
            if(v!=j && Dist[v][j] < INF){   //通过VE、VL计算E、L
                int _e = VE[v];
                int _l = VL[j] - Dist[v][j];
                if(_e == _l)  cout<<Sign[v]<<"--("<<Dist[v][j]<<")-->"<<Sign[j]<<endl;
            }
        }
    }
}

void AOE::CheckVE(){
    cout<<"VE: ";
    for(int i = 0; i < VertexNum; i++){   //输出VE
        if(Visited[i] == 1) cout<<"["<<Sign[i]<<"]"<<VE[i]<<" ";
    }
    cout<<endl;
}

void AOE::CheckVL(){
    cout<<"VL: ";
    for(int i = 0; i < VertexNum; i++){   //输出VL
        if(Visited[i] == 1)  cout<<"["<<Sign[i]<<"]"<<VL[i]<<" ";
    }
    cout<<endl;
}


