#ifndef C_ALLOCATOR_H
#define C_ALLOCATOR_H

#include "../include/allocator.h"

class CAllocator : public Allocator
{
public:
  CAllocator();
  virtual ~CAllocator();
  virtual void* Allocate(const std::size_t size, const std::size_t allignment=0) override;
  virtual void Free(void* ptr) override;
  virtual void Init() override;
};

#endif
