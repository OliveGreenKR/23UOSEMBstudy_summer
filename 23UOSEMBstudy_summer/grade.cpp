#include "pch.h"
#include <vector>
#include <list>
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
list<Student_Info> extract_fails_and_return(OUT list<Student_Info>& students) {
	list<Student_Info> fail;
	auto iter = students.begin();
	while (iter != students.end()) {
		if (fgrade(*iter)) {
			fail.push_back(*iter);
			iter = students.erase(iter);  //**  erase������ ���� iter�� ��ȯ ���ش�.
			// enditer���� ��ȯ���� �� ������ ���� ���ؾ��Ѵ�. �̸� �������� ����.
		}
		else
			++iter; //pre++�� ���� ����
	}
	return fail;
}
//�޸� ������ �ʹ� ���� ����Ѵ�. �׷��ٰ� �߰��߰� �����ϴ� ���� vector�� ���ۿ� ��︮�� �ʰ� ��ȿ�����̴�.
//���ʹ� erase �޼ҵ带 ������ ������, �ſ� ��ȿ����. ���ʹ� �ε����� ���� ���ٰ�, �� ���� ������ �߰� �� ������ ���� �̻����̴�.
//list ����غ���?
//list�� �߰� ���� �� �������� �ڷᱸ���� �������� �ʴ´�.
//��, list�� ������ ���� �޼ҵ带 ����ؾ���. 
// list.sort(pred)
