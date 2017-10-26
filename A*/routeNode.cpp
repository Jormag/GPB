//
// Created by cristian on 23/10/17.
//
#include <sstream>
#include "routeNode.h"

using namespace std;

routeNode::routeNode() {
    xPos=0;
    yPos=0;
    next=NULL;
    parent=NULL;
    gCost=0;
    hCost=0;
    type=0;
}

void routeNode::setPosition(int x, int y) {
    this->xPos =x;
    this->yPos =y;
}

void routeNode::setCost(int g, int h){
    this->gCost = g;
    this->hCost = h;
}

string routeNode::getPosition()
{
    ostringstream os;
    os << "[" << this->xPos << "," << this->yPos << "]";
    return os.str();
}

int routeNode::get_fCost() {
    return this->gCost+this->hCost;
}

void routeNode::setType(int type){
    this->type = type;
}

