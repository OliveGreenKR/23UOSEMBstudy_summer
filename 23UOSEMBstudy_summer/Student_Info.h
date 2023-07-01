#pragma once
#include <iostream>
#include <string>
#include <vector>

//�л����� ���� ������ �ٷ�� Ŭ���� [name][mid][final][hws...]
class Core {
public:
	//������ �� �Ҹ���
	Core() : _midterm(0), _final(0) { }; //�⺻ ������ + ��� ���� �ʱ�ȭ
	Core(std::istream& is) { read(is); };

	virtual ~Core() { }

public: 
	bool valid() const { return !_homework.empty(); } //����ִ� ��ü�� ���� �������� ���ܸ� ȸ�ǰ���
	std::string name() const { return _name; }

	virtual std::istream& read(std::istream&);
	virtual double grade() const;

	operator double() const;

protected:
	std::istream& read_common(std::istream&);
	double _midterm = 100.0; //���� �� ������ �̴ϼȶ��������� ���� ����ǹǷ�, ���������.
	double _final = 0.0;
	vector<double> _homework = vector<double>(0.);
private:
	string _name;
};

bool compare_name(const Core& A, const Core& B);
bool compare_grade(const Core& A, const Core& B);

//���п��� [name][mid][final][thesis][hws...]
class Grad : public Core {
public:
	Grad() : _thesis(0) { };
	Grad(std::istream& is) { read(is); }; // Core() : ... -> Grad(is) { Grad::read(is); }  

	double grade() const;
	std::istream& read(std::istream&);

private:
	double _thesis;
};


//�ڵ� Ŭ����
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

/*���� ��� �Լ�
* ���� ��� �Լ��� �ش� Ŭ���� Ÿ���� ��ü�� �̿��� ȣ�� ���� �ʴ´�.
* ���� ��� �Լ��� �Ϲ����� ��� �Լ��ʹ� �ٸ��� �ش� Ŭ������ ������ ��, Ư�� ��ü�� 
* ���� ���� �ʴ´�.
* 
* ���� ���� ��� �Լ��� Ŭ���� ��ü�� �������� ���� ������ ����� ������ �� ����.
* 
* �ܺο��� ����� ��, Student_info::compare_name
* �Լ���� ���� �����ڸ� ����ؾ��ϱ� ������, �������� �� �� �ֵ��� �Ѵ�.
*/