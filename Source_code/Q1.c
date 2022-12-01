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

static void append(int *queue, int v, int *pqr) 
{
    ++(*pqr);
    queue[*pqr] = v;
}
static int delete(int *queue, int *pqr) 
{
    int res = queue[0];
    int i;
    for (i = 0; i < *pqr; ++i) 
    {
        queue[i] = queue[i + 1];
    }
    --(*pqr);
    return res;
}

/*
 * @param n: Total number of airports
 * @param connections: Adjacency matrix which is a graph representing the
 * connections between the airports
 *
 * @return value: 1 if it is possible for a traveler to be able to go from any
 * airport to any other airport, directly or indirectly, and this being true for
 * all airports, else 0
 */
int q1(int n, const connection_t connections[n][n])
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i!=j)
            {
                int flag=0,k;
                int source=i;
                int dest=j;
                int qr = -1;
                // Initialise visited list and queue (init 0)
                int visited[n];
                int queue[n];
                for(k=0;k<n;k++)
                {
                    visited[k]=0;
                    queue[k]=0;
                }
                // Loop
                append(queue, source, &qr);
                visited[source] = 1;
                int vertex;
                // While queue is not empty
                while (qr != -1) 
                {
                    vertex = delete(queue, &qr);
                    
                    // Destination reached
                    if (vertex == dest) 
                    {
                        flag=1;
                        break;
                    }
                    int i;
                    for (i = 0; i < n; ++i) 
                    {
                        if (i!=vertex && connections[vertex][i].distance!=INT_MAX  && !visited[i]) 
                        {
                            visited[i] = 1;
                            append(queue, i, &qr);
                        }
                    }
                }
                free(visited);
                free(queue);
                if(flag==0)
                {
                    return 0;
                }
                //printf("\nj : %d",j);
            }
        }
    }
    return 1;
}
int main()
{
        // Q1
        {
            int n = 3;
            connection_t q1_t1_connections[3][3] = {
                {{0, 0}, {1, 2}, {2, 3}},
                 {{1, 2}, {0, 0}, {2, 3}},
                 {{2, 3}, {2, 3}, {0, 0}}};

            if (q1(n, q1_t1_connections))
            {
                printf("Q1 TestCase 1: " PASSED);
            }
            else
            {
                printf("Q1 TestCase 1: " FAILED);
            }
        }
        {
            int n = 3;
            connection_t q1_t2_connections[3][3] = {
                {{0, 0}, {INT_MAX, INT_MAX}, {3, 3}},
                {{INT_MAX, INT_MAX}, {0, 0}, {2, 3}},
                {{INT_MAX, INT_MAX}, {2, 3}, {0, 0}}};

            if (!q1(n, q1_t2_connections))
            {
                printf("Q1 TestCase 2: " PASSED);
            }
            else
            {
                printf("Q1 TestCase 2: " FAILED);
            }
        }
}