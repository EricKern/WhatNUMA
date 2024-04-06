#include <cstdio>
#include <omp.h>
#include <numa.h>   // for other numa stuff
#include <numaif.h> // for get_mempolicy
#include <sched.h>

#include <vector>
#include <memory>
// Allocator adaptor that interposes construct() calls to
// convert value initialization into default initialization.
template <typename T, typename A=std::allocator<T>>
class default_init_allocator : public A {
  typedef std::allocator_traits<A> a_t;
public:
  template <typename U> struct rebind {
    using other =
      default_init_allocator<
        U, typename a_t::template rebind_alloc<U>
      >;
  };

  using A::A;

  template <typename U>
  void construct(U* ptr)
    noexcept(std::is_nothrow_default_constructible<U>::value) {
    ::new(static_cast<void*>(ptr)) U;
  }
  template <typename U, typename...Args>
  void construct(U* ptr, Args&&... args) {
    a_t::construct(static_cast<A&>(*this),
                   ptr, std::forward<Args>(args)...);
  }
};

int main(int argc, char const *argv[])
{
  if (numa_available() < 0) {
    std::printf("NUMA not available on this system\n");
    return 1;
  }

  std::printf("CPU/Thread/NUMA-Node distribution\n\n");
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    // int cpu = sched_getcpu();
    uint cpu0, node0;
    getcpu(&cpu0, &node0);
    #pragma omp critical
    {
      std::printf("CPU: %d, Thread: %d, Node: %d", cpu0, tid, node0);
    }
  }

  std::vector<int, default_init_allocator<int>> thread_data{omp_get_max_threads()};
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    thread_data[tid] = 0;
  }
  std::printf("Vector initialization complete\n");

  for (size_t i = 0; i < thread_data.size(); ++i)
  {
    int* data = thread_data.data() + i;
    int node = -1;
    int status = get_mempolicy(&node, nullptr, 0, data, MPOL_F_NODE | MPOL_F_ADDR);
    if (status < 0) {
      std::printf("Failed to get memory policy");
      return 1;
    }
    std::printf("i: %03ld, NUMA node: %d", i, node);
  }


  return 0;
}
