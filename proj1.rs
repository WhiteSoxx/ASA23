use std::io;
use std::collections::HashMap;

fn read_input(input: &mut String){
  
    io::stdin().read_line(input).expect("Failed to read line");

    let mut size = input.trim().split(' ');

    // X-size of the original piece
    let x_size: i32 = match size.next() {
        Some(substring) => substring.parse().expect(&format!("Invalid number: {}", substring)),
        None => panic!("No substring found"),
    };

    // Y-size of the original piece
    let y_size: i32 = match size.next() {
        Some(substring) => substring.parse().expect(&format!("Invalid number: {}", substring)),
        None => panic!("No substring found"),
    };

    input.clear();

    io::stdin().read_line(input).expect("Failed to read line");

    let num_pieces: usize = input.trim().parse().expect("Invalid number");


    let mut _prices: Vec<i32> = vec![0;num_pieces];
    let mut _dimensions:HashMap<i32,(i32,i32)> = HashMap::new();

    let mut x:i32;
    let mut y:i32;

    for i in 0..num_pieces{
        input.clear();
        io::stdin().read_line(input).expect("Failed to read line");
        let mut pieces =  input.trim().split(' ');
        x = match pieces.next() {
            Some(substring) => substring.parse().expect(&format!("Invalid number: {}", substring)),
            None => panic!("No substring found"),
        };
        y = match pieces.next() {
            Some(substring) => substring.parse().expect(&format!("Invalid number: {}", substring)),
            None => panic!("No substring found"),
        };
        _prices[i] = match pieces.next() {
            Some(substring) => substring.parse().expect(&format!("Invalid number: {}", substring)),
            None => panic!("No substring found"),
        };
        _dimensions.insert(_prices[i],(x,y));
        println!("{}",_prices[i]);
        println!("{:?} ",_dimensions.get(&_prices[i]));
    }
    println!("First number: {}", x_size);
    println!("Second number: {}", y_size);
    println!("Number of pieces: {}", num_pieces);
}

fn main() {
    let mut input = String::new();
    read_input(&mut input);
}
