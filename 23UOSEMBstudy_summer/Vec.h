#pragma once

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

	Vec() { create(); }
	explicit Vec(size_t n, const T& val = T()) { create(n, val); }

public:
	size_type size() const					{ return _limit - _data; }
	T& operator[](size_type i)				{ return _data[i]; }
	const T& operator[](size_type i) const	{ return _data[i]; }

	iterator begin()						{ return _data; }
	const_iterator begin() const			{ return _data; }

	iterator end()							{ return _end; }
	const_iterator end() const				{ return _end; }

private:
	void create();
	void create(size_t n, const T& val);


private:
	iterator _data;	
	iterator _limit;	
};

/* operator overloading
* 기본적으로 인수 개수에 따라 피연산자 개수가 달라지며, 첫 번째가 왼쪽, 두번째가 오른쪽 피연산자이다.
* 
* -멤버로 오버로딩 :  자동으로 왼쪽 피연산자는 클래스 객체가 된다.
*/