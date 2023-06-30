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
Str s("hi");

Str t = "hello";
s = "hello";

위의 두 연산은
1. const Str&의 복사 생성자 로 t 초기화
2. 할당 연산자 =을 이용한 할당. 인수는 const char* 이다.
을 사용한다.
2번을 위해서는 기본 할당 연산자가 아닌 추가적인 할당 연산자와 복사 생성자를 오버로드 할 필요가 있어보인다.
다행히 생성자는 이미 존재한다. 또한 해당 생성자는 '사용자 정의 변환'(user-defined conversion)의 역할을 맡는다.
(const char* -> Str)
그렇다면 컴파일러는 2번 연산에서 다음과 같은 동작을 하게 된다.

1. 생성자를 이용해 일시적 Str 객체 생성.
2. Str의 기본 할당 연산을 이용해서 s 에 일시적 객체의 값을 할당.

따라서 위의 1,2 연산을 정상 동작함.
*/