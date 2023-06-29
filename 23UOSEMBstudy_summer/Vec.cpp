#include "pch.h"
#include "Vec.h"

template<class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs) {
	//자가할당 여부 확인
	if (&rhs != this) {
		uncreate(); //좌변 메모리 해제

		create(rhs.begin(), rhs.end()); // 우변이 지닌 요소를 좌변으로 복사.
	}
	return *this; //좌변의 객체의 참조를 리턴
}
