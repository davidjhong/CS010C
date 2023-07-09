#include "PrintJob.h"

PrintJob::PrintJob() : priority(0), jobNumber(0), numPages(0) {}

PrintJob::PrintJob (int setP, int setJ, int numP ) : priority(setP), jobNumber(setJ), numPages(numP) {}

int PrintJob::getPriority (){
    return priority;
}

int PrintJob::getJobNumber (){
    return jobNumber;
}

int PrintJob::getPages (){
    return numPages;
}
