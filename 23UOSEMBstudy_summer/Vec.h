#pragma once

/*
1. 클래스가 가져야할 인터페이스를 명시하기

	- 백터 생성
		ㄴ 빈 벡터 생성
		ㄴ 벡터의 크기를 지정하여 생성

	- 벡터가 사용하는 타입을 관리
		ㄴ iterator 사용

	- 인덱스 연산자를 이용해 각 요소 접근
		ㄴ size 알아내기
		ㄴ 인덱스 연산자 오버로딩

	- 표준 라이브러리 알고리즘, 어댑터 사용 어느 정도 가능
		ㄴ begin iterator
		ㄴ end iterator
*/


template <class T> 
class Vec {
public:
	using iterator = T*;
	using cosnt_iterator = const T*;
	using size_type = size_t;
	using value_type = T;
	using difference_type = signed int;
	using reference = T&;
	using const_reference = const T&;

	Vec() { create(); }
	explicit Vec(size_t n, const T& val = T()) { create(n, val); }

private:


private:
	T* _data;	// data pointer
	T* _limit;	// end pointer
};

//표준 템플릿 클래스의 규범에 따르면 프로그래머가 사용할 수 있는 타입 이름을 제공하되 자세한 구현은 숨겨야한다.