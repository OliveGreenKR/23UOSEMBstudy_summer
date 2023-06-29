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
	Vec(const Vec& v)/*복사생성자*/				{ create(v.begin(), v.end()); }
	explicit Vec(size_t n, const T& val = T())	{ create(n, val); }

	~Vec()										{ uncreate(); }

public:
	size_type size() const					{ return _avail - _data; } 

	T& operator[](size_type i)				{ return _data[i]; }
	const T& operator[](size_type i) const	{ return _data[i]; }

	//할당 연산자 - const 참조 타입 인수
	Vec& operator= (const Vec&);


	iterator begin()						{ return _data; }
	const_iterator begin() const			{ return _data; }

	iterator end()							{ return _avail; }
	const_iterator end() const				{ return _avail; }

	void push_back(const T& val) {
		if (_avail == _limit)
			grow(); //새로 공간 할당
		unchecked_append(val); //새로운 요소 추가
	}

private:
	void create();
	void create(size_t n, const T& val);
	void create(const_iterator begin, const_iterator right);

	void uncreate();

	void grow();
	void unchecked_append(const T& val);


private:
	iterator _data;	
	iterator _avail;
	iterator _limit;	

	allocator<T> _alloc;
};


/*
동적 배열 Vec을 만들기 위해서는
저장 공간이 동적으로 바뀔 수 있도록 하는 push_back 인터페이스가 필요하다.

앞으로 취할 push_back 전략은 다음과 같다.

0. 기본적으로 저장되어있는 데이터의 끝에 순차적으로 추가한다.
1. 공간이 부족하면 새로 할당, 이전 크기의 2배 만큼 할당한다.
2. 이후 이전 데이터를 옮기고, 이전 데이터의 메모리를 해제한다.
3. 새로 할당한 메모리에 새로운 값을 추가한다.

위와 같은 동작을 위해서는 저장하는 배열 범위를 파악하는 기존 방법을 바꾸어야함.
마지막을 나타내는 포인터가 2개가 되어야한다.
초기화 되지 않은 저장공간의 처음을 가리키는 포인터가 추가로 필요하다.

 [*][*][*][*][*][][][[][][][][][]
^_data          ^_avail          ^_limt

new-delete 방식은 기본적으로 문제가 있다.
사용하지 않을 공간까지 모두 초기화가 되어버린다.(자세한 내용은 Notion 참고)

따라서 메모리 할당을 위해 다른 방법을 사용할 것임. 
#include <memory> -> allocator<T> 클래스 사용.
-allocator<T>
	초기화 되지 않은 메모리 블럭을 할당하고, 블럭의 첫 번째 요소를 가리키는 포인터 반환.

*/