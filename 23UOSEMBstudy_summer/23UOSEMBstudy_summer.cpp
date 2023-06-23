#include <iostream>
#include <iomanip>  //setprecision
#include <ios>      //streamsize
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
//using std::cin;

bool Greater(const double& A, const double& B) {
    return A>B;
}

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

    vector<double> homeworks;
    double homework;
    double sum_hw = 0;
  
    cout << "Enter your howework grades , followd by EOF.\n";

    while (cin >> homework) {
        homeworks.push_back(homework);
        sum_hw += homework;
    }
   
    //sorting 오름차순
    ::sort(homeworks.begin(), homeworks.end());
    
    for (double hw : homeworks)
        cout << hw << " ";
    
    cout << "\n------------\n";

    //sorting 내림차순
    ::sort(homeworks.begin(), homeworks.end(),::greater<double>());
    //::sort(homeworks.begin(), homeworks.end(), [ ](const double& A, const double& B) { return A > B; });
    //::sort(homeworks.begin(), homeworks.end(), Greater);

 

    for (double hw : homeworks)
        cout << hw << " ";

    cout << "\n------------\n";




    streamsize prec = cout.precision();
    cout << "yout final grade is " << setprecision(3)
        << 0.2 * midterm + 0.4* final + 0.4*(sum_hw / homeworks.size()) << setprecision(prec) << endl;

    /* 
    streamsize prec = cout.precision(3);   
    cout << "yout final grade is " << setprecision(3)
         << 0.2 * midterm + 0.4* final + 0.4*(sum_hw / cnt_hw) << setprecision(prec) << endl;
    cout.precision(prec);
    
    이렇게도 가능하지만, 위의 방법을 추천.
    why? 아래의 방법은 cout 전체에 적용 -> 프로그램 전체에 영향을 미치므로 위험하다.
    */
}


