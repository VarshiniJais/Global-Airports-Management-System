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

static int dfs_helper(int n,const connection_t connections[n][n], int vertex, int *visited,int src) 
{
    visited[vertex] = 1;
    int i;
    for (i = 0; i <n; ++i) 
    {
        if(i==src && vertex!=i && connections[vertex][i].distance!=2147483647)
        {
            return 1;
        }
        if (connections[vertex][i].distance>0 && visited[i] == 0) 
        {
            return dfs_helper(n,connections,i,visited,src);
        }
    }
    return 0;
}
int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    int visited[n],k,i=0;
    for(k=0;k<n;k++)
    {
        visited[k]=0;
    }
    int val=dfs_helper(n,connections,src->num_id, visited,src->num_id);
}
int main()
{
        // Q3
        airport_t src = {0, "BLR"};
        int n = 3;
        connection_t q3_t1_connections[3][3] = {
            {{0, 0}, {1, 2}, {2, 3}},
            {{1, 2}, {0, 0}, {2, 3}},
            {{2, 3}, {2, 3}, {0, 0}}};

        if (q3(&src, n, q3_t1_connections))
        {
            printf("Q3 TestCase 1: " PASSED);
        }
        else
        {
            printf("Q3 TestCase 1: " FAILED);
        }
    }