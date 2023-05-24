#include <assert.h>
#include <stdio.h>

#include "general_reg.h"
#include "reg_macro.h"

GeneralReg::GeneralReg()
  : m_initDone(false) {}

void
GeneralReg::init(gen_dcxo_ctrl* dcxo_objects[MAX_XO]) {
  for (uint32_t i = 0; i < NUM_XO; i++) {
    m_dcxo[i] = dcxo_objects[i];
  }
  // Set init flag (always do this last!)
  m_initDone = true;
  return;
}

bool
GeneralReg::getInitDone() {
  return m_initDone;
}

int
GeneralReg::getZeroes(uint32_t* Zeroes){
  *Zeroes = readreg(GenReg::REG_ZEROES);
  return 0;
}

int
GeneralReg::getOnes(uint32_t* Ones){
  *Ones = readreg(GenReg::REG_ONES);
  return 0;
}

int
GeneralReg::getLoopback(uint32_t Index, uint32_t* Loopback){
  *Loopback = readreg(GenReg::REG_LOOPBACK0+Index);
  return 0;
}

void
GeneralReg::setLoopback(uint32_t Index, uint32_t Loopback){
  if(Index < 2)
  {
    writereg(GenReg::REG_LOOPBACK0+Index, Loopback);
  }
  return;
}

int
GeneralReg::getDebugPulseCount(uint32_t* DebugPulseCount){
  // Get the value from the register.
  uint32_t DebugPulseTemp = readreg(GenReg::REG_DEBUG_PLS);
  // Set the mask to be the only the number of bits in the MSB downto LSB range.
  uint32_t DebugPulseMask = 0xFFFFFFFF >> (32 - (GenReg::RANGE_TEST_COUNT_MSB-GenReg::RANGE_TEST_COUNT_LSB+1));
  // Shift the register value down by the lower bound of the LSB and then AND it with the mask to leave only the valid range.
  *DebugPulseCount = (DebugPulseTemp >> GenReg::RANGE_TEST_COUNT_LSB) & DebugPulseMask;
  return 0;
}

void
GeneralReg::setDebugPulseCount(uint32_t DebugPulseCount){
  for(uint32_t i = 0; i < DebugPulseCount; i++)
  {
    writereg(GenReg::REG_DEBUG_PLS, 1 << GenReg::RANGE_TEST_PULSE);
  }
  return;
}

// FPGA Index
int
GeneralReg::getFPGAIndex(bool* index){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_FPGA_INDEX);
  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_FPGA_INDEX, GenReg::RANGE_FPGA_INDEX);
  *index = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::setFPGAIndex(bool index){
  assert(m_initDone);
  uint32_t reg = 0;
  // Build up the register.
  CLEANSET32(reg, index, GenReg::RANGE_FPGA_INDEX, GenReg::RANGE_FPGA_INDEX);
  // Write value to register.
  writereg(GenReg::REG_FPGA_INDEX, reg);
  return 0;
}

// FPGA Reset
// No getFPGAReset because once you do this... the FPGA is reset.
int
GeneralReg::setFPGAReset(bool reset){
  assert(m_initDone);
  uint32_t reg = 0;
  // Build up the register.
  CLEANSET32(reg, reset, GenReg::RANGE_FPGA_RESET, GenReg::RANGE_FPGA_RESET);
  // Write value to register.
  writereg(GenReg::REG_FPGA_RESET, reg);
  return 0;
}

// HDMI
int
GeneralReg::getHdmiInHPD(uint8_t index, bool* hpd){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_HDMI_IN_HPD);
  // Extract the desired bits.
  uint32_t value;
  if (index == 0) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_HPD_0, GenReg::RANGE_HDMI_IN_HPD_0);
  }
  else if (index == 1) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_HPD_1, GenReg::RANGE_HDMI_IN_HPD_1);
  }
  else {
    // Index is out of range
    return -1;
  }
  *hpd = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::getHdmiOutHPD(uint8_t index, bool* hpd){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_HDMI_OUT_HPD);
  // Extract the desired bits.
  uint32_t value;
  if (index == 0) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_OUT_HPD_0, GenReg::RANGE_HDMI_OUT_HPD_0);
  }
  else if (index == 1) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_OUT_HPD_1, GenReg::RANGE_HDMI_OUT_HPD_1);
  }
  else {
    // Index is out of range
    return -1;
  }
  *hpd = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::getHdmiInCableDetect(uint8_t index, bool* cableDetect){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_HDMI_IN_CABLE_DETECT);
  // Extract the desired bits.
  uint32_t value;
  if (index == 0) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_CABLE_DETECT_0, GenReg::RANGE_HDMI_IN_CABLE_DETECT_0);
  }
  else if (index == 1) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_CABLE_DETECT_1, GenReg::RANGE_HDMI_IN_CABLE_DETECT_1);
  }
  else if (index == 2) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_CABLE_DETECT_2, GenReg::RANGE_HDMI_IN_CABLE_DETECT_2);
  }
  else if (index == 3) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_CABLE_DETECT_3, GenReg::RANGE_HDMI_IN_CABLE_DETECT_3);
  }
  else {
    // Index is out of range
    return -1;
  }
  *cableDetect = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::getHdmiInCableDetectMux(uint8_t index, bool* cableDetect){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_HDMI_IN_CABLE_DETECT_MUX);
  // Extract the desired bits.
  uint32_t value;
  if (index == 0) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_CABLE_DETECT_MUX_0, GenReg::RANGE_HDMI_IN_CABLE_DETECT_MUX_0);
  }
  else if (index == 1) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_CABLE_DETECT_MUX_1, GenReg::RANGE_HDMI_IN_CABLE_DETECT_MUX_1);
  }
  else {
    // Index is out of range
    return -1;
  }
  *cableDetect = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::getHdmiMuxSelect(uint8_t index, bool* select){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_HDMI_MUX_SEL);
  // Extract the desired bits.
  uint32_t value;
  if (index == 0) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_MUX_SEL_0, GenReg::RANGE_HDMI_IN_MUX_SEL_0);
  }
  else if (index == 1) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_MUX_SEL_1, GenReg::RANGE_HDMI_IN_MUX_SEL_1);
  }
  else if (index == 2) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_MUX_SEL_2, GenReg::RANGE_HDMI_IN_MUX_SEL_2);
  }
  else if (index == 3) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_MUX_SEL_3, GenReg::RANGE_HDMI_IN_MUX_SEL_3);
  }
  else if (index == 4) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_MUX_SEL_4, GenReg::RANGE_HDMI_IN_MUX_SEL_4);
  }
  else if (index == 5) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_MUX_SEL_5, GenReg::RANGE_HDMI_IN_MUX_SEL_5);
  }
  else if (index == 6) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_MUX_SEL_6, GenReg::RANGE_HDMI_IN_MUX_SEL_6);
  }
  else if (index == 7) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_IN_MUX_SEL_7, GenReg::RANGE_HDMI_IN_MUX_SEL_7);
  }
  else {
    // Index is out of range
    return -1;
  }
  *select = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::setHdmiMuxSelect(uint8_t index, bool select){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg = readreg(GenReg::REG_HDMI_MUX_SEL);

  // Build up the register.
  if (index == 0) {
    CLEANSET32(reg, select, GenReg::RANGE_HDMI_IN_MUX_SEL_0, GenReg::RANGE_HDMI_IN_MUX_SEL_0);
  }
  else if (index == 1) {
    CLEANSET32(reg, select, GenReg::RANGE_HDMI_IN_MUX_SEL_1, GenReg::RANGE_HDMI_IN_MUX_SEL_1);
  }
  else if (index == 2) {
    CLEANSET32(reg, select, GenReg::RANGE_HDMI_IN_MUX_SEL_2, GenReg::RANGE_HDMI_IN_MUX_SEL_2);
  }
  else if (index == 3) {
    CLEANSET32(reg, select, GenReg::RANGE_HDMI_IN_MUX_SEL_3, GenReg::RANGE_HDMI_IN_MUX_SEL_3);
  }
  else if (index == 4) {
    CLEANSET32(reg, select, GenReg::RANGE_HDMI_IN_MUX_SEL_4, GenReg::RANGE_HDMI_IN_MUX_SEL_4);
  }
  else if (index == 5) {
    CLEANSET32(reg, select, GenReg::RANGE_HDMI_IN_MUX_SEL_5, GenReg::RANGE_HDMI_IN_MUX_SEL_5);
  }
  else if (index == 6) {
    CLEANSET32(reg, select, GenReg::RANGE_HDMI_IN_MUX_SEL_6, GenReg::RANGE_HDMI_IN_MUX_SEL_6);
  }
  else if (index == 7) {
    CLEANSET32(reg, select, GenReg::RANGE_HDMI_IN_MUX_SEL_7, GenReg::RANGE_HDMI_IN_MUX_SEL_7);
  }
  else {
    // Index is out of range
    return -1;
  }
  // Write value to register.
  writereg(GenReg::REG_HDMI_MUX_SEL, reg);
  return 0;
}

int
GeneralReg::getHdmiOutDisable(uint8_t index, bool* disable){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_HDMI_OUT_DISABLE);
  // Extract the desired bits.
  uint32_t value;
  if (index == 0) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_OUT_DISABLE_0, GenReg::RANGE_HDMI_OUT_DISABLE_0);
  }
  else if (index == 1) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_OUT_DISABLE_1, GenReg::RANGE_HDMI_OUT_DISABLE_1);
  }
  else {
    // Index is out of range
    return -1;
  }
  *disable = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::setHdmiOutDisable(uint8_t index, bool disable){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg = readreg(GenReg::REG_HDMI_OUT_DISABLE);
  if (index == 0) {
    // Build up the register.
    CLEANSET32(reg, disable, GenReg::RANGE_HDMI_OUT_DISABLE_0, GenReg::RANGE_HDMI_OUT_DISABLE_0);
  }
  else if (index == 1) {
    // Build up the register.
    CLEANSET32(reg, disable, GenReg::RANGE_HDMI_OUT_DISABLE_1, GenReg::RANGE_HDMI_OUT_DISABLE_1);
  }
  else {
    // Index is out of range
    return -1;
  }
  // Write value to register.
  writereg(GenReg::REG_HDMI_OUT_DISABLE, reg);
  return 0;
}

int
GeneralReg::getHdmiOut5VDisable(uint8_t index, bool* disable){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_HDMI_OUT_5V_DISABLE);
  // Extract the desired bits.
  uint32_t value;
  if(index == 0) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_OUT_5V_DISABLE_0, GenReg::RANGE_HDMI_OUT_5V_DISABLE_0);
  }
  else if (index == 1) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_OUT_5V_DISABLE_1, GenReg::RANGE_HDMI_OUT_5V_DISABLE_1);
  }
  else {
    // Index is out of range
    return -1;
  }
  *disable = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::setHdmiOut5VDisable(uint8_t index, bool disable){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg = readreg(GenReg::REG_HDMI_OUT_5V_DISABLE);
  if (index == 0) {
    // Build up the register.
    CLEANSET32(reg, disable, GenReg::RANGE_HDMI_OUT_5V_DISABLE_0, GenReg::RANGE_HDMI_OUT_5V_DISABLE_0);
  }
  else if (index == 1) {
    // Build up the register.
    CLEANSET32(reg, disable, GenReg::RANGE_HDMI_OUT_5V_DISABLE_1, GenReg::RANGE_HDMI_OUT_5V_DISABLE_1);
  }
  else {
    // Index is out of range
    return -1;
  }
  // Write value to register.
  writereg(GenReg::REG_HDMI_OUT_5V_DISABLE, reg);
  return 0;
}

int
GeneralReg::getHdmiBridgeReset(uint8_t index, bool* reset){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_HDMI_BRG_RST);
  // Extract the desired bits.
  uint32_t value;
  if (index == 0) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_BRG_RST_0, GenReg::RANGE_HDMI_BRG_RST_0);
  }
  else if (index == 1) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_BRG_RST_1, GenReg::RANGE_HDMI_BRG_RST_1);
  }
  else if (index == 2) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_BRG_RST_2, GenReg::RANGE_HDMI_BRG_RST_2);
  }
  else if (index == 3) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_BRG_RST_3, GenReg::RANGE_HDMI_BRG_RST_3);
  }
  else if (index == 4) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_BRG_RST_4, GenReg::RANGE_HDMI_BRG_RST_4);
  }
  else if (index == 5) {
    CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_BRG_RST_5, GenReg::RANGE_HDMI_BRG_RST_5);
  }
  else {
    // Index is out of range
    return -1;
  }
  *reset = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::setHdmiBridgeReset(uint8_t index, bool reset){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg = readreg(GenReg::REG_HDMI_BRG_RST);

  // Build up the register.
  if (index == 0) {
    CLEANSET32(reg, reset, GenReg::RANGE_HDMI_BRG_RST_0, GenReg::RANGE_HDMI_BRG_RST_0);
  }
  else if (index == 1) {
    CLEANSET32(reg, reset, GenReg::RANGE_HDMI_BRG_RST_1, GenReg::RANGE_HDMI_BRG_RST_1);
  }
  else if (index == 2) {
    CLEANSET32(reg, reset, GenReg::RANGE_HDMI_BRG_RST_2, GenReg::RANGE_HDMI_BRG_RST_2);
  }
  else if (index == 3) {
    CLEANSET32(reg, reset, GenReg::RANGE_HDMI_BRG_RST_3, GenReg::RANGE_HDMI_BRG_RST_3);
  }
  else if (index == 4) {
    CLEANSET32(reg, reset, GenReg::RANGE_HDMI_BRG_RST_4, GenReg::RANGE_HDMI_BRG_RST_4);
  }
  else if (index == 5) {
    CLEANSET32(reg, reset, GenReg::RANGE_HDMI_BRG_RST_5, GenReg::RANGE_HDMI_BRG_RST_5);
  }
  else {
    // Index is out of range
    return -1;
  }
  // Write value to register.
  writereg(GenReg::REG_HDMI_BRG_RST, reg);
  return 0;
}

// HDMI MB
int
GeneralReg::getHdmiPause(bool* pause){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_HDMI_MB);
  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_PAUSE, GenReg::RANGE_HDMI_PAUSE);
  *pause = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::setHdmiPause(bool pause){
  assert(m_initDone);
  uint32_t reg = 0;
  // Build up the register.
  CLEANSET32(reg, pause, GenReg::RANGE_HDMI_PAUSE, GenReg::RANGE_HDMI_PAUSE);
  // Write value to register.
  writereg(GenReg::REG_HDMI_MB, reg);
  return 0;
}

int
GeneralReg::getHdmiReset(bool* reset){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_HDMI_MB);
  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_HDMI_RESET, GenReg::RANGE_HDMI_RESET);
  *reset = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::setHdmiReset(bool reset){
  assert(m_initDone);
  uint32_t reg = 0;
  // Build up the register.
  CLEANSET32(reg, reset, GenReg::RANGE_HDMI_RESET, GenReg::RANGE_HDMI_RESET);
  // Write value to register.
  writereg(GenReg::REG_HDMI_MB, reg);
  return 0;
}

// USB
int
GeneralReg::getUsbReset(bool *reset){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_USB_RESET);
  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_USB_RESET, GenReg::RANGE_USB_RESET);
  *reset = static_cast<bool>(value);
  return 0;
}

int
GeneralReg::setUsbReset(bool reset){
  assert(m_initDone);
  uint32_t reg = 0;
  // Build up the register.
  CLEANSET32(reg, reset, GenReg::RANGE_USB_RESET, GenReg::RANGE_USB_RESET);
  // Write value to register.
  writereg(GenReg::REG_USB_RESET, reg);
  return 0;
}

// Clock Frequencies Verification
int
GeneralReg::getXGEClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_XGE);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_XGE_LSB, GenReg::RANGE_MEASURE_XGE_MSB);

  *frequency = value*4;

  return 0;
}

int
GeneralReg::get125mhzClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_109_125MHZ);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_109_125MHZ_LSB, GenReg::RANGE_MEASURE_109_125MHZ_MSB);

  *frequency = value*4;

  return 0;
}

int
GeneralReg::get62m5hzClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_109_62M5HZ);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_109_62M5HZ_LSB, GenReg::RANGE_MEASURE_109_62M5HZ_MSB);

  *frequency = value*4;

  return 0;
}

int
GeneralReg::get312m5hzClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_109_312M5HZ);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_109_312M5HZ_LSB, GenReg::RANGE_MEASURE_109_312M5HZ_MSB);

  *frequency = value*4;

  return 0;
}

int
GeneralReg::get156m25hzClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_109_156M25HZ);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_109_156M25HZ_LSB, GenReg::RANGE_MEASURE_109_156M25HZ_MSB);

  *frequency = value*4;

  return 0;
}

int
GeneralReg::getHdmiSouthTxClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_HDMI_SOUTH_TX);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_HDMI_SOUTH_TX_LSB, GenReg::RANGE_MEASURE_HDMI_SOUTH_TX_MSB);

  *frequency = value*4*2;

  return 0;
}

int
GeneralReg::getHdmiNorthTxClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_HDMI_NORTH_TX);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_HDMI_NORTH_TX_LSB, GenReg::RANGE_MEASURE_HDMI_NORTH_TX_MSB);

  *frequency = value*4*2;

  return 0;
}

int
GeneralReg::getInterFPGAClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_INTERFPGA);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_INTERFPGA_LSB, GenReg::RANGE_MEASURE_INTERFPGA_MSB);

  *frequency = value*4;

  return 0;
}

int
GeneralReg::getDRUClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_DRU);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_DRU_LSB, GenReg::RANGE_MEASURE_DRU_MSB);

  *frequency = value*4;

  return 0;
}

int
GeneralReg::getReflockClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_REFLOCK);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_REFLOCK_LSB, GenReg::RANGE_MEASURE_REFLOCK_MSB);

  *frequency = value*4;

  return 0;
}

int
GeneralReg::getMgt110Refclk1ClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_MGT110_REFCLK1);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_MGT110_REFCLK1_LSB, GenReg::RANGE_MEASURE_MGT110_REFCLK1_MSB);

  *frequency = value*4;

  return 0;
}

int
GeneralReg::getMgt112Refclk1ClkFrequency(uint32_t* frequency){
  assert(m_initDone);

  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_MEASURE_MGT112_REFCLK1);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_MEASURE_MGT112_REFCLK1_LSB, GenReg::RANGE_MEASURE_MGT112_REFCLK1_MSB);

  *frequency = value*4;

  return 0;
}

// ICRON MDIO
int
GeneralReg::getUsbPhyMdio(uint32_t phy_addr, uint32_t reg_addr, uint32_t* status) {
  assert(m_initDone);
  uint32_t cmd_reg = (2 << 26) +( phy_addr << 21) + (reg_addr << 16);
  writereg(GenReg::REG_MDIO_USB_PHY_COMMAND, cmd_reg);
  writereg(GenReg::REG_MDIO_USB_PHY_START, 1);   //start writing command
  while((readreg(GenReg::REG_MDIO_USB_PHY_STATUS) && 0x00010000) == 0  ) {   //wait until read data ready
   }
  *status = (readreg(GenReg::REG_MDIO_USB_PHY_STATUS) && 0x0000ffff);
  return 0;
}

int
GeneralReg::setUsbPhyMdio(uint32_t phy_addr, uint32_t reg_addr, uint32_t command) {
  assert(m_initDone);
  uint32_t cmd_reg = (1 << 26) + (phy_addr << 21) + (reg_addr << 16) + command ;
  writereg(GenReg::REG_MDIO_USB_PHY_COMMAND, cmd_reg);
  writereg(GenReg::REG_MDIO_USB_PHY_START, 1);   //start writing command
  return 0;
}

int
GeneralReg::getAnalogMute(bool* mute){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_AUDIO_CONTROL_ANALOG);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_ANALOG_MUTE, GenReg::RANGE_ANALOG_MUTE);

  *mute = (bool)value;

  return 0;
}

int
GeneralReg::setAnalogMute(bool mute){
  assert(m_initDone);
  uint32_t reg = 0;
  // Build up the register.
  CLEANSET32(reg, mute, GenReg::RANGE_ANALOG_MUTE, GenReg::RANGE_ANALOG_MUTE);
  // Write value to register.
  writereg(GenReg::REG_AUDIO_CONTROL_ANALOG, reg);
  return 0;
}

int
GeneralReg::getUSBTxSrcSel(bool* src){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_USB_TX_SRC_SEL);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_USB_TX_SRC_SEL, GenReg::RANGE_USB_TX_SRC_SEL);

  *src = (bool)value;

  return 0;
}

int
GeneralReg::setUSBTxSrcSel(bool src){
  assert(m_initDone);
  uint32_t reg = 0;
  // Build up the register.
  CLEANSET32(reg, src, GenReg::RANGE_USB_TX_SRC_SEL, GenReg::RANGE_USB_TX_SRC_SEL);
  // Write value to register.
  writereg(GenReg::REG_USB_TX_SRC_SEL, reg);
  return 0;
}

int
GeneralReg::getSPDIFMute(uint8_t index, bool* mute){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_AUDIO_CONTROL_SPDIF);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, (GenReg::RANGE_SPDIF_MUTE_LSB+index), (GenReg::RANGE_SPDIF_MUTE_LSB+index));

  *mute = (bool)value;

  return 0;
}

int
GeneralReg::setSPDIFMute(uint8_t index, bool mute){
  assert(m_initDone);
  uint32_t reg = readreg(GenReg::REG_AUDIO_CONTROL_SPDIF);
  // Build up the register.
  CLEANSET32(reg, mute, (GenReg::RANGE_SPDIF_MUTE_LSB+index), (GenReg::RANGE_SPDIF_MUTE_LSB+index));
  // Write value to register.
  writereg(GenReg::REG_AUDIO_CONTROL_SPDIF, reg);
  return 0;
}

int
GeneralReg::getI2CExpanderReset(bool* reset){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_I2C_EXPANDER);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_I2C_EXPANDER_RESET, GenReg::RANGE_I2C_EXPANDER_RESET);

  *reset = (bool)value;

  return 0;
}

int
GeneralReg::setI2CExpanderReset(bool reset){
  assert(m_initDone);
  uint32_t reg = 0;
  // Build up the register.
  CLEANSET32(reg, reset, GenReg::RANGE_I2C_EXPANDER_RESET, GenReg::RANGE_I2C_EXPANDER_RESET);
  // Write value to register.
  writereg(GenReg::REG_I2C_EXPANDER, reg);
  return 0;
}

int
GeneralReg::getPbState(bool* pb){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_PUSH_BUTTON);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_PUSH_BUTTON, GenReg::RANGE_PUSH_BUTTON);

  *pb = (bool)value;

  return 0;
}

int
GeneralReg::getLedRgb(uint8_t* red, uint8_t* green, uint8_t* blue){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg_data = readreg(GenReg::REG_LED_CONTROL);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_LED_R_CONTROL_LSB, GenReg::RANGE_LED_R_CONTROL_MSB);
  *red = static_cast<uint8_t>(value);

  CLEANGET32(value, reg_data, GenReg::RANGE_LED_G_CONTROL_LSB, GenReg::RANGE_LED_G_CONTROL_MSB);
  *green = static_cast<uint8_t>(value);

  CLEANGET32(value, reg_data, GenReg::RANGE_LED_B_CONTROL_LSB, GenReg::RANGE_LED_B_CONTROL_MSB);
  *blue = static_cast<uint8_t>(value);
  return 0;
}

int
GeneralReg::setLedRgb(uint8_t red, uint8_t green, uint8_t blue){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg = readreg(GenReg::REG_LED_CONTROL);

  // Build up the register.
  CLEANSET32(reg, red,   GenReg::RANGE_LED_R_CONTROL_LSB, GenReg::RANGE_LED_R_CONTROL_MSB);
  CLEANSET32(reg, green, GenReg::RANGE_LED_G_CONTROL_LSB, GenReg::RANGE_LED_G_CONTROL_MSB);
  CLEANSET32(reg, blue,  GenReg::RANGE_LED_B_CONTROL_LSB, GenReg::RANGE_LED_B_CONTROL_MSB);

  // Write value to register.
  writereg(GenReg::REG_LED_CONTROL, reg);
  return 0;
}

int
GeneralReg::getSupply12vMonitor(uint8_t index, bool* monitor){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_PS_12VMON);
  // Extract the desired bits.
  uint32_t value;
  if(index == 0) {
    CLEANGET32(value, reg_data, GenReg::RANGE_PS1_12VMON, GenReg::RANGE_PS1_12VMON);
  }
  else if (index == 1) {
    CLEANGET32(value, reg_data, GenReg::RANGE_PS2_12VMON, GenReg::RANGE_PS2_12VMON);
  }
  else {
    // Index is out of range
    return -1;
  }
  *monitor = bool(value);
  return 0;
}

int
GeneralReg::getSupplyOrFault(uint8_t index, bool* orfault){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_PS_ORFAULT_N);
  // Extract the desired bits.
  uint32_t value;
  if(index == 0) {
    CLEANGET32(value, reg_data, GenReg::RANGE_PS1_ORFAULT_N, GenReg::RANGE_PS1_ORFAULT_N);
  }
  else if (index == 1) {
    CLEANGET32(value, reg_data, GenReg::RANGE_PS2_ORFAULT_N, GenReg::RANGE_PS2_ORFAULT_N);
  }
  else {
    // Index is out of range
    return -1;
  }
  *orfault = bool(value);
  return 0;
}

int
GeneralReg::getTRMSelect(bool* select){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_TRXS_TRM_SEL);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_TRXS_TRM_SEL, GenReg::RANGE_TRXS_TRM_SEL);

  // Return the value.
  *select = bool(value);
  return 0;
}

int
GeneralReg::setTRMSelect(bool select){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg = 0;

  // Build up the register.
  CLEANSET32(reg, select, GenReg::RANGE_TRXS_TRM_SEL, GenReg::RANGE_TRXS_TRM_SEL);

  // Write value to register.
  writereg(GenReg::REG_TRXS_TRM_SEL, reg);
  return 0;
}

int
GeneralReg::getXgeRxInvertPolarity(uint8_t index, bool* invert){
  assert(m_initDone);
  if (index > (GenReg::RANGE_XGE_RX_POLARITY_INVERT_MSB-GenReg::RANGE_XGE_RX_POLARITY_INVERT_LSB)) {
    // Index is out of range
    return -1;
  }

  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_XGE_POLARITY_INVERT);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, (GenReg::RANGE_XGE_RX_POLARITY_INVERT_LSB+index), (GenReg::RANGE_XGE_RX_POLARITY_INVERT_LSB+index));

  // Return the value.
  *invert = bool(value);
  return 0;
}

int
GeneralReg::setXgeRxInvertPolarity(uint8_t index, bool invert){
  assert(m_initDone);
  if (index > (GenReg::RANGE_XGE_RX_POLARITY_INVERT_MSB-GenReg::RANGE_XGE_RX_POLARITY_INVERT_LSB)) {
    // Index is out of range
    return -1;
  }

  // Get the value from the register.
  uint32_t reg = readreg(GenReg::REG_XGE_POLARITY_INVERT);

  // Build up the register.
  CLEANSET32(reg, invert, (GenReg::RANGE_XGE_RX_POLARITY_INVERT_LSB+index), (GenReg::RANGE_XGE_RX_POLARITY_INVERT_LSB+index));

  // Write value to register.
  writereg(GenReg::REG_XGE_POLARITY_INVERT, reg);
  return 0;
}

int
GeneralReg::getXgeTxInvertPolarity(uint8_t index, bool* invert){
  assert(m_initDone);
  if (index > (GenReg::RANGE_XGE_TX_POLARITY_INVERT_MSB-GenReg::RANGE_XGE_TX_POLARITY_INVERT_LSB)) {
    // Index is out of range
    return -1;
  }

  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_XGE_POLARITY_INVERT);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, (GenReg::RANGE_XGE_TX_POLARITY_INVERT_LSB+index), (GenReg::RANGE_XGE_TX_POLARITY_INVERT_LSB+index));

  // Return the value.
  *invert = bool(value);
  return 0;
}

int
GeneralReg::setXgeTxInvertPolarity(uint8_t index, bool invert){
  assert(m_initDone);
  if (index > (GenReg::RANGE_XGE_TX_POLARITY_INVERT_MSB-GenReg::RANGE_XGE_TX_POLARITY_INVERT_LSB)) {
    // Index is out of range
    return -1;
  }

  // Get the value from the register.
  uint32_t reg = readreg(GenReg::REG_XGE_POLARITY_INVERT);

  // Build up the register.
  CLEANSET32(reg, invert, (GenReg::RANGE_XGE_TX_POLARITY_INVERT_LSB+index), (GenReg::RANGE_XGE_TX_POLARITY_INVERT_LSB+index));

  // Write value to register.
  writereg(GenReg::REG_XGE_POLARITY_INVERT, reg);
  return 0;
}

int
GeneralReg::getSpiDisplay(uint8_t* data){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_SPI_DISPLAY);

  // Build up the register.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_SPI_DISPLAY_DATA_LSB, GenReg::RANGE_SPI_DISPLAY_DATA_MSB);

  // Return the value.
  *data = uint8_t(value);
  return 0;
}

int
GeneralReg::setSpiDisplay(uint8_t data){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg = 0;

  // Build up the register.
  CLEANSET32(reg, data, GenReg::RANGE_SPI_DISPLAY_DATA_LSB, GenReg::RANGE_SPI_DISPLAY_DATA_MSB);
  CLEANSET32(reg, 0x1, GenReg::RANGE_SPI_DISPLAY_START, GenReg::RANGE_SPI_DISPLAY_START);

  // Write value to register.
  writereg(GenReg::REG_SPI_DISPLAY, reg);
  return 0;
}

int
GeneralReg::getToggleSwitch(bool a_not_b, bool* toggle){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_TOGGLE_SWITCH);

  // Extract the desired bits.
  uint32_t value;
  if (a_not_b) {
    CLEANGET32(value, reg_data, GenReg::RANGE_TOGGLE_SWITCH_A, GenReg::RANGE_TOGGLE_SWITCH_A);
  } else {
    CLEANGET32(value, reg_data, GenReg::RANGE_TOGGLE_SWITCH_B, GenReg::RANGE_TOGGLE_SWITCH_B);
  }

  // Return the value.
  *toggle = bool(value);
  return 0;
}

int
GeneralReg::getLocalFault(bool* fault){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_LOCAL_FAULT);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_LOCAL_FAULT, GenReg::RANGE_LOCAL_FAULT);

  // Return the value.
  *fault = bool(value);
  return 0;
}

int
GeneralReg::setLocalFault(bool fault){
  assert(m_initDone);
  // Get the value from the register.
  uint32_t reg = 0;

  // Build up the register.
  CLEANSET32(reg, fault, GenReg::RANGE_LOCAL_FAULT, GenReg::RANGE_LOCAL_FAULT);

  // Write value to register.
  writereg(GenReg::REG_LOCAL_FAULT, reg);
  return 0;
}

int
GeneralReg::getFanFail(bool* fail){
  assert(m_initDone);
  // Read back the current register value.
  uint32_t reg_data = readreg(GenReg::REG_FAN_FAIL);

  // Extract the desired bits.
  uint32_t value;
  CLEANGET32(value, reg_data, GenReg::RANGE_FAN_FAIL, GenReg::RANGE_FAN_FAIL);

  // Return the value.
  *fail = bool(value);
  return 0;
}

int
GeneralReg::initDCXO(uint8_t index, dcxo_ctrl::dcxo_select_type dcxo, uint32_t si570DefaultFrequency){
  assert(m_initDone);
  // Check that index is in range.
  if(!getDCXOInRange(index)){
    return -1;
  }

  return m_dcxo[index]->initialize(dcxo, si570DefaultFrequency);
}

int
GeneralReg::initDCXO(uint8_t index, uint32_t si570DefaultFrequency){
  assert(m_initDone);
  // Check that index is in range.
  if(!getDCXOInRange(index)){
    return -1;
  }

  return m_dcxo[index]->initialize(si570DefaultFrequency);
}

inline bool
GeneralReg::getDCXOInRange(uint8_t index) {
  return index < MAX_XO;
}

int
GeneralReg::setDCXOClock(uint8_t index, uint32_t frequency, bool cy29411AcceptBestStableFreq){
  assert(m_initDone);
  // Check that index is in range.
  if(!getDCXOInRange(index)){
    return -1;
  }

  int status = m_dcxo[index]->setClock(frequency, cy29411AcceptBestStableFreq);

  return status;
}

int
GeneralReg::setDCXOLockEnable(uint8_t index, bool value){
  assert(m_initDone);
  // Check that index is in range.
  if(!getDCXOInRange(index)){
    return -1;
  }

  return m_dcxo[index]->setLock(value);
}

int
GeneralReg::getDCXOLockEnable(uint8_t index, bool* value){
  assert(m_initDone);
  // Check that index is in range.
  if(!getDCXOInRange(index))
  {
    return -1;
  }

  return m_dcxo[index]->getLock(value);
}

int
GeneralReg::setDCXODone(uint8_t index, bool value){
  assert(m_initDone);
  // Check that index is in range.
  if(!getDCXOInRange(index)){
    return -1;
  }

  // Read data currently in specified register.
  uint32_t reg_data = readreg(GenReg::REG_DCXO_CONTROL_0+index);
  // Set register bit.
  CLEANSET32(reg_data, (uint32_t)(value?1:0), GenReg::RANGE_DCXO_CTRL_DONE, GenReg::RANGE_DCXO_CTRL_DONE);
  // Write value to register.
  writereg(GenReg::REG_DCXO_CONTROL_0+index, reg_data);
  return 0;
}

int
GeneralReg::getDCXODone(uint8_t index, bool* value){
  assert(m_initDone);

  // Check that index is in range.
  if(!getDCXOInRange(index)){
    return -1;
  }

  // Read data currently in specified register.
  uint32_t reg_data = readreg(GenReg::REG_DCXO_CONTROL_0+index);
  // Get specified bit.
  uint32_t temp;
  CLEANGET32(temp, reg_data, GenReg::RANGE_DCXO_CTRL_DONE, GenReg::RANGE_DCXO_CTRL_DONE);
  *value = (bool) temp;
  return 0;
}

int
GeneralReg::readDCXOSelect(uint8_t index, bool* initialized, dcxo_ctrl::dcxo_select_type* dcxo) {
  assert(m_initDone);
  // Check that index is in range.
  if(!getDCXOInRange(index)){
    return -1;
  }

  return m_dcxo[index]->readDCXOSelect(initialized, dcxo);
}

int
GeneralReg::readDCXOSettingsCY29411(uint8_t index, bool* valid, cy29411_ctrl::cy29411_settings_type *settings) {
  assert(m_initDone);
  // Check that index is in range.
  if(!getDCXOInRange(index)){
    return -1;
  }

  return m_dcxo[index]->readCY29411Settings(valid, settings);
}

int
GeneralReg::readDCXOSettingsSi570(uint8_t index, bool* valid, si570_ctrl::si570_settings_type *settings) {
  assert(m_initDone);
  // Check that index is in range.
  if(!getDCXOInRange(index)){
    return -1;
  }

  return m_dcxo[index]->readSi570Settings(valid, settings);
}
