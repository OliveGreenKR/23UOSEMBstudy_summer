#pragma once
#include "Handle.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
//template < class Out>
//void split(const string& str, Out os);
//
//vector<string> split(const string& s); 
//vector<string> split(const string& s); 
//
//size_t width(const vector<string>& v);
//vector<string> frame(const vector<string>& v);
//
//vector<string> find_urls(const string& s);
//
//map<string, vector<int>> xref(istream& in, vector<string> find_words(const string&) = split);

class Picture;

class Pic_base {

	friend class String_Pic;
	friend class Frame_Pic;
	friend class VCat_Pic;
	friend class HCat_Pic;
	friend std::ostream& operator<< (std::ostream& os, const Picture& pic);

protected:
	using ht_sz = std::vector<std::string>::size_type;
	using wd_sz = std::string::size_type;

	static void pad(std::ostream& os, wd_sz beg, wd_sz end) {
		while (beg != end) {
			os << " ";
			++beg;
		}
	}
	/*
	* 추상 기본 클래스의 멤버함수
	* 
	* 추상 기본 클래스이지만 멤버 함수를 정의할 수가 있다. 기본 클래스의 객체의 존재 유무와 멤버함수의 유무는
	* 상관이 없기 때문.
	*/
private:
	virtual wd_sz width() const		= 0;
	virtual ht_sz height() const	= 0;
	virtual void display(std::ostream&, ht_sz, bool) const = 0;

public:
	virtual ~Pic_base() { }
};

class String_Pic : public Pic_base {

	friend class Picture;

private:
	String_Pic(const std::vector<string>& v) : _data(v) { }

	wd_sz width() const override;
	ht_sz height() const override { return _data.size(); }
	void display(std::ostream&, ht_sz, bool) const override;
private:
	std::vector<string> _data;
};

class Frame_Pic : public Pic_base {

	friend class Picture;

private:
	static const int border_size = 1;
	static const int space_size = 1;

	Frame_Pic(const Ptr<Pic_base>& pic) : _p(pic) { }

	wd_sz width() const override { return _p->width() + 2*(border_size+space_size); }
	ht_sz height() const override { return _p->height() + 2*(border_size+space_size); }
	void display(std::ostream&, ht_sz, bool) const override;

private:
	Ptr<Pic_base> _p;
};

class VCat_Pic : public Pic_base {

	friend class Picture;
private:
	VCat_Pic(const Ptr<Pic_base>& t , const Ptr<Pic_base>& b) : _top(t), _bottom(b) { }

	wd_sz width() const override { return std::max(_top->width(),_bottom->width()); }
	ht_sz height() const override { return _top->height() + _bottom->height(); }
	void display(std::ostream& , ht_sz, bool) const override;

private:
	Ptr<Pic_base> _top, _bottom;
};

class HCat_Pic : public Pic_base {

	friend class Picture;

private:
	HCat_Pic(const Ptr<Pic_base>& l, const Ptr<Pic_base>& r) : _left(l), _right(r) { }

	wd_sz width() const override { return _left->width() + _right->width(); }
	ht_sz height() const override { return std::max(_left->height(),_right->height()); }
	void display(std::ostream&, ht_sz, bool) const override;

private:
	Ptr<Pic_base> _left, _right;
};

//인터페이스 클래스
class Picture {

	friend class Pic_base;
	friend std::ostream& operator<< (std::ostream& os, const Picture& pic);

public:
	Picture(const std::vector<string>& = std::vector<string>());

	static Picture frame(const Picture& pic);
	static Picture vcat(const Picture& top, const Picture& bottom);
	static Picture hcat(const Picture& left, const Picture& right);

private:
	Picture(Pic_base* ptr) : _p(ptr) { }

private:
	Ptr<Pic_base> _p;
};

std::ostream& operator<< (std::ostream& os, const Picture& pic);