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
Handle Ŭ������ ��ü�� �����ϰų� �Ҵ��� ��, �ʿ����� ���� ��Ȳ������
���� �����͸� �����Ѵ�.(�׻� ���ε��� ��ü�� �����ϴ� ������ �����ϱ� ����)

������ ���纻�� ���� ������ ������ �� �־���Ѵ�. 
��ü�� ���纻�� ���� ���� ������ ������ �ʿ䵵 ���� ���� �ֱ� ����.

���� ���� ��ü�� �������� �ʴ� ���·� handle ��ü�� �����Ѵٸ�?
���� ���� ��ü�� �ټ��� Hanldle��ü�� ���ε� �� �� �ִ�.

�̶�, �ϳ��� handle��ü�� �Ҹ�Ǹ�? ������ Handle�� ���� ������ �޸𸮸� ������ ���°� �ȴ�.
(delete�� �����Ϳ� ����)
�� ������ �ذ��ϱ� ���� ����ϴ� ���
>> ���� ī��� (reference count)

���� ī��Ʈ�� �����ϴ� ��� 
���� ī��Ʈ�� ��ü�� Ÿ�԰��� ���������� �����ؾ��Ѵ�
-> ���� ī��Ʈ�� �ش� handler�� ����Ű�� ��ü�� Ŭ���� Ÿ�Կ� ���� �߰��� ���� ����.
-> ������ �����͸� �߰��Ͽ� ����.
=> handler�� ����Ű�� ���� ��ü�� ������ ���� ī��Ʈ�� ����Ͽ� ���纻 ������ �ľ�.
*/