#pragma once

/*
1. Ŭ������ �������� �������̽��� ����ϱ�

	- ���� ����
		�� �� ���� ����
		�� ������ ũ�⸦ �����Ͽ� ����

	- ���Ͱ� ����ϴ� Ÿ���� ����
		�� iterator ���

	- �ε��� �����ڸ� �̿��� �� ��� ����
		�� size �˾Ƴ���
		�� �ε��� ������ �����ε�

	- ǥ�� ���̺귯�� �˰���, ����� ��� ��� ���� ����
		�� begin iterator
		�� end iterator
*/


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

private:


private:
	T* _data;	// data pointer
	T* _limit;	// end pointer
};

//ǥ�� ���ø� Ŭ������ �Թ��� ������ ���α׷��Ӱ� ����� �� �ִ� Ÿ�� �̸��� �����ϵ� �ڼ��� ������ ���ܾ��Ѵ�.