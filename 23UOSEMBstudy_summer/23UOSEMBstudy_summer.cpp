#include <iostream>
#include <iomanip>  //setprecision
#include <ios>      //streamsize
#include <string>
#include <ostream>
using namespace std;
//using std::cin;

template <typename T>
void print(T arg) {
    std::cout << arg << std::endl;
}

template<>
void print(double arg) {
    streamsize prec = cout.precision();
    std::cout << setprecision(3) << arg << setprecision(prec) << std::endl;
}

template <typename... Types>
void print(double arg, Types... args) {
    streamsize prec = cout.precision();
    std::cout << setprecision(3) << arg << setprecision(prec) << ", ";
    print(args...);
}



template <typename T, typename... Types>
void print(T arg, Types... args) {
    std::cout << arg << ", ";
    print(args...);
}



int main()
{
    ios_base::sync_with_stdio(false); //FASTIO , dont use printf,scanf anymore
    double d = 3.5555;
	print("abc", 3.112313553, 1, d, 2, 3, 4, "jjjj");

}


