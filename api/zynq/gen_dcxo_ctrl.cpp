#include "gen_dcxo_ctrl.h"
#include "general_reg.h"
#include "reg_macro.h"

// ---------------- CLASS INITIALIZATION ----------------

gen_dcxo_ctrl::gen_dcxo_ctrl()
  : m_initDone(false) {}

int gen_dcxo_ctrl::init(uint32_t index) {
  m_index = index;
  m_initDone = true;
  return 0;
}

// ---------------- HELPER FUNCTIONS ----------------

inline int gen_dcxo_ctrl::setRegisterRange(uint32_t reg, uint32_t lsb, uint32_t msb, uint32_t value) {
  uint32_t temp = readreg(reg);      // Read data currently in specified register.
  CLEANSET32(temp, value, lsb, msb); // Set relevant self-clearing bit.
  writereg(reg, temp);               // Write altered data back to register.
  return 0;
}

inline int gen_dcxo_ctrl::setRegisterRange(uint32_t reg, uint32_t bit, bool value) {
  return setRegisterRange(reg, bit, bit, (uint32_t) value);
}

inline int gen_dcxo_ctrl::getRegisterRange(uint32_t reg, uint32_t lsb, uint32_t msb, uint32_t* result) {
  uint32_t reg_data = readreg(reg);        // Read data currently in specified register.
  CLEANGET32(*result, reg_data, lsb, msb); // Assign contents of specified range to result.
  return 0;
}

inline int gen_dcxo_ctrl::getRegisterRange(uint32_t reg, uint32_t lsb, uint32_t msb, uint16_t* result) {
  uint32_t temp;
  int status = getRegisterRange(reg, lsb, msb, &temp);
  *result = (uint16_t) temp;
  return status;
}

inline int gen_dcxo_ctrl::getRegisterRange(uint32_t reg, uint32_t lsb, uint32_t msb, uint8_t* result) {
  uint32_t temp;
  int status = getRegisterRange(reg, lsb, msb, &temp);
  *result = (uint8_t) temp;
  return status;
}

inline int gen_dcxo_ctrl::getRegisterRange(uint32_t reg, uint32_t bit, bool* result) {
  uint32_t temp;
  int status = getRegisterRange(reg, bit, bit, &temp);
  *result = (uint8_t) temp;
  return status;
}

// ---------------- SHARED GETTERS/SETTERS ----------------

int gen_dcxo_ctrl::setLock(bool lock) {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_LOCK_ENABLE, // bit index
                          lock);                               // value
}

int gen_dcxo_ctrl::getLock(bool* lock) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_LOCK_ENABLE, // bit index
                          lock);                               // result
}

int gen_dcxo_ctrl::triggerDCXOReset() {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_RESET);      // bit index
}

int gen_dcxo_ctrl::triggerDCXODID() {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_DID);        // bit index
}

int gen_dcxo_ctrl::triggerDCXOStart() {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_START);      // bit index
}

int gen_dcxo_ctrl::triggerDCXORead() {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_READ);       // bit index
}

int
gen_dcxo_ctrl::getDCXOIdle(bool* idle) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_IDLE,        // bit index
                          idle);                               // result
}

int gen_dcxo_ctrl::getDCXODIDValid(bool* did_valid) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_DID_VALID,   // bit index
                          did_valid);                          // result
}

int gen_dcxo_ctrl::getDCXOReadValid(bool* read_valid) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_READ_VALID,  // bit index
                          read_valid);                         // result
}

int gen_dcxo_ctrl::getDCXODID(uint8_t* did) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_DID_LSB,          // low bit
                          GenReg::RANGE_DCXO_DID_MSB,          // high bit
                          did);                                // result
}

int gen_dcxo_ctrl::setDCXOSelect(bool dcxo) {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_SELECT,      // bit index
                          dcxo);                               // value
}

int gen_dcxo_ctrl::getDCXOSelect(bool* dcxo) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CONTROL_0+m_index,  // register
                          GenReg::RANGE_DCXO_CTRL_SELECT,      // bit index
                          dcxo);                               // result
}

// ---------------- CY29411 SPECIFIC GETTERS/SETTERS ----------------

int gen_dcxo_ctrl::setDIVO(uint16_t DIVO) {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CY29411_PROG_0+m_index,       // register
                          GenReg::RANGE_DCXO_CY29411_PROG_DIVO_LSB,      // low bit
                          GenReg::RANGE_DCXO_CY29411_PROG_DIVO_MSB,      // high bit
                          (uint32_t) DIVO);                              // value
}

int gen_dcxo_ctrl::setDIVN_INT(uint16_t DIVN_INT) {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CY29411_PROG_0+m_index,       // register
                          GenReg::RANGE_DCXO_CY29411_PROG_DIVN_INT_LSB,  // low bit
                          GenReg::RANGE_DCXO_CY29411_PROG_DIVN_INT_MSB,  // high bit
                          (uint32_t) DIVN_INT);                          // value
}

int gen_dcxo_ctrl::setDIVN_FRAC(uint32_t DIVN_FRAC) {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CY29411_PROG_FRAC_0+m_index,  // register
                          GenReg::RANGE_DCXO_CY29411_PROG_DIVN_FRAC_LSB, // low bit
                          GenReg::RANGE_DCXO_CY29411_PROG_DIVN_FRAC_MSB, // high bit
                          DIVN_FRAC);                                    // value
}

int gen_dcxo_ctrl::setICP_BIN(uint8_t ICP_BIN) {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CY29411_PROG_0+m_index,       // register
                          GenReg::RANGE_DCXO_CY29411_PROG_ICP_BIN_LSB,   // low bit
                          GenReg::RANGE_DCXO_CY29411_PROG_ICP_BIN_MSB,   // high bit
                          (uint32_t) ICP_BIN);                           // value
}

int gen_dcxo_ctrl::setICP_OFFSET(bool ICP_OFFSET) {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CY29411_PROG_0+m_index,       // register
                          GenReg::RANGE_DCXO_CY29411_PROG_ICP_OFFSET,    // bit index
                          ICP_OFFSET);                                   // value
}

int gen_dcxo_ctrl::setPLL_MODE(bool PLL_MODE) {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_CY29411_PROG_0+m_index,       // register
                          GenReg::RANGE_DCXO_CY29411_PROG_PLL_MODE,      // bit index
                          PLL_MODE);                                     // value
}

int gen_dcxo_ctrl::getDIVO(uint16_t* DIVO) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CY29411_READ_0+m_index,       // register
                          GenReg::RANGE_DCXO_CY29411_READ_DIVO_LSB,      // low bit
                          GenReg::RANGE_DCXO_CY29411_READ_DIVO_MSB,      // high bit
                          DIVO);                                         // result
}

int gen_dcxo_ctrl::getDIVN_INT(uint16_t* DIVN_INT) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CY29411_READ_0+m_index,       // register
                          GenReg::RANGE_DCXO_CY29411_READ_DIVN_INT_LSB,  // low bit
                          GenReg::RANGE_DCXO_CY29411_READ_DIVN_INT_MSB,  // high bit
                          DIVN_INT);                                     // result
}

int gen_dcxo_ctrl::getDIVN_FRAC(uint32_t* DIVN_FRAC) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CY29411_READ_FRAC_0+m_index,  // register
                          GenReg::RANGE_DCXO_CY29411_READ_DIVN_FRAC_LSB, // low bit
                          GenReg::RANGE_DCXO_CY29411_READ_DIVN_FRAC_MSB, // high bit
                          DIVN_FRAC);                                    // result
}

int gen_dcxo_ctrl::getICP_BIN(uint8_t* ICP_BIN) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CY29411_READ_0+m_index,       // register
                          GenReg::RANGE_DCXO_CY29411_READ_ICP_BIN_LSB,   // low bit
                          GenReg::RANGE_DCXO_CY29411_READ_ICP_BIN_MSB,   // high bit
                          ICP_BIN);                                      // result
}

int gen_dcxo_ctrl::getICP_OFFSET(bool* ICP_OFFSET) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CY29411_READ_0+m_index,       // register
                          GenReg::RANGE_DCXO_CY29411_READ_ICP_OFFSET,    // bit index
                          ICP_OFFSET);                                   // result
}

int gen_dcxo_ctrl::getPLL_MODE(bool* PLL_MODE) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_CY29411_READ_0+m_index,       // register
                          GenReg::RANGE_DCXO_CY29411_READ_PLL_MODE,      // bit index
                          PLL_MODE);                                     // result
}

// ---------------- Si570 SPECIFIC GETTERS/SETTERS ----------------

int gen_dcxo_ctrl::setRFREQ(uint64_t RFREQ) {
  assert(m_initDone);
  // RFREQ's first 32 bits occupy the entire DCXO_SI570_PROG_LSB register.
  writereg(GenReg::REG_DCXO_SI570_PROG_LSB_0+m_index, (uint32_t) RFREQ);
  return setRegisterRange(GenReg::REG_DCXO_SI570_PROG_MSB_0+m_index,     // register
                          GenReg::RANGE_DCXO_SI570_PROG_MSB_RFREQ_LSB,   // low bit
                          GenReg::RANGE_DCXO_SI570_PROG_MSB_RFREQ_MSB,   // high bit
                          (uint32_t) (RFREQ >> 32));                     // value
}

int gen_dcxo_ctrl::setHSDIV(uint8_t HSDIV) {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_SI570_PROG_MSB_0+m_index,     // register
                          GenReg::RANGE_DCXO_SI570_PROG_MSB_HSDIV_LSB,   // low bit
                          GenReg::RANGE_DCXO_SI570_PROG_MSB_HSDIV_MSB,   // high bit
                          (uint32_t) HSDIV);                             // value
}

int gen_dcxo_ctrl::setN1(uint8_t N1) {
  assert(m_initDone);
  return setRegisterRange(GenReg::REG_DCXO_SI570_PROG_MSB_0+m_index,     // register
                          GenReg::RANGE_DCXO_SI570_PROG_MSB_N1_LSB,      // low bit
                          GenReg::RANGE_DCXO_SI570_PROG_MSB_N1_MSB,      // high bit
                          (uint32_t) N1);                                // value
}

int gen_dcxo_ctrl::getRFREQ(uint64_t* RFREQ) {
  assert(m_initDone);
  // Reference to RFREQ in 32-bit segments.
  // p32_RFREQ[0] => ls32b; p32_RFREQ[1] => ms32b.
  uint32_t *p32_RFREQ = (uint32_t*) RFREQ;

  // RFREQ's lowest 32 bits occupy the entire DCXO_SI570_READ_LSB register.
  p32_RFREQ[0] = readreg(GenReg::REG_DCXO_SI570_READ_LSB_0+m_index);
  return getRegisterRange(GenReg::REG_DCXO_SI570_READ_MSB_0+m_index,     // register
                          GenReg::RANGE_DCXO_SI570_READ_MSB_RFREQ_LSB,   // low bit
                          GenReg::RANGE_DCXO_SI570_READ_MSB_RFREQ_MSB,   // high bit
                          &(p32_RFREQ[1]));                              // result
}

int gen_dcxo_ctrl::getHSDIV(uint8_t* HSDIV) {
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_SI570_READ_MSB_0+m_index,     // register
                          GenReg::RANGE_DCXO_SI570_READ_MSB_HSDIV_LSB,   // low bit
                          GenReg::RANGE_DCXO_SI570_READ_MSB_HSDIV_MSB,   // high bit
                          HSDIV);                                        // result
}

int gen_dcxo_ctrl::getN1(uint8_t* N1){
  assert(m_initDone);
  return getRegisterRange(GenReg::REG_DCXO_SI570_READ_MSB_0+m_index,     // register
                          GenReg::RANGE_DCXO_SI570_READ_MSB_N1_LSB,      // low bit
                          GenReg::RANGE_DCXO_SI570_READ_MSB_N1_MSB,      // high bit
                          N1);                                           // result
}
