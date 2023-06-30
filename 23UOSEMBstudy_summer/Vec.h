#pragma once
#include <memory>
template <class T> 
class Vec {
public:
	using iterator = T*;
	using const_iterator = const T*;
	using size_type = size_t;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using reference = T&;
	using const_reference = const T&;

	Vec()										{ create(); }
	Vec(const Vec& v)/*���������*/				{ create(v.begin(), v.end()); }
	explicit Vec(size_t n, const T& val = T())	{ create(n, val); }

	~Vec()										{ uncreate(); }

public:
	size_type size() const					{ return _avail - _data; } 
	void clear();

	T& operator[](size_type i)				{ return _data[i]; }
	const T& operator[](size_type i) const	{ return _data[i]; }

	//�Ҵ� ������ - const ���� Ÿ�� �μ�
	Vec& operator= (const Vec&);


	iterator begin()						{ return _data; }
	const_iterator begin() const			{ return _data; }

	iterator end()							{ return _avail; }
	const_iterator end() const				{ return _avail; }

	void push_back(const T& val) {
		if (_avail == _limit)
			grow(); //���� ���� �Ҵ�
		unchecked_append(val); //���ο� ��� �߰�
	}

private:
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	void uncreate();

	void grow();
	void unchecked_append(const T& val);


private:
	iterator _data =  nullptr;	
	iterator _avail =  nullptr;
	iterator _limit=  nullptr;	

	allocator<T> _alloc;
};


template<class T>
void Vec<T>::clear() {
	if (_data != nullptr) {
		_avail = _data = nullptr;
	}
}

template<class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs) {
	//�ڰ��Ҵ� ���� Ȯ��
	if (&rhs != this) {
		uncreate(); //�º� �޸� ����

		create(rhs.begin(), rhs.end()); // �캯�� ���� ��Ҹ� �º����� ����.
	}
	return *this; //�º��� ��ü�� ������ ����
}

template<class T>
void Vec<T>::create() {
	_data = _avail = _limit = nullptr;
}

template<class T>
void Vec<T>::create(size_type n, const T& val) {
	_data = _alloc.allocate(n);
	_limit = _avail = _data + n;
	::uninitialized_fill(_data, _avail, val); //[data,_avail) val�� �ʱ�ȭ
}

template<class T>
void Vec<T>::create(const_iterator i, const_iterator j) {
	_data = _alloc.allocate(j-1);
	_limit = _avail = ::uninitialized_copy(i, j, _data);
	//[i,j)�� _dat�� �ʱ�ȭ ���� ������ ����� ������ ����Ű�� ������ ��ȯ
}

template<class T>
void Vec<T>::uncreate() {
	if (_data != nullptr) {
		//�������� �Ҹ�
		iterator it = _avail;
		while (it != _data)
			_alloc.destroy(--it);

		//������� ��ȯ
		_alloc.deallocate(_data, _limit - _data);
	}

	_data = _limit = _avail = nullptr;
}

template<class T>
void Vec<T>::grow() {
	//���� 2���� ���� �Ҵ�.
	size_type new_size = max(2*(_limit - _data), ptrdiff_t(1));

	//���ο� ������ ����
	iterator new_data = _alloc.allocate(new_size);
	iterator new_avail = ::uninitialized_copy(_data, _avail, new_data);
	//���� ��ȯ
	uncreate();
	//������ �缳��
	_data = new_data;
	_avail = new_avail;
	_limit = _data + new_size;
}

template<class T>
void Vec<T>::unchecked_append(const T& val) {
	_alloc.construct(_avail++, val); //�ʱ�ȭ �Ǿ��������� ������ ��ü ����.
}

/*
Ȯ���� class invariant
1. _data�� ù ��° ������ ��Ҹ� ����Ű��, �������� �ʴ´ٸ� data�� nullptr�̴�.
2. _data <= _avail <= _limit
3. ��ҵ��� [_data,_avail) �ȿ� ������,
4. ��ҵ��� [_avial,_limit)�ȿ� �������� ����.
*/