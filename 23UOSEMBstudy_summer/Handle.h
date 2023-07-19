#pragma once
#include <stdexcept>
template <class T>
T* clone(const T* tp) {
	return tp->clone();
}

//Memory Handler
template <class T>
class Ptr {

public:
	//조건에 따라 객체를 복사하는 새로운 멤버 함수 추가
	void make_unique() {
		if (*_refPtr != 1) {
			--* _refPtr;
			_refPtr = new size_t(1);
			_p = _p ? ::clone(_p) : nullptr;
		}
	}

public:
	Ptr() { }
	Ptr(const Ptr& h) : _p(h._p), _refPtr(h._refPtr) {
		++* _refPtr;
	}
	Ptr& operator=(const Ptr&);

	~Ptr() {
		if (--*_refPtr == 0) {
			delete _refPtr;
			delete _p;
		}
	}

	Ptr(T* t) : _p(t) { }

	operator bool() const { return (_p != nullptr); }
	T& operator*() const;
	T* operator->() const;

private:
	T* _p = nullptr;
	std::size_t* _refPtr =  new size_t(1);
};

template<class T>
Ptr<T>& Ptr<T>::operator=(const Ptr<T>& rhs) {
	//우항 참조 카운트 상승
	++*rhs._refPtr;
	//좌항 참조 카운트 감소
	if (--*_refPtr == 0) {
		delete _refPtr;
		delete _p;
	}

	_refPtr = rhs._refPtr;
	_p = rhs._p;

	return *this;
}

template<class T>
T& Ptr<T>::operator*() const {
	if (_p)
		return *_p;

	throw runtime_error("unbound Handle");
}

template<class T>
T* Ptr<T>::operator->() const {
	if (_p)
		return _p;

	throw runtime_error("unbound Handle");
}

/*
현재의 Ptr을 더욱개선해보자.

make_unique에서 _p->clone() 을 호출한다.

따라서 현재의 Ptr 클래스를 사용하기 위해서는 바인딩된 모든 클래스가
clone()을 멤버로 가지고 있어야한다. 그러나 Ptr에서는 Vec의 정의문을 바꿀 수 없다.

그렇다면 간접 접근 단계를 통해 해결해보자.

clone을 멤버함수가 아닌, 제네릭 전역 함수로 정의한다면?
필요한 타입에는 재정의를 하여 문제를 보완할 할 수 있다.( 템플릿 전문화 )

*/