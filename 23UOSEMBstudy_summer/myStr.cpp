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

/*
1. url�� ������ Ž��
(���ο����� �̿��� ���ɼ��� ���� -> ����� ǥ��x)

'��ȿ�� url��' �ִ��� *Ž�� �ؾ���.
��ȿ  -> ���������� ���� �ݺ��� ��ȯ.
��ȿx -> ��ȿ���� ������ ��ȯ�ؾ���.. -> ���ڿ��� end ��ȯ (�ݺ��� ����Ϳ� �����ϰ� �����ϵ���)

==> �ݺ��� ����� ��� (find_if) ==> ����ݺ���, ���� �ݺ���) 

2. url�� �������� Ž�� => 1���� ����� ��� ����ϸ� ���� ���ϼ� �ְ� ��������.
*/


/*
* find_if�� ����ϱ� ���� pred �����.
* url�� ���Ǵ� ��ȿ�� ���������� �Ǻ��ؾ���.
*/
bool not_url_char(char c) {
	static const string url_ch = "~;/?:@=&$-_.+!*'(),"; //url�� �� �� �ִ� Ư�� ����.
	//static�� ����Ͽ�, ù ��° ȣ�⿡���� ��ü ����, ���� ȣ�⿡�� �̸� ������� ��ü�� ����Ѵ�.
	//(stortage calass sepecifier ����)

	return !(::isalnum(c) || ::find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
	//���ĺ��̳� ���� �̸鼭 url_ch�� ����ִ� ��� => url ��ȿ => False ��ȯ
}

//b~e���� 'url�� �ƴ� ����'�� ã�� ��ȯ �ϰų�, ��� ��ȿ�� ��쿡�� e�� ��ȯ.
string::const_iterator url_end(string::const_iterator b, string::const_iterator e) {
	return ::find_if(b, e, not_url_char);
}

string::const_iterator url_beg(string::const_iterator b, string::const_iterator e) {
	static const string sep = "://";
	using iter = string::const_iterator;

	iter i = b;
	//���� ��ȣ ã��
	while ((i = ::search(i, e, sep.begin(), sep.end())) != e) { //ã���� ':' ��ġ ��ȯ
		//���� ��ȣ�� ó�� Ȥ�� �������� ��ġ���� �ʴ��� Ȯ��
		if (i != b && i + sep.size() != e) {
			iter beg = i; //�������� ���� ��ġ ã��
			while (beg != b && ::isalpha(beg[-1]))
				--beg;

			//���� ��ȣ �յڷ� url�� �Ϻο��� ��ȿ�� ���ڰ� �ϳ��� �ִ��� Ȯ��.
			if (beg != i && !not_url_char(i[sep.size()]))
				return beg;
		}
		//���б�ȣ�� url�� �Ϻΰ� �ƴ�.
		i += sep.size();
	}
	return e;
}