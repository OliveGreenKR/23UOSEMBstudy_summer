#include "pch.h"
#include <vector>
#include <list>
#include "grade.h"
#include "Student_Info.h"
#include <ios> //for domain_error
#include <numeric> //accumulate
#include <algorithm>

double getAverage(const vector<double>& v) {
	return ::accumulate(v.begin(), v.end(), 0.0) / v.size();  //return Ÿ���� ���� *0.0
}

double grade(const double midterm, const  double final, const vector<double>& homeworks) {

    if (homeworks.size() == 0)
        throw domain_error("student has done no homework");

    return 0.4 * midterm  + 0.4 * final + 0.2 * getAverage(homeworks);
}

double grade(const Student_Info& student) {
    return grade(student._midterm, student._final, student._homework);
}


//grade��� ���� �̸��� �ٸ� ������Ÿ���� ���� �Լ��� ����.
//�Լ���ü�� ���ڷ� �Ѱ��� �� ������ ����� ���� ���� -> �����Լ��� �Ѱ��ְ� ���⿡�� �Ǻ��ϵ��� ��.
//�Լ� ������ ���� �����ϸ鼭, ���� ó���� �Բ� ����.
double grade_aux(const Student_Info& s) {

	try {
		return grade(s);
	}
	catch (domain_error) {
		//������ �ϳ��� ����.
		const vector<double> hw(1, 0.0);
		return grade(s._midterm, s._final, hw);
	}
}


//�л� ���� �з�
bool did_all_hw(const Student_Info& s) {
	return ::find(s._homework.begin(), s._homework.end(), 0.0) ==  s._homework.end();
}

double average_analysis(const vector<Student_Info>& students) {
	vector<double> grades;
	//transform(��������,������,���������ġ,�������Լ�)
	//���� ������ template�̹Ƿ� const�� ���ڷ� �Ѱ��ش�.
	::transform(students.begin(), students.end(), ::back_inserter(grades), grade_aux);
	return getAverage(grades);
}


//���� ���� �Ǻ� �߰�
bool fgrade(const Student_Info& student) {
	return grade(student) < 60;
}

bool pgrade(const Student_Info& student) {
	return !fgrade(student);
}


vector<Student_Info> bad_extract_fails(OUT vector<Student_Info>& students) {
	vector<Student_Info> fail;
	::remove_copy_if(students.begin(), students.end(), back_inserter(fail), pgrade);//�����ϰ� ���� �� ����
	students.erase(remove_if(students.begin(), students.end(), fgrade),students.end());
	/*remove�� ������ �����ؾ���.
	remove�� ���Ŵ� '������' �̴�.
	������ ������ ��ȯ�� it���Ŀ��� garbage���� ���̰� �ȴ�.
	�̸� erase�� ���� ���������� ��
	�̷��� �������� ������, 
	student���� ����� �л��鸸 ���Եȴ�.
	*/

	//�̹���� ���͸� 2�� ��ȯ�Ѵ�. (remove_if, remove_copy_if)
	return fail;
}

//���ġ �˰����� �̿��� �ѹ��� ��ȯ�ϵ��� ������ ���� (�� 2���̻� ����)
vector<Student_Info> extract_fails(vector<Student_Info>& students) {
	vector<Student_Info>::iterator iter = ::stable_partition(students.begin(), students.end(), pgrade);
	/*
	 partition : ��ҵ��� ī�װ��� �����Ͽ� ���ġ
	 stable_partition : ���װ� �ȿ��� ��� ������ �����ϸ鼭 ���ġ
	 return : �� ��° ī�װ��� ù��° ��Ҹ� ��Ÿ���� �ݺ��� ��ȯ.(fail ���ۺκ�)
	*/
	vector<Student_Info> fail(iter, students.end());
	students.erase(iter, students.end());
	return fail;
}


list<Student_Info> extract_fails(OUT list<Student_Info>& students) {
	list<Student_Info> fail;
	auto iter = students.begin();
	while (iter != students.end()) {
		if (fgrade(*iter)) {
			fail.push_back(*iter);
			iter = students.erase(iter);  
			
		}
		else
			++iter; 
	}
	return fail;
}
