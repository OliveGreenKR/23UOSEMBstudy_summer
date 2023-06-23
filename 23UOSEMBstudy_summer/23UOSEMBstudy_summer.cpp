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
        in.clear(); //clear stream for next.
    }
    return in;
}

/*******************
*  prgram structualize
*******************/


struct Student_Info {
    string name;
    double midterm = 0;
    double final = 0;
    vector<double> hw = vector<double>(0.f);
}; //dont forget to add ';'


istream& read_student(istream& in, OUT Student_Info& student) {
	in >> student.name >> student.midterm >> student.final;
	read_hw(in, student.hw);
    return in;
}

double grade(Student_Info& student) {
    return grade(student.midterm, student.final, student.hw);
}

bool operator < (Student_Info& A, Student_Info& B) {  // 성적순으로 학생을 sorting 가능(오름차순)
    return grade(A) < grade(B);
}

bool compare_name(const Student_Info& A, const Student_Info& B) { // 이름순으로  sorting 가능(오름차순)
    return A.name < B.name;
}

int main()
{
    //ios_base::sync_with_stdio(false); //FASTIO , dont use printf,scanf anymore

    vector<Student_Info> students;
    Student_Info record;

    /*
   jeong 10 20 30 40 50
   kkk 10 20 50 60 30
   ppp 10 30 50 20  ^D
   ^D
   */
    while (read_student(cin, record)) {
        students.push_back(record);
    }
    
    //::sort(students.begin(), students.end()); //성적순
    ::sort(students.begin(), students.end(), compare_name); //이름순

    for (auto& s : students) {
        cout << s.name << "\n";
        try {
            double final_grade = grade(s);
            streamsize prec = cout.precision();

            cout << setprecision(3) << final_grade << setprecision(prec);
        }
        catch (domain_error e) {
            cout << e.what();
        }
        cout << endl;
    }
    return 0;
}


