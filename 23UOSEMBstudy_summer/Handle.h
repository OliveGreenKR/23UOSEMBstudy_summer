#pragma once
#include <stdexcept>
//Memory Handler
template <class T>
class Ptr {

public:
	//조건에 따라 객체를 복사하는 새로운 멤버 함수 추가
	void make_unique() {
		if (*_refPtr != 1) {
			--* _refPtr;
			_refPtr = new size_t(1);
			_p = _p ? _p->clone() : nullptr;
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

Ptr을 사용해서 Str을 다시 구현한다면?

Str클래스는 이미 존재하는 객체 2개를 결합하여 새로운 객체를 만들려고 
암묵적으로 여러 문자를 복사한다.

이러한 복사를 줄이고 싶어서 당신은 참조 카운트를 적용하고 싶다고 한다면?

*/