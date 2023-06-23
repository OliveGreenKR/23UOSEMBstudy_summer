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

    // ���� �Է�
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
   
    //sorting ��������
    ::sort(homeworks.begin(), homeworks.end());
    
    for (double hw : homeworks)
        cout << hw << " ";
    
    cout << "\n------------\n";

    //sorting ��������
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
    
    �̷��Ե� ����������, ���� ����� ��õ.
    why? �Ʒ��� ����� cout ��ü�� ���� -> ���α׷� ��ü�� ������ ��ġ�Ƿ� �����ϴ�.
    */
}


