#pragma once
#include "Vec.h"
#include <algorithm>
#include <iterator>  //back_inserter()
#include "Handle.h"
class Str {

	//��� ������ ���� ���� �ο�
	friend std::istream& operator>>(std::istream&, Str&);
	friend std::ostream& operator<<(std::ostream&, const Str&);

public:
	using size_type = Vec<char>::size_type;

	Str() : _data(new Vec<char>) { }
	Str(size_type n, char c) : _data(new Vec<char>(n,c)) { }
	//c_str Ÿ���� �迭������ ��ü ����
	Str(const char* cp) :  _data(new Vec<char>) {   
		std::copy(cp, cp+std::strlen(cp), std::back_inserter(*_data));
	}
	//�ݺ��ڷ� ��ü ����
	template <class In> 
	Str(In b, In e) {
		std::copy(b, e, std::back_inserter(*_data));
	}

public:
	char& operator[](size_type i) { 
		_data.make_unique();
		return (*_data)[i]; 
	}
	const char& operator[](size_type i) const { return (*_data)[i]; }
	Str& operator+= (const Str& s) {
		_data.make_unique();
		std::copy(s._data->begin(), s._data->end(), std::back_inserter(*_data));
		return *this;
	}

	size_type size() const { return _data->size(); }


private:
	Ptr<Vec<char>> _data;
};

//����� ������
std::istream& operator>>(std::istream&, Str&);
std::ostream& operator<<(std::ostream&, const Str&);
Str operator+ (const Str& s, const Str& t);


/*
���� Ŭ������ ���� �����ұ�? �ѹ� �����غ���
*/