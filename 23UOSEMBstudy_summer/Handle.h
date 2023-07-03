#pragma once
#include <stdexcept>
//Memory Handler
template <class T>
class Ptr {

public:
	//���ǿ� ���� ��ü�� �����ϴ� ���ο� ��� �Լ� �߰�
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
	//���� ���� ī��Ʈ ���
	++*rhs._refPtr;
	//���� ���� ī��Ʈ ����
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
������ Ptr�� �������غ���.

Ptr�� ����ؼ� Str�� �ٽ� �����Ѵٸ�?

StrŬ������ �̹� �����ϴ� ��ü 2���� �����Ͽ� ���ο� ��ü�� ������� 
�Ϲ������� ���� ���ڸ� �����Ѵ�.

�̷��� ���縦 ���̰� �; ����� ���� ī��Ʈ�� �����ϰ� �ʹٰ� �Ѵٸ�?

*/