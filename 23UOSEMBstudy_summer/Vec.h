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
	/*
	* begin, end
	* size =  (end-begin)으로 구현 
	* 
	*/

private:
	/*
	* 요소 저장 공간(동적 할당)
	* 데이터 시작(begin) 포인터, 끝 포인터(end)
	*/
};

