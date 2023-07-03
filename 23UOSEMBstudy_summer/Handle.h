#pragma once
#include "Student_Info.h"
/*
* generic handle class 'Handle'
* 
* Handle�� ��ü�� �����ϴ� ���̴�.
* ������ �� �ִ�.
* �ٸ� ��ü�� ���ε��Ǿ� �ִ��� ���θ� Ȯ���� �� �ִ�.
* ��� ���� ������ ���� Ŭ������ ����Ű��, �� ��ü�� ����Ͽ� ������ ������ �����ϰ� ���� �� �ִ�.
* (�����Լ��� ȣ�� �Ҷ�, ���� �����͸� ���� ȣ���� ��ó�� �����ؾ��Ѵ�.)
* 
* ���� Ư���� �����Ͽ� �⺻ �����Ͱ� ������ �������� �ذ��� ���̴�.
* 
* -���� �� ���ε��� ��ü�� ���纻�� ����� �̸� ����Ű�� �Ѵ�.
* -�Ҹ� �� ���ε��� ��ü ���� �Ҹ��Ų��.
* -���ε� ���� ���� Handle��ü�� �̿��ؼ� ������ü�� �����Ϸ��� �ϸ� ���� �߻���Ų��.
* -���� ��Ȳ�� ���� �� �ֵ��� ���α׷��Ӱ� ������� Ȯ���� �� �ִ� ����� ������ ���̴�.
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
