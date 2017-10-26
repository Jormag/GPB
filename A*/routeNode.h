//
// Created by cristian on 23/10/17.
//

#ifndef GPB_NODE_H
#define GPB_NODE_H

#include <iostream>
#include <vector>

using namespace std;

class routeNode {
public:
    routeNode* next;
    routeNode* parent;
    int xPos;
    int yPos;
    int gCost;
    int hCost;
    int type;

    routeNode();

    void setPosition(int, int);
    void setCost(int,int);
    string getPosition();
    int get_fCost();
    void setType(int);
    
};


#endif //GPB_NODE_H
