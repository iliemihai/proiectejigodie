#include "c_allocator.h"
#include <stdlib.h>

CAllocator::CAllocator() : Allocator(0)
{}

void CAllocator::Init()
{}

CAllocator::~CAllocator()
{}

void* CAllocator::Allocate(const std::size_t size, const std::size_t allignment)
{
  return malloc(size);
}

void CAllocator::Free(void* ptr)
{
  free(ptr);
}
