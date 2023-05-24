#ifndef GENERAL_REG_H
#define GENERAL_REG_H

#include <stdint.h>
#include "gen_dcxo_ctrl.h"

#define MAX_XO (2)
#define NUM_XO (2)

// Class Definition
class GeneralReg {

  public:

    GeneralReg();
    virtual ~GeneralReg() {};

    // -- Implementation Specific Methods --

    // Initialize the control software (mandatory, do this first!)
    void init(gen_dcxo_ctrl* dcxo_objects[MAX_XO]);

    // Get Init Done
    bool getInitDone();

    // Debug and Interface Verification
    int  getZeroes(uint32_t* Zeroes);
    int  getOnes(uint32_t* Ones);
    int  getLoopback(uint32_t Index, uint32_t* Loopback);
    void setLoopback(uint32_t Index, uint32_t Loopback);
    int  getDebugPulseCount(uint32_t* DebugPulseCount);
    void setDebugPulseCount(uint32_t DebugPulseCount);

    // FPGA Index
    int getFPGAIndex(bool* index);
    int setFPGAIndex(bool index);

    // FPGA Reset
    int setFPGAReset(bool reset);

    // HDMI
    int getHdmiInHPD(uint8_t index, bool* hpd);
    int getHdmiOutHPD(uint8_t index, bool* hpd);
    int getHdmiInCableDetect(uint8_t index, bool* cableDetect);
    int getHdmiInCableDetectMux(uint8_t index, bool* cableDetect);
    int getHdmiMuxSelect(uint8_t index, bool* select);
    int setHdmiMuxSelect(uint8_t index, bool select);
    int getHdmiOutDisable(uint8_t index, bool* disable);
    int setHdmiOutDisable(uint8_t index, bool disable);
    int getHdmiOut5VDisable(uint8_t index, bool* disable);
    int setHdmiOut5VDisable(uint8_t index, bool disable);
    int getHdmiBridgeReset(uint8_t index, bool* reset);
    int setHdmiBridgeReset(uint8_t index, bool reset);

    // HDMI MB
    int getHdmiPause(bool* pause);
    int setHdmiPause(bool pause);
    int getHdmiReset(bool* reset);
    int setHdmiReset(bool reset);

    // USB Reads
    int getUsbReset(bool* reset);
    int setUsbReset(bool reset);

    // Clock Frequencies Verification
    int getXGEClkFrequency(uint32_t* frequency);
    int get125mhzClkFrequency(uint32_t* frequency);
    int get62m5hzClkFrequency(uint32_t* frequency);
    int get312m5hzClkFrequency(uint32_t* frequency);
    int get156m25hzClkFrequency(uint32_t* frequency);
    int getHdmiSouthTxClkFrequency(uint32_t* frequency);
    int getHdmiNorthTxClkFrequency(uint32_t* frequency);
    int getInterFPGAClkFrequency(uint32_t* frequency);
    int getDRUClkFrequency(uint32_t* frequency);
    int getReflockClkFrequency(uint32_t* frequency);
    int getMgt110Refclk1ClkFrequency(uint32_t* frequency);
    int getMgt112Refclk1ClkFrequency(uint32_t* frequency);

    // ICRON MDIO
    int getUsbPhyMdio(uint32_t phy_addr, uint32_t reg_addr, uint32_t* status);
    int setUsbPhyMdio(uint32_t phy_addr, uint32_t reg_addr, uint32_t command);

    // Analog Audio
    int getAnalogMute(bool* mute);
    int setAnalogMute(bool mute);

    // USB TX Src Selection
    int getUSBTxSrcSel(bool* src);
    int setUSBTxSrcSel(bool src);

    // SPDIF Audio
    int getSPDIFMute(uint8_t index, bool* mute);
    int setSPDIFMute(uint8_t index, bool mute);

    // I2C Expander
    int getI2CExpanderReset(bool* reset);
    int setI2CExpanderReset(bool reset);

    // Board Level Components
    int getPbState(bool* pb);
    int getLedRgb(uint8_t* red, uint8_t* green, uint8_t* blue);
    int setLedRgb(uint8_t red, uint8_t green, uint8_t blue);

    // Power Supply
    int getSupply12vMonitor(uint8_t index, bool* monitor);
    int getSupplyOrFault(uint8_t index, bool* orfault);

    int getTRMSelect(bool* select);
    int setTRMSelect(bool select);
    int getXgeRxInvertPolarity(uint8_t index, bool* invert);
    int setXgeRxInvertPolarity(uint8_t index, bool invert);
    int getXgeTxInvertPolarity(uint8_t index, bool* invert);
    int setXgeTxInvertPolarity(uint8_t index, bool invert);
    int getSpiDisplay(uint8_t* data);
    int setSpiDisplay(uint8_t data);
    int getToggleSwitch(bool a_not_b, bool* toggle);
    int getLocalFault(bool* fault);
    int setLocalFault(bool fault);
    int getFanFail(bool* fail);

    // DCXO
    // Allows DCXO to be specified. si570DefaultFrequency may be omitted if CY29411 is specified.
    int initDCXO(uint8_t index, dcxo_ctrl::dcxo_select_type dcxo, uint32_t si570DefaultFrequency = 0);
    // DCXO determined automatically. si570DefaultFrequency required.
    int initDCXO(uint8_t index, uint32_t si570DefaultFrequency);
    int setDCXOClock(uint8_t index, uint32_t frequency, bool cy29411AcceptBestStableFreq);
    int setDCXOLockEnable(uint8_t index, bool value);
    int getDCXOLockEnable(uint8_t index, bool *value);
    int setDCXODone(uint8_t index, bool value);
    int getDCXODone(uint8_t index, bool* value);

    int readDCXOSelect(uint8_t index, bool* initialized, dcxo_ctrl::dcxo_select_type* dcxo);
    int readDCXOSettingsCY29411(uint8_t index, bool* valid, cy29411_ctrl::cy29411_settings_type* settings);
    int readDCXOSettingsSi570(uint8_t index, bool* valid, si570_ctrl::si570_settings_type* settings);

  private:

    // -- Implementation Specific Methods --
    bool getDCXOInRange(uint8_t index);

    // Write to register interface
    virtual void writereg(uint32_t reg, uint32_t data) = 0;
    // Read from register interface
    virtual uint32_t readreg(uint32_t reg) = 0;

   // -- Internal Data Members --
    bool m_initDone;
    gen_dcxo_ctrl* m_dcxo[MAX_XO];
};

 // Internal Register Interface
namespace GenReg {
  const uint32_t REG_ZEROES                               = 0;
  const uint32_t REG_ONES                                 = 1;
  const uint32_t REG_LOOPBACK0                            = 2;
  const uint32_t REG_LOOPBACK1                            = 3;
  const uint32_t REG_DEBUG_PLS                            = 4;
    const uint32_t RANGE_TEST_PULSE                         = 0;
    const uint32_t RANGE_TEST_COUNT_LSB                     = 1;
    const uint32_t RANGE_TEST_COUNT_MSB                     = 31;
  const uint32_t REG_HDMI_IN_HPD                          = 5;
    const uint32_t RANGE_HDMI_IN_HPD_0                      = 0;
    const uint32_t RANGE_HDMI_IN_HPD_1                      = 4;
  const uint32_t REG_HDMI_OUT_HPD                         = 6;
    const uint32_t RANGE_HDMI_OUT_HPD_0                     = 0;
    const uint32_t RANGE_HDMI_OUT_HPD_1                     = 4;
  const uint32_t REG_HDMI_IN_CABLE_DETECT                 = 7;
    const uint32_t RANGE_HDMI_IN_CABLE_DETECT_0             = 0;
    const uint32_t RANGE_HDMI_IN_CABLE_DETECT_1             = 4;
    const uint32_t RANGE_HDMI_IN_CABLE_DETECT_2             = 8;
    const uint32_t RANGE_HDMI_IN_CABLE_DETECT_3             = 12;
  const uint32_t REG_HDMI_IN_CABLE_DETECT_MUX             = 8;
    const uint32_t RANGE_HDMI_IN_CABLE_DETECT_MUX_0         = 0;
    const uint32_t RANGE_HDMI_IN_CABLE_DETECT_MUX_1         = 4;
  const uint32_t REG_HDMI_MUX_SEL                         = 9;
    const uint32_t RANGE_HDMI_IN_MUX_SEL_0                  = 0;
    const uint32_t RANGE_HDMI_IN_MUX_SEL_1                  = 4;
    const uint32_t RANGE_HDMI_IN_MUX_SEL_2                  = 8;
    const uint32_t RANGE_HDMI_IN_MUX_SEL_3                  = 12;
    const uint32_t RANGE_HDMI_IN_MUX_SEL_4                  = 16;
    const uint32_t RANGE_HDMI_IN_MUX_SEL_5                  = 20;
    const uint32_t RANGE_HDMI_IN_MUX_SEL_6                  = 24;
    const uint32_t RANGE_HDMI_IN_MUX_SEL_7                  = 28;
  const uint32_t REG_USB_RESET                            = 10;
    const uint32_t RANGE_USB_RESET                          = 0;
  const uint32_t REG_MEASURE_XGE                          = 11;
    const uint32_t RANGE_MEASURE_XGE_LSB                    = 0;
    const uint32_t RANGE_MEASURE_XGE_MSB                    = 25;
  const uint32_t REG_MEASURE_109_125MHZ                   = 12;
    const uint32_t RANGE_MEASURE_109_125MHZ_LSB             = 0;
    const uint32_t RANGE_MEASURE_109_125MHZ_MSB             = 24;
  const uint32_t REG_MEASURE_109_62M5HZ                   = 13;
    const uint32_t RANGE_MEASURE_109_62M5HZ_LSB             = 0;
    const uint32_t RANGE_MEASURE_109_62M5HZ_MSB             = 24;
  const uint32_t REG_MDIO_USB_PHY_COMMAND                 = 14;
    const uint32_t RANGE_MDIO_USB_PHY_COMMAND_LSB           = 0;
    const uint32_t RANGE_MDIO_USB_PHY_COMMAND_MSB           = 27;
  const uint32_t REG_MDIO_USB_PHY_START                   = 15;
    const uint32_t RANGE_MDIO_USB_PHY_START                 = 0;
  const uint32_t REG_MDIO_USB_PHY_STATUS                  = 16;
    const uint32_t RANGE_MDIO_USB_PHY_STATUS_LSB            = 0;
    const uint32_t RANGE_MDIO_USB_PHY_STATUS_MSB            = 15;
    const uint32_t RANGE_MDIO_USB_PHY_STAT_READY            = 31;
  const uint32_t REG_AUDIO_CONTROL_ANALOG                 = 17;
    const uint32_t RANGE_ANALOG_MUTE                        = 0;
  const uint32_t REG_AUDIO_CONTROL_SPDIF                  = 18;
    const uint32_t RANGE_SPDIF_MUTE_LSB                     = 0;
    const uint32_t RANGE_SPDIF_MUTE_MSB                     = 1;
  const uint32_t REG_I2C_EXPANDER                         = 19;
    const uint32_t RANGE_I2C_EXPANDER_RESET                 = 0;
  const uint32_t REG_PUSH_BUTTON                          = 20;
    const uint32_t RANGE_PUSH_BUTTON                        = 0;
  const uint32_t REG_PS_12VMON                            = 21;
    const uint32_t RANGE_PS1_12VMON                         = 0;
    const uint32_t RANGE_PS2_12VMON                         = 4;
  const uint32_t REG_PS_ORFAULT_N                         = 22;
    const uint32_t RANGE_PS1_ORFAULT_N                      = 0;
    const uint32_t RANGE_PS2_ORFAULT_N                      = 4;
  const uint32_t REG_LED_CONTROL                          = 23;
    const uint32_t RANGE_LED_R_CONTROL_LSB                  = 0;
    const uint32_t RANGE_LED_R_CONTROL_MSB                  = 7;
    const uint32_t RANGE_LED_G_CONTROL_LSB                  = 8;
    const uint32_t RANGE_LED_G_CONTROL_MSB                  = 15;
    const uint32_t RANGE_LED_B_CONTROL_LSB                  = 16;
    const uint32_t RANGE_LED_B_CONTROL_MSB                  = 23;
  const uint32_t REG_HDMI_OUT_DISABLE                     = 24;
    const uint32_t RANGE_HDMI_OUT_DISABLE_0                 = 0;
    const uint32_t RANGE_HDMI_OUT_DISABLE_1                 = 4;
  const uint32_t REG_HDMI_OUT_5V_DISABLE                  = 25;
    const uint32_t RANGE_HDMI_OUT_5V_DISABLE_0              = 0;
    const uint32_t RANGE_HDMI_OUT_5V_DISABLE_1              = 4;
  const uint32_t REG_MEASURE_HDMI_SOUTH_TX                = 26;
    const uint32_t RANGE_MEASURE_HDMI_SOUTH_TX_LSB          = 0;
    const uint32_t RANGE_MEASURE_HDMI_SOUTH_TX_MSB          = 26;
  const uint32_t REG_MEASURE_HDMI_NORTH_TX                = 27;
    const uint32_t RANGE_MEASURE_HDMI_NORTH_TX_LSB          = 0;
    const uint32_t RANGE_MEASURE_HDMI_NORTH_TX_MSB          = 26;
  const uint32_t REG_HDMI_BRG_RST                         = 28;
    const uint32_t RANGE_HDMI_BRG_RST_0                     = 0;
    const uint32_t RANGE_HDMI_BRG_RST_1                     = 4;
    const uint32_t RANGE_HDMI_BRG_RST_2                     = 8;
    const uint32_t RANGE_HDMI_BRG_RST_3                     = 12;
    const uint32_t RANGE_HDMI_BRG_RST_4                     = 16;
    const uint32_t RANGE_HDMI_BRG_RST_5                     = 20;
  const uint32_t REG_HDMI_MB                              = 29;
    const uint32_t RANGE_HDMI_PAUSE                         = 0;
    const uint32_t RANGE_HDMI_RESET                         = 4;
  const uint32_t REG_FPGA_INDEX                           = 30;
    const uint32_t RANGE_FPGA_INDEX                         = 0;
  const uint32_t REG_FPGA_RESET                           = 31;
    const uint32_t RANGE_FPGA_RESET                         = 0;
  const uint32_t REG_ETHERNET_RESET                       = 32;
    const uint32_t RANGE_ETHERNET_RESET                     = 0;
    const uint32_t RANGE_ETHERNET_GTX_STATUS_LSB            = 16;
    const uint32_t RANGE_ETHERNET_GTX_STATUS_MSB            = 31;
  const uint32_t REG_MEASURE_INTERFPGA                    = 33;
    const uint32_t RANGE_MEASURE_INTERFPGA_LSB              = 0;
    const uint32_t RANGE_MEASURE_INTERFPGA_MSB              = 25;
  const uint32_t REG_MEASURE_DRU                          = 34;
    const uint32_t RANGE_MEASURE_DRU_LSB                    = 0;
    const uint32_t RANGE_MEASURE_DRU_MSB                    = 24;
  const uint32_t REG_MEASURE_REFLOCK                      = 35;
    const uint32_t RANGE_MEASURE_REFLOCK_LSB                = 0;
    const uint32_t RANGE_MEASURE_REFLOCK_MSB                = 24;
  const uint32_t REG_MEASURE_109_312M5HZ                  = 36;
    const uint32_t RANGE_MEASURE_109_312M5HZ_LSB            = 0;
    const uint32_t RANGE_MEASURE_109_312M5HZ_MSB            = 26;
  const uint32_t REG_MEASURE_109_156M25HZ                 = 37;
    const uint32_t RANGE_MEASURE_109_156M25HZ_LSB           = 0;
    const uint32_t RANGE_MEASURE_109_156M25HZ_MSB           = 26;
  const uint32_t REG_USB_TX_SRC_SEL                       = 38;
    const uint32_t RANGE_USB_TX_SRC_SEL                     = 0;
  const uint32_t REG_TRXS_TRM_SEL                         = 39;
    const uint32_t RANGE_TRXS_TRM_SEL                       = 0;
  const uint32_t REG_XGE_POLARITY_INVERT                  = 40;
    const uint32_t RANGE_XGE_TX_POLARITY_INVERT_LSB         = 0;
    const uint32_t RANGE_XGE_TX_POLARITY_INVERT_MSB         = 3;
    const uint32_t RANGE_XGE_RX_POLARITY_INVERT_LSB         = 4;
    const uint32_t RANGE_XGE_RX_POLARITY_INVERT_MSB         = 7;
  const uint32_t REG_SPI_DISPLAY                          = 41;
    const uint32_t RANGE_SPI_DISPLAY_DATA_LSB               = 0;
    const uint32_t RANGE_SPI_DISPLAY_DATA_MSB               = 7;
    const uint32_t RANGE_SPI_DISPLAY_START                  = 8;
  const uint32_t REG_TOGGLE_SWITCH                        = 42;
    const uint32_t RANGE_TOGGLE_SWITCH_A                    = 0;
    const uint32_t RANGE_TOGGLE_SWITCH_B                    = 4;
  const uint32_t REG_LOCAL_FAULT                          = 43;
    const uint32_t RANGE_LOCAL_FAULT                        = 0;
  const uint32_t REG_FAN_FAIL                             = 44;
    const uint32_t RANGE_FAN_FAIL                           = 0;
  const uint32_t REG_MEASURE_MGT110_REFCLK1               = 45;
    const uint32_t RANGE_MEASURE_MGT110_REFCLK1_LSB         = 0;
    const uint32_t RANGE_MEASURE_MGT110_REFCLK1_MSB         = 26;
  const uint32_t REG_MEASURE_MGT112_REFCLK1               = 46;
    const uint32_t RANGE_MEASURE_MGT112_REFCLK1_LSB         = 0;
    const uint32_t RANGE_MEASURE_MGT112_REFCLK1_MSB         = 26;
  const uint32_t REG_DCXO_CONTROL_0                       = 47;
    const uint32_t RANGE_DCXO_CTRL_SELECT                   = 0;
    const uint32_t RANGE_DCXO_CTRL_DID                      = 4;
    const uint32_t RANGE_DCXO_CTRL_START                    = 5;
    const uint32_t RANGE_DCXO_CTRL_READ                     = 6;
    const uint32_t RANGE_DCXO_CTRL_RESET                    = 7;
    const uint32_t RANGE_DCXO_CTRL_LOCK_ENABLE              = 8;
    const uint32_t RANGE_DCXO_CTRL_DONE                     = 9;
    const uint32_t RANGE_DCXO_CTRL_IDLE                     = 16;
    const uint32_t RANGE_DCXO_CTRL_READ_VALID               = 17;
    const uint32_t RANGE_DCXO_CTRL_DID_VALID                = 18;
    const uint32_t RANGE_DCXO_DID_LSB                       = 20;
    const uint32_t RANGE_DCXO_DID_MSB                       = 27;
  const uint32_t REG_DCXO_CONTROL_1                       = 48;
  const uint32_t REG_DCXO_SI570_PROG_LSB_0                = 49;
    const uint32_t RANGE_DCXO_SI570_PROG_LSB_RFREQ_LSB      = 0;
    const uint32_t RANGE_DCXO_SI570_PROG_LSB_RFREQ_MSB      = 31;
  const uint32_t REG_DCXO_SI570_PROG_LSB_1                = 50;
  const uint32_t REG_DCXO_SI570_PROG_MSB_0                = 51;
    const uint32_t RANGE_DCXO_SI570_PROG_MSB_RFREQ_LSB      = 0;
    const uint32_t RANGE_DCXO_SI570_PROG_MSB_RFREQ_MSB      = 5;
    const uint32_t RANGE_DCXO_SI570_PROG_MSB_HSDIV_LSB      = 6;
    const uint32_t RANGE_DCXO_SI570_PROG_MSB_HSDIV_MSB      = 8;
    const uint32_t RANGE_DCXO_SI570_PROG_MSB_N1_LSB         = 9;
    const uint32_t RANGE_DCXO_SI570_PROG_MSB_N1_MSB         = 15;
  const uint32_t REG_DCXO_SI570_PROG_MSB_1                = 52;
  const uint32_t REG_DCXO_SI570_READ_LSB_0                = 53;
    const uint32_t RANGE_DCXO_SI570_READ_LSB_RFREQ_LSB      = 0;
    const uint32_t RANGE_DCXO_SI570_READ_LSB_RFREQ_MSB      = 31;
  const uint32_t REG_DCXO_SI570_READ_LSB_1                = 54;
  const uint32_t REG_DCXO_SI570_READ_MSB_0                = 55;
    const uint32_t RANGE_DCXO_SI570_READ_MSB_RFREQ_LSB      = 0;
    const uint32_t RANGE_DCXO_SI570_READ_MSB_RFREQ_MSB      = 5;
    const uint32_t RANGE_DCXO_SI570_READ_MSB_HSDIV_LSB      = 6;
    const uint32_t RANGE_DCXO_SI570_READ_MSB_HSDIV_MSB      = 8;
    const uint32_t RANGE_DCXO_SI570_READ_MSB_N1_LSB         = 9;
    const uint32_t RANGE_DCXO_SI570_READ_MSB_N1_MSB         = 15;
  const uint32_t REG_DCXO_SI570_READ_MSB_1                = 56;
  const uint32_t REG_DCXO_CY29411_PROG_0                  = 57;
    const uint32_t RANGE_DCXO_CY29411_PROG_DIVO_LSB         = 0;
    const uint32_t RANGE_DCXO_CY29411_PROG_DIVO_MSB         = 8;
    const uint32_t RANGE_DCXO_CY29411_PROG_DIVN_INT_LSB     = 16;
    const uint32_t RANGE_DCXO_CY29411_PROG_DIVN_INT_MSB     = 24;
    const uint32_t RANGE_DCXO_CY29411_PROG_PLL_MODE         = 27;
    const uint32_t RANGE_DCXO_CY29411_PROG_ICP_BIN_LSB      = 28;
    const uint32_t RANGE_DCXO_CY29411_PROG_ICP_BIN_MSB      = 30;
    const uint32_t RANGE_DCXO_CY29411_PROG_ICP_OFFSET       = 31;
  const uint32_t REG_DCXO_CY29411_PROG_1                  = 58;
  const uint32_t REG_DCXO_CY29411_PROG_FRAC_0             = 59;
    const uint32_t RANGE_DCXO_CY29411_PROG_DIVN_FRAC_LSB    = 0;
    const uint32_t RANGE_DCXO_CY29411_PROG_DIVN_FRAC_MSB    = 23;
  const uint32_t REG_DCXO_CY29411_PROG_FRAC_1             = 60;
  const uint32_t REG_DCXO_CY29411_READ_0                  = 61;
    const uint32_t RANGE_DCXO_CY29411_READ_DIVO_LSB         = 0;
    const uint32_t RANGE_DCXO_CY29411_READ_DIVO_MSB         = 8;
    const uint32_t RANGE_DCXO_CY29411_READ_DIVN_INT_LSB     = 16;
    const uint32_t RANGE_DCXO_CY29411_READ_DIVN_INT_MSB     = 24;
    const uint32_t RANGE_DCXO_CY29411_READ_PLL_MODE         = 27;
    const uint32_t RANGE_DCXO_CY29411_READ_ICP_BIN_LSB      = 28;
    const uint32_t RANGE_DCXO_CY29411_READ_ICP_BIN_MSB      = 30;
    const uint32_t RANGE_DCXO_CY29411_READ_ICP_OFFSET       = 31;
  const uint32_t REG_DCXO_CY29411_READ_1                  = 62;
  const uint32_t REG_DCXO_CY29411_READ_FRAC_0             = 63;
    const uint32_t RANGE_DCXO_CY29411_READ_DIVN_FRAC_LSB    = 0;
    const uint32_t RANGE_DCXO_CY29411_READ_DIVN_FRAC_MSB    = 23;
  const uint32_t REG_DCXO_CY29411_READ_FRAC_1             = 64;

  const uint32_t N_REG                                    = 65;
}

#endif //GENERAL_REG_H
