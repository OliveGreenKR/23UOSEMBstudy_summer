#include <iostream>
#include <iomanip>  //setprecision
#include <ios>      //streamsize
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define OUT

using namespace std;

template <typename T = double>
auto GetAvgFromVec = [](const vector<T>& vec) {  //lamda
	T sum = 0;
	for (auto& e : vec)
		sum += e;
	return  sum / vec.size();
};

double grade(double midterm, double final, vector<double>& homeworks) {

    if (homeworks.size() == 0)
        throw domain_error("student has done no homework");

    return 0.4 * midterm  + 0.4 * final + 0.2 * GetAvgFromVec<double>(homeworks);
}

//��Ʈ���� �̿��� ���� ������ �Է¹޾Ƽ� ���Ϳ� ����
istream& read_hw(istream& in, OUT vector<double>hws) {
    if (in) {
        
        hws.clear(); // make empty

        double x;
        while (in >> x) {
            hws.push_back(x);
        }

        in.clear(); //clear stream
    }
    return in;
}


int main()
{
    ios_base::sync_with_stdio(false); //FASTIO , dont use printf,scanf anymore

    //grade(0,0,vector<double>())
    //error - not lvalue

	/*
	* lvalue(�ް�)          : ���Ͻ��� ��.
	* rvalue(������)        : �ް��� �ƴ� ������. �ӽð��� ����� �ǹ�.
    * 
    * 
    * �ް� ���� : ���� ���� �� ���� ����
    * const �ް� ���� : read only
    * 
    * ������ ���� :  ������ ���� �� ���� ���� + ������ �ֹ߼��� ��Ÿ��.
    *               >> ����� '�̵�' �� ���� �̿�ȴ�. ����� ��ü ���� ����, ���� ���ҽ��� ���� '�̵�' ��ų �� ����.
    *
    */

    class Knight {
    public:
        Knight(int hp, int mp) {
            _hp = hp;
            _mp = mp;
        }

        void operator= (Knight&& k) noexcept {
            //���� ����
            _hp = k._hp;
            _mp = k._mp;
        }
        int _hp;
        int _mp;
    };


    auto k1 =  new Knight(100,100);
    auto k2 =  new Knight(20,20);
    
    cout << k2->_hp  << endl;
    k2 = k1;

    cout << k2->_hp << endl;
    cout << k1->_hp << endl;


    /* ���� ����(forwarding reference) :  Ÿ�� ����(deduction)�� �߻��� ��  ���������� �����ϴ� ��.
    */ 
    vector<double> vecs;

    for (auto&& v : vecs) {  //�ް�, ������ �ƹ��ų� ����
        cout << v << endl;
    }

	//for (const auto&& v : vecs) {  //���� ���� �ƴ�.
    //    cout << v << endl;
    //}

    Knight&& k5 = Knight(100, 100);

    auto testRvalue = [ ](Knight&& knight) { };
    testRvalue(::move(k5));
    //testRvalue(k5);


}


