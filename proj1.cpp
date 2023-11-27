#include <iostream>
#include <unordered_map>
#include <string>
#include <array>
using namespace std;
int _Xsize, _Ysize;
int _NumPieces;

unordered_map <string,int> _pieces;
// hasMap -> "x,y" : price
int **_results;
void readInput(){
    int x,y,price;
    cin >> _Xsize; cin.ignore(); cin >> _Ysize;
    cin >> _NumPieces;
    for (int i = 0; i < _NumPieces; i++){
        cin >> x; cin.ignore(); cin >> y; cin.ignore(); cin >> price;
        if (price > 0){
            string dimensions = to_string(x) + "," + to_string(y);
            string dimensions_rot = to_string(y) + "," + to_string(x);
            if (_pieces.count(dimensions) > 0 || _pieces.count(dimensions_rot)) price = max(price,_pieces[dimensions]);
            _pieces[dimensions] = price;
        }
    }

}
int maxPrice(int x, int y){
    if (_results[x-1][y-1] != -1) return _results[x-1][y-1];
    if (_results[y-1][x-1] != -1) return _results[y-1][x-1];
    int max_price = 0,vertical_cut = 0, horizontal_cut = 0;
    string key = to_string(x) + "," + to_string(y);
    string key_rot = to_string(y) + "," + to_string(x);
    if (_pieces.count(key) > 0) max_price = _pieces[key];
    else if(_pieces.count(key_rot) > 0) max_price = _pieces[key_rot];
    for (int k = 1; k < max(x,y); k++){
        if (x > k){
            horizontal_cut = maxPrice(k,y) + maxPrice(x-k,y);
            max_price = max(max_price,horizontal_cut);
        }
        if (y > k) {
            vertical_cut = maxPrice(x,k) + maxPrice(x,y-k);
            max_price = max(max_price,vertical_cut);
        }
        horizontal_cut = 0;
        vertical_cut = 0;
        _results[x-1][y-1] = max_price;
        _results[y-1][x-1] = _results[x-1][y-1];
    }
    return max_price;
}

int main(){
    readInput();
    _results = new int*[max(_Xsize,_Ysize)];
    for (int i = 0; i < max(_Xsize,_Ysize); i++){
        _results[i] = new int[max(_Xsize,_Ysize)];
    }
    for (int i = 0; i < max(_Xsize, _Ysize); i++){
        for (int j = 0; j < max(_Xsize, _Ysize); j++){
            _results[i][j] = -1;
        }
    }
    cout << maxPrice(_Xsize,_Ysize) << endl;
    return 0;
}