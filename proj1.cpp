
#include <iostream>
#include <list>
#include <vector>
#include <tuple>

using namespace std;
int _Xsize, _Ysize;
int _NumPieces;
std::list<std::tuple<int,int,int>> _pieces;
// tuple -> (x_size, y_size, price)
int **_results;

void readInput(){
    int x,y,price;
    std::cin >> _Xsize; std::cin.ignore(); std::cin >> _Ysize;
    std::cin >> _NumPieces;
    for (size_t i = 0; i < _NumPieces; i++){
        std::cin >> x; std::cin.ignore(); std::cin >> y; std::cin.ignore(); std::cin >> price;
        _pieces.push_front(std::make_tuple(x,y,price));
    }

}
// max{corte vertical, corte horizontal, vender(se possível)}
//para cada elemento da lista
int maxPrice(int x, int y){
    if (_results[x-1][y-1] != NULL) return _results[x-1][y-1];
    std::tuple<int,int,int> piece;
    int price = 0;
    std::tuple<int,int> horizontal_cut;
    std::tuple<int,int> vertical_cut;
    int maxfeuhrrehgbe;
    for (std::list<std::tuple<int,int,int>>::iterator it = _pieces.begin(); it != _pieces.end(); ++it){
        piece = *it;
        
        if ((x == std::get<0>(piece) && y == std::get<1>(piece)) ||
            x == std::get<1>(piece) && y == std::get<0>(piece))
                price = get<2>(piece);
        //corte horizontal
        if (x > std::get<0>(piece))
            horizontal_cut = std::make_tuple(x - std::get<0>(piece) ,x - (x - std::get<0>(piece)));
        if (y > std::get<1>(piece))
            vertical_cut = std::make_tuple(y - std::get<1>(piece) ,y - (y - std::get<1>(piece)));
        
        //vertical ou horizontal
        max(max(maxPrice(get<0>(horizontal_cut),y) + maxPrice(get<1>(horizontal_cut),y),
        maxPrice(x,get<0>(vertical_cut)) + maxPrice(x,get<1>(vertical_cut))),price);
            
        }
        //corte vertical
        
        
        return _results[_Xsize][_Ysize];
    }

int main(){
    readInput();
    _results = new int*[_Xsize];
    for (size_t i = 0; i < _Xsize; i++){
        _results[i] = new int[_Ysize];
    }
    maxPrice(_Xsize,_Ysize);
    return 0;
}
