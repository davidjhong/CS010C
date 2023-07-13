#include <string>
#include <vector>  
#include <iostream>
#include <queue>
#include <stack>
#include "Jug.h"
#include <sstream>

using namespace std;

int Jug :: solve (string& solution)
{
    stringstream invalidInput;
    // Check if inputs are valid
    if(!(cA > 0 && cA <= cB) || !(cB > N && cB <= 1000))
    {
        invalidInput << "";
        solution = invalidInput.str();
        return -1;
    }

    if(cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0)
    {
        invalidInput << "";
        solution = invalidInput.str();
        return -1;
    }
    
    //check if N is a valid solution
    bool valid = false; 
    for(unsigned int i = 0; i < graph.size(); i++)
    {
        if(graph[i].A == 0 && graph[i].B == N){
            valid = true;
        }
    }

    if(!valid)
    {
        return 0;
    }

    stringstream solutionString;
    queue<vertex*> unvisitedQueue;
    unvisitedQueue.push(&graph[0]);
    for(unsigned int i = 1; i < graph.size(); i++)
    {
        unvisitedQueue.push(&graph[i]);
    }
    
    // filling the edges 
    int altPathDistance = 0;
    while(!unvisitedQueue.empty())
    {
        vertex* curr = unvisitedQueue.front();
        unvisitedQueue.pop();
        for(unsigned int i = 0; i < 6; i++){
           if(graph[curr->newStateAfterAction[i]].A == curr->A && graph[curr->newStateAfterAction[i]].B == curr->B)
           {
           } 
           else 
           {
            if(i == 0)
            {
                curr->edgeWeight1 = cfA;
            } 
            else if(i == 1)
            {
                curr->edgeWeight2 = cfB;
            } 
            else if(i == 2)
            {
                curr->edgeWeight3 = ceA;
            } 
            else if(i == 3)
            {
                curr->edgeWeight4 = ceB;
            } 
            else if(i == 4)
            {
                curr->edgeWeight5 = cpAB;
            } 
            else 
            {
                curr->edgeWeight6 = cpBA;
            }
           }
        }
    }

    int timesToLoop = cB+1;
    graph[0].distance = 0;
    unvisitedQueue.push(&graph[0]);
    for(unsigned int i = 1; i < graph.size(); i++)
    {
        unvisitedQueue.push(&graph[i]);
    }

    //dijkstra's algorithm
    while(timesToLoop != 0)
    { 
        while(!unvisitedQueue.empty())
        {
            vertex* curr = unvisitedQueue.front();
            unvisitedQueue.pop();
            for(unsigned int i = 0; i < 6; i++)
            {
                if(i == 0)
                {
                    altPathDistance = curr->distance + curr->edgeWeight1;
                } 
                else if (i == 1)
                {
                    altPathDistance = curr->distance + curr->edgeWeight2;
                } 
                else if (i == 2)
                {
                    altPathDistance = curr->distance + curr->edgeWeight3;
                } 
                else if (i == 3)
                {
                    altPathDistance = curr->distance + curr->edgeWeight4;
                } 
                else if(i == 4)
                {
                    altPathDistance = curr->distance + curr->edgeWeight5;
                } 
                else if(i == 5){
                    altPathDistance = curr->distance + curr->edgeWeight6;
                }
            
                if(altPathDistance < graph[curr->newStateAfterAction[i]].distance)
                {
                    graph[curr->newStateAfterAction[i]].distance = altPathDistance;
                    graph[curr->newStateAfterAction[i]].prev = curr;
                }
            }
        }
        graph[0].distance = 0;
        unvisitedQueue.push(&graph[0]);
        for(unsigned int i = 1; i < graph.size(); i++)
        {
            unvisitedQueue.push(&graph[i]);
        }
        timesToLoop -= 1;
    }
    
    stack<vertex*> unvisitedStack;
    int indexOfSolution = 0;
    // find solution index
    for(unsigned int i = 0; i < graph.size(); i++)
    {
        if(graph[i].A == 0 && graph[i].B == N)
        {
            indexOfSolution = i;
        }
    }
    vertex* currVertex = &graph[indexOfSolution];
    
    while(currVertex != 0)
    {
        unvisitedStack.push(currVertex);
        currVertex = currVertex->prev;
    }

    while(unvisitedStack.size() - 1 != 0)
    {
        currVertex = unvisitedStack.top();
        unvisitedStack.pop();

        vertex* prior = unvisitedStack.top();
        if(&graph[currVertex->newStateAfterAction[0]] == prior)
        {
            solutionString << "fill A" << endl;
        }
        if(&graph[currVertex->newStateAfterAction[1]] == prior)
        {
            solutionString << "fill B" << endl;
        }
        if(&graph[currVertex->newStateAfterAction[2]] == prior)
        {
            solutionString << "empty A" << endl;
        }
        if(&graph[currVertex->newStateAfterAction[3]] == prior)
        {
            solutionString << "empty B" << endl;
        }
        if(&graph[currVertex->newStateAfterAction[4]] == prior)
        {
            solutionString << "pour A B" << endl;
        }
        if(&graph[currVertex->newStateAfterAction[5]] == prior)
        {
            solutionString << "pour B A" << endl;
        }
    }
    solutionString << "success " << graph[indexOfSolution].distance;
    solution = solutionString.str();

    return 1;
}
