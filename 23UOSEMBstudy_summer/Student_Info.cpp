#include "pch.h"
#include "Student_Info.h"

//스트림을 이용해 숙제 점수를 입력받아서 벡터에 저장
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

istream& read_student(istream& in, OUT Student_Info& student) {
    in >> student.name >> student.midterm >> student.final;
    read_hw(in, student.hw);
    return in;
}

bool compare_name(const Student_Info& A, const Student_Info& B) { // 이름순으로  sorting 가능(오름차순)
    return A.name < B.name;
}
