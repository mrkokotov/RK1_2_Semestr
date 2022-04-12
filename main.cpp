//Поскольку проект читает файлы из своей папки, надо чтобы QT помещал exe файл в папку с файлами условий для заданий 1-3.

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QList>


typedef uint8_t Uint8;





void task1(FILE* out, FILE* in)
{
    int ar[256];

    memset(&ar[0], 0x00, sizeof(int) * 256);
    char c = 0;

    while(fscanf(in, "%c", &c) != EOF)
    {
        ar[(Uint8)c]++;
    }

    for(int i = 0; i < 256; ++i)
    {
        fprintf(out, "%c\t%d\n", (char)i, ar[i]);
    }
}

void task2(int in, FILE* out)
{
    for(int i = 31; i >= 0; --i)
    {
        fprintf(out, "%c", ((1 << i) & in) ? '1' : '0');
        printf("%c", ((1 << i) & in) ? '1' : '0');
    }
}

const char value[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

char* task3(FILE* in)
{
    char c = 0;
    int length = 0;

    char chars[64];

    for(int i = 0; i < 63; ++i)
    {
        chars[i] = 0;
    }

    static char result[16];

    while(fscanf(in, "%c", &c) != EOF)
    {
        chars[length] = c;
        length++;
    }

    for(int i = 0; i < length; i += 4)
    {
        int temp = 0;

        for(int j = 0; j < 4; ++j)
        {
            temp |= (((chars[i + j] == 0x30) ? 0 : 1) << j);
        }

        result[i / 4] = value[temp];
    }

    return result;
}



QList<double> task5(int** mat, int N, int M) //5th task
{
    QList<double> averStr;

    for(int i = 0; i < N; ++i)
    {
        double averStr_temp = 0.0;

        for(int j = 0; j < M; ++j)
        {
            averStr_temp += mat[i][j];
        }

        averStr.append(averStr_temp / M);
    }

    return averStr;
}

struct Node
{
    Node* prev;
    Node* next;
    char* string;
    int size;
};

struct linklist
{
    Node* HEAD;
    Node* TAIL;
};

void linked_list_write_to_file(FILE* out, Node* TAIL, Node* HEAD) //6th task
{
    //C TAIL

    Node* cur_node = TAIL;

    int num_of_elements = 0;

    do
    {
        num_of_elements++;
        cur_node = cur_node->prev;
    }
    while(cur_node->prev != nullptr);

    cur_node = TAIL;

    while(cur_node != nullptr)
    {
        fprintf(out, "%d\t\"%s\"\t%d\n", num_of_elements, cur_node->string, cur_node->size);
        num_of_elements--;
        cur_node = cur_node->prev;
    }

    //C HEAD

    cur_node = HEAD;

    num_of_elements = 0;

    while(cur_node != nullptr)
    {
        fprintf(out, "%d\t\"%s\"\t%d\n", num_of_elements, cur_node->string, cur_node->size);
        num_of_elements++;
        cur_node = cur_node->next;
    }
}

void task7(Node* HEAD, Node* el, const int index) //7th task
{
    Node* cur_node = HEAD;
    int cur_index = 0;

    while(cur_index < index && cur_node != nullptr)
    {
        cur_node = cur_node->next;
        cur_index++;
    }

    el->next = cur_node->next;
    el->prev = cur_node;

    cur_node->next->prev = el;
    cur_node->next = el;


}

int main()
{
    FILE* in;
    FILE* out;
//1 номер
    in = fopen("task1.txt", "r");
    out = fopen("result1.txt", "w");

    task1(out, in);

    fclose(in);
    fclose(out);
//2 номер
    out = fopen("result2.txt", "w");

    task2(0xaabbcc33, out);

    fclose(out);

    std::cout << "\n\n";
//3 номер
    in = fopen("task3.txt", "r");

    char* nums = task3(in);

    nums[16] = '\0';

    std::cout << nums;

    fclose(in);

    std::cout << "\n\n";
//5 номер
    srand(time(NULL));
        int n = 4;
        int **mat = new int* [n];
        for (int i = 0; i < n; i++)
        {
            mat[i] = new int [n];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                mat[i][j] = rand() % 10;
                std::cout << mat[i][j] << " ";
            }
            std::cout << "\n";
        }

        QList<double> avers = task5(mat, 4, 4);


    for(int i = 0; i < 4; ++i)
    {
        std::cout << avers[i] << "\t";
    }
    // Удаление массива
    for (int i = 0; i < n; i++)
    {
        delete[]mat[i];
    }
    delete [] mat;
    return 0;


    std::cout << "\n\n";



    }//Конец.
