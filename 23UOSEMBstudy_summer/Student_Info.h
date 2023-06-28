#pragma once
#include <iostream>
#include <string>
#include <vector>

class Student_Info {
public: //인터페이스
	std::istream& read(std::istream&);
	double grade() const;  //const  : 해당 함수의 호출은 Student_Info의 정보를 바꾸지 않을 것이다.

	//accessor funtion (getter라고도 함)
	std::string name() const { return _name; }

	/*name만 accessor를 인터페이스(public)로서 허용한 이유:
	*  해당 클래스의 추상화는 1.학생 2. 학생의 최종 점수  이다.
	* 따라서 이름만 허용하고 점수는 은닉화를 유지하는 것이 좋은 선택.
	*/

private:
	string _name;
	double _midterm = 0.0;
	double _final = 0.0;
	vector<double> _homework = vector<double>(0.);
};
