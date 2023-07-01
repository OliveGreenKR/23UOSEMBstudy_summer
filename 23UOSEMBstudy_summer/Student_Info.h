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

	virtual ~Core() { }

public: 
	bool valid() const { return !_homework.empty(); } //비어있는 객체에 대한 잠재적인 예외를 회피가능
	std::string name() const { return _name; }

	virtual std::istream& read(std::istream&);
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


//핸들 클래스
class Student_info {

	enum Student : char {
		core	= 'U',
		grad    = 'G',
	};

public:
	Student_info() : _cp(nullptr) { }
	Student_info(std::istream& is) : _cp(nullptr) { read(is); }
	Student_info(const Student_info& s);
	Student_info operator= (const Student_info& s);

	~Student_info(){ delete _cp; }
public:
	std::istream& read(std::istream&);
	std::string name() const;
	double grade() const;

	static bool compare_name(const Student_info& s1, const Student_info& s2) {
		return s1.name() < s2.name();
	}

private:
	Core* _cp;
};

/*정적 멤버 함수
* 정적 멤버 함수는 해당 클래스 타입의 객체를 이용해 호출 하지 않는다.
* 정적 멤버 함수는 일반적인 멤버 함수와는 다르게 해당 클래스와 연관될 뿐, 특정 객체와 
* 연관 되지 않는다.
* 
* 따라서 정적 멤버 함수는 클래스 객체의 정적이지 않은 데이터 멤버에 접근할 수 없다.
* 
* 외부에서 사용할 때, Student_info::compare_name
* 함수라고 범위 연산자를 명시해야하기 때문에, 연관성을 알 수 있도록 한다.
*/