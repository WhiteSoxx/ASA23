#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <cstring>
#include <chrono>

#define WHITE 0
#define GRAY 1
#define BLACK 2
using namespace std;
//using namespace chrono;
int _V,_E,_SCC = 0;
int _time = 0,_end = 0;
int _path = 0;
struct Vertice{
    int color = WHITE;
    int end_time = 0;
    int scc = 0;
};
vector<Vertice> _vertices;
vector<int> _second_order;
vector<int> _scc_max_path;
vector<vector<int>> graph;
vector<vector<int>> graphT;

int main(){
    //auto start_time = high_resolution_clock::now();
    int u,v;
    if(scanf("%d %d",&_V,&_E))
    if (_V < 2){
        printf("%d\n",0);
        return 0;
    }
    _end = _V;
    graph =  vector<vector<int>>(_V+1,vector<int>());
    graphT = vector<vector<int>>(_V+1,vector<int>());
    _vertices = vector<Vertice> (_V+1);
    _second_order = vector<int>(_V+1);
    _scc_max_path = vector<int>(_V+1);
    //memset(_scc_max_path, 0, sizeof(*_scc_max_path));
    //_scc_max_path = {0};
    for (int i = 1; i <= _E; i++){
        if (i <= _V) _scc_max_path[i] = 0;
        if(scanf("%d %d",&u,&v))
        graph[u].push_back(v);
        graphT[v].push_back(u);
    }
    stack<int> stack;
    for (int i = 1; i <= _V; i++) {
        if (!_vertices[i].color){ // WHITE
        //if GRAY it's in the stack already
            stack.push(i);
            while(!stack.empty()) {
                int V = stack.top();
                
                int color = _vertices[V].color;
                switch(color) {
                    case(WHITE): {
                        _time++;
                        _vertices[V].color = GRAY;
                        for(int neighbour : graph[V]){
                            if(_vertices[neighbour].color == WHITE) 
                                stack.push(neighbour);
                        }
                        break;
                    }
                    case(GRAY): {
                            _vertices[V].color = BLACK;
                            _time++;
                            _vertices[V].end_time = ++_time;
                            _second_order[_end] = V;
                            _end--;
                        }
                    default: stack.pop();
                
                }
            }
        }
    }
    
    // delete[] graph;
    // delete[] _vertices;
    _vertices = vector<Vertice> (_V+1);

    for (int i = 1; i <= _V; i++) {
        if (!_vertices[_second_order[i]].color){ // WHITE
        //if GRAY it's in the stack already
            stack.push(_second_order[i]);
            _SCC++;
            while(!stack.empty()) {
                int V = stack.top();
                
                int color = _vertices[V].color;
                switch(color) {
                    case(WHITE): {
                        _vertices[V].color = GRAY;
                        _vertices[V].scc = _SCC;
                        for(int neighbour : graphT[V]){
                            if(_vertices[neighbour].color == WHITE) 
                                stack.push(neighbour);
                            if (_vertices[neighbour].color == BLACK && (_vertices[neighbour].scc != _SCC)){
                                _scc_max_path[_SCC] = max(_scc_max_path[_SCC], _scc_max_path[_vertices[neighbour].scc] + 1);
                                _path = max(_scc_max_path[_SCC],_path); 
                            }
                        }
                        break;
                    }
                    case(GRAY): {
                        _vertices[V].color = BLACK;
                    }
                    default: stack.pop();
                }
            }
        }
    }
    // delete[] graphT;


    // delete[] _scc_max_path;
    // delete[] _second_order;
    // delete[] _vertices;
    
    printf("%d\n",_path);
    // auto end_time = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(end_time - start_time);
    // cout << "it took " << duration.count()<<endl;
    return 0;
}
