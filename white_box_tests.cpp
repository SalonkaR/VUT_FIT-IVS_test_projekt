//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Matus Tvarozny <xtvaro00@stud.fit.vutbr.cz>
// $Date:       $2021-02-27
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Matus Tvarozny
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

#include <vector>
#include <stdio.h>

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class NonEmptyMatrix : public ::testing::Test
{
protected:
    virtual void SetUp() {
        matrix2x2.set(std::vector<std::vector<double>>{{1,2},{3,4}});
        matrix1x4.set(std::vector<std::vector<double>>{{1,2,3,4}});
        matrix3x2.set(std::vector<std::vector<double>>{{1,2},{3,4},{5,6}});
        matrix3x3.set(std::vector<std::vector<double>>{{1,2,3},{4,5,6},{7,8,9}});
        matrix4x4.set(std::vector<std::vector<double>>{{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}});

        matrix1x1_2.set(std::vector<std::vector<double>>{{1}});
        matrix2x2_2.set(std::vector<std::vector<double>>{{5,8},{1,3}});
        matrix1x4_2.set(std::vector<std::vector<double>>{{5,6,3,2}});
        matrix3x2_2.set(std::vector<std::vector<double>>{{4,3},{4,4},{5,7}});
        matrix3x3_2.set(std::vector<std::vector<double>>{{3,3,3},{6,6,6},{8,8,8}});
        matrix4x4_2.set(std::vector<std::vector<double>>{{1,2,3,3},{5,5,9,8},{9,11,10,12},{13,15,15,10}});
    }
    Matrix matrix1x1 = Matrix(1,1);
    Matrix matrix2x2 = Matrix(2,2);
    Matrix matrix1x4 = Matrix(1,4);
    Matrix matrix3x2 = Matrix(3,2);
    Matrix matrix3x3 = Matrix(3,3);
    Matrix matrix4x4 = Matrix(4,4);

    Matrix matrix1x1_2 = Matrix(1,1);
    Matrix matrix2x2_2 = Matrix(2,2);
    Matrix matrix1x4_2 = Matrix(1,4);
    Matrix matrix3x2_2 = Matrix(3,2);
    Matrix matrix3x3_2 = Matrix(3,3);
    Matrix matrix4x4_2 = Matrix(4,4);    
};


TEST_F(NonEmptyMatrix, Set){
    //valid index
    EXPECT_TRUE(matrix1x1.set(0,0,1));
    EXPECT_TRUE(matrix2x2.set(1,1,4));
    EXPECT_TRUE(matrix1x4.set(0,1,2));
    EXPECT_TRUE(matrix3x2.set(2,1,6));
    EXPECT_TRUE(matrix3x3.set(1,1,5));
    EXPECT_TRUE(matrix4x4.set(3,3,16));
    //invalid index
    EXPECT_FALSE(matrix1x1.set(10,10,0));
    EXPECT_FALSE(matrix2x2.set(10,10,0));
    EXPECT_FALSE(matrix1x4.set(10,10,0));
    EXPECT_FALSE(matrix3x2.set(10,10,0));
    EXPECT_FALSE(matrix3x3.set(10,10,0));
    EXPECT_FALSE(matrix4x4.set(10,10,0));
    EXPECT_FALSE(matrix2x2_2.set(std::vector<std::vector<double>>{{5,8,9}}));
    EXPECT_FALSE(matrix3x3.set(std::vector<std::vector<double>>{{5,8,9,10},{2,4}}));
    EXPECT_FALSE(matrix1x1.set(std::vector<std::vector<double>>{{5},{2,4},{12,23,23}}));
    //invalid size
    EXPECT_ANY_THROW(Matrix matrix_invalid = Matrix(0,0));
    EXPECT_ANY_THROW(Matrix matrix_invalid = Matrix(1,0));
    EXPECT_ANY_THROW(Matrix matrix_invalid = Matrix(0,5));
    
}

TEST_F(NonEmptyMatrix, Get){
    //correct
    EXPECT_EQ(matrix1x1.get(0,0), 0);
    EXPECT_EQ(matrix2x2.get(0,1), 2);
    EXPECT_EQ(matrix1x4.get(0,3), 4);
    EXPECT_EQ(matrix3x2.get(2,0), 5);
    EXPECT_EQ(matrix3x3.get(2,2), 9);
    EXPECT_EQ(matrix4x4.get(2,3), 12);
    //incorrect
    EXPECT_NE(matrix1x1.get(0,0), 1);
    EXPECT_NE(matrix2x2.get(0,1), 3);
    EXPECT_NE(matrix1x4.get(0,3), 3);
    EXPECT_NE(matrix3x2.get(2,0), 10);
    EXPECT_NE(matrix3x3.get(2,2), 1);
    EXPECT_NE(matrix4x4.get(2,3), 2);
    //invalid
    EXPECT_ANY_THROW(matrix1x1.get(10,10));
    EXPECT_ANY_THROW(matrix2x2.get(10,10));
    EXPECT_ANY_THROW(matrix1x4.get(10,10));
    EXPECT_ANY_THROW(matrix3x2.get(10,10));
    EXPECT_ANY_THROW(matrix3x3.get(10,10));
    EXPECT_ANY_THROW(matrix4x4.get(10,10));
}

TEST_F(NonEmptyMatrix, OperatorEqual){
    //equal
    EXPECT_TRUE(matrix1x1.operator==(matrix1x1));
    EXPECT_TRUE(matrix2x2.operator==(matrix2x2));
    EXPECT_TRUE(matrix1x4.operator==(matrix1x4));
    EXPECT_TRUE(matrix3x2.operator==(matrix3x2));
    EXPECT_TRUE(matrix3x3.operator==(matrix3x3));
    EXPECT_TRUE(matrix4x4.operator==(matrix4x4));
    //not equal
    EXPECT_FALSE(matrix1x1.operator==(matrix1x1_2));
    EXPECT_FALSE(matrix2x2.operator==(matrix2x2_2));
    EXPECT_FALSE(matrix1x4.operator==(matrix1x4_2));
    EXPECT_FALSE(matrix3x2.operator==(matrix3x2_2));
    EXPECT_FALSE(matrix3x3.operator==(matrix3x3_2));
    EXPECT_FALSE(matrix4x4.operator==(matrix4x4_2));
    //invalid
    EXPECT_ANY_THROW(matrix1x1.operator==(matrix2x2));
    EXPECT_ANY_THROW(matrix2x2.operator==(matrix3x2));
    EXPECT_ANY_THROW(matrix1x4.operator==(matrix3x3));
    EXPECT_ANY_THROW(matrix3x2.operator==(matrix4x4));
    EXPECT_ANY_THROW(matrix3x3.operator==(matrix3x2));
    EXPECT_ANY_THROW(matrix4x4.operator==(matrix1x4));
}

TEST_F(NonEmptyMatrix, OperatorPlus){
    //valid
    Matrix temp1x1 = Matrix(1,1);
    temp1x1.set(std::vector<std::vector<double>>{{1}});
    EXPECT_EQ(matrix1x1.operator+(matrix1x1_2), temp1x1);
    Matrix temp2x2 = Matrix(2,2);
    temp2x2.set(std::vector<std::vector<double>>{{6,10},{4,7}});
    EXPECT_EQ(matrix2x2.operator+(matrix2x2_2), temp2x2);
    Matrix temp1x4 = Matrix(1,4);
    temp1x4.set(std::vector<std::vector<double>>{{6,8,6,6}});
    EXPECT_EQ(matrix1x4.operator+(matrix1x4_2), temp1x4);
    Matrix temp3x2 = Matrix(3,2);
    temp3x2.set(std::vector<std::vector<double>>{{5,5},{7,8},{10,13}});
    EXPECT_EQ(matrix3x2.operator+(matrix3x2_2), temp3x2);
    Matrix temp3x3 = Matrix(3,3);
    temp3x3.set(std::vector<std::vector<double>>{{4,5,6},{10,11,12},{15,16,17}});
    EXPECT_EQ(matrix3x3.operator+(matrix3x3_2), temp3x3);
    Matrix temp4x4 = Matrix(4,4);
    temp4x4.set(std::vector<std::vector<double>>{{2,4,6,7},{10,11,16,16},{18,21,21,24},{26,29,30,26}});
    EXPECT_EQ(matrix4x4.operator+(matrix4x4_2), temp4x4);
    //invalid
    EXPECT_ANY_THROW(matrix1x1.operator+(matrix2x2));
    EXPECT_ANY_THROW(matrix2x2.operator+(matrix3x2));
    EXPECT_ANY_THROW(matrix1x4.operator+(matrix2x2));
    EXPECT_ANY_THROW(matrix3x2.operator+(matrix1x4));
    EXPECT_ANY_THROW(matrix3x3.operator+(matrix4x4));
    EXPECT_ANY_THROW(matrix4x4.operator+(matrix3x3));
}

TEST_F(NonEmptyMatrix, OperatorMultiply){
    //valid
    Matrix temp1x1 = Matrix(1,1);
    temp1x1.set(std::vector<std::vector<double>>{{0}});
    EXPECT_EQ(matrix1x1.operator*(matrix1x1_2), temp1x1);
    Matrix temp2x2 = Matrix(2,2);
    temp2x2.set(std::vector<std::vector<double>>{{7,14},{19,36}});
    EXPECT_EQ(matrix2x2.operator*(matrix2x2_2), temp2x2);
    Matrix temp1x4 = Matrix(1,4);
    temp1x4.set(std::vector<std::vector<double>>{{90,100,110,120}});
    EXPECT_EQ(matrix1x4.operator*(matrix4x4), temp1x4);
    Matrix temp3x2 = Matrix(3,2);
    temp3x2.set(std::vector<std::vector<double>>{{7,10},{15,22},{23,34}});
    EXPECT_EQ(matrix3x2.operator*(matrix2x2), temp3x2);
    Matrix temp3x3 = Matrix(3,3);
    temp3x3.set(std::vector<std::vector<double>>{{39,39,39},{90,90,90},{141,141,141}});
    EXPECT_EQ(matrix3x3.operator*(matrix3x3_2), temp3x3);
    Matrix temp4x4 = Matrix(4,4);
    temp4x4.set(std::vector<std::vector<double>>{{90,105,111,95},{202,237,259,227},{314,369,407,359},{426,501,555,491}});
    EXPECT_EQ(matrix4x4.operator*(matrix4x4_2), temp4x4);
    //invalid
    EXPECT_ANY_THROW(matrix1x1.operator*(matrix2x2));
    EXPECT_ANY_THROW(matrix1x1.operator*(matrix3x3));
    EXPECT_ANY_THROW(matrix3x3.operator*(matrix4x4));
    EXPECT_ANY_THROW(matrix1x1.operator*(matrix4x4));
    EXPECT_ANY_THROW(matrix4x4.operator*(matrix1x4));
}

TEST_F(NonEmptyMatrix, OperatorMultiplyConstant){
    //valid
    Matrix temp1x1 = Matrix(1,1);
    temp1x1.set(std::vector<std::vector<double>>{{0}});
    EXPECT_EQ(matrix1x1.operator*(2), temp1x1);
    Matrix temp2x2 = Matrix(2,2);
    temp2x2.set(std::vector<std::vector<double>>{{2,4},{6,8}});
    EXPECT_EQ(matrix2x2.operator*(2), temp2x2);
    Matrix temp1x4 = Matrix(1,4);
    temp1x4.set(std::vector<std::vector<double>>{{2,4,6,8}});
    EXPECT_EQ(matrix1x4.operator*(2), temp1x4);
    Matrix temp3x2 = Matrix(3,2);
    temp3x2.set(std::vector<std::vector<double>>{{2,4},{6,8},{10,12}});
    EXPECT_EQ(matrix3x2.operator*(2), temp3x2);
    Matrix temp3x3 = Matrix(3,3);
    temp3x3.set(std::vector<std::vector<double>>{{2,4,6},{8,10,12},{14,16,18}});
    EXPECT_EQ(matrix3x3.operator*(2), temp3x3);
    Matrix temp4x4 = Matrix(4,4);
    temp4x4.set(std::vector<std::vector<double>>{{2,4,6,8},{10,12,14,16},{18,20,22,24},{26,28,30,32}});
    EXPECT_EQ(matrix4x4.operator*(2), temp4x4);
}

TEST_F(NonEmptyMatrix, SolveEquation){
    //valid
    std::vector<double> temp = {1};
    EXPECT_EQ(matrix1x1_2.solveEquation(std::vector<double>{1}), temp);
    std::vector<double> temp2 = {0,0.5};
    EXPECT_EQ(matrix2x2.solveEquation(std::vector<double>{1,2}), temp2);
    temp2 = {0,0};
    EXPECT_EQ(matrix2x2_2.solveEquation(std::vector<double>{0,0}), temp2);
    //invalid - D==0
    EXPECT_ANY_THROW(matrix1x1.solveEquation(std::vector<double>{1}));
    EXPECT_ANY_THROW(matrix3x3.solveEquation(std::vector<double>{1,2,3}));
    EXPECT_ANY_THROW(matrix3x3_2.solveEquation(std::vector<double>{1,2,3}));
    EXPECT_ANY_THROW(matrix4x4.solveEquation(std::vector<double>{1,2,3,4}));
    //invalid - not a square type
    EXPECT_ANY_THROW(matrix1x4.solveEquation(std::vector<double>{1}));
    EXPECT_ANY_THROW(matrix3x2.solveEquation(std::vector<double>{1,2,3}));
    EXPECT_ANY_THROW(matrix3x2.solveEquation(std::vector<double>{1,2}));
}

TEST_F(NonEmptyMatrix, Transpose){
    //valid
    Matrix temp1x1 = Matrix(1,1);
    temp1x1.set(std::vector<std::vector<double>>{{0}});
    EXPECT_EQ(matrix1x1.transpose(), temp1x1);
    Matrix temp2x2 = Matrix(2,2);
    temp2x2.set(std::vector<std::vector<double>>{{1,3},{2,4}});
    EXPECT_EQ(matrix2x2.transpose(), temp2x2);
    Matrix temp4x1 = Matrix(4,1);
    temp4x1.set(std::vector<std::vector<double>>{{1},{2},{3},{4}});
    EXPECT_EQ(matrix1x4.transpose(), temp4x1);
    Matrix temp2x3 = Matrix(2,3);
    temp2x3.set(std::vector<std::vector<double>>{{1,3,5},{2,4,6}});
    EXPECT_EQ(matrix3x2.transpose(), temp2x3);
    Matrix temp3x3 = Matrix(3,3);
    temp3x3.set(std::vector<std::vector<double>>{{1,4,7},{2,5,8},{3,6,9}});
    EXPECT_EQ(matrix3x3.transpose(), temp3x3);
    Matrix temp4x4 = Matrix(4,4);
    temp4x4.set(std::vector<std::vector<double>>{{1,5,9,13},{2,6,10,14},{3,7,11,15},{4,8,12,16}});
    EXPECT_EQ(matrix4x4.transpose(), temp4x4);
}

TEST_F(NonEmptyMatrix, Inverse){
    //valid
    Matrix temp2x2 = Matrix(2,2);
    temp2x2.set(std::vector<std::vector<double>>{{-2,1},{1.5,-0.5}});
    EXPECT_EQ(matrix2x2.inverse(), temp2x2);
    //invalid
    EXPECT_ANY_THROW(matrix1x1.inverse());
    EXPECT_ANY_THROW(matrix1x4.inverse());
    EXPECT_ANY_THROW(matrix1x4_2.inverse());
    EXPECT_ANY_THROW(matrix3x3.inverse());
    EXPECT_ANY_THROW(matrix3x3_2.inverse());
    EXPECT_ANY_THROW(matrix4x4.inverse());
}
/*** Konec souboru white_box_tests.cpp ***/
