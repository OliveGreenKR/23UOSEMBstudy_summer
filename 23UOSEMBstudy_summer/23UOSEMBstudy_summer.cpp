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

//스트림을 이용해 숙제 점수를 입력받아서 벡터에 저장
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
	* lvalue(왼값)          : 비일시적 값.
	* rvalue(오른값)        : 왼값이 아닌 나머지. 임시값과 비슷한 의미.
    * 
    * 
    * 왼값 참조 : 원본 접근 및 수정 가능
    * const 왼값 참조 : read only
    * 
    * 오른값 참조 :  원본의 접근 및 수정 가능 + 원본의 휘발성을 나타냄.
    *               >> 대상의 '이동' 에 자주 이용된다. 대상의 전체 복사 없이, 적은 리소스로 값을 '이동' 시킬 수 있음.
    *
    */

    class Knight {
    public:
        Knight(int hp, int mp) {
            _hp = hp;
            _mp = mp;
        }

        void operator= (Knight&& k) noexcept {
            //얕은 복사
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


    /* 전달 참조(forwarding reference) :  타입 연역(deduction)이 발생할 때  보편적으로 참조하는 것.
    */ 
    vector<double> vecs;

    for (auto&& v : vecs) {  //왼값, 오른값 아무거나 받음
        cout << v << endl;
    }

	//for (const auto&& v : vecs) {  //전달 참조 아님.
    //    cout << v << endl;
    //}

    Knight&& k5 = Knight(100, 100);

    auto testRvalue = [ ](Knight&& knight) { };
    testRvalue(::move(k5));
    //testRvalue(k5);


}


