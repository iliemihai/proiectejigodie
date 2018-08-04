#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <time.h>
#include <cstddef>
#include <vector>
#include "allocator.h"

class BenchmarkResults {
public:
    long nOperations;
    double elapsedTime;
    float operationsPerSec;
    float timePerOperation;
    int memoryPeak;
};

class Benchmark {
public:
    Benchmark(const unsigned int nOperations);

    void SingleAllocation(Allocator* allocator, const std::size_t size, const std::size_t allignment);
    void SingleFree(Allocator* allocator,const std::size_t size, const std::size_t allignment);

    void MultipleAllocation(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& allignments);
    void MultipleFree(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& allignments);

    void RandomAllocation(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& allignments);
    void RandomFree(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& allignments);

private:
    void printResult(const BenchmarkResults& results) const;
    void setTimer(timespec& timer);
    void RandomAllocationAttr(const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& allignments, std::size_t& size, std::size_t& allignment);

    const double CalculateElapsedTime() const;
    const BenchmarkResults buildResults(const unsigned int nOperations, const double elapsedTime, const std::size_t MemoryUsed) const;

    unsigned int m_nOperations;
    timespec m_start, m_end;
};

#endif
