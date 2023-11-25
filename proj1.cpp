#include <iostream>
#include <list>
#include <vector>
#include <tuple>

using namespace std;
int _Xsize, _Ysize;
int _NumPieces;
int _horizontalCut[2];
int _verticalCut[2];
list<tuple<int,int,int>> _pieces;
// tuple -> (x_size, y_size, price)
int _results[20][20];

void readInput(){
    int x,y,price;
    cin >> _Xsize; cin.ignore(); cin >> _Ysize;
    cin >> _NumPieces;
    for (int i = 0; i < _NumPieces; i++){
        cin >> x; cin.ignore(); cin >> y; cin.ignore(); cin >> price;
        _pieces.push_front(make_tuple(x,y,price));
    }

}
// max{corte vertical, corte horizontal, vender(se possível)}
//para cada elemento da lista
int maxPrice(int x, int y){
    if (_results[x-1][y-1] != -1) return _results[x-1][y-1];
    int decider = 0 , price = 0, n = 1;
    int max_Price = 0, max_PricePiece;
    for (list<tuple<int,int,int>>::iterator it = _pieces.begin(); it != _pieces.end(); ++it){
        // cout <<  n  << endl;
        // cout << "----------" << endl;
        if ((x == get<0>(*it) && y == get<1>(*it)) ||
            (x == get<1>(*it) && y == get<0>(*it)))
            price = get<2>(*it);
        //horizontal cut
        if (x > get<0>(*it)){
            _horizontalCut[0] = x - get<0>(*it);
            _horizontalCut[1] =  x - _horizontalCut[0];
            decider++;
        }
        //vertical cut
        if (y > get<1>(*it)){
            _verticalCut[0] = y - get<1>(*it);
            _verticalCut[1] =  y - _verticalCut[0];
            decider+=2;
        }
        switch(decider){
            case(0): max_PricePiece = price;
                break;
            case(1): max_PricePiece = max(maxPrice(_horizontalCut[0],y) + maxPrice(_horizontalCut[1],y),price);
                break;
            case(2): max_PricePiece = max(maxPrice(x,_verticalCut[0]) + maxPrice(x,_verticalCut[1]),price);
                break;
            case(3): max_PricePiece = max(max(maxPrice(_horizontalCut[0],y) + maxPrice(_horizontalCut[1],y),
            maxPrice(x,_verticalCut[0]) + maxPrice(x,_verticalCut[1])),price);
                break;
            default: max_PricePiece = 0;
        }
        if (max_PricePiece > max_Price) max_Price = max_PricePiece;
        decider = 0;
    }
    _results[x-1][y-1] = max_Price;
    return _results[_Xsize-1][_Ysize-1];
}

int main(){
    readInput();
    for (int i= 0; i < _Xsize; i++){
        for (int j = 0; j < _Ysize; j++){
            _results[i][j] = -1;
        }
    }
    cout << maxPrice(_Xsize,_Ysize) << endl;
    return 0;
}
