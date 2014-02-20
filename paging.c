
#include <paging.h>
#include <types.h>
#include <screen.h>

static void paging_set_entry(page_entry_t *entry, uint32_t addr, uint32_t present, uint32_t rw, uint32_t user);
static __inline__ void write_cr3(uint32_t page_directory);
static __inline__ uint32_t read_cr0();
static __inline__ void write_cr0(uint32_t page_directory);

void init_paging() {
  page_entry_t *page_directory = (page_entry_t *) 0x9C000;

  page_entry_t *page_table = (page_entry_t *) 0x9D000;

  uint32_t address = 0;
  uint32_t i;

  // map the first 4MB of physical memory
  for(i=0; i<1024; i++) {
    paging_set_entry(page_table+i, address, 1, 1, 0);
    address += 4096; // 4kb
  }

  paging_set_entry(page_directory+0, (uint32_t) page_table, 1, 1, 0); // sets first 4MB of virtual memory

  for(i=1; i<1024; i++) { // fills up the rest of the page directory
    paging_set_entry(page_directory+i, 0, 0, 1, 0);
  }

  write_cr3((uint32_t) page_directory); // put the page directory address into CR3
  write_cr0(((uint32_t) read_cr0() | 0x80000000)); // set the paging bit in CR0 to 1
  
  
}

static void paging_set_entry(page_entry_t *entry, uint32_t addr, uint32_t present, uint32_t rw, uint32_t user) {

  entry->addr = (uint32_t) addr >> 12; // only upper 20 bits are used, and this ensures that the page is 4k aligned
  entry->present = present;
  entry->rw = rw;
  entry->user = user;
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
