#include <iostream>
#include <array>
#include <vector>
#include <chrono>
using namespace std;
//using namespace chrono;
// meter sem memoization (tentar)
// guardar os valores na tabela calcular para todos os da tabela;
// simplesmente iterar pela tabela-> já vou ter os valores para trás
int _Xsize, _Ysize;
struct Piece{
    int price = 0;
    int done = false;
};
Piece **_results;

void readInput(){
    int x,y,price,n;
    cin >> _Xsize; cin.ignore(); cin >> _Ysize;
    cin >> n;
    _results = new Piece*[_Xsize+1];
    for (int i = 1 ; i <= _Xsize ; i++)
        _results[i] = new Piece[_Ysize+1];
    for (int i = 0; i < n; i++){
        cin >> x; cin.ignore(); cin >> y; cin.ignore(); cin >> price;
        //if (price > 0 && ((x <= _Xsize && y <= _Ysize) || (x <= _Ysize && y <=_Xsize))){
        if (x <= _Xsize && y <= _Ysize) _results[x][y].price = max(_results[x][y].price,price);
        if (x <= _Ysize && y <= _Xsize) _results[y][x].price = max(_results[y][x].price,price);
    }
}
void maxPrice(int x, int y){
    int limit = max(x,y)/2,vertical_cut = 0,max_vertical_cut = 0, max_horizontal_cut = 0,horizontal_cut = 0;
    for (int k = 1; k <= limit; k++){
        if (x > k && k <= x/2){
            horizontal_cut = _results[k][y].price + _results[x-k][y].price;
            max_horizontal_cut = (horizontal_cut > max_horizontal_cut) ? horizontal_cut : max_horizontal_cut;
        }
        if (y > k && k <= y/2){
            vertical_cut = _results[x][k].price + _results[x][y-k].price;
            max_vertical_cut = (vertical_cut > max_vertical_cut) ? vertical_cut : max_vertical_cut;
        }
    }
    _results[x][y].price = max(max(_results[x][y].price,max_horizontal_cut),max_vertical_cut);
    if ((y > 1 || x > 1) && y <= _Xsize && x <= _Ysize && x != y){
        _results[y][x].price = _results[x][y].price;
        _results[y][x].done = true;
    }
}
int main(){
    //auto start_time = high_resolution_clock::now();
    readInput();
    for (int i = 1; i <= _Xsize ; i++){
        for(int j = 1; j <= _Ysize; j++)
            if (!_results[i][j].done) 
                maxPrice(i,j);
    }
    // for (int i = 0; i < _Xsize; i++){
    //     for(int j = 0; j < _Ysize; j++)
    //         cout << _results[i][j].first << " ";
    //     cout << endl;
    // }
    cout << _results[_Xsize][_Ysize].price<< endl;
    // auto end_time = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(end_time - start_time);
    // cout << "it took " << duration.count()<<endl;
    return 0;
}