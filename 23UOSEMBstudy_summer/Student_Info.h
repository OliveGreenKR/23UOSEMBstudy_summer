#pragma once
#include <iostream>
#include <string>
#include <vector>

class Student_Info {
public: //�������̽�
	std::istream& read(std::istream&);
	double grade() const;  //const  : �ش� �Լ��� ȣ���� Student_Info�� ������ �ٲ��� ���� ���̴�.

	//accessor funtion (getter��� ��)
	std::string name() const { return _name; }

	/*name�� accessor�� �������̽�(public)�μ� ����� ����:
	*  �ش� Ŭ������ �߻�ȭ�� 1.�л� 2. �л��� ���� ����  �̴�.
	* ���� �̸��� ����ϰ� ������ ����ȭ�� �����ϴ� ���� ���� ����.
	*/

private:
	string _name;
	double _midterm = 0.0;
	double _final = 0.0;
	vector<double> _homework = vector<double>(0.);
};
