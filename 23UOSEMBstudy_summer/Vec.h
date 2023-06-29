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
	Vec() :{ create(); }
	explicit Vec(size_t n, const T& val = T()) { create(n, val); }

private:
	T* _data;	// data pointer
	T* _limit;	// end pointer
};

