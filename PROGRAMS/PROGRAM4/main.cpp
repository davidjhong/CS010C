#include <iostream>
#include <cstring>
#include <sstream>
#include <queue>
#include <stack>
#include <climits>

#include "Jug.h"

using namespace std;

int main() {

    string solution;
    Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
    if (head.solve(solution) != 1) {
        cout << "Error 3" << endl;
    }
    cout << solution << endl << endl;


    string solution1;
    Jug head1( 3, 5, 4, 1, 1, 1, 1, 1, 2);         
    if(head1.solve(solution1) != 1) {
        cout << "Error 3" << endl;
    }
    cout << solution1 << endl;

    return 0;
}
