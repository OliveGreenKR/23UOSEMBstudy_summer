#include "pch.h"
#include "myStr.h"
#include <cctype>

vector<string> split(const string& s) {
	vector<string> ret;
	typedef string::size_type string_size;

	string_size i = 0;

	while (i != s.size()) {
		//공백 무시
		while ( i != s.size() && isspace(s[i]))
			++i;
		string_size j = i;

		//단어의 끝찾기
		while (j != s.size() && !isspace(s[j]))
			j++;

		//단어 복사
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

	ret.push_back(border); //상단 테두리 추가

	//양끝 테두리 
	for (auto& s : v) {
		ret.push_back("* " + s + string(maxlen - s.size(), ' ')+ " *");
	}

	ret.push_back(border); //하단 테두리 추가
	return ret;
}
