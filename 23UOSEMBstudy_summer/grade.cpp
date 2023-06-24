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


//낙제 여부 판별 추가
bool fgrade(Student_Info& student) {
	return grade(student) < 60;
}

//기존 학생들에게서 낙제 학생들을 제거하고, 낙제 학생들을 반환
list<Student_Info> extract_fails_and_return(OUT list<Student_Info>& students) {
	list<Student_Info> fail;
	auto iter = students.begin();
	while (iter != students.end()) {
		if (fgrade(*iter)) {
			fail.push_back(*iter);
			iter = students.erase(iter);  //**  erase된후의 다음 iter를 반환 해준다.
			// enditer역시 순환문을 돌 때마다 값을 구해야한다. 미리 저장하지 말기.
		}
		else
			++iter; //pre++가 좀더 빠름
	}
	return fail;
}
//메모리 공간을 너무 많이 사용한다. 그렇다고 중간중간 삭제하는 것은 vector의 동작에 어울리지 않고 비효율적이다.
//벡터는 erase 메소드를 제공은 하지만, 매우 비효율적. 벡터는 인덱스를 통한 접근과, 맨 끝의 원소의 추가 및 삭제가 가장 이상적이다.
//list 사용해볼까?
//list는 중간 삽입 및 삭제에도 자료구조가 무너지지 않는다.
//단, list의 정렬은 내부 메소드를 사용해야함. 
// list.sort(pred)
