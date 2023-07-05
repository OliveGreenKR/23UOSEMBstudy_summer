#pragma once
#include "Handle.h"
#include <vector>
#include <string>
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

	friend std::ostream& operator<< (std::ostream& os, const Picture& pic);

protected:
	using ht_sz = std::vector<std::string>::size_type;
	using wd_sz = std::string::size_type;
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
	ht_sz height() const override;
private:
	std::vector<string> _data;
};

class Frame_Pic : public Pic_base {

	friend class Picture;
	friend Picture frame(const Picture& pic);

private:
	Frame_Pic(const Ptr<Pic_base>& pic) : _p(pic) { }

	wd_sz width() const override;
	ht_sz height() const override;
	void display(std::ostream&, ht_sz, bool) const override;

private:
	Ptr<Pic_base> _p;
};

class VCat_Pic : public Pic_base {

	friend class Picture;
	friend Picture vcat(const Picture& top, const Picture& bottom);

private:
	VCat_Pic(const Ptr<Pic_base>& t , const Ptr<Pic_base>& b) : _top(t), _bottom(b) { }

	wd_sz width() const override;
	ht_sz height() const override;
	void display(std::ostream&, ht_sz, bool) const override;

private:
	Ptr<Pic_base> _top, _bottom;
};

class HCat_Pic : public Pic_base {

	friend class Picture;
	friend Picture hcat(const Picture& left, const Picture& right);

private:
	HCat_Pic(const Ptr<Pic_base>& l, const Ptr<Pic_base>& r) : _leff(l), _right(r) { }

	wd_sz width() const override;
	ht_sz height() const override;
	void display(std::ostream&, ht_sz, bool) const override;

private:
	Ptr<Pic_base> _leff, _right;
};

//인터페이스 클래스
class Picture {

	friend class Pic_base;
	friend Picture frame(const Picture& pic);
	friend Picture vcat(const Picture& top, const Picture& bottom);
	friend Picture hcat(const Picture& left, const Picture& right);
	friend std::ostream& operator<< (std::ostream& os, const Picture& pic);

public:
	Picture(const std::vector<string>& = std::vector<string>());

private:
	Picture(Pic_base* ptr) : _p(ptr) { }

private:
	Ptr<Pic_base> _p;
};

Picture frame(const Picture& pic);
Picture vcat(const Picture& top, const Picture& bottom);
Picture hcat(const Picture& left, const Picture& right);
std::ostream& operator<< (std::ostream& os, const Picture& pic);