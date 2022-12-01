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

struct pair
{
    int first;
    int second;
};
typedef struct pair pair_t;

int unordered_pair_compare(const pair_t *p1, const pair_t *p2)
{
	return ((p1->first == p2->first) && (p1->second == p2->second)) ||
		    ((p1->first == p2->second) && (p1->second == p2->first));
}

int check_edge_perm(const pair_t p[3], const pair_t *p1, const pair_t *p2, const pair_t *p3)
{
	return unordered_pair_compare(&p[0],p1) && unordered_pair_compare(&p[1],p2) && unordered_pair_compare(&p[2],p3);
}
/*
 * @param n: Total number of airports
 * @param edges: Array of type pair_t of length n-1 initialized to {-1,-1}.
 * @param connections: Adjacency matrix which is an undirected
   graph representing the connections between the airports
 *
 * @return value: Minimum total time
 *
 * At the end of the function must be filled with the edges belonging to the
 solution. The edges are represented by a pair with the start node and end node
 of the edge. The edges may be in any order. The start and end order in the pair
 is not important as it is undirected. All equivalent solutions are accepted.
 */
int prims(int n,const connection_t connections[n][n])
{
    
}
int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    int i, count, v, min, vertex,time=0;
    int parent[n];
    int key[n];
    int vertex_included[n];
    for (i = 0; i < n; i++)
    {
        key[i] = 2147483647;
        vertex_included[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;
    for (count = 0; count < n - 1; count++)
    {
        min = 2147483647;
        for (v = 0; v < n; v++)
        {
            if (vertex_included[v] == 0 && key[v] < min)
            {
                min = key[v], vertex = v;
            }
        }
        vertex_included[vertex] = 1;
        v=0;
        while (v < n)
        {
            if (vertex != v && connections[vertex][v].distance != 2147483647 && vertex_included[v] == 0 && connections[vertex][v].distance < key[v])
            {
                parent[v] = vertex;
                key[v] = connections[vertex][v].time;
            }
            v++;
        }
    }
    for(i=1;i<n;i++)
    {
       printf("%d - %d \n", parent[i], i);
        edges[i-1].first=parent[i];
        edges[i-1].second=i;
        time+=connections[parent[i]][i].time;
    }
    return time;
}

int main()
{
    // Q9
    connection_t q9_t1_connections[4][4] = {
        {{0, 0}, {1, 2}, {2, 6}, {INT_MAX, INT_MAX}},
        {{1, 2}, {0, 0}, {3, 5}, {4, 1}},
        {{2, 6}, {3, 5}, {0, 0}, {5, 7}},
        {{INT_MAX, INT_MAX}, {4, 1}, {5, 7}, {0, 0}}};

    int n = 4;

    pair_t edges[3] = {{-1, -1}, {-1, -1}, {-1, -1}};
    int result = q9(n, edges, q9_t1_connections);
    pair_t p1 = {0, 1};
    pair_t p2 = {1, 2};
    pair_t p3 = {1, 3};
    printf("result : %d\n",result);
    if (result == 8 && (check_edge_perm(edges, &p1, &p2, &p3) || check_edge_perm(edges, &p1, &p3, &p2) ||
                        check_edge_perm(edges, &p2, &p1, &p3) || check_edge_perm(edges, &p2, &p3, &p1) || check_edge_perm(edges, &p3, &p1, &p2) ||
                        check_edge_perm(edges, &p3, &p2, &p1)))
    {
        printf("Q9 TestCase 1: " PASSED);
    }
    else
    {
        printf("Q9 TestCase 1: " FAILED);
    }
}
