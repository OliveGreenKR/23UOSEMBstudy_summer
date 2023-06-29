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
확립된 class invariant
1. _data는 첫 번째 데이터 요소를 가리키며, 존재하지 않는다면 data는 nullptr이다.
2. _data <= _avail <= _limit
3. 요소들은 [_data,_avail) 안에 생성됨,
4. 요소들은 [_avial,_limit)안에 생성되지 않음.
*/