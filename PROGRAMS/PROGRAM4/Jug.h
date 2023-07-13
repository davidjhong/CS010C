#ifndef JUG_H
#define JUG_H

#include <string>
#include <vector>  
#include <iostream> 
#include <cstdlib>
#include <limits.h>
using namespace std;

// Pat Miller's skeleton for h.
// using graph structure provided by the professor
class Jug {
    // Our graph is made out of vertices.  Each with 6 outedges representing
    // which graph vertex is the result of our six possible actions
    struct vertex {
        int A;
        int B;
        int id;

        int distance = INT_MAX;
        vertex* prev = 0;
        int edgeWeight1 = 0;
        int edgeWeight2 = 0;
        int edgeWeight3 = 0;
        int edgeWeight4 = 0;
        int edgeWeight5 = 0;
        int edgeWeight6 = 0;
        // This is our adjacency list... each vertex can go one of six
        // places for our six possible actions.  Sometimes this is right
        // back to this vertex (e.g. if we are empty (0,0) and we do an
        // emptyA action, we are still empty.  -1 means unset here
        vector<int> newStateAfterAction;
        //vertex(): A(0), B(0), id(0), newStateAfterAction(6,-1), prev(0), distance(0){}
        vertex(int A, int B, int id) : A(A), B(B), id(id), newStateAfterAction(6, -1){}
    };
    private: 
        int cA;
        int cB;
        int N;
        int cfA;
        int cfB;
        int ceA;
        int ceB;
        int cpAB;
        int cpBA;
        // This is the graph we are trying to build.  Each vertex has six
        // outedges that represent the new state AFTER you do a...
        // * fillA
        // * fillB
        // * emptyA
        // * emptyB
        // * pourAToB
        // * pourBToA
        vector<vertex> graph;

        // This looks up an A:B combination in the graph and returns its
        // id (same as its index)
        int findInGraph(int A, int B, vector<int>& unfinishedVertices) {
            // We may already have this combination of A and B.  If so, return it
            for(unsigned int i = 0; i < graph.size(); ++i) {
                if (graph[i].A == A && graph[i].B == B){
                    return i;
                }
            }
            
            int id = graph.size();
            unfinishedVertices.push_back(id);
            //cout << "Add: " << A << "," << B << " at index " << id << endl;
            graph.push_back(vertex(A, B, id));
            return id;
        }
    
    public:
        Jug(int cA, int cB, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) : cA(cA), cB(cB), N(N), cfA(cfA), cfB(cfB),ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {
            // As we build the graph, we want to add in new vertices and we
            // have to remember to set all the outedges. This just keeps
            // track of which ones are not part of the graph
            vector<int> unfinishedNodes;

            // We start by adding the empty jug.  This creates a new vertex
            // and appends it to the graph.  Since we haven't set its six
            // out edges yet, we will make a note of it in the unfinishedNodes
            // stack
            int index = findInGraph(0, 0, unfinishedNodes);
            if(index != 0){
                cout << index;
            }
            // So here, we have one vertex in the graph.  It has an id of 0,
            // and the outedges are all -1 (unset), but it is in the list
            // of unfinishedNodes, so we'll fix that below

            // Now, for each unfinished vertex, we have to add connections that correspond
            // to the new state after doing one of the six actions (so six outedges).
            // Doing this may create new unfinished vertices

            if(!(cA <= 0 || cB <= 0 || N > cB || cB > 1000 || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0)){
            
            while(unfinishedNodes.size() > 0) {

            // Get an unfinished node
                int id = unfinishedNodes.back();
                unfinishedNodes.pop_back();

      
                // This state has a current A and B value
                int A = graph[id].A;
                int B = graph[id].B;
                // State after we fill up the A jug
                int fillA = findInGraph(cA, B, unfinishedNodes);

                // After filling the B jug
                int fillB = findInGraph(A, cB, unfinishedNodes);

                // After emptying the A jug
                int emptyA = findInGraph(0, B, unfinishedNodes);

                // After emptying the B jug
                int emptyB = findInGraph(A, 0, unfinishedNodes);

                // After pouring A into B
                int roomInB = cB - B;
                int poursize = min(A, roomInB);
                int pourAToB = findInGraph(A-poursize, B+poursize, unfinishedNodes);

                // After pouring B into A
                int roomInA = cA - A;
                poursize = min(B, roomInA);
                int pourBToA = findInGraph(A+poursize, B-poursize, unfinishedNodes);

                // Now we can set the six outedges for this vertex
                graph[id].newStateAfterAction[0] = fillA;
                graph[id].newStateAfterAction[1] = fillB;
                graph[id].newStateAfterAction[2] = emptyA;
                graph[id].newStateAfterAction[3] = emptyB;
                graph[id].newStateAfterAction[4] = pourAToB;
                graph[id].newStateAfterAction[5] = pourBToA;

                // The graph may now have some new unfinished vertices in it.
            }
        }
        }

        // Helper for printGraph
        void showState(int i) {
            cout << '\t' << i;
            if (i != -1) {
                cout << '(' << graph[i].A << ',' << graph[i].B << ')';
            }
        }

        // Display the graph in readable form
        void printGraph() {
            cout << "ID\t(A,B)\tfillA\tfillB\temptyA\temptyB\tpourAB\tpourBA" << endl;
            for(const auto& v: graph) {
                cout << v.id << "\t(" << v.A << ',' << v.B << ")";
                showState(v.newStateAfterAction[0]);
                showState(v.newStateAfterAction[1]);
                showState(v.newStateAfterAction[2]);
                showState(v.newStateAfterAction[3]);
                showState(v.newStateAfterAction[4]);
                showState(v.newStateAfterAction[5]);
                cout << endl;
            }
        }
        //~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
};

#endif
