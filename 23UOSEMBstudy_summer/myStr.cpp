#include "pch.h"
#include "myStr.h"
#include <cctype>

vector<string> split(const string& s) {
	vector<string> ret;
	typedef string::size_type string_size;

	string_size i = 0;

	while (i != s.size()) {
		//���� ����
		while ( i != s.size() && isspace(s[i]))
			++i;
		string_size j = i;

		//�ܾ��� ��ã��
		while (j != s.size() && !isspace(s[j]))
			j++;

		//�ܾ� ����
		if (i != j) {
			ret.push_back(s.substr(i, j-i)); 
			i = j;
		}
	}
	return ret;
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
