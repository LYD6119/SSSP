#include"SSSP.hpp"

AOE::AOE(int VertexNum,int _start,int _end):Map(VertexNum){
    Topologic = new int[VertexNum];
    Indegree = new int[VertexNum];
    Visited = new int[VertexNum];
    VE = new int[VertexNum];
    VL = new int[VertexNum];
    E = new int[VertexNum];
    L = new int[VertexNum];
    for(int i=0;i<VertexNum;i++){
        Topologic[i] = -1;
        Indegree [i] = Visited[i] = 0;
        VE[i] = VL[i] = E[i] = L[i] = 0;
    }
    Source = _start;
    Destination = _end;
    SourceNum=0;
}

void AOE::Init(int** _origin,int** _dist,int _source){   ////////////Problem!!
    Visited[_source] = 1;
    SourceNum++;
    if(_source == Destination)  return;
    for(int i=0;i<VertexNum;i++){
        if(i!=_source && _origin[_source][i] != INF && _dist[i][Destination] != INF){
            if(Visited[i]==0)
                Init(_origin,_dist,i);
            AddEdge(_source,i,_origin[_source][i]);
            Indegree[i]++;
        } 
    }
}


bool AOE::Topological_Sort(){
    /*
    for(int i=0;i<VertexNum;i++){
        cout<<Indegree[i]<<" ";
    }cout<<endl;
    */
    int Stack[VertexNum + 2]={0};
    int top=0, indic=0;
    for(int i=0;i<VertexNum;i++){
        if(Indegree[i]==0 && Visited[i] == 1){
            Stack[++top] = i; Indegree[i]--;
        }
    }
    while(top!=0){
        int v =Stack[top--];
        Topologic[indic++] = v;
        for(int i = 0;i<VertexNum;i++){
            if(Dist[v][i]!=INF && VE[v] + Dist[v][i] > VE[i]){
                VE[i] = VE[v] + Dist[v][i];
            }
            if(Dist[v][i] != INF) Indegree[i]--;
        }
        for(int i=0;i<VertexNum;i++){
            if(Indegree[i]==0&&Visited[i]==1){   //扫描入度为0的点
                Stack[++top] = i;   Indegree[i] = -1;
            }
        }
    }
    cout<<"Topologic: ";
    for(int i=0;i<VertexNum;i++){
        cout<<Topologic[i]<<" ";
    }cout<<endl;
    if(--indic<SourceNum) return false;
    return true;
}

void AOE::VL_Count(){
    VL[Topologic[SourceNum-1]] = VE[Topologic[SourceNum-1]];
    for(int i=SourceNum-2;i>0;i--){
        int v =Topologic[i];
        for(int i=0;i<VertexNum;i++){
            if(Dist[v][i]!=INF){
                int temp = VL[i] - Dist[v][i];
                if(VL[v]=-1) VL[v] = temp;
                else if(temp<VL[v])  VL[v] = temp;
            }
        }
    }
}

void AOE::Find_Imp(){
    for(int i=0;i<VertexNum;i++){
        for(int j=0;j<VertexNum;j++){
            cout<<((Dist[i][j]==INF)?-1:Dist[i][j])<<" ";
        }cout<<endl;
    }cout<<endl;
    Topological_Sort();
    VL_Count();
    /////////////////////////////////////////
    cout<<"VE: ";
    for(int i=0;i<VertexNum;i++){   //输出VE
        cout<<VE[i]<<" ";
    }cout<<endl;
    cout<<"VL: ";
    for(int i=0;i<VertexNum;i++){   //输出VL
        cout<<VL[i]<<" ";
    }cout<<endl;
    /////////////////////////////////////////
    for(int i=0;i<SourceNum;i++){
        int v=Topologic[i];
        for(int j=0;j<VertexNum;j++){
            if(v!=j && Dist[v][j]!=INF){
                int _e = VE[v];
                int _l = VL[j] - Dist[v][j];
                if(_e == _l)  cout<<v<<"--("<<Dist[v][j]<<")-->"<<j<<endl;
            }
        }
    }
}




