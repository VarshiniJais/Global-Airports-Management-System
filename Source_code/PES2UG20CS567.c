#include "header.h"
#include<limits.h>

// ANY STATIC FUNCTIONS ARE UP HERE
/**
 * Helper functions for Q1
 * append used to add an element into queue
 * delete used to remove an elemnt from queue
 * */
static void append(int *queue, int v, int *pqr)
{
    ++(*pqr);
    queue[*pqr] = v;
}
static int delete (int *queue, int *pqr)
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
/**
 * Helper functions for Q2
 * push is used to push element into stack
 * pop is used to remove an element from stack
 * */
static void push(int *top, int ele, int *stack)
{
    stack[++(*top)] = ele;
}
static int pop(int *top, int *stack)
{
    return stack[(*top)--];
}
/**
 * Helper functions for Q3
 * recursive dfc function is used
 * checks for cycles in the graph involving the source
 * */
static int dfs_helper(int n, const connection_t connections[n][n], int vertex, int *visited, int src)
{
    visited[vertex] = 1;
    int i;
    for (i = 0; i < n; ++i)
    {
        if (i == src && vertex != i && connections[vertex][i].distance != INT_MAX)
        {
            return 1;
        }
        if (connections[vertex][i].distance > 0 && visited[i] == 0)
        {
            return dfs_helper(n, connections, i, visited, src);
        }
    }
    return 0;
}
/**
 * Helper functions for Q4
 * quick sort algorithm is used
 * partition function is used to get the pivot element and place it in its appropriate position
 * quick sort funtion is used for recursive call
 * */
static int partition(airport_t array[], int low, int high, int (*predicate_func)(const airport_t *, const airport_t *))
{
    int k, n = 5;
    airport_t temp;
    int i, j, cmp;
    airport_t pivot = array[low];
    i = low;
    j = high + 1;
    do
    {
        do
        {
            i++;
            cmp = predicate_func(&array[i], &pivot);
        } while (cmp != 0 && i < high);
        do
        {
            j--;
            cmp = predicate_func(&array[j], &pivot);
        } while (cmp == 0 && j > low);
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    } while (i < j);
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    // swap(&array[i], &array[j]);
    // swap(&array[low], &array[j]);
    temp = array[low];
    array[low] = array[j];
    array[j] = temp;
    return j;
}
static void quickSort(airport_t array[], int low, int high, int (*predicate_func)(const airport_t *, const airport_t *))
{
    int i, n = 5;
    if (low < high)
    {
        int pi = partition(array, low, high, predicate_func);
        quickSort(array, low, pi - 1, predicate_func);
        quickSort(array, pi + 1, high, predicate_func);
    }
}

/**
 * Helper functions for Q5
 * used to compare the strings 
 * returns the length of the common prefix 
 * */
static int compare_airport(const char *a1,const char *a2)
{
    int i=0;
    while(a1[i] !='\0' || a2[i] !='\0')
    {
        if(a1[i]!=a2[i])
        {
            return i;
        }
        i++;
    }
    return i;
}
/**
 * Helper functions for Q6
 * binary search is implemented
 * more efficient than brute force
 * */
static int binary_search(const int array[], int x, int low, int high)
{
    int mid;
    high--;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (array[mid] == x)
        {
            return mid + 1;
        }
        if (array[mid] < x)
        {
            low = mid + 1;
            mid++;
        }
        else
        {
            high = mid - 1;
        }
    }
    return mid;
}
/**
 * Helper functions for Q7
 * Horsepool algorithm is implemented
 * strlength() is used to get string length
 * shifttable () is used to define the shift table
 * horsepool() is used for string matching
 * */
static int strlength(const char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}
static void shifttable(const char p[], int t[150])
{
    int i, j, m;
    m = strlength(p);
    for (i = 0; i < 150; i++)
    {
        t[i] = m;
    }
    for (j = 0; j < m - 1; j++)
    {
        t[p[j]] = m - 1 - j;
    }
}
static int horspool(const char *src, const char *p)
{
    int t[150];
    shifttable(p, t);
    int i, j, k, m, n;
    n = strlength(src);
    m = strlength(p);
    i = m - 1;

    while (i < n)
    {
        k = 0;
        while ((k < m) && (p[m - 1 - k] == src[i - k]))
        {
            k++;
        }
        if (k == m)
        {
            return 1;
        }
        else
        {
            i += t[src[i]];
        }
    }
    return 0;
}
/**
 * Helper functions for Q8
 * a new struct is defined here
 * this struct us used to keep track of the parent and the visit status of each node
 * path_gen() is used to generate path
 * d_cycle() indicates dfs 
 * */
struct pv
{
    int visited;
    int parent;
};
typedef struct pv pv;
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
    if (*min > mini && count == n - 1 )
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
// YOUR SOLUTIONS BELOW
/**
 * bfs approach is used
 * when the destination is reached, loop breaks and returns 1
 * if destination cannot be reached, returns a 0
 * */
int q1(int n, const connection_t connections[n][n])
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i != j)
            {
                int flag = 0, k;
                int source = i;
                int dest = j;
                int qr = -1;
                // Initialise visited list and queue (init 0)
                int visited[n];
                int queue[n];
                for (k = 0; k < n; k++)
                {
                    visited[k] = 0;
                    queue[k] = 0;
                }
                // Loop
                append(queue, source, &qr);
                visited[source] = 1;
                int vertex;
                // While queue is not empty
                while (qr != -1)
                {
                    vertex = delete (queue, &qr);

                    // Destination reached
                    if (vertex == dest)
                    {
                        flag = 1;
                        break;
                    }
                    int i;
                    for (i = 0; i < n; ++i)
                    {
                        if (i != vertex && connections[vertex][i].distance < INT_MAX && !visited[i])
                        {
                            visited[i] = 1;
                            append(queue, i, &qr);
                        }
                    }
                }
                /*free(visited);
                free(queue);*/
                if (flag == 0)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
/**
 * an iterative dfs approach is taken
 * returns 1 or 0 based on the number of flights taken
 * */
int q2(const airport_t *src, const airport_t *dest, int n, int k,
       const connection_t connections[n][n])
{
    int visited[n], i = 0, stack[n], top = -1, vertex, flag = 0, num = 0;
    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    push(&top, src->num_id, stack); // pushing source
    visited[src->num_id] = 1;
    vertex = src->num_id;
    while (top > -1) // top is stack pointer
    {
        for (i = 0; i < n; i++)
        {
            flag = 0;
            if (vertex == dest->num_id)
            {
                if (num <= k) // returns 1 only if the number of flights taken is lesser or equal to constrain
                {
                    return 1;
                }
                break;
            }
            if (vertex != i && visited[i] == 0 && connections[vertex][i].distance != INT_MAX)
            {
                push(&top, i, stack); // pushing vertex
                visited[i] = 1;
                num++;
                flag = 1;
                vertex = i;
                break;
            }
        }
        if (flag == 0) // enters when there is no more vertices to push
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
/**
 * dfs is used to check for a cycle
 * the function would return 1 if a cycle is found
 * returns 0 when no cycle is found from src
 * */
int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    int visited[n], k, i = 0;
    for (k = 0; k < n; k++)
    {
        visited[k] = 0;
    }
    int val = dfs_helper(n, connections, src->num_id, visited, src->num_id);
}
/**
 * Quick sort is used to sort the array in place 
 * */
void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{
    quickSort(airport_list, 0, n - 1, predicate_func);
}

/**
 * Used to compare the longest prefix
 * */
pair_t q5(int n, airport_t airports[n])
{
     int i,j,max=-1,count;
    pair_t ans={-1,-1};
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            count=compare_airport(airports[i].airport_name,airports[j].airport_name);
            if (count!=0 && count>max)
            {
                max=count;
                ans.first=i;
                ans.second=j;
            }
            
        }
    }
    return ans;
}
 /**
  * Binary search is used to find the number of airports
  * */
int q6(int n, int amount, const int entry_fee[n])
{
    return binary_search(entry_fee, amount, 0, n);
}
/**
 * Horsepool's algorithm used for string matching 
 * */
void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
    int i;
    for (i = 0; i < n; i++)
    {
        contains[i] = horspool(airports[i].airport_name, pat);
    }
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
/**
 * Prim's Algorithm is used to find the minimum spanning tree
 * parent[i] stores the parent of node i in the MST
 * use_edge is used to store the weights of the unused edges
 * */
int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    int i, count, v, min, vertex, time = 0;
    int parent[n];
    int use_edge[n];
    int vertex_included[n];
    for (i = 0; i < n; i++)
    {
        use_edge[i] = INT_MAX;
        vertex_included[i] = 0;
    }
    use_edge[0] = 0;
    parent[0] = -1;
    for (count = 0; count < n - 1; count++)
    {
        min = INT_MAX;
        for (v = 0; v < n; v++)
        {
            if (vertex_included[v] == 0 && use_edge[v] < min)
            {
                min = use_edge[v], vertex = v;
            }
        }
        vertex_included[vertex] = 1;
        v = 0;
        while (v < n)
        {
            if (vertex != v && connections[vertex][v].distance != INT_MAX && vertex_included[v] == 0 && connections[vertex][v].distance < use_edge[v])
            {
                parent[v] = vertex;
                use_edge[v] = connections[vertex][v].time;
            }
            v++;
        }
    }
    for (i = 1; i < n; i++)
    {
        edges[i - 1].first = parent[i];
        edges[i - 1].second = i;
        time += connections[parent[i]][i].time;
    }
    return time;
}
/**
 * Dijkstra's Algorithm is used to find the shortest path
 * time[i] is used to store the minimum of a node i from src
 * vertex_include[i] stores 1 if the shortest distance of i is computed
 * */
void q10(int n, int k, const airport_t *src,
         const connection_t connections[n][n], const int destinations[k],
         int costs[k])
{
    int i = 0, v, min, index;
    int time[n];
    int vertex_include[n];
    while (i < n)
    {
        time[i] = INT_MAX;
        vertex_include[i] = 0;
        i++;
    }
    time[src->num_id] = 0;
    for (i = 0; i < n - 1; i++)
    {
        min = INT_MAX;
        for (v = 0; v < n; v++)
        {
            if (vertex_include[v] == 0 && time[v] < min)
            {
                min = time[v];
                index = v;
            }
        }
        vertex_include[index] = 1;
        v = 0;
        while (v < n)
        {
            if (vertex_include[v] == 0 && index != v && connections[index][v].distance < INT_MAX && time[index] < INT_MAX)
            {
                if ((time[index] + connections[index][v].time) < time[v])
                {
                    time[v] = time[index] + connections[index][v].time;
                }
            }
            v++;
        }
    }
    v = 0;
    while (v < k)
    {
        costs[v] = time[destinations[v]];
        v++;
    }
}
// END