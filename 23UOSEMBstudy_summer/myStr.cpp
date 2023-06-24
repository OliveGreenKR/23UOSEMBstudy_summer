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
