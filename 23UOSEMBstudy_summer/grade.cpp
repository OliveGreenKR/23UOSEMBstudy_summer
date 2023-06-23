#include "grade.h"


template <typename T = double>
auto GetAvgFromVec = [ ](const vector<T>& vec) {  //lamda
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

double grade(Student_Info& student) {
    return grade(student.midterm, student.final, student.hw);
}
