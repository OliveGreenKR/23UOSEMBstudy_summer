#pragma once
#include <vector>
#include <string>
#include <map>
template < class Out>
void split(const string& str, Out os);

vector<string> split(const string& s); 
vector<string> split(const string& s); 

size_t width(const vector<string>& v);
vector<string> frame(const vector<string>& v);

vector<string> find_urls(const string& s);

map<string, vector<int>> xref(istream& in, vector<string> find_words(const string&) = split);


class Pic_base {
	using ht_sz = std::vector<std::string>::size_type;
	using wd_sz = std::string::size_type;
private:
	virtual wd_sz width() const		= 0;
	virtual ht_sz height() const	= 0;
	virtual void display(std::ostream&, ht_sz, bool) const = 0;
};