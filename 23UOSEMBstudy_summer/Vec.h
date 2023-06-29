#pragma once
#include <memory>
template <class T> 
class Vec {
public:
	using iterator = T*;
	using const_iterator = const T*;
	using size_type = size_t;
	using value_type = T;
	using difference_type = signed int;
	using reference = T&;
	using const_reference = const T&;

	Vec()										{ create(); }
	Vec(const Vec& v)/*���������*/				{ create(v.begin(), v.end()); }
	explicit Vec(size_t n, const T& val = T())	{ create(n, val); }

	~Vec()										{ uncreate(); }

public:
	size_type size() const					{ return _avail - _data; } 

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
	iterator _avai =  nullptr;
	iterator _limit=  nullptr;	

	allocator<T> _alloc;
};


/*
Ȯ���� class invariant
1. _data�� ù ��° ������ ��Ҹ� ����Ű��, �������� �ʴ´ٸ� data�� nullptr�̴�.
2. _data <= _avail <= _limit
3. ��ҵ��� [_data,_avail) �ȿ� ������,
4. ��ҵ��� [_avial,_limit)�ȿ� �������� ����.
*/