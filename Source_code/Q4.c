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

void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *), airport_t airport_list[n])
{
    quickSort(airport_list, 0, n - 1, predicate_func);
}
int main()
{
    // Q4
    {
        int n = 5;
        airport_t q4_t1_airport_list[5] = {
            {0, "BLR"}, {1, "SUR"}, {2, "DEL"}, {3, "NEL"}, {4, "MUM"}};

        q4(n, t1_predicate_func, q4_t1_airport_list);
        int k;
        for(k=0;k<n;k++)
        {
            printf("Num : %d Name : %s\n",q4_t1_airport_list[k].num_id,q4_t1_airport_list[k].airport_name);
        }
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
        int k;
        for(k=0;k<n;k++)
        {
            printf("Num : %d Name : %s\n",q4_t2_airport_list[k].num_id,q4_t2_airport_list[k].airport_name);
        }
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
        int k;
        for(k=0;k<n;k++)
        {
            printf("Num : %d Name : %s\n",q4_t3_airport_list[k].num_id,q4_t3_airport_list[k].airport_name);
        }
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