#pragma once

struct Student_Info {
    string name;
    double midterm = 0;
    double final = 0;
    vector<double> hw = vector<double>(0.f);
}; //dont forget to add ';'

bool compare_name(const Student_Info& A, const Student_Info& B);

istream& read_hw(istream& in, vector<double>& hws);
istream& read_student(istream& in, Student_Info& student);

bool compare_name(const Student_Info& A, const Student_Info& B);
