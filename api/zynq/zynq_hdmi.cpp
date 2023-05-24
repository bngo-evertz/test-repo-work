#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>

#include "zynq_hdmi.h"
#include "hw_api.h"

ZYNQHDMI::ZYNQHDMI(int baseaddr) {
	fd = open("/dev/mem", O_RDWR);
	if (fd >= 0) {
	  int ps = getpagesize();
	  Config = (Config_type*)
	  	mmap(0, ps, PROT_READ | PROT_WRITE, MAP_SHARED, fd, baseaddr & -ps);

	  if ((void*) -1 == Config) {
#ifdef DEBUG_MEMRW
      perror("mmap");
#endif
	  }
  } else {
#ifdef DEBUG_MEMRW
		perror("open /dev/mem");
#endif
	}
}

ZYNQHDMI::~ZYNQHDMI() {
	munmap((unsigned long*)Config, getpagesize());
	close(fd);
}

void
ZYNQHDMI::loopbackMode(uint8_t mode) {
  Config->TxUseLoopback = mode;
}
