#include <iostream>
#include <list>
#include <vector>
using namespace std;
int _V,_E;
list<int>* _G;

void readGraph(){
    int u,v;
    scanf("%d %d",&_V,&_E);
    _G = new list<int>[_V+1];
    for (int i = 1; i <=_E; i++){
        scanf("%d %d",&u,&v);
        _G[u].push_front(v);
    }
}
int main(){
    readGraph();
    for (int i = 1; i <= _V; i++){
        cout << i << ": ";
        for (list<int>::iterator it = _G[i].begin(); it != _G[i].end();it++){
            cout << *it << " ";
        }
        cout << endl;
    }
    return 0;
}

