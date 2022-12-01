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
static int strlength(const char str[])
{
    int i=0;
    while(str[i]!='\0')
    {
        i++;
    }
    return i;
}
static void shifttable(const char p[],int t[150]) 
{
	int i,j,m;
	m=strlength(p);
	for (i=0;i<150;i++)
    {
        t[i]=m;
    }
	for (j=0;j<m-1;j++)
	{
        t[p[j]]=m-1-j;
    }

    //printf("\n");
}
static int horspool(const char *src,const char *p) 
{
    int t[150];
    shifttable(p,t); 
	int i,j,k,m,n;
	n=strlength(src);
	m=strlength(p);
	i=m-1;
    
	while(i<n) 
    {
		k=0;
		while((k<m)&&(p[m-1-k]==src[i-k]))
        {
            k++;
        }
		if(k==m)
        {
            return 1;
        }
		else
        {
            i+=t[src[i]];
        }
	}
	return 0;
}
void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
    int i;
    for(i=0;i<n;i++)
    {
        contains[i]=horspool(airports[i].airport_name,pat);
    }
}
int main()
{
    // Q7
    {
        int n = 3;
        const char *pat = "KO";
        int contains[3] = {0, 0, 0};
        airport_t q7_t1_airports[] = {{0, "KOCHI"}, {1, "KIA"}, {2, "KOLKATA"}};

        q7(n, pat, contains, q7_t1_airports);

        if (contains[0] == 1 && contains[1] == 0 && contains[2] == 1)
        {
            printf("Q7 TestCase 1: " PASSED);
        }
        else
        {
            printf("Q7 TestCase 1: " FAILED);
        }
    }
    {
        int n = 3;
        const char *pat = "U";
        int contains[3] = {0, 0, 0};
        airport_t q7_t2_airports[] = {{0, "BLR"}, {1, "MUM"}, {2, "KOL"}};

        q7(n, pat, contains, q7_t2_airports);

        if (contains[0] == 0 && contains[1] == 1 && contains[2] == 0)
        {
            printf("Q7 TestCase 2: " PASSED);
        }
        else
        {
            printf("Q7 TestCase 2: " FAILED);
        }
    }
}