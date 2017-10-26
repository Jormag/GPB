//
// Created by cristian on 23/10/17.
//

#include <sstream>
#include "linkedList.h"


using namespace std;

// Constructor por defecto
linkedList::linkedList()
{
    size = 0;
    first = NULL;
}

// Insertar al inicio
void linkedList::add_first(routeNode* new_node)
{
    routeNode* temp = first;

    if (size==0) {
        first = new_node;
    } else {
        new_node->next = temp;
        this->first = new_node;
    }
    size++;
}

// Insertar al final
void linkedList::add_end(routeNode* new_node)
{
    routeNode* temp = first;

    if (size==0) {
        first = new_node;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    size++;
}


// Eliminar por position del nodo
void linkedList::deleteNode(routeNode* pos)
{
    routeNode* temp = first;
    routeNode* temp2 = first;

    if (!contains(pos)){
        cout << "The node is not in the list" << endl;
    }else {
        if (temp == pos) {
            first = temp->next;
        } else {
            while (temp !=NULL) {
                if (temp == pos){
                    temp2->next = temp->next;
                }
                temp2=temp;
                temp = temp->next;
            }
        }
        size--;
    }
}


// retornar la Lista
string linkedList::getList()
{
    routeNode* temp = first;
    ostringstream os;

    if (first == NULL) {
        os << "" << endl;
    } else {
        while (temp != NULL) {
            if (temp->next == NULL){
                os << temp->getPosition() <<endl;
            }else{
                os << temp->getPosition() << "-> ";
            }
            temp = temp->next;
        }
    }
    return os.str();
}

bool linkedList::contains(routeNode *node) {
    bool result = false;
    if(this->size>0){
        routeNode* temp = first;
        while(temp!=NULL){
            if(temp==node){
                result=true;
                break;
            }else{
                temp=temp->next;
            }
        }
    }
    return result;
}

routeNode* linkedList::getNode(int pos){
    routeNode* temp = first;
    if(this->size>0) {
        if (pos<0 || pos>this->size){
        }else {
            int index = 0;
            while (index < pos) {
                temp = temp->next;
                index++;
            }
        }
    }
    return temp;
}


routeNode* linkedList::returnLowestCost() {
    routeNode* temp = first;
    routeNode* temp2 = first;

    if(this->size>0){
        while(temp!=NULL){
            if(temp->get_fCost()<temp2->get_fCost()){
                temp2 = temp;
                break;
            }else{
                temp=temp->next;
            }
        }
    }
    return temp2;
}
void linkedList::reset(){
    this->size = 0;
    this->first = NULL;
}

