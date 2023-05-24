#ifndef GEN_DCXO_CTRL_H_
#define GEN_DCXO_CTRL_H_

#include <assert.h>
#include <stdint.h>

#include "dcxo_ctrl.h"

class gen_dcxo_ctrl : public dcxo_ctrl
{
  public:

    gen_dcxo_ctrl();
    virtual ~gen_dcxo_ctrl(){}
    int init(uint32_t index);
    int setLock(bool lock);
    int getLock(bool *lock);

  private:

    uint32_t m_index;
    bool m_initDone;

    virtual void writereg(uint32_t addr, uint32_t data) = 0;
    virtual uint32_t readreg(uint32_t addr) = 0;

    // Helper functions.
    int setRegisterRange(uint32_t reg, uint32_t lsb, uint32_t msb, uint32_t value);
    int setRegisterRange(uint32_t reg, uint32_t bit, bool value = true);
    int getRegisterRange(uint32_t reg, uint32_t lsb, uint32_t msb, uint32_t* result);
    int getRegisterRange(uint32_t reg, uint32_t lsb, uint32_t msb, uint16_t* result);
    int getRegisterRange(uint32_t reg, uint32_t lsb, uint32_t msb, uint8_t* result);
    int getRegisterRange(uint32_t reg, uint32_t bit, bool* result);

    // Shared getters/setters.
    int triggerDCXODID();   // self-clearing
    int triggerDCXOReset(); // self-clearing
    int triggerDCXOStart(); // self-clearing
    int triggerDCXORead();  // self-clearing

    int getDCXODIDValid(bool* valid);
    int getDCXOIdle(bool* idle);
    int getDCXOReadValid(bool* read_valid);

    int getDCXODID(uint8_t* did);
    int setDCXOSelect(bool dcxo);
    int getDCXOSelect(bool* dcxo);

    // CY29411 specific getters/setters.
    int setDIVO(uint16_t DIVO);
    int setDIVN_INT(uint16_t DIVN_INT);
    int setDIVN_FRAC(uint32_t DIVN_FRAC);
    int setICP_BIN(uint8_t ICP_BIN);
    int setICP_OFFSET(bool ICP_OFFSET);
    int setPLL_MODE(bool PLL_MODE);

    int getDIVO(uint16_t* DIVO);
    int getDIVN_INT(uint16_t* DIVN_INT);
    int getDIVN_FRAC(uint32_t* DIVN_FRAC);
    int getICP_BIN(uint8_t* ICP_BIN);
    int getICP_OFFSET(bool* ICP_OFFSET);
    int getPLL_MODE(bool* PLL_MODE);

    // Si570 specific getters/setters.
    int setRFREQ(uint64_t RFREQ);
    int setHSDIV(uint8_t HSDIV);
    int setN1(uint8_t N1);

    int getRFREQ(uint64_t* RFREQ);
    int getHSDIV(uint8_t* HSDIV);
    int getN1(uint8_t* N1);
};

#endif // GEN_DCXO_CTRL_H_
