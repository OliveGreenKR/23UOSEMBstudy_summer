#pragma once
#include <iostream>
#include <string>
#include <vector>

bool compare_name(const Core& A, const Core& B);

//학생들의 공통 정보를 다루는 클래스
class Core {
public:
	//생성자 및 소멸자
	Core() : _midterm(0), _final(0) { }; //기본 생성자 + 멤버 변수 초기화
	Core(std::istream&);
public: 
	bool valid() const { return !_homework.empty(); } //비어있는 객체에 대한 잠재적인 예외를 회피가능
	std::string name() const { return _name; }
	std::istream& read(std::istream&);
	double grade() const;
	operator double() const;

protected:
	std::istream& read_common(std::istream&);
	double _midterm = 100.0; //직접 값 지정은 이니셜라이저보다 먼저 실행되므로, 덮어씌어진다.
	double _final = 0.0;
	vector<double> _homework = vector<double>(0.);
private:
	string _name;
};


//대학원생
class Grad : public Core {
public:
	Grad();
	Grad(std::istream&);
	double grade() const;
	std::istream& read(std::istream&);

private:
	double _thesis;
};