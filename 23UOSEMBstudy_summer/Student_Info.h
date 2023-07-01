#pragma once
#include <iostream>
#include <string>
#include <vector>

bool compare_name(const Core& A, const Core& B);

//�л����� ���� ������ �ٷ�� Ŭ����
class Core {
public:
	//������ �� �Ҹ���
	Core() : _midterm(0), _final(0) { }; //�⺻ ������ + ��� ���� �ʱ�ȭ
	Core(std::istream&);
public: 
	bool valid() const { return !_homework.empty(); } //����ִ� ��ü�� ���� �������� ���ܸ� ȸ�ǰ���
	std::string name() const { return _name; }
	std::istream& read(std::istream&);
	double grade() const;
	operator double() const;

protected:
	std::istream& read_common(std::istream&);
	double _midterm = 100.0; //���� �� ������ �̴ϼȶ��������� ���� ����ǹǷ�, ���������.
	double _final = 0.0;
	vector<double> _homework = vector<double>(0.);
private:
	string _name;
};


//���п���
class Grad : public Core {
public:
	Grad();
	Grad(std::istream&);
	double grade() const;
	std::istream& read(std::istream&);

private:
	double _thesis;
};