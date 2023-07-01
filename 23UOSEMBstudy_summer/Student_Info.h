#pragma once
#include <iostream>
#include <string>
#include <vector>

//학생들의 공통 정보를 다루는 클래스 [name][mid][final][hws...]
class Core {
	friend class Student_info;

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
	virtual Core* clone() const { return new Core(*this); }

	double _midterm = 100.0; //직접 값 지정은 이니셜라이저보다 먼저 실행되므로, 덮어씌어진다.
	double _final = 0.0;
	vector<double> _homework = vector<double>(0.);
private:
	string _name;
};

//bool compare_name(const Core& A, const Core& B);
//bool compare_grade(const Core& A, const Core& B);

//대학원생 [name][mid][final][thesis][hws...]
class Grad : public Core {
	//Student_info 를  friend로 할 필요는 없다.
	//Student_info는 Core*를 사용하기에, 직접적으로 Grad의 clone함수에 접근하지 않기 때문.
	//Student_info는 가상함수인 Core::clone()만 호출할 뿐이다.
public:
	Grad() : _thesis(0) { };
	Grad(std::istream& is) { read(is); }; // Core() : ... -> Grad(is) { Grad::read(is); }  

	double grade() const;
	std::istream& read(std::istream&);

protected:
	Grad* clone() const { return new Grad(*this); }
	/*
	* 일반적으로 가상함수를 재정의할 때는 함수의 프로토타입이 모두 같아야한다.
	* 그러나 예외적으로, 기본 클래스의 함수가 기본클래스의 참조/포인터를 반환할 때는
	* 파생 클래스는 그것을 본인의 타입의 그것으로 반환할 수 있다.
	*/

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

/*Wrapper class의 복사 생성자, 할당 연산자
* 새로운 객체를 위한 공간을 할당하고 값을 초기화 해야함.
* 복사하려는 객체의 종류를 알아야한다.
* 포인터로는 Core 인지 Core에서 파생한 클래스 인지 알 수 없음.
* 
* >> 해결을 위해 복사역할의 가상함수를 추가한다.
*    또한, 이것은 인터페이스가 아니기 때문에 protected의 영역으로 할것.
* >> Wrapper Class를 Core의 friend로 해야함.
*/