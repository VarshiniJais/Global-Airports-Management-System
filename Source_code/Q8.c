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
struct pv
{
    int visited;
    int parent;
};
typedef struct pv pv;
typedef struct connection connection_t;
static void path_gen(int n, int *trip_order, pv *pv_arr, int source, int loop, const connection_t connections[n][n], int *min)
{
    int count = 1, mini = connections[loop][source].distance, temp = 0, temp2 = loop;
    while (source != loop)
    {
        count++;
        temp = loop;
        loop = pv_arr[loop].parent;
        mini += connections[loop][temp].distance;
    }
    if (count == n - 1 && *min > mini)
    {
        *min = mini;
        loop = temp2;
        int i;
        for (i = n - 2; i >= 0; i--)
        {
            trip_order[i] = loop;
            loop = pv_arr[loop].parent;
        }
        trip_order[0] = source;
    }
}
static void d_cycle(int n, pv *pv_arr, const connection_t connections[n][n], int src, int *trip_order, int *min)
{
    pv_arr[src].visited = 1;
    int i=0;
    while(i < n)
    {
        if (connections[src][i].distance != INT_MAX && connections[src][i].distance != 0)
        {
            if (pv_arr[i].visited != 1)
            {
                pv_arr[i].parent = src;
                d_cycle(n, pv_arr, connections, i, trip_order, min);
            }
            else if (pv_arr[src].parent != i)
            {
                path_gen(n, trip_order, pv_arr, i, src, connections, min);
            }
        }
        i++;
    }
    pv_arr[src].visited = 0;
}
int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    pv pv_arr[n];
    int min = INT_MAX;
    int i=0;
    while(i < n)
    {
        pv_arr[i].visited = 0;
        pv_arr[i].parent = -1;
        i++;
    }
    d_cycle(n, pv_arr, connections, 0, trip_order, &min);
    if (min == INT_MAX)
    {
        return -1;
    }
    return min;
}
int main()
{
    // Q8
    {
        connection_t q8_t1_connections[4][4] = {
            {{0, 0}, {7, 2}, {3, 5}, {INT_MAX, INT_MAX}},
            {{INT_MAX, INT_MAX}, {0, 0}, {INT_MAX, INT_MAX}, {1, 3}},
            {{INT_MAX, INT_MAX}, {2, 4}, {0, 0}, {4, 7}},
            {{4, 5}, {INT_MAX, INT_MAX}, {6, 3}, {0, 0}}};

        int n = 4;
        int trip_order[3] = {-1, -1, -1};

        int result = q8(n, trip_order, q8_t1_connections);

        if (result == 9 &&
            ((trip_order[0] == 1 && trip_order[1] == 3 && trip_order[2] == 2) ||
             (trip_order[0] == 2 && trip_order[1] == 1 && trip_order[2] == 3) ||
             (trip_order[0] == 3 && trip_order[1] == 2 && trip_order[2] == 1)))
        {
            printf("Q8 TestCase 1: " PASSED);
        }
        else
        {
            printf("Q8 TestCase 1: " FAILED);
        }
    }
    {
        connection_t q8_t2_connections[3][3] = {
            {{0, 0}, {1, 2}, {INT_MAX, INT_MAX}},
            {{INT_MAX, INT_MAX}, {0, 0}, {2, 3}},
            {{3, 4}, {INT_MAX, INT_MAX}, {0, 0}}};

        int n = 3;
        int trip_order[2] = {-1, -1};

        int result = q8(n, trip_order, q8_t2_connections);

        if (result == -1 && trip_order[0] == -1 && trip_order[1] == -1)
        {
            printf("Q8 TestCase 2: " PASSED);
        }
        else
        {
            printf("Q8 TestCase 2: " FAILED);
        }
    }
}