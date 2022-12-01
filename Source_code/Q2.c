#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PASSED "PASSED\n"
#define FAILED "FAILED\n"
struct airport
{
    int num_id;
    const char *airport_name;
};
typedef struct airport airport_t;

struct connection
{
    int distance;
    int time;
};
typedef struct connection connection_t;
/*
 * @param src: Start and end airport
 * @param n: Total number of airports
 * @param connections: Adjacency matrix which is a
   graph representing the connections between the airports
 *
 * @return value: boolean variable indicating if it is possible to start at the
 src airport and return to the src airport
 *
 */
static void push(int *top, int ele, int *stack)
{
    stack[++(*top)] = ele;
}
static int pop(int *top, int *stack)
{
    return stack[(*top)--];
}
int q2(const airport_t *src, const airport_t *dest, int n, int k,
       const connection_t connections[n][n])
{
    int visited[n], i = 0, stack[n], top = -1, vertex, flag = 0, num = 0;
    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    push(&top, src->num_id, stack);
    visited[src->num_id] = 1;
    vertex = src->num_id;
    while (top > -1)
    {
        for (i = 0; i < n; i++)
        {
            flag = 0;
            if (vertex == dest->num_id)
            {
                if (num <= k)
                {
                    return 1;
                }
                break;
            }
            if (vertex != i && visited[i] == 0 && connections[vertex][i].distance != 2147483647)
            {
                // printf("push in : %d\n",i);
                push(&top, i, stack);
                visited[i] = 1;
                num++;
                flag = 1;
                vertex = i;
                break;
            }
        }
        if (flag == 0)
        {
            num--;
            vertex = pop(&top, stack);
        }
    }
    if (num <= k && num > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    // Q2
    airport_t src = {0, "BLR"};
    airport_t dest = {1, "MUM"};
    int n = 3;
    int k = 2;
    connection_t q2_t1_connections[3][3] = {
        {{0, 0}, {INT_MAX, INT_MAX}, {1, 5}},
        {{1, 2}, {0, 0}, {4, 3}},
        {{2, 3}, {2, 3}, {0, 0}}};
    if (q2(&src, &dest, n, k, q2_t1_connections))
    {
        printf("Q2 TestCase 1: " PASSED);
    }
    else
    {
        printf("Q2 TestCase 1: " FAILED);
    }
}