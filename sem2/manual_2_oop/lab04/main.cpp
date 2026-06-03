#include <iostream>
#include "Student.h"
#include "Person.cpp"
#include "Student.cpp"

using namespace std;

void f1(Person& p) {
    p.setName("John");
}

Person f2() {
    Student bob("Bob", 21, "CS", 5);
    return bob;
}

int main() {
    Person alex("Alex", 20);
    cout << alex;
    Student studentAlex(alex, "Math", 5);
    cout << studentAlex;
    f1(studentAlex);
    cout << studentAlex;
    cout << f2();
}
