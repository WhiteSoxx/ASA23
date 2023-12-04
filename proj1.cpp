#include <iostream>
using namespace std;
int _Xsize, _Ysize;
struct Piece{
    int price = 0;
    int done = false;
};
Piece ** _results;
void readInput(){
    int x,y,price,n;
    scanf("%d %d",&_Xsize,&_Ysize);
    cin >> n;
    _results = new Piece*[_Xsize+1];
    for (int i = 1 ; i <= _Xsize ; i++)
        _results[i] = new Piece[_Ysize+1];
    for (int i = 0; i < n; i++){
        scanf("%d %d %d",&x,&y,&price);
        if (x <= _Xsize && y <= _Ysize) _results[x][y].price = max(_results[x][y].price,price);
        if (x <= _Ysize && y <= _Xsize) _results[y][x].price = max(_results[y][x].price,price);
    }
}
void maxPrice(int x, int y){
    int limit = max(x,y)/2,max_vertical_cut = 0, max_horizontal_cut = 0;
    for (int k = 1; k <= limit; k++){
        if (x > k && k <= x/2)
            max_horizontal_cut = max(_results[k][y].price + _results[x-k][y].price,max_horizontal_cut);
        if (y > k && k <= y/2)
            max_vertical_cut = max(max_vertical_cut,_results[x][k].price + _results[x][y-k].price);
    }
    _results[x][y].price = max(max(_results[x][y].price,max_horizontal_cut),max_vertical_cut);
    if ((y > 1 || x > 1) && y <= _Xsize && x <= _Ysize && x != y){
        _results[y][x].price = _results[x][y].price;
        _results[y][x].done = true;
    }
}
int main(){
    readInput();
    for (int i = 1; i <= _Xsize ; i++)
        for(int j = 1; j <= _Ysize; j++)
            if (!_results[i][j].done) 
                maxPrice(i,j);
    cout << _results[_Xsize][_Ysize].price<< endl;
    return 0;
}