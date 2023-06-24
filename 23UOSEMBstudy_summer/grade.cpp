#include "pch.h"
#include <vector>
#include "grade.h"
#include "Student_Info.h"
#include <ios> //for domain_error

template <typename T = double>
auto GetAvgFromVec = [ ](const vector<T>& vec) {  //lamda
	T sum = 0;
	for (auto& e : vec)
		sum += e;
	return  sum / vec.size();
};


double grade(double midterm, double final, vector<double>& homeworks) {

    if (homeworks.size() == 0)
        throw domain_error("student has done no homework");

    return 0.4 * midterm  + 0.4 * final + 0.2 * GetAvgFromVec<double>(homeworks);
}

double grade(Student_Info& student) {
    return grade(student.midterm, student.final, student.hw);
}


//���� ���� �Ǻ� �߰�
bool fgrade(Student_Info& student) {
	return grade(student) < 60;
}

//���� �л��鿡�Լ� ���� �л����� �����ϰ�, ���� �л����� ��ȯ
vector<Student_Info> extract_fails_and_return(OUT vector<Student_Info>& students) {
	vector<Student_Info> pass, fail;
	for (auto& s : students) {
		if (fgrade(s))
			fail.push_back(s);
		else
			pass.push_back(s);
	}
	students = pass;
	return fail;
}
