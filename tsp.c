//
// Student name
// Student name
// ...
//
// AED, 2018/2019
//
// solution of the traveling salesman problem
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "cities.h"
#include "elapsed_time.h"
#include "permutations.h"

//
// record best solutions
//

static int min_length, max_length;
static int min_tour[max_n_cities + 1], max_tour[max_n_cities + 1];
static long n_tours, hist[10000];

//
// first solution (brute force, distance computed at the end, compute best and worst tours)
//

void tsp_v1(int n, int m, int *a)
{
  int i, t;

  if (m < n - 1)
    for (i = m; i < n; i++)
    {
      t = a[m];
      a[m] = a[i];
      a[i] = t;
      tsp_v1(n, m + 1, a);
      t = a[m];
      a[m] = a[i];
      a[i] = t;
    }
  else
  { // visit permutation
    n_tours++;
    // modify the following code to do your stuff
    int soma = 0;
    a[n] = a[0];

    for (i = 0; i < n; i++)
    {
      int deumaparaoutra = cities[a[i]].distance[a[i + 1]];
      soma = soma + deumaparaoutra;
    }

    if (soma < min_length)
    {
      min_length = soma;
      for (i = 0; i < n; i++)
      {
        min_tour[i] = a[i];
      }
    }
    if (soma > max_length)
    {
      max_length = soma;
      for (i = 0; i < n; i++)
      {
        max_tour[i] = a[i];
      }
    }

    hist[(soma < 10000) ? soma : 9999]++;
  }
}

void tsp_v2(int n, int m, int *a)
{
  int i;
  int soma = 0;

  a[n] = a[0];

  for (i = 0; i < n; i++)
  {
    int deumaparaoutra = cities[a[i]].distance[a[i + 1]];
    soma = soma + deumaparaoutra;
  }

  if (soma < min_length)
  {
    min_length = soma;
    for (i = 0; i < n; i++)
    {
      min_tour[i] = a[i];
    }
  }
  if (soma > max_length)
  {
    max_length = soma;
    for (i = 0; i < n; i++)
    {
      max_tour[i] = a[i];
    }
  }
}

//
// main program
//

int main(int argc, char **argv)
{
  int n_mec, special, n, i, j, a[max_n_cities];
  char file_name[32];
  double dt1;
  FILE *fp = NULL;

  n_mec = 0; // CHANGE THIS!
  special = 0;
  init_cities_data(n_mec, special);
  printf("data for init_cities_data(%d,%d)\n", n_mec, special);
  fflush(stdout);

  for (n = 3; n < 15; n++)
  {
    //
    // try tsp_v1
    //
    dt1 = -1.0;
    if (n <= 16)
    {
      (double)elapsed_time();
      for (i = 0; i < n; i++)
        a[i] = i;
      min_length = 1000000000;
      max_length = 0;
      n_tours = 0l;
      tsp_v1(n,1,a); // no need to change the starting city, as we are making a tour
/*       for (j = 0; j < 1000000; j++)
      {
        if (n == 12)
        {
          rand_perm(n, a);
          tsp_v2(n, 1, a);
        }
      } */
      dt1 = elapsed_time();

      fp = fopen("data.txt", "w");
      for (int k = 0; k < 10000; k++)
      {
        fprintf(fp, "%d %ld\n", k, hist[k]);
      }

      fclose(fp);

      printf("tempo: %f\n", dt1);
      printf("tsp_v1() finished in %8.3fs (%ld tours generated)\n", dt1, n_tours);
      printf("  min %5d [", min_length);
      for (i = 0; i < n; i++)
        printf("%2d%s", min_tour[i], (i == n - 1) ? "]\n" : ",");
      printf("  max %5d [", max_length);
      for (i = 0; i < n; i++)
        printf("%2d%s", max_tour[i], (i == n - 1) ? "]\n" : ",");
      fflush(stdout);
      if (argc == 2 && strcmp(argv[1], "-f") == 0)
      {
        min_tour[n] = -1;
        sprintf(file_name, "min_%02d.svg", n);
        make_map(file_name, min_tour);
        max_tour[n] = -1;
        sprintf(file_name, "max_%02d.svg", n);
        make_map(file_name, max_tour);
      }
    }
  }
  return 0;
}
