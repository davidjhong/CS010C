#ifndef __PRINTJOB_H
#define __PRINTJOB_H

using namespace std;

class PrintJob {
private:
    int priority;
    int jobNumber;
    int numPages;

public:
    PrintJob(); // Default Constructor
    PrintJob (int, int, int); // Parameterized Constructor
    int getPriority ();
    int getJobNumber ();
    int getPages ();
};

#endif
