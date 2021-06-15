//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Matus Tvarozny <xtvaro00@stud.fit.vutbr.cz>
// $Date:       $2021-02-26
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Matus Tvarozny
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()     
{
    Element_t *temp = GetHead();
    while(temp != NULL){
        Element_t *tempCurr = temp;
        temp = temp->pNext;
        delete tempCurr;
    }
    
}

void PriorityQueue::Insert(int value)
{
    Element_t *temp = GetHead();
    Element_t *tempPrev;
    Element_t *inserted = new Element_t();
    inserted->value = value;
    if(temp != NULL){
        if(value > temp->value){                    //bigger than head
            inserted->pNext = temp;
            m_pHead = inserted;
            return;
        }
        while(temp != NULL){                        //other options
            if(temp->value == value){
                Element_t *temp2 = temp->pNext;
                temp->pNext = inserted;
                inserted->pNext = temp2;
                delete temp2;
                return;
            }else if(temp->value < value){
                tempPrev->pNext = inserted;
                inserted->pNext = temp;
                return;
            }
            tempPrev = temp;
            temp = temp->pNext;
        }
        tempPrev->pNext = inserted;
        inserted->pNext = NULL;
    }else{                                          //one&only
        m_pHead = inserted;
        inserted->pNext = NULL;
    }
    
}

bool PriorityQueue::Remove(int value)
{
    Element_t *temp = Find(value);
    size_t length = Length();
    if(temp != NULL){
        if(temp->value == GetHead()->value && length != 1){             //first
            m_pHead = temp->pNext;
            delete temp;
            return true;
        }
        if(length == 1){                                                //one&only
            delete temp;
            m_pHead = NULL;
            return true;
        }                            
        if(temp->pNext == NULL && length != 1){                         //last
            Element_t *tempPrev;
            Element_t *tempCurr = GetHead();
            while(tempCurr != NULL){
                if(tempCurr->value == value){
                    delete tempCurr;
                    tempPrev->pNext = NULL;
                    return true;
                }
                tempPrev = tempCurr;
                tempCurr = tempCurr->pNext;
            }
        }    
        if(temp->pNext != NULL){                                        //middle-check
            Element_t *tempPrev;
            Element_t *tempCurr = GetHead();
            while(tempCurr != NULL){
                if(tempCurr->value == value){
                    tempPrev->pNext = tempCurr->pNext;
                    delete tempCurr;
                    return true;
                }
                tempPrev = tempCurr;
                tempCurr = tempCurr->pNext;
            }
        }                           
    }else{
        return false;
    }
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t *temp = GetHead();
    while(temp != NULL){
        if(temp->value == value){
            return temp;
        }
        temp = temp->pNext;
    }
    return NULL;
}

size_t PriorityQueue::Length()
{
	size_t counter = 0;
    Element_t *temp = GetHead();
    while (temp != NULL)
    {
        counter+=1;
        temp = temp->pNext;
    }
    return counter;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
