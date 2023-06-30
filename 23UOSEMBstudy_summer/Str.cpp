#include "pch.h"
#include "Str.h"
#include <iostream>
#include <ios>

std::istream& operator>>(std::istream& is, Str& s) {
	
	s._data.clear();  //clear ����
	char c;

	while (is.get(c) && isspace(c));

	if (is) {
		do s._data.push_back(c);
		while (is.get(c) && !isspace(c));

		if (is) //�ٽ� ���� ����
			is.unget(); //�Է� ��Ʈ�� �ǵ�����(���� �ϳ���ŭ ����)
	}

	return is;
}

std::ostream& operator<<(std::ostream& os , const Str& s) {
	for (auto c : s._data) //vec�� begin�� ����� ��������
		os << c;
	return os;
}
