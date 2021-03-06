#include "PinnedMemoryAllocator.h"

#include "Context.h"

#if AT_CUDA_ENABLED()
#include <THC/THC.h>
#endif

#include <stdexcept>

namespace at {

void* PinnedMemoryAllocator::allocate(std::size_t n) const {
  auto state = globalContext().lazyInitCUDA();
#if AT_CUDA_ENABLED()
  return state->cudaHostAllocator->malloc(nullptr, n);
#else
  throw std::runtime_error("pinned memory requires CUDA");
#endif
}

void PinnedMemoryAllocator::deallocate(void* ptr) const {
  auto state = globalContext().lazyInitCUDA();
#if AT_CUDA_ENABLED()
  return state->cudaHostAllocator->free(nullptr, ptr);
#else
  throw std::runtime_error("pinned memory requires CUDA");
#endif
}

}
