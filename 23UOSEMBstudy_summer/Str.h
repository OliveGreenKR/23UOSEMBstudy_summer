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
StrŬ�������� ���� ������, �Ҵ� ������, �Ҹ��ڸ� ���� ���� �ʾҴ�.

>> �⺻������ �����ϱ� ����, �ش� Ŭ���� ��ü�� �޸� �Ҵ��� ���� �ʴ´�.(�Ҹ��ڰ� �ʿ����)
�޸� ������ Vec Ŭ�������� �ñ��.

��ó�� �Ϲ������� �Ҹ��ڰ� �ʿ���� Ŭ������, 
������� ���� �����ڳ� �Ҵ� �����ڸ� �߰��� �ʿ�� ���� �ʴ´�.
*/