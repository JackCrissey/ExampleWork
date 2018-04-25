//
//  Graph.cpp
//  Graph
//
//  Created by Jack Crissey on 2/18/17.
//  Copyright © 2017 Jack Crissey. All rights reserved.
//

#include "Graph.h"
#include <iostream>
using namespace std;
Graph::Graph(int n) //graph constructor
{
    m_size=n;
   if(m_size <= 0)
   {
       throw out_of_range("Graph::Graph(int n) : index is out of range");
       
   }
    else if(m_size > 0)
    {
        m_adjLists = new AdjListNode*[m_size];
        for(int x =0; x < m_size; x++)
        {
            m_adjLists[x] = new AdjListNode;
        }
    }
}

Graph::Graph(const Graph& G)
{
    m_adjLists = G.m_adjLists; // copy
    AdjListNode **holder = new AdjListNode*[G.m_size];
    holder = m_adjLists;
    AdjListNode **temp = new AdjListNode*[G.m_size];
    for(int x =0; x<G.m_size; x++)
    {
        temp[x] = new AdjListNode;
        while(holder[x] -> next != NULL)
        {
            temp[x]->next = holder[x]->next;
        }
    }
}

int Graph::size()
{
    return m_size;
}

Graph::~Graph()
{
    AdjListNode *head = new AdjListNode;
    AdjListNode *clean = new AdjListNode;
    for(int x = 0; x<m_size;x++)
    {
        clean = m_adjLists[x];
        head = clean->next;
        delete clean;
        while(head -> next != NULL)
        {
            clean = head;
            head = head->next;
            delete clean;
        }
        delete head;
    }
}

const Graph& Graph::operator= (const Graph& rhs)
{
    return rhs;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0)
    {
        throw out_of_range(" index is out of range");
    }
    AdjListNode *temp = new AdjListNode();
    AdjListNode *temp2 = new AdjListNode();
    temp->m_vertex = v;
    temp2->m_vertex = u;
    AdjListNode *arrayPoint1 = new AdjListNode();
    AdjListNode *arrayPoint2 = new AdjListNode();
    
    arrayPoint1 = m_adjLists[u];
    arrayPoint2 = m_adjLists[v];
    
    if(arrayPoint1->next == NULL)
    {
        arrayPoint1 -> next = temp;
    }
    else
    {
        while(arrayPoint1->next != NULL)
        {
            arrayPoint1 = arrayPoint1->next;
        }
        arrayPoint1 -> next = temp;
    }
   
    if(arrayPoint2->next == NULL)
    {
        arrayPoint2 -> next = temp2;
    }
    else
    {
        while(arrayPoint2->next != NULL)
        {
            arrayPoint2 = arrayPoint2->next;
        }
        arrayPoint2 -> next = temp2;
    }
}

void Graph::dump()
{
    //show graph
    int x =0;
    while(x<size())
    {
        cout<<x<<": ";
        AdjListNode *temp = new AdjListNode();
        temp =this->m_adjLists[x] -> next;
        while(temp -> next != NULL)
        {
            cout<<temp -> m_vertex<<", ";
            temp = temp ->next;
        }
        cout<<temp -> m_vertex<<", ";
        cout<<endl;
        x++;
    }
    
}

Graph::EgIterator::EgIterator(Graph *Gptr, bool isEnd)
{
    m_Gptr=Gptr;
    m_source = 0;
    if(m_Gptr != NULL)
    {
        m_where = m_Gptr->m_adjLists[m_source]->next;
    }
    if(isEnd == true)
    {
        m_source = m_Gptr->size()-1;
        m_where = m_Gptr->m_adjLists[m_source];
        while(m_where -> next != NULL)
        {
            m_where = m_where -> next;
        }
    }
    
}

bool Graph::EgIterator::operator!= (const EgIterator& rhs)
{
    if(rhs.m_where == this->m_where)
    {
        return false;
    }
    else{
        return true;
    }
}

void Graph::EgIterator::operator++(int dummy)
{
   if(m_where -> next != NULL)
   {
       m_where = m_where ->next;
       if(m_where ->m_vertex < m_source)
       {
           EgIterator::operator++(0);
       }
    }
   else
   {
       if(m_source<m_Gptr->size()-1)
       {
           m_source++;
           m_where= m_Gptr->m_adjLists[m_source];
          EgIterator::operator++(0); 
       }
   }
}

std::pair<int,int> Graph::EgIterator::operator*()
{
    return std::pair<int,int>(m_source, m_where->m_vertex);
}

Graph::EgIterator Graph::egBegin()
{
    return Graph::EgIterator(this, false);
}

Graph::EgIterator Graph::egEnd()
{
    return Graph::EgIterator(this, true);
}

Graph::NbIterator Graph::nbBegin(int n)
{
    return Graph::NbIterator(this, n, false);
}

Graph::NbIterator Graph::nbEnd(int n)
{
    return Graph::NbIterator(this, n, true);
}

Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd)
{
    
    m_Gptr = Gptr;
    m_source = v;
    if(m_Gptr != NULL)
    {
        m_where=m_Gptr->m_adjLists[m_source];
    }
    if(isEnd == true)
    {
        while(m_where -> next != NULL)
        {
            m_where = m_where -> next;
        }
    }
}

bool Graph::NbIterator::operator!= (const NbIterator& rhs)
{
    if(rhs.m_where == this->m_where)
    {
        return false;
    }
    else{
        return true;
    }

}

void Graph::NbIterator::operator++(int dummy)
{
   m_where = m_where->next;
}

int Graph::NbIterator::operator*()
{
   return m_where->next->m_vertex;
}

Graph::AdjListNode::AdjListNode(int v, AdjListNode *ptr)
{
    
}
