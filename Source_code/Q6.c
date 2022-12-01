#include "header.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#define PASSED "PASSED\n"
#define FAILED "FAILED\n"
/*
 * @param n: Total number of airports
 * @param amount: Amount of money you have
 * @param entry_fee: *Sorted* array containing entry fee of all airports
 *
 * @return_value: Number of airports you may be able to visit given the amount
 * of money available to you
 */
int binary_search(const int array[], int x, int low, int high)
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
int q6(int n, int amount, const int entry_fee[n])
{
    return binary_search(entry_fee, amount, 0, n);
}
int main()
{
    // Q6
    int q6_t1_entry_fee[] = {1, 2, 5, 10, 20, 25};
    int n = 6;

    int amount = 10;
    if (q6(n, amount, q6_t1_entry_fee) == 4)
    {
        printf("Q6 TestCase 1: " PASSED);
    }
    else
    {
        printf("Q6 TestCase 1: " FAILED);
    }

    amount = 30;
    if (q6(n, amount, q6_t1_entry_fee) == 6)
    {
        printf("Q6 TestCase 2: " PASSED);
    }
    else
    {
        printf("Q6 TestCase 2: " FAILED);
    }
}