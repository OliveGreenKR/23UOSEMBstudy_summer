#pragma once

template <class T> 
class Vec {
public:
	using iterator = T*;
	using cosnt_iterator = const T*;
	using size_type = size_t;
	using value_type = T;
	using difference_type = signed int;
	using reference = T&;
	using const_reference = const T&;

	Vec() { create(); }
	explicit Vec(size_t n, const T& val = T()) { create(n, val); }

public:
	size_type size() const					{ return _limit - _data; }
	T& operator[](size_type i)				{ return _data[i]; }
	const T& operator[](size_type i) const	{ return _data[i]; }

private:
	void create();
	void create(size_t n, const T& val);


private:
	iterator _data;	
	iterator _limit;	
};

/* operator overloading
* �⺻������ �μ� ������ ���� �ǿ����� ������ �޶�����, ù ��°�� ����, �ι�°�� ������ �ǿ������̴�.
* 
* -����� �����ε� :  �ڵ����� ���� �ǿ����ڴ� Ŭ���� ��ü�� �ȴ�.
*/