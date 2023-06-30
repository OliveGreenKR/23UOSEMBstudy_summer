#pragma once
#include "Vec.h"
#include <algorithm>
#include <iterator>  //back_inserter()
class Str {

	//��� ������ ���� ���� �ο�
	friend std::istream& operator>>(std::istream&, Str&);
	friend std::ostream& operator<<(std::ostream&, const Str&);

public:
	using size_type = Vec<char>::size_type;

	Str() { }
	Str(size_type n, char c) : _data(n, c) { }
	//c_str Ÿ���� �迭������ ��ü ����
	Str(const char* cp) {   
		std::copy(cp, cp+std::strlen(cp), std::back_inserter(_data));
	}
	//�ݺ��ڷ� ��ü ����
	template <class In> 
	Str(In b, In e) {
		std::copy(b, e, std::back_inserter(_data));
	}

public:
	size_type size() const { return _data.size(); }

private:
	Vec<char> _data;
};

//����� ������
std::istream& operator>>(std::istream&, Str&);
std::ostream& operator<<(std::ostream&, const Str&);