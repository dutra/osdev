#ifndef MEMLAYOUT_H
#define MEMLAYOUT_H

#define PDE_START 0x00100000 // physical memory position of the Page Directory Entry
#define PTE_START 0x00101000 // physical memory position of the first Page Table Entry

#define PDE_SIZE 0x1000 // Memory size of a Page Directory Entry
#define PTE_SIZE 0x1000 // Memory size of a single Page Table Entry

#define PAGE_SIZE 0x1000 // Page Size

#define PHY_MEM_MAX 0x4000000 // Max amount of physical memory to be mapped
#define PHY_MEM_MAX_IN_PDS PHY_MEM_MAX/1024/1024/4 // each Page Directory maps 4MB of memory

#endif /* MEMLAYOUT_H */
