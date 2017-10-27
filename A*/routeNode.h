//
// Created by cristian on 23/10/17.
//

#ifndef GPB_NODE_H
#define GPB_NODE_H


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
    std::string getPosition();
    int get_fCost();
    void setType(int type);

};


#endif //GPB_NODE_H
