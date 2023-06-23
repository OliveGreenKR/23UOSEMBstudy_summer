#include <iostream>
#include <iomanip>  //setprecision
#include <ios>      //streamsize
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define OUT

using namespace std;

template <typename T = double>
auto GetAvgFromVec = [](const vector<T>& vec) {  //lamda
	T sum = 0;
	for (auto& e : vec)
		sum += e;
	return  sum / vec.size();
};

double grade(double midterm, double final, vector<double>& homeworks) {

    if (homeworks.size() == 0)
        throw domain_error("student has done no homework");

    return 0.4 * midterm  + 0.4 * final + 0.2 * GetAvgFromVec<double>(homeworks);
}

//스트림을 이용해 숙제 점수를 입력받아서 벡터에 저장
istream& read_hw(istream& in, OUT vector<double>& hws) {
    if (in) {
        
        hws.clear(); // make empty

        double x;
        while (in >> x) {
            hws.push_back(x);
        }

        in.clear(); //clear stream
    }
    return in;
}

int main()
{
    ios_base::sync_with_stdio(false); //FASTIO , dont use printf,scanf anymore

    string name;
    cout << "student name : ";
    cin >> name;
    
    double midterm, final;
    cout << "midterm and final : ";
    cin >> midterm >> final; 

    vector<double> hw;
    cout << "homeworks followd by EOF : ";
    read_hw(::cin, hw);

    try {
        double final_grade = grade(midterm, final, hw);
        streamsize prec = cout.precision(3);
        cout << "yout final grade is : " << setprecision(3) << final_grade << setprecision(prec) << endl;
    }
    catch (domain_error) {
        cin.clear();
        cout << "you must enter your homework grades!\n"
            << "Try Again";
        return 1; //exit with error
    }

    return 0;
}


