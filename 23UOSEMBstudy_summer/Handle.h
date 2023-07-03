#pragma once

//Memory Handler
template <class T>
class Ref_Handle {
public:
	Ref_Handle() { }
	Ref_Handle(const Ref_Handle& h) : _p(h._p), _refPtr(h._refPtr) {
		++* _refPtr;
	}
	Ref_Handle& operator=(const Ref_Handle&);

	~Ref_Handle() {
		if (--*_refPtr == 0) {
			delete _refPtr;
			delete _p;
		}
	}

	Ref_Handle(T* t) : _p(t) { }

	operator bool() const { return (_p != nullptr); }
	T& operator*() const;
	T* operator->() const;

private:
	T* _p = nullptr;
	std::size_t* _refPtr =  new size_t(1);
};

template<class T>
Ref_Handle<T>& Ref_Handle<T>::operator=(const Ref_Handle<T>& rhs) {
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
T& Ref_Handle<T>::operator*() const {
	if (_p)
		return *_p;

	throw runtime_error("unbound Handle");
}

template<class T>
T* Ref_Handle<T>::operator->() const {
	if (_p)
		return _p;

	throw runtime_error("unbound Handle");
}

/*
Handle 클래스는 객체를 복사하거나 할당할 때, 필요하지 않은 상황에서도
기저 데이터를 복사한다.(항상 바인딩된 객체를 복사하는 것으로 동작하기 때문)

보통은 복사본은 만들 것인지 선택할 수 있어야한다. 
객체의 복사본이 같은 기저 정보를 공유할 필요도 있을 수도 있기 때문.

만약 기저 객체를 복사하지 않는 형태로 handle 객체를 복사한다면?
같은 기저 개체에 다수의 Hanldle객체가 바인딩 될 수 있다.

이때, 하나의 handle객체가 소멸되면? 나머지 Handle은 아주 위험한 메모리를 참조한 형태가 된다.
(delete한 포인터에 접근)
이 문제를 해결하기 위해 사용하는 방법
>> 참조 카운드 (reference count)

참조 카운트를 관리하는 방법 
참조 카운트는 객체의 타입과는 독립적으로 동작해야한다
-> 참조 카운트를 해당 handler가 가리키는 객체의 클래스 타입에 직접 추가할 수는 없음.
-> 별도의 포인터를 추가하여 관리.
=> handler가 가리키는 기저 객체는 저마다 참조 카운트를 사용하여 복사본 개수를 파악.
*/