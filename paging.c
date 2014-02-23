
#include <paging.h>
#include <types.h>
#include <screen.h>
#include <memlayout.h>

static void paging_set_entry(page_entry_t *entry, uint32_t addr, uint32_t flags);
static __inline__ void write_cr3(uint32_t page_directory);
static __inline__ uint32_t read_cr0();
static __inline__ void write_cr0(uint32_t page_directory);

void init_paging() {
  page_entry_t *page_directory = (page_entry_t *) PDE_START;

  page_entry_t *page_table = (page_entry_t *) PTE_START;

  uint32_t address = 0;
  uint32_t i, j;


  for(i=0; i<PHY_MEM_MAX_IN_PDS; i++) { // maps MEM_TOTAL memory

  /*   // maps 4MB of physical memory */
    for(j=0; j<1024; j++) {
      paging_set_entry(&page_table[j], address, PG_PRESENT | PG_RW);
      address += PAGE_SIZE; // 4kb
    }
    paging_set_entry(&page_directory[i], (uint32_t) page_table, PG_PRESENT | PG_RW); // sets 4MB of virtual memory

    page_table += PTE_SIZE; // moves 4096 bytes (a page entry) forward
  }

  
  for(i=PHY_MEM_MAX_IN_PDS; i<1024; i++) { // fills up the rest of the page directory
    paging_set_entry(&page_directory[i], 0, 0);
  }

  write_cr3((uint32_t) page_directory); // put the page directory address into CR3

  write_cr0(((uint32_t) read_cr0() | 0x80000000)); // set the paging bit in CR0 to 1
  

}

static void paging_set_entry(page_entry_t *entry, uint32_t addr, uint32_t flags) {

  entry->addr = (uint32_t) addr >> 12; // only upper 20 bits are used, and this ensures that the page is 4k aligned
  entry->present = flags & PG_PRESENT;
  entry->rw = flags & PG_RW;
  entry->user = flags & PG_USER;
  entry->pwt = 0; // lets make it writethrough
  entry->pcd = 0; // and cacheable
  entry->acessed = 0;
  entry->ign = 0;
  entry->avl = 0;

}

static __inline__ void write_cr3(uint32_t page_directory) {
  //"a"(data) means : load EAX with data
  __asm__ __volatile__ ("movl %%eax, %%cr3" : : "a" (page_directory));
}


static __inline__ uint32_t read_cr0() {
  uint32_t result;
  __asm__ __volatile__ ("movl %%cr0, %%eax" : "=a" (result) : );
  return result;

}

static __inline__ void write_cr0(uint32_t page_directory) {
  __asm__ __volatile__ ("movl %%eax, %%cr0" : : "a" (page_directory));
}
