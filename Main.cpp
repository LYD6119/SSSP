#include"SSSP.hpp"
#include"Map.cpp"

int main(){
    int vertexNum,edgeNum;
    cin>>vertexNum>>edgeNum;
    Map map(vertexNum);
    map.Init(edgeNum);
    map.PathSearch();
    return 0;
}
