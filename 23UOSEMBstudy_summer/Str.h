#pragma once
#include "Vec.h"
#include <algorithm>
#include <iterator>  //back_inserter()
class Str {
public:
	using size_type = Vec<char>::size_type;

	Str() { }
	Str(size_type n, char c) : _data(n, c) { }
	//c_str Ÿ���� �迭������ ��ü ����
	Str(const char* cp) {   
		std::copy(cp, cp+std::strlen(cp), std::back_inserter(_data));
	}
	//�ݺ��ڷ� ��ü ����
	template <class In> 
	Str(In b, In e) {
		std::copy(b, e, std::back_inserter(_data));
	}

private:
	Vec<char> _data;
};

/*
Str s("hi");

Str t = "hello";
s = "hello";

���� �� ������
1. const Str&�� ���� ������ �� t �ʱ�ȭ
2. �Ҵ� ������ =�� �̿��� �Ҵ�. �μ��� const char* �̴�.
�� ����Ѵ�.
2���� ���ؼ��� �⺻ �Ҵ� �����ڰ� �ƴ� �߰����� �Ҵ� �����ڿ� ���� �����ڸ� �����ε� �� �ʿ䰡 �־�δ�.
������ �����ڴ� �̹� �����Ѵ�. ���� �ش� �����ڴ� '����� ���� ��ȯ'(user-defined conversion)�� ������ �ô´�.
(const char* -> Str)
�׷��ٸ� �����Ϸ��� 2�� ���꿡�� ������ ���� ������ �ϰ� �ȴ�.

1. �����ڸ� �̿��� �Ͻ��� Str ��ü ����.
2. Str�� �⺻ �Ҵ� ������ �̿��ؼ� s �� �Ͻ��� ��ü�� ���� �Ҵ�.

���� ���� 1,2 ������ ���� ������.
*/