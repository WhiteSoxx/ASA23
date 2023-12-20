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
bool _first_dfs = true;
struct Vertice{
    int color = WHITE;
    int find_time = 0;
    int end_time = 0;
    int parent = 0;
    int path = 0;
    int scc = 0;
};
Vertice * _first_vertices;
int * _second_order;
int * _scc_max_path;
int * _scc;
vector<int>* graph;
vector<int>* graphT;

void readGraph(){
    int u,v;
    if(scanf("%d %d",&_V,&_E))
    _end = _V;
    graph = new vector<int>[_V+1];
    graphT = new vector<int>[_V+1];
    _first_vertices = new Vertice[_V+1];
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
        
        if(_first_vertices[V].color == WHITE) {
            _time++;
            _first_vertices[V].color = GRAY;
            _first_vertices[V].find_time = _time;
            for(vector<int>::iterator it = graph[V].begin(); it != graph[V].end();it++){
                if(_first_vertices[*it].color == WHITE) {
                    _first_vertices[*it].parent = V;
                    stack.push(*it);
                }
            }
        }
        else if(_first_vertices[V].color == GRAY) {
            _first_vertices[V].color = BLACK;
            _time++;
            _first_vertices[V].end_time = _time;
            _second_order[_end] = V;
            _end--;
            stack.pop();
        }
        else if(_first_vertices[V].color == BLACK) {
            stack.pop();
        }
    }
}

void visit2(stack<int> stack) {
    while(!stack.empty()) {
        int V = stack.top();
        
        if(_first_vertices[V].color == WHITE) {
            _first_vertices[V].color = GRAY;
            _first_vertices[V].scc = _SCC;
            for(vector<int>::iterator it = graphT[V].begin(); it != graphT[V].end();it++){
                if(_first_vertices[*it].color == WHITE) {
                    //_first_vertices[*it].parent = V;
                    stack.push(*it);
                }
            }
        }
        else if(_first_vertices[V].color == GRAY) {
            _first_vertices[V].color = BLACK;
            _first_vertices[V].end_time = _time;
            stack.pop();
        }
        else if(_first_vertices[V].color == BLACK) {
            stack.pop();
        }
    }
}



// void Dfs_Visit(vector<int>* local_graph, stack<int> stack,Vertice* vertices) {
//     int scc = 0;
//     bool scc_terminated = false;
//     while(!stack.empty()){
//         int V = stack.top();
//         if (vertices[V].color == WHITE){ 
//             _time++;
//             vertices[V].color = GRAY;
//             //printf("%d %d\n",V,_time);
//             vertices[V].find_time = _time;
//             for(vector<int>::iterator it = local_graph[V].begin(); it != local_graph[V].end();it++){
//                 if (!_first_dfs){ 
//                     vertices[*it].parent = V;
//                     if (_scc[0] != *it){
//                         if (vertices[V].color != BLACK){ 
//                             _scc[++scc] = *it;
//                             //printf("%d\n",*it);
//                         }
//                         //printf("%d\n",*it);
//                     }
//                     else scc_terminated = true;
//                     //printf("PARENT: %d ; VERTICE: %d\n", vertices[*it].parent,*it);
//                 }
//                 //o scc qnd é branco n tá definido
//                 stack.push(*it);
//             }
//         }else{
//             if (vertices[V].color == GRAY){
//                 _time++;
//                 vertices[V].color = BLACK;
//                 vertices[V].end_time = _time;
//                 if (_first_dfs){
//                     _second_order[_end] = V;
//                     _end--;
//                 }
//                 else{
//                     vertices[V].scc = _SCC;
                    
//                 }
//             }
//             if (!_first_dfs){
//                 _scc_max_path[vertices[V].scc] = max(vertices[V].path,_scc_max_path[vertices[V].scc]);
//                 _path = max(_scc_max_path[vertices[V].scc],_path);
//                 //printf("V: %d -> path: %d\n",V,vertices[V].path);
//             }
//             stack.pop();
//             // o scc do parent ainda tava nulo
//             if (!_first_dfs && (vertices[vertices[V].parent].scc != vertices[V].scc) && vertices[V].scc != 0 && vertices[V].parent
//             && !scc_terminated){
//                 vertices[vertices[V].parent].path = max(max(_scc_max_path[vertices[V].scc] + 1, _scc_max_path[vertices[vertices[V].parent].scc]),vertices[vertices[V].parent].path);
//                 //_path = max(_scc_max_path[vertices[V].scc],_path);
//                 //printf("parent: %d, path: %d\n",vertices[V].parent,vertices[vertices[V].parent].path);
                
//             }
//         }
//     }
// }

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
            if (!_first_dfs){
                _SCC++;
                //_scc[0] = _second_order[i];
                //printf("%d\n",_scc[0]);
            }
            visit2(stack);
        }
}

int main(){
    readGraph();
    Dfs(graph,_first_vertices);
    _time = 0;
    _first_dfs = false;

    for(int i = 1; i <= _V; i++){
        printf("%d \n",_second_order[i]);
    }

    // for (int i = 1; i <= _V; i++){
    //     printf("%d -> %d/%d -> scc: %d\n",i,_first_vertices[i].find_time,
    //         _first_vertices[i].end_time,_first_vertices[i].scc);
    // }
    delete[] graph;
    delete[] _first_vertices;
    _first_vertices = new Vertice[_V+1];

    _scc = new int[_V+1];

    
    Dfs2(graphT,_first_vertices);
    delete[] graphT;

    delete[] _scc_max_path;
    delete[] _scc;
    printf("---------------\n");
    for (int i = 1; i <= _V; i++){
        printf("%d -> %d/%d -> scc: %d\n",_second_order[i],_first_vertices[_second_order[i]].find_time,
            _first_vertices[_second_order[i]].end_time,_first_vertices[_second_order[i]].scc);
    }
    delete[] _second_order;
    delete[] _first_vertices;
    

    // for (int i = 1; i <= _V; i++){
    //     printf("SCC %d: %d\n",i,_scc_max_path[i]);
    // }
    printf("%d\n",_path);
    return 0;
}
