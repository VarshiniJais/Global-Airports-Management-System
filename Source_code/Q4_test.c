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

int t1_predicate_func(const airport_t *x, const airport_t *y)
{
    return strcmp(x->airport_name, y->airport_name) < 0;
}

int t2_predicate_func(const airport_t *x, const airport_t *y)
{
    return strcmp(x->airport_name, y->airport_name) > 0;
}

int t3_predicate_func(const airport_t *x, const airport_t *y)
{
    return (x->num_id % 10) < (y->num_id % 10);
}
int check_sorted(int n, const airport_t arr[n],
                 int (*predicate)(const airport_t *, const airport_t *))
{
    int i;
    for (i = 0; i < n - 1; ++i)
    {
        if (predicate(&arr[i + 1], &arr[i]))
            return 0;
    }
    return 1;
}
static int partition(int low, int n, int (*predicate_func)(const airport_t *, const airport_t *), airport_t airport_list[n])
{
    //printf("partition\n");
    int cmp;
    int pivot = low;
    int i = low + 1;
    int j = n-1;
    airport_t temp;
    while (i < j)
    { // to make sure i and j do not cross over
        cmp=predicate_func(&airport_list[i], &airport_list[pivot]);
        while (i < n && cmp)
        {
            cmp=predicate_func(&airport_list[i], &airport_list[pivot]);    
            i++;
        }
        cmp=predicate_func(&airport_list[pivot], &airport_list[j]);
        while (j > low && cmp)
        {
            cmp=predicate_func(&airport_list[pivot], &airport_list[j]);
            j--;
        }
        printf("i : %d\n",i);
        printf("j : %d\n", j);
        //printf("low : %d\n",low);
        if (i < j)
        {
            temp = airport_list[i];
            airport_list[i] = airport_list[j];
            airport_list[j] = temp;
        }
    }
    if (j != low)
    {
        temp=airport_list[low];
        airport_list[low] = airport_list[j];
        airport_list[j] = temp;
    }
    return j;
}
static void quick_sort(int low, int n, int (*predicate_func)(const airport_t *, const airport_t *), airport_t airport_list[n])
{
    //printf("quick sort\n");
    int a;
    if (low < n)
    {
        a = partition(low, n, predicate_func, airport_list);
        quick_sort(low, a - 1, predicate_func, airport_list);
        quick_sort(a + 1, n, predicate_func, airport_list);
    }
}
void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{
    // sort using quick sort
    quick_sort(0, n,predicate_func,airport_list);
}
int main()
{
    // Q4
    {
        int n = 5;
        airport_t q4_t1_airport_list[5] = {
            {0, "BLR"}, {1, "SUR"}, {2, "DEL"}, {3, "NEL"}, {4, "MUM"}};

        q4(n, t1_predicate_func, q4_t1_airport_list);
       /* int k;
        for(k=0;k<n;k++)
        {
            printf("Num : %d Name : %s\n",q4_t1_airport_list[k].num_id,q4_t1_airport_list[k].airport_name);
        }*/
        if (check_sorted(n, q4_t1_airport_list, t1_predicate_func))
        {
            printf("Q4 TestCase 1: " PASSED);
        }
        else
        {
            printf("Q4 TestCase 1: " FAILED);
        }
    }
    {
        int n = 5;
        airport_t q4_t2_airport_list[5] = {
            {0, "BLR"}, {1, "SUR"}, {2, "DEL"}, {3, "NEL"}, {4, "MUM"}};

        q4(n, t2_predicate_func, q4_t2_airport_list);
       /* int k;
        for(k=0;k<n;k++)
        {
            printf("Num : %d Name : %s\n",q4_t2_airport_list[k].num_id,q4_t2_airport_list[k].airport_name);
        }*/
        if (check_sorted(n, q4_t2_airport_list, t2_predicate_func))
        {
            printf("Q4 TestCase 2: " PASSED);
        }
        else
        {
            printf("Q4 TestCase 2: " FAILED);
        }
    }
    {
        int n = 5;
        airport_t q4_t3_airport_list[5] = {
            {0, "BLR"}, {10, "NEL"}, {11, "SUR"}, {22, "DEL"}, {4, "MUM"}};

        q4(n, t3_predicate_func, q4_t3_airport_list);
        /*int k;
        for(k=0;k<n;k++)
        {
            printf("Num : %d Name : %s\n",q4_t3_airport_list[k].num_id,q4_t3_airport_list[k].airport_name);
        }*/
        if (check_sorted(n, q4_t3_airport_list, t3_predicate_func))
        {
            printf("Q4 TestCase 3: " PASSED);
        }
        else
        {
            printf("Q4 TestCase 3: " FAILED);
        }
    }
}