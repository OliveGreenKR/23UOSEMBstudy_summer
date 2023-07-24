#include <iostream>
#include <iomanip>  //setprecision
#include <ios>      //streamsize
#include <string>
#include <ostream>
using namespace std;
//using std::cin;

template <typename T>
void print(T arg, string sep = "\n") {
    std::cout << arg << sep;
}

template<>
void print(double arg, string sep) {
    streamsize prec = cout.precision();
    std::cout << setprecision(3) << arg << setprecision(prec) << sep;
}

template <typename T,typename... Types>
void print(T arg, Types... args) {
    static string sep(", ");
    print(arg , sep);
    print(args...);
}

int main()
{
    ios_base::sync_with_stdio(false); //FASTIO , dont use printf,scanf anymore
    double d = 3.5555;
    print(1.45855);
	print(1.45855, "abc", 3.112313553, 1, d, 2, 3, 4, "jjjj");
}


