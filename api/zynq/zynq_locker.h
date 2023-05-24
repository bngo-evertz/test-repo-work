#ifndef TRXS_HW_REG_LOCKER_H
#define TRXS_HW_REG_LOCKER_H

#include "hw_lock.h"

class AutoLock {
  public:
    AutoLock(HwLock & locker) : locker(locker) {
      locker.lock();
    }

    ~AutoLock() {
      locker.unlock();
    }

  private:
    HwLock & locker;
};

// These should be used to lock
// the interface for a single word
// for cases where word accesses are
// not atomic (64 bit interfaces)
// NOTE: The APIs low level access functions
// already call these locks themselves
extern HwLock ZYNQRegXgeRXReadWordLocker;
extern HwLock ZYNQRegXgeTXReadWordLocker;
extern HwLock ZYNQRegXgeRXWriteWordLocker;
extern HwLock ZYNQRegXgeTXWriteWordLocker;

// These should be used to lock
// an entire interface for multiple
// reads / writes
extern HwLock ZYNQRegXGEDRPCh0Locker;
extern HwLock ZYNQRegXGEDRPCh1Locker;
extern HwLock ZYNQRegXGEDRPCoLocker;
extern HwLock ZYNQRegHDMI1Locker;
extern HwLock ZYNQRegHDMI0Locker;
extern HwLock ZYNQRegXGEM0Locker;
extern HwLock ZYNQRegXGEM1Locker;
extern HwLock ZYNQRegXGEIFLocker;
extern HwLock ZYNQRegXGETXLocker;
extern HwLock ZYNQRegXGERXLocker;
extern HwLock ZYNQRegSCA0Locker;
extern HwLock ZYNQRegSCA1Locker;
extern HwLock ZYNQRegSCA2Locker;
extern HwLock ZYNQRegSCA3Locker;
extern HwLock ZYNQRegSCB0Locker;
extern HwLock ZYNQRegSCB1Locker;
extern HwLock ZYNQRegSCB2Locker;
extern HwLock ZYNQRegSCB3Locker;
extern HwLock ZYNQRegSCRS0Locker;
extern HwLock ZYNQRegSCRS1Locker;
extern HwLock ZYNQRegSCRS2Locker;
extern HwLock ZYNQRegSCRS3Locker;
extern HwLock ZYNQRegSCMS0Locker;
extern HwLock ZYNQRegSCMS1Locker;
extern HwLock ZYNQRegSCMS2Locker;
extern HwLock ZYNQRegSCMS3Locker;
extern HwLock ZYNQRegSCWP0Locker;
extern HwLock ZYNQRegSCWP1Locker;
extern HwLock ZYNQRegSCWP2Locker;
extern HwLock ZYNQRegSCWP3Locker;
extern HwLock ZYNQRegSCPL0Locker;
extern HwLock ZYNQRegSCPL1Locker;
extern HwLock ZYNQRegSCPL2Locker;
extern HwLock ZYNQRegSCPL3Locker;
extern HwLock ZYNQRegMTestLocker;

// and so on...
//

#define __AUTOLOCKCODE(code, locker)      \
  do {                                  \
    AutoLock lockit(locker);          \
    code;                             \
  } while (0)

#define AUTOLOCKPROJ(code)            __AUTOLOCKCODE(code, TRXSRegProjLocker)
#define AUTOLOCKXGERX(code)           __AUTOLOCKCODE(code, TRXSRegXgeRxLocker)
#define AUTOLOCKXGETX(code)           __AUTOLOCKCODE(code, TRXSRegXgeTxLocker)

#endif
