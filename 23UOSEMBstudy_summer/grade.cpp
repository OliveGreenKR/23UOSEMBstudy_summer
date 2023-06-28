#include "pch.h"
#include <vector>
#include <list>
#include "grade.h"
#include "Student_Info.h"
#include <ios> //for domain_error
#include <numeric> //accumulate
#include <algorithm>

double getAverage(const vector<double>& v) {
	return ::accumulate(v.begin(), v.end(), 0.0) / v.size();  //return 타입을 위해 *0.0
}

double grade(const double midterm, const  double final, const vector<double>& homeworks) {

    if (homeworks.size() == 0)
        throw domain_error("student has done no homework");

    return 0.4 * midterm  + 0.4 * final + 0.2 * getAverage(homeworks);
}

double grade(const Student_Info& student) {
    return grade(student._midterm, student._final, student._homework);
}


//grade라는 같은 이름의 다른 프로토타입을 가진 함수가 많다.
//함수객체를 인자로 넘겨줄 때 구분할 방법이 현재 없음 -> 보조함수를 넘겨주고 여기에서 판별하도록 함.
//함수 버전을 쉽게 관리하면서, 예외 처리도 함께 가능.
double grade_aux(const Student_Info& s) {

	try {
		return grade(s);
	}
	catch (domain_error) {
		//과제를 하나도 안함.
		const vector<double> hw(1, 0.0);
		return grade(s._midterm, s._final, hw);
	}
}


//학생 상태 분류
bool did_all_hw(const Student_Info& s) {
	return ::find(s._homework.begin(), s._homework.end(), 0.0) ==  s._homework.end();
}

double average_analysis(const vector<Student_Info>& students) {
	vector<double> grades;
	//transform(범위시작,범위끝,결과저장위치,실행할함수)
	//단항 연산자 template이므로 const를 인자로 넘겨준다.
	::transform(students.begin(), students.end(), ::back_inserter(grades), grade_aux);
	return getAverage(grades);
}


//낙제 여부 판별 추가
bool fgrade(const Student_Info& student) {
	return grade(student) < 60;
}

bool pgrade(const Student_Info& student) {
	return !fgrade(student);
}


vector<Student_Info> bad_extract_fails(OUT vector<Student_Info>& students) {
	vector<Student_Info> fail;
	::remove_copy_if(students.begin(), students.end(), back_inserter(fail), pgrade);//제거하고 남은 값 복사
	students.erase(remove_if(students.begin(), students.end(), fgrade),students.end());
	/*remove의 동작을 이해해야함.
	remove의 제거는 '덮어씌우기' 이다.
	동작이 끝나면 반환한 it이후에는 garbage값이 쌓이게 된다.
	이를 erase를 통해 지워버리는 것
	이렇게 지우기까지 끝나면, 
	student에는 통과한 학생들만 남게된다.
	*/

	//이방법은 벡터를 2번 순환한다. (remove_if, remove_copy_if)
	return fail;
}

//재배치 알고리즘을 이용해 한번만 순환하도록 수정한 버전 (약 2배이상 빠름)
vector<Student_Info> extract_fails(vector<Student_Info>& students) {
	vector<Student_Info>::iterator iter = ::stable_partition(students.begin(), students.end(), pgrade);
	/*
	 partition : 요소들을 카테고리로 구분하여 재배치
	 stable_partition : 각테고리 안에서 요소 순서를 유지하면서 재배치
	 return : 두 번째 카테고리의 첫번째 요소를 나타내는 반복자 반환.(fail 시작부분)
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
