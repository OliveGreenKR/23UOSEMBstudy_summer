#include "pch.h"
#include "myStr.h"
#include <cctype>
#include <algorithm>
#include <iostream>

//�ݺ��ڸ� ���� split Ȯ�强 �������Ѻ���
template < class Out>
void split(const string& str, Out os) {
	using iter = string::const_iterator;
	iter i = str.begin();

	auto isSpace = [ ](char c) { return isspace(c); };
	auto NotSpace = [ ](char c) { return !isspace(c); };

	while (i != str.end()) {

		i = find_if(i, str.end(), NotSpace);

		iter j = find_if(i, str.end(), isSpace);

		if (i != str.end())
			*os++ = string(i, j);  //stl�� �ݺ��� Ư���� �̿�.

		i = j;
	}
}

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

bool not_url_char(char c) {
	static const string url_ch = "~;/?:@=&$-_.+!*'(),"; //url�� �� �� �ִ� Ư�� ����.
	return !(::isalnum(c) || ::find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator url_end(string::const_iterator b, string::const_iterator e) {
	return ::find_if(b, e, not_url_char);
}

string::const_iterator url_beg(string::const_iterator b, string::const_iterator e) {
	static const string sep = "://";
	using iter = string::const_iterator;

	iter i = b;
	while ((i = ::search(i, e, sep.begin(), sep.end())) != e) { 
		if (i != b && i + sep.size() != e) {
			iter beg = i; 
			while (beg != b && ::isalpha(beg[-1]))
				--beg;

			if (beg != i && !not_url_char(i[sep.size()]))
				return beg;
		}
		i += sep.size();
	}
	return e;
}

vector<string> find_urls(const string& s) {
	vector<string> ret;
	using iter = string::const_iterator;
	//typedef string::const_iterator  iter;

	iter b = s.begin(), e = s.end();

	while (b != e) {
		b = url_beg(b, e);
		if (b!=e) {
			iter after = url_end(b, e);
			ret.push_back(string(b, after));
			b = after;
		}
	}
	return ret;
}

/*
map
*/

map<string, vector<int>> xref(istream& in, vector<string> find_words(const string&)) {

	string line;
	int line_number = 0;
	map<string, vector<int> > ret;

	//������ �б�
	while (getline(in, line)) {
		++line_number;

		//�־��� ���� �Լ��� ���� ����.
		vector<string> words = find_words(line);

		//����
		for (auto word : words)
			ret[word].push_back(line_number);
	}
	return ret;
}

