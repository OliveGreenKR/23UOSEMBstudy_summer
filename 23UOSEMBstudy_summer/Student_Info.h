#pragma once
#include <iostream>
#include <string>
#include <vector>

//학생들의 공통 정보를 다루는 클래스 [name][mid][final][hws...]
class Core {
public:
	//생성자 및 소멸자
	Core() : _midterm(0), _final(0) { }; //기본 생성자 + 멤버 변수 초기화
	Core(std::istream& is) { read(is); };
public: 
	bool valid() const { return !_homework.empty(); } //비어있는 객체에 대한 잠재적인 예외를 회피가능
	std::string name() const { return _name; }
	std::istream& read(std::istream&);
	virtual double grade() const;
	operator double() const;

protected:
	std::istream& read_common(std::istream&);
	double _midterm = 100.0; //직접 값 지정은 이니셜라이저보다 먼저 실행되므로, 덮어씌어진다.
	double _final = 0.0;
	vector<double> _homework = vector<double>(0.);
private:
	string _name;
};

bool compare_name(const Core& A, const Core& B);
bool compare_grade(const Core& A, const Core& B);

//대학원생 [name][mid][final][thesis][hws...]
class Grad : public Core {
public:
	Grad() : _thesis(0) { };
	Grad(std::istream& is) { read(is); }; // Core() : ... -> Grad(is) { Grad::read(is); }  

	double grade() const;
	std::istream& read(std::istream&);

private:
	double _thesis;
};