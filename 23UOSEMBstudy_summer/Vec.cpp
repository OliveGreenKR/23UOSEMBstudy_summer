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

template<class T>
void Vec<T>::create() {
	_data = _avail = _limit = nullptr;
}

template<class T>
void Vec<T>::create(size_type n , const T& val) {
	_data = _alloc.allocate(n);
	_limit = _avail = _data + n;
	::uninitialized_fill(_data, _avail, val); //[data,_avail) val로 초기화
}

template<class T>
void Vec<T>::create(const_iterator i, const_iterator j ) {
	_data = _alloc.allocate(j-1);
	_limit = _avail = ::uninitialized_copy(i, j, _data); 
	//[i,j)를 _dat에 초기화 한후 마지막 요소의 다음을 가리키는 포인터 반환
}

template<class T>
void Vec<T>::uncreate() {
	if (_data != nullptr) {
		//역순으로 소멸
		iterator it = _avail;
		while (it != _data)
			_alloc.destroy(--it);

		//저장공간 반환
		_alloc.deallocate(_data, _limit - _data);
	}

	_data = _limit = _avail = nullptr;
}

template<class T>
void Vec<T>::grow() {
	//현재 2배의 공간 할당.
	size_type new_size = max(2*(_limit - _data), ptrdiff_t(1));

	//새로운 곳으로 복사
	iterator new_data = _alloc.allocate(new_size);
	iterator new_avail = ::uninitialized_copy(_data, _avail, new_data);
	//기존 반환
	uncreate();
	//포인터 재설정
	_data = new_data;
	_avail = new_avail;
	_limit = _data + new_size;
}

template<class T>
void Vec<T>::unchecked_append(const T& val) {
	_alloc.construct(_avail++, val); //초기화 되어있지않은 공간에 객체 생성.
}
