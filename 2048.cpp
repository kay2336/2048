#include <stdio.h>
#include <iostream>
using namespace std;

//---------------0.global variable---------------
#define ITEM_NUM 4
#define WINNING_NUM 2048

// 4*4 matrix(1*1 matrix means to a block)
int matrix[ITEM_NUM + 1][ITEM_NUM];

// input command
string readCommond;

// judge if ends
int game_over;

//---------------1.initializng---------------
// initial blocks to zero
void init_matrix()
{
    for (int i = 0; i < ITEM_NUM; i++)
    {
        for (int j = 0; j < ITEM_NUM; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

//---------------2.inputting command---------------
// return first one character('w','a','s','d')
char read_command()
{
    cin>>readCommond;
    return readCommond[0];
}

//---------------3.judging whether to win---------------
// (1) win
//  0: win
// -1: lose
int can_win()
{
    // traversal the matrix, return a significative number
    for (int i = 0; i < ITEM_NUM; i++)
    {
        for (int j = 0; j < ITEM_NUM; j++)
        {
            if (matrix[i][j] >= WINNING_NUM)
            {
                return 0;
            }
        }
    }
    return -1;
}

// (2) lose
//  0: merge
// -1: gather
int can_lose()
{
    // traversal all blocks' right and down side, judge whether to equal to each other
    // return_flag means return value
    int return_flag = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // judging whether to have empty block
            if (matrix[i][j] != 0)
            {
                return_flag = -1;
                return return_flag;
            }

            // the rightest and lowest side don't need to judge
            if (i == ITEM_NUM - 1 && j == ITEM_NUM - 1)
            {
                continue;
            }

            // judging the block by the lowest side
            // just compare the right block with itself
            if (i >= ITEM_NUM - 1 && matrix[i][j] == matrix[i][j + 1])
            {
                return_flag = -1;
                return return_flag;
            }

            // judging the block by the rightest side
            // just compare the down block with itself
            if (j >= ITEM_NUM - 1 && matrix[i][j] == matrix[i + 1][j])
            {
                return_flag = -1;
                return return_flag;
            }
        }
    }
    return return_flag;
}

//---------------4.the merging algorithm---------------

//---------------5.generate the block with random value---------------

//---------------*.printf the matrix---------------
// printf the matrix
void printf_matrix()
{
    printf("now your matrix is: \n");
    for (int i = 0; i < ITEM_NUM; i++)
    {
        for (int j = 0; j < ITEM_NUM; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

//---------------*.calculate the score---------------
// printf the score
void printf_score()
{
}

//---------------*.printf the consumed time---------------
// printf the consumed time
void p_consuming_time()
{
}

//---------------*.use the gold finger---------------
// transform every block into 1024
void gold_finger()
{
    for (int i = 0; i < ITEM_NUM; i++)
    {
        for (int j = 0; j < ITEM_NUM; j++)
        {
            matrix[i][j] = 512;
        }
    }
}

//---------------*.draw the miku---------------
void draw_miku()
{
    printf("           ***                                  \n");
    printf("          ** *****************     *****        \n");
    printf("          * *                  ** *   **        \n");
    printf("         *       *               ** ****        \n");
    printf("        **      * *     **         **  ***      \n");
    printf("      *** *   *** *    ****         **    *     \n");
    printf("     * ** *  ***   *  * ** **       **     *    \n");
    printf("     * *  *** **   ***  **  **      **     *    \n");
    printf("    *  *  *  ***    *  ***   *    *****     *   \n");
    printf("     * ****  **        **    *  *******     *   \n");
    printf("     *  **                  *   *******     *   \n");
    printf("     *  * **     ****       * ********      *   \n");
    printf("     *   ** *************** *****           *   \n");
    printf("     **        *           **  **           *   \n");
}

//---------------*.draw the 2048---------------
void draw_2048()
{
    printf("  **********  **********     ****     **********\n");
    printf("  **********  **********    *****     **********\n");
    printf("          **  **      **   **  **     **      **\n");
    printf("          **  **      **  **   **     **      **\n");
    printf("  **********  **      **  **   **     **********\n");
    printf("  **********  **      **  **********  **********\n");
    printf("  **          **      **  **********  **      **\n");
    printf("  **          **      **       **     **      **\n");
    printf("  **********  **********       **     **********\n");
    printf("  **********  **********       **     **********\n");
}
