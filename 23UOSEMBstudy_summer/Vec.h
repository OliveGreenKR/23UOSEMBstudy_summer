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

	Vec()										{ create(); }
	Vec(const Vec& v)							{ create(v.begin(), v.end()); }
	explicit Vec(size_t n, const T& val = T())	{ create(n, val); }

public:
	size_type size() const					{ return _limit - _data; }

	T& operator[](size_type i)				{ return _data[i]; }
	const T& operator[](size_type i) const	{ return _data[i]; }

	//할당 연산자 - const 참조 타입 인수
	Vec& operator= (const Vec&);


	iterator begin()						{ return _data; }
	const_iterator begin() const			{ return _data; }

	iterator end()							{ return _limit; }
	const_iterator end() const				{ return _limit; }

private:
	void create();
	void create(size_t n, const T& val);
	void create(iterator begin, iterator right);

	void uncreate();


private:
	iterator _data;	
	iterator _limit;	
};

/* 할당 연산자 (assignment operator)
* opertaor= 할당 연산자
* 클래스 자체의 const_reference 타입의 할당 연산자는 특별하다!
* 
* 클래스 타입의 값을 할당하는 것이 무엇을 의미하는지 정의하기 때문.
* 
* header내의 template 공간 안에서는 편의성을 위해 '<T>'를 생략해도 되지만, 외부에서 정의를하는 cpp에서는 꼭 명시해주어야한다.
* 하지만 cpp 에서도 한 함수에서 한번 <T>를 명시하면, 암묵적으로 <T>인 객체로 인정되어 생략가능.
*/

