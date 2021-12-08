#include"SSSP.hpp"
#include"Map.cpp"
#include"AOE.cpp"

int main(){
    int vertexNum,edgeNum,start,end;
    cin>>vertexNum>>edgeNum;
    Map map(vertexNum);
    if(map.Init(edgeNum)){
        map.Floyd();
    }
    cin>>start>>end;
    AOE aoe(vertexNum,start,end);
    aoe.Init(map.GetOrigin(),map.GetDist(),start);
    aoe.Find_Imp();
    return 0;
}

/*
9 11
0 1 2 3 4 5 6 7 8
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4
*/