#include <iostream>
#include <list>
#include <vector>
#include <stack>

#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;
int _V,_E,_SCC = 0;
int _time = 0,_end = 0;
int _path = 0;
struct Vertice{
    int color = WHITE;
    int find_time = 0;
    int end_time = 0;
    int parent = 0;
    int path = 0;
    int scc = 0;
};
Vertice * _vertices;
int * _second_order;
int * _scc_max_path;
vector<int>* graph;
vector<int>* graphT;

void readGraph(){
    int u,v;
    if(scanf("%d %d",&_V,&_E))
    _end = _V;
    graph = new vector<int>[_V+1];
    graphT = new vector<int>[_V+1];
    _vertices = new Vertice[_V+1];
    _second_order = new int[_V+1];
    _scc_max_path = new int[_V+1];
    for (int i = 1; i <= _E; i++){
        if (i <= _V){
            _scc_max_path[i] = 0;
        }
        if(scanf("%d %d",&u,&v))
        graph[u].insert(graph[u].begin(),v);
        graphT[v].insert(graphT[v].begin(),u);
    }
}

void visit(stack<int> stack) {
    while(!stack.empty()) {
        int V = stack.top();
        
        if(_vertices[V].color == WHITE) {
            _time++;
            _vertices[V].color = GRAY;
            _vertices[V].find_time = _time;
            for(vector<int>::iterator it = graph[V].begin(); it != graph[V].end();it++){
                if(_vertices[*it].color == WHITE) 
                    stack.push(*it);
            }
        }
        else if(_vertices[V].color == GRAY) {
            _vertices[V].color = BLACK;
            _time++;
            _vertices[V].end_time = _time;
            _second_order[_end] = V;
            _end--;
            stack.pop();
        }
        else if(_vertices[V].color == BLACK) {
            stack.pop();
        }
    }
}

void visit2(stack<int> stack) {
    while(!stack.empty()) {
        int V = stack.top();
        
        if(_vertices[V].color == WHITE) {
            _vertices[V].color = GRAY;
            _time++;
            _vertices[V].find_time = _time;
            _vertices[V].scc = _SCC;
            for(vector<int>::iterator it = graphT[V].begin(); it != graphT[V].end();it++){
                if(_vertices[*it].color == WHITE) 
                    stack.push(*it);
                if (_vertices[*it].color == BLACK && (_vertices[*it].scc != _SCC)){
                    _scc_max_path[_SCC] = max(_scc_max_path[_SCC], _scc_max_path[_vertices[*it].scc] + 1);
                    _path = max(_scc_max_path[_SCC],_path); 
                }
            }
        }
        else{
            if(_vertices[V].color == GRAY) {
            _vertices[V].color = BLACK;
            _time++;
            _vertices[V].end_time = _time;
            }
            stack.pop();
        }
    }
}

void Dfs(vector<int>* local_graph,Vertice * vertices){
    stack<int> stack;
    for (int i = 1; i <= _V; i++)
        if (!vertices[i].color){ // WHITE
        //if GRAY it's in the stack already
            stack.push(i);
            visit(stack);
        }
}

void Dfs2(vector<int>* local_graph,Vertice * vertices){
    stack<int> stack;
    for (int i = 1; i <= _V; i++)
        if (!vertices[_second_order[i]].color){ // WHITE
        //if GRAY it's in the stack already
            stack.push(_second_order[i]);
            _SCC++;
            visit2(stack);
        }
}

int main(){
    readGraph();
    Dfs(graph,_vertices);

    // for(int i = 1; i <= _V; i++){
    //     printf("%d \n",_second_order[i]);
    // }

    // for (int i = 1; i <= _V; i++){
    //     printf("%d -> %d/%d -> scc: %d\n",i,_vertices[i].find_time,
    //         _vertices[i].end_time,_vertices[i].scc);
    // }
    delete[] graph;
    delete[] _vertices;
    _vertices = new Vertice[_V+1];


    _time = 0;
    Dfs2(graphT,_vertices);
    delete[] graphT;


    delete[] _scc_max_path;
    // printf("---------------\n");
    // for (int i = 1; i <= _V; i++){
    //     printf("%d -> %d/%d -> scc: %d\n",_second_order[i],_vertices[_second_order[i]].find_time,
    //         _vertices[_second_order[i]].end_time,_vertices[_second_order[i]].scc);
    // }
    delete[] _second_order;
    delete[] _vertices;
    

    // for (int i = 1; i <= _V; i++){
    //     printf("SCC %d: %d\n",i,_scc_max_path[i]);
    // }
    printf("%d\n",_path);
    return 0;
}
