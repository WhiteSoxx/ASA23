#include <iostream>
#include <list>
#include <vector>
#include <bits/stdc++.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;
int _V,_E;

struct Vertice{
    int parent;
    int color = WHITE;
    int find_time = 0;
    int end_time = 0;
    int scc;
};

Vertice* _vertices;
Vertice* _vertices_second;
list<int>* graph;
list<int>* graphT;
void readGraph(){
    int u,v;
    scanf("%d %d",&_V,&_E);
    graph = new list<int>[_V+1];
    graphT = new list<int>[_V+1];
    _vertices = new Vertice[_V+1];
    _vertices_second = new Vertice[_V+1];
    for (int i = 1; i <= _E; i++){
        scanf("%d %d",&u,&v);
        graph[u].push_front(v);
        graphT[v].push_front(u);
    }
}
void Dfs_Visit(list<int>* local_graph, int time,int end, stack<int> stack,Vertice* vertices) {
    while(!stack.empty()){
        int V = stack.top();
        if (vertices[V].color == WHITE){ 
            time++;
            vertices[V].color = GRAY;
            vertices[V].find_time = time;
            for(list<int>::iterator it = local_graph[V].begin(); it != local_graph[V].end();it++)
                stack.push(*it);
        }else{
            if (vertices[V].color == GRAY){
                time++;
                vertices[V].color = BLACK;
                vertices[V].end_time = time;
                _vertices_second[end] = vertices[V];
                end--;
            }
            stack.pop();
        }
    }
    //cout << endl;
}
void Dfs(list<int>* local_graph,Vertice * vertices){
    int time = 0,end = _V;
    stack<int> stack;
    for (int vert = 1; vert <= _V; vert++)
        if (!vertices[vert].color){ // WHITE
        //if GRAY it's in the stack already
            stack.push(vert);
            Dfs_Visit(local_graph,time,end,stack,vertices);
        }
}

int main(){
    readGraph();
    //Vertice V = Vertice();
    //V.number = 3;
    //dfs(V);
    // for (int i = 1; i <= _V; i++){
    //     cout << i << ": ";
    //     for (list<int>::iterator it = graph[i].begin(); it != graph[i].end();it++){
    //         cout << *it << " ";
    //         cout << "color->";
    //         cout << vertices[*it].color << ";";
    //     }
    //     cout << endl;
    // }
    Dfs(graph,_vertices);
    Dfs(graphT,_vertices_second);
    for (int i = 1; i <= _V; i++){
        cout << i << "-> " << _vertices[i].find_time << "/" << _vertices[i].end_time << endl;
    }
    return 0;
}

