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
