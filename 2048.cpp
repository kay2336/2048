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

// score: every merging get the score(equal to value)
// example: 2 2 0 0 -> 4 0 0 0(score+=2) 
int score = 0;

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

//---------------4.the merging algorithm---------------
// merge_by_left 
void merge_by_left()
{
    // value存储上一位置的值（每行第一个存储，不合并），pos表示合并后的位置模拟指针
    int value, pos, i, j;
    // 遍历全局变量矩阵
    for (i = 0; i < ITEM_NUM; i++)
    {
        // 每经过一层两个伪指针初始化 
        value = 0, pos = 0;
        for (j = 0; j < ITEM_NUM; j++)
        {
            // 跳过空区块
            if (matrix[i][j] == 0)
                continue;

            if (value == 0)
            {
                value = matrix[i][j];
            }
            else
            {
                // 合并相同区块
                if (value == matrix[i][j])
                {
                    matrix[i][pos] = value * 2;
                    pos++;
                    score += value;
                    value = 0;
                }
                else
                {
                    matrix[i][pos] = value;
                    pos++;
                    value = matrix[i][j];
                }
            }
            // 默认赋0值
            matrix[i][j] = 0;
        }

        //末尾赋值
        if (value != 0)
            matrix[i][pos] = value;
    }
}

// merge_by_right 
void merge_by_right()
{
    // value存储上一位置的值（每行第一个存储，不合并），pos表示合并后的位置模拟指针
    int value, pos, i, j;
    // 遍历全局变量矩阵
    for (i = 0; i < ITEM_NUM; i++)
    {
        // 每经过一层两个伪指针初始化 
        value = 0, pos = ITEM_NUM - 1;
        for (j = ITEM_NUM-1; j >= 0; j--)
        {
            // 跳过空区块
            if (matrix[i][j] == 0)
                continue;

            if (value == 0)
            {
                value = matrix[i][j];
            }
            else
            {
                // 合并相同区块
                if (value == matrix[i][j])
                {
                    matrix[i][pos] = value * 2;
                    pos--;
                    score += value;
                    value = 0;
                }
                else
                {
                    matrix[i][pos] = value;
                    pos--;
                    value = matrix[i][j];
                }
            }
            // 默认赋0值
            matrix[i][j] = 0;
        }

        //末尾赋值
        if (value != 0)
            matrix[i][pos] = value;
    }
}

// merge_by_down
void merge_by_down()
{
    // value存储上一位置的值（每行第一个存储，不合并），pos表示合并后的位置模拟指针
    int value, pos, i, j;
    // 遍历全局变量矩阵
    for (j = 0; j < ITEM_NUM; j++)
    {
        // 每经过一层两个伪指针初始化 
        value = 0, pos = ITEM_NUM - 1;
        for (i = ITEM_NUM - 1; i >= 0; i--)
        {
            // 跳过空区块
            if (matrix[i][j] == 0)
                continue;

            if (value == 0)
            {
                value = matrix[i][j];
            }
            else
            {
                // 合并相同区块
                if (value == matrix[i][j])
                {
                    matrix[pos][j] = value * 2;
                    pos--;
                    score += value;
                    value = 0;
                }
                else
                {
                    matrix[pos][j] = value;
                    pos--;
                    value = matrix[i][j];
                }
            }
            // 默认赋0值
            matrix[i][j] = 0;
        }

        //末尾赋值
        if (value != 0)
            matrix[pos][j] = value;
    }
}

// merge_by_up
void merge_by_up()
{
    // value存储上一位置的值（每行第一个存储，不合并），pos表示合并后的位置模拟指针
    int value, pos, i, j;
    // 遍历全局变量矩阵
    for (j = 0; j < ITEM_NUM; j++)
    {
        // 每经过一层两个伪指针初始化 
        value = 0, pos = 0;
        for (i = 0; i < ITEM_NUM; i++)
        {
            // 跳过空区块
            if (matrix[i][j] == 0)
                continue;

            if (value == 0)
            {
                value = matrix[i][j];
            }
            else
            {
                // 合并相同区块
                if (value == matrix[i][j])
                {
                    matrix[pos][j] = value * 2;
                    pos++;
                    score += value;
                    value = 0;
                }
                else
                {
                    matrix[pos][j] = value;
                    pos++;
                    value = matrix[i][j];
                }
            }
            // 默认赋0值
            matrix[i][j] = 0;
        }

        //末尾赋值
        if (value != 0)
            matrix[pos][j] = value;
    }
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
//  0: lose
// -1: continue
int if_lose()
{
    // traversal all blocks' right and down side, judge whether to equal to each other
    for (int i = 0; i < ITEM_NUM; i++)
    {
        for (int j = 0; j < ITEM_NUM; j++)
        {
            if (matrix[i][j] == 0)
            {
                return -1;
            }

            if (j != ITEM_NUM - 1)
            {
                if (matrix[i][j] == matrix[i][j + 1])
                {
                    return -1;
                }
            }

            if (i != ITEM_NUM - 1)
            {
                if (matrix[i][j] == matrix[i + 1][j])
                {
                    return -1;
                }
            }
        }
    }
    return 0;
}

//---------------*.use the gold finger---------------
// transform every block into 512
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
    else if (char_command == 'g')
    {
        gold_finger();
    }
    return;
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

//---------------*.printf the score---------------
// printf the score
void printf_score()
{
    cout << "now your score is: " << score << endl;
}

//---------------*.printf the duration---------------
// printf the duration
void printf_duration(clock_t start)
{
    clock_t end = clock();
    cout << "now the game duration is: " << (double)(end-start) / CLOCKS_PER_SEC << endl;
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

    clock_t start;
    start = clock();

    while (1)
    {
        // win or lose
        if (if_win() == 0)
        {
            draw_miku();
            cout << "ありがとうございます !" << endl;
            Sleep(2000);
            return;
        }
        if (if_lose() == 0)
        {
            draw_miku();
            cout << "大丈夫 です!" << endl;
            Sleep(2000);
            return;
        }
        cout << "-------------------------------------" << endl;
        // generate new block with value
        give_random_value();

        cout << "plz input the command 'w s a d' to realize 'up down left right'" << endl;
        printf_duration(start);
        printf_score();

        // printf the matrix and score
        printf_matrix();
        cout << "-------------------------------------" << endl;

        // merge
        judge_input_command();

        // clean the content
        system("cls");
    }
}

int main()
{
    start_game();
    return 0;
}

