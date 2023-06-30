#pragma once
#include "Vec.h"
#include <algorithm>
#include <iterator>  //back_inserter()
class Str {

	//멤버 변수에 접근 권한 부여
	friend std::istream& operator>>(std::istream&, Str&);
	friend std::ostream& operator<<(std::ostream&, const Str&);

public:
	using size_type = Vec<char>::size_type;

	Str() { }
	Str(size_type n, char c) : _data(n, c) { }
	//c_str 타입의 배열에서도 객체 생성
	Str(const char* cp) {   
		std::copy(cp, cp+std::strlen(cp), std::back_inserter(_data));
	}
	//반복자로 객체 생성
	template <class In> 
	Str(In b, In e) {
		std::copy(b, e, std::back_inserter(_data));
	}

public:
	char& operator[](size_type i) { return _data[i]; }
	const char& operator[](size_type i) const { return _data[i]; }
	Str& operator+= (const Str& s) {
		std::copy(s._data.begin(), s._data.end(), std::back_inserter(_data));
		return *this;
	}

	size_type size() const { return _data.size(); }


private:
	Vec<char> _data;
};

//입출력 연산자
std::istream& operator>>(std::istream&, Str&);
std::ostream& operator<<(std::ostream&, const Str&);
Str operator+ (const Str& s, const Str& t);