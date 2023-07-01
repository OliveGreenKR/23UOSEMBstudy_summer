#include "pch.h"
#include "Student_Info.h"]
#include <list>
#include <ios> //for domain_error
#include <numeric> //accumulate
#include <algorithm>

double getAverage(const vector<double>& v) {
	return ::accumulate(v.begin(), v.end(), 0.0) / v.size();  //return 타입을 위해 *0.0
}

double grade(const double midterm, const  double final, const vector<double>& homeworks) {

	if (homeworks.size() == 0)
		throw domain_error("student has done no homework");

	return 0.4 * midterm  + 0.4 * final + 0.2 * getAverage(homeworks);
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

bool compare_name(const Core& A, const Core& B) {
    return A.name() < B.name(); 
}

//최종점수를 문자로 변환
string letter_grade(double grade) {
    static const double numbers[] = {97,94,90,87,84,80,77,74,70,60,0};
    static const char* const letters[] = {"A+", "A", "A-", "B+", "B","B-","C+", "C", "C-", "D", "F"};
    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);  //배열 길이 =  배열 전체 크기 / 요소 하나 크기

    for (size_t i = 0; i < ngrades; i++) {
        if (grade >= numbers[i])
            return letters[i];
    }
    return "???"; 
}

/**********************
* Core::
**********************/

std::istream& Core::read(std::istream& in) {
    in >> _name >> _midterm >> _final; 
    read_hw(in, _homework);
    return in;
}

//read student except hw
std::istream& Core::read_common(std::istream& in) {
    in >> _name >> _midterm >> _final;
    return in;
}

double Core::grade() const {
    return ::grade(_midterm, _final, _homework);  
}

Core::operator double() const {
    return grade();
}



/**********************
* Grad::
**********************/

double Grad::grade() const { //재정의
    return ::min(Core::grade(),_thesis);
    //여기는 범위 연산자를빼면, Grad::grade의 무한 호출이 발생한다.
}

std::istream& Grad::read(std::istream& in) {
    Core::read_common(in);    // 부모의 메소드 사용
    //read_common(in);        // 이것도 가능
    in >> _thesis;
    read_hw(in, _homework);
    return in;
}
