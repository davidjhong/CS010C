#include <iostream>
#include "IntList.h"

using namespace std;

int main() {
    IntList test1;
    test1.push_front(6);
    test1.push_front(2);
    test1.push_front(7);
    test1.push_back(5);
    test1.push_back(8);
    test1.push_back(12);
    cout << "Outputting list, expecting 7 2 6 5 8 12" << endl;
    cout << "Actual: " << test1 << endl;
    cout << "Outputting list in reverse, expecting 12 8 5 6 2 7" << endl;
    cout << "Actual: ";
    test1.printReverse();
    cout << endl;
    test1.pop_front();
    test1.pop_front();
    test1.pop_back();
    test1.pop_back();
    cout << "Outputting list after pop, expecting 6 5" << endl;
    cout << "Actual: " << test1 << endl;
    cout << "Outputting list in reverse, expecting 5 6" << endl;
    cout << "Actual: " << test1 << endl;
}
