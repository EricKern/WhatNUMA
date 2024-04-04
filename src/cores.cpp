#include<stdio.h>
#include <numa.h>
#include <sched.h>

int main(int argc, char const *argv[])
{
  int available = numa_available();
  printf("numa available: %d\n", available);

  unsigned int cpu, node;
  getcpu(&cpu, &node);
  printf("cpu: %d, node: %d\n", cpu, node);

  int numa_node = numa_node_of_cpu(cpu);

  printf("cpu: %d, node: %d\n", cpu, numa_node);

  return 0;
}
