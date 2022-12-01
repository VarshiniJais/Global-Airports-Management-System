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
int compare_airport(const char *a1,const char *a2)
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
int main()
{
    // Q5
    {
        airport_t q5_t1_airports[] = {{0, "KOC"}, {1, "KIA"}, {2, "KOL"}};

        pair_t q5_t1_result = q5(3, q5_t1_airports);
        if ((q5_t1_result.first == 0 && q5_t1_result.second == 2) ||
            (q5_t1_result.first == 2 && q5_t1_result.second == 0))
        {
            printf("Q5 TestCase 1: " PASSED);
        }
        else
        {
            printf("Q5 TestCase 1: " FAILED);
        }
    }
    {
        airport_t q5_t2_airports[] = {{0, "BLR"}, {1, "MUM"}, {2, "KOL"}};
        pair_t q5_t2_result = q5(3, q5_t2_airports);

        if (q5_t2_result.first == -1 && q5_t2_result.second == -1)
        {
            printf("Q5 TestCase 2: " PASSED);
        }
        else
        {
            printf("Q5 TestCase 2: " FAILED);
        }
    }
}