#include <math.h>
#include <assert.h>
#include <stdlib.h>

void rand_perm(int n, int a[])
{
    int i, j, k;
    for (i = 0; i < n; i++)
        a[i] = i;
    for (i = n - 1; i > 0; i--)
    {
        j = (int)floor((double)(i + 1) * (double)rand() / (1.0 + (double)RAND_MAX)); // range 0..i
        assert(j >= 0 && j <= i);
        k = a[i];
        a[i] = a[j];
        a[j] = k;
    }
}