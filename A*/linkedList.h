//
// Created by cristian on 23/10/17.
//

#ifndef GPB_LINKEDLIST_H
#define GPB_LINKEDLIST_H

#include "routeNode.cpp"

using namespace std;

class linkedList {
public:
     routeNode* first;
    int size;

    linkedList();

    void add_first(routeNode*);
    void add_end(routeNode*);

    void deleteNode(routeNode*);

    string getList();

    bool contains(routeNode *);

    routeNode* getNode(int);
    routeNode* returnLowestCost();

    void reset();
};


#endif //GPB_LINKEDLIST_H
