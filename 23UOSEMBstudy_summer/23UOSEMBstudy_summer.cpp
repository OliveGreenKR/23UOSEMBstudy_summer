#include <iostream>
#include <iomanip>  //setprecision
#include <ios>      //streamsize
#include <string>

using namespace std;
//using std::cin;


int main()
{
    ios_base::sync_with_stdio(false); //FASTIO , dont use printf,scanf anymore

    // 정보 입력
    string name;
    cout << "enter your first name : ";
    cin >> name; 

    double midterm, final;
    cout << "Enter your midterm and final exam grades : ";
    cin >> midterm >> final;

    double homework;
    double sum_hw = 0;
    int cnt_hw = 0;
    cout << "Enter your howework grades , followd by EOF.\n";

    while (cin >> homework) {
        ++cnt_hw;
        sum_hw += homework;
    }
   
    streamsize prec = cout.precision();
    cout << "yout final grade is " << setprecision(3)
        << 0.2 * midterm + 0.4* final + 0.4*(sum_hw / cnt_hw) << setprecision(prec) << endl;

    /* 
    streamsize prec = cout.precision(3);   
    cout << "yout final grade is " << setprecision(3)
         << 0.2 * midterm + 0.4* final + 0.4*(sum_hw / cnt_hw) << setprecision(prec) << endl;
    cout.precision(prec);
    
    이렇게도 가능하지만, 위의 방법을 추천.
    why? 아래의 방법은 cout 전체에 적용 -> 프로그램 전체에 영향을 미치므로 위험하다.
    */
}


