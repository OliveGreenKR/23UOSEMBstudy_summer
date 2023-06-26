#pragma once
#include <vector>
#include <list>
struct Student_Info;

double grade_aux(const Student_Info& );
double grade(double , double final, vector<double>& homeworks);
double grade(Student_Info& student);


bool did_all_hw(const Student_Info& s);


double average_analysis(const vector<Student_Info>& students);


vector<Student_Info> extract_fails(vector<Student_Info>& students);
list<Student_Info> extract_fails(OUT list<Student_Info>& students);