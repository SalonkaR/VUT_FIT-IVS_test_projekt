//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Matus Tvarozny <xtvaro00@stud.fit.vutbr.cz>
// $Date:       $2021-02-23
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Matus Tvarozny
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree bintree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp(){
        bintree.InsertNode(1);
        bintree.InsertNode(2);
        bintree.InsertNode(3);
        bintree.InsertNode(4);
        bintree.InsertNode(5);
    }

    BinaryTree bintree;
};

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp(){
        bintree.InsertNode(10);
        bintree.InsertNode(1);
        bintree.InsertNode(5);
        bintree.InsertNode(2);
        bintree.InsertNode(9);
        bintree.InsertNode(4);
        bintree.InsertNode(3);
        bintree.InsertNode(7);
        bintree.InsertNode(8);
        bintree.InsertNode(11);
        bintree.InsertNode(6);
    }

    BinaryTree bintree;
};

TEST_F(EmptyTree, InsertNode){
    //valid 
    EXPECT_TRUE(bintree.InsertNode(5).first);
    EXPECT_EQ(bintree.GetRoot()->key, 5);

    EXPECT_TRUE(bintree.InsertNode(1).first);
    EXPECT_TRUE(bintree.FindNode(1) != NULL);

    EXPECT_TRUE(bintree.InsertNode(7).first);
    EXPECT_TRUE(bintree.FindNode(7) != NULL);

    //invalid(already inserted)
    EXPECT_FALSE(bintree.InsertNode(5).first);
    EXPECT_FALSE(bintree.InsertNode(7).first);
    EXPECT_FALSE(bintree.InsertNode(1).first);
}

TEST_F(EmptyTree, DeleteNode){
    //invalid nodes(tree is empty)
    EXPECT_FALSE(bintree.DeleteNode(1));
    EXPECT_TRUE(bintree.FindNode(1) == NULL);
    
    EXPECT_FALSE(bintree.DeleteNode(7));
    EXPECT_TRUE(bintree.FindNode(7) == NULL);

    EXPECT_TRUE(bintree.GetRoot() == NULL);    
}

TEST_F(EmptyTree, FindNode){
    //tree is empty
    EXPECT_TRUE(bintree.FindNode(1) == NULL);
    EXPECT_TRUE(bintree.FindNode(7) == NULL);
}

TEST_F(NonEmptyTree, InsertNode){
    //valid
    EXPECT_TRUE(bintree.InsertNode(6).first);
    EXPECT_TRUE(bintree.FindNode(6) != NULL);
    
    EXPECT_TRUE(bintree.InsertNode(7).first);
    EXPECT_TRUE(bintree.FindNode(7) != NULL);
    
    //invalid(already inserted)
    EXPECT_FALSE(bintree.InsertNode(2).first);
    EXPECT_FALSE(bintree.InsertNode(5).first);
}

TEST_F(NonEmptyTree, DeleteNode){
    //valid nodes
    EXPECT_TRUE(bintree.DeleteNode(3));
    EXPECT_TRUE(bintree.FindNode(3) == NULL);

    EXPECT_TRUE(bintree.DeleteNode(4));
    EXPECT_TRUE(bintree.FindNode(4) == NULL);
    
    //invalid nodes
    EXPECT_FALSE(bintree.DeleteNode(3));
    EXPECT_FALSE(bintree.DeleteNode(6));
}

TEST_F(NonEmptyTree, FindNode){
    //valid nodes
    EXPECT_TRUE(bintree.FindNode(1) != NULL);
    EXPECT_TRUE(bintree.FindNode(5) != NULL);
    
    //invalid nodes
    EXPECT_FALSE(bintree.FindNode(0) != NULL);
    EXPECT_FALSE(bintree.FindNode(6) != NULL);
}

TEST_F(TreeAxioms, Axiom1){
    std::vector<BinaryTree::Node_t*> outLeafNodes;
    bintree.GetLeafNodes(outLeafNodes);
    for(int i = 0; i < outLeafNodes.size(); i++){
        EXPECT_EQ(outLeafNodes[i]->color, BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2){
    std::vector<BinaryTree::Node_t*> outNonLeafNodes;
    bintree.GetNonLeafNodes(outNonLeafNodes);
    for(int i = 0; i < outNonLeafNodes.size(); i++){
        if(outNonLeafNodes[i]->color, RED){
            EXPECT_EQ(outNonLeafNodes[i]->pLeft->color, BLACK);
            EXPECT_EQ(outNonLeafNodes[i]->pRight->color, BLACK);
        }
    }
}

TEST_F(TreeAxioms, Axiom3){
    std::vector<BinaryTree::Node_t*> outLeafNodes;
    bintree.GetLeafNodes(outLeafNodes);
    std::vector<int> blackCounterList;
    for(int i = 0; i < outLeafNodes.size(); i++){
        Node_t* temp = outLeafNodes[i];
        int blackCounter = 0;
        while(temp){
            if(temp->color == BLACK){
                blackCounter++;
            }
            temp = temp->pParent;
        }
        blackCounterList.push_back(blackCounter);
    }
    for(int i = 0; i < blackCounterList.size()-1; i++){
        EXPECT_EQ(blackCounterList[i], blackCounterList[i+1]);
    }
}
/*** Konec souboru black_box_tests.cpp ***/

