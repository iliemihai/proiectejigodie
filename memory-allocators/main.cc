#include "./linear_allocator/linear_allocator.h"
#include "./c_allocator/c_allocator.h"
#include "./include/allocator.h"
#include "./include/benchmark.h"
#include "./include/utils.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
  const std::vector<std::size_t> ALLOC_SIZES {32, 64, 128, 256, 512, 1024, 2048, 4096};
  const std::vector<std::size_t> ALLIGNMENTS {8, 8, 8, 8, 8, 8, 8, 8};

  Allocator* c_allocator = new CAllocator();
  Allocator* linear_allocator = new LinearAllocator(1e9);

  Benchmark bench(1e1);

  std::cout << "CUSTOM\n";
  bench.MultipleAllocation(c_allocator, ALLOC_SIZES, ALLIGNMENTS);
  // /bench.MultipleFree(linear_allocator, ALLOC_SIZES, ALLIGNMENTS);
  bench.RandomAllocation(c_allocator, ALLOC_SIZES, ALLIGNMENTS);

  std::cout << "LINEAR\n";
  bench.MultipleAllocation(linear_allocator, ALLOC_SIZES, ALLIGNMENTS);
  // /bench.MultipleFree(linear_allocator, ALLOC_SIZES, ALLIGNMENTS);
  bench.RandomAllocation(linear_allocator, ALLOC_SIZES, ALLIGNMENTS);

  delete c_allocator;
  delete linear_allocator;
  return 0;
}
