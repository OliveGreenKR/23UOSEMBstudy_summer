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
���� �迭 Vec�� ����� ���ؼ���
���� ������ �������� �ٲ� �� �ֵ��� �ϴ� push_back �������̽��� �ʿ��ϴ�.

������ ���� push_back ������ ������ ����.

0. �⺻������ ����Ǿ��ִ� �������� ���� ���������� �߰��Ѵ�.
1. ������ �����ϸ� ���� �Ҵ�, ���� ũ���� 2�� ��ŭ �Ҵ��Ѵ�.
2. ���� ���� �����͸� �ű��, ���� �������� �޸𸮸� �����Ѵ�.
3. ���� �Ҵ��� �޸𸮿� ���ο� ���� �߰��Ѵ�.

���� ���� ������ ���ؼ��� �����ϴ� �迭 ������ �ľ��ϴ� ���� ����� �ٲپ����.
�������� ��Ÿ���� �����Ͱ� 2���� �Ǿ���Ѵ�.
�ʱ�ȭ ���� ���� ��������� ó���� ����Ű�� �����Ͱ� �߰��� �ʿ��ϴ�.

 [*][*][*][*][*][][][[][][][][][]
^_data          ^_avail          ^_limt

new-delete ����� �⺻������ ������ �ִ�.
������� ���� �������� ��� �ʱ�ȭ�� �Ǿ������.(�ڼ��� ������ Notion ����)

���� �޸� �Ҵ��� ���� �ٸ� ����� ����� ����. 
#include <memory> -> allocator<T> Ŭ���� ���.
-allocator<T>
	�ʱ�ȭ ���� ���� �޸� ���� �Ҵ��ϰ�, ���� ù ��° ��Ҹ� ����Ű�� ������ ��ȯ.

*/