#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

//Create a template. This will allow functions to take in any type of variable
template<typename T>
//Function to find the index of the minimum value in an unsorted list
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned minIndex = index; //Initialize minimum index to input index
    for (unsigned int i = index; i < vals.size(); i++) {
        if (vals.at(i) < vals.at(minIndex)) {
            minIndex = i; //Compare values at min index with index at i, and set minIndex to whichever one is smaller
        }
    }
    return minIndex;
}

template<typename T>
//Passes in a vector of type T and sorts them based on the selection sort method. Uses min_index function to find the index of the min value in the unsorted portion of the vector
void selection_sort(vector<T> &vals) {
    for(unsigned int i = 0; i < vals.size(); i++){
        unsigned minIndex = min_index(vals, i);
        if (vals.at(i) > vals.at(minIndex)) {
            T temp = vals.at(i);
            vals.at(i) = vals.at(minIndex); //Loops through vector and compares values at current index with the index of the minimum value in unsorted list, and swaps if the value at the current index is larger than the min value in the vector
            vals.at(minIndex) = temp;
        }
    }
}

template<typename T>
// Passes in a vector of type T (T could be string, double or int) and an index of type int. The function returns the element located at the index of the vals.
T getElement(vector<T> vals, int index){
    //Try block
    unsigned int i = index;
    try {
        if (i < 0 || i > vals.size()) {
            throw runtime_error("out of range exception occurred"); //Throw out of range error if index is negative or greater than the vector size
        }
    }
    //Catch block
    catch (runtime_error& excpt) {
        cout << excpt.what() << endl;
    }
    return i;
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main(){
    //Part A
    vector<int>v1 = {5,-3,2,25,1};
     cout << "Testing selection sort on int values, values before selection sort: ";
    for(unsigned int i= 0; i < v1.size(); i++){
        cout << v1.at(i) << " ";
    }
    cout << endl;
    cout << "After selection sort (expected -3 1 2 5 25): ";
    selection_sort(v1);
    for(unsigned int i=0; i < v1.size(); i++){ 
        cout << v1.at(i) << " ";
    }
    cout << endl;

    vector<char>v2 = {'a', 'f', 'b', 'W', 'z'};
    cout << "Testing selection sort on char values, values before selection sort: ";
    for(unsigned int i = 0; i < v2.size(); i++){
        cout << v2.at(i) << " ";
        cout << endl;
    }
    cout << "After selection sort (expected W a f b z): ";
    selection_sort(v2);
    for(unsigned int i=0; i<v2.size(); i++){
        cout << v2.at(i) << " ";
    }
    cout << endl;
    
    vector<double>v3 = {59.1,0.2,-3.27,102.3,62.1, 2.1};
    cout << "Testing selection sort on double values, values before selection sort: ";
    for (unsigned int i = 0; i < v3.size(); ++i){
        cout << v3.at(i) << " ";
    }
    cout << endl;
    selection_sort(v3);
    cout << "After selection sort (expected -3.27 -.2 2.1 59.1 62.1 102.3):";
    for(unsigned int i=0; i<v3.size(); i++){
        cout << v3.at(i) << " ";
    }
    cout << endl;
    
    // Part B
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     while(--numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;
         curChar = getElement(vals,index);
         cout << "Element located at " << index << ": is " << curChar << endl;
    }
    return 0;
}
