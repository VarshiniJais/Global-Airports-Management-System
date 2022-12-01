#include <limits.h>
#include <stdio.h>
#include <string.h>
struct connection
{
    int distance;
    int time;
};
typedef struct connection connection_t;
connection_t q1_t2_connections[3][3] = {
                {{0, 0}, {INT_MAX, INT_MAX}, {3, 3}},
                {{INT_MAX, INT_MAX}, {0, 0}, {2, 3}},
                {{INT_MAX, INT_MAX}, {2, 3}, {0, 0}}};
void main()
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            printf("%d ",q1_t2_connections[i][j].distance);
        }
        printf("\n");
    }
}