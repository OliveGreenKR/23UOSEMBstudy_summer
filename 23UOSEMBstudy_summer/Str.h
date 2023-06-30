#pragma once
#include "Vec.h"
#include <algorithm>
#include <iterator>  //back_inserter()
class Str {
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

private:
	Vec<char> _data;
};

/*
Str클래스에는 복사 생성자, 할당 연산자, 소멸자를 정의 하지 않았다.

>> 기본값으로 동작하기 때문, 해당 클래스 자체는 메모리 할당을 하지 않는다.(소멸자가 필요없다)
메모리 관리는 Vec 클래스에게 맡긴다.

이처럼 일반적으로 소멸자가 필요없는 클래스는, 
명시적인 복사 생성자나 할당 연산자를 추가로 필요로 하지 않는다.
*/