#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Handle.h>

class Core {
	friend class Student_info;

public:
	Core() : _midterm(0), _final(0) { }; //기본 생성자 + 멤버 변수 초기화
	Core(std::istream& is) { read(is); };

	virtual ~Core() { }

public: 
	bool valid() const { return !_homework.empty(); } //비어있는 객체에 대한 잠재적인 예외를 회피가능
	std::string name() const { return _name; }

	virtual std::istream& read(std::istream&);
	virtual double grade() const;

	operator double() const;

	virtual Core* clone() const { return new Core(*this); }

protected:
	std::istream& read_common(std::istream&);
	
	double _midterm = 100.0; //직접 값 지정은 이니셜라이저보다 먼저 실행되므로, 덮어씌어진다.
	double _final = 0.0;
	vector<double> _homework = vector<double>(0.);
private:
	string _name;
};

class Grad : public Core {
public:
	Grad() : _thesis(0) { };
	Grad(std::istream& is) { read(is); };

	double grade() const;
	std::istream& read(std::istream&);

protected:
	Grad* clone() const { return new Grad(*this); }

private:
	double _thesis;
};

//인터페이스 클래스
class Student_info {
public:

	enum Student : char {
		core	= 'U',
		grad    = 'G',
	};

public:
	Student_info() { }
	Student_info(std::istream& is) { read(is); }
	//Student_info(const Student_info& s);
	//Student_info operator= (const Student_info& s);
	//~Student_info(){ delete _cp; }
public:
	std::istream& read(std::istream&);
	std::string name() const;
	double grade() const;

	static bool compare_name(const Core& s1, const Core& s2) {
		return s1.name() < s2.name();
	}
private:
	Handle<Core> _cp;
};

