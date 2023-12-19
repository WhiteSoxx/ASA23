#include <iostream>
#include <list>
#include <vector>
#include <stack>

#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;
int _V,_E,_SCC = 0;
int _time = 0,_end;
int _path = 0;
bool _first_dfs = true;
struct Vertice{
    int color = WHITE;
    int find_time = 0;
    int end_time = 0;
    int parent = 0;
    int path = 0;
    int scc;
};
Vertice * _first_vertices;
Vertice * _second_vertices;
int * _first_order;
int * _second_order;
int * _scc_max_path;
int * _scc;
list<int>* graph;
list<int>* graphT;

void readGraph(){
    int u,v;
    if(scanf("%d %d",&_V,&_E))
    _end = _V;
    graph = new list<int>[_V+1];
    graphT = new list<int>[_V+1];
    _first_vertices = new Vertice[_V+1];
    _first_order = new int[_V+1];
    _second_order = new int[_V+1];
    _scc_max_path = new int[_V+1];
    for (int i = 1; i <= _E; i++){
        if (i <= _V){
            _first_order[i] = i;
            _scc_max_path[i] = 0;
        }
        if(scanf("%d %d",&u,&v))
        graph[u].push_back(v);
        graphT[v].push_front(u);
    }
}
void Dfs_Visit(list<int>* local_graph, stack<int> stack,Vertice* vertices) {
    int scc = 0;
    bool scc_terminated = false;
    while(!stack.empty()){
        int V = stack.top();
        if (vertices[V].color == WHITE){ 
            _time++;
            vertices[V].color = GRAY;
            vertices[V].find_time = _time;
            for(list<int>::iterator it = local_graph[V].begin(); it != local_graph[V].end();it++){
                if (!_first_dfs){ 
                    vertices[*it].parent = V;
                    if (_scc[0] != *it){
                        if (vertices[V].color != BLACK){ 
                            _scc[++scc] = *it;
                            //printf("%d\n",*it);
                        }
                        //printf("%d\n",*it);
                    }
                    else scc_terminated = true;
                    //printf("PARENT: %d ; VERTICE: %d\n", vertices[*it].parent,*it);
                }
                //o scc qnd é branco n tá definido
                stack.push(*it);
            }
        }else{
            if (vertices[V].color == GRAY){
                _time++;
                vertices[V].color = BLACK;
                vertices[V].end_time = _time;
                if (_first_dfs){
                    _second_order[_end] = V;
                    _end--;
                }
                else{
                    vertices[V].scc = _SCC;
                    
                }
            }
            if (!_first_dfs){
                _scc_max_path[vertices[V].scc] = max(vertices[V].path,_scc_max_path[vertices[V].scc]);
                _path = max(_scc_max_path[vertices[V].scc],_path);
                //printf("V: %d -> path: %d\n",V,vertices[V].path);
            }
            stack.pop();
            // o scc do parent ainda tava nulo
            if (!_first_dfs && (vertices[vertices[V].parent].scc != vertices[V].scc) && vertices[V].scc != 0 && vertices[V].parent
            && !scc_terminated){
                vertices[vertices[V].parent].path = max(max(_scc_max_path[vertices[V].scc] + 1, _scc_max_path[vertices[vertices[V].parent].scc]),vertices[vertices[V].parent].path);
                //_path = max(_scc_max_path[vertices[V].scc],_path);
                //printf("parent: %d, path: %d\n",vertices[V].parent,vertices[vertices[V].parent].path);
                
            }
        }
    }
}

void Dfs(list<int>* local_graph,Vertice * vertices,int * order){
    stack<int> stack;
    for (int i = 1; i <= _V; i++)
        if (!vertices[order[i]].color){ // WHITE
        //if GRAY it's in the stack already
            stack.push(order[i]);
            if (!_first_dfs){
                _SCC++;
                _scc[0] = order[i];
                //printf("%d\n",_scc[0]);
            }
            Dfs_Visit(local_graph,stack,vertices);
        }
}
int main(){
    readGraph();
    Dfs(graph,_first_vertices,_first_order);
    _time = 0;
    _first_dfs = false;
    

    // for (int i = 1; i <= _V; i++){
    //     printf("%d -> %d/%d -> scc: %d\n",_first_order[i],_first_vertices[_first_order[i]].find_time,
    //         _first_vertices[_first_order[i]].end_time,_first_vertices[_first_order[i]].scc);
    // }
    delete [] _first_vertices;
    _first_vertices = new Vertice[_V+1];
    delete[] _first_order;
    _scc = new int[_V+1];

    
    Dfs(graphT,_first_vertices,_second_order);
    // printf("---------------\n");
    // for (int i = 1; i <= _V; i++){
    //     printf("%d -> %d/%d -> scc: %d\n",_second_order[i],_second_vertices[_second_order[i]].find_time,
    //         _second_vertices[_second_order[i]].end_time,_second_vertices[_second_order[i]].scc);
    // }
    // for (int i = 1; i <= _V; i++){
    //     printf("SCC %d: %d\n",i,_scc_max_path[i]);
    // }
    printf("%d\n",_path);
    return 0;
}
