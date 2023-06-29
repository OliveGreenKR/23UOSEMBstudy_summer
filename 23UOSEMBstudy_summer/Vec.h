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

	//�Ҵ� ������ - const ���� Ÿ�� �μ�
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

/* �Ҵ� ������ (assignment operator)
* opertaor= �Ҵ� ������
* Ŭ���� ��ü�� const_reference Ÿ���� �Ҵ� �����ڴ� Ư���ϴ�!
* 
* Ŭ���� Ÿ���� ���� �Ҵ��ϴ� ���� ������ �ǹ��ϴ��� �����ϱ� ����.
* 
* header���� template ���� �ȿ����� ���Ǽ��� ���� '<T>'�� �����ص� ������, �ܺο��� ���Ǹ��ϴ� cpp������ �� ������־���Ѵ�.
* ������ cpp ������ �� �Լ����� �ѹ� <T>�� ����ϸ�, �Ϲ������� <T>�� ��ü�� �����Ǿ� ��������.
*/

