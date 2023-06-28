#pragma once
#include <iostream>
#include <string>
#include <vector>

class Student_Info {
public:
	//생성자 및 소멸자
	Student_Info() : _midterm(0), _final(0) { }; //기본 생성자 + 멤버 변수 초기화
	Student_Info(std::istream&);
public: 
	bool valid() const { return !_homework.empty(); } //비어있는 객체에 대한 잠재적인 예외를 회피가능
	std::string name() const { return _name; }

	std::istream& read(std::istream&);

	double grade() const;

private:
	string _name;
	double _midterm = 100.0; //직접 값 지정은 이니셜라이저보다 먼저 실행되므로, 덮어씌어진다.
	double _final = 0.0;
	vector<double> _homework = vector<double>(0.);
};

bool compare_name(const Student_Info& A, const Student_Info& B);
