#include <iostream>
#include <list>
#include <vector>
#include <bits/stdc++.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;
int _V,_E,_SCC = 0;
int _time = 0,_end;
bool _first_dfs = true;
struct Vertice{
    int color = WHITE;
    int find_time = 0;
    int end_time = 0;
    int scc;
};
Vertice * _first_vertices;
Vertice * _second_vertices;
int * _first_order;
int * _second_order;
list<int>* graph;
list<int>* graphT;

void readGraph(){
    int u,v;
    scanf("%d %d",&_V,&_E);
    _end = _V;
    graph = new list<int>[_V+1];
    graphT = new list<int>[_V+1];
    _first_vertices = new Vertice[_V+1];
    _first_order = new int[_V+1];
    _second_order = new int[_V+1];
    for (int i = 1; i <= _E; i++){
        if (i <= _V) _first_order[i] = i;
        scanf("%d %d",&u,&v);
        graph[u].push_front(v);
        graphT[v].push_front(u);
    }
}
void Dfs_Visit(list<int>* local_graph, stack<int> stack,Vertice* vertices) {
    while(!stack.empty()){
        int V = stack.top();
        if (vertices[V].color == WHITE){ 
            _time++;
            vertices[V].color = GRAY;
            vertices[V].find_time = _time;
            for(list<int>::iterator it = local_graph[V].begin(); it != local_graph[V].end();it++)
                stack.push(*it);
        }else{
            if (vertices[V].color == GRAY){
                _time++;
                vertices[V].color = BLACK;
                vertices[V].end_time = _time;
                if (_first_dfs){
                    _second_order[_end] = V;
                    _end--;
                }
                else vertices[V].scc = _SCC;
            }
            stack.pop();
        }
    }
    //cout << endl;
}
void Dfs(list<int>* local_graph,Vertice * vertices,int * order){
    stack<int> stack;
    for (int i = 1; i <= _V; i++)
        if (!vertices[order[i]].color){ // WHITE
        //if GRAY it's in the stack already
            if (!_first_dfs) _SCC++;
            stack.push(order[i]);
            Dfs_Visit(local_graph,stack,vertices);
        }
}

int main(){
    readGraph();
    Dfs(graph,_first_vertices,_first_order);
    _time = 0;
    _first_dfs = false;
    free(_first_vertices);
    free(_first_order);
    _second_vertices = new Vertice[_V+1];
    Dfs(graphT,_second_vertices,_second_order);
    for (int i = 1; i <= _V; i++){
        printf("%d -> %d/%d -> scc: %d\n",_second_order[i],_second_vertices[_second_order[i]].find_time,
            _second_vertices[_second_order[i]].end_time,_second_vertices[_second_order[i]].scc);
    }
    return 0;
}

