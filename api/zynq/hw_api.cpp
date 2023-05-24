#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <unistd.h>
#include <time.h>

#include "hw_api.h"

/* -- Hidden helper Functions and Macros -- */

// Address space safety
inline uint32_t
addr_lim(uint32_t addr, uint32_t base, uint32_t high) {
#ifdef DEBUG_ADDR_LIM
    assert(addr >= base);
    assert(addr <= high);
#endif
    return std::min(std::max(addr,base),high);
}

// Address conversion
// Includes Address space safety
inline uint32_t
addr_conv(uint32_t addr, uint32_t bytes_per_addr, uint32_t base, uint32_t high) {
    return addr_lim(addr * bytes_per_addr + base, base, high);
}

/* -- Low Level Functions -- */

uint32_t
HW_API::readXGEDRPReg(uint32_t channel, uint32_t reg) {
    if (channel == 0) {
        return readl(addr_conv(reg, XGED0_BYTE_ADDR, XGED0_BASE_ADDR, XGED0_HIGH_ADDR));
    } else if (channel == 1) {
        return readl(addr_conv(reg, XGED1_BYTE_ADDR, XGED1_BASE_ADDR, XGED1_HIGH_ADDR));
    } else if (channel == 2) {
        return readl(addr_conv(reg, XGED2_BYTE_ADDR, XGED2_BASE_ADDR, XGED2_HIGH_ADDR));
    } else if (channel == 3) {
        return readl(addr_conv(reg, XGED3_BYTE_ADDR, XGED3_BASE_ADDR, XGED3_HIGH_ADDR));
    } else {
        return 0;
    }
}

void
HW_API::writeXGEDRPReg(uint32_t channel, uint32_t reg, uint32_t data) {
    if (channel == 0) {
        writel(addr_conv(reg, XGED0_BYTE_ADDR, XGED0_BASE_ADDR, XGED0_HIGH_ADDR), data);
    } else if (channel == 1) {
        writel(addr_conv(reg, XGED1_BYTE_ADDR, XGED1_BASE_ADDR, XGED1_HIGH_ADDR), data);
    } else if (channel == 2) {
        writel(addr_conv(reg, XGED2_BYTE_ADDR, XGED2_BASE_ADDR, XGED2_HIGH_ADDR), data);
    } else if (channel == 3) {
        writel(addr_conv(reg, XGED3_BYTE_ADDR, XGED3_BASE_ADDR, XGED3_HIGH_ADDR), data);
    }
    return;
}

uint32_t
HW_API::readDRPNLReg(uint32_t reg) {
    return readl(addr_conv(reg, DRPNL_BYTE_ADDR, DRPNL_BASE_ADDR, DRPNL_HIGH_ADDR));
}

void
HW_API::writeDRPNLReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, DRPNL_BYTE_ADDR, DRPNL_BASE_ADDR, DRPNL_HIGH_ADDR), data);
    return;
}

uint32_t
HW_API::readHDMIIPReg(uint32_t channel, uint32_t reg) {
    if (channel == 0) {
        return readl(addr_conv(reg, HDMI0_BYTE_ADDR, HDMI0_BASE_ADDR, HDMI0_HIGH_ADDR));
    } else if (channel == 1) {
        return readl(addr_conv(reg, HDMI1_BYTE_ADDR, HDMI1_BASE_ADDR, HDMI1_HIGH_ADDR));
    } else {
        return 0;
    }
}

void
HW_API::writeHDMIIPReg(uint32_t channel, uint32_t reg, uint32_t data) {
    if (channel == 0) {
        writel(addr_conv(reg, HDMI0_BYTE_ADDR, HDMI0_BASE_ADDR, HDMI0_HIGH_ADDR), data);
    } else if (channel == 1) {
        writel(addr_conv(reg, HDMI1_BYTE_ADDR, HDMI1_BASE_ADDR, HDMI1_HIGH_ADDR), data);
    }
    return;
}

uint32_t
HW_API::readXGEMacReg(uint32_t channel, uint32_t reg) {
    if (channel == 0) {
        return readl(addr_conv(reg, XGEM0_BYTE_ADDR, XGEM0_BASE_ADDR, XGEM0_HIGH_ADDR));
    } else if (channel == 1) {
        return readl(addr_conv(reg, XGEM1_BYTE_ADDR, XGEM1_BASE_ADDR, XGEM1_HIGH_ADDR));
    } else if (channel == 2) {
        return readl(addr_conv(reg, XGEM2_BYTE_ADDR, XGEM2_BASE_ADDR, XGEM2_HIGH_ADDR));
    } else if (channel == 3) {
        return readl(addr_conv(reg, XGEM3_BYTE_ADDR, XGEM3_BASE_ADDR, XGEM3_HIGH_ADDR));
    } else {
        return 0;
    }
}

void
HW_API::writeXGEMacReg(uint32_t channel, uint32_t reg, uint32_t data) {
    if (channel == 0) {
        writel(addr_conv(reg, XGEM0_BYTE_ADDR, XGEM0_BASE_ADDR, XGEM0_HIGH_ADDR), data);
    } else if (channel == 1) {
        writel(addr_conv(reg, XGEM1_BYTE_ADDR, XGEM1_BASE_ADDR, XGEM1_HIGH_ADDR), data);
    } else if (channel == 2) {
        writel(addr_conv(reg, XGEM2_BYTE_ADDR, XGEM2_BASE_ADDR, XGEM2_HIGH_ADDR), data);
    } else if (channel == 3) {
        writel(addr_conv(reg, XGEM3_BYTE_ADDR, XGEM3_BASE_ADDR, XGEM3_HIGH_ADDR), data);
    }
    return;
}

uint32_t
HW_API::readTEMACReg(uint32_t channel, uint32_t reg) {
    if (channel == 0) {
        return readl(addr_conv(reg, XGEM0_BYTE_ADDR, XGEM0_BASE_ADDR, XGEM0_HIGH_ADDR));
    } else if (channel == 1) {
        return readl(addr_conv(reg, XGEM1_BYTE_ADDR, XGEM1_BASE_ADDR, XGEM1_HIGH_ADDR));
    } else if (channel == 2) {
        return readl(addr_conv(reg, XGEM2_BYTE_ADDR, XGEM2_BASE_ADDR, XGEM2_HIGH_ADDR));
    } else if (channel == 3) {
        return readl(addr_conv(reg, XGEM3_BYTE_ADDR, XGEM3_BASE_ADDR, XGEM3_HIGH_ADDR));
    } else {
        return 0;
    }
}

void
HW_API::writeTEMACReg(uint32_t channel, uint32_t reg, uint32_t data) {
    if (channel == 0) {
        writel(addr_conv(reg, XGEM0_BYTE_ADDR, XGEM0_BASE_ADDR, XGEM0_HIGH_ADDR), data);
    } else if (channel == 1) {
        writel(addr_conv(reg, XGEM1_BYTE_ADDR, XGEM1_BASE_ADDR, XGEM1_HIGH_ADDR), data);
    } else if (channel == 2) {
        writel(addr_conv(reg, XGEM2_BYTE_ADDR, XGEM2_BASE_ADDR, XGEM2_HIGH_ADDR), data);
    } else if (channel == 3) {
        writel(addr_conv(reg, XGEM3_BYTE_ADDR, XGEM3_BASE_ADDR, XGEM3_HIGH_ADDR), data);
    }
    return;
}

uint32_t
HW_API::readXGEIfReg(uint32_t reg) {
    return readl(addr_conv(reg, IP_IF_BYTE_ADDR, IP_IF_BASE_ADDR, IP_IF_HIGH_ADDR));
}

void
HW_API::writeXGEIfReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, IP_IF_BYTE_ADDR, IP_IF_BASE_ADDR, IP_IF_HIGH_ADDR), data);
    return;
}

uint64_t
HW_API::readXGETxReg(uint32_t reg) {
    int status = 0;
    status |= HW_API::lockXGETxReadWord(true);
    uint64_t data = readll(addr_conv(reg, AV_IP_BYTE_ADDR, AV_IP_BASE_ADDR, AV_IP_HIGH_ADDR));
    status |= HW_API::lockXGETxReadWord(false);
    if (status != 0) {
        printf("HW_API:ERROR:XGE Tx Read Word Lock Error!\n");
    }
    return data;
}

void
HW_API::writeXGETxReg(uint32_t reg, uint64_t data) {
    int status = 0;
    status |= HW_API::lockXGETxWriteWord(true);
    writell(addr_conv(reg, AV_IP_BYTE_ADDR, AV_IP_BASE_ADDR, AV_IP_HIGH_ADDR), data);
    status |= HW_API::lockXGETxWriteWord(false);
    if (status != 0) {
        printf("HW_API:ERROR:XGE Tx Write Word Lock Error!\n");
    }
    return;
}

uint64_t
HW_API::readXGERxReg(uint32_t reg) {
    int status = 0;
    status |= HW_API::lockXGERxReadWord(true);
    uint64_t data = readll(addr_conv(reg, IP_AV_BYTE_ADDR, IP_AV_BASE_ADDR, IP_AV_HIGH_ADDR));
    status |= HW_API::lockXGERxReadWord(false);
    if (status != 0) {
        printf("HW_API:ERROR:XGE Rx Read Word Lock Error!\n");
    }
    return data;
}

void
HW_API::writeXGERxReg(uint32_t reg, uint64_t data) {
    int status = 0;
    status |= HW_API::lockXGERxWriteWord(true);
    writell(addr_conv(reg, IP_AV_BYTE_ADDR, IP_AV_BASE_ADDR, IP_AV_HIGH_ADDR), data);
    status |= HW_API::lockXGERxWriteWord(false);
    if (status != 0) {
        printf("HW_API:ERROR:XGE Rx Write Word Lock Error!\n");
    }
    return;
}

uint32_t
HW_API::readFPGAIDReg(uint32_t reg) {
    return readl(addr_conv(reg, FPGAI_BYTE_ADDR, FPGAI_BASE_ADDR, FPGAI_HIGH_ADDR));
}

void
HW_API::writeFPGAIDReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, FPGAI_BYTE_ADDR, FPGAI_BASE_ADDR, FPGAI_HIGH_ADDR), data);
    return;
}

uint32_t
HW_API::readXBARCONFIGReg(uint32_t reg) {
    return readl(addr_conv(reg, XBARC_BYTE_ADDR, XBARC_BASE_ADDR, XBARC_HIGH_ADDR));
}

void
HW_API::writeXBARCONFIGReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, XBARC_BYTE_ADDR, XBARC_BASE_ADDR, XBARC_HIGH_ADDR), data);
    return;
}

void
HW_API::writeVidProcReg(uint32_t reg, uint32_t data) {
  writel(addr_conv(reg, VIDPC_BYTE_ADDR, VIDPC_BASE_ADDR, VIDPC_HIGH_ADDR), data);
  return;
}

uint32_t
HW_API::readVidProcReg(uint32_t reg) {
  return readl(addr_conv(reg, VIDPC_BYTE_ADDR, VIDPC_BASE_ADDR, VIDPC_HIGH_ADDR));
}

uint32_t
HW_API::readScalerReg(uint32_t channel, uint32_t component, uint32_t register_address) {
    uint32_t sc_path  = channel%HW_API::SC_NUM_PATHS;
    uint32_t comp_idx  = component%HW_API::SC_NUM_COMPONENTS;
    return readl(addr_conv(register_address, SC_BYTE_ADDR[sc_path][comp_idx], SC_BASE_ADDR[sc_path][comp_idx], SC_HIGH_ADDR[sc_path][comp_idx]));
}

void
HW_API::writeScalerReg(uint32_t channel, uint32_t component, uint32_t register_address, uint32_t data) {
    uint32_t sc_path  = channel%HW_API::SC_NUM_PATHS;
    uint32_t comp_idx  = component%HW_API::SC_NUM_COMPONENTS;
    writel(addr_conv(register_address, SC_BYTE_ADDR[sc_path][comp_idx], SC_BASE_ADDR[sc_path][comp_idx], SC_HIGH_ADDR[sc_path][comp_idx]), data);
    return;
}

uint32_t
HW_API::readScalerAReg(uint32_t channel, uint32_t reg) {
    return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_SCALER_A,reg);
}

void
HW_API::writeScalerAReg(uint32_t channel, uint32_t reg, uint32_t data) {
    HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_SCALER_A,reg,data);
    return;
}

uint32_t
HW_API::readScalerBReg(uint32_t channel, uint32_t reg) {
    return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_SCALER_B,reg);
}

void
HW_API::writeScalerBReg(uint32_t channel, uint32_t reg, uint32_t data) {
    HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_SCALER_B,reg,data);
    return;
}

uint32_t
HW_API::readScaleRasterReg(uint32_t channel, uint32_t reg) {
    return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_RASTER,reg);
}

void
HW_API::writeScaleRasterReg(uint32_t channel, uint32_t reg, uint32_t data) {
    HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_RASTER,reg,data);
    return;
}

uint32_t
HW_API::readScaleMiscReg(uint32_t channel, uint32_t reg) {
    return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_MISC,reg);
}

void
HW_API::writeScaleMiscReg(uint32_t channel, uint32_t reg, uint32_t data) {
    HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_MISC,reg,data);
    return;
}

uint32_t
HW_API::readScalerWritePortReg(uint32_t channel, uint32_t reg) {
    return HW_API::readScalerWritePortReg(channel, 0, reg);
}

uint32_t
HW_API::readScalerWritePortReg(uint32_t channel, uint32_t tile, uint32_t reg) {
    switch (tile) {
      case 0:
        return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_0,reg);
      case 1:
        return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_1,reg);
      case 2:
        return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_2,reg);
      case 3:
        return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_3,reg);
      default:
        return 0;
    }
}

void
HW_API::writeScalerWritePortReg(uint32_t channel, uint32_t reg, uint32_t data) {
    HW_API::writeScalerWritePortReg(channel, 0, reg, data);
}

void
HW_API::writeScalerWritePortReg(uint32_t channel, uint32_t tile, uint32_t reg, uint32_t data) {
    switch (tile) {
      case 0:
        HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_0,reg,data);
        break;
      case 1:
        HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_1,reg,data);
        break;
      case 2:
        HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_2,reg,data);
        break;
      case 3:
        HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_3,reg,data);
        break;
      default:
        HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_0,reg,data);
    }
}

uint32_t
HW_API::readScalerDecWritePortReg(uint32_t channel, uint32_t reg) {
    return HW_API::readScalerDecWritePortReg(channel, 0, reg);
}

uint32_t
HW_API::readScalerDecWritePortReg(uint32_t channel, uint32_t tile, uint32_t reg) {
    switch (tile) {
      case 0:
        return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_0,reg);
      case 1:
        return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_1,reg);
      case 2:
        return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_2,reg);
      case 3:
        return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_3,reg);
      default:
        return 0;
    }
}

void
HW_API::writeScalerDecWritePortReg(uint32_t channel, uint32_t reg, uint32_t data) {
    HW_API::writeScalerDecWritePortReg(channel, 0, reg, data);
}

void
HW_API::writeScalerDecWritePortReg(uint32_t channel, uint32_t tile, uint32_t reg, uint32_t data) {
    switch (tile) {
      case 0:
        HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_0,reg,data);
        break;
      case 1:
        HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_1,reg,data);
        break;
      case 2:
        HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_2,reg,data);
        break;
      case 3:
        HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_3,reg,data);
        break;
      default:
        HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_WPORT_0,reg,data);
    }
}

uint32_t
HW_API::readScalerPlayoutReg(uint32_t channel, uint32_t reg) {
    return HW_API::readScalerReg(channel,HW_API::SC_COMP_IDX_PLAYOUT,reg);
}

void
HW_API::writeScalerPlayoutReg(uint32_t channel, uint32_t reg, uint32_t data) {
    HW_API::writeScalerReg(channel,HW_API::SC_COMP_IDX_PLAYOUT,reg,data);
    return;
}

uint32_t
HW_API::readAxiDmaIpReg(uint32_t index, uint32_t reg){
  if (index == 0) {
    return readl(addr_conv(reg, AXIDMA0_IP_BYTE_ADDR, AXIDMA0_IP_BASE_ADDR, AXIDMA0_IP_HIGH_ADDR));
  } else if (index == 1) {
    return readl(addr_conv(reg, AXIDMA1_IP_BYTE_ADDR, AXIDMA1_IP_BASE_ADDR, AXIDMA1_IP_HIGH_ADDR));
  } else {
    return 0;
  }
}

void
HW_API::writeAxiDmaIpReg(uint32_t index, uint32_t reg, uint32_t data){
  if (index == 0) {
    writel(addr_conv(reg, AXIDMA0_IP_BYTE_ADDR, AXIDMA0_IP_BASE_ADDR, AXIDMA0_IP_HIGH_ADDR), data);
  } else if (index == 1) {
    writel(addr_conv(reg, AXIDMA1_IP_BYTE_ADDR, AXIDMA1_IP_BASE_ADDR, AXIDMA1_IP_HIGH_ADDR), data);
  }
  return;
}

uint32_t
HW_API::readAxiDmaMemReg(uint32_t index, uint32_t reg){
  if (index == 0) {
    return readl(addr_conv(reg, AXIDMA0_MEM_BYTE_ADDR, AXIDMA0_MEM_BASE_ADDR, AXIDMA0_MEM_HIGH_ADDR));
  } else if (index == 1) {
    return readl(addr_conv(reg, AXIDMA1_MEM_BYTE_ADDR, AXIDMA1_MEM_BASE_ADDR, AXIDMA1_MEM_HIGH_ADDR));
  } else {
    return 0;
  }
}

void
HW_API::writeAxiDmaMemReg(uint32_t index, uint32_t reg, uint32_t data){
  if (index == 0) {
    writel(addr_conv(reg, AXIDMA0_MEM_BYTE_ADDR, AXIDMA0_MEM_BASE_ADDR, AXIDMA0_MEM_HIGH_ADDR), data);
  } else if (index == 1) {
    writel(addr_conv(reg, AXIDMA1_MEM_BYTE_ADDR, AXIDMA1_MEM_BASE_ADDR, AXIDMA1_MEM_HIGH_ADDR), data);
  }
  return;
}

uint32_t
HW_API::readMemTestReg(uint32_t idx, uint32_t reg) {
    if (idx == 0) {
        return readl(addr_conv(reg, MTEST0_BYTE_ADDR, MTEST0_BASE_ADDR, MTEST0_HIGH_ADDR));
    } else if (idx == 1) {
        return readl(addr_conv(reg, MTEST1_BYTE_ADDR, MTEST1_BASE_ADDR, MTEST1_HIGH_ADDR));
    } else {
        return 0;
    }
}

void
HW_API::writeMemTestReg(uint32_t idx, uint32_t reg, uint32_t data) {
    if (idx == 0) {
        writel(addr_conv(reg, MTEST0_BYTE_ADDR, MTEST0_BASE_ADDR, MTEST0_HIGH_ADDR), data);
    } else if (idx == 1) {
        writel(addr_conv(reg, MTEST1_BYTE_ADDR, MTEST1_BASE_ADDR, MTEST1_HIGH_ADDR), data);
    }
}

uint32_t
HW_API::readIcronUSBReg(uint32_t reg) {
    return readl(addr_conv(reg, USB_BYTE_ADDR, USB_BASE_ADDR, USB_HIGH_ADDR));
}

void
HW_API::writeIcronUSBReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, USB_BYTE_ADDR, USB_BASE_ADDR, USB_HIGH_ADDR), data);
    return;
}

// Tico Encoder
uint64_t
HW_API::readTICOENCReg(uint32_t reg) {
    int status = 0;
    status |= HW_API::lockTicoEncReg(true);
    uint64_t data = readll(addr_conv(reg, AV_IP_BYTE_ADDR, AV_IP_BASE_ADDR, AV_IP_HIGH_ADDR));
    status |= HW_API::lockTicoEncReg(false);
    if (status != 0) {
        printf("HW_API:ERROR:Tico Enc Reg Lock Error!\n");
    }
    return data;
}

void
HW_API::writeTICOENCReg(uint32_t reg, uint64_t data) {
    int status = 0;
    status |= HW_API::lockTicoEncReg(true);
    writell(addr_conv(reg, AV_IP_BYTE_ADDR, AV_IP_BASE_ADDR, AV_IP_HIGH_ADDR), data);
    status |= HW_API::lockTicoEncReg(false);
    if (status != 0) {
        printf("HW_API:ERROR:Tico Enc Reg Lock Error!\n");
    }
    return;
}

// Tico Encoder
uint64_t
HW_API::readTICODECReg(uint32_t reg) {
    int status = 0;
    status |= HW_API::lockTicoDecReg(true);
    uint64_t data = readll(addr_conv(reg, IP_AV_BYTE_ADDR, IP_AV_BASE_ADDR, IP_AV_HIGH_ADDR));
    status |= HW_API::lockTicoDecReg(false);
    if (status != 0) {
        printf("HW_API:ERROR:Tico Dec Reg Lock Error!\n");
    }
    return data;
}

void
HW_API::writeTICODECReg(uint32_t reg, uint64_t data) {
    int status = 0;
    status |= HW_API::lockTicoDecReg(true);
    writell(addr_conv(reg, IP_AV_BYTE_ADDR, IP_AV_BASE_ADDR, IP_AV_HIGH_ADDR), data);
    status |= HW_API::lockTicoDecReg(false);
    if (status != 0) {
        printf("HW_API:ERROR:Tico Dec Reg Lock Error!\n");
    }
    return;
}

// Audio Mixer
uint32_t
HW_API::readAudioMixerReg(uint32_t idx, uint32_t reg){
    if (idx == 0) {
        return readl(addr_conv(reg, AMIXER0_BYTE_ADDR, AMIXER0_BASE_ADDR, AMIXER0_HIGH_ADDR));
    } else if (idx == 1) {
        return readl(addr_conv(reg, AMIXER1_BYTE_ADDR, AMIXER1_BASE_ADDR, AMIXER1_HIGH_ADDR));
    } else {
        return 0;
    }
}

void
HW_API::writeAudioMixerReg(uint32_t idx, uint32_t reg, uint32_t data){
    if (idx == 0) {
        writel(addr_conv(reg, AMIXER0_BYTE_ADDR, AMIXER0_BASE_ADDR, AMIXER0_HIGH_ADDR), data);
        return;
    } else if (idx == 1) {
        writel(addr_conv(reg, AMIXER1_BYTE_ADDR, AMIXER1_BASE_ADDR, AMIXER1_HIGH_ADDR), data);
        return;
    } else {
        return;
    }
}

uint32_t
HW_API::readPTPReg(uint32_t reg) {
    return readl(addr_conv(reg, PTP_BYTE_ADDR, PTP_BASE_ADDR, PTP_HIGH_ADDR));
}

void
HW_API::writePTPReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, PTP_BYTE_ADDR, PTP_BASE_ADDR, PTP_HIGH_ADDR), data);
    return;
}

uint32_t
HW_API::readGeneralReg(uint32_t reg) {
    return readl(addr_conv(reg, GENREG_BYTE_ADDR, GENREG_BASE_ADDR, GENREG_HIGH_ADDR));
}

void
HW_API::writeGeneralReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, GENREG_BYTE_ADDR, GENREG_BASE_ADDR, GENREG_HIGH_ADDR), data);
    return;
}

uint32_t
HW_API::readInterfpgaReg(uint8_t idx, uint32_t reg) {
    if (idx == 0) {
        return readl(addr_conv(reg, INTER_BYTE_ADDR, INTER_BASE_ADDR, INTER_HIGH_ADDR));
    } else if (idx == 1) {
        return readl(addr_conv(reg, INTER_IP_BYTE_ADDR, INTER_IP_BASE_ADDR, INTER_IP_HIGH_ADDR));
    } else {
        return 0;
    }
}

void
HW_API::writeInterfpgaReg(uint8_t idx, uint32_t reg, uint32_t data) {
    if (idx == 0) {
        writel(addr_conv(reg, INTER_BYTE_ADDR, INTER_BASE_ADDR, INTER_HIGH_ADDR), data);
    } else if (idx == 1) {
        writel(addr_conv(reg, INTER_IP_BYTE_ADDR, INTER_IP_BASE_ADDR, INTER_IP_HIGH_ADDR), data);
    } else {
        return;
    }
    return;
}

uint32_t
HW_API::readIPRxReg(uint32_t reg) {
    return readl(addr_conv(reg, IPRX_BYTE_ADDR, IPRX_BASE_ADDR, IPRX_HIGH_ADDR));
}

void
HW_API::writeIPRxReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, IPRX_BYTE_ADDR, IPRX_BASE_ADDR, IPRX_HIGH_ADDR), data);
    return;
}

uint32_t
HW_API::readIPTxReg(uint32_t reg) {
    return readl(addr_conv(reg, IPTX_BYTE_ADDR, IPTX_BASE_ADDR, IPTX_HIGH_ADDR));
}

void
HW_API::writeIPTxReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, IPTX_BYTE_ADDR, IPTX_BASE_ADDR, IPTX_HIGH_ADDR), data);
    return;
}

uint32_t
HW_API::readSDI12GReg(uint32_t reg) {
    return readl(addr_conv(reg, SDI12G_BYTE_ADDR, SDI12G_BASE_ADDR, SDI12G_HIGH_ADDR));
}

void
HW_API::writeSDI12GReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, SDI12G_BYTE_ADDR, SDI12G_BASE_ADDR, SDI12G_HIGH_ADDR), data);
    return;
}

uint32_t
HW_API::readGenlockReg(uint32_t reg) {
    return readl(addr_conv(reg, GENLOCK_BYTE_ADDR, GENLOCK_BASE_ADDR, GENLOCK_HIGH_ADDR));
}

void
HW_API::writeGenlockReg(uint32_t reg, uint32_t data) {
    writel(addr_conv(reg, GENLOCK_BYTE_ADDR, GENLOCK_BASE_ADDR, GENLOCK_HIGH_ADDR), data);
    return;
}

/* -- Low Level Mutexes -- */

HwLock ZYNQRegXgeRXReadWordLocker("/evertz_zynq_hwapi_xgerx_read_word_lock");
HwLock ZYNQRegXgeTXReadWordLocker("/evertz_zynq_hwapi_xgetx_read_word_lock");
HwLock ZYNQRegXgeRXWriteWordLocker("/evertz_zynq_hwapi_xgerx_write_word_lock");
HwLock ZYNQRegXgeTXWriteWordLocker("/evertz_zynq_hwapi_xgetx_write_word_lock");
HwLock ZYNQRegXGEDRPCh0Locker("/evertz_zynq_hwapi_xge_drpch0_reg_lock");
HwLock ZYNQRegXGEDRPCh1Locker("/evertz_zynq_hwapi_xge_drpch1_reg_lock");
HwLock ZYNQRegXGEDRPCoLocker("/evertz_zynq_hwapi_xge_drpco_reg_lock");
HwLock ZYNQRegHDMI1Locker("/evertz_zynq_hwapi_hdmi1_reg_lock");
HwLock ZYNQRegHDMI0Locker("/evertz_zynq_hwapi_hdmi0_reg_lock");
HwLock ZYNQRegXGEM0Locker("/evertz_zynq_hwapi_xgem0_reg_lock");
HwLock ZYNQRegXGEM1Locker("/evertz_zynq_hwapi_xgem1_reg_lock");
HwLock ZYNQRegXGEIFLocker("/evertz_zynq_hwapi_xgeif_reg_lock");
HwLock ZYNQRegXGETXLocker("/evertz_zynq_hwapi_xgetx_reg_lock");
HwLock ZYNQRegXGERXLocker("/evertz_zynq_hwapi_xgerx_reg_lock");
HwLock ZYNQRegFPGAIDLocker("/evertz_zynq_hwapi_fpgaid_reg_lock");
HwLock ZYNQRegXBARLocker("/evertz_zynq_hwapi_xbar_reg_lock");
HwLock ZYNQRegSCA0Locker("/evertz_zynq_hwapi_sca0_reg_lock");
HwLock ZYNQRegSCA1Locker("/evertz_zynq_hwapi_sca1_reg_lock");
HwLock ZYNQRegSCA2Locker("/evertz_zynq_hwapi_sca2_reg_lock");
HwLock ZYNQRegSCA3Locker("/evertz_zynq_hwapi_sca3_reg_lock");
HwLock ZYNQRegSCB0Locker("/evertz_zynq_hwapi_scb0_reg_lock");
HwLock ZYNQRegSCB1Locker("/evertz_zynq_hwapi_scb1_reg_lock");
HwLock ZYNQRegSCB2Locker("/evertz_zynq_hwapi_scb2_reg_lock");
HwLock ZYNQRegSCB3Locker("/evertz_zynq_hwapi_scb3_reg_lock");
HwLock ZYNQRegSCRS0Locker("/evertz_zynq_hwapi_scrs0_reg_lock");
HwLock ZYNQRegSCRS1Locker("/evertz_zynq_hwapi_scrs1_reg_lock");
HwLock ZYNQRegSCRS2Locker("/evertz_zynq_hwapi_scrs2_reg_lock");
HwLock ZYNQRegSCRS3Locker("/evertz_zynq_hwapi_scrs3_reg_lock");
HwLock ZYNQRegSCMS0Locker("/evertz_zynq_hwapi_scms0_reg_lock");
HwLock ZYNQRegSCMS1Locker("/evertz_zynq_hwapi_scms1_reg_lock");
HwLock ZYNQRegSCMS2Locker("/evertz_zynq_hwapi_scms2_reg_lock");
HwLock ZYNQRegSCMS3Locker("/evertz_zynq_hwapi_scms3_reg_lock");
HwLock ZYNQRegSCWP0Locker("/evertz_zynq_hwapi_scwp0_reg_lock");
HwLock ZYNQRegSCWP1Locker("/evertz_zynq_hwapi_scwp1_reg_lock");
HwLock ZYNQRegSCWP2Locker("/evertz_zynq_hwapi_scwp2_reg_lock");
HwLock ZYNQRegSCWP3Locker("/evertz_zynq_hwapi_scwp3_reg_lock");
HwLock ZYNQRegSCDWP0Locker("/evertz_zynq_hwapi_scdwp0_reg_lock");
HwLock ZYNQRegSCDWP1Locker("/evertz_zynq_hwapi_scdwp1_reg_lock");
HwLock ZYNQRegSCDWP2Locker("/evertz_zynq_hwapi_scdwp2_reg_lock");
HwLock ZYNQRegSCDWP3Locker("/evertz_zynq_hwapi_scdwp3_reg_lock");
HwLock ZYNQRegSCPL0Locker("/evertz_zynq_hwapi_scpl0_reg_lock");
HwLock ZYNQRegSCPL1Locker("/evertz_zynq_hwapi_scpl1_reg_lock");
HwLock ZYNQRegSCPL2Locker("/evertz_zynq_hwapi_scpl2_reg_lock");
HwLock ZYNQRegSCPL3Locker("/evertz_zynq_hwapi_scpl3_reg_lock");
HwLock ZYNQRegAxiMemLocker("/evertz_zynq_hwapi_aximem_reg_lock");
HwLock ZYNQRegMTestLocker("/evertz_zynq_hwapi_mtest_reg_lock");
HwLock ZYNQRegMTest1Locker("/evertz_zynq_hwapi_mtest1_reg_lock");
HwLock ZYNQRegIcronLocker("/evertz_zynq_hwapi_icron_reg_lock");
HwLock ZYNQRegTicoEncLocker("/evertz_zynq_hwapi_tico_enc_reg_lock");
HwLock ZYNQRegTicoDecLocker("/evertz_zynq_hwapi_tico_dec_reg_lock");
HwLock ZYNQRegPTPLocker("/evertz_zynq_hwapi_ptp_reg_lock");
HwLock ZYNQRegIPRxLocker("/evertz_zynq_hwapi_iprx_reg_lock");
HwLock ZYNQRegIPTxLocker("/evertz_zynq_hwapi_iptx_reg_lock");
HwLock ZYNQRegSDI12GLocker("/evertz_zynq_hwapi_sdi12g_reg_lock");
HwLock ZYNQRegGenlockLocker("/evertz_zynq_hwapi_genlock_reg_lock");

int
HW_API::lockXGERxReadWord(bool lock) {
    if (lock) {
        return ZYNQRegXgeRXReadWordLocker.lock();
    } else {
        return ZYNQRegXgeRXReadWordLocker.unlock();
    }
}

int
HW_API::lockXGETxReadWord(bool lock) {
    if (lock) {
        return ZYNQRegXgeTXReadWordLocker.lock();
    } else {
        return ZYNQRegXgeTXReadWordLocker.unlock();
    }
}

int
HW_API::lockXGERxWriteWord(bool lock) {
    if (lock) {
        return ZYNQRegXgeRXWriteWordLocker.lock();
    } else {
        return ZYNQRegXgeRXWriteWordLocker.unlock();
    }
}

int
HW_API::lockXGETxWriteWord(bool lock) {
    if (lock) {
        return ZYNQRegXgeTXWriteWordLocker.lock();
    } else {
        return ZYNQRegXgeTXWriteWordLocker.unlock();
    }
}

int
HW_API::lockXGEDRPChReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegXGEDRPCh0Locker.lock();
        } else {
            return ZYNQRegXGEDRPCh0Locker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegXGEDRPCh1Locker.lock();
        } else {
            return ZYNQRegXGEDRPCh1Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockXGEDRPCoReg(bool lock) {
    if (lock) {
        return ZYNQRegXGEDRPCoLocker.lock();
    } else {
        return ZYNQRegXGEDRPCoLocker.unlock();
    }
}

int
HW_API::lockHDMIReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegHDMI0Locker.lock();
        } else {
            return ZYNQRegHDMI0Locker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegHDMI1Locker.lock();
        } else {
            return ZYNQRegHDMI1Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockXGEMReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegXGEM0Locker.lock();
        } else {
            return ZYNQRegXGEM0Locker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegXGEM1Locker.lock();
        } else {
            return ZYNQRegXGEM1Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockXGEIfReg(bool lock) {
    if (lock) {
        return ZYNQRegXGEIFLocker.lock();
    } else {
        return ZYNQRegXGEIFLocker.unlock();
    }
}

int
HW_API::lockXGETxReg(bool lock) {
    if (lock) {
        return ZYNQRegXGETXLocker.lock();
    } else {
        return ZYNQRegXGETXLocker.unlock();
    }
}

int
HW_API::lockXGERxReg(bool lock) {
    if (lock) {
        return ZYNQRegXGERXLocker.lock();
    } else {
        return ZYNQRegXGERXLocker.unlock();
    }
}

int
HW_API::lockFPGAIDReg(bool lock) {
    if (lock) {
        return ZYNQRegFPGAIDLocker.lock();
    } else {
        return ZYNQRegFPGAIDLocker.unlock();
    }
}

int
HW_API::lockXBARReg(bool lock) {
    if (lock) {
        return ZYNQRegXBARLocker.lock();
    } else {
        return ZYNQRegXBARLocker.unlock();
    }
}

int
HW_API::lockScalerAReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegSCA0Locker.lock();
        } else {
            return ZYNQRegSCA0Locker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegSCA1Locker.lock();
        } else {
            return ZYNQRegSCA1Locker.unlock();
        }
    } else if (idx == 2) {
        if (lock) {
            return ZYNQRegSCA2Locker.lock();
        } else {
            return ZYNQRegSCA2Locker.unlock();
        }
    } else if (idx == 3) {
        if (lock) {
            return ZYNQRegSCA3Locker.lock();
        } else {
            return ZYNQRegSCA3Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockScalerBReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegSCB0Locker.lock();
        } else {
            return ZYNQRegSCB0Locker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegSCB1Locker.lock();
        } else {
            return ZYNQRegSCB1Locker.unlock();
        }
    } else if (idx == 2) {
        if (lock) {
            return ZYNQRegSCB2Locker.lock();
        } else {
            return ZYNQRegSCB2Locker.unlock();
        }
    } else if (idx == 3) {
        if (lock) {
            return ZYNQRegSCB3Locker.lock();
        } else {
            return ZYNQRegSCB3Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockScaleRasterReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegSCRS0Locker.lock();
        } else {
            return ZYNQRegSCRS0Locker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegSCRS1Locker.lock();
        } else {
            return ZYNQRegSCRS1Locker.unlock();
        }
    } else if (idx == 2) {
        if (lock) {
            return ZYNQRegSCRS2Locker.lock();
        } else {
            return ZYNQRegSCRS2Locker.unlock();
        }
    } else if (idx == 3) {
        if (lock) {
            return ZYNQRegSCRS3Locker.lock();
        } else {
            return ZYNQRegSCRS3Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockScaleMiscReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegSCMS0Locker.lock();
        } else {
            return ZYNQRegSCMS0Locker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegSCMS1Locker.lock();
        } else {
            return ZYNQRegSCMS1Locker.unlock();
        }
    } else if (idx == 2) {
        if (lock) {
            return ZYNQRegSCMS2Locker.lock();
        } else {
            return ZYNQRegSCMS2Locker.unlock();
        }
    } else if (idx == 3) {
        if (lock) {
            return ZYNQRegSCMS3Locker.lock();
        } else {
            return ZYNQRegSCMS3Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockScalerWritePortReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegSCWP0Locker.lock();
        } else {
            return ZYNQRegSCWP0Locker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegSCWP1Locker.lock();
        } else {
            return ZYNQRegSCWP1Locker.unlock();
        }
    } else if (idx == 2) {
        if (lock) {
            return ZYNQRegSCWP2Locker.lock();
        } else {
            return ZYNQRegSCWP2Locker.unlock();
        }
    } else if (idx == 3) {
        if (lock) {
            return ZYNQRegSCWP3Locker.lock();
        } else {
            return ZYNQRegSCWP3Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockScalerDecWritePortReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegSCDWP0Locker.lock();
        } else {
            return ZYNQRegSCDWP0Locker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegSCDWP1Locker.lock();
        } else {
            return ZYNQRegSCDWP1Locker.unlock();
        }
    } else if (idx == 2) {
        if (lock) {
            return ZYNQRegSCDWP2Locker.lock();
        } else {
            return ZYNQRegSCDWP2Locker.unlock();
        }
    } else if (idx == 3) {
        if (lock) {
            return ZYNQRegSCDWP3Locker.lock();
        } else {
            return ZYNQRegSCDWP3Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockScalerPlayoutReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegSCPL0Locker.lock();
        } else {
            return ZYNQRegSCPL0Locker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegSCPL1Locker.lock();
        } else {
            return ZYNQRegSCPL1Locker.unlock();
        }
    } else if (idx == 2) {
        if (lock) {
            return ZYNQRegSCPL2Locker.lock();
        } else {
            return ZYNQRegSCPL2Locker.unlock();
        }
    } else if (idx == 3) {
        if (lock) {
            return ZYNQRegSCPL3Locker.lock();
        } else {
            return ZYNQRegSCPL3Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockAxiMemoryDmaReg(bool lock) {
    if (lock) {
        return ZYNQRegAxiMemLocker.lock();
    } else {
        return ZYNQRegAxiMemLocker.unlock();
    }
}

int
HW_API::lockMemTestReg(uint32_t idx, bool lock) {
    if (idx == 0) {
        if (lock) {
            return ZYNQRegMTestLocker.lock();
        } else {
            return ZYNQRegMTestLocker.unlock();
        }
    } else if (idx == 1) {
        if (lock) {
            return ZYNQRegMTest1Locker.lock();
        } else {
            return ZYNQRegMTest1Locker.unlock();
        }
    } else {
        return -1;
    }
}

int
HW_API::lockIcronUSBReg(bool lock) {
    if (lock) {
        return ZYNQRegIcronLocker.lock();
    } else {
        return ZYNQRegIcronLocker.unlock();
    }
}

int
HW_API::lockTicoEncReg(bool lock) {
    if (lock) {
        return ZYNQRegTicoEncLocker.lock();
    } else {
        return ZYNQRegTicoEncLocker.unlock();
    }
}

int
HW_API::lockTicoDecReg(bool lock) {
    if (lock) {
        return ZYNQRegTicoDecLocker.lock();
    } else {
        return ZYNQRegTicoDecLocker.unlock();
    }
}

int
HW_API::lockPTPReg(bool lock) {
    if (lock) {
        return ZYNQRegPTPLocker.lock();
    } else {
        return ZYNQRegPTPLocker.unlock();
    }
}

int
HW_API::lockIPRxReg(bool lock) {
    if (lock) {
        return ZYNQRegIPRxLocker.lock();
    } else {
        return ZYNQRegIPRxLocker.unlock();
    }
}

int
HW_API::lockIPTxReg(bool lock) {
    if (lock) {
        return ZYNQRegIPTxLocker.lock();
    } else {
        return ZYNQRegIPTxLocker.unlock();
    }
}

int
HW_API::lockSDI12GReg(bool lock) {
    if (lock) {
        return ZYNQRegSDI12GLocker.lock();
    } else {
        return ZYNQRegSDI12GLocker.unlock();
    }
}

int
HW_API::lockGenlockReg(bool lock) {
    if (lock) {
        return ZYNQRegGenlockLocker.lock();
    } else {
        return ZYNQRegGenlockLocker.unlock();
    }
}

/* -- Sleep -- */
void
HW_API::hwSleep(uint64_t ns) {
    struct timespec tim;
    tim.tv_sec = ns / 1000000000;
    tim.tv_nsec = ns % 1000000000;
    nanosleep(&tim, NULL);
    return;
}

/* -- API/FPGA BIST -- */

void
HW_API::bistSleep() {
    printf("Sleeping for 1 second...");
    fflush(stdout);
    HW_API::hwSleep((uint64_t)1000000000);
    printf("Done.\n");
    printf("Sleeping for 5 seconds...");
    fflush(stdout);
    HW_API::hwSleep((uint64_t)5000000000);
    printf("Done.\n");
    return;
}

void
HW_API::bistMutex() {
    int stat = 0;
    printf("Toggling mutexes...");
    fflush(stdout);
    if (HW_API::lockXGERxReadWord(true)){
        printf("\nXGERxReadWord Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGERxReadWord(false);
    if (HW_API::lockXGETxReadWord(true)){
        printf("\nXGETxReadWord Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGETxReadWord(false);
    if (HW_API::lockXGERxWriteWord(true)){
        printf("\nXGERxWriteWord Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGERxWriteWord(false);
    if (HW_API::lockXGETxWriteWord(true)){
        printf("\nXGETxWriteWord Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGETxWriteWord(false);
    if (HW_API::lockXGEDRPChReg(0, true)){
        printf("\nXGEDRPChReg 0 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGEDRPChReg(0, false);
    if (HW_API::lockXGEDRPChReg(1, true)){
        printf("\nXGEDRPChReg 1 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGEDRPChReg(1, false);
    if (HW_API::lockXGEDRPCoReg(true)){
        printf("\nXGEDRPCoReg Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGEDRPCoReg(false);
    if (HW_API::lockHDMIReg(0,true)){
        printf("\nHDMIReg0 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockHDMIReg(0,false);
    if (HW_API::lockHDMIReg(1,true)){
        printf("\nHDMIReg1 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockHDMIReg(1,false);
    if (HW_API::lockXGEMReg(0,true)){
        printf("\nXGEMReg0 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGEMReg(0,false);
    if (HW_API::lockXGEMReg(1,true)){
        printf("\nXGEMReg1 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGEMReg(1,false);
    if (HW_API::lockXGEIfReg(true)){
        printf("\nXGEIfReg Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGEIfReg(false);
    if (HW_API::lockXGETxReg(true)){
        printf("\nXGETxReg Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGETxReg(false);
    if (HW_API::lockXGERxReg(true)){
        printf("\nXGERxReg Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockXGERxReg(false);
    if (HW_API::lockScalerAReg(0,true)){
        printf("\nScaler A 0 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScalerAReg(0,false);
    if (HW_API::lockScalerAReg(1,true)){
        printf("\nScaler A 1 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScalerAReg(1,false);
    if (HW_API::lockScalerBReg(0,true)){
        printf("\nScaler B 0 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScalerBReg(0,false);
    if (HW_API::lockScalerBReg(1,true)){
        printf("\nScaler B 1 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScalerBReg(1,false);
    if (HW_API::lockScaleRasterReg(0,true)){
        printf("\nScaler Raster 0 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScaleRasterReg(0,false);
    if (HW_API::lockScaleRasterReg(1,true)){
        printf("\nScaler Raster 1 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScaleRasterReg(1,false);
    if (HW_API::lockScaleMiscReg(0,true)){
        printf("\nScaler Misc 0 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScaleMiscReg(0,false);
    if (HW_API::lockScaleMiscReg(1,true)){
        printf("\nScaler Misc 1 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScaleMiscReg(1,false);
    if (HW_API::lockScalerWritePortReg(0,true)){
        printf("\nScaler Misc 0 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScalerWritePortReg(0,false);
    if (HW_API::lockScalerWritePortReg(1,true)){
        printf("\nScaler Misc 1 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScalerWritePortReg(1,false);
    if (HW_API::lockScalerPlayoutReg(0,true)){
        printf("\nScaler Misc 0 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScalerPlayoutReg(0,false);
    if (HW_API::lockScalerPlayoutReg(1,true)){
        printf("\nScaler Misc 1 Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockScalerPlayoutReg(1,false);
    if (HW_API::lockMemTestReg(0,true)){
        printf("\nMemory Test Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockMemTestReg(0,false);
    if (HW_API::lockIcronUSBReg(true)){
        printf("\nIcron USB Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockIcronUSBReg(false);
    if (HW_API::lockTicoEncReg(true)){
        printf("\nTico Enc Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockTicoEncReg(false);
    if (HW_API::lockTicoDecReg(true)){
        printf("\nTico Dec Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockTicoDecReg(false);
    if (HW_API::lockPTPReg(true)){
        printf("\nPTP Mutex is stuck!");
        stat = -1;
    }
    HW_API::lockPTPReg(false);

    if (stat) {
        printf("\nDone.\n");
    } else {
        printf("Done.\n");
    }
    return;
}

void
HW_API::bistReg() {
    uint32_t data32 = 0;
    uint64_t data64 = 0;
    printf("Polling Registers:\n");

    printf("  Reading XGE DRP 0 Reg...");
    fflush(stdout);
    data32 ^= readXGEDRPReg(0, 0x15c); //RX_PRBS_ERR_CNT
    printf("Done.\n");
    printf("  Writing XGE DRP 0 Reg...");
    fflush(stdout);
    writeXGEDRPReg(0, 0x15c, 0); //RX_PRBS_ERR_CNT
    printf("Done.\n");
    printf("  Reading XGE DRP 1 Reg...");
    fflush(stdout);
    data32 ^= readXGEDRPReg(1, 0x15c); //RX_PRBS_ERR_CNT
    printf("Done.\n");
    printf("  Writing XGE DRP 1 Reg...");
    fflush(stdout);
    writeXGEDRPReg(1, 0x15c, 0); //RX_PRBS_ERR_CNT
    printf("Done.\n");

    printf("  Reading DRPNL Reg...");
    fflush(stdout);
    data32 ^= readDRPNLReg(0x30); //QPLL_INIT_CFG
    printf("Done.\n");

    printf("  Reading HDMI IP 0 Reg...");
    fflush(stdout);
    data32 ^= readHDMIIPReg(0, 0x0); //Version Register
    printf("Done.\n");
    printf("  Writing HDMI IP 0 Reg...");
    fflush(stdout);
    writeHDMIIPReg(0, 0x0, 0); //Version Register
    printf("Done.\n");
    printf("  Reading HDMI IP 1 Reg...");
    fflush(stdout);
    data32 ^= readHDMIIPReg(0, 0x0); //Version Register
    printf("Done.\n");
    printf("  Writing HDMI IP 1 Reg...");
    fflush(stdout);
    writeHDMIIPReg(0, 0x0, 0); //Version Register
    printf("Done.\n");

    printf("  Reading XGE MAC 0 Reg...");
    fflush(stdout);
    data32 ^= readXGEMacReg(0, 0x400); //Pause Frame MAC address
    printf("Done.\n");
    printf("  Writing XGE MAC 0 Reg...");
    fflush(stdout);
    writeXGEMacReg(0, 0x400, 0); //Pause Frame MAC address
    printf("Done.\n");
    printf("  Reading XGE MAC 1 Reg...");
    fflush(stdout);
    data32 ^= readXGEMacReg(1, 0x400); //Pause Frame MAC address
    printf("Done.\n");
    printf("  Writing XGE MAC 1 Reg...");
    fflush(stdout);
    writeXGEMacReg(1, 0x400, 0); //Pause Frame MAC address
    printf("Done.\n");

    printf("  Reading XGE If Reg...");
    fflush(stdout);
    data32 ^= readXGEIfReg(0x0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing XGE If Reg...");
    fflush(stdout);
    writeXGEIfReg(0x0, 0); //REG_ZEROES
    printf("Done.\n");

    printf("  Reading XGE Tx Reg...");
    fflush(stdout);
    data64 ^= readXGETxReg(0x0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing XGE Tx Reg...");
    fflush(stdout);
    writeXGETxReg(0x0, 0); //REG_ZEROES
    printf("Done.\n");

    printf("  Reading XGE Rx Reg...");
    fflush(stdout);
    data64 ^= readXGERxReg(0x0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing XGE Rx Reg...");
    fflush(stdout);
    writeXGERxReg(0x0, 0); //REG_ZEROES
    printf("Done.\n");

    printf("  Reading FPGA ID Reg...");
    fflush(stdout);
    data32 ^= readFPGAIDReg(0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing FPGA ID Reg...");
    fflush(stdout);
    writeFPGAIDReg(0, 0); //REG_ZEROES
    printf("Done.\n");

    printf("  Reading Scaler A 0 Reg...");
    fflush(stdout);
    data32 ^= readScalerAReg(0,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scaler A 0 Reg...");
    fflush(stdout);
    writeScalerAReg(0, 30, 0); //REG_SC_VRST
    printf("Done.\n");
    printf("  Reading Scaler A 1 Reg...");
    fflush(stdout);
    data32 ^= readScalerAReg(1,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scaler A 1 Reg...");
    fflush(stdout);
    writeScalerAReg(1, 30, 0); //REG_SC_VRST
    printf("Done.\n");
    printf("  Reading Scaler B 0 Reg...");
    fflush(stdout);
    data32 ^= readScalerBReg(0,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scaler B 0 Reg...");
    fflush(stdout);
    writeScalerBReg(0, 30, 0); //REG_SC_VRST
    printf("Done.\n");
    printf("  Reading Scaler B 1 Reg...");
    fflush(stdout);
    data32 ^= readScalerBReg(1,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scaler B 1 Reg...");
    fflush(stdout);
    writeScalerBReg(1, 30, 0); //REG_SC_VRST
    printf("Done.\n");
    printf("  Reading Scale Raster 0 Reg...");
    fflush(stdout);
    data32 ^= readScaleRasterReg(0,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scale Raster 0 Reg...");
    fflush(stdout);
    writeScaleRasterReg(0, 0, 0); //REG_ZEROES
    printf("Done.\n");
    printf("  Reading Scale Raster 1 Reg...");
    fflush(stdout);
    data32 ^= readScaleRasterReg(1,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scale Raster 1 Reg...");
    fflush(stdout);
    writeScaleRasterReg(1, 0, 0); //REG_ZEROES
    printf("Done.\n");
    printf("  Reading Scale Misc 0 Reg...");
    fflush(stdout);
    data32 ^= readScaleMiscReg(0,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scale Misc 0 Reg...");
    fflush(stdout);
    writeScaleMiscReg(0, 0, 0); //REG_ZEROES
    printf("Done.\n");
    printf("  Reading Scale Misc 1 Reg...");
    fflush(stdout);
    data32 ^= readScaleMiscReg(1,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scale Misc 1 Reg...");
    fflush(stdout);
    writeScaleMiscReg(1, 0, 0); //REG_ZEROES
    printf("Done.\n");
    printf("  Reading Scaler Write Port 0 Reg...");
    fflush(stdout);
    data32 ^= readScalerWritePortReg(0,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scaler Write Port 0 Reg...");
    fflush(stdout);
    writeScalerWritePortReg(0, 0, 0); //REG_ZEROES
    printf("Done.\n");
    printf("  Reading Scaler Write Port 1 Reg...");
    fflush(stdout);
    data32 ^= readScalerWritePortReg(1,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scaler Write Port 1 Reg...");
    fflush(stdout);
    writeScalerWritePortReg(1, 0, 0); //REG_ZEROES
    printf("Done.\n");
    printf("  Reading Scaler Playout 0 Reg...");
    fflush(stdout);
    data32 ^= readScalerPlayoutReg(0,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scaler Playout 0 Reg...");
    fflush(stdout);
    writeScalerPlayoutReg(0, 0, 0); //REG_ZEROES
    printf("Done.\n");
    printf("  Reading Scaler Playout 1 Reg...");
    fflush(stdout);
    data32 ^= readScalerPlayoutReg(1,0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Scaler Playout 1 Reg...");
    fflush(stdout);
    writeScalerPlayoutReg(1, 0, 0); //REG_ZEROES
    printf("Done.\n");

    printf("  Reading Memory Test Reg...");
    fflush(stdout);
    if (HW_API::getFPGACapability("INC_DDR3A")>0 && HW_API::getFPGACapability("INC_DDR3B")>0) {
      data32 ^= readMemTestReg(0, 0); //REG_ZEROES
      printf("Done.\n");
      printf("  Writing Memory Test Reg...");
      fflush(stdout);
      writeMemTestReg(0, 0, 0); //REG_ZEROES
      printf("Done.\n");
    } else {
      printf("Peripheral missing.\n");
    }

    printf("  Reading Icron USB Reg...");
    fflush(stdout);
    data32 ^= readIcronUSBReg(0); //REG_ZEROES
    printf("Done.\n");
    printf("  Writing Icron USB Reg...");
    fflush(stdout);
    writeIcronUSBReg(0, 0); //REG_ZEROES
    printf("Done.\n");

    printf("Done.  Read checks = %08x, %08x%08x\n", data32, (uint32_t)data64, (uint32_t)(data64>>32));
    return;
}

void
HW_API::bistMem(uint32_t bank, uint32_t depth_div_exp, bool quick) {
    if (bank == 0)
    {
      printf("Running %s HP Memory Test Suite:\n",quick?"Fast":"Slow");
      printf("  Initializing HP Memory... \n");
    } else
    {
      printf("Running %s HR Memory Test Suite:\n",quick?"Fast":"Slow");
      printf("  Initializing HR Memory... \n");

    }
    HW_API::initMemoryTest(bank);
    assert(HW_API::getMemoryTestInitDone(bank));
    printf("Done.\n");

    printf("  Checking Memory Calibration...\n");
    assert(HW_API::getMemoryCalibrated(bank));
    printf("Done.\n");

    uint32_t num_scaler_and_fb = HW_API::getFPGACapability("N_SCALER") + HW_API::getFPGACapability("N_FRAME_BUFFER");
    if ((num_scaler_and_fb > 0) && (bank == 0))
    {
      printf("  Disabling Scalers and Frame Buffers.\n");
      for (uint32_t i = 0; i < num_scaler_and_fb; i++)
      {
        if (!HW_API::getScalerPathInitDone(i)){
          HW_API::initScalerPath(i);
        }
        HW_API::disableScalerReadPort(i, true);
        HW_API::disableScalerWritePort(i, true);
      }
    }
    if (quick) {
        runMemoryTest(bank, depth_div_exp, HW_API::MEM_TEST_TYPE_RANDOM_ONCE);
        runMemoryTest(bank, depth_div_exp, HW_API::MEM_TEST_TYPE_BIT_WALK_ONCE);
    } else {
        runMemoryTest(bank, depth_div_exp, HW_API::MEM_TEST_TYPE_RANDOM);
        runMemoryTest(bank, depth_div_exp, HW_API::MEM_TEST_TYPE_BIT_WALK);
        runMemoryTest(bank, depth_div_exp, HW_API::MEM_TEST_TYPE_ADDR_EQ_DATA);
    }
    if ((num_scaler_and_fb > 0) && (bank == 0))
    {
      printf("  Re-Enabling Scalers and Frame Buffers.\n");
      for (uint32_t i = 0; i < num_scaler_and_fb; i++)
      {
        HW_API::disableScalerReadPort(i, false);
        HW_API::disableScalerWritePort(i, false);
      }
    }
    printf("Done.\n");
}

void
HW_API::bistMemAddrStress(uint32_t bank, uint32_t iterations, bool quick) {
    if (bank == 0)
    {
      printf("Running %s HP Memory Test Suite:\n",quick?"Fast":"Slow");
      printf("  Initializing HP Memory... \n");
    } else
    {
      printf("Running %s HR Memory Test Suite:\n",quick?"Fast":"Slow");
      printf("  Initializing HR Memory... \n");

    }
    HW_API::initMemoryTest(bank);
    assert(HW_API::getMemoryTestInitDone(bank));
    printf("Done.\n");

    printf("  Checking Memory Calibration...\n");
    assert(HW_API::getMemoryCalibrated(bank));
    printf("Done.\n");

    uint32_t num_scaler_and_fb = HW_API::getFPGACapability("N_SCALER") + HW_API::getFPGACapability("N_FRAME_BUFFER");
    if ((num_scaler_and_fb > 0) && (bank == 0))
    {
      printf("  Disabling Scalers and Frame Buffers.\n");
      for (uint32_t i = 0; i < num_scaler_and_fb; i++)
      {
        if (!HW_API::getScalerPathInitDone(i)){
          HW_API::initScalerPath(i);
        }
        HW_API::disableScalerReadPort(i, true);
        HW_API::disableScalerWritePort(i, true);
      }
    }

    if (quick) {
      runMemoryAddressStressTest(bank, iterations, HW_API::MEM_TEST_TYPE_ADDR_STRESS_ONCE);
    } else {
      runMemoryAddressStressTest(bank, iterations, HW_API::MEM_TEST_TYPE_ADDR_STRESS);
    }

    if ((num_scaler_and_fb > 0) && (bank == 0))
    {
      printf("  Re-Enabling Scalers and Frame Buffers.\n");
      for (uint32_t i = 0; i < num_scaler_and_fb; i++)
      {
        HW_API::disableScalerReadPort(i, false);
        HW_API::disableScalerWritePort(i, false);
      }
    }
    printf("Done.\n");
}

void
HW_API::bistMemAddressHammer(uint32_t bank, uint32_t iterations) {
    printf("Preparing memory hammer...\n");
    if (bank == 0)
    {
      printf("  Initializing HP Memory... \n");
    } else
    {
      printf("  Initializing HR Memory... \n");

    }
    HW_API::initMemoryTest(bank);
    assert(HW_API::getMemoryTestInitDone(bank));
    printf("Done.\n");

    printf("  Checking Memory Calibration...\n");
    assert(HW_API::getMemoryCalibrated(bank));
    printf("Done.\n");

    uint32_t num_scaler_and_fb = HW_API::getFPGACapability("N_SCALER") + HW_API::getFPGACapability("N_FRAME_BUFFER");
    if ((num_scaler_and_fb > 0) && (bank == 0))
    {
      printf("  Disabling Scalers and Frame Buffers.\n");
      for (uint32_t i = 0; i < num_scaler_and_fb; i++)
      {
        if (!HW_API::getScalerPathInitDone(i)){
          HW_API::initScalerPath(i);
        }
        HW_API::disableScalerReadPort(i, true);
        HW_API::disableScalerWritePort(i, true);
      }
    }

    runMemoryAddressHammer(bank, iterations, HW_API::MEM_TEST_TYPE_ADDR_HAMMER);

    if ((num_scaler_and_fb > 0) && (bank == 0))
    {
      printf("  Re-Enabling Scalers and Frame Buffers.\n");
      for (uint32_t i = 0; i < num_scaler_and_fb; i++)
      {
        HW_API::disableScalerReadPort(i, false);
        HW_API::disableScalerWritePort(i, false);
      }
    }
    printf("Done.\n");
}

void
HW_API::bist10GEMac() {
    for (uint32_t i = 0; i < N_TOTAL_10GE_CHANNELS; i++) {
        if (i >= N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
        {
          printf("Skipping index %u because INC_TEST_XGE feature is not enabled!\n", i);
          continue;
        }
        printf("Getting 10GE Mac %u Status:\n",i);
        // Init
        printf("  Initializing 10GE Mac... ");
        HW_API::init10GEMac(i);
        assert(HW_API::get10GEMacInitDone(i));
        printf("Done.\n");

        printf("  Mac Rx Enable = %u\n", get10GEMacRxEnable(i));
        printf("  Mac Tx Enable = %u\n", get10GEMacTxEnable(i));
        if (!get10GEMacMDIOEnable(i)) {
            printf("  MDIO not enabled! Initializing...");
            fflush(stdout);
            set10GEMacMDIOEnable(i,true);
            printf("Done.\n");
        }
        printf("  10GE Rx Signal Detect = %u\n", get10GERxSignalDetect(i));
        printf("  10GE Rx Link Up = %u\n", get10GELinkUp(i));
        printf("  10GE Rx Local Fault = %u\n", get10GELocalFault(i));
        printf("  10GE Rx Transmit Fault = %u\n", get10GETransmitFault(i));
        printf("  10GE Rx Receive Fault = %u\n", get10GEReceiveFault(i));
        printf("Done.\n");
    }
    return;
}

void
HW_API::bist10GEMacLinkUp() {
    for (uint32_t i = 0; i < N_TOTAL_10GE_CHANNELS; i++) {
        if (i >= N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
        {
          printf("Skipping index %u because INC_TEST_XGE feature is not enabled!\n", i);
          continue;
        }
        printf("Getting 10GE Mac %u Status:\n",i);
        // Init
        printf("  Initializing 10GE Mac... ");
        HW_API::init10GEMac(i);
        assert(HW_API::get10GEMacInitDone(i));
        printf("Done.\n");

        if (!HW_API::get10GEMacMDIOEnable(i)) {
            printf("  MDIO not enabled! Initializing...");
            fflush(stdout);
            HW_API::set10GEMacMDIOEnable(i,true);
            printf("Done.\n");
        }
        HW_API::get10GELinkUp(i);
    }
    printf("Done.\n");
    printf("Getting 10GE Mac Link Status:\n");
    for (uint32_t i = 0; i < N_TOTAL_10GE_CHANNELS; i++) {
        if (i >= N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
        {
          continue;
        }
        printf("  10GE Mac %u Rx Link Up = %u\n", i, HW_API::get10GELinkUp(i));
    }
    printf("Done.\n");
    return;
}

void
HW_API::bistTEMAC() {
    for (uint32_t i = 0; i < N_TOTAL_10GE_CHANNELS; i++) {
        if (i >= N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
        {
          printf("Skipping index %u because INC_TEST_XGE feature is not enabled!\n", i);
          continue;
        }
        printf("Getting TEMAC %u Status:\n",i);
        // Init
        printf("  Initializing TEMAC... ");
        HW_API::initTEMAC(i);
        assert(HW_API::getTEMACInitDone(i));
        printf("Done.\n");

        printf("  Mac Rx Enable = %u\n", getTEMACRxEnable(i));
        printf("  Mac Tx Enable = %u\n", getTEMACTxEnable(i));
        if (!getTEMACMDIOEnable(i)) {
            printf("  MDIO not enabled! Initializing...");
            fflush(stdout);
            setTEMACMDIOEnable(i,true);
        }
        // Take PHY out of isolation. This is bit 10 in register 0
        printf("  TEMAC Rx Link Up = %u\n", get1GLinkUp(i));
        printf("  TEMAC Rx Remote Fault = %u\n", get1GRemoteFault(i));
        printf("Done.\n");
    }
    return;
}

void
HW_API::bist10GETx(uint32_t sfp_a, uint32_t sfp_b, bool srtp, uint32_t vstd, bool aspen422, bool aspen444, bool tico, bool smpte2110, bool audio, HW_API::XTxColourSpecification colour_spec_inp, HW_API::XTxSampleStructure colour_struct_inp, bool meta, HW_API::XTxElectroopticalTransferFunction eotf, HW_API::XTxColourSpace colour_space, bool usb) {
    if (sfp_a >= HW_API::N_XGE_RX)
    {
      printf("sfp_a out of range!\n");
      return;
    }
    if (sfp_b >= HW_API::N_XGE_RX)
    {
      printf("sfp_b out of range!\n");
      return;
    }
    // In hardware, we have 1 instance of av_to_ip, with N_VID=4, N_VIDE_PER_IP_UNIT=6,
    // N_XGE=2, and REDUNDANCY=true. Both ASPEN422 and ASPEN444 paths are enabled.
    // The first 2 video paths are ASPEN422 paths, next 2 are ASPEN444 and the final 2 are
    // TICO. This function configures all four ASPEN paths and both TICO paths for a given SFP.
    // With respect to audio, we have 3 audio groups per SFP. This function configures audio
    // paths 0, 1, and 2 for SFP0, and audio paths 3, 4, and 5 for SFP1.
    uint32_t aspen_path_offset = 0;
    uint32_t tico_path_offset = HW_API::getFPGACapability("INC_ASPEN444_TX") <= 0 ? 2 : 4; // 4 ASPEN paths per SFP
    uint32_t smpte2110_path_offset = tico_path_offset + 2; // 4 ASPEN + 2 TICO paths per SFP
    if (aspen422 && aspen444)
    {
      printf("aspen422 and aspen444 options are mutually exclusive!\n");
      return;
    }
    printf("Initializing 10GE %u,%u Tx path(s) with known good defaults:\n", sfp_a, sfp_b);
    // Init
    printf("  Initializing controller...");
    fflush(stdout);
    HW_API::initAVtoIP();
    assert(HW_API::getAVtoIPInitDone());
    HW_API::initIPTx(7);
    assert(HW_API::getIPTxInitDone());
    printf("Done.\n");
    // PID
    printf("  Setting PIDs to 361 (ASPEN), 362 (Tico), and 200 (audio)...");
    fflush(stdout);
    HW_API::setVideoTxPID(361);
    HW_API::setVideoTxPID_Tico(362);
    HW_API::setAudioTxPID(200);
    printf("Done.\n");
    // Standard
    HW_API::XTxVidStandard std;
    switch (vstd) {
      case  0 : // 1080P60
        printf("  Setting Video Standard to 1080P60...\n");
        fflush(stdout);
        std.interlaced = false;
        std.bw = (HW_API::Vid_HD);
        std.hs_pol_high = true;
        std.vs_pol_high = true;
        std.cmp_size = 10;
        std.sptl = 2200;
        std.spal = 1920;
        std.tlpf0 = 1125;
        std.tlpf1 = 0;
        std.alpf0 = 1080;
        std.alpf1 = 0;
        std.soha  = 280;
        std.sova0 = 41;
        std.sova1 = 0xffff;
        std.sova_ext0 = 41;
        std.sova_ext1 = 0xffff;
        std.frame_rate_num = 60;
        std.frame_rate_den = 1;
        std.hs_start = 88;
        std.hs_stop = 132;
        std.vs_start0 = 0;
        std.vs_start1 = 0xffff;
        std.vs_stop0 = 5;
        std.vs_stop1 = 0xffff;
        std.vs_hpos0 = 88;
        std.vs_hpos1 = 0xffff;
        std.copyright = false;
        std.hpos_flag = true;
        std.clr_spec_inp = colour_spec_inp;
        std.smp_struct_inp = colour_struct_inp;
        break;
      case  1 : // 1080I60
        printf("  Setting Video Standard to 1080I60...\n");
        fflush(stdout);
        std.interlaced = true;
        std.bw = (HW_API::Vid_HD);
        std.hs_pol_high = true;
        std.vs_pol_high = true;
        std.cmp_size = 10;
        std.sptl = 2200;
        std.spal = 1920;
        std.tlpf0 = 1125;
        std.tlpf1 = 0;
        std.alpf0 = 1080;
        std.alpf1 = 0;
        std.soha  = 280;
        std.sova0 = 41;
        std.sova1 = 0xffff;
        std.sova_ext0 = 41;
        std.sova_ext1 = 0xffff;
        std.frame_rate_num = 60;
        std.frame_rate_den = 1;
        std.hs_start = 88;
        std.hs_stop = 132;
        std.vs_start0 = 0;
        std.vs_start1 = 0xffff;
        std.vs_stop0 = 5;
        std.vs_stop1 = 0xffff;
        std.vs_hpos0 = 88;
        std.vs_hpos1 = 0xffff;
        std.copyright = false;
        std.hpos_flag = true;
        std.clr_spec_inp = colour_spec_inp;
        std.smp_struct_inp = colour_struct_inp;
        break;
      case  2 : // 2160P30
        printf("  Setting Video Standard to 4K30...\n");
        fflush(stdout);
        std.interlaced = false;
        std.bw = (HW_API::Vid_3G);
        std.hs_pol_high = true;
        std.vs_pol_high = true;
        std.cmp_size = 10;
        std.sptl = 4400;
        std.spal = 3840;
        std.tlpf0 = 2250;
        std.tlpf1 = 0;
        std.alpf0 = 2160;
        std.alpf1 = 0;
        std.soha  = 560;
        std.sova0 = 41;
        std.sova1 = 0xffff;
        std.sova_ext0 = 41;
        std.sova_ext1 = 0xffff;
        std.frame_rate_num = 30;
        std.frame_rate_den = 1;
        std.hs_start = 176;
        std.hs_stop = 264;
        std.vs_start0 = 0;
        std.vs_start1 = 0xffff;
        std.vs_stop0 = 10;
        std.vs_stop1 = 0xffff;
        std.vs_hpos0 = 176;
        std.vs_hpos1 = 0xffff;
        std.copyright = false;
        std.hpos_flag = true;
        std.clr_spec_inp = colour_spec_inp;
        std.smp_struct_inp = colour_struct_inp;
        break;
      case  3 : // 2160P60
        printf("  Setting Video Standard to 4K60...\n");
        fflush(stdout);
        std.interlaced = false;
        std.bw = (HW_API::Vid_3G);
        std.hs_pol_high = true;
        std.vs_pol_high = true;
        std.cmp_size = 10;
        std.sptl = 4400;
        std.spal = 3840;
        std.tlpf0 = 2250;
        std.tlpf1 = 0;
        std.alpf0 = 2160;
        std.alpf1 = 0;
        std.soha  = 560;
        std.sova0 = 41;
        std.sova1 = 0xffff;
        std.sova_ext0 = 41;
        std.sova_ext1 = 0xffff;
        std.frame_rate_num = 60;
        std.frame_rate_den = 1;
        std.hs_start = 176;
        std.hs_stop = 264;
        std.vs_start0 = 0;
        std.vs_start1 = 0xffff;
        std.vs_stop0 = 10;
        std.vs_stop1 = 0xffff;
        std.vs_hpos0 = 176;
        std.vs_hpos1 = 0xffff;
        std.copyright = false;
        std.hpos_flag = true;
        std.clr_spec_inp = colour_spec_inp;
        std.smp_struct_inp = colour_struct_inp;
        break;
      case  4 : // 1080P30
        printf("  Setting Video Standard to 1080P30...\n");
        fflush(stdout);
        std.interlaced = false;
        std.bw = (HW_API::Vid_HD);
        std.hs_pol_high = true;
        std.vs_pol_high = true;
        std.cmp_size = 10;
        std.sptl = 2200;
        std.spal = 1920;
        std.tlpf0 = 1125;
        std.tlpf1 = 0;
        std.alpf0 = 1080;
        std.alpf1 = 0;
        std.soha  = 280;
        std.sova0 = 41;
        std.sova1 = 0xffff;
        std.sova_ext0 = 41;
        std.sova_ext1 = 0xffff;
        std.frame_rate_num = 30;
        std.frame_rate_den = 1;
        std.hs_start = 88;
        std.hs_stop = 132;
        std.vs_start0 = 0;
        std.vs_start1 = 0xffff;
        std.vs_stop0 = 5;
        std.vs_stop1 = 0xffff;
        std.vs_hpos0 = 88;
        std.vs_hpos1 = 0xffff;
        std.copyright = false;
        std.hpos_flag = true;
        std.clr_spec_inp = colour_spec_inp;
        std.smp_struct_inp = colour_struct_inp;
        break;
      case  5 : // 2160P24
        printf("  Setting Video Standard to 4K24...\n");
        fflush(stdout);
        std.interlaced = false;
        std.bw = (HW_API::Vid_3G);
        std.hs_pol_high = true;
        std.vs_pol_high = true;
        std.cmp_size = 10;
        std.sptl = 5500;
        std.spal = 3840;
        std.tlpf0 = 2250;
        std.tlpf1 = 0;
        std.alpf0 = 2160;
        std.alpf1 = 0;
        std.soha  = 1660;
        std.sova0 = 41;
        std.sova1 = 0xffff;
        std.sova_ext0 = 41;
        std.sova_ext1 = 0xffff;
        std.frame_rate_num = 24;
        std.frame_rate_den = 1;
        std.hs_start = 176;
        std.hs_stop = 264;
        std.vs_start0 = 0;
        std.vs_start1 = 0xffff;
        std.vs_stop0 = 10;
        std.vs_stop1 = 0xffff;
        std.vs_hpos0 = 176;
        std.vs_hpos1 = 0xffff;
        std.copyright = false;
        std.hpos_flag = true;
        std.clr_spec_inp = colour_spec_inp;
        std.smp_struct_inp = colour_struct_inp;
        break;
      case  6 : // 2160P23_98
        printf("  Setting Video Standard to 4K23.98...\n");
        fflush(stdout);
        std.interlaced = false;
        std.bw = (HW_API::Vid_3G);
        std.hs_pol_high = true;
        std.vs_pol_high = true;
        std.cmp_size = 10;
        std.sptl = 5500;
        std.spal = 3840;
        std.tlpf0 = 2250;
        std.tlpf1 = 0;
        std.alpf0 = 2160;
        std.alpf1 = 0;
        std.soha  = 1660;
        std.sova0 = 41;
        std.sova1 = 0xffff;
        std.sova_ext0 = 41;
        std.sova_ext1 = 0xffff;
        std.frame_rate_num = 24000;
        std.frame_rate_den = 1001;
        std.hs_start = 176;
        std.hs_stop = 264;
        std.vs_start0 = 0;
        std.vs_start1 = 0xffff;
        std.vs_stop0 = 10;
        std.vs_stop1 = 0xffff;
        std.vs_hpos0 = 176;
        std.vs_hpos1 = 0xffff;
        std.copyright = false;
        std.hpos_flag = true;
        std.clr_spec_inp = colour_spec_inp;
        std.smp_struct_inp = colour_struct_inp;
        break;
      case  7 : // 2160P59_94
        printf("  Setting Video Standard to 4K59.94...\n");
        fflush(stdout);
        std.interlaced = false;
        std.bw = (HW_API::Vid_3G);
        std.hs_pol_high = true;
        std.vs_pol_high = true;
        std.cmp_size = 10;
        std.sptl = 4400;
        std.spal = 3840;
        std.tlpf0 = 2250;
        std.tlpf1 = 0;
        std.alpf0 = 2160;
        std.alpf1 = 0;
        std.soha  = 560;
        std.sova0 = 41;
        std.sova1 = 0xffff;
        std.sova_ext0 = 41;
        std.sova_ext1 = 0xffff;
        std.frame_rate_num = 60000;
        std.frame_rate_den = 1001;
        std.hs_start = 176;
        std.hs_stop = 264;
        std.vs_start0 = 0;
        std.vs_start1 = 0xffff;
        std.vs_stop0 = 10;
        std.vs_stop1 = 0xffff;
        std.vs_hpos0 = 176;
        std.vs_hpos1 = 0xffff;
        std.copyright = false;
        std.hpos_flag = true;
        std.clr_spec_inp = colour_spec_inp;
        std.smp_struct_inp = colour_struct_inp;
        break;
      case  8 : // 2160P29_98
        printf("  Setting Video Standard to 4K29.98...\n");
        fflush(stdout);
        std.interlaced = false;
        std.bw = (HW_API::Vid_3G);
        std.hs_pol_high = true;
        std.vs_pol_high = true;
        std.cmp_size = 10;
        std.sptl = 4400;
        std.spal = 3840;
        std.tlpf0 = 2250;
        std.tlpf1 = 0;
        std.alpf0 = 2160;
        std.alpf1 = 0;
        std.soha  = 560;
        std.sova0 = 41;
        std.sova1 = 0xffff;
        std.sova_ext0 = 41;
        std.sova_ext1 = 0xffff;
        std.frame_rate_num = 30000;
        std.frame_rate_den = 1001;
        std.hs_start = 176;
        std.hs_stop = 264;
        std.vs_start0 = 0;
        std.vs_start1 = 0xffff;
        std.vs_stop0 = 10;
        std.vs_stop1 = 0xffff;
        std.vs_hpos0 = 176;
        std.vs_hpos1 = 0xffff;
        std.copyright = false;
        std.hpos_flag = true;
        std.clr_spec_inp = colour_spec_inp;
        std.smp_struct_inp = colour_struct_inp;
        break;
      case  9 : // 1080P59_94
        printf("  Setting Video Standard to 1080P59.94...\n");
        fflush(stdout);
        std.interlaced = false;
        std.bw = (HW_API::Vid_HD);
        std.hs_pol_high = true;
        std.vs_pol_high = true;
        std.cmp_size = 10;
        std.sptl = 2200;
        std.spal = 1920;
        std.tlpf0 = 1125;
        std.tlpf1 = 0;
        std.alpf0 = 1080;
        std.alpf1 = 0;
        std.soha  = 280;
        std.sova0 = 41;
        std.sova1 = 0xffff;
        std.sova_ext0 = 41;
        std.sova_ext1 = 0xffff;
        std.frame_rate_num = 60000;
        std.frame_rate_den = 1001;
        std.hs_start = 88;
        std.hs_stop = 132;
        std.vs_start0 = 0;
        std.vs_start1 = 0xffff;
        std.vs_stop0 = 5;
        std.vs_stop1 = 0xffff;
        std.vs_hpos0 = 88;
        std.vs_hpos1 = 0xffff;
        std.copyright = false;
        std.hpos_flag = true;
        std.clr_spec_inp = colour_spec_inp;
        std.smp_struct_inp = colour_struct_inp;
        break;
    }
    std.eotf = eotf;
    std.clr_space = colour_space;
    std.clr_spec = HW_API::C_REC709;
    std.smp_struct = HW_API::S_422;
    HW_API::setVideoStandard((aspen_path_offset+0),std);
    printf("HW_API::setVideoStandard(%u,std)\n",aspen_path_offset+0);
    HW_API::setVideoStandard((aspen_path_offset+1),std);
    printf("HW_API::setVideoStandard(%u,std)\n",aspen_path_offset+1);
    std.clr_spec = colour_spec_inp;
    std.smp_struct = HW_API::S_444;
    HW_API::setVideoStandard((aspen_path_offset+2),std);
    printf("HW_API::setVideoStandard(%u,std)\n",aspen_path_offset+2);
    HW_API::setVideoStandard((aspen_path_offset+3),std);
    printf("HW_API::setVideoStandard(%u,std)\n",aspen_path_offset+3);
    std.clr_spec = colour_spec_inp;
    std.smp_struct = colour_struct_inp;
    HW_API::setVideoStandard((tico_path_offset+0), std);
    printf("HW_API::setVideoStandard(%u,std)\n",tico_path_offset+0);
    HW_API::setVideoStandard((tico_path_offset+1), std);
    printf("HW_API::setVideoStandard(%u,std)\n",tico_path_offset+1);
    std.clr_spec = HW_API::C_REC709;
    std.smp_struct = HW_API::S_422;
    HW_API::setVideoStandard((smpte2110_path_offset+0), std);
    printf("HW_API::setVideoStandard(%u,std)\n",smpte2110_path_offset+0);
    HW_API::setVideoStandard((smpte2110_path_offset+1), std);
    printf("HW_API::setVideoStandard(%u,std)\n",smpte2110_path_offset+1);

    HW_API::TicoSubSampling_Mode subsample;
    if (colour_struct_inp == HW_API::S_422) {
      subsample = HW_API::TICO_YCC422;
    } else if  (colour_spec_inp == HW_API::C_SRGB) {
      subsample = HW_API::TICO_RGB;
    } else {
      subsample = HW_API::TICO_YCC444;
    }
    // Specify the lvl_weight according to the colour
    uint32_t lvl_weight;
    if (subsample == HW_API::TICO_YCC422) {
      lvl_weight = 3; // YCC Visual
    } else {
      lvl_weight = 4; // RGB Visual
    }
    if (tico and HW_API::getFPGACapability("TICO_MODE") > 0) {
      uint64_t tico_bitrate = (std.spal * std.alpf0 * std.frame_rate_num) / std.frame_rate_den;
      tico_bitrate *= 4; // always set to 4bpp.
      HW_API::configTicoEnc(0, std.spal, std.alpf0, tico_bitrate, std.frame_rate_num, std.frame_rate_den, 10, lvl_weight, subsample, smpte2110, std.interlaced);
      printf("HW_API::configTicoEnc(0, %u, %u, %llu, %u, %u, 10, %u, %u, %u, %u))\n",std.spal,std.alpf0,tico_bitrate,std.frame_rate_num,std.frame_rate_den,lvl_weight,(uint32_t)subsample,smpte2110,std.interlaced);
      HW_API::configTicoEnc(1, std.spal, std.alpf0, tico_bitrate, std.frame_rate_num, std.frame_rate_den, 10, lvl_weight, subsample, smpte2110, std.interlaced);
      printf("HW_API::configTicoEnc(1, %u, %u, %llu, %u, %u, 10, %u, %u, %u, %u))\n",std.spal,std.alpf0,tico_bitrate,std.frame_rate_num,std.frame_rate_den,lvl_weight,(uint32_t)subsample,smpte2110,std.interlaced);
    }

    printf("Done.\n");
    for (uint32_t sfp_safe = sfp_a; sfp_safe<sfp_b; sfp_safe++) {
      if ((sfp_safe != sfp_a) && (sfp_safe != sfp_b)) continue; // Only configure selected SFPs
      // Source IP
      printf("  Setting Source IP Address to 192.168.99.115...\n");
      fflush(stdout);
      HW_API::setSourceIPAddress(sfp_safe, 192 << 24 | 168 << 16 |99 << 8 | 115);
      printf("HW_API::setSourceIPAddress(%u, 192 << 24 | 168 << 16 |99 << 8 | 115)\n",sfp_safe);
      printf("Done.\n");
      printf("  Setting Source IP Port to 0000...\n");
      fflush(stdout);
      HW_API::setSourceIPPort(sfp_safe, 0);
      printf("HW_API::setSourceIPPort(%u, 0)\n",sfp_safe);
      printf("Done.\n");
      // Source MAC
      printf("  Setting Source MAC Addresses to 00:02:c5:17:21:36...\n");
      fflush(stdout);
      HW_API::setSourceMACAddress(sfp_safe, (uint64_t)0x00 << 40 |
                                            (uint64_t)0x02 << 32 |
                                            (uint64_t)0xc5 << 24 |
                                            (uint64_t)0x17 << 16 |
                                            (uint64_t)0x21 << 8  |
                                            (uint64_t)0x36 << 0);
      printf("HW_API::setSourceMACAddress(%u, (uint64_t)0x00 << 40 | (uint64_t)0x02 << 32 | (uint64_t)0xc5 << 24 | (uint64_t)0x17 << 16 | (uint64_t)0x21 << 8  | (uint64_t)0x36 << 0)\n", sfp_safe);
      printf("Done.\n");
      // TTL
      uint32_t ttl = 3;
      printf("  Setting TTLs to %u...\n",ttl);
      fflush(stdout);
      if (usb) {
        HW_API::setTTL(sfp_safe,get10GTxUSBChannel(0),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxUSBChannel(0),ttl);
      }
      if (aspen422) {
        HW_API::setTTL(sfp_safe,get10GTxVideoChannel(HW_API::VT_ASPEN422,0),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxVideoChannel(HW_API::VT_ASPEN422,0),ttl);
        HW_API::setTTL(sfp_safe,get10GTxVideoChannel(HW_API::VT_ASPEN422,1),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxVideoChannel(HW_API::VT_ASPEN422,1),ttl);
      }
      if (aspen444) {
        HW_API::setTTL(sfp_safe,get10GTxVideoChannel(HW_API::VT_ASPEN444,0),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxVideoChannel(HW_API::VT_ASPEN444,0),ttl);
        HW_API::setTTL(sfp_safe,get10GTxVideoChannel(HW_API::VT_ASPEN444,1),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxVideoChannel(HW_API::VT_ASPEN444,1),ttl);
      }
      if (tico) {
        HW_API::setTTL(sfp_safe,get10GTxVideoChannel(HW_API::VT_TICO,0),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxVideoChannel(HW_API::VT_TICO,0),ttl);
        HW_API::setTTL(sfp_safe,get10GTxVideoChannel(HW_API::VT_TICO,1),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxVideoChannel(HW_API::VT_TICO,1),ttl);
      }
      if (smpte2110) {
        HW_API::setTTL(sfp_safe,get10GTxVideoChannel(HW_API::VT_ST2110,0),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxVideoChannel(HW_API::VT_ST2110,0),ttl);
        HW_API::setTTL(sfp_safe,get10GTxVideoChannel(HW_API::VT_ST2110,1),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxVideoChannel(HW_API::VT_ST2110,1),ttl);
      }
      if (audio) {
        HW_API::setTTL(sfp_safe,get10GTxAudioChannel(0),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxAudioChannel(0),ttl);
        HW_API::setTTL(sfp_safe,get10GTxAudioChannel(1),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxAudioChannel(1),ttl);
        HW_API::setTTL(sfp_safe,get10GTxAudioChannel(2),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxAudioChannel(2),ttl);
      }
      if (meta) {
        HW_API::setTTL(sfp_safe,get10GTxMetaChannel(0),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxMetaChannel(0),ttl);
        HW_API::setTTL(sfp_safe,get10GTxMetaChannel(1),ttl);
        printf("HW_API::setTTL(%u,%u,%u)\n",sfp_safe,get10GTxMetaChannel(1),ttl);
      }
      printf("Done.\n");
      // Destination MAC
      printf("  Setting Destination MACs to 01:00:5E:00:00:01 (multicast)...\n");
      fflush(stdout);
      uint64_t destMac = (uint64_t)0x01 << 40 |
                         (uint64_t)0x00 << 32 |
                         (uint64_t)0x5E << 24 |
                         (uint64_t)0x00 << 16 |
                         (uint64_t)0x00 << 8  |
                         (uint64_t)0x01 << 0;


      if (usb) {
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxUSBChannel(0), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxUSBChannel(0), destMac);
      }
      if (aspen422) {
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), destMac);
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), destMac);
      }
      if (aspen444) {
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), destMac);
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), destMac);
      }
      if (tico) {
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,0), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,0), destMac);
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,1), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,1), destMac);
      }
      if (smpte2110) {
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,0), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,0), destMac);
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,1), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,1), destMac);
      }
      if (audio) {
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxAudioChannel(0), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxAudioChannel(0), destMac);
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxAudioChannel(1), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxAudioChannel(1), destMac);
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxAudioChannel(2), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxAudioChannel(2), destMac);
      }
      if (meta) {
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxMetaChannel(0), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxMetaChannel(0), destMac);
        HW_API::setDestinationMACAddress(sfp_safe, get10GTxMetaChannel(1), destMac);
        printf("HW_API::setDestinationMACAddress(%u, %u, %llx)\n",sfp_safe, get10GTxMetaChannel(1), destMac);
      }
      printf("Done.\n");
      // Destination IP
      printf("  Setting Destination IPs to 239.0.1.1/2   (aspen422_0/aspen422_1, aspen444_0,aspen444_1, tico0/tico1, smpte2110_0/smpte2110_1)/\n");
      printf("                                  .2.1/2/3 (aud0/aud1/aud2)\n");
      printf("                                  .3.1/2   (meta0/meta1)\n");
      printf("                                  .4.1     (usb)...\n");
      fflush(stdout);
      uint32_t baseIP = 239 << 24 | 0 << 16 | 0 << 8 | 0 << 0;
      uint32_t destIP;
      if (usb) {
        destIP = baseIP + (4 << 8 | 1 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxUSBChannel(0), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n",sfp_safe, get10GTxUSBChannel(0), destIP);
      }
      if (aspen422) {
        destIP = baseIP + (1 << 8 | 1 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), destIP);
        destIP = baseIP + (1 << 8 | 2 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), destIP);
      }
      if (aspen444) {
        destIP = baseIP + (1 << 8 | 1 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), destIP);
        destIP = baseIP + (1 << 8 | 2 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), destIP);
      }
      if (tico) {
        destIP = baseIP + (1 << 8 | 1 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,0), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,0), destIP);
        destIP = baseIP + (1 << 8 | 2 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,1), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,1), destIP);
      }
      if (smpte2110) {
        destIP = baseIP + (1 << 8 | 1 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,0), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,0), destIP);
        destIP = baseIP + (1 << 8 | 2 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,1), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,1), destIP);
      }
      if (audio) {
        destIP = baseIP + (2 << 8 | 1 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxAudioChannel(0), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxAudioChannel(0), destIP);
        destIP = baseIP + (2 << 8 | 2 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxAudioChannel(1), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxAudioChannel(1), destIP);
        destIP = baseIP + (2 << 8 | 3 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxAudioChannel(2), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxAudioChannel(2), destIP);
      }
      if (meta) {
        destIP = baseIP + (3 << 8 | 1 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxMetaChannel(0), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxMetaChannel(0), destIP);
        destIP = baseIP + (3 << 8 | 2 << 0);
        HW_API::setDestinationIPAddress(sfp_safe, get10GTxMetaChannel(1), destIP);
        printf("HW_API::setDestinationIPAddress(%u, %u, %x)\n", sfp_safe, get10GTxMetaChannel(1), destIP);
      }
      printf("Done.\n");
      // Destination Port
      printf("  Setting Destination Ports to 1234...\n");
      fflush(stdout);
      if (usb) {
        HW_API::setDestinationPort(sfp_safe, get10GTxUSBChannel(0), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxUSBChannel(0), 1234);
      }
      if (aspen422) {
        HW_API::setDestinationPort(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), 1234);
        HW_API::setDestinationPort(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), 1234);
      }
      if (aspen444) {
        HW_API::setDestinationPort(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), 1234);
        HW_API::setDestinationPort(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), 1234);
      }
      if (tico) {
        HW_API::setDestinationPort(sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,0), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,0), 1234);
        HW_API::setDestinationPort(sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,1), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,1), 1234);
      }
      if (smpte2110) {
        HW_API::setDestinationPort(sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,0), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,0), 1234);
        HW_API::setDestinationPort(sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,1), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,1), 1234);
      }
      if (audio) {
        HW_API::setDestinationPort(sfp_safe, get10GTxAudioChannel(0), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxAudioChannel(0), 1234);
        HW_API::setDestinationPort(sfp_safe, get10GTxAudioChannel(1), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxAudioChannel(1), 1234);
        HW_API::setDestinationPort(sfp_safe, get10GTxAudioChannel(2), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxAudioChannel(2), 1234);
      }
      if (meta) {
        HW_API::setDestinationPort(sfp_safe, get10GTxMetaChannel(0), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxMetaChannel(0), 1234);
        HW_API::setDestinationPort(sfp_safe, get10GTxMetaChannel(1), 1234);
        printf("HW_API::setDestinationPort(%u, %u, %u)\n", sfp_safe, get10GTxMetaChannel(1), 1234);
      }
      printf("Done.\n");
      // Keys
      if (srtp) {
        printf("  Setting Keys to 0 ...\n");
        fflush(stdout);
        uint32_t key[4] = {0,0,0,0};
        if (usb) {
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxUSBChannel(0),                       key, 1); // USB
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxUSBChannel(0), key[0], key[1], key[2], key[3]);
        }
        if (aspen422) {
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), key, 1); // ASPEN 4:2:2 0
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), key[0], key[1], key[2], key[3]);
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), key, 1); // ASPEN 4:2:2 1
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), key[0], key[1], key[2], key[3]);
        }
        if (aspen444) {
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), key, 1); // ASPEN 4:4:4 0
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), key[0], key[1], key[2], key[3]);
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), key, 1); // ASPEN 4:4:4 1
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), key[0], key[1], key[2], key[3]);
        }
        if (tico) {
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_TICO,0),     key, 1); // TICO 0
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_TICO,0), key[0], key[1], key[2], key[3]);
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_TICO,1),     key, 1); // TICO 1
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_TICO,1), key[0], key[1], key[2], key[3]);
        }
        if (smpte2110) {
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ST2110,0),   key, 1); // SMPTE2110 0
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ST2110,0), key[0], key[1], key[2], key[3]);
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ST2110,1),   key, 1); // SMPTE2110 1
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ST2110,1), key[0], key[1], key[2], key[3]);
        }
        if (audio) {
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxAudioChannel(0),                     key, 1); // Audio 0
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxAudioChannel(0), key[0], key[1], key[2], key[3]);
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxAudioChannel(1),                     key, 1); // Audio 1
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxAudioChannel(1), key[0], key[1], key[2], key[3]);
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxAudioChannel(2),                     key, 1); // Audio 2
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxAudioChannel(2), key[0], key[1], key[2], key[3]);
        }
        if (meta) {
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxMetaChannel(0),                      key, 1); // Meta 0
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxMetaChannel(0), key[0], key[1], key[2], key[3]);
          HW_API::set10GTxKey(sfp_safe%N_XGE, get10GTxMetaChannel(1),                      key, 1); // Meta 1
          printf("HW_API::set10GTxKey(%u, %u, [%x, %x, %x, %x], 1)\n", sfp_safe%N_XGE, get10GTxMetaChannel(1), key[0], key[1], key[2], key[3]);
        }
        printf("Done.\n");
      }
      // Path
      printf("  Setting Path Enables...\n");
      fflush(stdout);
      if (usb) {
        if (sfp_safe < N_XGE) {
          HW_API::set10GETxEnable(sfp_safe, get10GTxUSBChannel(0), usb);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxUSBChannel(0), usb);
        } else {
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxUSBChannel(0), usb);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxUSBChannel(0), usb);
        }
      }
      if (aspen422) {
        if (sfp_safe < N_XGE) {
          HW_API::set10GETxEnable(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), aspen422);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), aspen422);
          HW_API::set10GETxEnable(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), aspen422);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), aspen422);
        } else {
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), aspen422);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN422,0), aspen422);
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), aspen422);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN422,1), aspen422);
        }
      }
      if (aspen444) {
        if (sfp_safe < N_XGE) {
          HW_API::set10GETxEnable(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), aspen444);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), aspen444);
          HW_API::set10GETxEnable(sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), aspen444);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), aspen444);
        } else {
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), aspen444);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN444,0), aspen444);
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), aspen444);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ASPEN444,1), aspen444);
        }
      }
      if (tico) {
        if (sfp_safe < N_XGE) {
          HW_API::set10GETxEnable(sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,0), tico);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,0), tico);
          HW_API::set10GETxEnable(sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,1), tico);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_TICO,1), tico);
        } else {
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_TICO,0), tico);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_TICO,0), tico);
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_TICO,1), tico);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_TICO,1), tico);
        }
      }
      if (smpte2110) {
        if (sfp_safe < N_XGE) {
          HW_API::set10GETxEnable(sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,0), smpte2110);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,0), smpte2110);
          HW_API::set10GETxEnable(sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,1), smpte2110);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxVideoChannel(HW_API::VT_ST2110,1), smpte2110);
        } else {
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ST2110,0), smpte2110);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ST2110,0), smpte2110);
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ST2110,1), smpte2110);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxVideoChannel(HW_API::VT_ST2110,1), smpte2110);
        }
      }
      if (audio) {
        if (sfp_safe < N_XGE) {
          HW_API::set10GETxEnable(sfp_safe, get10GTxAudioChannel(0), audio);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxAudioChannel(0), audio);
          HW_API::set10GETxEnable(sfp_safe, get10GTxAudioChannel(1), audio);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxAudioChannel(1), audio);
          HW_API::set10GETxEnable(sfp_safe, get10GTxAudioChannel(2), audio);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxAudioChannel(2), audio);
        } else {
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxAudioChannel(0), audio);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxAudioChannel(0), audio);
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxAudioChannel(1), audio);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxAudioChannel(1), audio);
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxAudioChannel(2), audio);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxAudioChannel(2), audio);
        }
      }
      if (meta) {
        if (sfp_safe < N_XGE) {
          HW_API::set10GETxEnable(sfp_safe, get10GTxMetaChannel(0), meta);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxMetaChannel(0), meta);
          HW_API::set10GETxEnable(sfp_safe, get10GTxMetaChannel(1), meta);
          printf("HW_API::set10GETxEnable(%u, %u, %u)\n", sfp_safe, get10GTxMetaChannel(1), meta);
        } else {
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxMetaChannel(0), meta);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxMetaChannel(0), meta);
          HW_API::setInterFPGAChannelEnable(sfp_safe%N_XGE, get10GTxMetaChannel(1), meta);
          printf("HW_API::setInterFPGAChannelEnable(%u, %u, %u)\n", sfp_safe%N_XGE, get10GTxMetaChannel(1), meta);
        }
      }
      printf("Done.\n");
    }
    // Done
    printf("Done.\n");
    return;
}

void
HW_API::bist10GERx(uint32_t sfp_a, uint32_t sfp_b, bool redundancy, bool srtp) {
    if (sfp_a >= HW_API::N_XGE_RX)
    {
      printf("sfp_a out of range!\n");
      return;
    }
    if (sfp_b >= HW_API::N_XGE_RX)
    {
      printf("sfp_b out of range!\n");
      return;
    }
    printf("Initializing 10GE %u,%u Rx paths with known good defaults:\n", sfp_a, sfp_b);
    // Init
    printf("  Initializing controllers...");
    fflush(stdout);
    HW_API::initIPRx();
    assert(HW_API::getIPRxInitDone());
    HW_API::initIPtoAV();
    assert(HW_API::getIPtoAVInitDone());
    printf("Done.\n");
    // video/audio mapping same as bist10GETx except:
    // The TX has separate paths for ASPEN422, ASPEN444 and TICO, that can all be enabled
    // at the same time. The RX path automaticlly detects whether the stream is
    // ASPEN422, ASPEN444 or TICO so only 2 (and not 6) are needed.
    uint32_t video_path_offset = 0; // 4 ASPEN or TICO paths per SFP
    uint32_t video_2110_path_offset = 4; // 2 SMPTE 2110-20 paths per SFP
    uint32_t aud_path_offset = 0; // 3 Audio paths per SFP
    // Channel mapping
    uint32_t usb_chan = 0;
    uint32_t vid_0_chan = 1;
    uint32_t vid_1_chan = 2;
    uint32_t vid_2110_0_chan = 1;
    uint32_t vid_2110_1_chan = 2;
    uint32_t aud_0_chan = 3;
    uint32_t aud_1_chan = 4;
    uint32_t aud_2_chan = 5;
    uint32_t meta_0_chan = 6;
    uint32_t meta_1_chan = 7;
    // Map IP / Port to channels
    printf("  Setting Rx IP Address and Port to 239.0.1.1(vid0)/2(vid1)/.2.1(aud0)/.2.2(aud1)/.2.3(aud2)/.3.1(meta0)/.3.2(meta1)/.4.1(usb)...");
    fflush(stdout);
    HW_API::setRxDataAddrPort(sfp_a   , vid_0_chan      , 239 << 24 | 0 << 16 | 1 << 8 | 1, 1234, false);  // aspen422/aspen444/tico_0/smpte2110_0
    HW_API::setRxDataAddrPort(sfp_b   , vid_0_chan      , 239 << 24 | 0 << 16 | 1 << 8 | 1, 1234, false);
    HW_API::setRxDataAddrPort(sfp_a   , vid_1_chan      , 239 << 24 | 0 << 16 | 1 << 8 | 2, 1234, false);  // aspen422/aspen444/tico_1/smpte2110_1
    HW_API::setRxDataAddrPort(sfp_b   , vid_1_chan      , 239 << 24 | 0 << 16 | 1 << 8 | 2, 1234, false);
    HW_API::setRxDataAddrPort(sfp_a   , aud_0_chan      , 239 << 24 | 0 << 16 | 2 << 8 | 1, 1234, false);  // aud_0
    HW_API::setRxDataAddrPort(sfp_b   , aud_0_chan      , 239 << 24 | 0 << 16 | 2 << 8 | 1, 1234, false);
    HW_API::setRxDataAddrPort(sfp_a   , aud_1_chan      , 239 << 24 | 0 << 16 | 2 << 8 | 2, 1234, false);  // aud_1
    HW_API::setRxDataAddrPort(sfp_b   , aud_1_chan      , 239 << 24 | 0 << 16 | 2 << 8 | 2, 1234, false);
    HW_API::setRxDataAddrPort(sfp_a   , aud_2_chan      , 239 << 24 | 0 << 16 | 2 << 8 | 3, 1234, false);  // aud_2
    HW_API::setRxDataAddrPort(sfp_b   , aud_2_chan      , 239 << 24 | 0 << 16 | 2 << 8 | 3, 1234, false);
    HW_API::setRxDataAddrPort(sfp_a   , meta_0_chan     , 239 << 24 | 0 << 16 | 3 << 8 | 1, 1234, false);  // meta_0
    HW_API::setRxDataAddrPort(sfp_b   , meta_0_chan     , 239 << 24 | 0 << 16 | 3 << 8 | 1, 1234, false);
    HW_API::setRxDataAddrPort(sfp_a   , meta_1_chan     , 239 << 24 | 0 << 16 | 3 << 8 | 2, 1234, false);  // meta_1
    HW_API::setRxDataAddrPort(sfp_b   , meta_1_chan     , 239 << 24 | 0 << 16 | 3 << 8 | 2, 1234, false);
    HW_API::setRxDataAddrPort(sfp_a   , usb_chan        , 239 << 24 | 0 << 16 | 4 << 8 | 1, 1234, false);  // usb
    HW_API::setRxDataAddrPort(sfp_b   , usb_chan        , 239 << 24 | 0 << 16 | 4 << 8 | 1, 1234, false);
    // Map channels to receivers
    HW_API::setVidSFPChannel((video_path_offset+0),        sfp_a,    vid_0_chan      , true);
    HW_API::setVidSFPChannel((video_path_offset+0),        sfp_b,    vid_0_chan      , false);
    HW_API::setVidSFPChannel((video_path_offset+1),        sfp_a,    vid_1_chan      , true);
    HW_API::setVidSFPChannel((video_path_offset+1),        sfp_b,    vid_1_chan      , false);
    HW_API::setVidSFPChannel((video_2110_path_offset+0),   sfp_a,    vid_2110_0_chan , true);
    HW_API::setVidSFPChannel((video_2110_path_offset+0),   sfp_b,    vid_2110_0_chan , false);
    HW_API::setVidSFPChannel((video_2110_path_offset+1),   sfp_a,    vid_2110_1_chan , true);
    HW_API::setVidSFPChannel((video_2110_path_offset+1),   sfp_b,    vid_2110_1_chan , false);
    HW_API::setAudSFPChannel((aud_path_offset+0),          sfp_a,    aud_0_chan      , true);
    HW_API::setAudSFPChannel((aud_path_offset+0),          sfp_b,    aud_0_chan      , false);
    HW_API::setAudSFPChannel((aud_path_offset+1),          sfp_a,    aud_1_chan      , true);
    HW_API::setAudSFPChannel((aud_path_offset+1),          sfp_b,    aud_1_chan      , false);
    HW_API::setAudSFPChannel((aud_path_offset+2),          sfp_a,    aud_2_chan      , true);
    HW_API::setAudSFPChannel((aud_path_offset+2),          sfp_b,    aud_2_chan      , false);
    HW_API::setUSBSFPChannel(0,                            sfp_a,    usb_chan        , true);
    HW_API::setUSBSFPChannel(0,                            sfp_b,    usb_chan        , false);
    HW_API::setMetaSFPChannel(0,                           sfp_a,    meta_0_chan     , true);
    HW_API::setMetaSFPChannel(0,                           sfp_b,    meta_0_chan     , false);
    HW_API::setMetaSFPChannel(1,                           sfp_a,    meta_1_chan     , true);
    HW_API::setMetaSFPChannel(1,                           sfp_b,    meta_1_chan     , false);
    printf("Done.\n");
    // PID
    printf("  Setting Rx PIDs to 361 (ASPEN), 362 (Tico), and 200 (audio)...");
    fflush(stdout);
    HW_API::setVideoRxAspenPID((video_path_offset+0),361);
    HW_API::setVideoRxTicoPID((video_path_offset+0),362);
    HW_API::setVideoRxAspenPID((video_path_offset+1),361);
    HW_API::setVideoRxTicoPID((video_path_offset+1),362);
    HW_API::setAudioRxPID((aud_path_offset+0),200);
    HW_API::setAudioRxPID((aud_path_offset+1),200);
    HW_API::setAudioRxPID((aud_path_offset+2),200);
    printf("Done.\n");
    // Allow Descramble
    printf("  Setting Rx allowDescramble to true...");
    fflush(stdout);
    HW_API::allowDescramble10GERxVid((video_path_offset+0), true);
    HW_API::allowDescramble10GERxVid((video_path_offset+1), true);
    printf("Done.\n");
    // Enable
    printf("  Setting Path Enables...");
    fflush(stdout);
    HW_API::setVidStreamEnable((video_path_offset+0),true,true);
    HW_API::setVidStreamEnable((video_path_offset+0),redundancy,false);
    HW_API::setVidStreamEnable((video_path_offset+1),true,true);
    HW_API::setVidStreamEnable((video_path_offset+1),redundancy,false);
    HW_API::setVidStreamEnable((video_2110_path_offset+0),true,true);
    HW_API::setVidStreamEnable((video_2110_path_offset+0),redundancy,false);
    HW_API::setVidStreamEnable((video_2110_path_offset+1),true,true);
    HW_API::setVidStreamEnable((video_2110_path_offset+1),redundancy,false);
    HW_API::setAudStreamEnable((aud_path_offset+0),true,true);
    HW_API::setAudStreamEnable((aud_path_offset+0),redundancy,false);
    HW_API::setAudStreamEnable((aud_path_offset+1),true,true);
    HW_API::setAudStreamEnable((aud_path_offset+1),redundancy,false);
    HW_API::setAudStreamEnable((aud_path_offset+2),true,true);
    HW_API::setAudStreamEnable((aud_path_offset+2),redundancy,false);
    HW_API::setMetaStreamEnable(0,true,true);
    HW_API::setMetaStreamEnable(0,redundancy,false);
    HW_API::setMetaStreamEnable(1,true,true);
    HW_API::setMetaStreamEnable(1,redundancy,false);
    HW_API::setUSBStreamEnable(0,true,true);
    HW_API::setUSBStreamEnable(0,redundancy,false);

    printf("Done.\n");
    // Keys
    if (srtp) {
      // These map to the channels corresponding to an addr:port
      printf("  Setting Keys to 0 ...");
      fflush(stdout);
      uint32_t key[4] = {0,0,0,0};
      HW_API::set10GRxKey(sfp_a,    vid_0_chan  , key, 1); // ASPEN/TICO 0
      HW_API::set10GRxKey(sfp_b,    vid_0_chan  , key, 1); // ASPEN/TICO 0
      HW_API::set10GRxKey(sfp_a,    vid_1_chan  , key, 1); // ASPEN/TICO 1
      HW_API::set10GRxKey(sfp_b,    vid_1_chan  , key, 1); // ASPEN/TICO 1
      HW_API::set10GRxKey(sfp_a,    aud_0_chan  , key, 1); // Audio 0
      HW_API::set10GRxKey(sfp_b,    aud_0_chan  , key, 1); // Audio 0
      HW_API::set10GRxKey(sfp_a,    aud_1_chan  , key, 1); // Audio 1
      HW_API::set10GRxKey(sfp_b,    aud_1_chan  , key, 1); // Audio 1
      HW_API::set10GRxKey(sfp_a,    aud_2_chan  , key, 1); // Audio 1
      HW_API::set10GRxKey(sfp_b,    aud_2_chan  , key, 1); // Audio 1
      HW_API::set10GRxKey(sfp_a,    usb_chan    , key, 1); // USB
      HW_API::set10GRxKey(sfp_b,    usb_chan    , key, 1); // USB
      HW_API::set10GRxKey(sfp_a,    meta_0_chan , key, 1); // Meta 0
      HW_API::set10GRxKey(sfp_b,    meta_0_chan , key, 1); // Meta 0
      HW_API::set10GRxKey(sfp_a,    meta_1_chan , key, 1); // Meta 1
      HW_API::set10GRxKey(sfp_b,    meta_1_chan , key, 1); // Meta 1
      printf("Done.\n");
    }
    //
    HW_API::setVidBnotA((video_path_offset+0), false);
    HW_API::setVidBnotA((video_path_offset+1), false);
    HW_API::setVidBnotA((video_2110_path_offset+0), false);
    HW_API::setVidBnotA((video_2110_path_offset+1), false);
    HW_API::setAudBnotA((aud_path_offset+0), false);
    HW_API::setAudBnotA((aud_path_offset+1), false);
    HW_API::setAudBnotA((aud_path_offset+2), false);
    HW_API::setMetaBnotA(0, false);
    HW_API::setMetaBnotA(1, false);
    HW_API::setUSBBnotA(0, false);
    printf("Done.\n");
    // Redundancy
    printf("  Setting Path Redundancies...");
    fflush(stdout);
    HW_API::setVidRedundancy((video_path_offset+0), redundancy);
    HW_API::setVidRedundancy((video_path_offset+1), redundancy);
    HW_API::setVidRedundancy((video_2110_path_offset+0), redundancy);
    HW_API::setVidRedundancy((video_2110_path_offset+1), redundancy);
    HW_API::setAudRedundancy((aud_path_offset+0), redundancy);
    HW_API::setAudRedundancy((aud_path_offset+1), redundancy);
    HW_API::setAudRedundancy((aud_path_offset+2), redundancy);
    HW_API::setMetaRedundancy(0, redundancy);
    HW_API::setMetaRedundancy(1, redundancy);
    HW_API::setUSBRedundancy(0, redundancy);
    printf("Done.\n");
    printf("  Configure Tico Decode:\n");
    uint32_t tico_vid = 0;
    printf("    Reading Video Standard RX %u\n",tico_vid);
    HW_API::vidSTD std = HW_API::getVidSTD(tico_vid);
    printf("      10GE Rx Vid %u Standard:\n", tico_vid);
    printf("        SPAL        = %u\n", std.spal);
    printf("        ALPF0       = %u\n", std.alpf0);
    printf("        RATE_NUM    = %u\n", std.rate_num);
    printf("        RATE_DEN    = %u\n", std.rate_den);
    printf("        STREAM_TYPE = %u\n", std.stream_type);
    IPtoAVType::aspenColourSpecification colourSpecification;
    HW_API::getVidColourSpecification(tico_vid,&colourSpecification);
    printf("      10GE Rx Vid %u Colour Specification = %u\n", tico_vid, colourSpecification);
    IPtoAVType::aspenSampleStructure sampleStructure;
    HW_API::getVidSampleStructure(tico_vid,&sampleStructure);
    printf("      10GE Rx Vid %u Sample Structure = %u\n", tico_vid, sampleStructure);

    HW_API::configTicoDec(0, std.spal, std.alpf0, std.rate_num, std.rate_den, 0);

    // Done
    printf("Done.\n");
}

void
HW_API::bist10GEUSB(uint32_t sfp_a, uint32_t sfp_b, bool redundancy, bool srtp) {
    if (sfp_a >= HW_API::N_XGE_RX)
    {
      printf("sfp_a out of range!\n");
      return;
    }
    if (sfp_b >= HW_API::N_XGE_RX)
    {
      printf("sfp_b out of range!\n");
      return;
    }
    printf("Initializing 10GE %u,%u USB paths with known good defaults:\n", sfp_a, sfp_b);
    // Rx
    // Init
    printf("  Initializing controllers...");
    fflush(stdout);
    HW_API::initIPRx();
    assert(HW_API::getIPRxInitDone());
    HW_API::initIPtoAV();
    assert(HW_API::getIPtoAVInitDone());
    printf("Done.\n");
    // Channel mapping
    uint32_t usb_chan = 0;
    // Map IP / Port to channel
    printf("  Setting Rx IP Address and Port to 239.0.4.1 on channel %u...", usb_chan);
    fflush(stdout);
    HW_API::setRxDataAddrPort(sfp_a   , usb_chan, 239 << 24 | 0 << 16 | 4 << 8 | 1, 1234, false);  // usb
    HW_API::setRxDataAddrPort(sfp_b   , usb_chan, 239 << 24 | 0 << 16 | 4 << 8 | 1, 1234, false);
    // Map channels to receivers
    HW_API::setUSBSFPChannel(0, sfp_a   , usb_chan, true);
    HW_API::setUSBSFPChannel(0, sfp_b,    usb_chan, false);
    printf("Done.\n");
    // Enable
    printf("  Setting Path Enables...");
    fflush(stdout);
    HW_API::setUSBStreamEnable(0,true,true);
    HW_API::setUSBStreamEnable(0,redundancy,false);
    printf("Done.\n");
    // Keys
    if (srtp) {
      // These map to the channels corresponding to an addr:port
      printf("  Setting channel 1 Keys to 0 ...");
      fflush(stdout);
      uint32_t key[4] = {0,0,0,0};
      HW_API::set10GRxKey(sfp_a   , usb_chan, key, 1);
      HW_API::set10GRxKey(sfp_b,    usb_chan, key, 1);
      printf("Done.\n");
    }
    //
    HW_API::setUSBBnotA(0, false);
    printf("Done.\n");
    // Redundancy
    printf("  Setting Path Redundancies...");
    fflush(stdout);
    HW_API::setUSBRedundancy(0, redundancy);
    printf("Done.\n");
    // Tx
    // Init
    printf("  Initializing controller...");
    fflush(stdout);
    HW_API::initAVtoIP();
    assert(HW_API::getAVtoIPInitDone());
    HW_API::initIPTx(7);
    assert(HW_API::getIPTxInitDone());
    printf("Done.\n");
    for (uint32_t sfp_safe = sfp_a; sfp_safe<sfp_b; sfp_safe++) {
      if ((sfp_safe != sfp_a) && (sfp_safe != sfp_b)) continue; // Only configure selected SFPs
      // Source IP
      printf("  Setting Source IP Address to 192.169.99.115...");
      fflush(stdout);
      HW_API::setSourceIPAddress(sfp_safe, 192 << 24 | 168 << 16 |99 << 8 | 115);
      printf("Done.\n");
      printf("  Setting Source IP Port to 0000...");
      fflush(stdout);
      HW_API::setSourceIPPort(sfp_safe, 0);
      printf("Done.\n");
      // Source MAC
      printf("  Setting Source MAC Addresses to 00:02:c5:17:21:36...");
      fflush(stdout);
      HW_API::setSourceMACAddress(sfp_safe, (uint64_t)0x00 << 40 |
                                            (uint64_t)0x02 << 32 |
                                            (uint64_t)0xc5 << 24 |
                                            (uint64_t)0x17 << 16 |
                                            (uint64_t)0x21 << 8  |
                                            (uint64_t)0x36 << 0);
      printf("Done.\n");
      // TTL
      printf("  Setting TTLs to 3...");
      fflush(stdout);
      HW_API::setTTL(sfp_safe,get10GTxUSBChannel(0),3);
      printf("Done.\n");
      // Destination MAC
      printf("  Setting Destination MACs to 01:00:5E:00:00:01 (multicast)...");
      fflush(stdout);
      HW_API::setDestinationMACAddress(sfp_safe, get10GTxUSBChannel(0),   (uint64_t)0x01 << 40 |
                                                                          (uint64_t)0x00 << 32 |
                                                                          (uint64_t)0x5E << 24 |
                                                                          (uint64_t)0x00 << 16 |
                                                                          (uint64_t)0x00 << 8  |
                                                                          (uint64_t)0x01 << 0);
      printf("Done.\n");
      // Destination IP
      printf("  Setting Destination IP to 239.0.4.1...");
      fflush(stdout);
      HW_API::setDestinationIPAddress(sfp_safe, get10GTxUSBChannel(0), 239 << 24 |
                                                                         0 << 16 |
                                                                         4 <<  8 |
                                                                         1 <<  0);
      printf("Done.\n");
      // Destination Port
      printf("  Setting Destination Ports to 1234...");
      fflush(stdout);
      HW_API::setDestinationPort(sfp_safe, get10GTxUSBChannel(0), 1234);
      printf("Done.\n");
      // Keys
      if (srtp) {
        printf("  Setting Keys to 0 ...");
        fflush(stdout);
        uint32_t key[4] = {0,0,0,0};
        HW_API::set10GTxKey(sfp_safe,get10GTxUSBChannel(0),key,1);
        printf("Done.\n");
      }
      // Path
      printf("  Setting Path Enables...");
      fflush(stdout);
      HW_API::set10GETxEnable(sfp_safe, get10GTxUSBChannel(0), true);
      printf("Done.\n");
    }
    // Done
    printf("Done.\n");
}

void
HW_API::bist10GEPCR(uint32_t sfp_a, uint32_t sfp_b, bool redundancy, bool srtp, bool remote) {
    printf("Initializing 10GE %u,%u PCR paths with known good defaults:\n", sfp_a, sfp_b);
    // Rx
    // Init
    printf("  Initializing controllers...");
    fflush(stdout);
    HW_API::initIPRx();
    assert(HW_API::getIPRxInitDone());
    HW_API::initIPtoAV();
    assert(HW_API::getIPtoAVInitDone());
    printf("Done.\n");
    // Channel mapping
    uint32_t pcr_chan = 7;
    // Map IP / Port to channel
    printf("  Setting Rx IP Address and Port to 239.0.10.1 on channel %u...", pcr_chan);
    fflush(stdout);
    HW_API::setRxDataAddrPort(sfp_a   , pcr_chan, 239 << 24 | 0 << 16 | 10 << 8 | 1, 1234, false);  // pcr
    HW_API::setRxDataAddrPort(sfp_b   , pcr_chan, 239 << 24 | 0 << 16 | 10 << 8 | 1, 1234, false);
    // Map channels to receivers
    HW_API::setPCRSFPChannel(sfp_a   , pcr_chan, true);
    HW_API::setPCRSFPChannel(sfp_b,    pcr_chan, false);
    printf("Done.\n");
    // Enable
    printf("  Setting Path Enables...");
    fflush(stdout);
    HW_API::setPCRStreamEnable(true,true);
    HW_API::setPCRStreamEnable(redundancy,false);
    HW_API::setUseRemotePCR(remote);
    printf("Done.\n");
    // Keys
    if (srtp) {
      // These map to the channels corresponding to an addr:port
      printf("  Setting channel %u Keys to 0 ...",pcr_chan);
      fflush(stdout);
      uint32_t key[4] = {0,0,0,0};
      HW_API::set10GRxKey(sfp_a   , pcr_chan, key, 1);
      HW_API::set10GRxKey(sfp_b,    pcr_chan, key, 1);
      printf("Done.\n");
    }
    //
    HW_API::setPCRBnotA(false);
    printf("Done.\n");
    // Redundancy
    printf("  Setting Path Redundancies...");
    fflush(stdout);
    HW_API::setPCRRedundancy(redundancy);
    printf("Done.\n");
    // Tx
    // Init
    printf("  Initializing controller...");
    fflush(stdout);
    HW_API::initAVtoIP();
    assert(HW_API::getAVtoIPInitDone());
    HW_API::initIPTx(7);
    assert(HW_API::getIPTxInitDone());
    printf("Done.\n");
    for (uint32_t sfp_safe = sfp_a%HW_API::N_XGE_TX; sfp_safe<sfp_b%HW_API::N_XGE_TX; sfp_safe++) {
      if ((sfp_safe != sfp_a) && (sfp_safe != sfp_b)) continue; // Only configure selected SFPs
      // Source IP
      printf("  Setting Source IP Address to 192.169.99.115...");
      fflush(stdout);
      HW_API::setSourceIPAddress(sfp_safe, 192 << 24 | 168 << 16 |99 << 8 | 115);
      printf("Done.\n");
      printf("  Setting Source IP Port to 0000...");
      fflush(stdout);
      HW_API::setSourceIPPort(sfp_safe, 0);
      printf("Done.\n");
      // Source MAC
      printf("  Setting Source MAC Addresses to 00:02:c5:17:21:36...");
      fflush(stdout);
      HW_API::setSourceMACAddress(sfp_safe, (uint64_t)0x00 << 40 |
                                            (uint64_t)0x02 << 32 |
                                            (uint64_t)0xc5 << 24 |
                                            (uint64_t)0x17 << 16 |
                                            (uint64_t)0x21 << 8  |
                                            (uint64_t)0x36 << 0);
      printf("Done.\n");
      // TTL
      printf("  Setting TTLs to 3...");
      fflush(stdout);
      HW_API::setTTL(sfp_safe,get10GTxPCRChannel(),3);
      printf("Done.\n");
      // Destination MAC
      printf("  Setting Destination MACs to 01:00:5E:00:00:01 (multicast)...");
      fflush(stdout);
      HW_API::setDestinationMACAddress(sfp_safe, get10GTxPCRChannel(),    (uint64_t)0x01 << 40 |
                                                                          (uint64_t)0x00 << 32 |
                                                                          (uint64_t)0x5E << 24 |
                                                                          (uint64_t)0x00 << 16 |
                                                                          (uint64_t)0x00 << 8  |
                                                                          (uint64_t)0x01 << 0);
      printf("Done.\n");
      // Destination IP
      printf("  Setting Destination IP to 239.0.10.1...");
      fflush(stdout);
      HW_API::setDestinationIPAddress(sfp_safe, get10GTxPCRChannel(), 239 << 24 |
                                                                        0 << 16 |
                                                                       10 <<  8 |
                                                                        1 <<  0);
      printf("Done.\n");
      // Destination Port
      printf("  Setting Destination Ports to 1234...");
      fflush(stdout);
      HW_API::setDestinationPort(sfp_safe, get10GTxPCRChannel(), 1234);
      printf("Done.\n");
      // Keys
      if (srtp) {
        printf("  Setting Keys to 0 ...");
        fflush(stdout);
        uint32_t key[4] = {0,0,0,0};
        HW_API::set10GTxKey(sfp_safe,get10GTxPCRChannel(),key,1);
        printf("Done.\n");
      }
      // Path
      printf("  Setting Path Enables...");
      fflush(stdout);
      HW_API::set10GETxEnable(sfp_safe, get10GTxPCRChannel(), true);
      printf("Done.\n");
    }
    // Done
    printf("Done.\n");
}

void
HW_API::bistScaler(uint32_t path, HW_API::bwBIST bw_inp, HW_API::bwBIST bw_out) {
  HW_API::bistScaler(path, bw_inp, HW_API::CSF_RGB, bw_out, HW_API::CSF_RGB);
  return;
}

void
HW_API::bistScaler(uint32_t path, HW_API::bwBIST bw_inp, HW_API::scColourFormat_type colour_inp, HW_API::bwBIST bw_out, HW_API::scColourFormat_type colour_out) {
    printf("Initializing Scaler path %u with known good defaults:\n", path);
    // Init
    printf("  Initializing scaler...");
    HW_API::initScalerPath(path);
    assert(HW_API::getScalerPathInitDone(path));
    printf("Done.\n");
    printf("  Setting reference to source %u...", path);
    HW_API::setRefClkenSource(path, path);
    printf("Done.\n");

    printf("  Setting up scaler %u to: ", path);
    RasterTypes::CVTParameters in_hdmi_params;
    RasterTypes::CVTParameters out_hdmi_params;
    HW_API::ScalerSettings sc_settings;
    HW_API::ScalerFrameRate in_rate;
    HW_API::ScalerFrameRate out_rate;
    switch (bw_inp) {
        case HW_API::BW_1920_1080I60:
            printf("1080i60");
            in_hdmi_params.appl = 1920;
            in_hdmi_params.tppl = 2200;
            in_hdmi_params.hs_width = 44;
            in_hdmi_params.hs_front_porch = 88;
            in_hdmi_params.hs_back_porch = 148;
            in_hdmi_params.alpf[0] = 540;
            in_hdmi_params.alpf[1] = 540;
            in_hdmi_params.tlpf[0] = 562;
            in_hdmi_params.tlpf[1] = 563;
            in_hdmi_params.vs_width = 5;
            in_hdmi_params.vs_front_porch = 2;
            in_hdmi_params.vs_back_porch = 15;
            in_rate.frame_rate_num = 60;
            in_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_1920_1080P30:
            printf("1080p30");
            in_hdmi_params.appl = 1920;
            in_hdmi_params.tppl = 2200;
            in_hdmi_params.hs_width = 44;
            in_hdmi_params.hs_front_porch = 88;
            in_hdmi_params.hs_back_porch = 148;
            in_hdmi_params.alpf[0] = 1080;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1125;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5;
            in_hdmi_params.vs_front_porch = 4;
            in_hdmi_params.vs_back_porch = 36;
            in_rate.frame_rate_num = 30;
            in_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_3840_2160P30:
            printf("2160p30");
            in_hdmi_params.appl = 1920*2;
            in_hdmi_params.tppl = 2200*2;
            in_hdmi_params.hs_width = 44*2;
            in_hdmi_params.hs_front_porch = 88*2;
            in_hdmi_params.hs_back_porch = 148*2;
            in_hdmi_params.alpf[0] = 1080*2;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1125*2;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5*2;
            in_hdmi_params.vs_front_porch = 4*2;
            in_hdmi_params.vs_back_porch = 36*2;
            in_rate.frame_rate_num = 30;
            in_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_3840_2160P60:
            printf("2160p60");
            in_hdmi_params.appl = 1920*2;
            in_hdmi_params.tppl = 2200*2;
            in_hdmi_params.hs_width = 44*2;
            in_hdmi_params.hs_front_porch = 88*2;
            in_hdmi_params.hs_back_porch = 148*2;
            in_hdmi_params.alpf[0] = 1080*2;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1125*2;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5*2;
            in_hdmi_params.vs_front_porch = 4*2;
            in_hdmi_params.vs_back_porch = 36*2;
            in_rate.frame_rate_num = 60;
            in_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_3840_2160P24:
            printf("2160p24");
            in_hdmi_params.appl = 1920*2;
            in_hdmi_params.tppl = 2750*2;
            in_hdmi_params.hs_width = 44*2;
            in_hdmi_params.hs_front_porch = 638*2;
            in_hdmi_params.hs_back_porch = 148*2;
            in_hdmi_params.alpf[0] = 1080*2;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1125*2;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5*2;
            in_hdmi_params.vs_front_porch = 4*2;
            in_hdmi_params.vs_back_porch = 36*2;
            in_rate.frame_rate_num = 24;
            in_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_3840_2160P23_98:
            printf("2160p23.98");
            in_hdmi_params.appl = 1920*2;
            in_hdmi_params.tppl = 2750*2;
            in_hdmi_params.hs_width = 44*2;
            in_hdmi_params.hs_front_porch = 638*2;
            in_hdmi_params.hs_back_porch = 148*2;
            in_hdmi_params.alpf[0] = 1080*2;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1125*2;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5*2;
            in_hdmi_params.vs_front_porch = 4*2;
            in_hdmi_params.vs_back_porch = 36*2;
            in_rate.frame_rate_num = 24000;
            in_rate.frame_rate_den = 1001;
            break;
        case HW_API::BW_3840_2160P59_94:
            printf("2160p59.94");
            in_hdmi_params.appl = 1920*2;
            in_hdmi_params.tppl = 2200*2;
            in_hdmi_params.hs_width = 44*2;
            in_hdmi_params.hs_front_porch = 88*2;
            in_hdmi_params.hs_back_porch = 148*2;
            in_hdmi_params.alpf[0] = 1080*2;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1125*2;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5*2;
            in_hdmi_params.vs_front_porch = 4*2;
            in_hdmi_params.vs_back_porch = 36*2;
            in_rate.frame_rate_num = 60000;
            in_rate.frame_rate_den = 1001;
            break;
        case HW_API::BW_3840_2160P29_98:
            printf("2160p29.98");
            in_hdmi_params.appl = 1920*2;
            in_hdmi_params.tppl = 2200*2;
            in_hdmi_params.hs_width = 44*2;
            in_hdmi_params.hs_front_porch = 88*2;
            in_hdmi_params.hs_back_porch = 148*2;
            in_hdmi_params.alpf[0] = 1080*2;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1125*2;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5*2;
            in_hdmi_params.vs_front_porch = 4*2;
            in_hdmi_params.vs_back_porch = 36*2;
            in_rate.frame_rate_num = 30000;
            in_rate.frame_rate_den = 1001;
            break;
        case HW_API::BW_1920_1080P59_94:
            printf("1080p59.94");
            in_hdmi_params.appl = 1920;
            in_hdmi_params.tppl = 2200;
            in_hdmi_params.hs_width = 44;
            in_hdmi_params.hs_front_porch = 88;
            in_hdmi_params.hs_back_porch = 148;
            in_hdmi_params.alpf[0] = 1080;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1125;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5;
            in_hdmi_params.vs_front_porch = 4;
            in_hdmi_params.vs_back_porch = 36;
            in_rate.frame_rate_num = 60000;
            in_rate.frame_rate_den = 1001;
            break;
        case HW_API::BW_1920_1200P60:
            printf("1920x1200p60\n");
            in_hdmi_params.appl = 1920;
            in_hdmi_params.tppl = 2080;
            in_hdmi_params.hs_width = 32;
            in_hdmi_params.hs_front_porch = 48;
            in_hdmi_params.hs_back_porch = 80;
            in_hdmi_params.alpf[0] = 1200;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1235;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 3;
            in_hdmi_params.vs_front_porch = 6;
            in_hdmi_params.vs_back_porch = 26;
            in_rate.frame_rate_num = 60;
            in_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_1920_1080P24:
            printf("1920x1080p24\n");
            in_hdmi_params.appl = 1920;
            in_hdmi_params.tppl = 2750;
            in_hdmi_params.hs_width = 44;
            in_hdmi_params.hs_front_porch = 638;
            in_hdmi_params.hs_back_porch = 148;
            in_hdmi_params.alpf[0] = 1080;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1125;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5;
            in_hdmi_params.vs_front_porch = 4;
            in_hdmi_params.vs_back_porch = 36;
            in_rate.frame_rate_num = 24;
            in_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_1280_720P60:
            printf("1280x720p60\n");
            in_hdmi_params.appl = 1280;
            in_hdmi_params.tppl = 1650;
            in_hdmi_params.hs_width = 40;
            in_hdmi_params.hs_front_porch = 110;
            in_hdmi_params.hs_back_porch = 220;
            in_hdmi_params.alpf[0] = 720;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 750;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5;
            in_hdmi_params.vs_front_porch = 5;
            in_hdmi_params.vs_back_porch = 20;
            in_rate.frame_rate_num = 60;
            in_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_640_480P60:
            printf("640x480p60\n");
            in_hdmi_params.appl = 640;
            in_hdmi_params.tppl = 800;
            in_hdmi_params.hs_width = 96;
            in_hdmi_params.hs_front_porch = 24;
            in_hdmi_params.hs_back_porch = 40;
            in_hdmi_params.alpf[0] = 480;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 525;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 2;
            in_hdmi_params.vs_front_porch = 18;
            in_hdmi_params.vs_back_porch = 25;
            in_rate.frame_rate_num = 60;
            in_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_1920_1080P60:
        default:
            printf("1080p60");
            in_hdmi_params.appl = 1920;
            in_hdmi_params.tppl = 2200;
            in_hdmi_params.hs_width = 44;
            in_hdmi_params.hs_front_porch = 88;
            in_hdmi_params.hs_back_porch = 148;
            in_hdmi_params.alpf[0] = 1080;
            in_hdmi_params.alpf[1] = 0;
            in_hdmi_params.tlpf[0] = 1125;
            in_hdmi_params.tlpf[1] = 0;
            in_hdmi_params.vs_width = 5;
            in_hdmi_params.vs_front_porch = 4;
            in_hdmi_params.vs_back_porch = 36;
            in_rate.frame_rate_num = 60;
            in_rate.frame_rate_den = 1;
            break;
    }
    printf(" -> ");
    switch (bw_out) {
         case HW_API::BW_1920_1200P60:
            printf("1920x1200p60\n");
            out_hdmi_params.appl = 1920;
            out_hdmi_params.tppl = 2080;
            out_hdmi_params.hs_width = 32;
            out_hdmi_params.hs_front_porch = 48;
            out_hdmi_params.hs_back_porch = 80;
            out_hdmi_params.alpf[0] = 1200;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1235;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 3;
            out_hdmi_params.vs_front_porch = 6;
            out_hdmi_params.vs_back_porch = 26;
            out_rate.frame_rate_num = 60;
            out_rate.frame_rate_den = 1;
            break;
       case HW_API::BW_1920_1080P24:
            printf("1920x1080p24\n");
            out_hdmi_params.appl = 1920;
            out_hdmi_params.tppl = 2750;
            out_hdmi_params.hs_width = 44;
            out_hdmi_params.hs_front_porch = 638;
            out_hdmi_params.hs_back_porch = 148;
            out_hdmi_params.alpf[0] = 1080;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1125;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5;
            out_hdmi_params.vs_front_porch = 4;
            out_hdmi_params.vs_back_porch = 36;
            out_rate.frame_rate_num = 24;
            out_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_1280_720P60:
            printf("1280x720p60\n");
            out_hdmi_params.appl = 1280;
            out_hdmi_params.tppl = 1650;
            out_hdmi_params.hs_width = 40;
            out_hdmi_params.hs_front_porch = 110;
            out_hdmi_params.hs_back_porch = 220;
            out_hdmi_params.alpf[0] = 720;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 750;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5;
            out_hdmi_params.vs_front_porch = 5;
            out_hdmi_params.vs_back_porch = 20;
            out_rate.frame_rate_num = 60;
            out_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_640_480P60:
            printf("640x480p60\n");
            out_hdmi_params.appl = 640;
            out_hdmi_params.tppl = 800;
            out_hdmi_params.hs_width = 96;
            out_hdmi_params.hs_front_porch = 24;
            out_hdmi_params.hs_back_porch = 40;
            out_hdmi_params.alpf[0] = 480;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 525;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 2;
            out_hdmi_params.vs_front_porch = 18;
            out_hdmi_params.vs_back_porch = 25;
            out_rate.frame_rate_num = 60;
            out_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_1920_1080I60:
            printf("1080i60\n");
            out_hdmi_params.appl = 1920;
            out_hdmi_params.tppl = 2200;
            out_hdmi_params.hs_width = 44;
            out_hdmi_params.hs_front_porch = 88;
            out_hdmi_params.hs_back_porch = 148;
            out_hdmi_params.alpf[0] = 540;
            out_hdmi_params.alpf[1] = 540;
            out_hdmi_params.tlpf[0] = 562;
            out_hdmi_params.tlpf[1] = 563;
            out_hdmi_params.vs_width = 5;
            out_hdmi_params.vs_front_porch = 2;
            out_hdmi_params.vs_back_porch = 15;
            out_rate.frame_rate_num = 60;
            out_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_3840_2160P30:
            printf("2160p30\n");
            out_hdmi_params.appl = 1920*2;
            out_hdmi_params.tppl = 2200*2;
            out_hdmi_params.hs_width = 44*2;
            out_hdmi_params.hs_front_porch = 88*2;
            out_hdmi_params.hs_back_porch = 148*2;
            out_hdmi_params.alpf[0] = 1080*2;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1125*2;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5*2;
            out_hdmi_params.vs_front_porch = 4*2;
            out_hdmi_params.vs_back_porch = 36*2;
            out_rate.frame_rate_num = 30;
            out_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_3840_2160P60:
            printf("2160p60\n");
            out_hdmi_params.appl = 1920*2;
            out_hdmi_params.tppl = 2200*2;
            out_hdmi_params.hs_width = 44*2;
            out_hdmi_params.hs_front_porch = 88*2;
            out_hdmi_params.hs_back_porch = 148*2;
            out_hdmi_params.alpf[0] = 1080*2;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1125*2;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5*2;
            out_hdmi_params.vs_front_porch = 4*2;
            out_hdmi_params.vs_back_porch = 36*2;
            out_rate.frame_rate_num = 60;
            out_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_3840_2160P24:
            printf("2160p24\n");
            out_hdmi_params.appl = 1920*2;
            out_hdmi_params.tppl = 2750*2;
            out_hdmi_params.hs_width = 44*2;
            out_hdmi_params.hs_front_porch = 638*2;
            out_hdmi_params.hs_back_porch = 148*2;
            out_hdmi_params.alpf[0] = 1080*2;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1125*2;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5*2;
            out_hdmi_params.vs_front_porch = 4*2;
            out_hdmi_params.vs_back_porch = 36*2;
            out_rate.frame_rate_num = 24;
            out_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_3840_2160P23_98:
            printf("2160p23.98\n");
            out_hdmi_params.appl = 1920*2;
            out_hdmi_params.tppl = 2750*2;
            out_hdmi_params.hs_width = 44*2;
            out_hdmi_params.hs_front_porch = 638*2;
            out_hdmi_params.hs_back_porch = 148*2;
            out_hdmi_params.alpf[0] = 1080*2;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1125*2;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5*2;
            out_hdmi_params.vs_front_porch = 4*2;
            out_hdmi_params.vs_back_porch = 36*2;
            out_rate.frame_rate_num = 24000;
            out_rate.frame_rate_den = 1001;
            break;
        case HW_API::BW_3840_2160P59_94:
            printf("2160p59.94\n");
            out_hdmi_params.appl = 1920*2;
            out_hdmi_params.tppl = 2200*2;
            out_hdmi_params.hs_width = 44*2;
            out_hdmi_params.hs_front_porch = 88*2;
            out_hdmi_params.hs_back_porch = 148*2;
            out_hdmi_params.alpf[0] = 1080*2;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1125*2;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5*2;
            out_hdmi_params.vs_front_porch = 4*2;
            out_hdmi_params.vs_back_porch = 36*2;
            out_rate.frame_rate_num = 60000;
            out_rate.frame_rate_den = 1001;
            break;
        case HW_API::BW_3840_2160P29_98:
            printf("2160p29.98\n");
            out_hdmi_params.appl = 1920*2;
            out_hdmi_params.tppl = 2200*2;
            out_hdmi_params.hs_width = 44*2;
            out_hdmi_params.hs_front_porch = 88*2;
            out_hdmi_params.hs_back_porch = 148*2;
            out_hdmi_params.alpf[0] = 1080*2;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1125*2;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5*2;
            out_hdmi_params.vs_front_porch = 4*2;
            out_hdmi_params.vs_back_porch = 36*2;
            out_rate.frame_rate_num = 30000;
            out_rate.frame_rate_den = 1001;
            break;
        case HW_API::BW_1920_1080P59_94:
            printf("1080p59.94\n");
            out_hdmi_params.appl = 1920;
            out_hdmi_params.tppl = 2200;
            out_hdmi_params.hs_width = 44;
            out_hdmi_params.hs_front_porch = 88;
            out_hdmi_params.hs_back_porch = 148;
            out_hdmi_params.alpf[0] = 1080;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1125;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5;
            out_hdmi_params.vs_front_porch = 4;
            out_hdmi_params.vs_back_porch = 36;
            out_rate.frame_rate_num = 60000;
            out_rate.frame_rate_den = 1001;
            break;
        case HW_API::BW_1920_1080P30:
            printf("1080p30\n");
            out_hdmi_params.appl = 1920;
            out_hdmi_params.tppl = 2200;
            out_hdmi_params.hs_width = 44;
            out_hdmi_params.hs_front_porch = 88;
            out_hdmi_params.hs_back_porch = 148;
            out_hdmi_params.alpf[0] = 1080;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1125;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5;
            out_hdmi_params.vs_front_porch = 4;
            out_hdmi_params.vs_back_porch = 36;
            out_rate.frame_rate_num = 30;
            out_rate.frame_rate_den = 1;
            break;
        case HW_API::BW_1920_1080P60:
        default:
            printf("1080p60\n");
            out_hdmi_params.appl = 1920;
            out_hdmi_params.tppl = 2200;
            out_hdmi_params.hs_width = 44;
            out_hdmi_params.hs_front_porch = 88;
            out_hdmi_params.hs_back_porch = 148;
            out_hdmi_params.alpf[0] = 1080;
            out_hdmi_params.alpf[1] = 0;
            out_hdmi_params.tlpf[0] = 1125;
            out_hdmi_params.tlpf[1] = 0;
            out_hdmi_params.vs_width = 5;
            out_hdmi_params.vs_front_porch = 4;
            out_hdmi_params.vs_back_porch = 36;
            out_rate.frame_rate_num = 60;
            out_rate.frame_rate_den = 1;
            break;
    }
    sc_settings.crop_top = 0;
    sc_settings.crop_left = 0;
    sc_settings.crop_height = 0;
    sc_settings.crop_width = 0;
    sc_settings.aspect_mode = HW_API::ASPECT_FIT;
    sc_settings.brdr_yg = 0x00;
    sc_settings.brdr_cbb = 0x00;
    sc_settings.brdr_crr = 0x00;
    HW_API::switchScalerInput(path, in_hdmi_params, in_rate, colour_inp);
    HW_API::switchScalerPathSettings(path, &sc_settings);
    HW_API::initVidProc();
    HW_API::setScalerOutput(path, out_hdmi_params, out_rate, colour_out);
    HW_API::useScalerPath(path, true);
    HW_API::dumpScalerConfig(path);
    HW_API::dumpScalerStatus(path);

    RasterTypes::RasterParameters out_raster;
    HW_API::getScalerPlayoutRaster(path,&out_raster);
    printf("\n");
    printf("out_raster.h_act_start = %u\n",out_raster.h_act_start);
    printf("out_raster.h_act_stop = %u\n",out_raster.h_act_stop);
    printf("\n");

    return;
}

void
HW_API::bistHdmiTx(uint32_t txchan, HW_API::bwBIST bw_out, bool fractional, HW_API::scColourFormat_type colour, uint32_t bits_per_component){
  HW_API::initHdmi(txchan);
  assert(HW_API::getHdmiInitDone(txchan));

  printf("Setting up HDMI TX %u to: ", txchan);
  HDMI_Xil_Type::VideoStream_type videostream;
  uint8_t videoIDCode;

  bool dviMode = false;
  uint8_t lte_340mcsc_scramble = 0;
  uint8_t max_tmds_character_rate = 120;
  uint8_t max_tmds_clock = 60;
  bool sendBasicInfoFrames = true;

  switch (bw_out){
    case HW_API::BW_1280_720P60:
      printf("1280x720p60.\n");
      videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
      videostream.PixPerClk = HDMI_Xil_Type::PPC_2;
      videostream.FrameRate = HDMI_Xil_Type::FR_60HZ;
      videostream.Info_3D.Format = HDMI_Xil_Type::FORMAT_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Method = HDMI_Xil_Type::SAMPLING_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Position = HDMI_Xil_Type::SAMPPOS_3D_UNKNOWN;
      videoIDCode = 0;
      videostream.Timing.HActive        = 1280;
      videostream.Timing.HFrontPorch    = 110;
      videostream.Timing.HSyncWidth     = 40;
      videostream.Timing.HBackPorch     = 220;
      videostream.Timing.HTotal         = 1650;
      videostream.Timing.VActive        = 720;
      videostream.Timing.F0PVFrontPorch = 4;
      videostream.Timing.F0PVSyncWidth  = 5;
      videostream.Timing.F0PVBackPorch  = 20;
      videostream.Timing.F0PVTotal      = 1650;
      videostream.Timing.F1VFrontPorch  = 0;
      videostream.Timing.F1VSyncWidth   = 0;
      videostream.Timing.F1VBackPorch   = 0;
      videostream.Timing.F1VTotal       = 0;
      videostream.Timing.HSyncPolarity  = 1;
      videostream.Timing.VSyncPolarity  = 1;
      videostream.IsInterlaced          = 0;
      videostream.Is3D                  = 0;
      break;
    case HW_API::BW_1920_1080P24:
      printf("1920x1080p24.\n");
      videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
      videostream.PixPerClk = HDMI_Xil_Type::PPC_2;
      videostream.FrameRate = HDMI_Xil_Type::FR_24HZ;
      videostream.Info_3D.Format = HDMI_Xil_Type::FORMAT_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Method = HDMI_Xil_Type::SAMPLING_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Position = HDMI_Xil_Type::SAMPPOS_3D_UNKNOWN;
      videoIDCode = 0;
      videostream.Timing.HActive        = 1920;
      videostream.Timing.HFrontPorch    = 638;
      videostream.Timing.HSyncWidth     = 44;
      videostream.Timing.HBackPorch     = 148;
      videostream.Timing.HTotal         = 2750;
      videostream.Timing.VActive        = 1080;
      videostream.Timing.F0PVFrontPorch = 4;
      videostream.Timing.F0PVSyncWidth  = 5;
      videostream.Timing.F0PVBackPorch  = 36;
      videostream.Timing.F0PVTotal      = 1125;
      videostream.Timing.F1VFrontPorch  = 0;
      videostream.Timing.F1VSyncWidth   = 0;
      videostream.Timing.F1VBackPorch   = 0;
      videostream.Timing.F1VTotal       = 0;
      videostream.Timing.HSyncPolarity  = 1;
      videostream.Timing.VSyncPolarity  = 1;
      videostream.IsInterlaced          = 0;
      videostream.Is3D                  = 0;
      break;
    case HW_API::BW_1920_1200P60:
      printf("1920x1200p60.\n");
      videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
      videostream.PixPerClk = HDMI_Xil_Type::PPC_2;
      videostream.FrameRate = HDMI_Xil_Type::FR_60HZ;
      videostream.Info_3D.Format = HDMI_Xil_Type::FORMAT_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Method = HDMI_Xil_Type::SAMPLING_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Position = HDMI_Xil_Type::SAMPPOS_3D_UNKNOWN;
      videoIDCode = 0;
      videostream.Timing.HActive        = 1920;
      videostream.Timing.HFrontPorch    = 48;
      videostream.Timing.HSyncWidth     = 32;
      videostream.Timing.HBackPorch     = 80;
      videostream.Timing.HTotal         = 2080;
      videostream.Timing.VActive        = 1200;
      videostream.Timing.F0PVFrontPorch = 3;
      videostream.Timing.F0PVSyncWidth  = 6;
      videostream.Timing.F0PVBackPorch  = 26;
      videostream.Timing.F0PVTotal      = 1235;
      videostream.Timing.F1VFrontPorch  = 0;
      videostream.Timing.F1VSyncWidth   = 0;
      videostream.Timing.F1VBackPorch   = 0;
      videostream.Timing.F1VTotal       = 0;
      videostream.Timing.HSyncPolarity  = 1;
      videostream.Timing.VSyncPolarity  = 0;
      videostream.IsInterlaced          = 0;
      videostream.Is3D                  = 0;
      break;
    case HW_API::BW_640_480P60:
      printf("640x480p60.\n");
      videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
      videostream.PixPerClk = HDMI_Xil_Type::PPC_2;
      videostream.FrameRate = HDMI_Xil_Type::FR_60HZ;
      videostream.Info_3D.Format = HDMI_Xil_Type::FORMAT_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Method = HDMI_Xil_Type::SAMPLING_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Position = HDMI_Xil_Type::SAMPPOS_3D_UNKNOWN;
      videoIDCode = 0;
      videostream.Timing.HActive        = 640;
      videostream.Timing.HFrontPorch    = 24;
      videostream.Timing.HSyncWidth     = 96;
      videostream.Timing.HBackPorch     = 40;
      videostream.Timing.HTotal         = 800;
      videostream.Timing.VActive        = 480;
      videostream.Timing.F0PVFrontPorch = 18;
      videostream.Timing.F0PVSyncWidth  = 2;
      videostream.Timing.F0PVBackPorch  = 25;
      videostream.Timing.F0PVTotal      = 525;
      videostream.Timing.F1VFrontPorch  = 0;
      videostream.Timing.F1VSyncWidth   = 0;
      videostream.Timing.F1VBackPorch   = 0;
      videostream.Timing.F1VTotal       = 0;
      videostream.Timing.HSyncPolarity  = 1;
      videostream.Timing.VSyncPolarity  = 1;
      videostream.IsInterlaced          = 0;
      videostream.Is3D                  = 0;
      break;
    case HW_API::BW_1920_1080I60:
      printf("1080i60.\n");
      videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
      videostream.PixPerClk = HDMI_Xil_Type::PPC_2;
      videostream.FrameRate = HDMI_Xil_Type::FR_60HZ;
      videostream.Info_3D.Format = HDMI_Xil_Type::FORMAT_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Method = HDMI_Xil_Type::SAMPLING_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Position = HDMI_Xil_Type::SAMPPOS_3D_UNKNOWN;
      videoIDCode = 5;
      videostream.Timing.HActive        = 1920;
      videostream.Timing.HFrontPorch    = 88;
      videostream.Timing.HSyncWidth     = 44;
      videostream.Timing.HBackPorch     = 148;
      videostream.Timing.HTotal         = 2200;
      videostream.Timing.VActive        = 540;
      videostream.Timing.F0PVFrontPorch = 2;
      videostream.Timing.F0PVSyncWidth  = 5;
      videostream.Timing.F0PVBackPorch  = 15;
      videostream.Timing.F0PVTotal      = 562;
      videostream.Timing.F1VFrontPorch  = 3;
      videostream.Timing.F1VSyncWidth   = 5;
      videostream.Timing.F1VBackPorch   = 15;
      videostream.Timing.F1VTotal       = 563;
      videostream.Timing.HSyncPolarity  = 1;
      videostream.Timing.VSyncPolarity  = 1;
      videostream.IsInterlaced          = 1;
      videostream.Is3D                  = 0;
      break;
    case HW_API::BW_3840_2160P30:
    case HW_API::BW_3840_2160P29_98:
      printf("2160p30.\n");
      videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
      videostream.PixPerClk =  HDMI_Xil_Type::PPC_2;
      videostream.FrameRate = HDMI_Xil_Type::FR_30HZ;
      videostream.Info_3D.Format = HDMI_Xil_Type::FORMAT_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Method = HDMI_Xil_Type::SAMPLING_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Position = HDMI_Xil_Type::SAMPPOS_3D_UNKNOWN;
      videoIDCode = 95;
      videostream.Timing.HActive        = 3840;
      videostream.Timing.HFrontPorch    = 176;
      videostream.Timing.HSyncWidth     = 88;
      videostream.Timing.HBackPorch     = 296;
      videostream.Timing.HTotal         = 4400;
      videostream.Timing.VActive        = 2160;
      videostream.Timing.F0PVFrontPorch = 8;
      videostream.Timing.F0PVSyncWidth  = 10;
      videostream.Timing.F0PVBackPorch  = 72;
      videostream.Timing.F0PVTotal      = 2250;
      videostream.Timing.F1VFrontPorch  = 0;
      videostream.Timing.F1VSyncWidth   = 0;
      videostream.Timing.F1VBackPorch   = 0;
      videostream.Timing.F1VTotal       = 0;
      videostream.Timing.HSyncPolarity  = 1;
      videostream.Timing.VSyncPolarity  = 1;
      videostream.IsInterlaced          = 0;
      videostream.Is3D                  = 0;
      break;
    case HW_API::BW_3840_2160P60:
    case HW_API::BW_3840_2160P59_94:
      printf("2160p60.\n");
      videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
      videostream.PixPerClk = HDMI_Xil_Type::PPC_2;
      videostream.FrameRate = HDMI_Xil_Type::FR_60HZ;
      videostream.Info_3D.Format = HDMI_Xil_Type::FORMAT_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Method = HDMI_Xil_Type::SAMPLING_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Position = HDMI_Xil_Type::SAMPPOS_3D_UNKNOWN;
      videoIDCode = 97;
      videostream.Timing.HActive        = 3840;
      videostream.Timing.HFrontPorch    = 176;
      videostream.Timing.HSyncWidth     = 88;
      videostream.Timing.HBackPorch     = 296;
      videostream.Timing.HTotal         = 4400;
      videostream.Timing.VActive        = 2160;
      videostream.Timing.F0PVFrontPorch = 8;
      videostream.Timing.F0PVSyncWidth  = 10;
      videostream.Timing.F0PVBackPorch  = 72;
      videostream.Timing.F0PVTotal      = 2250;
      videostream.Timing.F1VFrontPorch  = 0;
      videostream.Timing.F1VSyncWidth   = 0;
      videostream.Timing.F1VBackPorch   = 0;
      videostream.Timing.F1VTotal       = 0;
      videostream.Timing.HSyncPolarity  = 1;
      videostream.Timing.VSyncPolarity  = 1;
      videostream.IsInterlaced          = 0;
      videostream.Is3D                  = 0;
      break;
    case HW_API::BW_1920_1080P30:
      printf("1080p30.\n");
      videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
      videostream.PixPerClk = HDMI_Xil_Type::PPC_2;
      videostream.FrameRate = HDMI_Xil_Type::FR_30HZ;
      videostream.Info_3D.Format = HDMI_Xil_Type::FORMAT_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Method = HDMI_Xil_Type::SAMPLING_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Position = HDMI_Xil_Type::SAMPPOS_3D_UNKNOWN;
      videoIDCode = 34;
      videostream.Timing.HActive        = 1920;
      videostream.Timing.HFrontPorch    = 88;
      videostream.Timing.HSyncWidth     = 44;
      videostream.Timing.HBackPorch     = 148;
      videostream.Timing.HTotal         = 2200;
      videostream.Timing.VActive        = 1080;
      videostream.Timing.F0PVFrontPorch = 4;
      videostream.Timing.F0PVSyncWidth  = 5;
      videostream.Timing.F0PVBackPorch  = 36;
      videostream.Timing.F0PVTotal      = 1125;
      videostream.Timing.F1VFrontPorch  = 0;
      videostream.Timing.F1VSyncWidth   = 0;
      videostream.Timing.F1VBackPorch   = 0;
      videostream.Timing.F1VTotal       = 0;
      videostream.Timing.HSyncPolarity  = 1;
      videostream.Timing.VSyncPolarity  = 1;
      videostream.IsInterlaced          = 0;
      videostream.Is3D                  = 0;
      break;
    case HW_API::BW_3840_2160P24:
    case HW_API::BW_3840_2160P23_98:
      printf("2160p24.\n");
      videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
      videostream.PixPerClk = HDMI_Xil_Type::PPC_2;
      videostream.FrameRate = HDMI_Xil_Type::FR_24HZ;
      videostream.Info_3D.Format = HDMI_Xil_Type::FORMAT_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Method = HDMI_Xil_Type::SAMPLING_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Position = HDMI_Xil_Type::SAMPPOS_3D_UNKNOWN;
      videoIDCode = 93;
      videostream.Timing.HActive        = 3840;
      videostream.Timing.HFrontPorch    = 1276;
      videostream.Timing.HSyncWidth     = 88;
      videostream.Timing.HBackPorch     = 296;
      videostream.Timing.HTotal         = 5500;
      videostream.Timing.VActive        = 2160;
      videostream.Timing.F0PVFrontPorch = 8;
      videostream.Timing.F0PVSyncWidth  = 10;
      videostream.Timing.F0PVBackPorch  = 72;
      videostream.Timing.F0PVTotal      = 2250;
      videostream.Timing.F1VFrontPorch  = 0;
      videostream.Timing.F1VSyncWidth   = 0;
      videostream.Timing.F1VBackPorch   = 0;
      videostream.Timing.F1VTotal       = 0;
      videostream.Timing.HSyncPolarity  = 1;
      videostream.Timing.VSyncPolarity  = 1;
      videostream.IsInterlaced          = 0;
      videostream.Is3D                  = 0;
      break;
    case HW_API::BW_1920_1080P59_94:
    case HW_API::BW_1920_1080P60:
    default:
      printf("1080p60.\n");
      videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
      videostream.PixPerClk = HDMI_Xil_Type::PPC_2;
      videostream.FrameRate = HDMI_Xil_Type::FR_60HZ;
      videostream.Info_3D.Format = HDMI_Xil_Type::FORMAT_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Method = HDMI_Xil_Type::SAMPLING_3D_UNKNOWN;
      videostream.Info_3D.Sampling.Position = HDMI_Xil_Type::SAMPPOS_3D_UNKNOWN;
      videoIDCode = 16;
      videostream.Timing.HActive        = 1920;
      videostream.Timing.HFrontPorch    = 88;
      videostream.Timing.HSyncWidth     = 44;
      videostream.Timing.HBackPorch     = 148;
      videostream.Timing.HTotal         = 2200;
      videostream.Timing.VActive        = 1080;
      videostream.Timing.F0PVFrontPorch = 4;
      videostream.Timing.F0PVSyncWidth  = 5;
      videostream.Timing.F0PVBackPorch  = 36;
      videostream.Timing.F0PVTotal      = 1125;
      videostream.Timing.F1VFrontPorch  = 0;
      videostream.Timing.F1VSyncWidth   = 0;
      videostream.Timing.F1VBackPorch   = 0;
      videostream.Timing.F1VTotal       = 0;
      videostream.Timing.HSyncPolarity  = 1;
      videostream.Timing.VSyncPolarity  = 1;
      videostream.IsInterlaced          = 0;
      videostream.Is3D                  = 0;
      break;
  }
  videostream.ColourFormatId = (HDMI_Xil_Type::ColourFormat_type)colour;
  printf("videostream.ColourFormatId = %u\n",(uint32_t)videostream.ColourFormatId);

  if  (bits_per_component == 8) {
    videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
    printf("Bits per Component = %u\n",bits_per_component);
  } else if (bits_per_component == 10) {
    videostream.ColourDepth = HDMI_Xil_Type::BPC_10;
    printf("Bits per Component = %u\n",bits_per_component);
  } else if (bits_per_component == 12) {
    videostream.ColourDepth = HDMI_Xil_Type::BPC_12;
    printf("Bits per Component = %u\n",bits_per_component);
  } else if (bits_per_component == 16) {
    videostream.ColourDepth = HDMI_Xil_Type::BPC_16;
    printf("Bits per Component = %u\n",bits_per_component);
  } else {
    videostream.ColourDepth = HDMI_Xil_Type::BPC_8;
    printf("Bits per component invalid, 8,10,12,16 bits supported\n");
  }

  if (HW_API::getHdmiTxVideoConfigValid(txchan, &videostream, videoIDCode, dviMode, lte_340mcsc_scramble, max_tmds_character_rate, max_tmds_clock, fractional) != HDMI_Xil_Type::RET_SUCCESS)
  {
    printf("WARNING: getHdmiTxVideoConfigValid failed!\n");
    return;
  }

  HW_API::setHdmiTxVideoConfig(txchan, &videostream, videoIDCode, dviMode, lte_340mcsc_scramble, max_tmds_character_rate, max_tmds_clock, sendBasicInfoFrames, fractional);
  HW_API::setHdmiTxInfoFramesInitialized(txchan);
  return;
}

void
HW_API::bistHdmiLoopback(uint32_t rxchan, uint32_t txchan, HW_API::bwBIST bw){
  HW_API::initHdmi(rxchan);
  HW_API::initHdmi(txchan);

  /* Check that Rx is Connected */
  if (!HW_API::getHdmiRxIsConnected(rxchan)) {
    printf("Channel %u Rx cable not connected!\n", rxchan);
    return;
  }
  /* Check that Tx is Connected */
  if (!HW_API::getHdmiTxIsConnected(txchan)) {
    printf("Channel %u Tx cable not connected!\n", txchan);
    return;
  }
  /* Validate the Scaler Path */
  uint32_t path = txchan;
  if (path >= (uint32_t)HW_API::getFPGACapability("N_SCALER"))
  {
    printf("Scaler Path %u is out of range, overriding Path to 0!\n", path);
    path = 0;
  }
  /* Copy the EDID from Tx to Rx */
  uint8_t edid[256];
  uint32_t size;
  uint8_t valid;
  if (HW_API::getHdmiTxEDID(txchan, edid, &size, &valid) != HDMI_Xil_Type::RET_SUCCESS) {
    printf("getHdmiTxEDID failed!\n");
    return;
  }
  if (HW_API::setHdmiRxEDID(rxchan, edid, size) != HDMI_Xil_Type::RET_SUCCESS) {
    printf("setHdmiRxEDID failed!\n");
    return;
  }
  /* Enable video through the HDMI Rx */
  HW_API::setHdmiRxOutputEnable(rxchan);
  bool fractional;
  HW_API::getHdmiRxVideoFractional(rxchan, &fractional);
  /* Route the HDMI to/from the Scaler */
  HW_API::setVideoXbarSel(VID_OUT_SCALER0+path, VID_IN_HDMI0+rxchan);
  if (HW_API::getFPGACapability("INC_META_XBAR") > 0)
  {
    HW_API::setMetaXbarSel(META_OUT_SCALER0+path, META_IN_HDMI0+rxchan);
  }
  /* Configure the Scaler */
  HW_API::bistScaler(path, bw, bw);
  HW_API::setRefClkenSource(path, txchan);
  HW_API::setLossofInput(path, false);
  /* Configure the HDMI Tx */
  HW_API::setHdmiTxInfoFramesInitialized(txchan);
  HW_API::bistHdmiTx(txchan, bw, fractional);
  return;
}

void
HW_API::bistHdmiLink(uint32_t rxchan, uint32_t txchan, HW_API::bwBIST bw, uint32_t path, uint8_t* edid, bool fast){
  HW_API::initHdmi(rxchan);
  HW_API::initHdmi(txchan);
  uint32_t num_iterations = 40;

  printf("Running HDMI Link Test.\n");
  printf("Please ensure cables are connected direction from HDMI Tx %u to HDMI Rx %u.\n", txchan, rxchan);
  /* Check that Rx is Connected */
  if (!HW_API::getHdmiRxIsConnected(rxchan)) {
    printf("Channel %u Rx cable not connected!\n", rxchan);
    return;
  }
  /* Set the EDID */
  uint32_t size = 256;
  printf("Setting Default EDID.\n");
  if (HW_API::setHdmiRxEDID(rxchan, edid, size) != HDMI_Xil_Type::RET_SUCCESS) {
    printf("Setting Default EDID Failed!\n");
    return;
  }
  /* Wait for HPD to be active */
  printf("Wait for HDMI Tx %u HPD to be active...", txchan);
  /* Check that Tx is Connected */
  for (uint32_t i=0; i<=num_iterations;i++) {
    if (HW_API::getHdmiTxIsConnected(txchan))
    {
      printf("Done.\n");
      break;
    } else if (i == num_iterations){
      printf("\nFailed to detect HPD.\n");
      return;
    } else {
      printf(".");
      fflush(stdout);
      usleep(500000);
    }
  }

  /* Enable video through the HDMI Rx */
  HW_API::setHdmiRxOutputEnable(rxchan);
  /* Route the HDMI to/from the Scaler in a loop */
  HW_API::setVideoXbarSel(VID_OUT_SCALER0+path, VID_IN_HDMI0+rxchan);
  if (HW_API::getFPGACapability("INC_META_XBAR") > 0)
  {
    HW_API::setMetaXbarSel(META_OUT_SCALER0+path, META_IN_HDMI0+rxchan);
  }
  /* Configure the Scaler */
  HW_API::bistScaler(path, bw, bw);
  HW_API::setRefClkenSource(path, txchan);
  /* Show LOI Raster */
  HW_API::setLossofInputColour(path, HW_API::RGB444_GREY);
  HW_API::setLossofInput(path, true);
  /* Configure the HDMI Tx */
  HW_API::setHdmiTxInfoFramesInitialized(txchan);
  printf("Start the HDMI Tx.\n");
  HW_API::bistHdmiTx(txchan, bw, false);
  usleep (2000000);
  HW_API::bistHdmiTx(txchan, bw, false);
  usleep (2000000);
  HW_API::bistHdmiTx(txchan, bw, false);
  usleep (2000000);
  HW_API::bistHdmiTx(txchan, bw, false);
  usleep (2000000);
  HW_API::bistHdmiTx(txchan, bw, false);

  /* Wait for the links to settle */
  printf("Wait for HDMI Tx %u to come up...", txchan);
  /* Check that Tx Stream is Up */
  for (uint32_t i=0; i<=num_iterations;i++) {
    if (HW_API::getHdmiTxStreamIsUp(txchan))
    {
      printf("Done.\n");
      break;
    } else if (i == num_iterations){
      printf("\nFailed to establish Tx link.\n");
      return;
    } else {
      printf(".");
      fflush(stdout);
      usleep(500000);
    }
  }
  printf("Wait for HDMI Rx %u to come up...", rxchan);
  /* Check that Rx Stream is Up */
  for (uint32_t i=0; i<=num_iterations;i++) {
    if (HW_API::getHdmiRxStreamIsUp(rxchan))
    {
      printf("Done.\n");
      break;
    } else if (i == num_iterations/2){
      printf("Resetting link.\n");
      HW_API::bistHdmiTx(txchan, bw, false);
    } else if (i == num_iterations){
      printf("\nFailed to establish Rx link.\n");
      return;
    } else {
      printf(".");
      fflush(stdout);
      usleep(500000);
    }
  }
  /* Let the link settle for another 2s */
  usleep(2000000);

  /* Run the test */
  printf("Running HDMI Tx %u -> Rx %u Link Tests...\n", txchan, rxchan);
  uint8_t result = 0;
  HW_API::setLossofInputColour(path, HW_API::RGB444_RED);
  result += HW_API::bistHdmiRxLinkError(rxchan,fast);
  HW_API::setLossofInputColour(path, HW_API::RGB444_GREEN);
  result += HW_API::bistHdmiRxLinkError(rxchan,fast);
  HW_API::setLossofInputColour(path, HW_API::RGB444_BLUE);
  result += HW_API::bistHdmiRxLinkError(rxchan,fast);

  HW_API::setLossofInputColour(path, HW_API::RGB444_WHITE);
  printf("\nHDMI Link Test Result: %s.\n\n", (result == 0 ? "PASS" : "FAIL"));
  return;
}

bool
HW_API::bistHdmiRxLinkError(uint32_t rxchan, bool fast){
  HW_API::initHdmi(rxchan);
  uint32_t link[3] = {0};
  uint32_t link_min[3] = {0};
  uint32_t link_average[3] = {0};
  uint32_t link_max[3] = {0};
  uint32_t num_iterations = 10000;
  /* False = No errors, True = Errors */
  bool result = false;
  if (fast)
  {
    num_iterations = 1000;
  }
  /* Check that Rx is Connected */
  if (!HW_API::getHdmiRxIsConnected(rxchan)) {
    printf("Channel %u Rx cable not connected!\n", rxchan);
    result = true;
    return result;
  }
  for (uint32_t i=1; i<num_iterations;i++)
  {
    HW_API::getHdmiRxLinkStatusError(rxchan, &link[0], &link[1], &link[2]);
    for (uint32_t j=0; j<=2;j++)
    {
      if (link[j] < link_min[j])
      {
        link_min[j] = link[j];
      }
      if (link[j] > link_max[j])
      {
        link_max[j] = link[j];
      }
      link_average[j] = ((link_average[j]*(i-1))+link[j])/i;
    }
    usleep(1000);
  }
  printf("Channel %u Rx Link Error Statistics:\n", rxchan);
  printf("  Rx Link 0 Error Min: %d, Average: %d, Max: %d\n", link_min[0], link_average[0], link_max[0]);
  printf("  Rx Link 1 Error Min: %d, Average: %d, Max: %d\n", link_min[1], link_average[1], link_max[1]);
  printf("  Rx Link 2 Error Min: %d, Average: %d, Max: %d\n", link_min[2], link_average[2], link_max[2]);

  if ((link_max[0] + link_max[1] + link_max[2]) > 10)
  {
    result = true;
  }
  return result;
}

void
HW_API::bistGearboxRx(HW_API::bwBIST bw, HW_API::scColourFormat_type colour) {
    uint32_t path = 0;
    if (!HW_API::getScalerArchMatch("QUAD_DUAL_POST")) {
      printf("Scaler architecture must be QUAD_DUAL_POST!\n");
      return;
    }
    printf("Initializing Gearbox Rx with known good defaults:\n");
    // Init
    printf("  Initializing gearbox...");
    HW_API::initScalerPath(path);
    assert(HW_API::getScalerPathInitDone(path));
    printf("Done.\n");

    printf("  Setting up gearbox to output ");
    RasterTypes::CVTParameters hdmi_params;
    HW_API::ScalerSettings sc_settings;
    HW_API::ScalerFrameRate rate;
    switch (bw) {
        case HW_API::BW_3840_2160P30:
            printf("2160p30\n");
            hdmi_params.appl = 1920*2;
            hdmi_params.tppl = 2200*2;
            hdmi_params.hs_width = 44*2;
            hdmi_params.hs_front_porch = 88*2;
            hdmi_params.hs_back_porch = 148*2;
            hdmi_params.alpf[0] = 1080*2;
            hdmi_params.alpf[1] = 0;
            hdmi_params.tlpf[0] = 1125*2;
            hdmi_params.tlpf[1] = 0;
            hdmi_params.vs_width = 5*2;
            hdmi_params.vs_front_porch = 4*2;
            hdmi_params.vs_back_porch = 36*2;
            rate.frame_rate_num = 30;
            rate.frame_rate_den = 1;
            break;
        case HW_API::BW_3840_2160P60:
        default:
            printf("2160p60\n");
            hdmi_params.appl = 1920*2;
            hdmi_params.tppl = 2200*2;
            hdmi_params.hs_width = 44*2;
            hdmi_params.hs_front_porch = 88*2;
            hdmi_params.hs_back_porch = 148*2;
            hdmi_params.alpf[0] = 1080*2;
            hdmi_params.alpf[1] = 0;
            hdmi_params.tlpf[0] = 1125*2;
            hdmi_params.tlpf[1] = 0;
            hdmi_params.vs_width = 5*2;
            hdmi_params.vs_front_porch = 4*2;
            hdmi_params.vs_back_porch = 36*2;
            rate.frame_rate_num = 60;
            rate.frame_rate_den = 1;
            break;
    }
    sc_settings.crop_top = 0;
    sc_settings.crop_left = 0;
    sc_settings.crop_height = 0;
    sc_settings.crop_width = 0;
    sc_settings.aspect_mode = HW_API::ASPECT_FIT;
    sc_settings.brdr_yg = 0x00;
    sc_settings.brdr_cbb = 0x00;
    sc_settings.brdr_crr = 0x00;
    HW_API::switchScalerInput(path, hdmi_params, rate, colour);
    HW_API::switchScalerPathSettings(path, &sc_settings);
    HW_API::initVidProc();
    HW_API::setScalerOutput(path, hdmi_params, rate, colour);
    HW_API::useScalerPath(path, true);
    HW_API::dumpScalerConfig(path);
    HW_API::dumpScalerStatus(path);
    return;
}

/* -- AXI DMA Memory Interface -- */

ZYNQAxiDmaMemory AxiDmaMemory[HW_API::N_MEM_BANKS];

void
HW_API::initAxiDmaMemory(){
  if (HW_API::getFPGACapability("INC_AXI_MEM_DMA") <= 0) {
    printf("INC_AXI_MEM_DMA is required but not included!\n");
    return;
  }
  if ((HW_API::getFPGACapability("INC_DDR3A") <= 0) &&
      (HW_API::getFPGACapability("INC_DDR3B") <= 0)) {
    printf("INC_DDR3A or INC_DDR3B is required but not included!\n");
    return;
  }
  if (HW_API::getFPGACapability("INC_DDR3A") > 0) {
    AxiDmaMemory[0].init(0);
  }
  if (HW_API::getFPGACapability("INC_DDR3B") > 0) {
    AxiDmaMemory[1].init(1);
  }
  return;
}

bool
HW_API::getInitAxiDmaMemoryDone(uint32_t index){
  if (index >= HW_API::N_MEM_BANKS) {
    printf("AXI DMA Index Out of Bounds!\n");
    return false;
  }
  return AxiDmaMemory[index].getInitDone();
}

uint32_t
HW_API::setAxiDmaMemoryDmaReadToDdrWrite(uint32_t index, uint32_t rd_src_addr, uint32_t wr_dst_addr, uint32_t wr_burst_size_in_bytes, uint32_t bytes_to_transfer) {
  assert(HW_API::getInitAxiDmaMemoryDone(index));
  return AxiDmaMemory[index].DmaReadToDdrWrite(rd_src_addr, wr_dst_addr, wr_burst_size_in_bytes, bytes_to_transfer);
}

BitmapConvert bitmapConvert;
uint32_t*
HW_API::convertMemoryFrame(uint32_t scaler_path, uint32_t height, uint32_t width, unsigned char* buffer_24, uint32_t* buf_size_p) {
  //pixel is always come in 8b array, with R in 1st element, G in 2nd element and B in 3rd element
  //buffer_24 size = height*width*3

  // Convert color space based on scaler parameters
  if (height > HW_API::getScalerMaxALPF(scaler_path)) {
    printf("Vertical size exceeds the maximum allowable lines per frame.\n");
    return NULL;
  }
  if (width > HW_API::getScalerMaxASPL(scaler_path)) {
    printf("Horizontal size exceeds the maximum allowable pixels per line.\n");
    return NULL;
  }

  uint32_t  length        = height*width*3;
  uint32_t* pixels        = NULL;
  uint32_t  bitsPerPixel;
  if (HW_API::getScalerYCbCrNotRGB(scaler_path)) {
    pixels = bitmapConvert.convert_rgb24_to_ycbcr16(buffer_24, length);
    bitsPerPixel = 16;
  } else {
    pixels = bitmapConvert.convert_24bit_to_30bit(buffer_24, length);
    bitsPerPixel = 30;
  }

  uint32_t pixelMask;
  // Only 16 or 24 or 30 bits per pixel is currently supported
  switch (bitsPerPixel) {
    case 16:
      pixelMask = 0x0000ffff;
      break;
    case 30:
      pixelMask = 0x3fffffff;
      break;
    default:
      printf("bitsPerPixel is not supported.\n");
      break;
  }

  uint32_t pixelsPerBurst = HW_API::getScalerPixelsPerReadBurst(scaler_path);
  uint32_t burstBytes = HW_API::getScalerSDRAMRPortWidth(scaler_path)/8;
  uint32_t maxBurstsPerLine = HW_API::getScalerMaxReadBurstsPerLine(scaler_path);

  const uint32_t buf_size_out = height*maxBurstsPerLine*burstBytes;
  uint32_t* buffer_out = (uint32_t*)malloc(buf_size_out);
  if (!buffer_out) {
    printf("Failed to allocate buffer for frame buffer image.\n");
    return NULL;
  }
  uint32_t* bytesArray  = buffer_out;

  // Determine how many active bursts in this row
  uint32_t activeBurstsThisRow;
  activeBurstsThisRow = width%pixelsPerBurst?
                        width/pixelsPerBurst+1:
                        width/pixelsPerBurst;

  // Iterate over number of lines
  for (uint32_t row = 0; row < height; row++) {
    // Write the active pixel of each line
    for (uint32_t burst = 0; burst < activeBurstsThisRow; burst++) {
      // Create a 32b temp buffer with a burst size
      uint32_t data[burstBytes/sizeof(uint32_t)] = {0};
      uint32_t* data_p = data;
      // Determine how many pixels in this burst
      uint32_t pixelsThisBurst;
      if ((burst == activeBurstsThisRow-1) && (width%pixelsPerBurst != 0)) {
        // Final burst in a row and it's not a full one
        pixelsThisBurst = width%pixelsPerBurst;
      } else {
        pixelsThisBurst = pixelsPerBurst;
      } // if

      // Build up a burst use pixel words. A burst is stored into a data array of uint32_t.
      // 2 cases: 16bpp x 1 (pixel_per_word=1) fill up 128b burst, or 30bpp x 2 or 30bpp x4 fill up 512b burst
      switch (bitsPerPixel) {
        case 16:
          *data_p  = *pixels & pixelMask;
          for (uint32_t i = 1; i < 8; i++) {
            pixels++;
            if (i == pixelsThisBurst) goto next_loop;
            if (i%2 != 0) {
              *data_p |= (*pixels & pixelMask) << 16;
              data_p++;
            } else {
              *data_p = (*pixels & pixelMask);
            }
          }
          pixels++;
          break;
        case 30:
          *data_p  = *pixels & pixelMask;
          for (uint32_t i = 1; i < 16; i++) {
            pixels++;
            if (i == pixelsThisBurst) goto next_loop;
            *data_p |= (*pixels & pixelMask) << (2*16-2*i);
            data_p++;
            if (i < 15) {
              *data_p  = (*pixels & pixelMask) >> (2*i);
            }
          }
          data_p++;
          data_p++; // leave last word in burst empty
          pixels++;
          break;
        default:
          break;
          next_loop:
            continue;
      } // switch

      // assign data array to output array
      for (uint32_t w =0; w < sizeof(data)/sizeof(uint32_t); w++) {
        *bytesArray = data[w];
        bytesArray++;
        }
    }

    // Fill the non-active line with 0
    for (uint32_t burst = activeBurstsThisRow; burst < maxBurstsPerLine; burst++) {
      // Create a 32b temp buffer with a burst size fill with 0
      uint32_t data[burstBytes/sizeof(uint32_t)] = {0};
      // assign data array to output array
      for (uint32_t w =0; w < sizeof(data)/sizeof(uint32_t); w++) {
        *bytesArray = data[w];
        bytesArray++;
        }
     }
  }

  // Assign pointers.
  *buf_size_p = buf_size_out/sizeof(uint32_t);

  return buffer_out;
}

uint32_t*
HW_API::writeAxiDmaMemoryConvertBmpFormat(uint32_t scaler_path, const char *bmp_file_input, const char *frame_file_output)
{
  // Load bitmap image from input file.
  uint32_t height;
  uint32_t width;
  unsigned char *buffer_24 = NULL;
  buffer_24 = bitmapConvert.load_bitmap_file(bmp_file_input, &height, &width);

  // Convert image to the "frame buffer" format.
  uint32_t *myArray = NULL;
  uint32_t buf_size_out;
  myArray = HW_API::convertMemoryFrame(scaler_path, height, width, buffer_24, &buf_size_out);
  free(buffer_24);

  // Write "frame buffer" image to output file.
  FILE * filePtr;
  uint32_t* myArray_p = myArray;
  filePtr = fopen(frame_file_output,"wb");
  fwrite(myArray_p, sizeof(uint32_t), buf_size_out, filePtr);
  fclose(filePtr);

  return myArray;
}

uint32_t
HW_API::getScalerFrameBufferPageAddress(uint32_t scaler_path, uint8_t page, uint8_t* ddr_bank, uint32_t* address) {
  // Project-specific DDR bank mapping by scaler index.
  uint8_t bank = 0; // Always bank 0

  // Update the scaler index based on the project-specific bank.
  uint32_t path = scaler_path; // Always on bank 0, so keep index the same.

  // Project-specific number of frame buffer pages per frame buffer.
  uint8_t max_page = 4;

  if(page >= max_page) {
    return -1;
  }

  // Calculate the scaler addressing bits.
  uint32_t burst_bits = log2(HW_API::getScalerSDRAMRPortWidth(scaler_path) / HW_API::getScalerSDRAMRBurstLength(scaler_path));
  uint32_t pixel_bits = log2(HW_API::getScalerMaxReadBurstsPerLine(scaler_path));
  uint32_t line_bits  = log2(HW_API::getScalerMaxALPF(scaler_path));
  uint32_t page_bits  = log2(max_page);

  // Calculate the scaler address.
  // Power of 2 addressing. path_bits are protected by max_page.
  uint32_t addr = 0;
  addr |= page << (burst_bits + pixel_bits + line_bits);
  addr |= path << (burst_bits + pixel_bits + line_bits + page_bits);

  // Assign the outputs.
  *ddr_bank = bank;
  *address  = addr;

  return 0;
}

uint32_t
HW_API::getScalerLossOfInputImageAddress(uint32_t scaler_path, uint8_t* ddr_bank, uint32_t* address) {
  // Get page for Loss of Input Image
  uint8_t page = HW_API::getScalerLossOfInputImagePage(scaler_path);

  // Calculate the address.
  return HW_API::getScalerFrameBufferPageAddress(scaler_path, page, ddr_bank, address);
}

uint32_t
HW_API::setScalerLossOfInputImage(uint32_t scaler_path, uint32_t ps_ddr_addr, uint32_t image_bytes) {
  // Get the project-specific and scaler-specific address.
  uint8_t ddr_bank = 0;
  uint32_t address = 0;
  HW_API::getScalerLossOfInputImageAddress(scaler_path, &ddr_bank, &address);

  // Use the same size bursts as the scaler.
  uint32_t burstBytes = HW_API::getScalerSDRAMRPortWidth(scaler_path)/8;

  // Transfer the image from PS DDR to the scaler frame buffer page.
  return HW_API::setAxiDmaMemoryDmaReadToDdrWrite(ddr_bank, ps_ddr_addr, address, burstBytes, image_bytes);
}

uint32_t
HW_API::setScalerLossOfInputImageEnable(uint32_t scaler_path, bool enable) {
  assert(HW_API::getScalerPathInitDone(scaler_path));
  // Get page for Loss of Input Image
  uint8_t page = HW_API::getScalerLossOfInputImagePage(scaler_path);

  bool use_b = HW_API::getScalerFrameBufferUseB(scaler_path);

  // Lock / unlock the frame buffer read page.
  // progScalers in updown_scale_wrapper will flip to use_b to a new value if required and halted
  HW_API::setScalerReadPage(scaler_path, page, enable, use_b);

  // Disable the Loss of Input solid raster if enabling Loss of Input Image.
  if (enable) {
    HW_API::setLossofInput(scaler_path, false);
  }
  return 0;
}

/* -- FPGA Build ID -- */

ZYNQFPGAID fpga_id;

void
HW_API::bistCapability() {
    printf("Testing getFPGACapability:\n");
    int valid = 0;
    valid = HW_API::getFPGACapability("INVALID");
    printf("  getFPGACapability(\"INVALID\")                 = %i.\n",valid);
    valid = HW_API::getFPGACapability("THIS_STRING_IS_TOO_LONG");
    printf("  getFPGACapability(\"THIS_STRING_IS_TOO_LONG\") = %i.\n",valid);
    valid = HW_API::getFPGACapability("N_HDMI");
    printf("  getFPGACapability(\"N_HDMI\")                  = %i.\n",valid);
    valid = HW_API::getFPGACapability("BITS_PER_PIXEL");
    printf("  getFPGACapability(\"BITS_PER_PIXEL\")          = %i.\n",valid);
    valid = HW_API::getFPGACapability("INC_RGMII");
    printf("  getFPGACapability(\"INC_RGMII\")               = %i.\n",valid);
    bool match;
    match = HW_API::getScalerArchMatch("PRE_AND_POST");
    printf("  getScalerArchMatch(\"PRE_AND_POST\")           = %u.\n",match);
    match = HW_API::getScalerArchMatch("DUAL_POST");
    printf("  getScalerArchMatch(\"DUAL_POST\")              = %u.\n",match);
    match = HW_API::getScalerArchMatch("SINGLE_POST");
    printf("  getScalerArchMatch(\"SINGLE_POST\")            = %u.\n",match);
    match = HW_API::getScalerArchMatch("QUAD_DUAL_POST");
    printf("  getScalerArchMatch(\"QUAD_DUAL_POST\")         = %u.\n",match);
    match = HW_API::getScalerArchMatch("SINGLE_PRE");
    printf("  getScalerArchMatch(\"SINGLE_PRE\")             = %u.\n",match);
    return;
}

void
HW_API::initFPGABuildID() {
    fpga_id.init();
    return;
}

bool
HW_API::getFPGABuildIDInitDone() {
  return fpga_id.getInitDone();
}

static const uint32_t NUM_FPGA_ID_PARAM = 91;
static const uint32_t FPGA_ID_PARAM_NAME_LENGTH_MAX = 22;
const char* FPGA_ID_PARAM_NAME[NUM_FPGA_ID_PARAM+1] = {
  "Build Number",
  "Git Revision",
  "FPGA_BUILD_YEAR",
  "FPGA_BUILD_MONTH",
  "FPGA_BUILD_DAY",
  "FPGA_BUILD_HOUR",
  "FPGA_BUILD_MINUTE",
  "FPGA_BUILD_SECOND",
  "Build User",
  "Build Host",
  "FPGA_POSITION",
  "N_XGE",
  "INC_XGE",
  "INC_1GE",
  "INC_TEST_XGE",
  "INC_DDR3A",
  "INC_DDR3B",
  "INC_MEM_TEST",
  "N_HDMI",
  "N_VID_RX",
  "N_AUD_RX",
  "N_AUD_CH_RX",
  "N_VID_TX",
  "N_AUD_TX",
  "N_AUD_CH_TX",
  "N_XGE_TX",
  "BITS_PER_PIXEL",
  "PIXELS_PER_CLOCK",
  "INC_HDMI",
  "INC_AUDIO",
  "INC_ASPEN",
  "TICO_MODE",
  "INC_DAISY_CHAIN",
  "N_SCALER",
  "INC_HDMI_PREBUFFER",
  "INC_ICRON_USB",
  "INC_AUDIO_XBAR",
  "INC_VIDEO_XBAR",
  "INC_HDMI_LOOPBACK",
  "INC_HDMI_NORTH_TX",
  "INC_HDMI_NORTH_RX",
  "INC_HDMI_SOUTH_TX",
  "INC_HDMI_SOUTH_RX",
  "INC_AUD_PRES_DET",
  "INC_AUD_GAIN",
  "SCALER_ARCH_INDEX",
  "INC_ASPEN422_RX",
  "INC_ASPEN444_RX",
  "INC_ASPEN444_TX",
  "INC_REDUNDANCY",
  "INC_2G5E",
  "N_AUDIO_MIXERS",
  "N_AUDIO_MIXER_INS",
  "N_AUDIO_MIXER_CH",
  "N_FRAME_BUFFER",
  "FB_ARCH_INDEX",
  "TICO_RESOLUTION",
  "INC_AXI_MEM_DMA",
  "INC_HDMI_HDCP",
  "N_IP_RX_PATHS",
  "N_IP_TX_PATHS",
  "INC_SCALER_OSD",
  "TICO_XS",
  "INC_META_XBAR",
  "UNUSED1",
  "UNUSED2",
  "INC_ENCRYPTION",
  "RX_ENCRYPTION_MODE",
  "TX_ENCRYPTION_MODE",
  "N_INTER",
  "N_XGE_RX",
  "INC_PTP",
  "INC_SMPTE2110",
  "N_INTER_IP_RX",
  "N_PIP_SCALER_PATHS",
  "PIP_SCALER_ARCH_INDEX",
  "N_VIDPROC_MIXER",
  "N_LANES_PER_INTER",
  "N_INTER_IP_TX",
  "INC_SDI_12G",
  "N_SDI_12G",
  "INC_SDI_RX",
  "INC_SDI_TX",
  "BOARD_IDX",
  "N_AUD_PER_LANE",
  "TICO_ENC_422_PPC",
  "TICO_ENC_444_PPC",
  "TICO_DEC_422_PPC",
  "TICO_DEC_444_PPC",
  "INC_GENLOCK",
  "INC_HDCP_CRYPTO",
  "ERR_OUT_OF_BOUNDS"
};

static const uint32_t NUM_SCALER_ARCH = 6;
static const uint32_t SCALER_ARCH_NAME_LENGTH_MAX = 22;
const char* SCALER_ARCH_NAME[NUM_SCALER_ARCH+1] = {
  "UNKNOWN",
  "PRE_AND_POST",
  "DUAL_POST",
  "QUAD_DUAL_POST",
  "SINGLE_POST",
  "SINGLE_PRE",
  "ERR_OUT_OF_BOUNDS"
};

const char* months[] = {"ERR", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec", "ERR"};

void
HW_API::dumpFPGABuildID() {
    assert(HW_API::getFPGABuildIDInitDone());
    printf("FPGA Identification Information:\n");
    ZYNQFPGAIDType::BuildTime build_time;
    fpga_id.getBuildTime(&build_time);

    // Build Time from USR_ACCESSE2.
    printf("  Build Time: ");
    printf("%s %u %u | %02u:%02u:%02u\n", months[build_time.month%14], build_time.day, build_time.year,
                                          build_time.hour, build_time.minute, build_time.second);

    // Build Info from build_info.py.
    uint32_t param_count  = fpga_id.getNumParameters();
    printf("  Build Info:\n");
    printf("    %-*s = %u\n", FPGA_ID_PARAM_NAME_LENGTH_MAX, FPGA_ID_PARAM_NAME[0], fpga_id.getParameter(0));                      // Jenkins Build Number, 0 if desk build.
    printf("    %-*s = %x\n", FPGA_ID_PARAM_NAME_LENGTH_MAX, FPGA_ID_PARAM_NAME[1], fpga_id.getParameter(1));                      // Git Revision
    printf("    %-*s = %02u-%02u-%02u at %02u:%02u:%02u\n", FPGA_ID_PARAM_NAME_LENGTH_MAX, "Build Date", fpga_id.getParameter(2),  // Build Year
                                                                                                         fpga_id.getParameter(3),  // Build Month
                                                                                                         fpga_id.getParameter(4),  // Build Day
                                                                                                         fpga_id.getParameter(5),  // Build Hours
                                                                                                         fpga_id.getParameter(6),  // Build Minutes
                                                                                                         fpga_id.getParameter(7)); // Build Seconds
    printf("    %-*s = %c%c%c%c\n", FPGA_ID_PARAM_NAME_LENGTH_MAX, FPGA_ID_PARAM_NAME[8], (fpga_id.getParameter(8) >> 24) & 0xFF,  // Build User 1st Character
                                                                                          (fpga_id.getParameter(8) >> 16) & 0xFF,  // Build User 2nd Character
                                                                                          (fpga_id.getParameter(8) >>  8) & 0xFF,  // Build User 3rd Character
                                                                                          (fpga_id.getParameter(8)      ) & 0xFF); // Build User 4th Character
    printf("    %-*s = %c%c%c%c\n", FPGA_ID_PARAM_NAME_LENGTH_MAX, FPGA_ID_PARAM_NAME[9], (fpga_id.getParameter(9) >> 24) & 0xFF,  // Build Host 1st Character
                                                                                          (fpga_id.getParameter(9) >> 16) & 0xFF,  // Build Host 2nd Character
                                                                                          (fpga_id.getParameter(9) >>  8) & 0xFF,  // Build Host 3rd Character
                                                                                          (fpga_id.getParameter(9)      ) & 0xFF); // Build Host 4th Character

    // All other parameters defined in fpga_id instantiation.
    printf("  Parameters:\n");
    for (uint32_t i = 10; (i < param_count)&&(i < NUM_FPGA_ID_PARAM); i++) {
        printf("    %-*s = %u\n", FPGA_ID_PARAM_NAME_LENGTH_MAX,
                                  FPGA_ID_PARAM_NAME[i],
                                  fpga_id.getParameter(i));
    }
    return;
}

/* -- Capabilities -- */
int
HW_API::getFPGACapability(const char* parameter) {
    assert(HW_API::getFPGABuildIDInitDone());
    int      value        = -1;
    uint32_t value_length = (unsigned)strlen(parameter);
    uint32_t param_count  = fpga_id.getNumParameters();
    if (value_length > FPGA_ID_PARAM_NAME_LENGTH_MAX)
    {
        printf("ERROR: getFPGACapability(\"%s\") = Invalid string length: %u, which is greater than FPGA_ID_PARAM_NAME_LENGTH_MAX = %u.\n", parameter, value_length, FPGA_ID_PARAM_NAME_LENGTH_MAX);
        value = -2;
        return value;
    }
    for (uint32_t i = 0; (i < param_count)&&(i < NUM_FPGA_ID_PARAM); i++) {
        if (!strcmp(FPGA_ID_PARAM_NAME[i],parameter)) {
          value = fpga_id.getParameter(i);
          break;
        }
    }
    if (value >= 0)
    {
        //printf("INFO:  getFPGACapability(\"%s\") = %u\n", parameter,value);
    } else {
        printf("ERROR: getFPGACapability(\"%s\") = Invalid Capability!\n", parameter);
    }
    return value;
}

bool
HW_API::getScalerArchMatch(const char* arch, uint32_t arch_type) {
    // arch_type  0 = Scaler
    //            1 = Frame Buffer
    //            2 = Pip Scaler

    uint32_t arch_str_length = (unsigned)strlen(arch);
    if (arch_str_length > SCALER_ARCH_NAME_LENGTH_MAX) {
        printf("ERROR: getScalerArchMatch(\"%s\") = Invalid string length: %u, which is greater than SCALER_ARCH_NAME_LENGTH_MAX = %u.\n", arch, arch_str_length, SCALER_ARCH_NAME_LENGTH_MAX);
        return false;
    }
    int arch_str_index = -1;
    for (uint32_t i = 0; i < NUM_SCALER_ARCH; i++) {
        if (!strcmp(SCALER_ARCH_NAME[i],arch)) {
          arch_str_index = (int)i;
          break;
        }
    }
    if (arch_str_index < 0) {
      printf("ERROR: Invalid scaler architecture!\n");
      return false;
    }
    int arch_fpga_index;
    if (arch_type == 1) {
      arch_fpga_index = getFPGACapability("FB_ARCH_INDEX");
    } else if (arch_type == 2){
      arch_fpga_index = getFPGACapability("PIP_SCALER_ARCH_INDEX");
    //} else if (arch_type == 0){
    } else {
      arch_fpga_index = getFPGACapability("SCALER_ARCH_INDEX");
    }
    if (arch_fpga_index <= 0) {
      printf("ERROR: FPGA scaler architecture not recognized!\n");
      return false;
    }
    return arch_str_index == arch_fpga_index;
}

/* -- XBAR -- */
ZYNQXBARCONFIG xbar_config(HW_API::N_AUD_XBAR_IN, HW_API::N_AUD_XBAR_OUT,
                           HW_API::N_VID_XBAR_IN, HW_API::N_VID_XBAR_OUT,
                           HW_API::N_META_XBAR_IN, HW_API::N_META_XBAR_OUT,
                           HW_API::THRESH_WIDTH, HW_API::UNDER_DUR_WIDTH,
                           HW_API::UNDER_THRESH, HW_API::UNDER_DURATION);

// Audio
int32_t
HW_API::getAudioXbarSel(uint32_t index) {
    if (HW_API::getFPGACapability("INC_AUDIO_XBAR") <= 0)
    {
      printf("INC_AUDIO_XBAR feature is required but not enabled!\n");
      return -1;
    }
    xbar_config.init();
    return xbar_config.getAudioXbarSel(index);
}

void
HW_API::setAudioXbarSel(uint32_t index, uint32_t sel) {
    if (HW_API::getFPGACapability("INC_AUDIO_XBAR") <= 0)
    {
      printf("INC_AUDIO_XBAR feature is required but not enabled!\n");
      return;
    }
    xbar_config.init();
    xbar_config.setAudioXbarSel(index, sel);
    return;
}

// Video
int32_t
HW_API::getVideoXbarSel(uint32_t index) {
    if (HW_API::getFPGACapability("INC_VIDEO_XBAR") <= 0)
    {
      printf("INC_VIDEO_XBAR feature is required but not enabled!\n");
      return -1;
    }
    xbar_config.init();
    return xbar_config.getVideoXbarSel(index);
}

void
HW_API::setVideoXbarSel(uint32_t index, uint32_t sel) {
    if (HW_API::getFPGACapability("INC_VIDEO_XBAR") <= 0)
    {
      printf("INC_VIDEO_XBAR feature is required but not enabled!\n");
      return;
    }
    xbar_config.init();
    xbar_config.setVideoXbarSel(index, sel);
    return;
}

// Metadata
int32_t
HW_API::getMetaXbarSel(uint32_t index) {
    if (HW_API::getFPGACapability("INC_META_XBAR") <= 0)
    {
      printf("INC_META_XBAR feature is required but not enabled!\n");
      return -1;
    }
    xbar_config.init();
    return xbar_config.getMetaXbarSel(index);
}

void
HW_API::setMetaXbarSel(uint32_t index, uint32_t sel) {
    if (HW_API::getFPGACapability("INC_META_XBAR") <= 0)
    {
      printf("INC_META_XBAR feature is required but not enabled!\n");
      return;
    }
    xbar_config.init();
    xbar_config.setMetaXbarSel(index, sel);
    return;
}

// Audio Presence
// Initialization
bool
HW_API::initAudPres(){
    if (HW_API::getFPGACapability("INC_AUD_PRES_DET") <= 0)
    {
      printf("INC_AUD_PRES_DET feature is required but not enabled!\n");
      return false;
    }
    xbar_config.init();
    xbar_config.initAudPres();
    return true;
}
// Status read back
int32_t
HW_API::getAudInStatus(uint32_t index, XBARCONFIG::audio_status_type* audio_status){
    if (HW_API::getFPGACapability("INC_AUD_PRES_DET") <= 0)
    {
      printf("INC_AUD_PRES_DET feature is required but not enabled!\n");
      return -1;
    }
    xbar_config.init();
    return xbar_config.getAudInStatus(index, audio_status);
}
int32_t
HW_API::getAudOutStatus(uint32_t index, XBARCONFIG::audio_status_type* audio_status){
    if (HW_API::getFPGACapability("INC_AUD_PRES_DET") <= 0)
    {
      printf("INC_AUD_PRES_DET feature is required but not enabled!\n");
      return -1;
    }
    xbar_config.init();
    return xbar_config.getAudOutStatus(index, audio_status);
}
// Audio Gain
void
HW_API::setAudInGain(uint32_t index, double gain){
    if (HW_API::getFPGACapability("INC_AUD_GAIN") <= 0)
    {
      printf("INC_AUD_GAIN feature is required but not enabled!\n");
      return;
    }
    xbar_config.init();
    xbar_config.setAudInGain(index, gain);
    return;
}
void
HW_API::setAudOutGain(uint32_t index, double gain){
    if (HW_API::getFPGACapability("INC_AUD_GAIN") <= 0)
    {
      printf("INC_AUD_GAIN feature is required but not enabled!\n");
      return;
    }
    xbar_config.init();
    xbar_config.setAudOutGain(index, gain);
    return;
}

/* -- TICO -- */
ZYNQTICOtoIP tico_enc(HW_API::N_XGE_TX_VID_TICO,
                      HW_API::BITS_PER_PIXEL);
ZYNQIPtoTICO tico_dec(HW_API::N_XGE_RX_VID_ASPENTICO,
                      HW_API::CORE_CLK_FREQ_HZ,
                      HW_API::PIXELS_PER_CLOCK,
                      HW_API::BITS_PER_PIXEL);

// Tico Encoder
void
HW_API::configTicoEnc(uint32_t index, uint32_t width, uint32_t height, uint64_t bitrate, uint32_t refresh_rate_num, uint32_t refresh_rate_den, uint32_t bit_depth, uint32_t lvl_weights, HW_API::TicoSubSampling_Mode subsample, bool s2110, bool interlaced, bool legacy_cs){
    if (HW_API::getFPGACapability("TICO_MODE") <= 0)
    {
      printf("TICO_MODE>0 feature is required but not enabled!\n");
      return;
    }
    bool xs = false;
    if (HW_API::getFPGACapability("TICO_MODE") > 1)
    {
      xs = true;
    }
    const char *subsampling_mode;

    const char *subsampling_mode_y422 = "4:2:2 YCbCr";
    const char *subsampling_mode_y444 = "4:4:4 YCbCr";
    const char *subsampling_mode_rgb  = "4:4:4 RGB";

    if (HW_API::BITS_PER_PIXEL == 20) {
      subsampling_mode = subsampling_mode_y422;
    } else {
      switch (subsample) {
        case HW_API::TICO_YCC422:
          subsampling_mode = subsampling_mode_y422;
          break;
        case HW_API::TICO_YCC444:
          subsampling_mode = subsampling_mode_y444;
          break;
        case HW_API::TICO_RGB:
        default:
          subsampling_mode = subsampling_mode_rgb;
          break;
      }
    }
    tico_enc.encoderCoreConfig(index, width, height, bitrate, refresh_rate_num, refresh_rate_den, bit_depth, lvl_weights, subsampling_mode, xs, s2110, interlaced, legacy_cs);
    return;
}

TICOtoIP::enc_status
HW_API::getTicoEncStatus(uint32_t index){
    if (HW_API::getFPGACapability("TICO_MODE") <= 0)
    {
      printf("TICO_MODE>0 feature is required but not enabled!\n");
      TICOtoIP::enc_status null_status = {
        false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, false};
      return null_status;
    }
    return tico_enc.encoderPathStatus(index);
}

void
HW_API::restartTicoEnc(uint32_t index){
    if (HW_API::getFPGACapability("TICO_MODE") <= 0)
    {
      printf("TICO_MODE>0 feature is required but not enabled!\n");
      return;
    }
    tico_enc.encoderPathReset(index, true);
    tico_enc.encoderPathReset(index, false);
}

void
HW_API::enableTicoEnc(uint32_t index){
    if (HW_API::getFPGACapability("TICO_MODE") <= 0)
    {
      printf("TICO_MODE>0 feature is required but not enabled!\n");
      return;
    }
    tico_enc.encoderPathEnable(index, true);
}

void
HW_API::disableTicoEnc(uint32_t index){
    if (HW_API::getFPGACapability("TICO_MODE") <= 0)
    {
      printf("TICO_MODE>0 feature is required but not enabled!\n");
      return;
    }
    tico_enc.encoderPathEnable(index, false);
}

// Tico Decoder
void
HW_API::configTicoDec(uint32_t index, uint32_t width, uint32_t height, uint32_t refresh_rate_num, uint32_t refresh_rate_den, uint32_t downscale){
    if (HW_API::getFPGACapability("TICO_MODE") <= 0)
    {
      printf("TICO_MODE>0 feature is required but not enabled!\n");
      return;
    }
    bool xs = false;
    if (HW_API::getFPGACapability("TICO_MODE") > 1)
    {
      xs = true;
    }
    tico_dec.decoderCoreConfig(index, width, height, refresh_rate_num, refresh_rate_den, downscale, xs);
}

IPtoTICO::dec_status
HW_API::getTicoDecStatus(uint32_t index){
    if (HW_API::getFPGACapability("TICO_MODE") <= 0)
    {
      printf("TICO_MODE>0 feature is required but not enabled!\n");
      IPtoTICO::dec_status null_status = {
        false, false, false, false, false, false, false, false};
      return null_status;
    }
    return tico_dec.decoderPathStatus(index);
}

void
HW_API::restartTicoDec(uint32_t index){
    if (HW_API::getFPGACapability("TICO_MODE") <= 0)
    {
      printf("TICO_MODE>0 feature is required but not enabled!\n");
      return;
    }
    tico_dec.decoderPathReset(index, true);
    tico_dec.decoderPathReset(index, false);
}

/* -- Memory Test -- */

ZYNQMemTestWrapper mem_test[HW_API::N_MEM_BANKS];

void
HW_API::initMemoryTest(uint32_t bank) {
    assert(bank < HW_API::N_MEM_BANKS);
    if (HW_API::getFPGACapability("INC_MEM_TEST") <= 0) {
      printf("INC_MEM_TEST feature is required but not enabled!\n");
      return;
    }
    else if (bank == 0 && (HW_API::getFPGACapability("INC_DDR3A") <= 0)) {
      printf ("INC_DDR3A feature is required but not enabled!\n");
      return;
    }
    else if (bank == 1 && (HW_API::getFPGACapability("INC_DDR3B") <= 0)) {
      printf ("INC_DDR3B feature is required but not enabled!\n");
      return;
    }
    mem_test[bank].localInit(bank);
    mem_test[bank].init();
    return;
}

bool
HW_API::getMemoryTestInitDone(uint32_t bank) {
    return mem_test[bank].getInitDone();
}

void
HW_API::dumpMemoryTestConfig(uint32_t bank) {
    assert(HW_API::getMemoryTestInitDone(bank));
    mem_test[bank].dumpConfigInfo();
    return;
}

bool
HW_API::getMemoryTestReady(uint32_t bank) {
    assert(HW_API::getMemoryTestInitDone(bank));
    return mem_test[bank].getTestReady();
}

bool
HW_API::runMemoryTest(uint32_t bank, uint32_t depth_div_exp, HW_API::MemTestType type) {
    assert(HW_API::getMemoryTestInitDone(bank));
    return mem_test[bank].runMemTest(depth_div_exp, (MemTestWrapperType::TestType)type);
}

bool
HW_API::runMemoryAddressStressTest(uint32_t bank, uint32_t iterations, HW_API::MemTestType type) {
    assert(HW_API::getMemoryTestInitDone(bank));
    return mem_test[bank].runMemAddrStressTest(iterations, (MemTestWrapperType::TestType)type);
}

bool
HW_API::runMemoryAddressHammer(uint32_t bank, uint32_t iterations, HW_API::MemTestType type) {
    assert(HW_API::getMemoryTestInitDone(bank));
    return mem_test[bank].runMemAddrHammer(iterations, (MemTestWrapperType::TestType)type);
}

bool
HW_API::getMemoryCalibrated(uint32_t bank) {
    assert(HW_API::getMemoryTestInitDone(bank));
    return mem_test[bank].getMemoryCalibrated();
}

/* -- 10GE Mac -- */

ZYNQX7XGEMac x7_xge_mac[HW_API::N_TOTAL_10GE_CHANNELS];

void
HW_API::init10GEMac(uint32_t channel) {
    assert(channel < HW_API::N_TOTAL_10GE_CHANNELS);
    if ((HW_API::getFPGACapability("INC_XGE") <= 0) && (HW_API::getFPGACapability("INC_1GE") <= 0) && (HW_API::getFPGACapability("INC_2G5E") <= 0))
    {
      printf("INC_XGE or INC_1GE or INC_2G5E feature is required but not enabled!\n");
      return;
    }
    if (channel >= N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
    {
      printf("INC_TEST_XGE feature is required but not enabled!\n");
      return;
    }
    x7_xge_mac[channel].init(channel);
    return;
}

bool
HW_API::get10GEMacInitDone(uint32_t channel) {
    assert(channel < HW_API::N_TOTAL_10GE_CHANNELS);
    return x7_xge_mac[channel].getInitDone();
}

void
HW_API::dump10GEMacStatNames() {
    assert(HW_API::get10GEMacInitDone(0));
    x7_xge_mac[0].dumpStatisticNames();
    return;
}

uint64_t
HW_API::get10GEMacStatistic(uint32_t channel, uint32_t stat_index) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].getStatistic((X7XGEMacReg::StatReg)stat_index);
}

void
HW_API::reset10GEMacRx(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    x7_xge_mac[channel].resetReceiver();
    return;
}

void
HW_API::reset10GEMacTx(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    x7_xge_mac[channel].resetTransmitter();
    return;
}

bool
HW_API::get10GEMacRxEnable(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].getReceiverEnable();
}

void
HW_API::set10GEMacRxEnable(uint32_t channel, bool enable) {
    assert(HW_API::get10GEMacInitDone(channel));
    x7_xge_mac[channel].setReceiverEnable(enable);
    return;
}

bool
HW_API::get10GEMacTxEnable(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].getTransmitterEnable();
}

void
HW_API::set10GEMacTxEnable(uint32_t channel, bool enable) {
    assert(HW_API::get10GEMacInitDone(channel));
    x7_xge_mac[channel].setTransmitterEnable(enable);
    return;
}

bool
HW_API::get10GEMacFaultInhibit(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].getFaultInhibit();
}

void
HW_API::set10GEMacFaultInhibit(uint32_t channel, bool enable) {
    assert(HW_API::get10GEMacInitDone(channel));
    x7_xge_mac[channel].setFaultInhibit(enable);
    return;
}

bool
HW_API::get10GEMacMDIOEnable(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].getMDIOControlEnable();
}

const uint32_t XGE_MAC_REG_CLK_FREQUENCY = 100000000;

void
HW_API::set10GEMacMDIOEnable(uint32_t channel, bool enable) {
    assert(HW_API::get10GEMacInitDone(channel));
    if (enable) {
        x7_xge_mac[channel].enableMDIOControl(XGE_MAC_REG_CLK_FREQUENCY);
    } else {
        x7_xge_mac[channel].disableMDIOControl();
    }
    return;
}

void
HW_API::write10GEMacMDIO(uint32_t channel, uint32_t dev_addr, uint32_t reg_addr, uint16_t data) {
    assert(HW_API::get10GEMacInitDone(channel));
    x7_xge_mac[channel].writeMDIO(dev_addr, reg_addr, data);
    return;
}

uint16_t
HW_API::read10GEMacMDIO(uint32_t channel, uint32_t dev_addr, uint32_t reg_addr) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].readMDIO(dev_addr, reg_addr);
}

void
HW_API::read10GEMacMDIOInc(uint32_t channel, uint32_t dev_addr, uint32_t reg_addr, uint32_t count, uint16_t * data) {
    assert(HW_API::get10GEMacInitDone(channel));
    x7_xge_mac[channel].readMDIOInc(dev_addr, reg_addr, count, data);
    return;
}

bool
HW_API::get10GERxSignalDetect(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].getRxSignalDetect();
}

bool
HW_API::get10GELinkUp(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].getLinkUp();
}

bool
HW_API::get10GELocalFault(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].getLocalFault();
}

bool
HW_API::get10GETransmitFault(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].getTransmitFault();
}

bool
HW_API::get10GEReceiveFault(uint32_t channel) {
    assert(HW_API::get10GEMacInitDone(channel));
    return x7_xge_mac[channel].getReceiveFault();
}

/* -- 1GE Mac -- */

ZYNQX7TEMAC x7_temac[HW_API::N_TOTAL_10GE_CHANNELS];

void
HW_API::initTEMAC(uint32_t channel) {
    assert(channel < HW_API::N_TOTAL_10GE_CHANNELS);
    if ((HW_API::getFPGACapability("INC_XGE") <= 0) && (HW_API::getFPGACapability("INC_1GE") <= 0) && (HW_API::getFPGACapability("INC_2G5E") <= 0))
    {
      printf("INC_XGE or INC_1GE or INC_2G5E feature is required but not enabled!\n");
      return;
    }
    if (channel >= N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
    {
      printf("INC_TEST_XGE feature is required but not enabled!\n");
      return;
    }
    x7_temac[channel].init(channel);
    // Always enable MDIO before turning off PHY isolation.
    HW_API::setTEMACMDIOEnable(channel, true);
    HW_API::set1GPHYisolate(channel,0);
    if (HW_API::getFPGACapability("INC_2G5E") > 0)
    {
      // Disable auto-negotiation.
      HW_API::setEnableAutonegotiation(channel,0);
    }
    return;
}

bool
HW_API::getTEMACInitDone(uint32_t channel) {
    assert(channel < HW_API::N_TOTAL_10GE_CHANNELS);
    return x7_temac[channel].getInitDone();
}

void
HW_API::dumpTEMACStatNames() {
    assert(HW_API::getTEMACInitDone(0));
    x7_temac[0].dumpStatisticNames();
    return;
}

uint64_t
HW_API::getTEMACStatistic(uint32_t channel, uint32_t stat_index) {
    assert(HW_API::getTEMACInitDone(channel));
    return x7_temac[channel].getStatistic((X7TEMACReg::StatReg)stat_index);
}

void
HW_API::resetTEMACRx(uint32_t channel) {
    assert(HW_API::getTEMACInitDone(channel));
    x7_temac[channel].resetReceiver();
    return;
}

void
HW_API::resetTEMACTx(uint32_t channel) {
    assert(HW_API::getTEMACInitDone(channel));
    x7_temac[channel].resetTransmitter();
    return;
}

bool
HW_API::getTEMACRxEnable(uint32_t channel) {
    assert(HW_API::getTEMACInitDone(channel));
    return x7_temac[channel].getReceiverEnable();
}

void
HW_API::setTEMACRxEnable(uint32_t channel, bool enable) {
    assert(HW_API::getTEMACInitDone(channel));
    x7_temac[channel].setReceiverEnable(enable);
    return;
}

bool
HW_API::getTEMACTxEnable(uint32_t channel) {
    assert(HW_API::getTEMACInitDone(channel));
    return x7_temac[channel].getTransmitterEnable();
}

void
HW_API::setTEMACTxEnable(uint32_t channel, bool enable) {
    assert(HW_API::getTEMACInitDone(channel));
    x7_temac[channel].setTransmitterEnable(enable);
    return;
}

bool
HW_API::getTEMACMDIOEnable(uint32_t channel) {
    assert(HW_API::getTEMACInitDone(channel));
    return x7_temac[channel].getMDIOControlEnable();
}

const uint32_t TEMAC_REG_CLK_FREQUENCY = 100000000;

void
HW_API::setTEMACMDIOEnable(uint32_t channel, bool enable) {
    assert(HW_API::getTEMACInitDone(channel));
    if (enable) {
        x7_temac[channel].enableMDIOControl(TEMAC_REG_CLK_FREQUENCY);
    } else {
        x7_temac[channel].disableMDIOControl();
    }
    return;
}

void
HW_API::writeTEMACMDIO(uint32_t channel, uint32_t reg_addr, uint16_t data) {
    assert(HW_API::getTEMACInitDone(channel));
    x7_temac[channel].writeMDIO(reg_addr, data);
    return;
}

uint16_t
HW_API::readTEMACMDIO(uint32_t channel, uint32_t reg_addr) {
    assert(HW_API::getTEMACInitDone(channel));
    return x7_temac[channel].readMDIO(reg_addr);
}

void
HW_API::set1GPHYisolate(uint32_t channel, bool isolate) {
    assert(HW_API::getTEMACInitDone(channel));
    x7_temac[channel].setPHYisolation(isolate);
    return;
}

void
HW_API::set1GUnidirectionalEnable(uint32_t channel, bool enable) {
    assert(HW_API::getTEMACInitDone(channel));
    x7_temac[channel].setUnidirectionalEnable(enable);
    return;
}

void
HW_API::setEnableAutonegotiation(uint32_t channel, bool enable) {
    assert(HW_API::getTEMACInitDone(channel));
    x7_temac[channel].setEnableAutonegotiation(enable);
    return;
}

void
HW_API::set1GSgmii(uint32_t channel, bool sgmii) {
    assert(HW_API::getTEMACInitDone(channel));
    x7_temac[channel].setSgmii(sgmii);
    return;
}

bool
HW_API::get1GSgmii(uint32_t channel) {
    assert(HW_API::getTEMACInitDone(channel));
    return x7_temac[channel].getSgmii();
}

bool
HW_API::get1GLinkUp(uint32_t channel) {
    assert(HW_API::getTEMACInitDone(channel));
    return x7_temac[channel].getLinkUp();
}

bool
HW_API::get1GRemoteFault(uint32_t channel) {
    assert(HW_API::getTEMACInitDone(channel));
    return x7_temac[channel].getRemoteFault();
}

/* -- 10GE Transceiver -- */

ZYNQXGEDRP xge_drp[HW_API::N_TOTAL_10GE_CHANNELS];

void
HW_API::init10GEXcvr(uint32_t channel) {
    assert(channel < HW_API::N_TOTAL_10GE_CHANNELS);
    if ((HW_API::getFPGACapability("INC_XGE") <= 0) && (HW_API::getFPGACapability("INC_1GE") <= 0) && (HW_API::getFPGACapability("INC_2G5E") <= 0))
    {
      printf("INC_XGE or INC_1GE or INC_2G5E feature is required but not enabled!\n");
      return;
    }
    if (channel >= N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
    {
      printf("INC_TEST_XGE feature is required but not enabled!\n");
      return;
    }
    xge_drp[channel].init(channel);
    return;
}

bool
HW_API::get10GEXcvrInitDone(uint32_t channel) {
    assert(channel < HW_API::N_TOTAL_10GE_CHANNELS);
    return xge_drp[channel].getInitDone();
}

uint32_t
HW_API::get10GEXcvrRxDataWidth(uint32_t channel) {
    assert(HW_API::get10GEXcvrInitDone(channel));
    return xge_drp[channel].getRxDataWidth();
}

bool
HW_API::get10GEXcvrRxIntDataWidth(uint32_t channel) {
    assert(HW_API::get10GEXcvrInitDone(channel));
    return xge_drp[channel].getRxIntDataWidth();
}

uint32_t
HW_API::get10GEXcvrRxOutDiv(uint32_t channel) {
    assert(HW_API::get10GEXcvrInitDone(channel));
    return xge_drp[channel].getRxOutDiv();
}

void
HW_API::run10GERxEyeScan(uint32_t channel, uint32_t target_sample_time_ms, uint32_t h_gap, uint32_t v_gap) {
    assert(HW_API::get10GEXcvrInitDone(channel));
    const uint64_t RX_FREQ = (uint64_t)156250000*(uint64_t)66;
    const uint64_t RX_DATA_WIDTH = 32;
    const uint64_t SAMPLE_RATE = RX_FREQ/RX_DATA_WIDTH;
    uint64_t target_samples = SAMPLE_RATE * target_sample_time_ms / (uint64_t)1000;
    xge_drp[channel].runEyeScan(false, target_samples, h_gap, v_gap);
    return;
}

/* -- 10GE Interface -- */

ZYNQAXI10GIntf xge_intf;

void
HW_API::init10GEIntf() {
    if ((HW_API::getFPGACapability("INC_XGE") <= 0) && (HW_API::getFPGACapability("INC_1GE") <= 0) && (HW_API::getFPGACapability("INC_2G5E") <= 0))
    {
      printf("INC_XGE or INC_1GE or INC_2G5E feature is required but not enabled!\n");
      return;
    }
    xge_intf.init();
    return;
}

bool
HW_API::get10GEIntfInitDone() {
    return xge_intf.getInitDone();
}

bool
HW_API::get10GEDaisyEnTx() {
    assert(HW_API::get10GEIntfInitDone());
    return xge_intf.getDaisyEnTx();
}

void
HW_API::set10GEDaisyEnTx(bool enable) {
    assert(HW_API::get10GEIntfInitDone());
    xge_intf.setDaisyEnTx(enable);
    return;
}

bool
HW_API::get10GEDaisyEnRx() {
    assert(HW_API::get10GEIntfInitDone());
    return xge_intf.getDaisyEnRx();
}

void
HW_API::set10GEDaisyEnRx(bool enable) {
    assert(HW_API::get10GEIntfInitDone());
    xge_intf.setDaisyEnRx(enable);
    return;
}

uint32_t
HW_API::get10GEDaisyDropCount(uint32_t index) {
    assert(HW_API::get10GEIntfInitDone());
    return xge_intf.getDaisyDropCount(index);
}

uint32_t
HW_API::get10GERxDropCount(uint32_t index) {
    assert(HW_API::get10GEIntfInitDone());
    return xge_intf.getRxDropCount(index);
}

uint32_t
HW_API::get10GERxMaxPacketLength(uint32_t index) {
    assert(HW_API::get10GEIntfInitDone());
    return xge_intf.getRxMaxPacketLength(index);
}

uint32_t
HW_API::get10GERxBandwidth(uint32_t index) {
    assert(HW_API::get10GEIntfInitDone());
    return xge_intf.getRxBandwidth(index);
}

uint32_t
HW_API::get10GETxBandwidth(uint32_t index) {
    assert(HW_API::get10GEIntfInitDone());
    return xge_intf.getTxBandwidth(index);
}

/* -- IP Receiver -- */
ZYNQIPRx ip_rx(HW_API::N_XGE_RX,
               HW_API::N_CHANNELS_RX,
               HW_API::IP_CAM_DEPTH);

void
HW_API::initIPRx() {
    if ((HW_API::getFPGACapability("INC_XGE") <= 0) &&
        (HW_API::getFPGACapability("INC_2G5E") <= 0) &&
        (HW_API::getFPGACapability("INC_1GE") <= 0))
    {
      printf("INC_XGE or INC_1GE or INC_2G5E feature is required but not enabled!\n");
      return;
    }
    ip_rx.init();
    return;
}

bool
HW_API::getIPRxInitDone() {
    return ip_rx.getInitDone();
}

void
HW_API::setRxDataAddrPort(uint32_t sfp, uint32_t channel, uint32_t ip_addr, uint16_t port, bool bypass) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.setDataCAM(sfp, channel, ip_addr, port, bypass);
    return;
}

void
HW_API::setRxDataAddrPort(uint32_t sfp, uint32_t channel, uint32_t ip_addr, uint16_t port) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.setDataCAM(sfp, channel, ip_addr, port, false);
    return;
}

void
HW_API::setRxDataBypass(uint32_t sfp, uint32_t channel, bool bypass) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.setDataBypass(sfp, channel, bypass);
    return;
}

void
HW_API::setInBandControlIPAddress(uint32_t sfp, uint32_t addr_idx, uint32_t ip_addr, uint32_t ip_mask) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.setIBCIPAddr(sfp, addr_idx, ip_addr, ip_mask);
    return;
}

HW_API::ibcStatus
HW_API::getInBandControlStatus(uint32_t sfp) {
    assert(HW_API::getIPRxInitDone());
    HW_API::ibcStatus stat;
    IPRxType::ibcStatus xstat = ip_rx.getIBCStatus(sfp);
    stat.ready = xstat.ready;
    stat.empty = xstat.empty;
    stat.error = xstat.error;
    stat.sop   = xstat.sop;
    stat.eop   = xstat.eop;
    return stat;
}

uint64_t
HW_API::getInBandControlData(uint32_t sfp) {
    assert(HW_API::getIPRxInitDone());
    return ip_rx.getIBCData(sfp);
}

void
HW_API::getInBandControlPacket(uint32_t sfp, HW_API::ibcPacket * pkt, bool* ptp, uint64_t* ptp_sec, uint32_t* ptp_nsec) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.getIBCPacket(sfp, (IPRxType::ibcPacket*)pkt, ptp, ptp_sec, ptp_nsec);
    return;
}

uint8_t
HW_API::getInBandControlDropCount(uint32_t sfp) {
    assert(HW_API::getIPRxInitDone());
    return ip_rx.getIBCDropCount(sfp);
}

void
HW_API::clearInBandControlDropCount(uint32_t sfp) {
    ip_rx.clearIBCDropCount(sfp);
    return;
}

uint8_t
HW_API::getInBandControlKeepCount(uint32_t sfp) {
    assert(HW_API::getIPRxInitDone());
    return ip_rx.getIBCKeepCount(sfp);
}

void
HW_API::clearInBandControlKeepCount(uint32_t sfp) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.clearIBCKeepCount(sfp);
    return;
}

uint64_t
HW_API::getRxSFPInBandwidth(uint32_t sfp) {
    assert(HW_API::getIPRxInitDone());
    return ip_rx.getRxBandwidth(sfp);
}

void
HW_API::set10GRxKey(uint32_t sfp, uint32_t chan, uint32_t* key, uint8_t keyId) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.setKey(sfp, chan, key, keyId);
    return;
}

void
HW_API::unset10GRxKey(uint32_t sfp, uint32_t chan, uint8_t keyId) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.unsetKey(sfp, chan, keyId);
    return;
}

void
HW_API::getKeyStatus(uint32_t sfp, uint32_t chan, uint32_t* keyreq, uint32_t* srcIp, uint32_t* dstIp, uint32_t* dstPort) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.getKeyStatus(sfp, chan, keyreq, srcIp, dstIp, dstPort);
    return;
}

void
HW_API::getRTPPayloadType(uint32_t sfp, uint32_t chan, uint8_t* payloadType) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.getRTPPayloadType(sfp, chan, payloadType);
    return;
}

void
HW_API::getSRTPState(uint32_t sfp, uint32_t chan, bool* is_srtp) {
    assert(HW_API::getIPRxInitDone());
    ip_rx.getSRTPState(sfp, chan, is_srtp);
    return;
}

/* -- IP Transmitter -- */
ZYNQIPTxUDPIP obj[HW_API::N_XGE];
iptx_udpip_encap* ref[HW_API::N_XGE];
ZYNQIPTx ip_tx(HW_API::N_XGE,
               HW_API::N_CHANNELS_TX*2);
bool ip_tx_init_done = false;
uint32_t n_tx_vid_ts;
uint32_t n_tx_aspen_ts;
uint32_t n_tx_vid_2110;
uint32_t n_tx_audio;
uint32_t n_tx_meta;
uint32_t n_tx_usb;
uint32_t n_tx_lowrate;
uint32_t n_tx_pcr;

void
HW_API::initIPTx(uint32_t ppf) {
    if ((HW_API::getFPGACapability("INC_XGE") <= 0) &&
        (HW_API::getFPGACapability("INC_2G5E") <= 0) &&
        (HW_API::getFPGACapability("INC_1GE") <= 0))
    {
      printf("INC_XGE or INC_1GE or INC_2G5E feature is required but not enabled!\n");
      return;
    }
    for (uint32_t i = 0; i < HW_API::N_XGE; i++) {
        ref[i] = (iptx_udpip_encap*)&obj[i];
        ref[i]->init(i);
    }
    n_tx_vid_ts = HW_API::N_XGE_TX_VID_ASPEN422 +
                  (getFPGACapability("INC_ASPEN444_TX") > 0 ? HW_API::N_XGE_TX_VID_ASPEN444 : 0) +
                  HW_API::N_XGE_TX_VID_TICO;
    n_tx_aspen_ts = HW_API::N_XGE_TX_VID_ASPEN422 +
                    (getFPGACapability("INC_ASPEN444_TX") > 0 ? HW_API::N_XGE_TX_VID_ASPEN444 : 0);
    n_tx_vid_2110 = HW_API::N_XGE_TX_VID_SMPTE2110;
    n_tx_audio = (HW_API::N_XGE_TX_AUD_CH+3)/4;
    n_tx_meta  = HW_API::N_XGE_TX_META;
    n_tx_usb   = HW_API::N_XGE_TX_USB;
    n_tx_lowrate = HW_API::N_XGE_TX_LOWRATE;
    n_tx_pcr   = HW_API::N_XGE_TX_PCR;
    ip_tx.init(ref);
    assert(ip_tx.getInitDone());
    // Program lengths for each stream type
    // The layer underneath doesn't know about type to stream mapping, so do it here
    // Note that N_CHANNELS_TX is doubled: this is to accomodate channels directly from av_to_ip, plus
    // channels from ip_tx arriving via interfpga (upper N_CHANNELS).
    for (uint32_t sfp=0;sfp<N_XGE;sfp++) {
        bool rtp_en[2*N_CHANNELS_TX];
        for (uint32_t chan=0;chan<2*N_CHANNELS_TX;chan++) {
            uint32_t length;
            if (chan%N_CHANNELS_TX < n_tx_usb) {
                length = 0; // dynamic length
                rtp_en[chan] = true;
            } else if (chan%N_CHANNELS_TX < n_tx_usb + n_tx_vid_ts) {
                length = ppf*188; // ppf TS packets
                rtp_en[chan] = true;
            } else if (chan%N_CHANNELS_TX < n_tx_usb + n_tx_vid_ts + n_tx_vid_2110) {
                length = 0; // dynamic length for SMPTE2110 packets
                rtp_en[chan] = false; // this is done upstream
            } else if (chan%N_CHANNELS_TX < n_tx_usb + n_tx_vid_ts + n_tx_vid_2110 + n_tx_audio) {
                length = 188; // 1 TS packet
                rtp_en[chan] = true;
            } else if (chan%N_CHANNELS_TX < n_tx_usb + n_tx_vid_ts + n_tx_vid_2110 + n_tx_audio + n_tx_meta) {
                length = 40;
                rtp_en[chan] = true;
            } else if (chan%N_CHANNELS_TX < n_tx_usb + n_tx_vid_ts + n_tx_vid_2110 + n_tx_audio + n_tx_meta + n_tx_lowrate) {
                length = 0; // dynamic length
                rtp_en[chan] = true;
            } else if (chan%N_CHANNELS_TX < n_tx_usb + n_tx_vid_ts + n_tx_vid_2110 + n_tx_audio + n_tx_meta + n_tx_lowrate + n_tx_pcr) {
                length = 188; // 1 TS packet
                rtp_en[chan] = true;
            } else {
                length = 0;
                rtp_en[chan] = true;
            }
            ip_tx.setPayloadLength(sfp,chan,length);
        }
        ip_tx.setRTPEnables(sfp, rtp_en, 2*N_CHANNELS_TX);
    }
    ip_tx_init_done = true;
    return;
}

bool
HW_API::getIPTxInitDone() {
    return ip_tx_init_done;
}

int
HW_API::lockHost(bool lock) {
    assert(HW_API::getIPTxInitDone());
    return ip_tx.lockHost(lock);
}

void
HW_API::setHostPayload(uint32_t sfp, uint64_t data) {
    assert(HW_API::getIPTxInitDone());
    ip_tx.setHostPayload(sfp, data);
    return;
}

void
HW_API::setHostCtrl(uint32_t sfp, uint8_t be, bool last, bool we, bool weop) {
    assert(HW_API::getIPTxInitDone());
    ip_tx.setHostCtrl(sfp, be, last, we, weop);
    return;
}

bool
HW_API::getHostRdy(uint32_t sfp) {
    assert(HW_API::getIPTxInitDone());
    return ip_tx.getHostRdy(sfp);
}

void
HW_API::set10GTxKey(uint32_t sfp, uint32_t chan, uint32_t* key, uint8_t keyId) {
    assert(HW_API::getIPTxInitDone());
    uint32_t chan_adj = sfp >= N_XGE?chan+N_CHANNELS_TX:chan;
    ip_tx.setKey(sfp%N_XGE, chan_adj, key, keyId);
    return;
}

void
HW_API::unset10GTxKey(uint32_t sfp, uint32_t chan, uint8_t keyId) {
    assert(HW_API::getIPTxInitDone());
    uint32_t chan_adj = sfp >= N_XGE?chan+N_CHANNELS_TX:chan;
    ip_tx.unsetKey(sfp%N_XGE, chan_adj, keyId);
    return;
}

uint64_t
HW_API::getTxEncapBandwidth(uint32_t sfp) {
    assert(HW_API::getIPTxInitDone());
    return ip_tx.getEncapBandwidth(sfp);
}

uint64_t
HW_API::getTxEncapTotalBandwidth(uint32_t sfp) {
    assert(HW_API::getIPTxInitDone());
    return ip_tx.getEncapTotalBandwidth(sfp);
}

void
HW_API::setSourceIPAddress(uint32_t sfp, uint32_t ip) {
    assert(HW_API::getIPTxInitDone());
    ip_tx.setSrcIP(sfp%N_XGE, ip);
    return;
}

void
HW_API::setSourceIPPort(uint32_t sfp, uint32_t port) {
    assert(HW_API::getIPTxInitDone());
    ip_tx.setSrcPort(sfp%N_XGE, port);
    return;
}

void
HW_API::setSourceMACAddress(uint32_t sfp, uint64_t mac) {
    assert(HW_API::getIPTxInitDone());
    ip_tx.setSrcMac(sfp%N_XGE, mac);
    return;
}

void
HW_API::setTTL(uint32_t sfp, uint32_t chan, uint32_t ttl) {
    assert(HW_API::getIPTxInitDone());
    uint32_t chan_adj = sfp >= N_XGE?chan+N_CHANNELS_TX:chan;
    ip_tx.setTTL(sfp%N_XGE, chan_adj, ttl);
    return;
}

void
HW_API::setDestinationMACAddress(uint32_t sfp, uint32_t chan, uint64_t mac) {
    assert(HW_API::getIPTxInitDone());
    uint32_t chan_adj = sfp >= N_XGE?chan+N_CHANNELS_TX:chan;
    ip_tx.setDestMac(sfp%N_XGE, chan_adj, mac);
    return;
}

void
HW_API::setDestinationIPAddress(uint32_t sfp, uint32_t chan, uint32_t ip) {
    assert(HW_API::getIPTxInitDone());
    uint32_t chan_adj = sfp >= N_XGE?chan+N_CHANNELS_TX:chan;
    ip_tx.setDestIP(sfp%N_XGE, chan_adj, ip);
    return;
}

void
HW_API::setDestinationPort(uint32_t sfp, uint32_t chan, uint32_t port) {
    assert(HW_API::getIPTxInitDone());
    uint32_t chan_adj = sfp >= N_XGE?chan+N_CHANNELS_TX:chan;
    ip_tx.setDestPort(sfp%N_XGE, chan_adj, port);
    return;
}

void
HW_API::setInterFPGAChannelEnable(uint32_t sfp, uint32_t chan, bool enable) {
    assert(HW_API::getIPTxInitDone());
    assert(chan < N_CHANNELS_TX);
    ip_tx.setChannelEnable(sfp, N_CHANNELS_TX+chan, enable);
}

/* -- 10GE Tx -- */

ZYNQAVtoIP av2ip;

void
HW_API::initAVtoIP() {
  if ((HW_API::getFPGACapability("INC_XGE") <= 0) && (HW_API::getFPGACapability("INC_1GE") <= 0) && (HW_API::getFPGACapability("INC_2G5E") <= 0))
  {
    printf("INC_XGE or INC_1GE or INC_2G5E feature is required but not enabled!\n");
    return;
  }
  n_tx_vid_ts = HW_API::N_XGE_TX_VID_ASPEN422 +
                (getFPGACapability("INC_ASPEN444_TX") > 0 ? HW_API::N_XGE_TX_VID_ASPEN444 : 0) +
                HW_API::N_XGE_TX_VID_TICO;
  n_tx_vid_2110 = HW_API::N_XGE_TX_VID_SMPTE2110;
  n_tx_audio = (HW_API::N_XGE_TX_AUD_CH+3)/4;
  n_tx_meta  = HW_API::N_XGE_TX_META;
  n_tx_usb   = HW_API::N_XGE_TX_USB;
  n_tx_lowrate = HW_API::N_XGE_TX_LOWRATE;
  n_tx_pcr   = HW_API::N_XGE_TX_PCR;
  uint32_t aspen444_offset = HW_API::getFPGACapability("INC_ASPEN444_TX") <= 0 ? 2 : 0;
  av2ip.init(HW_API::N_XGE_TX_VID - HW_API::N_XGE_TX_VID_SMPTE2110 - aspen444_offset, HW_API::N_XGE_TX_AUD, HW_API::N_XGE_TX_AUD_CH, HW_API::N_XGE_TX_META, HW_API::N_XGE_TX_USB, HW_API::N_XGE_TX_LOWRATE, HW_API::N_XGE_TX_VID_SMPTE2110, HW_API::N_XGE+HW_API::getFPGACapability("N_INTER_IP_TX"),HW_API::N_CHANNELS_TX);
  return;
}

bool
HW_API::getAVtoIPInitDone() {
  return av2ip.getInitDone();
}

void
HW_API::setVideoTxPID(uint32_t pid) {
    assert(HW_API::getAVtoIPInitDone());
    av2ip.setVidPID(pid);
    return;
}

void
HW_API::setVideoTxPID_Tico(uint32_t pid) {
    assert(HW_API::getAVtoIPInitDone());
    av2ip.setVidPID_Tico(pid);
    return;
}

void
HW_API::setAudioTxPID(uint32_t pid) {
    assert(HW_API::getAVtoIPInitDone());
    av2ip.setAudPID(pid, 0);
    return;
}

void
HW_API::setVideoStandard(uint32_t vid, XTxVidStandard std) {
    assert(HW_API::getAVtoIPInitDone());
    AVtoIPType::VidSTD xstd;
    xstd.interlaced = std.interlaced;
    xstd.bw = (AVtoIPType::VidBW)std.bw;
    xstd.hs_pol_high = std.hs_pol_high;
    xstd.vs_pol_high = std.vs_pol_high;
    xstd.clr_spec = (AVtoIPType::ColourSpecification)std.clr_spec;
    xstd.cmp_size = std.cmp_size;
    xstd.smp_struct = (AVtoIPType::SampleStructure)std.smp_struct;
    xstd.sptl = std.sptl;
    xstd.spal = std.spal;
    xstd.tlpf0 = std.tlpf0;
    xstd.tlpf1 = std.tlpf1;
    xstd.alpf0 = std.alpf0;
    xstd.alpf1 = std.alpf1;
    xstd.soha  = std.soha;
    xstd.sova0 = std.sova0;
    xstd.sova1 = std.sova1;
    xstd.sova_ext0 = std.sova_ext0;
    xstd.sova_ext1 = std.sova_ext1;
    xstd.rate_num = std.frame_rate_num;
    xstd.rate_den = std.frame_rate_den;
    xstd.hs_start = std.hs_start;
    xstd.hs_stop = std.hs_stop;
    xstd.vs_start0 = std.vs_start0;
    xstd.vs_start1 = std.vs_start1;
    xstd.vs_stop0 = std.vs_stop0;
    xstd.vs_stop1 = std.vs_stop1;
    xstd.vs_hpos0 = std.vs_hpos0;
    xstd.vs_hpos1 = std.vs_hpos1;
    xstd.copyright = std.copyright;
    xstd.hpos_flag = std.hpos_flag;
    xstd.clr_spec_inp = (AVtoIPType::ColourSpecification)std.clr_spec_inp;
    xstd.smp_struct_inp = (AVtoIPType::SampleStructure)std.smp_struct_inp;
    xstd.eotf = (AVtoIPType::ElectroopticalTransferFunction)std.eotf;
    xstd.clr_space = (AVtoIPType::ColourSpace)std.clr_space;
    av2ip.setVidSTD(vid, xstd);
    return;
}

void
HW_API::set10GETxEnable(uint32_t sfp, uint32_t chan, bool enable) {
    assert(HW_API::getAVtoIPInitDone());
    if (HW_API::N_XGE > 0) {
      assert(HW_API::getIPTxInitDone());
    }
    av2ip.setTSChannelEnable(sfp, chan, enable);
    if (sfp < HW_API::N_XGE) {
      ip_tx.setChannelEnable(sfp, chan, enable);
    }
    return;
}

void
HW_API::setAudioTxAES67PacketTime(uint32_t aud, uint32_t grp, bool p1ms) {
    assert(HW_API::getAVtoIPInitDone());
    av2ip.setAudTxAES67PacketTime(aud, grp, p1ms);
    return;
}

uint64_t
HW_API::getTxVidBandwidth(uint32_t vid) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getVidBandwidth(vid);
}

uint64_t
HW_API::getTxVidActBandwidth(uint32_t vid) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getVidActBandwidth(vid);
}

uint64_t
HW_API::getTxVidTSBandwidth(uint32_t vid) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getVidTSBandwidth(vid);
}

uint64_t
HW_API::getTxVidTSTotalBandwidth(uint32_t vid) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getVidTSTotalBandwidth(vid);
}

uint64_t
HW_API::getTxAudTSBandwidth(uint32_t aud) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getAudTSBandwidth(aud, 0);
}

uint64_t
HW_API::getTxAudTSTotalBandwidth(uint32_t aud) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getAudTSTotalBandwidth(aud, 0);
}

uint64_t
HW_API::getTxMetaTSBandwidth(uint32_t meta) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getMetaTSBandwidth(meta);
}

uint64_t
HW_API::getTxMetaTSTotalBandwidth(uint32_t meta) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getMetaTSTotalBandwidth(meta);
}

uint64_t
HW_API::getTxUSBTSBandwidth(uint32_t usb) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getUSBTSBandwidth(usb);
}

uint64_t
HW_API::getTxUSBTSTotalBandwidth(uint32_t usb) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getUSBTSTotalBandwidth(usb);
}

uint64_t
HW_API::getTxEncapTSBandwidth(uint32_t sfp) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getEncapTSBandwidth(sfp);
}

uint64_t
HW_API::getTxEncapTSTotalBandwidth(uint32_t sfp) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getEncapTSTotalBandwidth(sfp);
}

uint64_t
HW_API::getTxPayloadTSBandwidth(uint32_t sfp) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getPayloadTSBandwidth(sfp);
}

uint64_t
HW_API::getTxPayloadTSTotalBandwidth(uint32_t sfp) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getPayloadTSTotalBandwidth(sfp);
}

void
HW_API::dumpTxVidRouteBandwidth(uint32_t sfp, uint32_t vid) {
    assert(HW_API::getAVtoIPInitDone());
    av2ip.dumpVidRouteBandwidth(sfp, vid);
    printf("Output BW = %llu\n", HW_API::getTxEncapBandwidth(sfp));
    printf("Output Total BW = %llu\n", HW_API::getTxEncapTotalBandwidth(sfp));
    return;
}

void
HW_API::dumpTxAudRouteBandwidth(uint32_t sfp, uint32_t aud) {
    assert(HW_API::getAVtoIPInitDone());
    av2ip.dumpAudRouteBandwidth(sfp, aud, 0);
    printf("Output BW = %llu\n", HW_API::getTxEncapBandwidth(sfp));
    printf("Output Total BW = %llu\n", HW_API::getTxEncapTotalBandwidth(sfp));
    return;
}

void
HW_API::dumpTxMetaRouteBandwidth(uint32_t sfp, uint32_t meta) {
    assert(HW_API::getAVtoIPInitDone());
    av2ip.dumpMetaRouteBandwidth(sfp, meta);
    printf("Output BW = %llu\n", HW_API::getTxEncapBandwidth(sfp));
    printf("Output Total BW = %llu\n", HW_API::getTxEncapTotalBandwidth(sfp));
    return;
}

void
HW_API::dumpTxUSBRouteBandwidth(uint32_t sfp, uint32_t usb) {
    assert(HW_API::getAVtoIPInitDone());
    av2ip.dumpUSBRouteBandwidth(sfp, usb);
    printf("Output BW = %llu\n", HW_API::getTxEncapBandwidth(sfp));
    printf("Output Total BW = %llu\n", HW_API::getTxEncapTotalBandwidth(sfp));
    return;
}

void
HW_API::dumpTxVidSMPTE2110(uint32_t vid) {
    assert(HW_API::getAVtoIPInitDone());
    av2ip.dumpSMPTE2110Vid(vid);
    return;
}

bool
HW_API::getTxEncapOverflow(uint32_t sfp) {
    assert(HW_API::getAVtoIPInitDone());
    return av2ip.getEncapOverflow(sfp);
}

uint32_t
HW_API::get10GTxUSBChannel(uint32_t usb) {
  return usb;
}

int32_t
HW_API::get10GTxVideoChannel(HW_API::e_VideoType vid_type, uint32_t vid) {
  switch (vid_type) {
    case HW_API::VT_ASPEN422:
      return N_XGE_TX_USB +
             vid;
    case HW_API::VT_ASPEN444:
      return N_XGE_TX_USB +
             N_XGE_TX_VID_ASPEN422 +
             vid;
    case HW_API::VT_TICO:
      return N_XGE_TX_USB +
             n_tx_aspen_ts +
             vid;
    case HW_API::VT_ST2110:
      return N_XGE_TX_USB +
             n_tx_vid_ts +
             vid;
    default:
      return -1;
  }
}

uint32_t
HW_API::get10GTxAudioChannel(uint32_t aud) {
  return N_XGE_TX_USB + n_tx_vid_ts + N_XGE_TX_VID_SMPTE2110 + aud;
}

uint32_t
HW_API::get10GTxMetaChannel(uint32_t meta) {
  return N_XGE_TX_USB + n_tx_vid_ts + N_XGE_TX_VID_SMPTE2110 + N_XGE_TX_AUD + meta;
}

uint32_t
HW_API::get10GTxLowrateChannel(uint32_t lowrate) {
  return N_XGE_TX_USB + n_tx_vid_ts + N_XGE_TX_VID_SMPTE2110 + N_XGE_TX_AUD + N_XGE_TX_META + lowrate;
}

uint32_t
HW_API::get10GTxPCRChannel() {
  return N_XGE_TX_USB + n_tx_vid_ts + N_XGE_TX_VID_SMPTE2110 + N_XGE_TX_AUD + N_XGE_TX_META + N_XGE_TX_LOWRATE;
}

/* -- 10GE Rx -- */

ZYNQIPtoAV ip2av(HW_API::N_XGE_RX_VID_ASPENTICO,
                 HW_API::N_XGE_RX_VID_SMPTE2110,
                 HW_API::N_XGE_RX_AUD,
                 HW_API::N_XGE_RX_AUD_CH,
                 HW_API::N_XGE_RX_META,
                 HW_API::N_XGE_RX_USB,
                 HW_API::N_XGE_RX_LOWRATE,
                 HW_API::N_XGE_RX);

void
HW_API::initIPtoAV() {
  if ((HW_API::getFPGACapability("INC_XGE") <= 0) && (HW_API::getFPGACapability("INC_1GE") <= 0) && (HW_API::getFPGACapability("INC_2G5E") <= 0))
  {
    printf("INC_XGE or INC_1GE or INC_2G5E feature is required but not enabled!\n");
    return;
  }
  ip2av.init();
  return;
}

bool
HW_API::getIPtoAVInitDone() {
  return ip2av.getInitDone();
}

void
HW_API::setVidSFPChannel(uint32_t vid, uint32_t sfp, uint32_t channel, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setVidSFPChannel(vid, sfp, channel, main);
    return;
}

void
HW_API::setAudSFPChannel(uint32_t aud, uint32_t sfp, uint32_t channel, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setAudSFPChannel(aud, 0, sfp, channel, main);
    return;
}

void
HW_API::setUSBSFPChannel(uint32_t usb, uint32_t sfp, uint32_t channel, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setUSBSFPChannel(usb, sfp, channel, main);
    return;
}

void
HW_API::setMetaSFPChannel(uint32_t meta, uint32_t sfp, uint32_t channel, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setMetaSFPChannel(meta, sfp, channel, main);
    return;
}

void
HW_API::setPCRSFPChannel(uint32_t sfp, uint32_t channel, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setPCRSFPChannel(sfp, channel, main);
    return;
}

void
HW_API::setVidRedundancy(uint32_t vid, bool redundancy) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setVidRedundancy(vid, redundancy);
    return;
}

void
HW_API::setVidBnotA(uint32_t vid, bool b) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setVidABSel(vid, b);
    return;
}

bool
HW_API::getVidBnotA(uint32_t vid) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidABDet(vid);
}

void
HW_API::setAudRedundancy(uint32_t aud, bool redundancy) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setAudRedundancy(aud, 0, redundancy);
    return;
}

void
HW_API::setAudBnotA(uint32_t aud, bool b) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setAudABSel(aud, 0, b);
    return;
}

bool
HW_API::getAudBnotA(uint32_t aud) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudABDet(aud, 0);
}

void
HW_API::setMetaRedundancy(uint32_t meta, bool redundancy) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setMetaRedundancy(meta, redundancy);
    return;
}

void
HW_API::setMetaBnotA(uint32_t meta, bool b) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setMetaABSel(meta, b);
    return;
}

bool
HW_API::getMetaBnotA(uint32_t meta) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getMetaABDet(meta);
}

void
HW_API::setUSBRedundancy(uint32_t usb, bool redundancy) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setUSBRedundancy(usb, redundancy);
    return;
}

void
HW_API::setUSBBnotA(uint32_t usb, bool b) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setUSBABSel(usb, b);
    return;
}

bool
HW_API::getUSBBnotA(uint32_t usb) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getUSBABDet(usb);
}

void
HW_API::setPCRRedundancy(bool redundancy) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setPCRRedundancy(redundancy);
    return;
}

void
HW_API::setPCRBnotA(bool b) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setPCRABSel(b);
    return;
}

bool
HW_API::getPCRBnotA() {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getPCRABDet();
}

bool
HW_API::getVidStreamRTP(uint32_t vid, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidStreamRTP(vid, main);
}

uint64_t
HW_API::getVidStreamRTPErrors(uint32_t vid, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidStreamRTPErrors(vid, main);
}

void
HW_API::setVidStreamEnable(uint32_t vid, bool enable, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setVidStreamEnable(vid, enable, main);
    return;
}

uint32_t
HW_API::getVidPIDDet(uint32_t vid, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidPIDDet(vid, main);
}

uint32_t
HW_API::getVidPPF(uint32_t vid, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidPPF(vid, main);
}

bool
HW_API::getAudStreamRTP(uint32_t aud, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudStreamRTP(aud, 0, main);
}

uint64_t
HW_API::getAudStreamRTPErrors(uint32_t aud, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudStreamRTPErrors(aud, 0, main);
}

void
HW_API::setAudStreamEnable(uint32_t aud, bool enable, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setAudStreamEnable(aud, 0, enable, main);
    return;
}

bool
HW_API::getMetaStreamRTP(uint32_t meta, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getMetaStreamRTP(meta, main);
}

uint64_t
HW_API::getMetaStreamRTPErrors(uint32_t meta, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getMetaStreamRTPErrors(meta, main);
}

void
HW_API::setMetaStreamEnable(uint32_t meta, bool enable, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setMetaStreamEnable(meta, enable, main);
    return;
}

bool
HW_API::getUSBStreamRTP(uint32_t usb, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getUSBStreamRTP(usb, main);
}

uint64_t
HW_API::getUSBStreamRTPErrors(uint32_t usb, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getUSBStreamRTPErrors(usb, main);
}

void
HW_API::setUSBStreamEnable(uint32_t usb, bool enable, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setUSBStreamEnable(usb, enable, main);
    return;
}

bool
HW_API::getPCRStreamRTP(bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getPCRStreamRTP(main);
}

uint64_t
HW_API::getPCRStreamRTPErrors(bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getPCRStreamRTPErrors(main);
}

void
HW_API::setPCRStreamEnable(bool enable, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setPCRStreamEnable(enable, main);
    return;
}

uint32_t
HW_API::getAudPIDDet(uint32_t aud, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudPIDDet(aud, 0, main);
}

uint32_t
HW_API::getAudPPF(uint32_t aud, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudPPF(aud, 0, main);
}

void
HW_API::setVideoRxAspenPID(uint32_t vid, uint32_t pid) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setVidAspenPID(vid, pid);
    return;
}

void
HW_API::setVideoRxTicoPID(uint32_t vid, uint32_t pid) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setVidTicoPID(vid, pid);
    return;
}

void
HW_API::setVidFrameCount(uint32_t vid, uint32_t f0_cnt, uint32_t f1_cnt) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setVidFrameCount(vid, f0_cnt, f1_cnt);
    return;
}

HW_API::vidSTD
HW_API::getVidSTD(uint32_t vid) {
    assert(HW_API::getIPtoAVInitDone());
    HW_API::vidSTD std;
    IPtoAVType::vidSTD xstd = ip2av.getVidSTD(vid);
    std.hs_pol_high = xstd.hs_pol_high;
    std.vs_pol_high = xstd.vs_pol_high;
    std.sptl = xstd.sptl;
    std.spal = xstd.spal;
    std.tlpf0 = xstd.tlpf0;
    std.tlpf1 = xstd.tlpf1;
    std.alpf0 = xstd.alpf0;
    std.alpf1 = xstd.alpf1;
    std.soha = xstd.soha;
    std.sova0 = xstd.sova0;
    std.sova1 = xstd.sova1;
    std.sova_ext0 = xstd.sova_ext0;
    std.sova_ext1 = xstd.sova_ext1;
    std.rate_num = xstd.rate_num;
    std.rate_den = xstd.rate_den;
    std.hs_start = xstd.hs_start;
    std.hs_stop = xstd.hs_stop;
    std.vs_start0 = xstd.vs_start0;
    std.vs_stop0 = xstd.vs_stop0;
    std.vs_start1 = xstd.vs_start1;
    std.vs_stop1 = xstd.vs_stop1;
    std.vs_hpos0 = xstd.vs_hpos0;
    std.vs_hpos1 = xstd.vs_hpos1;
    std.copyright = xstd.copyright;
    std.stream_type = xstd.stream_type;
    return std;
}

int
HW_API::getVidColourSpecification(uint32_t vid, IPtoAVType::aspenColourSpecification* colourSpecification) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidColourSpecification(vid, colourSpecification);
}

int
HW_API::getVidElectroopticalTransferFunction(uint32_t vid, IPtoAVType::aspenElectroopticalTransferFunction* eotf) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidElectroopticalTransferFunction(vid, eotf);
}

int
HW_API::getVidColourSpace(uint32_t vid, IPtoAVType::aspenColourSpace* colourSpace) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidColourSpace(vid, colourSpace);
}

int
HW_API::getVidSampleStructure(uint32_t vid, IPtoAVType::aspenSampleStructure* sampleStructure) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidSampleStructure(vid, sampleStructure);
}

int
HW_API::getVidFrameRate(uint32_t vid, float* framerate) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidFrameRate(vid, framerate);
}

int
HW_API::getVidSMPTE2110ASPL(uint32_t vid, uint16_t* aspl) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidSMPTE2110ASPL(vid, aspl);
}

int
HW_API::getVidSMPTE2110SamplesPerPixel(uint32_t vid, uint8_t* samples_per_pixel) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidSMPTE2110SamplesPerPixel(vid, samples_per_pixel);
}

int
HW_API::getVidSMPTE2110SampleWidth(uint32_t vid, uint8_t* sample_width) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidSMPTE2110SampleWidth(vid, sample_width);
}

int
HW_API::getVidSMPTE2110RGB(uint32_t vid, bool* rgb) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidSMPTE2110RGB(vid, rgb);
}

int
HW_API::getVidSMPTE2110Sampling(uint32_t vid, char* sampling) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidSMPTE2110Sampling(vid, sampling);
}

int
HW_API::getVidSMPTE2110Sampling(uint32_t vid, IPtoAVType::smpte2110_20_Sampling* sampling) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidSMPTE2110Sampling(vid, sampling);
}

int
HW_API::setVidSMPTE2110Config(uint32_t vid, uint16_t aspl, const char* sampling, uint8_t sample_width) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.setVidSMPTE2110Config(vid, aspl, sampling, sample_width);
}

int
HW_API::setVidSMPTE2110Config(uint32_t vid, uint16_t aspl, IPtoAVType::smpte2110_20_Sampling sampling, uint8_t sample_width) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.setVidSMPTE2110Config(vid, aspl, sampling, sample_width);
}

int
HW_API::getVidSMPTE2110Status(uint32_t vid, IPtoAVType::vid2110Status* status) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidSMPTE2110Status(vid, status);
}

void
HW_API::dumpVidSTD(uint32_t vid) {
    assert(HW_API::getIPtoAVInitDone());
    HW_API::vidSTD std = HW_API::getVidSTD(vid);
    if (vid < N_XGE_RX_VID_ASPENTICO) {
      printf("10GE Rx Vid %u ASPEN/TICO Standard:\n", vid);
      printf("  HS Pol      = %u\n", std.hs_pol_high);
      printf("  VS Pol      = %u\n", std.vs_pol_high);
      printf("  SPTL        = %u\n", std.sptl);
      printf("  SPAL        = %u\n", std.spal);
      printf("  TLPF0       = %u\n", std.tlpf0);
      printf("  TLPF1       = %u\n", std.tlpf1);
      printf("  ALPF0       = %u\n", std.alpf0);
      printf("  ALPF1       = %u\n", std.alpf1);
      printf("  SOHA        = %u\n", std.soha);
      printf("  SOVA0       = %u\n", std.sova0);
      printf("  SOVA1       = %u\n", std.sova1);
      printf("  SOVA_EXT0   = %u\n", std.sova_ext0);
      printf("  SOVA_EXT1   = %u\n", std.sova_ext1);
      printf("  RATE_NUM    = %u\n", std.rate_num);
      printf("  RATE_DEN    = %u\n", std.rate_den);
      printf("  HS_START    = %u\n", std.hs_start);
      printf("  HS_STOP     = %u\n", std.hs_stop);
      printf("  VS_START0   = %u\n", std.vs_start0);
      printf("  VS_STOP0    = %u\n", std.vs_stop0);
      printf("  VS_START1   = %u\n", std.vs_start1);
      printf("  VS_STOP1    = %u\n", std.vs_stop1);
      printf("  VS_HPOS0    = %u\n", std.vs_hpos0);
      printf("  VS_HPOS1    = %u\n", std.vs_hpos1);
      printf("  COPYRIGHT   = %u\n", std.copyright);
      printf("  STREAM_TYPE = %u\n", std.stream_type);
      float framerate;
      HW_API::getVidFrameRate(vid,&framerate);
      printf("10GE Rx Vid %u Frame Rate = %.2f\n", vid, framerate);
      printf("10GE Rx Vid %u PID = %u\n", vid, HW_API::getVidPIDDet(vid));
      printf("10GE Rx Vid %u PPF = %u\n", vid, HW_API::getVidPPF(vid));
      IPtoAVType::aspenColourSpecification colourSpecification;
      HW_API::getVidColourSpecification(vid,&colourSpecification);
      printf("10GE Rx Vid %u Colour Specification = %u\n", vid, colourSpecification);
      IPtoAVType::aspenElectroopticalTransferFunction eotf;
      HW_API::getVidElectroopticalTransferFunction(vid,&eotf);
      printf("10GE Rx Vid %u EOTF = %u\n", vid, eotf);
      IPtoAVType::aspenColourSpace colourSpace;
      HW_API::getVidColourSpace(vid,&colourSpace);
      printf("10GE Rx Vid %u Colour Space = %u\n", vid, colourSpace);
      IPtoAVType::aspenSampleStructure sampleStructure;
      HW_API::getVidSampleStructure(vid,&sampleStructure);
      printf("10GE Rx Vid %u Sample Structure = %u\n", vid, sampleStructure);
    } else {
      char     sampling[16];
      uint16_t aspl;
      uint8_t  samples_per_pixel;
      uint8_t  sample_width;
      bool     rgb;
      HW_API::getVidSMPTE2110Sampling(vid, sampling);
      HW_API::getVidSMPTE2110ASPL(vid, &aspl);
      HW_API::getVidSMPTE2110SamplesPerPixel(vid, &samples_per_pixel);
      HW_API::getVidSMPTE2110SampleWidth(vid, &sample_width);
      HW_API::getVidSMPTE2110RGB(vid, &rgb);
      printf("10GE Rx Vid %u SMPTE 2110-20 Configuration:\n", vid);
      printf("  ASPL              = %u\n", aspl);
      printf("  Sampling          = %s\n", sampling);
      printf("  Sample Width      = %u\n", sample_width);
      printf("  Samples Per Pixel = %u\n", samples_per_pixel);
      printf("  RGB               = %u\n", rgb);
      printf("10GE Rx Vid %u SMPTE 2110-20 Standard:\n", vid);
      printf("  SPAL  = %u\n", std.spal);
      printf("  ALPF0 = %u\n", std.alpf0);
      printf("  ALPF1 = %u\n", std.alpf1);
      float framerate;
      HW_API::getVidFrameRate(vid,&framerate);
      printf("10GE Rx Vid %u Frame Rate = %.2f\n", vid, framerate);
      IPtoAVType::vid2110Status status;
      HW_API::getVidSMPTE2110Status(vid, &status);
      printf("10GE Rx Vid %u SMPTE 2110-20 Status:\n", vid);
      printf("  Locked       = %u\n", status.locked);
      printf("  Interlaced   = %u\n", status.interlaced);
      printf("  Error        = %u\n", status.error);
      printf("  BytesPerRow  = %u\n", status.bytes_per_row);
      printf("  RowsPerField = %u\n", status.rows_per_field);
      printf("  FieldRate F0 = %.2f\n", status.timestamp_fieldrate_f0);
      printf("  FieldRate F1 = %.2f\n", status.timestamp_fieldrate_f1);
    }
    return;
}

bool
HW_API::getAudioRxCompressed(uint32_t aud) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudCompressed(aud, 0);
}

uint32_t
HW_API::getAudioRxSamplingFrequency(uint32_t aud) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudSamplingFrequency(aud, 0);
}

bool
HW_API::getAudioRxHBR(uint32_t aud) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudHBR(aud, 0);
}

uint8_t
HW_API::getAudioRxType(uint32_t aud, char* aud_type) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudType(aud, 0, aud_type);
}

uint8_t
HW_API::getAudioRxChans(uint32_t aud) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudChans(aud, 0);
}

void
HW_API::setAudioRxPID(uint32_t aud, uint32_t pid) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.setAudPID(aud, 0, pid);
}

void
HW_API::setAudioRxAES67Ctrl(uint32_t aud, uint32_t chans, uint32_t sf_hz) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.setAudRxAES67Ctrl(aud, 0, chans, sf_hz);
}

void
HW_API::setUseRemotePCR(bool remote) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.setUseRemotePCR(remote);
    return;
}

uint64_t
HW_API::getRxSFPTSBandwidth(uint32_t sfp) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getSFPTSBandwidth(sfp);
}

uint64_t
HW_API::getRxVidTSBandwidth(uint32_t vid, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidTSBandwidth(vid, main);
}

uint64_t
HW_API::getRxAudTSBandwidth(uint32_t aud, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudTSBandwidth(aud, 0, main);
}

uint64_t
HW_API::getRxMetaTSBandwidth(uint32_t meta, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getMetaTSBandwidth(meta, main);
}

uint64_t
HW_API::getRxUSBTSBandwidth(uint32_t usb, bool main) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getUSBTSBandwidth(usb, main);
}

uint64_t
HW_API::getRxVidBandwidth(uint32_t vid) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getVidBandwidth(vid);
}

uint64_t
HW_API::getRxAudBandwidth(uint32_t aud) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getAudBandwidth(aud, 0);
}

uint64_t
HW_API::getRxMetaBandwidth(uint32_t meta) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getMetaBandwidth(meta);
}

uint64_t
HW_API::getRxUSBBandwidth(uint32_t usb) {
    assert(HW_API::getIPtoAVInitDone());
    return ip2av.getUSBBandwidth(usb);
}

void
HW_API::dumpRxVidRouteBandwidth(uint32_t sfp, uint32_t vid) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.dumpVidRouteBandwidth(sfp, vid);
    return;
}

void
HW_API::dumpRxAudRouteBandwidth(uint32_t sfp, uint32_t aud) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.dumpAudRouteBandwidth(sfp, aud, 0);
    return;
}

void
HW_API::dumpRxMetaRouteBandwidth(uint32_t sfp, uint32_t meta) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.dumpMetaRouteBandwidth(sfp, meta);
    return;
}

void
HW_API::dumpRxUSBRouteBandwidth(uint32_t sfp, uint32_t usb) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.dumpUSBRouteBandwidth(sfp, usb);
    return;
}

void
HW_API::allowDescramble10GERxVid(uint32_t vid, bool descramble) {
    assert(HW_API::getIPtoAVInitDone());
    ip2av.allowVidDescramble(vid, descramble);
    return;
}

int32_t
HW_API::get10GRxVideoChannel(HW_API::e_VideoType vid_type, uint32_t vid) {
  switch (vid_type) {
    case HW_API::VT_ASPEN422:
    case HW_API::VT_ASPEN444:
    case HW_API::VT_TICO:
      return vid;
    case HW_API::VT_ST2110:
      return N_XGE_RX_VID_ASPENTICO +
             vid;
    default:
      return -1;
  }
}

uint32_t
HW_API::get10GRxAudioChannel(uint32_t aud) {
  return N_XGE_RX_VID + 4*aud;
}

uint32_t
HW_API::get10GRxMetaChannel(uint32_t meta) {
  return N_XGE_RX_VID + 4*N_XGE_RX_AUD + meta;
}

uint32_t
HW_API::get10GRxUSBChannel(uint32_t usb) {
  return N_XGE_RX_VID + 4*N_XGE_RX_AUD + N_XGE_RX_META + usb;
}

uint32_t
HW_API::get10GRxPCRChannel() {
  return N_XGE_RX_VID + 4*N_XGE_RX_AUD + N_XGE_RX_META + N_XGE_RX_USB + N_XGE_RX_LOWRATE;
}

/* -- Frame Buffer and Scaler -- */

ZYNQVidScale scaler_a                     [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];
ZYNQVidScale scaler_b                     [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];
ZYNQUpDownScaleWport sc_wport             [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS][4];
ZYNQUpDownScaleDecWport sc_dec_wport      [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];
ZYNQPlayoutCtrl sc_po_ctrl                [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];
ZYNQRasterGenProg sc_raster               [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];
UpDownScalePreAndPost sc_pnp_core         [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];
UpDownScaleDualPost sc_dlp_core           [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];
UpDownScaleQuadDualPost sc_qdlp_core      [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];
UpDownScaleSinglePost sc_sp_core          [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];
UpDownScaleSinglePre sc_spre_core         [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];
ZYNQUpDownScaleWrapper scale_path         [HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS];

int
HW_API::getScalerPathArchType(uint32_t path) {
    assert(path < HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS);

    uint32_t path_arch_type = 0;
    bool path_valid     = false;
    if (path < (uint32_t)HW_API::getFPGACapability("N_SCALER"))
    {
      path_arch_type = 0;
      path_valid     = true;
    } else if ((path - (uint32_t)HW_API::getFPGACapability("N_SCALER")) < (uint32_t)HW_API::getFPGACapability("N_FRAME_BUFFER"))
    {
      path_arch_type = 1;
      path_valid     = true;
    } else if ((path - (uint32_t)HW_API::getFPGACapability("N_SCALER") - (uint32_t)HW_API::getFPGACapability("N_FRAME_BUFFER")) < (uint32_t)HW_API::getFPGACapability("N_PIP_SCALER_PATHS"))
    {
      path_arch_type = 2;
      path_valid     = true;
    }

    if (path_valid) {
      return path_arch_type;
    } else {
      return -1;
    }
}

void
HW_API::initScalerPath(uint32_t path) {
    assert(path < HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS);

    uint32_t path_arch_type = 0;
    bool path_valid     = false;
    int path_arch = getScalerPathArchType(path);

    if (path_arch != -1) {
      path_valid = true;
      path_arch_type = uint32_t(path_arch);
    }

    if (!path_valid)
    {
      printf("N_SCALER or N_FRAME_BUFFER or N_PIP_SCALER_PATHS feature is required but not enabled for this path!\n");
      return;
    }
    if (HW_API::getScalerArchMatch("PRE_AND_POST", path_arch_type)) {
      printf("Initializing PRE_AND_POST architecture!\n");
      scaler_a[path].localInit(path, 0);
      scaler_b[path].localInit(path, 1);
      sc_raster[path].localInit(path);
      scale_path[path].localInit(path);
      sc_pnp_core[path].init(&scaler_a[path],
          &scaler_b[path], &sc_raster[path]);
      scale_path[path].init(&sc_pnp_core[path]);
    } else if (HW_API::getScalerArchMatch("DUAL_POST", path_arch_type)) {
      printf("Initializing DUAL_POST architecture!\n");
      sc_wport[path][0].localInit(path, 0);
      scaler_a[path].localInit(path, 0);
      scaler_b[path].localInit(path, 1);
      sc_po_ctrl[path].localInit(path);
      sc_raster[path].localInit(path);
      scale_path[path].localInit(path);
      sc_dlp_core[path].init(&sc_wport[path][0], &scaler_a[path],
          &scaler_b[path], &sc_po_ctrl[path], &sc_raster[path]);
      scale_path[path].init(&sc_dlp_core[path]);
    } else if (HW_API::getScalerArchMatch("SINGLE_POST", path_arch_type)) {
        printf("Initializing SINGLE_POST architecture!\n");
        sc_wport[path][0].localInit(path, 0);
        scaler_b[path].localInit(path, 1);
        sc_raster[path].localInit(path);
        scale_path[path].localInit(path);
        sc_sp_core[path].init(&sc_wport[path][0], &scaler_b[path],
            &sc_raster[path]);
        scale_path[path].init(&sc_sp_core[path]);
    } else if (HW_API::getScalerArchMatch("SINGLE_PRE", path_arch_type)) {
      printf("Initializing SINGLE_PRE architecture!\n");
      scaler_a[path].localInit(path, 0);
      scaler_b[path].localInit(path, 1);
      sc_raster[path].localInit(path);
      scale_path[path].localInit(path);
      sc_spre_core[path].init(&scaler_a[path],
          &scaler_b[path], &sc_raster[path]);
      scale_path[path].init(&sc_spre_core[path]);
    } else if (HW_API::getScalerArchMatch("QUAD_DUAL_POST", path_arch_type)) {
      printf("Initializing QUAD_DUAL_POST architecture!\n");
      sc_wport[path][0].localInit(path, 0);
      sc_wport[path][1].localInit(path, 1);
      sc_wport[path][2].localInit(path, 2);
      sc_wport[path][3].localInit(path, 3);
      scaler_a[path].localInit(path, 0);
      scaler_b[path].localInit(path, 1);
      sc_po_ctrl[path].localInit(path);
      sc_raster[path].localInit(path);
      scale_path[path].localInit(path);
      sc_qdlp_core[path].init(&sc_wport[path][0], &sc_wport[path][1], &sc_wport[path][2], &sc_wport[path][3],
          &scaler_a[path], &scaler_b[path], &sc_po_ctrl[path], &sc_raster[path]);
      scale_path[path].init(&sc_qdlp_core[path]);
      scale_path[path].set2siNotQuad(false);
    } else {
      printf("Scaler architecture could not be determined and so init was not done!\n");
      return;
    }
    return;
}

bool
HW_API::getScalerPathInitDone(uint32_t path) {
    assert(path < HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS+HW_API::N_PIP_SCALER_PATHS);
    return scale_path[path].getInitDone();
}

bool
HW_API::getScalerYCbCrNotRGB(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].getYCbCrNotRGB();
}

uint32_t
HW_API::getScalerMaxASPL(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].getMaxASPL();
}

uint32_t
HW_API::getScalerMaxALPF(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].getMaxALPF();
}

uint32_t
HW_API::getScalerSDRAMRPortWidth(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].getSDRAMRPortWidth();
}

uint32_t
HW_API::getScalerSDRAMRBurstLength(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].getSDRAMBurstLength();
}

uint32_t
HW_API::getScalerPixelsPerReadBurst(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].getPixelsPerReadBurst();
}

uint32_t
HW_API::getScalerMaxReadBurstsPerLine(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].getMaxReadBurstsPerLine();
}

uint8_t
HW_API::getScalerLossOfInputImagePage(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].getLossOfInputImagePage();
}

void
HW_API::setUseExternalClock(uint32_t path, bool use) {
  assert(HW_API::getScalerPathInitDone(path));
  scale_path[path].setUseExternalClock(use);
}

bool
HW_API::getUseExternalClock(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].getUseExternalClock();
}

void
HW_API::useScalerPath(uint32_t path, bool enable) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setFrameBufferEnable(enable);
    return;
}

void
HW_API::setScalerPhase(uint32_t path, uint32_t hphase, uint32_t vphase) {
    assert(HW_API::getScalerPathInitDone(path));
    sc_raster[path].setHVPhase(0, // Set master phase, others will follow
                               hphase, vphase);
    return;
}

void
HW_API::dumpScalerConfig(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].dumpConfigInfo();
    scale_path[path].dumpSubBlockConfig();
    return;
}

void
HW_API::dumpScalerStatus(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].dumpSubBlockStatus();
    scale_path[path].dumpFrameRateStatus();
    return;
}

void
HW_API::getBorderSettings(uint32_t path, MVScalerTopType::BorderSettings *border_settings, bool sel_scaler_b)
{
    assert(HW_API::getScalerPathInitDone(path));
    bool use_b = scale_path[path].getFrameBufferUseB();
    int pipe_idx = use_b ? 1 : 0;
    if (sel_scaler_b) {
      scaler_b[path].getBorderSettings(pipe_idx, border_settings);
    } else {
      scaler_a[path].getBorderSettings(pipe_idx, border_settings);
    }
}

void
HW_API::setBorderSettings(uint32_t path, MVScalerTopType::BorderSettings * border_settings, bool sel_scaler_b)
{
    assert(HW_API::getScalerPathInitDone(path));
    bool use_b = scale_path[path].getFrameBufferUseB();
    int pipe_idx = use_b ? 1 : 0;
    if (sel_scaler_b) {
      scaler_b[path].setBorderSettings(pipe_idx, border_settings);
    } else {
      scaler_a[path].setBorderSettings(pipe_idx, border_settings);
    }
    return;
}

void
HW_API::setBorderColour(uint32_t path, uint32_t yg, uint32_t cbb, uint32_t crr, bool sel_scaler_b)
{
    assert(HW_API::getScalerPathInitDone(path));
    bool use_b = scale_path[path].getFrameBufferUseB();
    int pipe_idx = use_b ? 1 : 0;
    if (sel_scaler_b) {
      scaler_b[path].updateBorderColour(pipe_idx, yg, cbb, crr);
    } else {
      scaler_a[path].updateBorderColour(pipe_idx, yg, cbb, crr);
    }
    return;
}

void
HW_API::getScalerSettings(uint32_t path, MVScalerTopType::ScalerSettings * scaler_settings, bool sel_scaler_b)
{
    assert(HW_API::getScalerPathInitDone(path));
    bool use_b = scale_path[path].getFrameBufferUseB();
    int pipe_idx = use_b ? 1 : 0;
    if (sel_scaler_b) {
      scaler_b[path].getScalerSettings(pipe_idx, scaler_settings);
    } else {
      scaler_a[path].getScalerSettings(pipe_idx, scaler_settings);
    }
    return;
}

void
HW_API::startScalerSwitch(uint32_t path, HW_API::ScalerSwitchType switch_type) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].startSwitch((UpDownScaleWrapperType::SwitchType)switch_type);
    return;
}

void
HW_API::switchScalerInput(uint32_t path, RasterTypes::CVTParameters in_params, HW_API::ScalerFrameRate in_rate, HW_API::scColourFormat_type colour) {
    assert(HW_API::getScalerPathInitDone(path));
    UpDownScaleWrapperType::FrameRate rate;
    rate.frame_rate_num = in_rate.frame_rate_num;
    rate.frame_rate_den = in_rate.frame_rate_den;
    scale_path[path].switchInput(&in_params, rate, (UpDownScaleWrapperType::ColourFormat_type)colour);
    return;
}

void
HW_API::switchScalerInput(uint32_t path, RasterTypes::AspenParameters in_params, HW_API::ScalerFrameRate in_rate, HW_API::scColourFormat_type colour) {
    assert(HW_API::getScalerPathInitDone(path));
    UpDownScaleWrapperType::FrameRate rate;
    rate.frame_rate_num = in_rate.frame_rate_num;
    rate.frame_rate_den = in_rate.frame_rate_den;
    scale_path[path].switchInput(&in_params, rate, (UpDownScaleWrapperType::ColourFormat_type)colour);
    return;
}

void
HW_API::switchScalerInput(uint32_t path, RasterTypes::RasterParameters in_raster, HW_API::ScalerFrameRate in_rate, HW_API::scColourFormat_type colour) {
    assert(HW_API::getScalerPathInitDone(path));
    UpDownScaleWrapperType::FrameRate rate;
    rate.frame_rate_num = in_rate.frame_rate_num;
    rate.frame_rate_den = in_rate.frame_rate_den;
    scale_path[path].switchInput(&in_raster, rate, (UpDownScaleWrapperType::ColourFormat_type)colour);
    return;
}

void
HW_API::switchScalerPathSettings(uint32_t path, HW_API::ScalerSettings * settings) {
    assert(HW_API::getScalerPathInitDone(path));
    UpDownScaleWrapperType::ScaleSettings sc_settings;
    sc_settings.crop_top = settings->crop_top;
    sc_settings.crop_left = settings->crop_left;
    sc_settings.crop_height = settings->crop_height;
    sc_settings.crop_width = settings->crop_width;
    sc_settings.aspect_mode = (MVScalerTopType::AspectMode)settings->aspect_mode;
    sc_settings.angle = MVScalerTopType::ROT_0;
    sc_settings.brdr_yg = settings->brdr_yg;
    sc_settings.brdr_cbb = settings->brdr_cbb;
    sc_settings.brdr_crr = settings->brdr_crr;
    scale_path[path].switchPathSettings(&sc_settings);
    return;
}

void
HW_API::finishScalerSwitch(uint32_t path, uint8_t ignoreNFrames) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].finishSwitch(ignoreNFrames);
    return;
}

void
HW_API::setScalerOutput(uint32_t path, RasterTypes::CVTParameters out_params, HW_API::ScalerFrameRate out_rate, HW_API::scColourFormat_type colour) {
    assert(HW_API::getScalerPathInitDone(path));
    assert(HW_API::getVidProcInitDone());
    UpDownScaleWrapperType::FrameRate rate;
    rate.frame_rate_num = out_rate.frame_rate_num;
    rate.frame_rate_den = out_rate.frame_rate_den;
    scale_path[path].setOutput(&out_params, rate, (UpDownScaleWrapperType::ColourFormat_type)colour);

    // Set Border to black based on colour format
    // Incorporate into scaler api?
    MVScalerTopType::BorderSettings hw_bordersettings;
    HW_API::getBorderSettings(path, &hw_bordersettings);

    if        (colour == HW_API::CSF_YCRCB_444) {
      hw_bordersettings.brdr_yg       = 0x80;
      hw_bordersettings.brdr_cbb      = 0x80;
      hw_bordersettings.brdr_crr      = 0x10; // YG  Sample 0 is Y / G  in HDL
    } else if (colour == HW_API::CSF_YCRCB_422) {// Scaler internals running at Y444
      hw_bordersettings.brdr_yg       = 0x80;
      hw_bordersettings.brdr_cbb      = 0x80;
      hw_bordersettings.brdr_crr      = 0x10; // YG  Sample 0 is Y / G  in HDL
    } else {          // CSF_RGB
      hw_bordersettings.brdr_yg       = 0x10;
      hw_bordersettings.brdr_cbb      = 0x10;
      hw_bordersettings.brdr_crr      = 0x10;
    }
    hw_bordersettings.brdr_yg       = hw_bordersettings.brdr_yg <<2;  // (10bit sample width - 8 bit values);
    hw_bordersettings.brdr_cbb      = hw_bordersettings.brdr_cbb<<2;  //
    hw_bordersettings.brdr_crr      = hw_bordersettings.brdr_crr<<2;  //
    HW_API::setBorderSettings(path, &hw_bordersettings);

    return;
}

void
HW_API::setScalerOutput(uint32_t path, RasterTypes::AspenParameters out_params, HW_API::ScalerFrameRate out_rate, HW_API::scColourFormat_type colour) {
    assert(HW_API::getScalerPathInitDone(path));
    assert(HW_API::getVidProcInitDone());
    UpDownScaleWrapperType::FrameRate rate;
    rate.frame_rate_num = out_rate.frame_rate_num;
    rate.frame_rate_den = out_rate.frame_rate_den;
    scale_path[path].setOutput(&out_params, rate, (UpDownScaleWrapperType::ColourFormat_type)colour);

    // Set Border to black based on colour format
    // Incorporate into scaler api?
    MVScalerTopType::BorderSettings hw_bordersettings;
    HW_API::getBorderSettings(path, &hw_bordersettings);

    if        (colour == HW_API::CSF_YCRCB_444) {
      hw_bordersettings.brdr_yg       = 0x80;
      hw_bordersettings.brdr_cbb      = 0x80;
      hw_bordersettings.brdr_crr      = 0x10; // YG  Sample 0 is Y / G  in HDL
    } else if (colour == HW_API::CSF_YCRCB_422) {// Scaler internals running at Y444
      hw_bordersettings.brdr_yg       = 0x80;
      hw_bordersettings.brdr_cbb      = 0x80;
      hw_bordersettings.brdr_crr      = 0x10; // YG  Sample 0 is Y / G  in HDL
    } else {          // CSF_RGB
      hw_bordersettings.brdr_yg       = 0x10;
      hw_bordersettings.brdr_cbb      = 0x10;
      hw_bordersettings.brdr_crr      = 0x10;
    }
    hw_bordersettings.brdr_yg       = hw_bordersettings.brdr_yg <<2;  // (10bit sample width - 8 bit values);
    hw_bordersettings.brdr_cbb      = hw_bordersettings.brdr_cbb<<2;  //
    hw_bordersettings.brdr_crr      = hw_bordersettings.brdr_crr<<2;  //
    HW_API::setBorderSettings(path, &hw_bordersettings);
    return;
}

void
HW_API::setScalerOutput(uint32_t path, RasterTypes::RasterParameters out_raster, HW_API::ScalerFrameRate out_rate, HW_API::scColourFormat_type colour) {
    assert(HW_API::getScalerPathInitDone(path));
    assert(HW_API::getVidProcInitDone());
    UpDownScaleWrapperType::FrameRate rate;
    rate.frame_rate_num = out_rate.frame_rate_num;
    rate.frame_rate_den = out_rate.frame_rate_den;
    scale_path[path].setOutput(&out_raster, rate, (UpDownScaleWrapperType::ColourFormat_type)colour);

    // Set Border to black based on colour format
    // Incorporate into scaler api?
    MVScalerTopType::BorderSettings hw_bordersettings;
    HW_API::getBorderSettings(path, &hw_bordersettings);

    if        (colour == HW_API::CSF_YCRCB_444) {
      hw_bordersettings.brdr_yg       = 0x80;
      hw_bordersettings.brdr_cbb      = 0x80;
      hw_bordersettings.brdr_crr      = 0x10; // YG  Sample 0 is Y / G  in HDL
    } else if (colour == HW_API::CSF_YCRCB_422) {// Scaler internals running at Y444
      hw_bordersettings.brdr_yg       = 0x80;
      hw_bordersettings.brdr_cbb      = 0x80;
      hw_bordersettings.brdr_crr      = 0x10; // YG  Sample 0 is Y / G  in HDL
    } else {          // CSF_RGB
      hw_bordersettings.brdr_yg       = 0x10;
      hw_bordersettings.brdr_cbb      = 0x10;
      hw_bordersettings.brdr_crr      = 0x10;
    }
    hw_bordersettings.brdr_yg       = hw_bordersettings.brdr_yg <<2;  // (10bit sample width - 8 bit values);
    hw_bordersettings.brdr_cbb      = hw_bordersettings.brdr_cbb<<2;  //
    hw_bordersettings.brdr_crr      = hw_bordersettings.brdr_crr<<2;  //
    HW_API::setBorderSettings(path, &hw_bordersettings);
    return;
}

void
HW_API::setScalerOutputPip(uint32_t path, HW_API::ScalerPipSettings pip_settings, RasterTypes::CVTParameters raster_out_params, HW_API::ScalerFrameRate out_rate, HW_API::scColourFormat_type colour) {
    assert(HW_API::getScalerPathInitDone(path));
    assert(HW_API::getVidProcInitDone());
    RasterParameters raster_out_params_i(raster_out_params);
    bool raster_out_interlaced = false;
    if(raster_out_params.alpf[1] > 0){
      raster_out_interlaced = true;
    }

    // Calculate Scaler Output Window
    RasterTypes::RasterParameters scaler_out_params;
    scaler_out_params.h_tot_start = 0;
    scaler_out_params.h_tot_stop = pip_settings.pip_h_right - pip_settings.pip_h_left+10;
    scaler_out_params.h_act_start = 0;
    scaler_out_params.h_act_stop = pip_settings.pip_h_right - pip_settings.pip_h_left;

    scaler_out_params.v_tot_start = 0;
    scaler_out_params.v_tot_stop = pip_settings.pip_v_bottom - pip_settings.pip_v_top+10;
    scaler_out_params.v_act_start[0] = 0;
    scaler_out_params.v_act_stop[0] = pip_settings.pip_v_bottom - pip_settings.pip_v_top;
    if(raster_out_interlaced){
      scaler_out_params.v_act_start[1] = 0;
      scaler_out_params.v_act_stop[1] = pip_settings.pip_v_bottom - pip_settings.pip_v_top;
    }
    raster_out_params_i.h_act_stop       = pip_settings.pip_h_right+raster_out_params_i.h_act_start;
    if (raster_out_params_i.h_act_stop > raster_out_params_i.h_tot_stop) {
      raster_out_params_i.h_act_stop -= raster_out_params_i.h_tot_stop;
      raster_out_params_i.h_act_stop -= 1;
    }
    raster_out_params_i.h_act_start      = pip_settings.pip_h_left+raster_out_params_i.h_act_start;
    raster_out_params_i.v_act_stop[0]    = pip_settings.pip_v_bottom+raster_out_params_i.v_act_start[0];
    if (raster_out_params_i.v_act_stop[0] > raster_out_params_i.v_tot_stop) {
      raster_out_params_i.v_act_stop[0] -= raster_out_params_i.v_tot_stop;
      raster_out_params_i.v_act_stop[0] -= 1;
    }
    raster_out_params_i.v_act_start[0]   = pip_settings.pip_v_top+raster_out_params_i.v_act_start[0];
    if (raster_out_interlaced) {
      raster_out_params_i.v_act_stop[1]    = pip_settings.pip_v_bottom+raster_out_params_i.v_act_start[1];
      raster_out_params_i.v_act_start[1]   = pip_settings.pip_v_top+raster_out_params_i.v_act_start[1];
      if (raster_out_params_i.v_act_stop[1] > raster_out_params_i.v_tot_stop) {
        raster_out_params_i.v_act_stop[1] -= raster_out_params_i.v_tot_stop;
        raster_out_params_i.v_act_stop[1] -= 1;
      }
    }
    UpDownScaleWrapperType::FrameRate rate;
    rate.frame_rate_num = out_rate.frame_rate_num;
    rate.frame_rate_den = out_rate.frame_rate_den;
    scale_path[path].setOutputPip(&scaler_out_params, &raster_out_params_i, rate, (UpDownScaleWrapperType::ColourFormat_type)colour);
    return;
}

int
HW_API::setScalerPipPath(uint32_t path, HW_API::ScalerPipSettings pip_settings, RasterTypes::CVTParameters raster_out_params, HW_API::ScalerFrameRate out_rate, HW_API::scColourFormat_type colour, uint32_t lock_type) {
    // Intended to be a macro function which configures the Scaler Architecture and associated PiP Region
    // Assumed Pip region not enabled during this configuration

    // Interlaced pip vertical ranges are expressed with respect to the 'total active raster'
    //  Values will be divided by 2 and assigned to each field.
    //  example 1080i60 bottom right quad would be Horizontal 960 to 1920 and Vertical 540 to 1080

    // return
    //   0 complete
    //  -1 failed

    // lock_type =  0 no lock
    //              1 source lock
    //              2 ptp lock
    //              3 genlock

    const uint32_t vidmix_idx = 0;

    int path_arch = getScalerPathArchType(path);
    bool pip_scaler_path = false;

    // Invalid Locktype
    if (lock_type >= UpDownScaleWrapperType::NUM_LOCKTYPE) {
      return -1;
    }
    // Check if Pip scaler path
    if (path_arch == 2) {
      pip_scaler_path = true;
    }

    assert(HW_API::getScalerPathInitDone(path));
    assert(HW_API::getVidProcInitDone());
    RasterParameters raster_out_params_i(raster_out_params);

    // Check if 4K60 type rates.
    //  PiP paths have a special configuration to support this.
    uint32_t pixel_rate_calc;
    bool high_rate_pip_mode = false;
    pixel_rate_calc =   (raster_out_params_i.v_tot_stop - raster_out_params_i.v_tot_start)
                      * (raster_out_params_i.h_tot_stop - raster_out_params_i.h_tot_start);
    pixel_rate_calc /= out_rate.frame_rate_den;
    pixel_rate_calc *= out_rate.frame_rate_num;

    if (      (pixel_rate_calc > pip_scaler_path_pixel_clock_limit)
          &&  (pip_scaler_path)
        ){
      high_rate_pip_mode = true;
    }

    uint32_t scaler_raster_buffer_phase;
    if (high_rate_pip_mode) {
      scaler_raster_buffer_phase = pip_scaler_raster_buffer_phase_pip_path_high_rate;
    } else {
      scaler_raster_buffer_phase = pip_scaler_raster_buffer_phase;
    }

    bool raster_out_interlaced = false;
    if(raster_out_params.alpf[1] > 0){
      raster_out_interlaced = true;
    }

    // Calculate Scaler Output Window
    RasterTypes::RasterParameters scaler_out_params;
    scaler_out_params.h_act_start = 0;
    scaler_out_params.h_act_stop = pip_settings.pip_h_right - pip_settings.pip_h_left;
    scaler_out_params.h_tot_start = 0;
    scaler_out_params.h_tot_stop = scaler_out_params.h_act_stop + 10;

    if (raster_out_interlaced) {
      scaler_out_params.v_act_start[0] = 0;
      scaler_out_params.v_act_stop[0] = (pip_settings.pip_v_bottom - pip_settings.pip_v_top)/2 + scaler_out_params.v_act_start[0];
      scaler_out_params.v_act_start[1] = scaler_out_params.v_act_stop[0] + 10;
      scaler_out_params.v_act_stop[1] = (pip_settings.pip_v_bottom - pip_settings.pip_v_top)/2 + scaler_out_params.v_act_start[1];
      scaler_out_params.v_tot_start = 0;
      scaler_out_params.v_tot_stop = scaler_out_params.v_act_stop[1] + 10;
    } else {
      scaler_out_params.v_act_start[0] = 0;
      scaler_out_params.v_act_stop[0] = pip_settings.pip_v_bottom - pip_settings.pip_v_top;
      scaler_out_params.v_tot_start = 0;
      scaler_out_params.v_tot_stop = scaler_out_params.v_act_stop[0] + 10;
    }

    // Calculate Playout Raster Active Window

    // Scaler playout horizontal active region setup
    if (high_rate_pip_mode) {
      //  Divide horizontal values by 2 to support high rate outputs with one scaler
      //  example 38040x2160 becomes 1920x2160
      //  Assumes start positions are even and inclusive  (first pixel included)
      //  Assumes stop positions are inclusive (last pixel included)
      raster_out_params_i.h_act_start = raster_out_params_i.h_act_start/2;        // positional numbers
      if (raster_out_params_i.h_act_stop != 0) {
        raster_out_params_i.h_act_stop  = ((raster_out_params_i.h_act_stop+1)/2)-1; // positional numbers
      } else {
        raster_out_params_i.h_act_stop  = 0; // positional numbers
      }
      raster_out_params_i.h_tot_start = raster_out_params_i.h_tot_start/2;        // positional numbers
      raster_out_params_i.h_tot_stop  = ((raster_out_params_i.h_tot_stop+1)/2)-1; // positional numbers
      raster_out_params_i.h_end_of_line = ((raster_out_params_i.h_end_of_line+1)/2)-1; // positional numbers

      // In high rate mode active region is not aligned horizontal to final Pip window
      raster_out_params_i.h_act_start    = raster_out_params_i.h_act_start; // pip left to 0
      raster_out_params_i.h_act_stop     = (pip_settings.pip_h_right-pip_settings.pip_h_left)+raster_out_params_i.h_act_start; // shift left by pip_left amount
      if (raster_out_params_i.h_act_stop > raster_out_params_i.h_tot_stop) {
        raster_out_params_i.h_act_stop -= raster_out_params_i.h_tot_stop;
        raster_out_params_i.h_act_stop -= 1;
      }

    } else {
      raster_out_params_i.h_act_stop       = pip_settings.pip_h_right+raster_out_params_i.h_act_start;
      if (raster_out_params_i.h_act_stop > raster_out_params_i.h_tot_stop) {
        raster_out_params_i.h_act_stop -= raster_out_params_i.h_tot_stop;
        raster_out_params_i.h_act_stop -= 1;
      }
      raster_out_params_i.h_act_start      = pip_settings.pip_h_left+raster_out_params_i.h_act_start;
    }

    // Scaler playout vertical active region setup
    if (raster_out_interlaced) {
      // Interlaced PiP regions are halfed vertically and offset into eacg field position
      raster_out_params_i.v_act_start[0]  += pip_settings.pip_v_top / 2;
      raster_out_params_i.v_act_stop[0]   = raster_out_params_i.v_act_start[0];
      raster_out_params_i.v_act_stop[0]   += (pip_settings.pip_v_bottom - pip_settings.pip_v_top) / 2;
      if (raster_out_params_i.v_act_stop[0] > raster_out_params_i.v_tot_stop) {
        raster_out_params_i.v_act_stop[0] -= raster_out_params_i.v_tot_stop;
        raster_out_params_i.v_act_stop[0] -= 1;
      }
      raster_out_params_i.v_act_start[1]  += pip_settings.pip_v_top / 2;
      raster_out_params_i.v_act_stop[1]   = raster_out_params_i.v_act_start[1];
      raster_out_params_i.v_act_stop[1]   += (pip_settings.pip_v_bottom - pip_settings.pip_v_top) / 2;
      if (raster_out_params_i.v_act_stop[1] > raster_out_params_i.v_tot_stop) {
        raster_out_params_i.v_act_stop[1] -= raster_out_params_i.v_tot_stop;
        raster_out_params_i.v_act_stop[1] -= 1;
      }
    } else {
      raster_out_params_i.v_act_start[0]   = pip_settings.pip_v_top + raster_out_params_i.v_act_start[0];
      raster_out_params_i.v_act_stop[0]    = (pip_settings.pip_v_bottom - pip_settings.pip_v_top) + raster_out_params_i.v_act_start[0];
      if (raster_out_params_i.v_act_stop[0] > raster_out_params_i.v_tot_stop) {
        raster_out_params_i.v_act_stop[0] -= raster_out_params_i.v_tot_stop;
        raster_out_params_i.v_act_stop[0] -= 1;
      }
    }

    UpDownScaleWrapperType::FrameRate scaler_path_output_frame_rate;
    scaler_path_output_frame_rate.frame_rate_num = out_rate.frame_rate_num;
    scaler_path_output_frame_rate.frame_rate_den = out_rate.frame_rate_den;
    scale_path[path].setOutputPip(&scaler_out_params, &raster_out_params_i, scaler_path_output_frame_rate, (UpDownScaleWrapperType::ColourFormat_type)colour);

    RasterTypes::RasterParameters sc_out_raster_readback;
    HW_API::getScalerPlayoutRaster(path, &sc_out_raster_readback);

    // Create new pip settings based off scaler playout adjusted settings
    //  todo: could get rid of removeBorders function inside scalers, read back from scaler directly and change setups here?

    HW_API::ScalerPipSettings pip_settings_adjusted = pip_settings;
    HW_API::ScalerPipSettings pip_settings_adjusted_f1 = pip_settings;
    RasterParameters raster_out_params_r(raster_out_params);  // orignal settings, used to restore shifted values

    // Use new raster positions which may have shrunk to remove bordering, depending on aspect mode
    if (high_rate_pip_mode) {
      // Undo offset applied earlier for half horizontal raster
      // Restore offset Pip values if high rate shifted
      uint32_t sc_out_raster_readback_h_tot_stop_prot = 0;
      uint32_t pip_h_center = pip_settings.pip_h_left + ((pip_settings.pip_h_right - pip_settings.pip_h_left) / 2);

      // Protection against sc_out_raster_readback.h_act_stop wrap values
      if (sc_out_raster_readback.h_act_stop > sc_out_raster_readback.h_act_start) {
        sc_out_raster_readback_h_tot_stop_prot = sc_out_raster_readback.h_act_stop;
      } else {
        sc_out_raster_readback_h_tot_stop_prot = sc_out_raster_readback.h_tot_stop + 1;
      }

      pip_settings_adjusted.pip_h_left  = pip_h_center - ((sc_out_raster_readback_h_tot_stop_prot - sc_out_raster_readback.h_act_start) / 2);
      if (pip_settings_adjusted.pip_h_left < pip_settings.pip_h_left) {
          pip_settings_adjusted.pip_h_left = pip_settings.pip_h_left;
      }
      pip_settings_adjusted.pip_h_left  += raster_out_params_r.h_act_start;

      pip_settings_adjusted.pip_h_right = pip_settings_adjusted.pip_h_left + (sc_out_raster_readback_h_tot_stop_prot - sc_out_raster_readback.h_act_start) - 1;
      if (pip_settings_adjusted.pip_h_right > uint32_t(raster_out_params_r.h_tot_stop)){
        pip_settings_adjusted.pip_h_right = raster_out_params_r.h_tot_stop;
      }

      // Use vertical settings as is.
      pip_settings_adjusted.pip_v_top = sc_out_raster_readback.v_act_start[0];
      pip_settings_adjusted.pip_v_bottom = sc_out_raster_readback.v_act_stop[0]-1;
      if (pip_settings_adjusted.pip_v_bottom > uint32_t(sc_out_raster_readback.v_tot_stop)) {
        pip_settings_adjusted.pip_v_bottom = sc_out_raster_readback.v_tot_stop;
      }
    } else {

      pip_settings_adjusted.pip_h_left = sc_out_raster_readback.h_act_start;
      if (sc_out_raster_readback.h_act_stop == 0) {
        pip_settings_adjusted.pip_h_right = sc_out_raster_readback.h_tot_stop;
      } else {
        pip_settings_adjusted.pip_h_right = sc_out_raster_readback.h_act_stop-1;
      }
      if (pip_settings_adjusted.pip_h_right > uint32_t(sc_out_raster_readback.h_tot_stop)) {
        pip_settings_adjusted.pip_h_right = sc_out_raster_readback.h_tot_stop;
      }
      pip_settings_adjusted.pip_v_top = sc_out_raster_readback.v_act_start[0];
      pip_settings_adjusted.pip_v_bottom = sc_out_raster_readback.v_act_stop[0]-1;
      if (pip_settings_adjusted.pip_v_bottom > uint32_t(sc_out_raster_readback.v_tot_stop)) {
        pip_settings_adjusted.pip_v_bottom = sc_out_raster_readback.v_tot_stop;
      }

      // Interlaced
      if (sc_out_raster_readback.getVActive(RasterTypes::FIELD1)) {
        pip_settings_adjusted_f1.pip_v_top = sc_out_raster_readback.v_act_start[1];
        pip_settings_adjusted_f1.pip_v_bottom = sc_out_raster_readback.v_act_stop[1]-1;
        if (pip_settings_adjusted_f1.pip_v_bottom > uint32_t(sc_out_raster_readback.v_tot_stop)) {
          pip_settings_adjusted_f1.pip_v_bottom = sc_out_raster_readback.v_tot_stop;
        }
      }
    }

    HW_API::setScalerRasterPhase(path,0,scaler_raster_buffer_phase,0);
    if (high_rate_pip_mode) {
        HW_API::setVidProcScalerReferenceDiv(path, 1);
    } else {
        HW_API::setVidProcScalerReferenceDiv(path, 0);
    }
    HW_API::setVidProcScalerRasterSyncSourcePipMixer(path,0);

    // Video pip mixer pixel width protection on region start
    pip_settings_adjusted.pip_h_right -= pip_settings_adjusted.pip_h_left % PIXELS_PER_CLOCK;
    pip_settings_adjusted.pip_h_left  -= pip_settings_adjusted.pip_h_left % PIXELS_PER_CLOCK;
    setVidProcPipArea(path, pip_settings_adjusted.pip_h_left, pip_settings_adjusted.pip_h_right, pip_settings_adjusted.pip_v_top, pip_settings_adjusted.pip_v_bottom, pip_settings_adjusted_f1.pip_v_top, pip_settings_adjusted_f1.pip_v_bottom);

    // Setup locking
    HW_API::setScalerPipPathLock(path, vidmix_idx, raster_out_params, out_rate, lock_type);
    return 0;
}

int
HW_API::setScalerPipPathLock(uint32_t scaler_path, uint32_t vidmix_idx, RasterTypes::CVTParameters vid_mix_raster_params, HW_API::ScalerFrameRate out_rate, uint32_t lock_type) {
  RasterParameters vidmix_raster(vid_mix_raster_params);
  return setScalerPipPathLock(scaler_path, vidmix_idx, vidmix_raster, out_rate, lock_type);
}

int
HW_API::setScalerPipPathLock(uint32_t scaler_path, uint32_t vidmix_idx, RasterTypes::RasterParameters vid_mix_raster_params, HW_API::ScalerFrameRate out_rate, uint32_t lock_type) {
    // Intended to only setup lock modes and not reprogram scalers

    // return
    //   0 complete
    //  -1 failed

    // lock_type =  0 no lock
    //              1 source lock
    //              2 ptp lock
    //              3 genlock

    // Product specific setup
    int path_arch = getScalerPathArchType(scaler_path);
    bool pip_scaler_path = false;

    // Only one video pip mixer
    if (vidmix_idx != 0) {
      return -1;
    }
    // Only Scaler scaler_path 0 supports locking in Pip configurations
    if (scaler_path != 0) {
      return -1;
    }
    // Invalid Locktype
    if (lock_type >= UpDownScaleWrapperType::NUM_LOCKTYPE) {
      return -1;
    }
    // Check if Pip scaler path
    if (path_arch == 2) {
      pip_scaler_path = true;
    }
    // Check if 4K60 type rates.
    //  PiP paths have a special configuration to support this.
    uint32_t pixel_rate_calc;
    bool high_rate_pip_mode = false;
    pixel_rate_calc =   (vid_mix_raster_params.v_tot_stop - vid_mix_raster_params.v_tot_start)
                      * (vid_mix_raster_params.h_tot_stop - vid_mix_raster_params.h_tot_start);
    pixel_rate_calc /= out_rate.frame_rate_den;
    pixel_rate_calc *= out_rate.frame_rate_num;

    if (      (pixel_rate_calc > pip_scaler_path_pixel_clock_limit)
          &&  (pip_scaler_path)
        ){
      high_rate_pip_mode = true;
    }

    uint32_t scaler_raster_buffer_phase;
    if (high_rate_pip_mode) {
      scaler_raster_buffer_phase = pip_scaler_raster_buffer_phase_pip_path_high_rate;
    } else {
      scaler_raster_buffer_phase = pip_scaler_raster_buffer_phase;
    }

    UpDownScaleWrapperType::FrameRate scaler_path_output_frame_rate;
    scaler_path_output_frame_rate.frame_rate_num = out_rate.frame_rate_num;
    scaler_path_output_frame_rate.frame_rate_den = out_rate.frame_rate_den;

    if (lock_type == UpDownScaleWrapperType::VID_LOCK) { //  Source Tracking Lock
      // Disable other lock types
      HW_API::setScalerPTPLock(scaler_path,0);
      HW_API::setScalerGenlockLock(scaler_path,0);
      // Setup video mixer sync position to start of active
      HW_API::setVidProcVidMixRasterPhase(vidmix_idx, 0, vid_mix_raster_params.h_act_start, vid_mix_raster_params.v_act_start[RasterTypes::FIELD0]-1);
      // Setup video mixer sync source to scaler sc phase output
      HW_API::setVidProcPipMixerRasterSyncSourceScPhase(vidmix_idx,scaler_path);
      // Enable VidLock
      HW_API::setScalerVidLockEnable(scaler_path, 1);
      //  Assign Video Mixer raster
      scale_path[scaler_path].setOutputRates(&vid_mix_raster_params, scaler_path_output_frame_rate);
      //  Change scaler raster synch position for PiP alignment
      //    Scalers align to start of frame of pip mixer raster, adjusted for buffering requirement
      //    Needs to be run after setScalerVidLockEnable and setOutputRates which both setup phase (legacy)
      HW_API::setScalerRasterPhase(scaler_path,0,scaler_raster_buffer_phase,0);

    } else if (lock_type == UpDownScaleWrapperType::PTP_LOCK){
      // Disable other lock types
      HW_API::setScalerVidLockEnable(scaler_path, 0);
      HW_API::setScalerGenlockLock(scaler_path,0);
      // Setup video mixer sync position to start of active
      HW_API::setVidProcVidMixRasterPhase(vidmix_idx, 0, vid_mix_raster_params.h_act_start, vid_mix_raster_params.v_act_start[RasterTypes::FIELD0]-1);
      // Setup video mixer sync source to scaler sc phase output
      HW_API::setVidProcPipMixerRasterSyncSourceScPhase(vidmix_idx,scaler_path);
      //  Assign Video Mixer raster
      scale_path[scaler_path].setOutputRates(&vid_mix_raster_params, scaler_path_output_frame_rate);
      //  PTP Configure
      HW_API::setScalerPTPPhase(scaler_path);
      //  PTP Lock enable
      HW_API::setScalerPTPLock(scaler_path,1);
      //  Change scaler raster synch position for PiP alignment
      //    Scalers align to start of frame of pip mixer raster, adjusted for buffering requirement
      //    Needs to be run after PTP setup (which configures raster to start of active)
      HW_API::setScalerRasterPhase(scaler_path,0,scaler_raster_buffer_phase,0);

    } else if (lock_type == UpDownScaleWrapperType::GEN_LOCK){
      // Disable other lock types
      HW_API::setScalerVidLockEnable(scaler_path, 0);
      HW_API::setScalerPTPLock(scaler_path,0);
      // Setup video mixer sync position to start of active
      HW_API::setVidProcVidMixRasterPhase(vidmix_idx, 0, vid_mix_raster_params.h_act_start, vid_mix_raster_params.v_act_start[RasterTypes::FIELD0]-1);
      // Setup video mixer sync source to scaler sc phase output
      HW_API::setVidProcPipMixerRasterSyncSourceScPhase(vidmix_idx,scaler_path);
      //  Assign Video Mixer raster
      scale_path[scaler_path].setOutputRates(&vid_mix_raster_params, scaler_path_output_frame_rate);
      //  Genlock Configure
      //  Genlock Enable
      HW_API::setScalerGenlockLock(scaler_path,1);
      //  Change scaler raster synch position for PiP alignment
      //    Scalers align to start of frame of pip mixer raster, adjusted for buffering requirement
      HW_API::setScalerRasterPhase(scaler_path,0,scaler_raster_buffer_phase,0);

    } else { // No Locking
      HW_API::setVidProcPipMixerRasterSyncSourceDisable(vidmix_idx);
      HW_API::setScalerVidLockEnable(scaler_path, 0);
      HW_API::setScalerPTPLock(scaler_path,0);
      HW_API::setScalerGenlockLock(scaler_path,0);
    }
    return 0;
}

void
HW_API::getScalerPlayoutRaster(uint32_t path, RasterTypes::RasterParameters * out_raster){
  assert(HW_API::getScalerPathInitDone(path));
  scale_path[path].getPlayoutRaster(out_raster);
  return;
}

uint32_t
HW_API::getScalerVidInpBufferError(uint32_t path){
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].getVidInpBufferError();
}

bool
HW_API::setScalerRasterSyncMaskWidth(uint32_t path, uint32_t mask_width){
  sc_raster[path].init();
  return sc_raster[path].setSyncMaskWidth(mask_width);
}

void
HW_API::disableScalerReadPort(uint32_t path, bool disable) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].disableMemReadPort(disable);
    return;
}

void
HW_API::disableScalerWritePort(uint32_t path, bool disable) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].disableMemWritePort(disable);
    return;
}

void
HW_API::setScalerReadPage(uint32_t path, uint8_t page, bool lock) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setReadPage(page, lock);
    return;
}

void
HW_API::setScalerReadPage(uint32_t path, uint8_t page, bool lock, bool use_b) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setReadPage(page, lock, use_b);
    return;
}

void
HW_API::setLossofInputColour(uint32_t path, HW_API::YCbCr422Colour colour) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setLossofInputColour((UpDownScaleWrapperType::YCbCr422Colour)colour);
    return;
}

void
HW_API::setLossofInputColour(uint32_t path, HW_API::YCbCr444Colour colour) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setLossofInputColour((UpDownScaleWrapperType::YCbCr444Colour)colour);
    return;
}

void
HW_API::setLossofInputColour(uint32_t path, HW_API::RGB444Colour colour) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setLossofInputColour((UpDownScaleWrapperType::RGB444Colour)colour);
    return;
}

void
HW_API::setLossofInputColour(uint32_t path, HW_API::MixerColour * colour) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setLossofInputColour((UpDownScaleWrapperType::MixerColour *)colour);
    return;
}

void
HW_API::setLossofInput(uint32_t path, bool lost) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setLossofInput(lost);
    return;
}

void
HW_API::setRefClkenSource(uint32_t path, uint32_t source) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setRefClkenSource(source);
}

uint32_t
HW_API::getRefClkenSource(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    return scale_path[path].getRefClkenSource();
}

bool
HW_API::getScalerFrameBufferUseB(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    return scale_path[path].getFrameBufferUseB();
}

void
HW_API::setScalerFrameBufferUseB(uint32_t path, bool use_b) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setFrameBufferUseB(!use_b);
    return;
}

bool
HW_API::getScalerFrameBufferHalt(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    return scale_path[path].getFrameBufferHalt();
}

// Video Lock
void
HW_API::setScalerVidLockEnable(uint32_t path, bool enable) {
    // Lock lock type to 2 if enabled, otherwise 0
    // Mode 2 is freq+phase locking
    // Mode 0 is disabled
    uint8_t lock_type = enable?2:0;
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setVidLockLockType(lock_type);
    return;
}

bool
HW_API::getScalerVidLockEnable(uint32_t path) {
  // Lock lock type to 2 if enabled, otherwise 0
  // Mode 2 is frequency +phase locking
  // Mode 0 is disabled
  assert(HW_API::getScalerPathInitDone(path));
  uint8_t lock_type = scale_path[path].getVidLockLockType();
  return lock_type;
}

void
HW_API::getScalerVidLockLockType(uint32_t path, uint8_t* lock_type) {
    assert(HW_API::getScalerPathInitDone(path));
    *lock_type = scale_path[path].getVidLockLockType();
    return;
}

void
HW_API::setScalerVidLockLockType(uint32_t path, uint8_t lock_type) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setVidLockLockType(lock_type);
    return;
}

void
HW_API::scalerVidLockRecenter(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setVidLockRecenter();
    return;
}

bool
HW_API::setScalerRasterPhase(uint32_t path, int const out, int const hphase, int const vphase){
  assert(HW_API::getScalerPathInitDone(path));
  return sc_raster[path].setHVPhase(out,hphase,vphase);
}

void
HW_API::setScalerVidLockResyncPhase(uint32_t path, uint32_t phase){
  scale_path[path].setVidLockResyncPhase(phase);
  return;
}

uint32_t
HW_API::getScalerVidLockResyncPhase(uint32_t path){
  return scale_path[path].getVidLockResyncPhase();
}

void
HW_API::setScalerVidLockRateLimit(uint32_t path, uint32_t limit){
  scale_path[path].setVidLockRateLimit(limit);
  return;
}

uint32_t
HW_API::getScalerVidLockRateLimit(uint32_t path){
  return scale_path[path].getVidLockRateLimit();
}

void
HW_API::getScalerPTPLock(uint32_t path, bool* enable) {
    assert(HW_API::getScalerPathInitDone(path));
    *enable = scale_path[path].getPTPLock();
    return;
}

void
HW_API::setScalerPTPLock(uint32_t path, bool enable) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setPTPLock(enable);
    return;
}

void
HW_API::setScalerPTPPhase(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setPTPPhase();
    return;
}

void
HW_API::setScalerPTPPhaseJam(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setPTPPhaseJam();
    return;
}

void
HW_API::setScalerPTPReferenceLockReset(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setPTPReferenceLockReset();
    return;
}

void
HW_API::getScalerPTPReferenceLockLocked(uint32_t path, bool* locked) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].getPTPReferenceLockLocked(locked);
    return;
}

void
HW_API::getScalerRxRTPOffset(uint32_t path, uint32_t* rxoffset) {
    assert(HW_API::getScalerPathInitDone(path));
    *rxoffset = scale_path[path].getRxRTPOffset();
    return;
}

void
HW_API::setScalerRxRTPOffset(uint32_t path, uint32_t rxoffset) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setRxRTPOffset(rxoffset);
    return;
}

void
HW_API::getScalerGenlockLock(uint32_t path, bool* enable) {
    assert(HW_API::getScalerPathInitDone(path));
    *enable = scale_path[path].getGenlockLock();
    return;
}

void
HW_API::setScalerGenlockLock(uint32_t path, bool enable) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setGenlockLock(enable);
    return;
}

void
HW_API::setScalerGenlockPhaseJam(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setGenlockPhaseJam();
    return;
}

void
HW_API::setScalerGenlockReferenceLockReset(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setGenlockReferenceLockReset();
    return;
}

void
HW_API::getScalerGenlockReferenceLockLocked(uint32_t path, bool* locked) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].getGenlockReferenceLockLocked(locked);
    return;
}

void
HW_API::setScalerOutputSimp(uint32_t path, RasterTypes::CVTParameters out_params) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setScalerOutput(&out_params);
    return;
}

void
HW_API::setScalerOutputSimp(uint32_t path, RasterTypes::AspenParameters out_params) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setScalerOutput(&out_params);
    return;
}

void
HW_API::setScalerOutputSimp(uint32_t path, RasterTypes::RasterParameters out_raster) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].setScalerOutput(&out_raster);
    return;
}

bool
HW_API::getScalerOutputOverflow(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    bool oflow = false;
    oflow = scale_path[path].getOutBufferOverflow();
    scale_path[path].clrOutBufferOverflow();
    return oflow;
}

bool
HW_API::getScalerOutputUnderflow(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    bool uflow = false;
    uflow = scale_path[path].getOutBufferUnderflow();
    scale_path[path].clrOutBufferUnderflow();
    return uflow;
}

uint32_t
HW_API::getScalerOutputBandwidth(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    uint32_t bw = 0;
    bw = scale_path[path].getPlayoutBandwidth();
    return bw;
}

uint32_t
HW_API::getScalerInputRasterRate(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    uint32_t bw = 0;
    bw = scale_path[path].getInputRasterRate();
    return bw;
}

uint32_t
HW_API::getScalerOutputRasterRate(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    uint32_t bw = 0;
    bw = scale_path[path].getOutputRasterRate();
    return bw;
}

uint32_t
HW_API::getScalerOutputHCount(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    uint32_t bw = 0;
    bw = scale_path[path].getPlayoutHSize();
    return bw;
}

uint32_t
HW_API::getScalerOutputVCount(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    uint32_t bw = 0;
    bw = scale_path[path].getPlayoutVSize();
    return bw;
}

uint32_t
HW_API::getScalerOutputTCount(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    uint32_t bw = 0;
    bw = scale_path[path].getPlayoutTSize();
    return bw;
}

void
HW_API::dumpScalerDebugCounters(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].dumpDebugCounters();
    return;
}

void
HW_API::dumpScalerLockStatus(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].dumpLockStatus();
    return;
}

void
HW_API::dumpScalerPTPStatus(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].dumpPTPStatus();
    return;
}

void
HW_API::dumpScalerPTPPlayoutTimingStats(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].dumpPTPPlayoutTimingStats();
    return;
}

void
HW_API::dumpScalerReferenceLockStatus(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].dumpReferenceLockStatus();
    return;
}

void
HW_API::dumpScalerOSDSettings(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].dumpOSDSettings();
    return;
}

void
HW_API::dumpScalerLockPhase(uint32_t path) {
    assert(HW_API::getScalerPathInitDone(path));
    scale_path[path].dumpLockPhase();
    return;
}

uint32_t
HW_API::getScalerLockResyncCount(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].readLockResyncCount();
}

uint32_t
HW_API::getScalerLockPhaseError(uint32_t path) {
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].readLockPhaseError();
}

/* -- Video Processing -- */
ZYNQRasterGenProgVMix vmix_raster;
ZYNQVideoProcessingWrapper vidproc;


void
HW_API::initVidProc() {
  vmix_raster.localInit();
  vidproc.init(&vmix_raster);
  // Video mixer's alpha blending stage is only set to unsigned colour space currently.
  //   (only set to (0, 1) when CbCr use non-offset 2's complement values)
  setBldColorSpace(0, 0);
}

bool
HW_API::getVidProcInitDone() {
  return vidproc.getInitDone();
}

void
HW_API::setVidProcMux(uint32_t vid_mix_idx, uint32_t vid_mix_mux_index) {
  assert(HW_API::getVidProcInitDone());
  vidproc.setVidOutMux(vid_mix_idx,vid_mix_mux_index);
}

uint32_t
HW_API::getVidProcMux(uint32_t vid_mix_idx) {
  assert(HW_API::getVidProcInitDone());
  return vidproc.getVidOutMux(vid_mix_idx);
}

void
HW_API::setVidProcPipArea(uint32_t idx, uint32_t h_start, uint32_t h_stop, uint32_t v_start_field0, uint32_t v_stop_field0, uint32_t v_start_field1, uint32_t v_stop_field1) {
  assert(HW_API::getVidProcInitDone());
  uint32_t h_start_div        = h_start;
  uint32_t h_stop_div         = h_stop ;
  vidproc.setPipArea(idx, h_start_div, h_stop_div, v_start_field0, v_stop_field0, v_start_field1, v_stop_field1);
  return;
}

void
HW_API::getVidProcPipArea(uint32_t idx, uint32_t* h_start, uint32_t* h_stop, uint32_t* v_start_field0, uint32_t* v_stop_field0, uint32_t* v_start_field1, uint32_t* v_stop_field1) {
  assert(HW_API::getVidProcInitDone());
  vidproc.getPipArea(idx, h_start, h_stop, v_start_field0, v_stop_field0, v_start_field1, v_stop_field1);
  return;
}

void
HW_API::setPipEnable(uint32_t vid_mix_idx, uint32_t inp_idx, bool enable) {
  assert(HW_API::getVidProcInitDone());
  vidproc.setPipEnable(vid_mix_idx, inp_idx, enable);
  return;
}

uint32_t
HW_API::getPipEnable(uint32_t vid_mix_idx, uint32_t inp_idx) {
  assert(HW_API::getVidProcInitDone());
  return vidproc.getPipEnable(vid_mix_idx, inp_idx);
}

void
HW_API::setPipEnableMask(uint32_t vid_mix_idx, uint32_t mask) {
  assert(HW_API::getVidProcInitDone());
  vidproc.setPipEnableMask(vid_mix_idx, mask);
  return;
}

void
HW_API::setBldColorSpace(uint32_t vid_mix_idx, uint32_t fmt) {
  assert(HW_API::getVidProcInitDone());
  vidproc.setBldColorSpace(vid_mix_idx, fmt);
  return;
}

uint32_t
HW_API::getBldColorSpace(uint32_t vid_mix_idx) {
  assert(HW_API::getVidProcInitDone());
  return vidproc.getBldColorSpace(vid_mix_idx);
}

void
HW_API::setMixOutSelect(uint32_t vid_mix_idx, uint32_t select) {
  assert(HW_API::getVidProcInitDone());
  vidproc.setMixOutSelect(vid_mix_idx, select);
  return;
}

uint32_t
HW_API::getMixOutSelect(uint32_t vid_mix_idx) {
  assert(HW_API::getVidProcInitDone());
  return vidproc.getMixOutSelect(vid_mix_idx);
}

bool
HW_API::setVidProcRaster(RasterTypes::CVTParameters const &raster_params) {
  assert(HW_API::getVidProcInitDone());
  return vidproc.setVidMixRaster(raster_params);
}

bool
HW_API::setVidProcRaster(RasterTypes::SDIParameters const &raster_params) {
  assert(HW_API::getVidProcInitDone());
  return vidproc.setVidMixRaster(raster_params);
}

bool
HW_API::setVidProcRaster(RasterTypes::AspenParameters const &raster_params) {
  assert(HW_API::getVidProcInitDone());
  return vidproc.setVidMixRaster(raster_params);
}

bool
HW_API::setVidProcRaster(RasterTypes::RasterParameters const &raster_params) {
  assert(HW_API::getVidProcInitDone());
  return vidproc.setVidMixRaster(raster_params);
}

bool
HW_API::setVidProcRasterIdx(uint32_t vid_mix_idx ,uint32_t raster_idx) {
  assert(HW_API::getVidProcInitDone());
  RasterTypes::CVTParameters in_hdmi_params;
  printf("\n");
  printf("Setting Video Processing Pip Mixer %u Output Raster to : ",vid_mix_idx);
  switch (raster_idx) {
      case HW_API::BW_1920_1080P24:
          printf("1920x1080p24\n");
          in_hdmi_params.appl = 1920;
          in_hdmi_params.tppl = 2750;
          in_hdmi_params.hs_width = 44;
          in_hdmi_params.hs_front_porch = 638;
          in_hdmi_params.hs_back_porch = 148;
          in_hdmi_params.alpf[0] = 1080;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1125;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5;
          in_hdmi_params.vs_front_porch = 4;
          in_hdmi_params.vs_back_porch = 36;
          break;
      case HW_API::BW_1280_720P60:
          printf("1280x720p60\n");
          in_hdmi_params.appl = 1280;
          in_hdmi_params.tppl = 1650;
          in_hdmi_params.hs_width = 40;
          in_hdmi_params.hs_front_porch = 110;
          in_hdmi_params.hs_back_porch = 220;
          in_hdmi_params.alpf[0] = 720;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 750;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5;
          in_hdmi_params.vs_front_porch = 5;
          in_hdmi_params.vs_back_porch = 20;
          break;
      case HW_API::BW_1920_1200P60:
          printf("1920x1200p60\n");
          in_hdmi_params.appl = 1920;
          in_hdmi_params.tppl = 2080;
          in_hdmi_params.hs_width = 32;
          in_hdmi_params.hs_front_porch = 48;
          in_hdmi_params.hs_back_porch = 80;
          in_hdmi_params.alpf[0] = 1200;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1235;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 6;
          in_hdmi_params.vs_front_porch = 3;
          in_hdmi_params.vs_back_porch = 26;
          break;
      case HW_API::BW_640_480P60:
          printf("640x480p60\n");
          in_hdmi_params.appl = 640;
          in_hdmi_params.tppl = 800;
          in_hdmi_params.hs_width = 96;
          in_hdmi_params.hs_front_porch = 24;
          in_hdmi_params.hs_back_porch = 40;
          in_hdmi_params.alpf[0] = 480;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 525;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 2;
          in_hdmi_params.vs_front_porch = 18;
          in_hdmi_params.vs_back_porch = 25;
          break;
      case HW_API::BW_1920_1080I60:
          printf("1080i60");
          in_hdmi_params.appl = 1920;
          in_hdmi_params.tppl = 2200;
          in_hdmi_params.hs_width = 44;
          in_hdmi_params.hs_front_porch = 88;
          in_hdmi_params.hs_back_porch = 148;
          in_hdmi_params.alpf[0] = 540;
          in_hdmi_params.alpf[1] = 540;
          in_hdmi_params.tlpf[0] = 562;
          in_hdmi_params.tlpf[1] = 563;
          in_hdmi_params.vs_width = 5;
          in_hdmi_params.vs_front_porch = 2;
          in_hdmi_params.vs_back_porch = 15;
          break;
      case HW_API::BW_1920_1080P30:
          printf("1080p30");
          in_hdmi_params.appl = 1920;
          in_hdmi_params.tppl = 2200;
          in_hdmi_params.hs_width = 44;
          in_hdmi_params.hs_front_porch = 88;
          in_hdmi_params.hs_back_porch = 148;
          in_hdmi_params.alpf[0] = 1080;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1125;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5;
          in_hdmi_params.vs_front_porch = 4;
          in_hdmi_params.vs_back_porch = 36;
          break;
      case HW_API::BW_3840_2160P30:
          printf("2160p30");
          in_hdmi_params.appl = 1920*2;
          in_hdmi_params.tppl = 2200*2;
          in_hdmi_params.hs_width = 44*2;
          in_hdmi_params.hs_front_porch = 88*2;
          in_hdmi_params.hs_back_porch = 148*2;
          in_hdmi_params.alpf[0] = 1080*2;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1125*2;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5*2;
          in_hdmi_params.vs_front_porch = 4*2;
          in_hdmi_params.vs_back_porch = 36*2;
          break;
      case HW_API::BW_3840_2160P60:
          printf("2160p60");
          in_hdmi_params.appl = 1920*2;
          in_hdmi_params.tppl = 2200*2;
          in_hdmi_params.hs_width = 44*2;
          in_hdmi_params.hs_front_porch = 88*2;
          in_hdmi_params.hs_back_porch = 148*2;
          in_hdmi_params.alpf[0] = 1080*2;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1125*2;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5*2;
          in_hdmi_params.vs_front_porch = 4*2;
          in_hdmi_params.vs_back_porch = 36*2;
          break;
      case HW_API::BW_3840_2160P24:
          printf("2160p24");
          in_hdmi_params.appl = 1920*2;
          in_hdmi_params.tppl = 2750*2;
          in_hdmi_params.hs_width = 44*2;
          in_hdmi_params.hs_front_porch = 638*2;
          in_hdmi_params.hs_back_porch = 148*2;
          in_hdmi_params.alpf[0] = 1080*2;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1125*2;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5*2;
          in_hdmi_params.vs_front_porch = 4*2;
          in_hdmi_params.vs_back_porch = 36*2;
          break;
      case HW_API::BW_3840_2160P23_98:
          printf("2160p23.98");
          in_hdmi_params.appl = 1920*2;
          in_hdmi_params.tppl = 2750*2;
          in_hdmi_params.hs_width = 44*2;
          in_hdmi_params.hs_front_porch = 638*2;
          in_hdmi_params.hs_back_porch = 148*2;
          in_hdmi_params.alpf[0] = 1080*2;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1125*2;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5*2;
          in_hdmi_params.vs_front_porch = 4*2;
          in_hdmi_params.vs_back_porch = 36*2;
          break;
      case HW_API::BW_3840_2160P59_94:
          printf("2160p59.94");
          in_hdmi_params.appl = 1920*2;
          in_hdmi_params.tppl = 2200*2;
          in_hdmi_params.hs_width = 44*2;
          in_hdmi_params.hs_front_porch = 88*2;
          in_hdmi_params.hs_back_porch = 148*2;
          in_hdmi_params.alpf[0] = 1080*2;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1125*2;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5*2;
          in_hdmi_params.vs_front_porch = 4*2;
          in_hdmi_params.vs_back_porch = 36*2;
          break;
      case HW_API::BW_3840_2160P29_98:
          printf("2160p29.98");
          in_hdmi_params.appl = 1920*2;
          in_hdmi_params.tppl = 2200*2;
          in_hdmi_params.hs_width = 44*2;
          in_hdmi_params.hs_front_porch = 88*2;
          in_hdmi_params.hs_back_porch = 148*2;
          in_hdmi_params.alpf[0] = 1080*2;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1125*2;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5*2;
          in_hdmi_params.vs_front_porch = 4*2;
          in_hdmi_params.vs_back_porch = 36*2;
          break;
      case HW_API::BW_1920_1080P59_94:
          printf("1080p59.94");
          in_hdmi_params.appl = 1920;
          in_hdmi_params.tppl = 2200;
          in_hdmi_params.hs_width = 44;
          in_hdmi_params.hs_front_porch = 88;
          in_hdmi_params.hs_back_porch = 148;
          in_hdmi_params.alpf[0] = 1080;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1125;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5;
          in_hdmi_params.vs_front_porch = 4;
          in_hdmi_params.vs_back_porch = 36;
          break;
      case HW_API::BW_1920_1080P60:
      default:
          printf("1080p60");
          in_hdmi_params.appl = 1920;
          in_hdmi_params.tppl = 2200;
          in_hdmi_params.hs_width = 44;
          in_hdmi_params.hs_front_porch = 88;
          in_hdmi_params.hs_back_porch = 148;
          in_hdmi_params.alpf[0] = 1080;
          in_hdmi_params.alpf[1] = 0;
          in_hdmi_params.tlpf[0] = 1125;
          in_hdmi_params.tlpf[1] = 0;
          in_hdmi_params.vs_width = 5;
          in_hdmi_params.vs_front_porch = 4;
          in_hdmi_params.vs_back_porch = 36;
          break;
    }

    bool raster_success;
    raster_success = HW_API::setVidProcRaster(in_hdmi_params);
    if (raster_success) {
      printf(" ... verified\n");
    } else {
      printf(" ... failed verification\n");
    }

    RasterTypes::RasterParameters vidmix_raster;
    vidmix_raster = (RasterParameters)in_hdmi_params;
    HW_API::setVidProcVidMixRasterPhase(vid_mix_idx, 0, (uint32_t)vidmix_raster.h_act_start, (uint32_t)vidmix_raster.v_act_start);
    HW_API::setVidProcVidMixRasterSyncMaskWidth(vid_mix_idx, 4);

    return raster_success;
}

bool
HW_API::setVidProcVidMixRasterPhase(uint32_t vid_mix_idx, uint32_t raster_num, uint32_t hphase, uint32_t vphase){
  assert(HW_API::getVidProcInitDone());
  return vidproc.setVidMixRasterPhase(vid_mix_idx, raster_num, hphase, vphase);
}

bool
HW_API::setVidProcVidMixRasterSyncMaskWidth(uint32_t vid_mix_idx, uint32_t mask_width){
  assert(HW_API::getVidProcInitDone());
  return vidproc.setVidMixRasterSyncMaskWidth(vid_mix_idx, mask_width);
}

void
HW_API::setVidProcScalerReferenceDiv(uint32_t sc_idx, uint32_t div){
  assert(HW_API::getVidProcInitDone());
  vidproc.setScalerReferenceDiv(sc_idx, div);
  return;
}

uint32_t
HW_API::getVidProcScalerReferenceDiv(uint32_t sc_idx){
  assert(HW_API::getVidProcInitDone());
  return vidproc.getScalerReferenceDiv(sc_idx);
}

void
HW_API::setVidProcPipBorderColour(uint32_t idx, uint32_t colour_g_y, uint32_t colour_b_cb, uint32_t colour_r_cr){
  assert(HW_API::getVidProcInitDone());
  vidproc.setPipBorderColour( idx, colour_g_y, colour_b_cb, colour_r_cr);
  return;
}

void
HW_API::getVidProcPipBorderColour(uint32_t idx, uint32_t* colour_g_y, uint32_t* colour_b_cb, uint32_t* colour_r_cr){
  assert(HW_API::getVidProcInitDone());
  vidproc.getPipBorderColour(idx, colour_g_y, colour_b_cb, colour_r_cr);
  return;
}

uint32_t
HW_API::getVidProcScalerRasterSyncSource(uint32_t sc_idx){
  assert(HW_API::getVidProcInitDone());
  return vidproc.getScalerRasterSyncSource(sc_idx);
}

void
HW_API::setVidProcScalerRasterSyncSource(uint32_t sc_idx, uint32_t sc_source_idx){
  assert(HW_API::getVidProcInitDone());
  vidproc.setScalerRasterSyncSource(sc_idx, sc_source_idx);
  return;
}
void
HW_API::setVidProcScalerRasterSyncSourceScRaster(uint32_t sc_idx, uint32_t sc_source_idx){
  assert(HW_API::getVidProcInitDone());
  vidproc.setScalerRasterSyncSourceScRaster(sc_idx, sc_source_idx);
  return;
}
void
HW_API::setVidProcScalerRasterSyncSourcePipMixer(uint32_t sc_idx, uint32_t vid_mix_idx){
  assert(HW_API::getVidProcInitDone());
  vidproc.setScalerRasterSyncSourcePipMixer(sc_idx, vid_mix_idx);
  return;
}
void
HW_API::setVidProcScalerRasterSyncSourceScPhase(uint32_t sc_idx, uint32_t sc_source_idx){
  assert(HW_API::getVidProcInitDone());
  vidproc.setScalerRasterSyncSourceScPhase(sc_idx, sc_source_idx);
  return;
}
void
HW_API::setVidProcScalerRasterSyncSourceDisable(uint32_t sc_idx){
  assert(HW_API::getVidProcInitDone());
  vidproc.setScalerRasterSyncSourceDisable(sc_idx);
  return;
}
void
HW_API::setVidProcPipMixerRasterSyncSourceScRaster(uint32_t pip_idx, uint32_t sc_source_idx){
  assert(HW_API::getVidProcInitDone());
  vidproc.setPipMixerSyncSourceScRaster(pip_idx, sc_source_idx);
  return;
}
void
HW_API::setVidProcPipMixerRasterSyncSourcePipMixer(uint32_t pip_idx, uint32_t vid_mix_idx){
  assert(HW_API::getVidProcInitDone());
  vidproc.setPipMixerSyncSourcePipMixer(pip_idx, vid_mix_idx);
  return;
}
void
HW_API::setVidProcPipMixerRasterSyncSourceScPhase(uint32_t pip_idx, uint32_t sc_source_idx){
  assert(HW_API::getVidProcInitDone());
  vidproc.setPipMixerSyncSourceScPhase(pip_idx, sc_source_idx);
  return;
}
void
HW_API::setVidProcPipMixerRasterSyncSourceDisable(uint32_t pip_idx){
  assert(HW_API::getVidProcInitDone());
  vidproc.setPipMixerSyncSourceDisable(pip_idx);
  return;
}

/* -- HDMI -- */

ZYNQHDMI hdmi[] = {ZYNQHDMI(HDMI0_BASE_ADDR),
                   ZYNQHDMI(HDMI1_BASE_ADDR)};

void
HW_API::initHdmi(uint32_t chan) {
    assert(chan < HW_API::N_HDMI_CHANS);
    if (HW_API::getFPGACapability("INC_HDMI") <= 0)
    {
      printf("INC_HDMI feature is required but not enabled!\n");
      return;
    }
    if ((chan == 0) && (HW_API::getFPGACapability("INC_HDMI_NORTH_RX") <= 0) && (HW_API::getFPGACapability("INC_HDMI_NORTH_TX") <= 0))
    {
      printf("INC_HDMI_NORTH_RX or INC_HDMI_NORTH_TX feature are required when trying to access channel 0, but are not enabled!\n");
      return;
    }
    if ((chan == 1) && (HW_API::getFPGACapability("INC_HDMI_SOUTH_RX") <= 0) && (HW_API::getFPGACapability("INC_HDMI_SOUTH_TX") <= 0))
    {
      printf("INC_HDMI_SOUTH_RX or INC_HDMI_SOUTH_TX feature are required when trying to access channel 1, but are not enabled!\n");
      return;
    }
    hdmi[chan].init();
    return;
}

bool
HW_API::getHdmiInitDone(uint32_t chan) {
    assert(chan < HW_API::N_HDMI_CHANS);
    return hdmi[chan].getInitDone();
}

int
HW_API::getHdmiStateRunning(uint32_t chan, bool* running) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getStateRunning(running);
}

int
HW_API::getHdmiMainLoopHeartbeat(uint32_t chan, uint32_t* mainLoopHeartbeat) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getMainLoopHeartbeat(mainLoopHeartbeat);
}

uint8_t
HW_API::debugHdmiRead(uint32_t chan, uint32_t addr) {
  assert(HW_API::getHdmiInitDone(chan));
  return hdmi[chan].read(addr);
}

void
HW_API::debugHdmiWrite(uint32_t chan, uint32_t addr, uint8_t data) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].write(addr, data);
}

void
HW_API::debugHdmiConfig(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printConfig();
}

void
HW_API::debugHdmiConfigMemory(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printConfigMemory();
}

void
HW_API::debugHdmiConfigStatus(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printConfigStatus();
}

void
HW_API::debugHdmiConfigRx(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printConfigRx();
}

void
HW_API::debugHdmiConfigRxStatus(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printConfigRxStatus();
}

void
HW_API::debugHdmiConfigTx(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printConfigTx();
}

void
HW_API::debugHdmiConfigTxStatus(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printConfigTxStatus();
}

void
HW_API::debugHdmiCheckConfig(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].checkConfig();
}

void
HW_API::debugHdmiWriteConfig(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].writeConfig();
}

void
HW_API::debugHdmiSizeConfig(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].sizeConfig();
}

void
HW_API::debugHdmiClkDetFreq(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printClkDetFreq();
}

void
HW_API::debugHdmiTxClkDetFreq(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printClkDetFreqTx();
}

void
HW_API::debugHdmiRxHdcp14(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printHdcp14DebugRx();
}

void
HW_API::debugHdmiTxHdcp14(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printHdcp14DebugTx();
}

void
HW_API::debugHdmiRxHdcp22(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printHdcp22DebugRx();
}

void
HW_API::debugHdmiTxHdcp22(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printHdcp22DebugTx();
}

void
HW_API::debugHdmiRxLinkCounters(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printRxLinkCounters();
}

void
HW_API::debugHdmiRxLinkStatus(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].printRxLinkStatusDebug();
}

void
HW_API::setHdmiLoopbackMode(uint32_t chan, uint8_t mode) {
  assert(HW_API::getHdmiInitDone(chan));
  hdmi[chan].loopbackMode(mode);
}

bool
HW_API::getHdmiRxIsConnected(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  return (hdmi[chan].getRxIsConnected() == HDMI_Xil_Type::RET_SUCCESS);
}

bool
HW_API::getHdmiTxIsConnected(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  return (hdmi[chan].getTxIsConnected() == HDMI_Xil_Type::RET_SUCCESS);
}

bool
HW_API::getHdmiRxStreamIsUp(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  return (hdmi[chan].getRxStreamIsUp() == HDMI_Xil_Type::RET_SUCCESS);
}

bool
HW_API::getHdmiTxStreamIsUp(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  return (hdmi[chan].getTxStreamIsUp() == HDMI_Xil_Type::RET_SUCCESS);
}

int
HW_API::getHdmiRxHotplugDetect(uint32_t chan, bool* enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxHotplugDetect(enabled);
}

int
HW_API::setHdmiRxHotplugDetect(uint32_t chan, bool enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setRxHotplugDetect(enabled);
}

int
HW_API::getHdmiTxEDID(uint32_t chan, uint8_t* edid, uint32_t* size, uint8_t* valid, uint8_t* edid_idx) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxEDID(edid, size, valid, edid_idx);
}

int
HW_API::setHdmiRxEDID(uint32_t chan, uint8_t* edid, uint32_t size) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setRxEDID(edid, size);
}

int
HW_API::getHdmiTxHdmi20Capable(uint32_t chan, bool* capable) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxHdmi20Capable(capable);
}

int
HW_API::getHdmiTxHdcp22Capable(uint32_t chan, bool* capable) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxHdcp22Capable(capable);
}

int
HW_API::getHdmiTxTmdsClockRatio(uint32_t chan, bool* ratio) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxTmdsClockRatio(ratio);
}

int
HW_API::getHdmiTxSinkClockRatio(uint32_t chan, bool* ratio) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxSinkClockRatio(ratio);
}

int
HW_API::getHdmiTxTmdsClockRatioReprogrammed(uint32_t chan, uint8_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxTmdsClockRatioReprogrammed(count);
}

int
HW_API::setHdmiTxSetTmdsClockRatio(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxSetTmdsClockRatio();
}

int
HW_API::getHdmiRxAudioChannels(uint32_t chan, uint8_t* chans) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxAudioChannels(chans);
}

int
HW_API::getHdmiRxAudioSamplingFrequency(uint32_t chan, uint32_t* sf) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxAudioSamplingFrequency(sf);
}

int
HW_API::getHdmiRxAudioCompressed(uint32_t chan, uint8_t* compressed) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxAudioCompressed(compressed);
}

int
HW_API::getHdmiRxAudioDataType(uint32_t chan, char* aud_type) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxAudioDataType(aud_type);
}

int
HW_API::getHdmiRxAudioHBR(uint32_t chan, uint8_t* hbr) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxAudioHBR(hbr);
}

int
HW_API::getHdmiTxAudioSamplingFrequency(uint32_t chan, uint32_t* sf) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxAudioSamplingFrequency(sf);
}

int
HW_API::getHdmiTxAudioCompressed(uint32_t chan, bool* compressed) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxAudioCompressed(compressed);
}

int
HW_API::getHdmiTxAudioSRC(uint32_t chan, bool* useSRC) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxAudioSRC(useSRC);
}

int
HW_API::getHdmiTxAudioDrop(uint32_t chan, bool* drop) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxAudioDrop(drop);
}

int
HW_API::getHdmiTxAudioHBR(uint32_t chan, uint8_t* hbr) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxAudioHBR(hbr);
}

int
HW_API::setHdmiTxAudioChannels(uint32_t chan, uint8_t chans) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxAudioChannels(chans);
}

int
HW_API::setHdmiTxAudioMute(uint32_t chan, bool mute) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxAudioMute(mute);
}

int
HW_API::setHdmiTxAudioReset(uint32_t chan, bool reset) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxAudioReset(reset);
}

int
HW_API::setHdmiTxAudioCbits(uint32_t chan, bool restamp, bool professional) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxAudioCbits(restamp, professional);
}

int
HW_API::setHdmiTxAudioForceSRC(uint32_t chan, bool forcesrc) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxAudioForceSRC(forcesrc);
}

int
HW_API::getHdmiRxAuxPacket(uint32_t chan, uint8_t* ptr, uint32_t* size) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxAuxPacket(ptr, size);
}

int
HW_API::setHdmiTxAuxPacket(uint32_t chan, uint8_t* ptr, uint32_t size) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxAuxPacket(ptr, size);
}

int
HW_API::getHdmiHDCPKeysPresent(uint32_t chan, bool* present) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getHDCPKeysPresent(present);
}

int
HW_API::getHdmiHDCPKeysLoaded(uint32_t chan, HDMI_Xil_Type::Key_type* status) {
  assert(HW_API::getHdmiInitDone(chan));
  return hdmi[chan].getHDCPKeysLoaded(status);
}

int
HW_API::getHdmiHDCPEEPROMData(uint32_t chan, uint8_t* hdcp_eeprom_data) {
  assert(HW_API::getHdmiInitDone(chan));
  return hdmi[chan].getHDCPEEPROMData(hdcp_eeprom_data);
}

int
HW_API::setHdmiRxHDCPProtocol(uint32_t chan, HDMI_Xil_Type::HDCP_type hdcpProtocol) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setRxHDCPProtocol(hdcpProtocol);
}

int
HW_API::getHdmiRxHDCPProtocol(uint32_t chan, HDMI_Xil_Type::HDCP_type* hdcpProtocol) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxHDCPProtocol(hdcpProtocol);
}

int
HW_API::getHdmiRxHDCPIsAuthenticated(uint32_t chan, bool* isAuthenticated) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxHDCPIsAuthenticated(isAuthenticated);
}

int
HW_API::getHdmiRxHDCPIsEncrypted(uint32_t chan, bool* isEncrypted) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxHDCPIsEncrypted(isEncrypted);
}

int
HW_API::getHdmiRxTicoRequired(uint32_t chan, bool* ticoRequired, HDMI_Xil_Type::ColourFormat_type colourFormat, HDMI_Xil_Type::ColourDepth_type colourDepth, bool fractional){
  assert(HW_API::getHdmiInitDone(chan));
  uint64_t aspen_tx_bandwidth_limit = (uint64_t)CORE_CLK_FREQ_HZ * (uint64_t)ASPEN_TX_BUS_WIDTH;

  uint16_t horizontal_total_pixels;
  uint16_t vertical_field0_total_lines;
  uint16_t vertical_field1_total_lines;
  if (hdmi[chan].getRxVideoTimingTotals(&horizontal_total_pixels, &vertical_field0_total_lines, &vertical_field1_total_lines) != HDMI_Xil_Type::RET_SUCCESS)
  {
    return -1;
  }

  uint16_t frame_rate;
  if (hdmi[chan].getRxVideoFrameRate(&frame_rate) != HDMI_Xil_Type::RET_SUCCESS)
  {
    return -2;
  }

  uint8_t pixel_size;
  if (hdmi[chan].getPixelSize(&pixel_size, colourFormat, colourDepth) != HDMI_Xil_Type::RET_SUCCESS)
  {
    return -3;
  }

  uint64_t pixel_clock;
  if (hdmi[chan].getPixelClock(&pixel_clock, frame_rate, horizontal_total_pixels, vertical_field0_total_lines, vertical_field1_total_lines, fractional) != HDMI_Xil_Type::RET_SUCCESS)
  {
    return -4;
  }

  uint64_t bandwidth_required = pixel_size * pixel_clock;
  if (bandwidth_required == 0)
  {
    return -5;
  }

  if (bandwidth_required > aspen_tx_bandwidth_limit)
  {
    *ticoRequired = true;
  }
  else
  {
    *ticoRequired = false;
  }

  return 0;
}

int
HW_API::getHdmiRxTMDS181BadState(uint32_t chan, bool* badState){
  assert(HW_API::getHdmiInitDone(chan));
  bool connected = HW_API::getHdmiRxIsConnected(chan);
  bool streamisup = HW_API::getHdmiRxStreamIsUp(chan);
  bool ratio;
  hdmi[chan].getRxTMDSClockRatio(&ratio);
  uint32_t clock;
  hdmi[chan].getRxReferenceClock(&clock);

  // If the cable is connected, but no stream is up, and the core detects a source set the TMDS Ratio bit
  // and the clock is Non-0, and the clock is less than 340 MHz / 4, then the TMDS181 is in a known bad state.
  if (connected && !streamisup && ratio && (clock > 0) && (clock < (340000000/4)))
  {
    *badState = true;
  }
  else
  {
    *badState = false;
  }

  return 0;
}

//int
//HW_API::setHdmiTxHDCPProtocol(uint32_t chan, HDMI_Xil_Type::HDCP_type hdcpProtocol) {
//  assert(HW_API::getHdmiInitDone(chan));
//  return (int)hdmi[chan].setTxHDCPProtocol(hdcpProtocol);
//}

int
HW_API::getHdmiTxHDCPProtocol(uint32_t chan, HDMI_Xil_Type::HDCP_type* hdcpProtocol) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxHDCPProtocol(hdcpProtocol);
}

int
HW_API::getHdmiTxHDCPIsAuthenticated(uint32_t chan, bool* isAuthenticated) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxHDCPIsAuthenticated(isAuthenticated);
}

int
HW_API::getHdmiTxHDCPIsEncrypted(uint32_t chan, bool* isEncrypted) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxHDCPIsEncrypted(isEncrypted);
}

int
HW_API::setHdmiTxHDCPEnableEncryption(uint32_t chan, bool enableEncryption) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxHDCPEnableEncryption(enableEncryption);
}

int
HW_API::getHdmiTxHDCPAuthenticationRequest(uint32_t chan, bool* reqAuthentication) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxHDCPAuthenticationRequest(reqAuthentication);
}

int
HW_API::setHdmiTxHDCPAuthenticationRequest(uint32_t chan, bool reqAuthentication) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxHDCPAuthenticationRequest(reqAuthentication);
}

int
HW_API::getHdmiTxHDCPWaitingPeriod(uint32_t chan, uint32_t* waitingPeriod) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxHDCPWaitingPeriod(waitingPeriod);
}

int
HW_API::setHdmiTxHDCPWaitingPeriod(uint32_t chan, uint32_t waitingPeriod) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxHDCPWaitingPeriod(waitingPeriod);
}

int
HW_API::setHdmiTxHDCPMask(uint32_t chan, HDMI_Xil_Type::HDCPMask_type hdcpMask) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxHDCPMask(hdcpMask);
}

int
HW_API::getHdmiTxHDCPMask(uint32_t chan, HDMI_Xil_Type::HDCPMask_type* hdcpMask) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxHDCPMask(hdcpMask);
}

int
HW_API::getHdmiTxHDCPWaitCount(uint32_t chan, uint32_t* waitCount) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxHDCPWaitCount(waitCount);
}

int
HW_API::getHdmiTxHDCPBlank(uint32_t chan, bool* blank) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxHDCPBlank(blank);
}

int
HW_API::getHdmiRxVideoConfig(uint32_t chan, HDMI_Xil_Type::VideoStream_type* videoStream, HDMI_Xil_Type::VideoConfig_type* videoConfig) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxVideoConfig(videoStream, videoConfig);
}

int
HW_API::setHdmiTxVideoConfig(uint32_t chan, HDMI_Xil_Type::VideoStream_type* videoStream, uint8_t videoIDCode, bool dviMode, uint8_t lte_340mcsc_scramble, uint8_t max_tmds_character_rate, uint8_t max_tmds_clock, bool sendBasicInfoFrames, bool fractional) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxVideoConfig(videoStream, videoIDCode, dviMode, lte_340mcsc_scramble, max_tmds_character_rate, max_tmds_clock, sendBasicInfoFrames, fractional);
}

int
HW_API::getHdmiTxVideoConfig(uint32_t chan, HDMI_Xil_Type::VideoStream_type* videoStream, bool* dviMode) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxVideoConfig(videoStream, dviMode);
}

int
HW_API::getHdmiTxVideoConfigValid(uint32_t chan, HDMI_Xil_Type::VideoStream_type* videoStream, uint8_t videoIDCode, bool dviMode, uint8_t lte_340mcsc_scramble, uint8_t max_tmds_character_rate, uint8_t max_tmds_clock, bool fractional) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxVideoConfigValid(videoStream, videoIDCode, dviMode, lte_340mcsc_scramble, max_tmds_character_rate, max_tmds_clock, fractional);
}

int
HW_API::setHdmiTxVideoLoopback(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxVideoLoopback();
}

int
HW_API::getHdmiTxTmdsClockOff(uint32_t chan, bool* off) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxTmdsClockOff(off);
}

int
HW_API::getHdmiTxOff(uint32_t chan, bool* off) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxOff(off);
}

int
HW_API::setHdmiTxOff(uint32_t chan, bool off) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxOff(off);
}

int
HW_API::setHdmiRxOutputEnable(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setRxOutputEnable();
}

int
HW_API::getHdmiRxVideoFractional(uint32_t chan, bool* fractional) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxVideoFractional(fractional);
}

int
HW_API::getHdmiTxMetadataFlushedCount(uint32_t chan, uint16_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataFlushedCount(count);
}

int
HW_API::getHdmiTxMetadataDRMCount(uint32_t chan, uint16_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataDRMCount(count);
}

int
HW_API::getHdmiTxMetadataHDR10PlusCount(uint32_t chan, uint16_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataHDR10PlusCount(count);
}

int
HW_API::getHdmiTxMetadataDolbyCountMasked(uint32_t chan, uint16_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataDolbyCountMasked(count);
}

int
HW_API::getHdmiTxMetadataDolbyCountSent(uint32_t chan, uint16_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataDolbyCountSent(count);
}

int
HW_API::getHdmiTxMetadataH14bDolbyCountMasked(uint32_t chan, uint16_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataH14bDolbyCountMasked(count);
}

int
HW_API::getHdmiTxMetadataH14bDolbyCountSent(uint32_t chan, uint16_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataH14bDolbyCountSent(count);
}

int
HW_API::getHdmiTxMetadataGenericCount(uint32_t chan, uint16_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataGenericCount(count);
}

int
HW_API::getHdmiTxMetadataDRM(uint32_t chan, HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type* drmInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataDRM(drmInfoFrame);
}

int
HW_API::getHdmiTxMetadataHDR10Plus(uint32_t chan, HDMI_Xil_Type::HDR10PlusInfoFrame_type* hdr10pInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataHDR10Plus(hdr10pInfoFrame);
}

int
HW_API::getHdmiTxMetadataDolby(uint32_t chan, HDMI_Xil_Type::DolbyInfoFrame_type* dolbyInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataDolby(dolbyInfoFrame);
}

int
HW_API::getHdmiTxMetadataGenericBuffer(uint32_t chan, HDMI_Xil_Type::Aux_type* genericAuxBuffer) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataGenericBuffer(genericAuxBuffer);
}

int
HW_API::getHdmiTxMetadataSent_localh14b_vsif(uint32_t chan, bool* sent) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataSent_localh14b_vsif(sent);
}

int
HW_API::getHdmiTxMetadataSent_remoteh14b_vsif(uint32_t chan, bool* sent) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataSent_remoteh14b_vsif(sent);
}

int
HW_API::getHdmiTxMetadataSent_dolby_h14b_vsif(uint32_t chan, bool* sent) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataSent_dolby_h14b_vsif(sent);
}

int
HW_API::getHdmiTxMetadataSent_dolby_vsif(uint32_t chan, bool* sent) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxMetadataSent_dolby_vsif(sent);
}

int
HW_API::getHdmiTxInfoFramesInitialized(uint32_t chan, bool* initialized) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFramesInitialized(initialized);
}

int
HW_API::getHdmiTxInfoFrameVSIFEnable(uint32_t chan, bool* enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameVSIFEnable(enabled);
}

int
HW_API::getHdmiTxInfoFrameDRMEnable(uint32_t chan, bool* enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameDRMEnable(enabled);
}

int
HW_API::getHdmiTxInfoFrameHDR10PlusEnable(uint32_t chan, bool* enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameHDR10PlusEnable(enabled);
}

int
HW_API::getHdmiTxInfoFrameDolbyEnable(uint32_t chan, bool* enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameDolbyEnable(enabled);
}

int
HW_API::getHdmiTxInfoFrameSPDEnable(uint32_t chan, bool* enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameSPDEnable(enabled);
}

int
HW_API::getHdmiTxInfoFrameAudioMetadataEnable(uint32_t chan, bool* enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameAudioMetadataEnable(enabled);
}

int
HW_API::getHdmiTxInfoFrameAudio(uint32_t chan, HDMI_Xil_Type::AudioInfoFrame_type* audioInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameAudio(audioInfoFrame);
}

int
HW_API::getHdmiTxInfoFrameAVI(uint32_t chan, HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type* aviInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameAVI(aviInfoFrame);
}

int
HW_API::getHdmiTxInfoFrameVSIF(uint32_t chan, HDMI_Xil_Type::VendorSpecificInfoFrame_type* vsifInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameVSIF(vsifInfoFrame);
}

int
HW_API::getHdmiTxInfoFrameDRM(uint32_t chan, HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type* drmInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameDRM(drmInfoFrame);
}

int
HW_API::getHdmiTxInfoFrameHDR10Plus(uint32_t chan, HDMI_Xil_Type::HDR10PlusInfoFrame_type* hdr10pInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameHDR10Plus(hdr10pInfoFrame);
}

int
HW_API::getHdmiTxInfoFrameDolby(uint32_t chan, HDMI_Xil_Type::DolbyInfoFrame_type* dolbyInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameDolby(dolbyInfoFrame);
}

int
HW_API::getHdmiTxInfoFrameSPD(uint32_t chan, HDMI_Xil_Type::SourceProductDescriptorInfoFrame_type* spdInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameSPD(spdInfoFrame);
}

int
HW_API::getHdmiTxInfoFrameAudioMetadata(uint32_t chan, HDMI_Xil_Type::AudioMetadataPacket_type* audiometadataInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxInfoFrameAudioMetadata(audiometadataInfoFrame);
}

int
HW_API::setHdmiTxInfoFramesInitialized(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFramesInitialized();
}

int
HW_API::setHdmiTxInfoFrameVSIFEnable(uint32_t chan, bool enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameVSIFEnable(enabled);
}

int
HW_API::setHdmiTxInfoFrameDRMEnable(uint32_t chan, bool enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameDRMEnable(enabled);
}

int
HW_API::setHdmiTxInfoFrameHDR10PlusEnable(uint32_t chan, bool enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameHDR10PlusEnable(enabled);
}

int
HW_API::setHdmiTxInfoFrameDolbyEnable(uint32_t chan, bool enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameDolbyEnable(enabled);
}

int
HW_API::setHdmiTxInfoFrameSPDEnable(uint32_t chan, bool enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameSPDEnable(enabled);
}

int
HW_API::setHdmiTxInfoFrameAudioMetadataEnable(uint32_t chan, bool enabled) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameAudioMetadataEnable(enabled);
}

int
HW_API::setHdmiTxInfoFrameAudio(uint32_t chan, HDMI_Xil_Type::AudioInfoFrame_type* audioInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameAudio(audioInfoFrame);
}

int
HW_API::setHdmiTxInfoFrameAVI(uint32_t chan, HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type* aviInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameAVI(aviInfoFrame);
}

int
HW_API::setHdmiTxInfoFrameVSIF(uint32_t chan, HDMI_Xil_Type::VendorSpecificInfoFrame_type* vsifInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameVSIF(vsifInfoFrame);
}

int
HW_API::setHdmiTxInfoFrameDRM(uint32_t chan, HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type* drmInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameDRM(drmInfoFrame);
}

int
HW_API::setHdmiTxInfoFrameHDR10Plus(uint32_t chan, HDMI_Xil_Type::HDR10PlusInfoFrame_type* hdr10pInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameHDR10Plus(hdr10pInfoFrame);
}

int
HW_API::setHdmiTxInfoFrameDolby(uint32_t chan, HDMI_Xil_Type::DolbyInfoFrame_type* dolbyInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameDolby(dolbyInfoFrame);
}

int
HW_API::setHdmiTxInfoFrameSPD(uint32_t chan, HDMI_Xil_Type::SourceProductDescriptorInfoFrame_type* spdInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameSPD(spdInfoFrame);
}

int
HW_API::setHdmiTxInfoFrameAudioMetadata(uint32_t chan, HDMI_Xil_Type::AudioMetadataPacket_type* audiometadataInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxInfoFrameAudioMetadata(audiometadataInfoFrame);
}

int
HW_API::setHdmiRxDisableDropErr(uint32_t chan, bool set) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setRxDisableDropErr(set);
}

int
HW_API::setHdmiRxDisableHCountErr(uint32_t chan, bool set) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setRxDisableHCountErr(set);
}

int
HW_API::resetHdmiRxCounters(uint32_t chan) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].resetRxCounters();
}

int
HW_API::getHdmiRxFrameCount(uint32_t chan, uint32_t* frames) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxFrameCount(frames);
}

int
HW_API::getHdmiRxDropErrCount(uint32_t chan, uint32_t* errors, uint16_t* line, uint16_t* hcount) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxDropErrCount(errors, line, hcount);
}

int
HW_API::getHdmiRxHCountErrCount(uint32_t chan, uint32_t* errors, uint16_t* line, uint16_t* hcount) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxHCountErrCount(errors, line, hcount);
}

int
HW_API::getHdmiRxVCountErrCount(uint32_t chan, uint32_t* errors, uint16_t* vcount) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxVCountErrCount(errors, vcount);
}

int
HW_API::setHdmiRxLinkStatusInterval(uint32_t chan, uint32_t statusInterval) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setRxLinkStatusInterval(statusInterval);
}

int
HW_API::getHdmiRxLinkStatusError(uint32_t chan, uint32_t* link0, uint32_t* link1, uint32_t* link2) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxLinkStatusError(link0, link1, link2);
}

int
HW_API::getHdmiTxSi570LockEnable(uint32_t chan, bool* enable) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getTxSi570LockEnable(enable);
}

int
HW_API::setHdmiTxSi570LockEnable(uint32_t chan, bool enable) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setTxSi570LockEnable(enable);
}

int
HW_API::getHdmiRxInfoFrameAudio(uint32_t chan, HDMI_Xil_Type::AudioInfoFrame_type* audioInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameAudio(audioInfoFrame);
}

int
HW_API::getHdmiRxInfoFrameAVI(uint32_t chan, HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type* aviInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameAVI(aviInfoFrame);
}

int
HW_API::getHdmiRxInfoFrameVSIF(uint32_t chan, HDMI_Xil_Type::VendorSpecificInfoFrame_type* vsifInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameVSIF(vsifInfoFrame);
}

int
HW_API::getHdmiRxInfoFrameGCP(uint32_t chan, HDMI_Xil_Type::GeneralControlInfoFrame_type* gcpInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameGCP(gcpInfoFrame);
}

int
HW_API::getHdmiRxInfoFrameDRM(uint32_t chan, HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type* drmInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameDRM(drmInfoFrame);
}

int
HW_API::getHdmiRxInfoFrameSPD(uint32_t chan, HDMI_Xil_Type::SourceProductDescriptorInfoFrame_type* spdInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameSPD(spdInfoFrame);
}

int
HW_API::getHdmiRxInfoFrameHDR10Plus(uint32_t chan, HDMI_Xil_Type::HDR10PlusInfoFrame_type* hdr10pInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameHDR10Plus(hdr10pInfoFrame);
}

int
HW_API::getHdmiRxInfoFrameDolby(uint32_t chan, HDMI_Xil_Type::DolbyInfoFrame_type* dolbyInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameDolby(dolbyInfoFrame);
}

int
HW_API::getHdmiRxInfoFrameAudioMetadata(uint32_t chan, HDMI_Xil_Type::AudioMetadataPacket_type* audiometadataInfoFrame) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameAudioMetadata(audiometadataInfoFrame);
}

int
HW_API::getHdmiRxMetadataCount(uint32_t chan, uint16_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxMetadataCount(count);
}

int
HW_API::getHdmiRxInfoFrameSPDAfterStreamUp(uint32_t chan, bool* spdAfterStreamUp) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameSPDAfterStreamUp(spdAfterStreamUp);
}

int
HW_API::getHdmiRxInfoFrameDolby14bCnt(uint32_t chan, uint8_t* dolby14bCnt) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxInfoFrameDolby14bCnt(dolby14bCnt);
}

int
HW_API::getHdmiRxInfoFrameAudio_ChannelCount(HDMI_Xil_Type::AudioInfoFrame_type audioInfoFrame, uint8_t* cc) {
  *cc = audioInfoFrame.CC;
  return 0;
}

int
HW_API::getHdmiRxInfoFrameAudio_ChannelAllocation(HDMI_Xil_Type::AudioInfoFrame_type audioInfoFrame, uint8_t* ca) {
  *ca = audioInfoFrame.CA;
  return 0;
}

int
HW_API::getHdmiRxInfoFrameAVI_VIC(HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type aviInfoFrame, uint8_t* vic) {
  *vic = aviInfoFrame.VIC;
  return 0;
}

int
HW_API::getHdmiRxInfoFrameVSIF_HDMI_VIC(HDMI_Xil_Type::VendorSpecificInfoFrame_type vsifInfoFrame, uint8_t* hdmi_vic) {
  *hdmi_vic = vsifInfoFrame.HDMI_VIC;
  return 0;
}

int
HW_API::getHdmiRxInfoFrameGCP_Clear_AVMUTE(HDMI_Xil_Type::GeneralControlInfoFrame_type gcpInfoFrame, uint8_t* clear_avmute) {
  *clear_avmute = gcpInfoFrame.Clear_AVMUTE;
  return 0;
}

int
HW_API::getHdmiRxInfoFrameGCP_Set_AVMUTE(HDMI_Xil_Type::GeneralControlInfoFrame_type gcpInfoFrame, uint8_t* set_avmute) {
  *set_avmute = gcpInfoFrame.Set_AVMUTE;
  return 0;
}

int
HW_API::getHdmiRxClockNoVideo(uint32_t chan, uint32_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxClockNoVideo(count);
}

int
HW_API::getHdmiRxClockNoVideoThreshold(uint32_t chan, uint32_t* count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].getRxClockNoVideoThreshold(count);
}

int
HW_API::setHdmiRxClockNoVideoThreshold(uint32_t chan, uint32_t count) {
  assert(HW_API::getHdmiInitDone(chan));
  return (int)hdmi[chan].setRxClockNoVideoThreshold(count);
}

/* -- Icron USB -- */

ZYNQUsbIPUDPIP trxs_usb[HW_API::N_XGE];
usb_udpip_encap* usb_ptr[HW_API::N_XGE];
ZYNQIcronUSB icron_usb;

void
HW_API::initIcronUSB() {
  if (HW_API::getFPGACapability("INC_ICRON_USB") <= 0)
  {
    printf("INC_ICRON_USB feature is required but not enabled!\n");
    return;
  }
  if ((HW_API::getFPGACapability("INC_XGE") <= 0) && (HW_API::getFPGACapability("INC_1GE") <= 0) && (HW_API::getFPGACapability("INC_2G5E") <= 0))
  {
    printf("INC_XGE or INC_1GE or INC_2G5E feature is required but not enabled!\n");
    return;
  }
  for (uint32_t i = 0; i < HW_API::N_XGE; i++) {
      usb_ptr[i] = (usb_udpip_encap*)&trxs_usb[i];
      usb_ptr[i]->init(i);
  }
  icron_usb.init(usb_ptr);
  // Set offset values according to SFP mode, with slower modes needing
  // larger offsets
  if (HW_API::getFPGACapability("INC_1GE") > 0) { // 1G
    icron_usb.setOffset(2048);
  } else if (HW_API::getFPGACapability("INC_2G5E") > 0) { // 2.5G
    icron_usb.setOffset(1024);
  } else { // 10G
    icron_usb.setOffset(512);
  }
  icron_usb.setLockedMode(0, 1); // Enable locked mode
  return;
}

bool
HW_API::getIcronUSBInitDone() {
  return icron_usb.getInitDone();
}

int
HW_API::getIcronUSBGTXStatus(uint32_t* GTXStatus){
  assert(icron_usb.getInitDone());
  return icron_usb.getGTXStatus(0, GTXStatus);
}

int
HW_API::getIcronUSBLink(bool* link){
  assert(icron_usb.getInitDone());
  return icron_usb.getIcronLink(0, link);
}

int
HW_API::getIcronUSBHost(bool* host){
  assert(icron_usb.getInitDone());
  return icron_usb.getIcronHost(0, host);
}

int
HW_API::getIcronUSBVbusEn(bool* vbus_en){
  assert(icron_usb.getInitDone());
  return icron_usb.getIcronVbusEn(0, vbus_en);
}

int
HW_API::getIcronUSBActivity(bool* activity){
  assert(icron_usb.getInitDone());
  return icron_usb.getIcronActivity(0, activity);
}

int
HW_API::getIcronUSBGMII(bool* gmii_rx, bool* gmii_tx){
  assert(icron_usb.getInitDone());
  return icron_usb.getIcronGMII(0, gmii_rx, gmii_tx);
}

int
HW_API::getIcronUSBLinkState(IcronUSB::linkState* state){
  assert(icron_usb.getInitDone());
  return icron_usb.getIcronLinkState(0, state);
}

int
HW_API::getIcronUSBHostState(bool* state){
  assert(icron_usb.getInitDone());
  return icron_usb.getIcronHostState(0, state);
}

int
HW_API::getIcronUSBVbusEnState(bool* state){
  assert(icron_usb.getInitDone());
  return icron_usb.getIcronVbusEnState(0, state);
}

int
HW_API::getIcronUSBActivityState(bool* state){
  assert(icron_usb.getInitDone());
  return icron_usb.getIcronActivityState(0, state);
}

int
HW_API::getIcronUSBGMIIState(bool* state_rx, bool* state_tx){
  assert(icron_usb.getInitDone());
  return icron_usb.getIcronGMIIState(0, state_rx, state_tx);
}

int
HW_API::dumpIcronUSBStatus(){
  assert(icron_usb.getInitDone());
  return icron_usb.dumpIcronStatus(0);
}

int
HW_API::dumpIcronUSBStatusState(){
  assert(icron_usb.getInitDone());
  return icron_usb.dumpIcronStatusState(0);
}

int
HW_API::dumpIcronUSBControl(){
  assert(icron_usb.getInitDone());
  return icron_usb.dumpIcronControl(0);
}

int
HW_API::setIcronUSBProgB(bool prog_B){
  assert(icron_usb.getInitDone());
  return icron_usb.setIcronProgB(0, prog_B);
}

int
HW_API::setIcronUSBBootSel0(bool boot_sel0){
  assert(icron_usb.getInitDone());
  return icron_usb.setIcronBootSel0(0, boot_sel0);
}

int
HW_API::setIcronUSBMode(bool usbmode){
  assert(icron_usb.getInitDone());
  return icron_usb.setIcronUsbMode(0, usbmode);
}

int
HW_API::setIcronUSBPhyL2En(bool phyl2en){
  assert(icron_usb.getInitDone());
  return icron_usb.setIcronPhyL2En(0, phyl2en);
}

int
HW_API::setIcronUSBPairN(bool pairn){
  assert(icron_usb.getInitDone());
  return icron_usb.setIcronPairN(0, pairn);
}

int
HW_API::setIcronUSBResetN(bool resetn){
  assert(icron_usb.getInitDone());
  return icron_usb.setIcronResetN(0, resetn);
}

int
HW_API::setIcronUSBRexLexMode(bool rex_mode){
  assert(icron_usb.getInitDone());
  return icron_usb.setIcronRexLexMode(0, rex_mode);
}

int
HW_API::getIcronRxOffset(uint32_t* offset) {
  assert(icron_usb.getInitDone());
  return icron_usb.getRxOffset(0, offset);
}

int
HW_API::setIcronOffset(uint32_t offset) {
  assert(icron_usb.getInitDone());
  return icron_usb.setOffset(offset);
 }

int
HW_API::getIcronOffset(uint32_t* offset) {
  assert(icron_usb.getInitDone());
  return icron_usb.getOffset(offset);
}

int
HW_API::setIcronLockedMode(bool enable) {
  assert(icron_usb.getInitDone());
  return icron_usb.setLockedMode(0, enable);
}

int
HW_API::getIcronLockedMode(bool* enable) {
  assert(icron_usb.getInitDone());
  return icron_usb.getLockedMode(0, enable);
}

int
HW_API::getIcronRxLocked(bool* locked) {
  assert(icron_usb.getInitDone());
  return icron_usb.getRxLocked(0, locked);
}

int
HW_API::getIcronRxFifoStatus(uint32_t* status) {
  assert(icron_usb.getInitDone());
  return icron_usb.getUSBRxFifoStatus(0, status);
}

int
HW_API::getIcronTxFifoStatus(uint32_t* status) {
  assert(icron_usb.getInitDone());
  return icron_usb.getUSBTxFifoStatus(0, status);
}

/* -- Audio Mixer Interface --*/
ZYNQ_Audio_Mixer amixer[HW_API::NUM_MIXERS];

void
HW_API::initAMixer(uint8_t index, uint8_t InBits, uint8_t FlBits){
  if(index >= HW_API::getFPGACapability("N_AUDIO_MIXERS"))
  {
    printf("N_AUDIO_MIXER feature is less than index %u.!\n", index);
    return;
  }
  amixer[index].init(index, InBits, FlBits);
  return;
}

bool
HW_API::getAMixerInitDone(uint8_t index){
  return amixer[index].getInitDone();
}

int
HW_API::setAMixerCommandInput(uint8_t index, uint8_t channel, uint8_t branch, bool invert, uint8_t inStream, uint8_t inChannel, float gain){
  assert(amixer[index].getInitDone());
  return amixer[index].setCommandInput(channel, branch, invert, inStream, inChannel, gain);
}

int
HW_API::getAMixerInvertControl(uint8_t index, uint8_t channel, uint8_t branch, bool *invert){
  assert(amixer[index].getInitDone());
  return amixer[index].getInvertControl(channel, branch, invert);
}

int
HW_API::getAMixerInStream(uint8_t index, uint8_t channel, uint8_t branch, uint8_t *inStream){
  assert(amixer[index].getInitDone());
  return amixer[index].getInStream(channel, branch, inStream);
}

int
HW_API::getAMixerInChannel(uint8_t index, uint8_t channel, uint8_t branch, uint8_t *inChannel){
  assert(amixer[index].getInitDone());
  return amixer[index].getInChannel(channel, branch, inChannel);
}

int
HW_API::getAMixerGainCoefficient(uint8_t index, uint8_t channel, uint8_t branch, float *gain){
  assert(amixer[index].getInitDone());
  return amixer[index].getGainCoefficient(channel, branch, gain);
}

int
HW_API::getAMixerCommandInput(uint8_t index, uint8_t channel, uint8_t branch, bool *invert, uint8_t *inStream, uint8_t *inChannel, float *gain){
  assert(amixer[index].getInitDone());
  return amixer[index].getCommandInput(channel, branch, invert, inStream, inChannel, gain);
}

int
HW_API:: setAMixerInvertControl(uint8_t index, uint8_t channel, uint8_t branch, bool invert){
  assert(amixer[index].getInitDone());
  return amixer[index].setInvertControl(channel, branch, invert);
}

int
HW_API:: setAMixerInStream(uint8_t index, uint8_t channel, uint8_t branch, uint8_t inStream){
  assert(amixer[index].getInitDone());
  return amixer[index].setInStream(channel, branch, inStream);
}

int
HW_API:: setAMixerInChannel(uint8_t index, uint8_t channel, uint8_t branch, uint8_t inChannel){
  assert(amixer[index].getInitDone());
  return amixer[index].setInChannel(channel, branch, inChannel);
}

int
HW_API:: setAMixerGainCoefficient(uint8_t index, uint8_t channel, uint8_t branch, float gain){
  assert(amixer[index].getInitDone());
  return amixer[index].setGainCoefficient(channel, branch, gain);
}

// OSD for Scalers
// Update Settings
int
HW_API::setScalerOSDSettings(uint32_t path, MVScalerTopType::OSDSettings *osd_settings){
  assert(HW_API::getScalerPathInitDone(path));
  return scale_path[path].setOSDSettings(osd_settings);
}

// Char Table
void
HW_API::setCharTable(uint32_t path, uint32_t idx, uint32_t addr_max, char * char_ptr, char colour){
  assert(HW_API::getScalerPathInitDone(path));
  // convert unsigned char to uint32_t to be able to pass value in memset
  uint32_t colour_font = static_cast<uint32_t>(colour);
  char colour_buffer[MVScalerTopConsts::OSD_MAX_CHAR_ROWS * MVScalerTopConsts::OSD_MAX_CHAR_COLS];
  // colour_ptr starts at first index of colour_buffer
  char * colour_ptr = &colour_buffer[0];
  // set the bytes of colour_buffer starting at address of colour_buffer to the value of colour_font
  memset(colour_buffer, colour_font, sizeof(colour_buffer));
  scale_path[path].writeOSDCharBlock(idx, addr_max, char_ptr, colour_ptr);
  return;
}

void
HW_API::setCharTable(uint32_t path, uint32_t idx, uint32_t addr_max, char* char_ptr, char* colour_ptr){
  assert(HW_API::getScalerPathInitDone(path));
  scale_path[path].writeOSDCharBlock(idx, addr_max, char_ptr, colour_ptr);
  return;
}

// Font Table
void
HW_API::setFontTable(uint32_t path, uint32_t idx, uint32_t addr_max, uint32_t char_max, uint32_t *data){
  assert(HW_API::getScalerPathInitDone(path));
  scale_path[path].writeOSDFontBlock(idx, addr_max, char_max, data);
  return;
}

// Update Settings
void
HW_API::setScalerOSDSettings(uint32_t path, bool use_b, bool osd_enable,
                             uint32_t char_win_h_start, uint32_t char_win_v_start, uint32_t char_win_h_length, uint32_t char_win_v_lines,
                             uint32_t font_h_length, uint32_t font_v_lines, uint32_t font_v_start, uint32_t font_h_scale, uint32_t font_v_scale,
                             uint32_t font_alpha, uint32_t bg_alpha){
  assert(HW_API::getScalerPathInitDone(path));
  scale_path[path].initOSDParameters();
  scale_path[path].setOSDUseB(use_b);
  scale_path[path].setOSDEnable(osd_enable);
  scale_path[path].setCharWinHStart(char_win_h_start);
  scale_path[path].setCharWinVStart(char_win_v_start);
  scale_path[path].setCharWinHLength(char_win_h_length);
  scale_path[path].setCharWinVLines(char_win_v_lines);
  scale_path[path].setFontHLength(font_h_length);
  scale_path[path].setFontVLines(font_v_lines);
  scale_path[path].setFontVStart(font_v_start);
  scale_path[path].setFontHScale(font_h_scale);
  scale_path[path].setFontVScale(font_v_scale);
  scale_path[path].setFontAlpha(font_alpha);
  scale_path[path].setBgAlpha(bg_alpha);
  return;
}

// General Register Functions
ZYNQGENDCXO gen_dcxo[NUM_XO];
gen_dcxo_ctrl* p_dcxo_objects[NUM_XO];
ZYNQGENREG genreg;

void
HW_API::initGeneral(){
  for (uint32_t i = 0; i < NUM_XO; i++) {
    p_dcxo_objects[i] = (gen_dcxo_ctrl*) &gen_dcxo[i];
    p_dcxo_objects[i]->init(i);
  }
  genreg.init(p_dcxo_objects);
  return;
}

bool
HW_API::getGeneralInitDone(){
  return genreg.getInitDone();
}

int
HW_API::getGeneralFPGAIndex(bool* index){
  assert(HW_API::getGeneralInitDone());
  return genreg.getFPGAIndex(index);
}

int
HW_API::setGeneralFPGAIndex(bool index){
  assert(HW_API::getGeneralInitDone());
  return genreg.setFPGAIndex(index);
}

int
HW_API::setGeneralFPGAReset(bool reset){
  assert(HW_API::getGeneralInitDone());
  return genreg.setFPGAReset(reset);
}

int
HW_API::getGeneralHdmiInHPD(uint8_t index, bool* hpd){
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiInHPD(index, hpd);
}

int
HW_API::getGeneralHdmiOutHPD(uint8_t index, bool* hpd){
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiOutHPD(index, hpd);
}

int
HW_API::getGeneralHdmiInCableDetect(uint8_t index, bool* cableDetect){
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiInCableDetect(index, cableDetect);
}

int
HW_API::getGeneralHdmiInCableDetectMux(uint8_t index, bool* cableDetect){
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiInCableDetectMux(index, cableDetect);
}

int
HW_API::getGeneralHdmiMuxSelect(uint8_t index, bool* select){
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiMuxSelect(index, select);
}

int
HW_API::setGeneralHdmiMuxSelect(uint8_t index, bool select){
  assert(HW_API::getGeneralInitDone());
  return genreg.setHdmiMuxSelect(index, select);
}

int
HW_API::getGeneralHdmiOutDisable(uint8_t index, bool* disable){
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiOutDisable(index, disable);
}

int
HW_API::setGeneralHdmiOutDisable(uint8_t index, bool disable){
  assert(HW_API::getGeneralInitDone());
  return genreg.setHdmiOutDisable(index, disable);
}

int
HW_API::getGeneralHdmiOut5VDisable(uint8_t index, bool* disable){
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiOut5VDisable(index, disable);
}

int
HW_API::setGeneralHdmiOut5VDisable(uint8_t index, bool disable){
  assert(HW_API::getGeneralInitDone());
  return genreg.setHdmiOut5VDisable(index, disable);
}

int
HW_API::getGeneralHdmiBridgeReset(uint8_t index, bool* reset){
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiBridgeReset(index, reset);
}

int
HW_API::setGeneralHdmiBridgeReset(uint8_t index, bool reset){
  assert(HW_API::getGeneralInitDone());
  return genreg.setHdmiBridgeReset(index, reset);
}

int
HW_API::getGeneralHdmiPause(bool* pause){
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiPause(pause);
}

int
HW_API::setGeneralHdmiPause(bool pause){
  assert(HW_API::getGeneralInitDone());
  return genreg.setHdmiPause(pause);
}

int
HW_API::getGeneralHdmiReset(bool* reset){
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiReset(reset);
}

int
HW_API::setGeneralHdmiReset(bool reset){
  assert(HW_API::getGeneralInitDone());
  return genreg.setHdmiReset(reset);
}

int
HW_API::getGeneralUsbReset(bool* reset){
  assert(HW_API::getGeneralInitDone());
  return genreg.getUsbReset(reset);
}

int
HW_API::setGeneralUsbReset(bool reset){
  assert(HW_API::getGeneralInitDone());
  return genreg.setUsbReset(reset);
}

int
HW_API::getGeneralXGEClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.getXGEClkFrequency(frequency);
}

int
HW_API::getGeneral125mhzClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.get125mhzClkFrequency(frequency);
}

int
HW_API::getGeneral62m5hzClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.get62m5hzClkFrequency(frequency);
}

int
HW_API::getGeneral312m5hzClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.get312m5hzClkFrequency(frequency);
}

int
HW_API::getGeneral156m25hzClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.get156m25hzClkFrequency(frequency);
}

int
HW_API::getGeneralHdmiSouthTxClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiSouthTxClkFrequency(frequency);
}

int
HW_API::getGeneralHdmiNorthTxClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.getHdmiNorthTxClkFrequency(frequency);
}

int
HW_API::getGeneralInterFPGAClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.getInterFPGAClkFrequency(frequency);
}

int
HW_API::getGeneralDRUClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.getDRUClkFrequency(frequency);
}

int
HW_API::getGeneralReflockClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.getReflockClkFrequency(frequency);
}

int
HW_API::getGeneralMgt110Refclk1ClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.getMgt110Refclk1ClkFrequency(frequency);
}

int
HW_API::getGeneralMgt112Refclk1ClkFrequency(uint32_t* frequency) {
  assert(HW_API::getGeneralInitDone());
  return genreg.getMgt112Refclk1ClkFrequency(frequency);
}

int
HW_API::getGeneralUsbPhyMdio(uint32_t phy_addr, uint32_t reg_addr, uint32_t* status){
  assert(HW_API::getGeneralInitDone());
  return genreg.getUsbPhyMdio(phy_addr, reg_addr, status);
}

int
HW_API::setGeneralUsbPhyMdio(uint32_t phy_addr, uint32_t reg_addr, uint32_t command){
  assert(HW_API::getGeneralInitDone());
  return genreg.setUsbPhyMdio(phy_addr, reg_addr, command);
}

int
HW_API::getGeneralAnalogMute(bool* mute){
  assert(HW_API::getGeneralInitDone());
  return genreg.getAnalogMute(mute);
}

int
HW_API::setGeneralAnalogMute(bool mute){
  assert(HW_API::getGeneralInitDone());
  return genreg.setAnalogMute(mute);
}

int
HW_API::getGeneralUSBTxSrcSel(bool* src){
  assert(HW_API::getGeneralInitDone());
  return genreg.getUSBTxSrcSel(src);
}

int
HW_API::setGeneralUSBTxSrcSel(bool src){
  assert(HW_API::getGeneralInitDone());
  return genreg.setUSBTxSrcSel(src);
}

int
HW_API::getGeneralSPDIFMute(uint8_t index, bool* mute){
  assert(HW_API::getGeneralInitDone());
  return genreg.getSPDIFMute(index, mute);
}

int
HW_API::setGeneralSPDIFMute(uint8_t index, bool mute){
  assert(HW_API::getGeneralInitDone());
  return genreg.setSPDIFMute(index, mute);
}

int
HW_API::getGeneralI2CExpanderReset(bool* reset){
  assert(HW_API::getGeneralInitDone());
  return genreg.getI2CExpanderReset(reset);
}

int
HW_API::setGeneralI2CExpanderReset(bool reset){
  assert(HW_API::getGeneralInitDone());
  return genreg.setI2CExpanderReset(reset);
}

int
HW_API::getGeneralPbState(bool* pb){
  assert(HW_API::getGeneralInitDone());
  return genreg.getPbState(pb);
}

int
HW_API::getGeneralLedRgb(uint8_t* red, uint8_t* green, uint8_t* blue){
  assert(HW_API::getGeneralInitDone());
  return genreg.getLedRgb(red, green, blue);
}

int
HW_API::setGeneralLedRgb(uint8_t red, uint8_t green, uint8_t blue){
  assert(HW_API::getGeneralInitDone());
  return genreg.setLedRgb(red, green, blue);
}

int
HW_API::getGeneralSupply12vMonitor(uint8_t index, bool* monitor){
  assert(HW_API::getGeneralInitDone());
  return genreg.getSupply12vMonitor(index, monitor);
}

int
HW_API::getGeneralSupplyOrFault(uint8_t index, bool* orfault){
  assert(HW_API::getGeneralInitDone());
  return genreg.getSupplyOrFault(index, orfault);
}

int
HW_API::getGeneralTRMSelect(bool* select){
  assert(HW_API::getGeneralInitDone());
  return genreg.getTRMSelect(select);
}

int
HW_API::setGeneralTRMSelect(bool select){
  assert(HW_API::getGeneralInitDone());
  return genreg.setTRMSelect(select);
}

int
HW_API::getGeneralXgeRxInvertPolarity(uint8_t index, bool* invert){
  assert(HW_API::getGeneralInitDone());
  return genreg.getXgeRxInvertPolarity(index, invert);
}

int
HW_API::setGeneralXgeRxInvertPolarity(uint8_t index, bool invert){
  assert(HW_API::getGeneralInitDone());
  return genreg.setXgeRxInvertPolarity(index, invert);
}

int
HW_API::getGeneralXgeTxInvertPolarity(uint8_t index, bool* invert){
  assert(HW_API::getGeneralInitDone());
  return genreg.getXgeTxInvertPolarity(index, invert);
}

int
HW_API::setGeneralXgeTxInvertPolarity(uint8_t index, bool invert){
  assert(HW_API::getGeneralInitDone());
  return genreg.setXgeTxInvertPolarity(index, invert);
}

int
HW_API::getGeneralSpiDisplay(uint8_t* data){
  assert(HW_API::getGeneralInitDone());
  return genreg.getSpiDisplay(data);
}

int
HW_API::setGeneralSpiDisplay(uint8_t data){
  assert(HW_API::getGeneralInitDone());
  return genreg.setSpiDisplay(data);
}

int
HW_API::getGeneralToggleSwitch(bool a_not_b, bool* toggle){
  assert(HW_API::getGeneralInitDone());
  return genreg.getToggleSwitch(a_not_b, toggle);
}

int
HW_API::getGeneralLocalFault(bool* fault){
  assert(HW_API::getGeneralInitDone());
  return genreg.getLocalFault(fault);
}

int
HW_API::setGeneralLocalFault(bool fault){
  assert(HW_API::getGeneralInitDone());
  return genreg.setLocalFault(fault);
}

int
HW_API::getGeneralFanFail(bool* fail){
  assert(HW_API::getGeneralInitDone());
  return genreg.getFanFail(fail);
}

int
HW_API::initGeneralDCXO(uint8_t index, dcxo_ctrl::dcxo_select_type dcxo, uint32_t si570DefaultFrequency){
  assert(genreg.getInitDone());
  return genreg.initDCXO(index, dcxo, si570DefaultFrequency);
};

int
HW_API::initGeneralDCXO(uint8_t index, uint32_t si570DefaultFrequency){
  assert(genreg.getInitDone());
  return genreg.initDCXO(index, si570DefaultFrequency);
};

int
HW_API::setGeneralDCXOClock(uint8_t index, uint32_t frequency, bool cy29411AcceptBestStableFreq){
  assert(genreg.getInitDone());
  return genreg.setDCXOClock(index, frequency, cy29411AcceptBestStableFreq);
};

int
HW_API::setGeneralDCXOLockEnable(uint8_t index, bool value){
  assert(genreg.getInitDone());
  return genreg.setDCXOLockEnable(index, value);
};

int
HW_API::getGeneralDCXOLockEnable(uint8_t index, bool* value){
  assert(genreg.getInitDone());
  return genreg.getDCXOLockEnable(index, value);
};

int
HW_API::setGeneralDCXODone(uint8_t index, bool value){
  assert(genreg.getInitDone());
  return genreg.setDCXODone(index, value);
};

int
HW_API::getGeneralDCXODone(uint8_t index, bool* value){
  assert(genreg.getInitDone());
  return genreg.getDCXODone(index, value);
};

int
HW_API::readGeneralDCXOSelect(uint8_t index, bool* initialized, dcxo_ctrl::dcxo_select_type* dcxo) {
  assert(genreg.getInitDone());
  return genreg.readDCXOSelect(index, initialized, dcxo);
}

int
HW_API::readGeneralDCXOSettingsCY29411(uint8_t index, bool* valid, cy29411_ctrl::cy29411_settings_type* settings){
  assert(genreg.getInitDone());
  return genreg.readDCXOSettingsCY29411(index, valid, settings);
};

int
HW_API::readGeneralDCXOSettingsSi570(uint8_t index, bool* valid, si570_ctrl::si570_settings_type* settings){
  assert(genreg.getInitDone());
  return genreg.readDCXOSettingsSi570(index, valid, settings);
};

// InterFPGA Functions
ZYNQInterfpga interfpga[HW_API::NUM_INTERFPGA_QUADS];

uint8_t
HW_API::mapInterfpgaQuadToIndex(uint8_t quad)
{
  switch (quad) {
    case 111:
      return HW_API::INTERFPGA_MGT111;
    case 109:
      return HW_API::INTERFPGA_MGT109;
    default:
      printf("InterFPGA quad %u must be 109 or 111!\n", quad);
      return 2;
  }
}

void
HW_API::initInterfpga(uint8_t quad)
{
  if(quad == HW_API::INTERFPGA_MGT111 && 0 >= HW_API::getFPGACapability("N_INTER")) {
    printf("N_INTER feature must be non-0 for mgt111!\n");
    return;
  } else if (quad == HW_API::INTERFPGA_MGT109 && 0 >= HW_API::getFPGACapability("N_INTER_IP_RX")) {
    printf("N_INTER_IP_RX feature must be non-0 for mgt109!\n");
    return;
  }
  interfpga[quad].init(quad);
  return;
}

bool
HW_API::getInterfpgaInitDone(uint8_t quad)
{
  return interfpga[quad].getInitDone();
}

int
HW_API::getInterfpgaLinkStatus(uint8_t quad, uint8_t chan, bool* status){
  assert(HW_API::getInterfpgaInitDone(quad));
  *status = interfpga[quad].getLinkStatus(chan);
  return 0;
}

int
HW_API::getInterfpgaLaneStatus(uint8_t quad, uint8_t chan, uint8_t* status){
  assert(HW_API::getInterfpgaInitDone(quad));
  *status = interfpga[quad].getLaneStatus(chan);
  return 0;
}

int
HW_API::getInterfpgaSoftErrorStatus(uint8_t quad, uint8_t chan, bool* error){
  assert(HW_API::getInterfpgaInitDone(quad));
  *error = interfpga[quad].getSoftErrorStatus(chan);
  return 0;
}

int
HW_API::getInterfpgaHardErrorStatus(uint8_t quad, uint8_t chan, bool* error){
  assert(HW_API::getInterfpgaInitDone(quad));
  *error = interfpga[quad].getHardErrorStatus(chan);
  return 0;
}

int
HW_API::setInterfpgaReset(uint8_t quad, uint8_t chan, bool reset){
  assert(HW_API::getInterfpgaInitDone(quad));
  if (chan == 0 && HW_API::getFPGACapability("N_LANES_PER_INTER") ==1 ) {
    for (int i = 0; i < HW_API::getFPGACapability("N_INTER"); i++)
      {
        interfpga[quad].setReset(i, reset);
      }
    for (int i = 0; i < HW_API::getFPGACapability("N_INTER_IP_RX"); i++)
      {
        interfpga[quad].setIpReset(i, reset);
      }
  } else if (chan == 0 && HW_API::getFPGACapability("N_LANES_PER_INTER") ==2 ) {
    for (int i = 0; i < HW_API::getFPGACapability("N_INTER"); i++)
      {
        interfpga[quad].setReset(i, reset);
      }
  } else {
    interfpga[quad].setReset(chan, reset);
  }
  return 0;
}

int
HW_API::getInterfpgaIpLinkStatus(uint8_t quad, uint8_t chan, bool* status){
  assert(HW_API::getInterfpgaInitDone(quad));
  *status = interfpga[quad].getIpLinkStatus(chan);
  return 0;
}

int
HW_API::getInterfpgaIpLaneStatus(uint8_t quad, uint8_t chan, uint8_t* status){
  assert(HW_API::getInterfpgaInitDone(quad));
  *status = interfpga[quad].getIpLaneStatus(chan);
  return 0;
}

int
HW_API::getInterfpgaIpSoftErrorStatus(uint8_t quad, uint8_t chan, bool* error){
  assert(HW_API::getInterfpgaInitDone(quad));
  *error = interfpga[quad].getIpSoftErrorStatus(chan);
  return 0;
}

int
HW_API::getInterfpgaIpHardErrorStatus(uint8_t quad, uint8_t chan, bool* error){
  assert(HW_API::getInterfpgaInitDone(quad));
  *error = interfpga[quad].getIpHardErrorStatus(chan);
  return 0;
}

int
HW_API::setInterfpgaIpReset(uint8_t quad, uint8_t chan, bool reset){
  assert(HW_API::getInterfpgaInitDone(quad));
  if (chan == 0 && HW_API::getFPGACapability("N_LANES_PER_INTER") ==2 ) {
    for (int i = 0; i < HW_API::getFPGACapability("N_INTER_IP_RX"); i++)
      {
        interfpga[quad].setIpReset(i, reset);
      }
  } else {
    interfpga[quad].setIpReset(chan, reset);
  }
  return 0;
}

int
HW_API::getInterfpgaTxcErrorCnt(uint8_t quad, uint8_t chan){
  assert(HW_API::getInterfpgaInitDone(quad));
  return (int)interfpga[quad].getTxcErrorCnt(chan);
}

int
HW_API::resetInterfpgaTxcErrorCnt(uint8_t quad, uint8_t chan, bool reset){
  assert(HW_API::getInterfpgaInitDone(quad));
  interfpga[quad].resetTxcErrorCnt(chan, reset);
  return 0;
}

int
HW_API::getInterfpgaTxaErrorCnt(uint8_t quad, uint8_t chan){
  assert(HW_API::getInterfpgaInitDone(quad));
  return (int)interfpga[quad].getTxaErrorCnt(chan);
}

int
HW_API::resetInterfpgaTxaErrorCnt(uint8_t quad, uint8_t chan, bool reset){
  assert(HW_API::getInterfpgaInitDone(quad));
  interfpga[quad].resetTxaErrorCnt(chan, reset);
  return 0;
}

int
HW_API::getInterfpgaTxmErrorCnt(uint8_t quad, uint8_t chan){
  assert(HW_API::getInterfpgaInitDone(quad));
  return (int)interfpga[quad].getTxmErrorCnt(chan);
}

int
HW_API::resetInterfpgaTxmErrorCnt(uint8_t quad, uint8_t chan, bool reset){
  assert(HW_API::getInterfpgaInitDone(quad));
  interfpga[quad].resetTxmErrorCnt(chan, reset);
  return 0;
}

int
HW_API::getInterfpgaTxuErrorCnt(uint8_t quad, uint8_t chan){
  assert(HW_API::getInterfpgaInitDone(quad));
  return (int)interfpga[quad].getTxuErrorCnt(chan);
}

int
HW_API::resetInterfpgaTxuErrorCnt(uint8_t quad, uint8_t chan, bool reset){
  assert(HW_API::getInterfpgaInitDone(quad));
  interfpga[quad].resetTxuErrorCnt(chan, reset);
  return 0;
}

int
HW_API::getInterfpgaTxvErrorCnt(uint8_t quad, uint8_t chan){
  assert(HW_API::getInterfpgaInitDone(quad));
  return (int)interfpga[quad].getTxvErrorCnt(chan);
}

int
HW_API::resetInterfpgaTxvErrorCnt(uint8_t quad, uint8_t chan, bool reset){
  assert(HW_API::getInterfpgaInitDone(quad));
  interfpga[quad].resetTxvErrorCnt(chan, reset);
  return 0;
}

// --12G SDI --

ZYNQSDI12GDCXO sdi_12g_dcxo[2];
sdi_12g_dcxo_ctrl* sdi_12g_dcxo_ptr[2];
ZYNQSDI12G sdi_12g;

void
HW_API::initSDI12G() {
  if (HW_API::getFPGACapability("INC_SDI_12G") <= 0)
  {
    printf("INC_SDI_12G feature is required but not enabled!\n");
    return;
  }
  for (uint32_t i = 0; i < 2; i++) {
    sdi_12g_dcxo_ptr[i] = (sdi_12g_dcxo_ctrl*)&sdi_12g_dcxo[i];
    sdi_12g_dcxo_ptr[i]->init(i);
  }
  sdi_12g.init(sdi_12g_dcxo_ptr);
  return;
}

bool
HW_API::getSDI12GInitDone() {
  return sdi_12g.getInitDone();
}

int
HW_API::getSDI12GYasCodeFractional(bool fractional, SDI_12G::sdi_yas_code_type input_yascode, SDI_12G::sdi_yas_code_type* output_yascode){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getYasCodeFractional(fractional, input_yascode, output_yascode);
};

void
HW_API::getSDI12GPTPLock(bool* enable) {
    assert(sdi_12g.getInitDone());
    *enable = sdi_12g.getPTPLock();
    return;
}

void
HW_API::setSDI12GPTPLock(bool enable) {
    assert(sdi_12g.getInitDone());
    sdi_12g.setPTPLock(enable);
    return;
}

void
HW_API::setSDI12GPTPReferenceLockReset() {
    assert(sdi_12g.getInitDone());
    sdi_12g.setPTPReferenceLockReset();
    return;
}

void
HW_API::getSDI12GPTPReferenceLockLocked(bool* locked) {
    assert(sdi_12g.getInitDone());
    sdi_12g.getPTPReferenceLockLocked(locked);
    return;
}

void
HW_API::getSDI12GGenlockLock(bool* enable) {
    assert(sdi_12g.getInitDone());
    *enable = sdi_12g.getGenlockLock();
    return;
}

void
HW_API::setSDI12GGenlockLock(bool enable) {
    assert(sdi_12g.getInitDone());
    sdi_12g.setGenlockLock(enable);
    return;
}

void
HW_API::setSDI12GGenlockReferenceLockReset() {
    assert(sdi_12g.getInitDone());
    sdi_12g.setGenlockReferenceLockReset();
    return;
}

void
HW_API::getSDI12GGenlockReferenceLockLocked(bool* locked) {
    assert(sdi_12g.getInitDone());
    sdi_12g.getGenlockReferenceLockLocked(locked);
    return;
}

void
HW_API::dumpSDI12GReferenceLockStatus() {
  assert(sdi_12g.getInitDone());
  sdi_12g.dumpReferenceLockStatus();
  return;
}

int
HW_API::getSDI12G148M500HzClockFrequency(uint32_t* clockFrequency){
  assert(sdi_12g.getInitDone());
  return sdi_12g.get148M500HzClockFrequency(clockFrequency);
};

int
HW_API::getSDI12G148M350HzClockFrequency(uint32_t* clockFrequency){
  assert(sdi_12g.getInitDone());
  return sdi_12g.get148M350HzClockFrequency(clockFrequency);
};

int
HW_API::getSDI12GFractional(bool* fractional){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdi12GFractional(fractional);
};

int
HW_API::setSDI12GFractional(bool fractional, bool force){
  assert(sdi_12g.getInitDone());

  bool current_fractional;
  uint32_t defaultFrequency = 74250000;
  uint32_t targetFrequency;
  uint32_t programFrequency;
  uint32_t measuredFrequency;
  int32_t offsetFrequency;
  int32_t ppmAccuracyMax = 5000;
  int32_t ppmAccuracyMin = 50;
  int8_t loop_counter = 0;
  int32_t ret = 0;

  /* Check if a change is required. */
  if (!force)
  {
    ret += HW_API::getSDI12GFractional(&current_fractional);
    if (current_fractional == fractional)
    {
      return 0;
    }
  }

  /* Select the reference clock frequency required. */
  if (fractional)
  {
    targetFrequency = 148351648;
  } else {
    targetFrequency = 148500000;
  }
  programFrequency = targetFrequency;

  /* Set the clock as unstable. */
  ret += HW_API::setSDI12GDCXODone(0, false);
  for (uint32_t i = 0; i < HW_API::N_SDI_12G; i++)
  {
    /* Disable outputs */
    ret += HW_API::setSDI12GTxMuxSelect(i, HW_API::N_SDI_12G);
  }

  /* Initialize the DCXO. */
  ret += HW_API::initSDI12GDCXO(0, defaultFrequency);

  while (loop_counter < 5)
  {
    /* Program the DCXO. */
    ret += HW_API::setSDI12GDCXOClock(0, programFrequency);
    /* Wait 2s (2x the measurement period) for the frequency to be measured. */
    usleep(2000000);
    /* Read the frequency. */
    ret += HW_API::getSDI12G148M350HzClockFrequency(&measuredFrequency);
    /* Calculate the offset between programmed and measured frequency. */
    offsetFrequency = (int32_t)targetFrequency - (int32_t)measuredFrequency;
    if ((offsetFrequency >= 0 && offsetFrequency > ppmAccuracyMax) ||
        (offsetFrequency <  0 && offsetFrequency < (-1*ppmAccuracyMax)))
    {
      /* Something is wrong, re-initialize and try again. */
      ret += HW_API::initSDI12GDCXO(0, defaultFrequency);
      loop_counter++;
    } else if ((offsetFrequency >= 0 && offsetFrequency > ppmAccuracyMin) ||
               (offsetFrequency <  0 && offsetFrequency < (-1*ppmAccuracyMin)))
    {
      /* Clock is slightly off, try to centre it. */
      programFrequency = uint32_t(targetFrequency + offsetFrequency);
      loop_counter++;
    } else {
      break;
    }
  }
  /* Set the fractional mode. */
  ret += sdi_12g.setSdi12GFractional(fractional);
  /* Set the clock as stable. */
  ret += HW_API::setSDI12GDCXODone(0,true);

  return ret;
};

int
HW_API::initSDI12GDCXO(uint8_t index, uint32_t si570DefaultFrequency){
  assert(sdi_12g.getInitDone());
  return sdi_12g.initDCXO(index, si570DefaultFrequency);
};

int
HW_API::setSDI12GDCXOClock(uint8_t index, uint32_t frequency){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setDCXOClock(index, frequency);
};

int
HW_API::setSDI12GDCXOLockEnable(uint8_t index, bool value){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setDCXOLockEnable(index, value);
};

int
HW_API::getSDI12GDCXOLockEnable(uint8_t index, bool* value){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getDCXOLockEnable(index, value);
};

int
HW_API::setSDI12GDCXODone(uint8_t index, bool value){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setDCXODone(index, value);
};

int
HW_API::getSDI12GDCXODone(uint8_t index, bool* value){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getDCXODone(index, value);
};

int
HW_API::readSDI12GDCXOSettings(uint8_t index, bool* valid, si570_ctrl::si570_settings_type* settings) {
  assert(sdi_12g.getInitDone());
  return sdi_12g.readDCXOSettings(index, valid, settings);
};

int
HW_API::setSDI12GRxReset(uint32_t chan, bool reset){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiRxReset(chan, reset);
};

int
HW_API::setSDI12GTxReset(uint32_t chan, bool reset){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiTxReset(chan, reset);
};

int
HW_API::setSDI12GRxGTXReset(uint32_t chan, bool reset){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiRxGTXReset(chan, reset);
};

int
HW_API::setSDI12GTxGTXReset(uint32_t chan, bool reset){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiTxGTXReset(chan, reset);
};

int
HW_API::getSDI12GStatus(uint32_t chan, SDI_12G::sdi_status_type* SdiStatus){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiStatus(chan, SdiStatus);
};

int
HW_API::getSDI12GRxDetectDisable(uint32_t chan, bool* disable){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxDetectDisable(chan, disable);
};

int
HW_API::setSDI12GRxDetectDisable(uint32_t chan, bool disable){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiRxDetectDisable(chan, disable);
};

int
HW_API::getSDI12GRxForcedMode(uint32_t chan, uint8_t* mode){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxForcedMode(chan, mode);
};

int
HW_API::setSDI12GRxForcedMode(uint32_t chan, uint8_t mode){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiRxForcedMode(chan, mode);
};

int
HW_API::getSDI12GRxRaster(uint32_t chan, SDI_12G::sdi_rx_raster_type* SdiRxRaster){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxRaster(chan, SdiRxRaster);
};

int
HW_API::getSDI12GRxAudioInformation(uint32_t chan, SDI_12G::sdi_rx_audio_information_type* SdiRxAudioInformation){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxAudioInformation(chan, SdiRxAudioInformation);
};

int
HW_API::getSDI12GRxAudioGroupPresent(uint32_t chan, uint32_t group, bool* SdiRxAudioGroupPresent){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxAudioGroupPresent(chan, group, SdiRxAudioGroupPresent);
};

int
HW_API::getSDI12GRxAudioGroupError(uint32_t chan, uint32_t group, bool* SdiRxAudioGroupError){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxAudioGroupError(chan, group, SdiRxAudioGroupError);
};

int
HW_API::getSDI12GRxAudioGroupRate(uint32_t chan, uint32_t group, SDI_12G::sdi_rx_audio_rate* SdiRxAudioGroupRate){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxAudioGroupRate(chan, group, SdiRxAudioGroupRate);
};

int
HW_API::getSDI12GRxAudioChannelActive(uint32_t chan, uint32_t channel, bool* SdiRxAudioChannelActive){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxAudioChannelActive(chan, channel, SdiRxAudioChannelActive);
};

int
HW_API::getSDI12GRxRasterError(uint32_t chan, SDI_12G::sdi_rx_raster_error_type* SdiRxRasterError){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxRasterError(chan, SdiRxRasterError);
};

int
HW_API::getSDI12GRxVPIDY(uint32_t chan, uint32_t* SdiRxVPID){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxVPIDY(chan, SdiRxVPID);
};

int
HW_API::getSDI12GRxVPIDC(uint32_t chan, uint32_t* SdiRxVPID){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxVPIDC(chan, SdiRxVPID);
};

int
HW_API::setSDI12GRxCRCErrorClear(uint32_t chan){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiRxCRCErrorClear(chan);
};

int
HW_API::getSDI12GRxCRCErrorCount(uint32_t chan, uint32_t* SdiRxCRCErrorCount){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxCRCErrorCount(chan, SdiRxCRCErrorCount);
};

int
HW_API::getSDI12GTxYasCode(uint32_t chan, SDI_12G::sdi_yas_code_type* SdiTxYasCode){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiTxYasCode(chan, SdiTxYasCode);
};

int
HW_API::setSDI12GTxYasCode(uint32_t chan, SDI_12G::sdi_yas_code_type SdiTxYasCode){
  assert(sdi_12g.getInitDone());
  bool fractional;
  SDI_12G::sdi_yas_code_type temp;
  int32_t ret = 0;
  /* Get the current fractional mode and check if SdiTxYasCode is valid for this mode. */
  ret += HW_API::getSDI12GFractional(&fractional);
  ret += HW_API::getSDI12GYasCodeFractional(fractional, SdiTxYasCode, &temp);

  if (ret < 0)
  {
    /* No possible output standard / fractional pair. */
    return -5;
  } else if ((SdiTxYasCode.yas_clock_code  != temp.yas_clock_code) ||
             (SdiTxYasCode.yas_link_code   != temp.yas_link_code)  ||
             (SdiTxYasCode.yas_format_code != temp.yas_format_code))
  {
    /* Fractional pair possible. */
    return -6;
  }
  /* Standard is valid for this fractional mode. */
  return sdi_12g.setSdiTxYasCode(chan, SdiTxYasCode);
};

int
HW_API::setSDI12GTxMuxSelect(uint32_t chan, uint8_t SdiTxMuxSelect){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiTxMuxSelect(chan, SdiTxMuxSelect);
};

int
HW_API::setSDI12GTxAudioGroupEnable(uint32_t chan, uint32_t group, bool SdiTxAudioGroupEnable){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiTxAudioGroupEnable(chan, group, SdiTxAudioGroupEnable);
};

int
HW_API::setSDI12GTxAudioChannelEnable(uint32_t chan, uint32_t channel, bool SdiTxAudioChannelEnable){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiTxAudioChannelEnable(chan, channel, SdiTxAudioChannelEnable);
};

int
HW_API::getSDI12GTxVpidData(uint32_t chan, uint32_t* SdiTxVpidData){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiTxVpidData(chan, SdiTxVpidData);
};

int
HW_API::setSDI12GTxVpidData(uint32_t chan, uint32_t SdiTxVpidData){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiTxVpidData(chan, SdiTxVpidData);
};

int
HW_API::setSDI12GTxVpidInsertLine(uint32_t chan, uint16_t SdiTxVpidInsertLineField0, uint16_t SdiTxVpidInsertLineField1){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiTxVpidInsertLine(chan, SdiTxVpidInsertLineField0, SdiTxVpidInsertLineField1);
};

int
HW_API::getSDI12GTxStatus(uint32_t chan, SDI_12G::sdi_tx_status_type* SdiTxStatus){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiTxStatus(chan, SdiTxStatus);
};

int
HW_API::getSDI12GTx2SIEnable(uint32_t chan, bool* SdiTx2SIEnable){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiTx2SIEnable(chan, SdiTx2SIEnable);
};

int
HW_API::setSDI12GTx2SIEnable(uint32_t chan, bool SdiTx2SIEnable){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiTx2SIEnable(chan, SdiTx2SIEnable);
};

int
HW_API::getSDI12GTx2SIBypass(uint32_t chan, bool* SdiTx2SIBypass){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiTx2SIBypass(chan, SdiTx2SIBypass);
};

int
HW_API::setSDI12GTx2SIBypass(uint32_t chan, bool SdiTx2SIBypass){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiTx2SIBypass(chan, SdiTx2SIBypass);
};

int
HW_API::getSDI12GRx2SIEnable(uint32_t chan, bool* SdiRx2SIEnable){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRx2SIEnable(chan, SdiRx2SIEnable);
};

int
HW_API::getSDI12GRx2SIBypass(uint32_t chan, bool* SdiRx2SIBypass){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRx2SIBypass(chan, SdiRx2SIBypass);
};

int
HW_API::setSDI12GRx2SIBypass(uint32_t chan, bool SdiRx2SIBypass){
  assert(sdi_12g.getInitDone());
  return sdi_12g.setSdiRx2SIBypass(chan, SdiRx2SIBypass);
};

int
HW_API::getSDI12GRxActiveStreams(uint32_t chan, uint8_t* SdiRxActiveStreams){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getSdiRxActiveStreams(chan, SdiRxActiveStreams);
};

int
HW_API::getSDI12GRxUsrclockFrequency(uint32_t chan, uint32_t* clockFrequency){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getRxUsrclockFrequency(chan, clockFrequency);
};

int
HW_API::getSDI12GTxUsrclockFrequency(uint32_t chan, uint32_t* clockFrequency){
  assert(sdi_12g.getInitDone());
  return sdi_12g.getTxUsrclockFrequency(chan, clockFrequency);
};

/* -- Genlock -- */

ZYNQGenlock genlock;

void
HW_API::initGenlock() {
  if (HW_API::getFPGACapability("INC_GENLOCK") <= 0)
  {
    printf("INC_GENLOCK feature is required but not enabled!\n");
    return;
  }
  genlock.init();
  return;
}

bool
HW_API::getGenlockInitDone() {
  return genlock.getInitDone();
}

int
HW_API::setGenlockEnable(){
  assert(genlock.getInitDone());
  return genlock.setEnable();
};

int
HW_API::setGenlockDisable(){
  assert(genlock.getInitDone());
  genlock.setDisable();
  return 0;
};

int
HW_API::getGenlockStatus(bool* present, bool* locked, char* standard){
  assert(genlock.getInitDone());
  genlock.getStatus(present, locked, standard);
  return 0;
};

int
HW_API::setGenlockHPhase(uint32_t hphase){
  assert(genlock.getInitDone());
  genlock.setHPhase(hphase);
  return 0;
};

int
HW_API::setGenlockRefSourceDisable(){
  assert(genlock.getInitDone());
  genlock.setRefSourceDisable();
  return 0;
};

int
HW_API::setGenlockRefSource1(){
  assert(genlock.getInitDone());
  genlock.setRefSource1();
  return 0;
};

int
HW_API::setGenlockRefSource2(){
  assert(genlock.getInitDone());
  genlock.setRefSource2();
  return 0;
};

int
HW_API::setGenlockXOControl(bool enable){
  assert(genlock.getInitDone());
  genlock.setXOControl(enable);
  return 0;
};

int
HW_API::setGenlockXOSelect(bool xo){
  assert(genlock.getInitDone());
  genlock.setXOSelect(xo);
  return 0;
};

int
HW_API::getGenlockXOSelect(bool* xo){
  assert(genlock.getInitDone());
  genlock.getXOSelect(xo);
  return 0;
};

int
HW_API::getGenlockFreqError(uint32_t* freq_err){
  assert(genlock.getInitDone());
  *freq_err = genlock.getFreqError();
  return 0;
};

int
HW_API::getGenlockPhaseError(uint32_t* phase_err){
  assert(genlock.getInitDone());
  *phase_err = genlock.getPhaseError();
  return 0;
};

int
HW_API::getGenlockMaxLevel(uint32_t* max_level){
  assert(genlock.getInitDone());
  *max_level = genlock.getMaxLevel();
  return 0;
};

int
HW_API::getGenlockMinLevel(uint32_t* min_level){
  assert(genlock.getInitDone());
  *min_level = genlock.getMinLevel();
  return 0;
};

int
HW_API::getGenlockNominalFreqError(bool* nom_freq_err){
  assert(genlock.getInitDone());
  *nom_freq_err = genlock.getNominalFreqError();
  return 0;
};

int
HW_API::getGenlockMeasuredFreq(uint32_t* freq_measured){
  assert(genlock.getInitDone());
  *freq_measured = genlock.getMeasuredFreq();
  return 0;
};

// vim:set sts=2 sw=2 tw=0 expandtab fileformat=unix:
