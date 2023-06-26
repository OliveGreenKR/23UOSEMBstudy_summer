#include "pch.h"
#include "myStr.h"
#include <cctype>
#include <algorithm>

//반복자 어댑터를 이용해 수정해보기
vector<string> split(const string& s) {
	vector<string> ret;
	typedef string::const_iterator iter;

	iter i = s.begin();

	auto isSpace = [ ](char c) { return isspace(c); };
	auto NotSpace = [ ](char c) { return !isspace(c); };

	while (i != s.end()) {
		//공백 무시
		i = ::find_if(i, s.end(), NotSpace);

		//다음단어 끝 찾기
		iter j = ::find_if(i, s.end(), isSpace);

		//복사
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

	ret.push_back(border); //상단 테두리 추가

	//양끝 테두리 
	for (auto& s : v) {
		ret.push_back("* " + s + string(maxlen - s.size(), ' ')+ " *");
	}

	ret.push_back(border); //하단 테두리 추가
	return ret;
}


/*
URL찾기
	URL = {protocol} + '://' + {resource}

1. :// 를 찾음
2. 그것을 기준으로 프로토콜과 리소스를 알 수 있음.
*/

vector<string> find_urls(const string& s) {
	vector<string> ret;
	using iter = string::const_iterator;
	//typedef string::const_iterator  iter;

	iter now = s.begin(), e = s.end();

	while (now != e) {

		// 1. '://'의  앞쪽을 탐색
		// 2. 문자가 존재한다면 url의 나머지를 탐색
		// 3. url을 완성하여 vector에 push
		// 4. now 증가

	}

}