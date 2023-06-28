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

double grade(const Student_Info& student) {
	return grade(student._midterm, student._final, student._homework);
}

double grade_aux(const Student_Info& s) {

	try {
		return grade(s);
	}
	catch (domain_error) {
		//과제를 하나도 안함.
		const vector<double> hw(1, 0.0);
		return grade(s._midterm, s._final, hw);
	}
}

bool did_all_hw(const Student_Info& s) {
	return ::find(s._homework.begin(), s._homework.end(), 0.0) ==  s._homework.end();
}

double average_analysis(const vector<Student_Info>& students) {
	vector<double> grades;
	::transform(students.begin(), students.end(), ::back_inserter(grades), grade_aux);
	return getAverage(grades);
}

bool fgrade(const Student_Info& student) {
	return grade(student) < 60;
}

bool pgrade(const Student_Info& student) {
	return !fgrade(student);
}

vector<Student_Info> extract_fails(vector<Student_Info>& students) {
	vector<Student_Info>::iterator iter = ::stable_partition(students.begin(), students.end(), pgrade);
	vector<Student_Info> fail(iter, students.end());
	students.erase(iter, students.end());
	return fail;
}

list<Student_Info> extract_fails(OUT list<Student_Info>& students) {
	list<Student_Info> fail;
	auto iter = students.begin();
	while (iter != students.end()) {
		if (fgrade(*iter)) {
			fail.push_back(*iter);
			iter = students.erase(iter);

		}
		else
			++iter;
	}
	return fail;
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

istream& read_student(istream& in, OUT Student_Info& student) {
    in >> student._name >> student._midterm >> student._final;
    read_hw(in, student._homework);
    return in;
}

bool compare_name(const Student_Info& A, const Student_Info& B) { // 이름순으로  sorting 가능(오름차순)
    return A._name < B._name;
}

std::istream& Student_Info::read(std::istream& in) {
    in >> _name >> _midterm >> _final; //해당 클래스에 별다른 선언없이도 접근 가능.
    read_hw(in, _homework);
    return in;
}

double Student_Info::grade() const {
    return ::grade(_midterm, _final, _homework); //::를 통해 grade함수 확정! 
}
