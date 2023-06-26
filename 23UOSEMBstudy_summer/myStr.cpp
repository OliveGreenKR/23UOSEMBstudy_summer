#include "pch.h"
#include "myStr.h"
#include <cctype>
#include <algorithm>

//�ݺ��� ����͸� �̿��� �����غ���
vector<string> split(const string& s) {
	vector<string> ret;
	typedef string::const_iterator iter;

	iter i = s.begin();

	auto isSpace = [ ](char c) { return isspace(c); };
	auto NotSpace = [ ](char c) { return !isspace(c); };

	while (i != s.end()) {
		//���� ����
		i = ::find_if(i, s.end(), NotSpace);

		//�����ܾ� �� ã��
		iter j = ::find_if(i, s.end(), isSpace);

		//����
		if (i != s.end()) {
			ret.push_back(string(i, j));
		}

		i = j;
	}

	return ret;
}

bool is_palindrome(const string& s) {
	return equal(s.begin(), s.end(), s.rbegin());
}

size_t width(const vector<string>& v) {
	size_t maxlen = 0;
	for (auto& str : v)
		maxlen = ::max(maxlen, str.size());
	return maxlen;
}

vector<string> frame(const vector<string>& v) {
	vector<string> ret;
	size_t maxlen = width(v);
	string border(maxlen+4, '*');

	ret.push_back(border); //��� �׵θ� �߰�

	//�糡 �׵θ� 
	for (auto& s : v) {
		ret.push_back("* " + s + string(maxlen - s.size(), ' ')+ " *");
	}

	ret.push_back(border); //�ϴ� �׵θ� �߰�
	return ret;
}


/*
URLã��
	URL = {protocol} + '://' + {resource}

1. :// �� ã��
2. �װ��� �������� �������ݰ� ���ҽ��� �� �� ����.
*/

vector<string> find_urls(const string& s) {
	vector<string> ret;
	using iter = string::const_iterator;
	//typedef string::const_iterator  iter;

	iter now = s.begin(), e = s.end();

	while (now != e) {

		// 1. '://'��  ������ Ž��
		// 2. ���ڰ� �����Ѵٸ� url�� �������� Ž��
		// 3. url�� �ϼ��Ͽ� vector�� push
		// 4. now ����

	}

}