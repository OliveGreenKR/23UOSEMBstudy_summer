#pragma once
#include <vector>
#include <string>
#include <map>

vector<string> split(const string& s); 

size_t width(const vector<string>& v);
vector<string> frame(const vector<string>& v);

vector<string> find_urls(const string& s);

map<string, vector<int>> xref(istream& in, vector<string> find_words(const string&) = split);