#include "pch.h"
#include "Student_Info.h"]
#include <list>
#include <ios> //for domain_error
#include <numeric> //accumulate
#include <algorithm>

double getAverage(const vector<double>& v) {
	return ::accumulate(v.begin(), v.end(), 0.0) / v.size();  //return Ÿ���� ���� *0.0
}

double grade(const double midterm, const  double final, const vector<double>& homeworks) {

	if (homeworks.size() == 0)
		throw domain_error("student has done no homework");

	return 0.4 * midterm  + 0.4 * final + 0.2 * getAverage(homeworks);
}

//��Ʈ���� �̿��� ���� ������ �Է¹޾Ƽ� ���Ϳ� ����
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

bool compare_name(const Student_Info& A, const Student_Info& B) {
    return A.name() < B.name(); 
}

//���������� ���ڷ� ��ȯ
string letter_grade(double grade) {
    static const double numbers[] = {97,94,90,87,84,80,77,74,70,60,0};
    static const char* const letters[] = {"A+", "A", "A-", "B+", "B","B-","C+", "C", "C-", "D", "F"};
    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);  //�迭 ���� =  �迭 ��ü ũ�� / ��� �ϳ� ũ��

    for (size_t i = 0; i < ngrades; i++) {
        if (grade >= numbers[i])
            return letters[i];
    }
    return "???"; 
}

/**********************
* Student_Info::
**********************/

Student_Info::Student_Info(std::istream& is) {
    read(is);
}

std::istream& Student_Info::read(std::istream& in) {
    in >> _name >> _midterm >> _final; 
    read_hw(in, _homework);
    return in;
}

double Student_Info::grade() const {
    return ::grade(_midterm, _final, _homework);  
}

Student_Info::operator double() const {
    return grade();
}
