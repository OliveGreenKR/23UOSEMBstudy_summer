#pragma once
#include "Student_Info.h"
/*
* generic handle class 'Handle'
* 
* Handle은 객체를 참조하는 값이다.
* 복사할 수 있다.
* 다른 객체에 바인딩되어 있는지 여부를 확인할 수 있다.
* 상속 계층 구조에 속한 클래스를 가리키면, 이 객체를 사용하여 다형성 동작을 실행하게 만들 수 있다.
* (가상함수를 호출 할때, 실제 포인터를 통해 호출한 것처럼 동작해야한다.)
* 
* 위의 특성을 구현하여 기본 포인터가 가지는 문제점을 해결할 것이다.
* 
* -복사 시 바인딩된 객체의 복사본을 만들고 이를 가리키게 한다.
* -소멸 시 바인딩된 객체 또한 소멸시킨다.
* -바인딩 되지 않은 Handle객체를 이용해서 참조객체에 접근하려고 하면 예외 발생시킨다.
* -위의 상황을 피할 수 있도록 프로그래머가 사용전에 확인할 수 있는 방법을 제시할 것이다.
*/

template <class T>
class Handle {
public:
	 Handle() { }
	 Handle(const Handle& s) {
		 if (s._p)
			 _p = s._p->clone();
	 }
	 Handle& operator=(const Handle&);

	 ~Handle() { delete _p; }

	 Handle(T* t)  : _p(t){ }

	 operator bool() const { return (_p != nullptr); }
	 T& operator*() const;
	 T* operator->() const;

private:
	T* _p = nullptr;
};

template<class T>
Handle<T>& Handle<T>::operator=(const Handle& rhs) {
	if (&rhs != this) {
		delete _p;
		_p =  rhs._p ? rhs._p -> clone() : nullptr ;
	}
	return *this;
}

template<class T>
T& Handle<T>::operator*() const {
	if(_p)
		return *_p;

	throw runtime_error("unbound Handle");
}

template<class T>
T* Handle<T>::operator->() const {
	if(_p)
		return _p;

	throw runtime_error("unbound Handle");
}
