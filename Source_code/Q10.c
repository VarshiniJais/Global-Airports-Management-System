#include <limits.h>
#include <stdio.h>
#include <string.h>
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
void q10(int n, int k, const airport_t *src, const connection_t connections[n][n],
         const int destinations[k], int costs[k])
{
    int i = 0, v, min, index;
    int distances[n];
    int vertex_include[n];
    while (i < n)
    {
        distances[i] = 2147483647;
        vertex_include[i] = 0;
        i++;
    }
    distances[src->num_id] = 0;
    for (i = 0; i < n - 1; i++)
    {
        min = 2147483647;
        for (v = 0; v < n; v++)
        {
            if (vertex_include[v] == 0 && distances[v] < min)
            {
                min = distances[v];
                index = v;
            }
        }
        vertex_include[index] = 1;
        v = 0;
        while (v < n)
        {
            if (vertex_include[v] == 0 && index != v && connections[index][v].distance < 2147483647 && distances[index] < 2147483647)
            {
                if ((distances[index] + connections[index][v].time) < distances[v])
                {
                    distances[v] = distances[index] + connections[index][v].time;
                    // printf("Con : %d D : %d\n",distances[index]+connections[index][v].distance,distances[v]);
                }
            }
            v++;
        }
    }
    v = 0;
    while (v < k)
    {
        costs[v] = distances[destinations[v]];
        v++;
    }
}
int main()
{
    // Q10
    connection_t q10_t1_connections[4][4] = {
        {{0, 0}, {1, 2}, {2, 6}, {INT_MAX, INT_MAX}},
        {{1, 2}, {0, 0}, {3, 5}, {4, 1}},
        {{2, 6}, {3, 5}, {0, 0}, {5, 7}},
        {{INT_MAX, INT_MAX}, {4, 1}, {5, 7}, {0, 0}}};

    int n = 4;
    int k = 2;
    int destinations[] = {0, 2};
    int costs[2] = {INT_MAX, INT_MAX};

    airport_t src = {3, "BLR"};
    q10(n, k, &src, q10_t1_connections, destinations, costs);

    if (costs[0] == 3 && costs[1] == 6)
    {
        printf("Q10 TestCase 1: " PASSED);
    }
    else
    {
        printf("Q10 TestCase 1: " FAILED);
    }
}