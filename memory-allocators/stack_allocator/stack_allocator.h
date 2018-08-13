#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include "../include/allocator.h"


class StackAllocator : public Allocator {
protected:
	void* m_start_ptr = nullptr;
	std::size_t m_offset;
public:
	StackAllocator(const std::size_t totalSize);
	virtual ~StackAllocator();
	virtual void* Allocate(const std::size_t size, const std::size_t allignment=0) override;
	virtual void Free(void* ptr);
	virtual void Init() override;
	virtual void Reset();
private:
	StackAllocator(StackAllocator& stackAllocator);
	struct AllocationHeader {
		char padding;
	};
};
#endif