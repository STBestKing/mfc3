#include "pch.h"
#include "Student.h"


Student::Student()
{
}


Student::~Student()
{
}

void Student::calcuavr()
{
	average = (sub1 + sub2 + sub3) / 3;
}