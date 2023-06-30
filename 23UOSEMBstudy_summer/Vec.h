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
	Vec(const Vec& v)/*복사생성자*/				{ create(v.begin(), v.end()); }
	explicit Vec(size_t n, const T& val = T())	{ create(n, val); }

	~Vec()										{ uncreate(); }

public:
	size_type size() const					{ return _avail - _data; } 
	void clear();

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
	//자가할당 여부 확인
	if (&rhs != this) {
		uncreate(); //좌변 메모리 해제

		create(rhs.begin(), rhs.end()); // 우변이 지닌 요소를 좌변으로 복사.
	}
	return *this; //좌변의 객체의 참조를 리턴
}

template<class T>
void Vec<T>::create() {
	_data = _avail = _limit = nullptr;
}

template<class T>
void Vec<T>::create(size_type n, const T& val) {
	_data = _alloc.allocate(n);
	_limit = _avail = _data + n;
	::uninitialized_fill(_data, _avail, val); //[data,_avail) val로 초기화
}

template<class T>
void Vec<T>::create(const_iterator i, const_iterator j) {
	_data = _alloc.allocate(j-1);
	_limit = _avail = ::uninitialized_copy(i, j, _data);
	//[i,j)를 _dat에 초기화 한후 마지막 요소의 다음을 가리키는 포인터 반환
}

template<class T>
void Vec<T>::uncreate() {
	if (_data != nullptr) {
		//역순으로 소멸
		iterator it = _avail;
		while (it != _data)
			_alloc.destroy(--it);

		//저장공간 반환
		_alloc.deallocate(_data, _limit - _data);
	}

	_data = _limit = _avail = nullptr;
}

template<class T>
void Vec<T>::grow() {
	//현재 2배의 공간 할당.
	size_type new_size = max(2*(_limit - _data), ptrdiff_t(1));

	//새로운 곳으로 복사
	iterator new_data = _alloc.allocate(new_size);
	iterator new_avail = ::uninitialized_copy(_data, _avail, new_data);
	//기존 반환
	uncreate();
	//포인터 재설정
	_data = new_data;
	_avail = new_avail;
	_limit = _data + new_size;
}

template<class T>
void Vec<T>::unchecked_append(const T& val) {
	_alloc.construct(_avail++, val); //초기화 되어있지않은 공간에 객체 생성.
}

/*
확립된 class invariant
1. _data는 첫 번째 데이터 요소를 가리키며, 존재하지 않는다면 data는 nullptr이다.
2. _data <= _avail <= _limit
3. 요소들은 [_data,_avail) 안에 생성됨,
4. 요소들은 [_avial,_limit)안에 생성되지 않음.
*/