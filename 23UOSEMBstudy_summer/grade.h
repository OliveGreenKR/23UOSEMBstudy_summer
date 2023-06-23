#pragma once

#include <vector>
#include "Student_Info.h"

using namespace std;

double grade(double midterm, double final, vector<double>& homeworks);
double grade(Student_Info& student);