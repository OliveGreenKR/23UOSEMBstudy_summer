#include "pch.h"
#include "Student_Info.h"
#include <list>
#include <ios> //for domain_error
#include <numeric> //accumulate
#include <algorithm>

double getAverage(const vector<double>& v) {
	return ::accumulate(v.begin(), v.end(), 0.0) / v.size();  //return Ÿ���� ���� *0.0
}

double grade(const double midterm, const  double final, const vector<double>& homeworks) {

	if (homeworks.size() == 0)
		throw domain_error("student has done no homework");

	return 0.4 * midterm  + 0.4 * final + 0.2 * getAverage(homeworks);
}

//��Ʈ���� �̿��� ���� ������ �Է¹޾Ƽ� ���Ϳ� ����
istream& read_hw(istream& in, OUT vector<double>& hws) {
    if (in) {
        hws.clear(); // make empty
        double x;
        while (in >> x) {
            hws.push_back(x);
        }
        in.clear(); //clear stream for next.
    }
    return in;
}

//���������� ���ڷ� ��ȯ
string letter_grade(double grade) {
    static const double numbers[] = {97,94,90,87,84,80,77,74,70,60,0};
    static const char* const letters[] = {"A+", "A", "A-", "B+", "B","B-","C+", "C", "C-", "D", "F"};
    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);  //�迭 ���� =  �迭 ��ü ũ�� / ��� �ϳ� ũ��

    for (size_t i = 0; i < ngrades; i++) {
        if (grade >= numbers[i])
            return letters[i];
    }
    return "???"; 
}

/**********************
* Core::
**********************/

std::istream& Core::read(std::istream& in) {
    in >> _name >> _midterm >> _final; 
    read_hw(in, _homework);
    return in;
}

//read student except hw
std::istream& Core::read_common(std::istream& in) {
    in >> _name >> _midterm >> _final;
    return in;
}

double Core::grade() const {
    return ::grade(_midterm, _final, _homework);  
}

void Core::regrade(double final, double thesis) {
    _final = final;
}

Core::operator double() const {
    return grade();
}



/**********************
* Grad::
**********************/

double Grad::grade() const { //������
    return ::min(Core::grade(),_thesis);
    //����� ���� �����ڸ�����, Grad::grade�� ���� ȣ���� �߻��Ѵ�.
}

std::istream& Grad::read(std::istream& in) {
    Core::read_common(in);    // �θ��� �޼ҵ� ���
    //read_common(in);        // �̰͵� ����
    in >> _thesis;
    read_hw(in, _homework);
    return in;
}

void Grad::regrade(double final, double thesis) {
    _final = final;
    _thesis = thesis;
}


/**************
* Student_info
*****************/

//Student_info::Student_info(const Student_info& s) :_cp(nullptr) {
//    if (s._cp)
//        _cp = s._cp->clone();
//}
//
//Student_info Student_info::operator=(const Student_info& s) {
//    if (&s != this) {
//        delete _cp;
//        if(s._cp)
//            _cp = s._cp->clone();
//        else
//            _cp = nullptr;
//    }
//    return *this;
//}


std::istream& Student_info::read(std::istream& is) {
    
    //delete _cp;  //nulltpr�� ��� �ƹ��͵� �������� �ʴ´�.
    char ch;
    is >> ch;

    if(ch == Student::core)
        _cp = new Core(is);
    else
        _cp =  new Grad(is);

    return is;
}

std::string Student_info::name() const {
    if(_cp)
        return _cp->name();
    throw std::runtime_error("uninitiallized Student");
}

double Student_info::grade() const {
    if(_cp)
        return _cp->grade();
    throw std::runtime_error("uninitiallized Student");
}

void Student_info::regrade(double final, double thesis) {
    _cp.make_unique(); //���纻 ����

    if(_cp)
        _cp->regrade(final,thesis);
    else
        throw runtime_error("regrade of unknown student");
}
