#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <stdlib.h>
#include "A*/linkedList.cpp"

const int mapX=10; // horizontal size of the map
const int mapY=10; // vertical size size of the map
const int obs=10; //Number of obstacles
const int cStr=10;// Straight cost for movement
const int cDiag=14;// Diagonal cost for movement

static routeNode* map[mapX][mapY];
static routeNode* player;
static routeNode* obstacleArray[obs];

static linkedList closedList; // map of closed (tried-out) nodes
static linkedList openList; // map of open (not-yet-tried) nodes
static linkedList routeList;//array of the routeList

using namespace std;

int getDistance(routeNode* start, routeNode* target){
    int dstX = abs(start->xPos - target->xPos);
    int dstY = abs(start->yPos - target->yPos);

    if(dstX > dstY)
        return cDiag*dstY + cStr*(dstX-dstY);

    return (cDiag*dstX + cStr*(dstY-dstX));
}

void retracePath(routeNode* start, routeNode* target){
    routeNode* current = target;

    while(current != start){
        routeList.add_first(current);
        current=current->parent;
    }

}

void pathFinding(routeNode *start, routeNode *target){
    closedList = linkedList();
    openList = linkedList();

    openList.add_first(start);
    cout << "new list created" << endl;
    cout << openList.getList() << endl;

    while(openList.size>0){
        routeNode* current = openList.first;
        for(int i=1;i<openList.size;i++){
            if (openList.getNode(i)->get_fCost() < current->get_fCost() || openList.getNode(i)->get_fCost() == current->get_fCost()
                    && openList.getNode(i)->hCost <current->hCost){
                current = openList.getNode(i);
            }
        }

        openList.deleteNode(current);
        current->next=NULL;
        closedList.add_end(current);

        if (current == target){
            retracePath(start,target);
            return;
        }

        for (int x=-1;x<=1;x++) {
            for (int y = -1; y <= 1; y++) {
                if (x == 0 && y == 0) {
                    continue;
                } else {
                    int checkX = current->xPos + x;
                    int checkY = current->yPos + y;

                    if (checkX >= 0 && checkX < mapX && checkY >= 0 && checkY < mapY) {
                        routeNode *neighbour = map[checkX][checkY];
                        if (neighbour->type == 1 || neighbour->type == 3 || closedList.contains(neighbour)) {
                            continue;
                        } else {
                            int newMovementCostToNeighbour = current->gCost + getDistance(current, neighbour);

                            if (newMovementCostToNeighbour < neighbour->gCost || !openList.contains(neighbour)) {
                                neighbour->gCost = newMovementCostToNeighbour;
                                neighbour->hCost = getDistance(neighbour, target);
                                neighbour->parent = current;

                                if (!openList.contains(neighbour)) {
                                    openList.add_end(neighbour);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void startTrajectory(routeNode* startNode,routeNode* targetNode){
    // get the routeList
    pathFinding(startNode, targetNode);
    if (routeList.size == 0) {
        cout << "An empty routeList generated!" << endl;
        exit(1);
    }

    cout << "Route:" << endl;
    cout << routeList.getList() << endl << endl;

    // follow the routeList on the map and display it
    if (routeList.size > 0) {
        routeNode *temp = routeList.first;
        while (temp != NULL) {
            if (temp->next == NULL) {

            } else {
                temp->type = 4;
            }

            temp = temp->next;
        }
    }

    // display the map with the routeList
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++)
            if (map[x][y]->type == 0)
                cout << "\u2588";
            else if (map[x][y]->type == 3)
                cout << "\033[1;31m\u2591\033[0m";//obstacle with red color
            else if (map[x][y]->type == 1)
                cout << "\033[1;32m\u2593\033[0m";//startNode with green color
            else if (map[x][y]->type == 4)
                cout << "\033[1;36m\u2588\033[0m";//routeList
            else if (map[x][y]->type == 2)
                cout << "\033[1;34m\u2593\033[0m";//targetNode with blue color
            else if (map[x][y]->type == 5)
                cout << "\033[1;33m\u2593\033[0m";//player with yellow color
        cout << endl;
    }
}



int main() {
    srand(time(NULL));
    routeList = linkedList();

    // create empty map
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            map[x][y] = new routeNode();
            map[x][y]->setPosition(x, y);
        }
    }

    // randomly select startNode and targetNode locations
    int xA, yA, xB, yB;
    xA = 0, yA = rand() % (mapY - 1), xB = (mapX - 1), yB = rand() % (mapY - 1);
    //Define the startNode and targetNode nodes
    routeNode *startNode = map[xA][yA];
    startNode->setType(1);
    routeNode *targetNode = map[xB][yB];
    targetNode->setType(2);
    player = startNode;

    // fill out the map matrix with random obstacles
    int i = 0;
    while (i < obs) {
        int x = rand() % (mapX - 1) + 0;
        int y = rand() % (mapY - 1) + 0;

        if (map[x][y]->type == 0) {
            map[x][y]->setType(3);
            obstacleArray[i]=map[x][y];
            i++;
        }
    }

    cout << "Map Size (X,Y): " << mapX << "," << mapY << endl;
    cout << "Start: " << xA << "," << yA << endl;
    cout << "Finish: " << xB << "," << yB << endl;

    startTrajectory(startNode,targetNode);
    /*

    cout << "antes del while"<<endl;
    while(player->xPos != targetNode->xPos && player->yPos != targetNode->yPos){
        player = routeList.first;
        startTrajectory(player,targetNode);
    }
    cout << "despues del while"<<endl;
     */



    return(0);
}
