#include <stdio.h>
#include <iostream>
#include <time.h>
#include <random>
#include <windows.h>
using namespace std;

//---------------0.global variable---------------
#define ITEM_NUM 4
#define WINNING_NUM 2048

// 4*4 matrix(1*1 matrix means to a block)
int matrix[ITEM_NUM][ITEM_NUM];

// input command
string readCommond;

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
// -1: continue
int if_win()
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
// -1: continue
int if_lose()
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
// merge_by_left 
void merge_by_left()
{
    // value贋刈貧匯了崔議峙��耽佩及匯倖贋刈��音栽旺����pos燕幣栽旺朔議了崔庁亭峺寞
    int value, pos, i, j;
    // 演煽畠蕉延楚裳專
    for (i = 0; i < ITEM_NUM; i++)
    {
        // 耽将狛匯蚊曾倖留峺寞兜兵晒 
        value = 0, pos = 0;
        for (j = 0; j < ITEM_NUM; j++)
        {
            // 柳狛腎曝翠
            if (matrix[i][j] == 0)
                continue;

            if (value == 0)
            {
                value = matrix[i][j];
            }
            else
            {
                // 栽旺�猴�曝翠
                if (value == matrix[i][j])
                {
                    matrix[i][pos] = value * 2;
                    pos++;
                    //score += value;
                    value = 0;
                }
                else
                {
                    matrix[i][pos] = value;
                    pos++;
                    value = matrix[i][j];
                }
            }
            // 潮範験0峙
            matrix[i][j] = 0;
        }

        //挑硫験峙
        if (value != 0)
            matrix[i][pos] = value;
    }
}

// merge_by_right 
void merge_by_right()
{
    // value贋刈貧匯了崔議峙��耽佩及匯倖贋刈��音栽旺����pos燕幣栽旺朔議了崔庁亭峺寞
    int value, pos, i, j;
    // 演煽畠蕉延楚裳專
    for (i = 0; i < ITEM_NUM; i++)
    {
        // 耽将狛匯蚊曾倖留峺寞兜兵晒 
        value = 0, pos = ITEM_NUM - 1;
        for (j = ITEM_NUM-1; j >= 0; j--)
        {
            // 柳狛腎曝翠
            if (matrix[i][j] == 0)
                continue;

            if (value == 0)
            {
                value = matrix[i][j];
            }
            else
            {
                // 栽旺�猴�曝翠
                if (value == matrix[i][j])
                {
                    matrix[i][pos] = value * 2;
                    pos--;
                    //score += value;
                    value = 0;
                }
                else
                {
                    matrix[i][pos] = value;
                    pos--;
                    value = matrix[i][j];
                }
            }
            // 潮範験0峙
            matrix[i][j] = 0;
        }

        //挑硫験峙
        if (value != 0)
            matrix[i][pos] = value;
    }
}

// merge_by_down
void merge_by_down()
{
    // value贋刈貧匯了崔議峙��耽佩及匯倖贋刈��音栽旺����pos燕幣栽旺朔議了崔庁亭峺寞
    int value, pos, i, j;
    // 演煽畠蕉延楚裳專
    for (j = 0; j < ITEM_NUM; j++)
    {
        // 耽将狛匯蚊曾倖留峺寞兜兵晒 
        value = 0, pos = ITEM_NUM - 1;
        for (i = ITEM_NUM - 1; i >= 0; i--)
        {
            // 柳狛腎曝翠
            if (matrix[i][j] == 0)
                continue;

            if (value == 0)
            {
                value = matrix[i][j];
            }
            else
            {
                // 栽旺�猴�曝翠
                if (value == matrix[i][j])
                {
                    matrix[pos][j] = value * 2;
                    pos--;
                    //score += value;
                    value = 0;
                }
                else
                {
                    matrix[pos][j] = value;
                    pos--;
                    value = matrix[i][j];
                }
            }
            // 潮範験0峙
            matrix[i][j] = 0;
        }

        //挑硫験峙
        if (value != 0)
            matrix[pos][j] = value;
    }
}

// merge_by_up
void merge_by_up()
{
    // value贋刈貧匯了崔議峙��耽佩及匯倖贋刈��音栽旺����pos燕幣栽旺朔議了崔庁亭峺寞
    int value, pos, i, j;
    // 演煽畠蕉延楚裳專
    for (j = 0; j < ITEM_NUM; j++)
    {
        // 耽将狛匯蚊曾倖留峺寞兜兵晒 
        value = 0, pos = 0;
        for (i = 0; i < ITEM_NUM; i++)
        {
            // 柳狛腎曝翠
            if (matrix[i][j] == 0)
                continue;

            if (value == 0)
            {
                value = matrix[i][j];
            }
            else
            {
                // 栽旺�猴�曝翠
                if (value == matrix[i][j])
                {
                    matrix[pos][j] = value * 2;
                    pos++;
                    //score += value;
                    value = 0;
                }
                else
                {
                    matrix[pos][j] = value;
                    pos++;
                    value = matrix[i][j];
                }
            }
            // 潮範験0峙
            matrix[i][j] = 0;
        }

        //挑硫験峙
        if (value != 0)
            matrix[pos][j] = value;
    }
}

// controller
void judge_input_command()
{
    char char_command = read_command();
    if (char_command == 'w')
    {
        merge_by_up();
    }
    else if (char_command == 's')
    {
        merge_by_down();
    }
    else if (char_command == 'a')
    {
        merge_by_left();
    }
    else if (char_command == 'd')
    {
        merge_by_right();
    }
    return;
}


//---------------5.generate the block with random value---------------
// get the number of zero block
int matrix_zero_num()
{
    int i, j, cnt = 0;
    for (i = 0; i < ITEM_NUM; i++)
    {
        for (j = 0; j < ITEM_NUM; j++)
        {
            if (matrix[i][j] == 0)
            {
                cnt++;
            }
        }
    }
    return cnt;
}

// give the random value to random zero block
void give_random_value()
{
    int random_value_array[] = { 2,2,2,2,2,4,2,2,2,2 };
    int random_value = random_value_array[rand()%10];

    // zero_num explain that it doesn't need to generate new random value blcok
    int zero_num = matrix_zero_num();
    if (zero_num == 0)
        return;

    int selected_zero_block = rand()% zero_num;

    int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (matrix[i][j] == 0)
            {
                if (cnt == selected_zero_block)
                {
                    matrix[i][j] = random_value;
                    return ;
                }
                cnt++;
            }
        }
    }
}

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

void start_game()
{
    srand(time(NULL));
    init_matrix();
    give_random_value();
    printf_matrix();
    cout << "plz input the command 'w s a d' to realize 'up down left right'" << endl;

    while (1)
    {
        // win or lose
        if (if_win == 0)
        {
            draw_miku();
            cout << "ありがとうございます !" << endl;
            Sleep(2000);
            return;
        }
        if (if_lose == 0)
        {
            draw_miku();
            cout << "寄嬋健 です!" << endl;
            Sleep(2000);
            return;
        }

        // merge
        judge_input_command();

        // generate new block with value
        give_random_value();

        // printf the matrix
        printf_matrix();
    }
}

int main()
{
    start_game();
    return 0;
}

