#include <iostream>
#include <unordered_map>
#include <string>
#include <array>
#include <utility>
#include <chrono>
using namespace std;
//using namespace chrono;
int _Xsize, _Ysize;
int _NumPieces;
struct Price{int price = -1;};
unordered_map <string,int> _pieces;
Price **_results;
string key;
string key_rot;
void readInput(){
    int x,y,price;
    cin >> _Xsize; cin.ignore(); cin >> _Ysize;
    cin >> _NumPieces;
    for (int i = 0; i < _NumPieces; i++){
        cin >> x; cin.ignore(); cin >> y; cin.ignore(); cin >> price;
        if (price > 0){
            string dimensions = to_string(x) + "," + to_string(y);
            //string dimensions_rot = to_string(y) + "," + to_string(x);
            //if (_pieces.count(dimensions) > 0 || _pieces.count(dimensions_rot)) price = max(price,_pieces[dimensions]);
            _pieces[dimensions] = price;
        }
    }

}
int maxPrice(int x, int y){
    if (_results[x-1][y-1].price != -1) return _results[x-1][y-1].price;
    if (_results[y-1][x-1].price != -1) return _results[y-1][x-1].price;
    int max_price = 0;
    key = to_string(x) + "," + to_string(y);
    key_rot = to_string(y) + "," + to_string(x);
    if (_pieces.count(key) > 0) max_price = _pieces[key];
    else if(_pieces.count(key_rot) > 0) max_price = _pieces[key_rot];
    for (int k = 1; k < max(x,y); k++){
        if (x > k)
            max_price = max(max_price,maxPrice(k,y) + maxPrice(x-k,y));
        if (y > k) 
            max_price = max(max_price,maxPrice(x,k) + maxPrice(x,y-k));
    }
    _results[x-1][y-1].price = max_price;
    _results[y-1][x-1] = _results[x-1][y-1];
    return max_price;
}

int main(){
    //auto start_time = high_resolution_clock::now();
    readInput();
    _results = new Price*[max(_Xsize,_Ysize)];
    for (int i = 0; i < max(_Xsize,_Ysize); i++){
        _results[i] = new Price[max(_Xsize,_Ysize)];
    }
    // for (int i = 0; i < max(_Xsize, _Ysize); i++){
    //     for (int j = 0; j < max(_Xsize, _Ysize); j++){
    //         _results[i][j] = -1;
    //     }
    // }
    cout << maxPrice(_Xsize,_Ysize) << endl;
    // auto end_time = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(end_time - start_time);
    // cout << "it took " << duration.count()<<endl; 
    return 0;
}