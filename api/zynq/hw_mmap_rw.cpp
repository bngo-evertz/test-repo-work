#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "hw_mmap_rw.h"

//#define DEBUG_MEMRW

#ifdef DEBUG_MEMRW
#include <stdio.h>

int mem_debug_verbose=0x0;

// debug flag
enum {
  HW_MEM_DEBUG_READ  = 0x0001,
  HW_MEM_DEBUG_WRITE = 0x0002,
  HW_MEM_DEBUG_ALL   = 0xFFFF,
};
#endif

uint32_t readl(int addr)
{
  unsigned long * mem = 0;
  int fd = openmem(&mem, addr);
  if (fd < 0)
    return 0xFFFFFFFF;

  uint32_t val = mem[ADDR2IDX(addr)];

#ifdef DEBUG_MEMRW
  if (HW_MEM_DEBUG_READ & mem_debug_verbose)
    printf("READ %08X=%08x\n", addr, val);
#endif

  closemem(mem, fd);
  return val;
}

uint32_t readl_burst(int addr, int len, uint32_t* data)
{
  unsigned long * mem = 0;
  int fd = openmem(&mem, addr);
  if (fd < 0)
    return 0xFFFFFFFF;
  // Go through volatile pointer to avoid issues with caching
  volatile uint32_t* mem_v = (volatile uint32_t*)mem;

  uint32_t* ptr = data;
  for (int i=0; i<len; i++) {
    *ptr = mem_v[ADDR2IDX(addr)];
#ifdef DEBUG_MEMRW
    if (HW_MEM_DEBUG_READ & mem_debug_verbose)
      printf("READ %08X=%08x\n", addr, *ptr);
#endif
    ptr++;
  }


  closemem(mem, fd);
  return 0;
}

uint64_t readll(int addr)
{
  unsigned long * mem = 0;
  volatile unsigned long * safe_mem;
  int fd = openmem(&mem, addr);
  if (fd < 0)
    return 0xFFFFFFFFFFFFFFFF;

  safe_mem = mem;

  uint32_t vall = safe_mem[ADDR2IDX(addr)];
  uint32_t valh = safe_mem[ADDR2IDX(addr+4)];
  uint64_t val = ((uint64_t)valh<<32) | vall;

#ifdef DEBUG_MEMRW
  if (HW_MEM_DEBUG_READ & mem_debug_verbose)
    printf("READ %08X=%016llx\n", addr, val);
#endif

  closemem(mem, fd);
  return val;
}

uint32_t readll_burst(int addr, int len, uint64_t* data)
{
  unsigned long * mem = 0;
  int fd = openmem(&mem, addr);
  if (fd < 0)
    return 0xFFFFFFFF;
  volatile uint32_t* mem_v = (volatile uint32_t*)mem;

  uint64_t* ptr = data;
  for (int i=0; i<len; i++) {
    uint32_t vall = mem_v[ADDR2IDX(addr)];
    uint32_t valh = mem_v[ADDR2IDX(addr+4)];
    *ptr = ((uint64_t)valh<<32) | vall;
#ifdef DEBUG_MEMRW
    if (HW_MEM_DEBUG_READ & mem_debug_verbose)
      printf("READ %08X=%016llx\n", addr, val);
#endif
    ptr++;
  }

  closemem(mem, fd);
  return 0;
}

uint32_t writel(int addr, uint32_t val) {
  unsigned long * mem = 0;
  int fd = openmem(&mem, addr);
  if (fd < 0)
    return 0xFFFFFFFF;

#ifdef DEBUG_MEMRW
  if (HW_MEM_DEBUG_WRITE & mem_debug_verbose)
    printf("WRITE %08X=%08x --> %08x\n", addr, (unsigned)(mem[ADDR2IDX(addr)]), val);
#endif

  mem[ADDR2IDX(addr)] = val;

  closemem(mem, fd);
  return 0;
}

uint32_t writel_burst(int addr, int len, uint32_t* val) {
  unsigned long * mem = 0;
  int fd = openmem(&mem, addr);
  if (fd < 0)
    return 0xFFFFFFFF;
  // Go through volatile pointer to avoid issues with caching
  volatile uint32_t* mem_v = (volatile uint32_t*)mem;

  uint32_t* ptr = val;
  for (int i=0; i<len; i++) {
#ifdef DEBUG_MEMRW
    if (HW_MEM_DEBUG_WRITE & mem_debug_verbose)
      printf("WRITE %08X=%08x --> %08x\n", addr, (unsigned)(mem_v[ADDR2IDX(addr)]), *ptr);
#endif
    mem_v[ADDR2IDX(addr)] = *ptr;
    ptr++;
  }

  closemem(mem, fd);
  return 0;
}

uint32_t writell(int addr, uint64_t val) {
  unsigned long * mem = 0;
  int fd = openmem(&mem, addr);
  if (fd < 0)
    return 0xFFFFFFFF;
  volatile uint32_t* mem_v = (volatile uint32_t*)mem;

#ifdef DEBUG_MEMRW
  if (HW_MEM_DEBUG_WRITE & mem_debug_verbose)
    printf("WRITE %08X=%08x%08x --> %016llx\n", addr, (unsigned)(mem[ADDR2IDX(addr)]), (unsigned)(mem[ADDR2IDX(addr+4)]), val);
#endif

  mem_v[ADDR2IDX(addr+4)] = val>>32;
  mem_v[ADDR2IDX(addr)] = val;

  closemem(mem, fd);
  return 0;
}

uint32_t writell_burst(int addr, int len, uint64_t* val) {
  unsigned long * mem = 0;
  int fd = openmem(&mem, addr);
  if (fd < 0)
    return 0xFFFFFFFF;
  // Go through volatile pointer to avoid issues with caching
  volatile uint32_t* mem_v = (volatile uint32_t*)mem;

  uint64_t* ptr = val;
  for (int i=0; i<len; i++) {
#ifdef DEBUG_MEMRW
    if (HW_MEM_DEBUG_WRITE & mem_debug_verbose)
      printf("WRITE %08X=%08x%08x --> %016llx\n", addr, (unsigned)(mem[ADDR2IDX(addr)]), (unsigned)(mem[ADDR2IDX(addr+4)]), *ptr);
#endif
    mem_v[ADDR2IDX(addr+4)] = *ptr>>32;
    mem_v[ADDR2IDX(addr)] = *ptr;
    ptr++;
  }

  closemem(mem, fd);
  return 0;
}



int openmem(unsigned long **mem, int addr)
{
  int fd = open("/dev/mem", O_RDWR);
  if (fd < 0) {
#ifdef DEBUG_MEMRW
    perror("open /dev/mem");
#endif
    return -1;
  }

  int ps = getpagesize();
  *mem = (unsigned long*)
    mmap(0, ps, PROT_READ | PROT_WRITE, MAP_SHARED, fd, addr & -ps);

  if ((void*) -1 == *mem) {
#ifdef DEBUG_MEMRW
    perror("mmap");
#endif
    return -1;
  }
  return fd;
}

void closemem(unsigned long* mem, int fd) {
  munmap(mem, getpagesize());
  close(fd);
}

