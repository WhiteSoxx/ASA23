#include <iostream>
#include <list>
#include <vector>
#include <tuple> 
unsigned _Xsize, _Ysize, _NumPieces;
std::list<std::tuple<int,int,int>> _pieces;
// tuple -> (x_size, y_size, price)

void readInput(){
    int x,y,price;
    std::cin >> _Xsize; std::cin.ignore(); std::cin >> _Ysize;
    std::cin >> _NumPieces;
    for (size_t i = 0; i < _NumPieces; i++){
        std::cin >> x; std::cin.ignore(); std::cin >> y; std::cin.ignore(); std::cin >> price;
        _pieces.push_front(std::make_tuple(x,y,price));
    }
    
    // std :: cout << _Xsize << std::endl;
    // std :: cout << _Ysize << std::endl;
    // for (std::list<std::tuple<int,int,int>>::iterator it_i = _pieces.begin(); it_i != _pieces.end(); ++it_i) {
    //     std::cout << std::get<0>(*it_i) << " ";
    //     std::cout << std::get<1>(*it_i) << " ";
    //     std::cout << std::get<2>(*it_i) << std::endl;
        
    // }



}
int main(){
    readInput();
    return 0;
}
