#ifndef HW_MMAP_RW_H
#define HW_MMAP_RW_H

#include <unistd.h>  // getpagesize
#include <stdint.h>  // uintXX_t

#ifdef __cplusplus
extern "C" {
#endif

// Read the physical address
uint32_t readl(int addr);
uint32_t readl_burst(int addr, int len, uint32_t* data);
// Write the physical address
uint32_t writel(int addr, uint32_t val);
uint32_t writel_burst(int addr, int len, uint32_t* val);
// Read/Write the physical address as u64.
uint64_t readll(int addr);
uint32_t readll_burst(int addr, int len, uint64_t* data);
uint32_t writell(int addr, uint64_t val);
uint32_t writell_burst(int addr, int len, uint64_t* val);

// expose the memory for better performance.
int  openmem(unsigned long **mem, int addr);
void closemem(unsigned long* mem, int fd);
#define ADDR2IDX(addr)           (((addr) & ~(-getpagesize()))/4)

#ifdef __cplusplus
}
#endif


#endif
