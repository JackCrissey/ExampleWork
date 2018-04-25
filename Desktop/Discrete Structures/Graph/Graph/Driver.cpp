//
//  Driver.cpp
//  Graph
//
//  Created by Jack Crissey on 2/18/17.
//  Copyright © 2017 Jack Crissey. All rights reserved.
//

#include <iostream>
#include <utility>
using namespace std ;

#include "Graph.h"

int main() {
    
    // G has 9 vertices the are numbered 0 through 8
    Graph G(9) ;
    // adding edges
    G.addEdge(3,4) ;
    G.addEdge(8,7) ;
    G.addEdge(7,6) ;
    G.addEdge(6,5) ;
    G.addEdge(5,4) ;
    G.addEdge(8,4) ;
    G.addEdge(7,1) ;
    G.addEdge(1,4) ;
    G.addEdge(0,7) ;
    G.addEdge(0,4) ;
    G.addEdge(6,1) ;
    G.addEdge(1,8) ;
    G.addEdge(2,5) ;
    
    
    // dumping out the data structure
    G.dump();
    
    // Test neighboring iterator
    Graph::NbIterator nit ;
    
    cout << "\nThe neighbors of vertex 6 are:\n" ;
    for (nit = G.nbBegin(6); nit != G.nbEnd(6) ; nit++)
    {
        cout << *nit << " " ;
    }
    cout << endl ;
    
    //Adding another edge to the list
    G.addEdge(3,2);
    G.addEdge(7,5);
   
    cout << "\nThe neighbors of vertex 3 are:\n" ;
    for (nit = G.nbBegin(3); nit != G.nbEnd(3) ; nit++)
    {
        cout << *nit << " " ;
    }
    cout << endl ;
    
    // Test edge iterator
    //
    Graph::EgIterator eit ;
    pair<int,int> edge ;
    
    cout << "\nThe edges in the graph are:\n" ;
    for (eit = G.egBegin() ; eit != G.egEnd() ; eit++)
    {
        edge = *eit ; // retreaves the current edge
        
        // the two data members of a pair are first and second
        //
        cout << "(" << edge.first << ", " << edge.second << ") " ;
        
    }
    cout << endl ;
}
