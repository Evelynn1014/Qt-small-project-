#include "mygraph.h"

mygraph::mygraph()
{


}

void mygraph::getMapFromFile(string filename){
    ifstream readfile(filename);
    readfile>>n;
    for(int i = 0;i<n;i++){
        readfile>>vexs[i].vexName;
        readfile>>vexs[i].x;
        readfile>>vexs[i].y;
        readfile>>vexs[i].fee;
        readfile>>vexs[i].message;
    }
    int num;
    for(int i = 0;i<n*n;i++){
        matrix[i] = Max;
    }
    for(int i = 0;i<n*n;i++){
        readfile>>num;
        if(num!=0){
            matrix[i] = num;
        }
    }
    readfile.close();
}
int mygraph::getPosition(int row,int column){
    return matrix[row*n+column];
}
int mygraph::getPos(int row,int column){
    return matrix1[row*n+column];
}

void mygraph::DFS(int begin){

    path[0] = begin;
    if(stk.empty())
        toStk(begin);
    while(!stk.empty() && !findPath){
        point p = stk.top();
        stk.pop();
        insertPath(p);
        toStk(p.y);
    }
}
void mygraph::toStk(int a){
    int x = 0;
    int vis[Num] = {0};
    for(int i = 0;i<n;i++){
        if(path[i] == a){
            x = i;
            break;
        }
    }
    if(x == n-1){
        for(int i = 0;i<n;i++){
            cout<<path[i]<<" ";
        }
        cout<<endl;
        findPath = true;
    }
    for(int i = 0;i<x+1;i++){
        vis[path[i]] = 1;
    }
    bool exe = false;
    for(int i = 0;i<n;i++){
        if(vis[i] == 0 && getPosition(a,i)!=Max){
            exe = true;
            stk.push(point(a,i));
        }
    }
    if(!exe){
        for(int i = x-1;i>=0 && !exe;i--){
            for(int j = 0;j<n;j++){
                if(getPosition(path[i],j)!=Max && vis[j] == 0){
                    stk.push(point(path[x],j));
                    exe = true;
                    break;
                }
            }
        }
    }
}
void mygraph::insertPath(point p){
    for(int i = 0;i<n;i++){
        if(path[i] == p.x){
            path[i+1] = p.y;
            break;
        }
    }
}

void mygraph::Kruskal(){
    sort();
    for(int i = 0;i<n;i++){
        parent[i] = i;
    }
    while(!que.empty()){
        point p = que.front();
        que.pop();
        Union(p.x,p.y);
    }
}

int mygraph::findminD(){
    int min = Max;
    int minDex = 0;
    for(int i = 0;i<n;i++){
        if(D[i]!=-1 && D[i]<min){
            min = D[i];
            minDex = i;
        }
    }
    return minDex;
}
void mygraph::sort(){
    bool change = true;
    for(int i = 0;i<n*n;i++){
        matrix1[i] = matrix[i];
    }
    int min = Max;
    point p(0,0);
    while(change){
        change = false;
        min = Max;
        for(int i = 0;i<n;i++){
            for(int j = 0;j<i;j++){
                if(getPos(i,j)<min){
                    change = true;
                    min = getPos(i,j);
                    p.x = i;
                    p.y = j;
                }
            }
        }
        if(change){
            matrix1[p.x * n+p.y] = Max;
            que.push(p);
        }
    }
}
int mygraph::Find(int v){
    while(parent[v] != v) {
            v = parent[v];
        }
        return v;
}
void mygraph::Union(int s, int e){
    int sRoot = Find(s);
        int eRoot = Find(e);
        if(sRoot != eRoot) {
            parent[sRoot] = eRoot;
            pathQue.push(point(s,e));
        }
}
