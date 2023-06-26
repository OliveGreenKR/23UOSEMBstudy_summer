#pragma once
#include <vector>
#include <string>

vector<string> split(const string& s); 

size_t width(const vector<string>& v);
vector<string> frame(const vector<string>& v);

vector<string> find_urls(const string& s);