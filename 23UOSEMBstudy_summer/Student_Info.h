#pragma once
#include <iostream>
#include <string>
#include <vector>

class Student_Info {
public:
	//������ �� �Ҹ���
	Student_Info() : _midterm(0), _final(0) { }; //�⺻ ������ + ��� ���� �ʱ�ȭ
	Student_Info(std::istream&);
public: 
	bool valid() const { return !_homework.empty(); } //����ִ� ��ü�� ���� �������� ���ܸ� ȸ�ǰ���
	std::string name() const { return _name; }

	std::istream& read(std::istream&);

	double grade() const;

private:
	string _name;
	double _midterm = 100.0; //���� �� ������ �̴ϼȶ��������� ���� ����ǹǷ�, ���������.
	double _final = 0.0;
	vector<double> _homework = vector<double>(0.);
};

bool compare_name(const Student_Info& A, const Student_Info& B);
