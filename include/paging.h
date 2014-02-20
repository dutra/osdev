#ifndef PAGING_H
#define PAGING_H

#include <types.h>

typedef struct page_entry_struct {
  uint32_t present : 1; // Present bit. Indicates whether the page is present. Page fault occurs if 0 and program tried to access this page
  uint32_t rw : 1; // Read / Write bit. 1 for write/read, 0 for read-only
  uint32_t user : 1; // Available for user access if 1. Supervisor only if 0.
  uint32_t pwt : 1; // Page-level Writethrough bit. If 0, physical page has a writeback caching policy. If 1, writethrough.
  uint32_t pcd : 1; // Page-level Cache Disable bit. If 0, physical page is cacheable. If 1, not cacheable.
  uint32_t acessed : 1; // Access bit set by the processor on the first time it access this memory location.
  uint32_t ign : 3; // Ignored bits
  uint32_t avl : 3; // Available to Software bit. These bits can be used by the kernel.
  uint32_t addr : 20; // Address
}  page_entry_t;

void init_paging();

#endif /* PAGING_H */
