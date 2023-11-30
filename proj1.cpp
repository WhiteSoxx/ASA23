#include <iostream>
#include <array>
#include <chrono>
using namespace std;
//using namespace chrono;
// meter sem memoization (tentar)
// guardar os valores na tabela calcular para todos os da tabela;
// simplesmente iterar pela tabela-> já vou ter os valores para trás
int _Xsize, _Ysize;
int _NumPieces;
struct Price{int price = -1;};
Price **_results;

void readInput(){
    int x,y,price;
    cin >> _Xsize; cin.ignore(); cin >> _Ysize;
    cin >> _NumPieces;
    _results = new Price*[max(_Xsize,_Ysize)];
    for (int i = 0; i < max(_Xsize,_Ysize); i++)
        _results[i] = new Price[max(_Xsize,_Ysize)];
    for (int i = 0; i < _NumPieces; i++){
        cin >> x; cin.ignore(); cin >> y; cin.ignore(); cin >> price;
        if (price > 0 && ((x <= _Xsize && y <= _Ysize) || (x <= _Ysize && y <=_Xsize))){
            if (_results[x-1][y-1].price > 0 || _results[y-1][x-1].price > 0){
                _results[x-1][y-1].price = max(max(_results[x-1][y-1].price, _results[y-1][x-1].price),price);
                _results[y-1][x-1].price = -1;
            }
            else{_results[x-1][y-1].price = price;}
        }
    }
}
void maxPrice(int x, int y){
    int price = 0,vertical_cut = 0,max_vertical_cut = 0, max_horizontal_cut = 0,horizontal_cut = 0;
    if (_results[x-1][y-1].price != -1) price = _results[x-1][y-1].price;
    if (_results[y-1][x-1].price != -1) price = _results[y-1][x-1].price;
    for (int k = 1; k < max(x,y); k++){
        if (x > k && k <= x/2){
            horizontal_cut = _results[k-1][y-1].price + _results[x-k-1][y-1].price;
            max_horizontal_cut = (horizontal_cut > max_horizontal_cut) ? horizontal_cut : max_horizontal_cut;
        }
        if (y > k && k <= y/2){
            vertical_cut = _results[x-1][k-1].price + _results[x-1][y-k-1].price;
            max_vertical_cut = (vertical_cut > max_vertical_cut) ? vertical_cut : max_vertical_cut;
        }
    }
    _results[x-1][y-1].price = max(max(price,max_horizontal_cut),max_vertical_cut);
}
int main(){
    //auto start_time = high_resolution_clock::now();
    readInput();
    for (int i = 0; i < _Xsize; i++)
        for(int j = 0; j < _Ysize; j++)
            maxPrice(i+1,j+1);
    cout << _results[_Xsize-1][_Ysize-1].price << endl;
    // auto end_time = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(end_time - start_time);
    // cout << "it took " << duration.count()<<endl;
    return 0;
}