#include "pch.h"
#include "Str.h"
#include <iostream>
#include <ios>

std::istream& operator>>(std::istream& is, Str& s) {
	
	s._data.clear();  //clear 구현
	char c;

	while (is.get(c) && isspace(c));

	if (is) {
		do s._data.push_back(c);
		while (is.get(c) && !isspace(c));

		if (is) //다시 공백 읽음
			is.unget(); //입력 스트림 되돌리기(문자 하나만큼 역행)
	}

	return is;
}

std::ostream& operator<<(std::ostream& os , const Str& s) {
	for (auto c : s._data) //vec의 begin을 사용해 구현가능
		os << c;
	return os;
}
