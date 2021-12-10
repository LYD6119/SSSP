#include"SSSP.hpp"
#include"Map.cpp"
#include"AOE.cpp"

int main(){
    int vertexNum,edgeNum,start,end;
    cout<<">> Vertex Number: ";
    cin>>vertexNum;
    cout<<">> Edge Number: ";
    cin>>edgeNum;
    Map map(vertexNum);
    if(map.Init(edgeNum)){
        char start,end;
        cout<<">> Start and End: ";
        cin>>start>>end;
        if(!map.MinimalPath(start,end)){
            cout<<">> Error!"<<endl;
            return -1;
        }
        /////////////////////////////////////////
        AOE aoe(vertexNum,map.GetSign(),start,end);
        aoe.Init(map.GetOrigin(),map.GetDist());
        aoe.Critical_Path();
    }
    cout<<">> Complete."<<endl;
    return 0;
}

/*
9 11
A B C D E F G H I
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
////////////
9 11
1 2 3 4 5 6 7 8 9
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
4 6 9
4 7 8
5 7 4
6 8 2
7 8 4
*/