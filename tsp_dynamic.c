//
//
// Student name
// ...
//
// AED, 2018/2019
//
// solution of the traveling salesman problem with dynamic programming
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "cities.h"
#include "elapsed_time.h"

static int best_distance[max_n_cities][1 << 18];
static int best_path[max_n_cities][1 << 18];

int tsp_dynamic(int n, int dest, int mask)
{
  if (mask == ((1 << n) - 1)) // última cidade retorna o caminho de volta à origem
  {
    best_path[dest][mask] = -1;
    return best_distance[dest][mask] = cities[dest].distance[0];
  }
  if (best_distance[dest][mask] != -1) // retornar distância calculada anteriormente
    return best_distance[dest][mask];

  int i, short_i = -1, short_distance = 10000, new_distance;
  for (i = 1; i < n; i++)
  {
    if ((mask & (1 << i)) == 0) // evita calcular caminhos com cidades repetidas
    {
      new_distance = tsp_dynamic(n, i, mask | (1 << i)) + cities[dest].distance[i];
      if (new_distance < short_distance)
      {
        short_distance = new_distance;
        short_i = i;
      }
    }
  }
  best_path[dest][mask] = short_i;
  return best_distance[dest][mask] = short_distance;
}

//
// main program
//

int main(int argc, char **argv)
{
  int n_mec, special, n;

  n_mec = 68826; // CHANGE THIS!
  special = 1;
  init_cities_data(n_mec, special);
  printf("data for init_cities_data(%d,%d)\n", n_mec, special);
  fflush(stdout);

  for (n = 3; n <= n_cities; n++)
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < (1 << n); j++)
        best_distance[i][j] = -1;

    int best = tsp_dynamic(n, 0, 1);
    printf("First %d cities: %d\n", n, best);

    printf("Best path: ");

    int dest, mask;
    dest = 0;
    mask = 1;
    while (dest >= 0)
    {
      printf("%d ", dest);
      dest = best_path[dest][mask];
      mask |= 1 << dest;
    }
    printf("\n");
  }
  double dt2 = elapsed_time();
  printf("Finished in %8.3fs\n", dt2);

  printf("\n");
  return 0;
}
