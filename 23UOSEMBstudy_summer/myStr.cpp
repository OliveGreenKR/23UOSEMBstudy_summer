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

/*
1. url의 앞쪽을 탐색
(내부에서만 이용할 가능성이 높음 -> 헤더에 표시x)

'유효한 url이' 있는지 *탐색 해야함.
유효  -> 프로토콜의 시작 반복자 반환.
유효x -> 유효하지 않음을 반환해야함.. -> 문자열의 end 반환 (반복자 어댑터와 유사하게 동작하도록)

==> 반복자 어댑터 사용 (find_if) ==> 현재반복자, 종료 반복자) 

2. url의 나머지를 탐색 => 1번과 비슷한 방식 사용하면 쉽고 통일성 있게 구현가능.
*/


/*
* find_if를 사용하기 위한 pred 만들기.
* url에 사용되는 유효한 문자인지를 판별해야함.
*/
bool not_url_char(char c) {
	static const string url_ch = "~;/?:@=&$-_.+!*'(),"; //url에 들어갈 수 있는 특수 문자.
	//static을 사용하여, 첫 번째 호출에서만 객체 생성, 이후 호출에는 미리 만들어진 객체를 사용한다.
	//(stortage calass sepecifier 참고)

	return !(::isalnum(c) || ::find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
	//알파벳이나 숫자 이면서 url_ch에 들어있는 경우 => url 유효 => False 반환
}

//b~e에서 'url이 아닌 문자'를 찾고 반환 하거나, 모두 유효할 경우에는 e를 반환.
string::const_iterator url_end(string::const_iterator b, string::const_iterator e) {
	return ::find_if(b, e, not_url_char);
}

string::const_iterator url_beg(string::const_iterator b, string::const_iterator e) {
	static const string sep = "://";
	using iter = string::const_iterator;

	iter i = b;
	//구분 기호 찾기
	while ((i = ::search(i, e, sep.begin(), sep.end())) != e) { //찾으면 ':' 위치 반환
		//구분 기호가 처음 혹은 마지막에 위치하지 않는지 확인
		if (i != b && i + sep.size() != e) {
			iter beg = i; //프로토콜 시작 위치 찾기
			while (beg != b && ::isalpha(beg[-1]))
				--beg;

			//구분 기호 앞뒤로 url의 일부에서 유효한 문자가 하나라도 있는지 확인.
			if (beg != i && !not_url_char(i[sep.size()]))
				return beg;
		}
		//구분기호가 url의 일부가 아님.
		i += sep.size();
	}
	return e;
}