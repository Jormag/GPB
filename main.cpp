#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

#include "A*/linkedList.cpp"

const int mapX=10; // horizontal size of the map
const int mapY=10; // vertical size size of the map
const int asteroids=10; //Number of asteroids
const int enemyShips=5; //Number of enemy ships

const int cStr=10;// Straight cost for movement
const int cDiag=14;// Diagonal cost for movement


static routeNode* map[mapX][mapY];
static routeNode* asteroidsArray[asteroids];
static routeNode* enemiesArray[enemyShips];


static linkedList closedList; // map of closed (tried-out) nodes
static linkedList openList; // map of open (not-yet-tried) nodes
static linkedList routeList;//array of the routeList


using namespace std;

/**
 *
 * @param start
 * @param target
 * calculate the h_cost depending of the movements between the start pos and the target pos and
 * take the low value and multiply it for the diagonal cost and addition the multiply of the straight cost and the difference of the distances
 * @return the h_cost
 */
int getDistance(routeNode* start, routeNode* target){
    int dstX = abs(start->xPos - target->xPos);
    int dstY = abs(start->yPos - target->yPos);

    if(dstX > dstY)
        return cDiag*dstY + cStr*(dstX-dstY);

    return (cDiag*dstX + cStr*(dstY-dstX));
}
/**
 *
 * @param start
 * @param target
 * Asign the parent nodes of the routeList
 */
void retracePath(routeNode* start, routeNode* target){
    routeNode* current = target;

    while(current != start){
        routeList.add_first(current);
        current=current->parent;
    }
}
/**
 *
 * @param start
 * @param target
 * first prepare the map for multiple runs of the a_star
 * next calculate the cost of the neightbours node and add then to the open list if is a valid node
 * when find the target node stops the function
 */
void a_star(routeNode *start, routeNode *target){
    //prepare the map for multiple runs of the a_star
    closedList = linkedList();
    openList = linkedList();
    routeList = linkedList();

    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            map[x][y]->next = NULL;
            map[x][y]->type=0;
            map[x][y]->parent = NULL;
        }
    }


    start->setType(1);
    target->setType(2);

    for (int i=0;i<enemyShips;i++){
        enemiesArray[i]->setType(4);
    }

    // fill out the map matrix with random obstacles
    for(int i=0;i<asteroids;i++){
        int x = rand()% (mapX - 1) + 0;
        int y = rand()% (mapY - 1) + 0;

        if (map[x][y]->type == 0) {
            map[x][y]->setType(3);
            asteroidsArray[i]=map[x][y];
        }else{
            i--;
        }
    }

    for (int i=0;i<asteroids;i++){
        asteroidsArray[i]->setType(3);
    }


    //begin of the a_star
    openList.add_first(start);
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
                        if (neighbour->type == 1 ||neighbour->type == 3|| neighbour->type == 4||closedList.contains(neighbour)) {
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
/**
 * Displays the map on console
 */
void displayMap(){
    // display the map with the routeList
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            if (map[x][y]->type == 0)
                cout << "\u2588";
            else if (map[x][y]->type == 1)
                cout << "\033[1;32m\u2593\033[0m";//startNode with green color
            else if (map[x][y]->type == 2)
                cout << "\033[1;34m\u2593\033[0m";//targetNode with blue color
            else if (map[x][y]->type == 3)
                cout << "\033[1;31m\u2591\033[0m";//asteroid with red color
            else if (map[x][y]->type == 4)
                cout << "\033[1;35m\u2593\033[0m";//enemies with magenta color
            else if (map[x][y]->type == 5)
                cout << "\033[1;36m\u2588\033[0m";//routeList
        }
        cout << endl;
    }
}

/**
 *
 * @param startNode
 * @param targetNode
 * does a call to the funtion a_star and calculate the routelist to the targetNode
 * follows the route list and asign the node as a routeNode
 */
void pathFinding(routeNode *startNode, routeNode *targetNode){
    // get the routeList
    a_star(startNode, targetNode);
    if (routeList.size == 0 && startNode!= targetNode) {
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
                temp->type = 5;
            }
            temp = temp->next;
        }
    }
}

int main() {
    //variables
    int HEIGHT = 1000;
    int WIDTH = 1000;

    //allegro variables
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_BITMAP* playerImage=NULL;
    ALLEGRO_BITMAP* background=NULL;
    ALLEGRO_BITMAP* base=NULL;
    ALLEGRO_COLOR black = al_map_rgb(0,0,0);
    ALLEGRO_BITMAP* asteroidsImages[asteroids];
    ALLEGRO_BITMAP* enemiesImages[asteroids];

    //program init
    if(!al_init()){
        al_show_native_message_box(NULL,NULL,NULL, "Could not initialize",NULL,ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    display = al_create_display(HEIGHT,WIDTH);
    al_set_new_display_flags(ALLEGRO_FRAMELESS);
    al_set_window_position(display,200,100);
    al_set_window_title(display,"Main Menu");

    if (!display){
        al_show_native_message_box(display,"Sample Title", "Display Settings","Display Window was not created",NULL,ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //addon init
    al_install_keyboard();
    al_init_image_addon();

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue,al_get_keyboard_event_source());

    playerImage = al_load_bitmap("/home/cristian/CLionProjects/GPB/A*/MillenniumFalcon.png");
    background = al_load_bitmap("/home/cristian/CLionProjects/GPB/A*/Space.png");
    base = al_load_bitmap("/home/cristian/CLionProjects/GPB/A*/Base.png");

    for (int i=0;i<asteroids;i++){
       asteroidsImages[i] = al_load_bitmap("/home/cristian/CLionProjects/GPB/A*/asteroids.png");
    }
    for (int i=0;i<enemyShips;i++){
        enemiesImages[i] = al_load_bitmap("/home/cristian/CLionProjects/GPB/A*/TIEFighter.png");
    }

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
    routeNode* player = startNode;


    // fill out the map matrix with random obstacles
    for(int i=0;i<asteroids;i++){
        int x = rand()% (mapX - 1) + 0;
        int y = rand()% (mapY - 1) + 0;

        if (map[x][y]->type == 0) {
            map[x][y]->setType(3);
            asteroidsArray[i]=map[x][y];
        }else{
            i--;
        }
    }

    // fill out the map matrix with random enemies
    for(int i=0;i<enemyShips;i++){
        int x = rand()% (mapX - 1) + 0;
        int y = rand()% (mapY - 1) + 0;

        if (map[x][y]->type == 0) {
            map[x][y]->setType(4);
            enemiesArray[i]=map[x][y];
        }else{
            i--;
        }
    }

    int px = startNode->xPos*100;
    int py = startNode->yPos*100;
    bool inPos = true;
    while(targetNode->parent!=player || inPos!= true){
        if (inPos == true) {
            if (routeList.size == 0) {
                player = startNode;
            } else {
                player = routeList.first;
            }
            pathFinding(player, targetNode);
            displayMap();
        }
        if(px > player->xPos*100){
            inPos = false;
            px-=5;
        }
        if(px < player->xPos*100){
            inPos = false;
            px+=5;
        }

        if(py > player->yPos*100){
            inPos = false;
            py-=5;
        }
        if (py < player->yPos*100){
            inPos = false;
            py+=5;
        }
        if (px == player->xPos*100 && py == player->yPos*100){
            inPos = true;
        }

        al_draw_bitmap(background,0,0,0);

        //al_draw_bitmap(playerImage,(player->xPos)*100, (player->yPos)*100,0);
        al_draw_bitmap(playerImage,px+20/2, py+20/2,0);

        al_draw_bitmap(base,(targetNode->xPos)*100, (targetNode->yPos)*100,0);
        for(int i=0;i<asteroids;i++){
            al_draw_bitmap(asteroidsImages[i],(asteroidsArray[i]->xPos)*100+20/2,(asteroidsArray[i]->yPos)*100+20/2,0);
        }
        for(int i=0;i<enemyShips;i++){
            al_draw_bitmap(enemiesImages[i],(enemiesArray[i]->xPos)*100+20/2,(enemiesArray[i]->yPos)*100+20/2,0);
        }
        al_flip_display();
        al_clear_to_color(black);
        al_rest(0.1);

    }
    al_show_native_message_box(display,"Program State", "Successful","The Millennium Falcon arrived to the rebel base",NULL,ALLEGRO_MESSAGEBOX_WARN);
    cout << "Arrived to the target node" << endl;

    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(playerImage);
    al_destroy_bitmap(background);
    al_destroy_display(display);

    for(int i=0;i<asteroids;i++){
        al_destroy_bitmap(asteroidsImages[i]);
    }
    for(int i=0;i<enemyShips;i++){
        al_destroy_bitmap(enemiesImages[i]);
    }


    return(0);

    //comando para compilar
    //gcc main.cpp -o main `pkg-config --cflags --libs allegro-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_image-5.0` -lstdc++
}
