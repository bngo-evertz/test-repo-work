#ifndef ADDR_MAP_H
#define ADDR_MAP_H
#include <stdint.h>

    // Zynq address space reserved for AXI interface 0
    static const uint32_t AXI_INTF0_BASE_ADDR = 0x43c00000;
    static const uint32_t AXI_INTF0_HIGH_ADDR = 0x6007ffff;

    //M00 -- DRPRQ
      // Total Boundary
    static const uint32_t DRPRQ_BASE_ADDR = 0x43c00000;
    static const uint32_t DRPRQ_HIGH_ADDR = 0x43c0ffff;
      // 10GE PHY 0 DRP
    static const uint32_t XGED0_BASE_ADDR = 0x43c00000;
    static const uint32_t XGED0_HIGH_ADDR = 0x43c007ff;
    static const uint32_t XGED0_BYTE_ADDR = 4;
      // 10GE PHY 1 DRP
    static const uint32_t XGED1_BASE_ADDR = 0x43c00800;
    static const uint32_t XGED1_HIGH_ADDR = 0x43c00fff;
    static const uint32_t XGED1_BYTE_ADDR = 4;
      // 10GE PHY 2 DRP
    static const uint32_t XGED2_BASE_ADDR = 0x43c01000;
    static const uint32_t XGED2_HIGH_ADDR = 0x43c017ff;
    static const uint32_t XGED2_BYTE_ADDR = 4;
      // 10GE PHY 3 DRP
    static const uint32_t XGED3_BASE_ADDR = 0x43c01800;
    static const uint32_t XGED3_HIGH_ADDR = 0x43c01fff;
    static const uint32_t XGED3_BYTE_ADDR = 4;
    //M01 -- DRP
    static const uint32_t DRPNL_BASE_ADDR = 0x43c10000;
    static const uint32_t DRPNL_HIGH_ADDR = 0x43c1ffff;
    static const uint32_t DRPNL_BYTE_ADDR = 4;
    //M02 -- HDMI Channel 1
    static const uint32_t HDMI0_BASE_ADDR = 0x43c20000;
    static const uint32_t HDMI0_HIGH_ADDR = 0x43c2ffff;
    static const uint32_t HDMI0_BYTE_ADDR = 1;
    //M03 -- HDMI Channel 2
    static const uint32_t HDMI1_BASE_ADDR = 0x43c30000;
    static const uint32_t HDMI1_HIGH_ADDR = 0x43c3ffff;
    static const uint32_t HDMI1_BYTE_ADDR = 1;
    //M04 -- SFP0 MAC layer
    static const uint32_t XGEM0_BASE_ADDR = 0x43c40000;
    static const uint32_t XGEM0_HIGH_ADDR = 0x43c4ffff;
    static const uint32_t XGEM0_BYTE_ADDR = 1;
    //M05 -- SFP1 MAC layer
    static const uint32_t XGEM1_BASE_ADDR = 0x43c50000;
    static const uint32_t XGEM1_HIGH_ADDR = 0x43c5ffff;
    static const uint32_t XGEM1_BYTE_ADDR = 1;
    //M06 -- SFP2 MAC layer
    static const uint32_t XGEM2_BASE_ADDR = 0x43c60000;
    static const uint32_t XGEM2_HIGH_ADDR = 0x43c6ffff;
    static const uint32_t XGEM2_BYTE_ADDR = 1;
    //M07 -- SFP3 MAC layer
    static const uint32_t XGEM3_BASE_ADDR = 0x43c70000;
    static const uint32_t XGEM3_HIGH_ADDR = 0x43c7ffff;
    static const uint32_t XGEM3_BYTE_ADDR = 1;
    //M08 -- FPGA ID
    static const uint32_t FPGAI_BASE_ADDR = 0x43c80000;
    static const uint32_t FPGAI_HIGH_ADDR = 0x43c80fff;
    static const uint32_t FPGAI_BYTE_ADDR = 4;
    //M09 -- IP interface layer
    static const uint32_t IP_IF_BASE_ADDR = 0x43c90000;
    static const uint32_t IP_IF_HIGH_ADDR = 0x43c9ffff;
    static const uint32_t IP_IF_BYTE_ADDR = 4;
    //M10 -- AV to IP
    static const uint32_t AV_IP_BASE_ADDR = 0x43ca0000;
    static const uint32_t AV_IP_HIGH_ADDR = 0x43caffff;
    static const uint32_t AV_IP_BYTE_ADDR = 8;
    //M11 -- IP to AV
    static const uint32_t IP_AV_BASE_ADDR = 0x43cb0000;
    static const uint32_t IP_AV_HIGH_ADDR = 0x43cbffff;
    static const uint32_t IP_AV_BYTE_ADDR = 8;
    //M12 -- XBAR CONFIG
    static const uint32_t XBARC_BASE_ADDR = 0x43cc0000;
    static const uint32_t XBARC_HIGH_ADDR = 0x43cc0fff;
    static const uint32_t XBARC_BYTE_ADDR = 4;
    //M13 -- Video Processing Wrapper (Scalers / Pip)
      // Total Boundary
    static const uint32_t VIDPR_BASE_ADDR = 0x43e00000;
    static const uint32_t VIDPR_HIGH_ADDR = 0x43efffff;
    static const uint32_t VIDPR_BYTE_ADDR = 4;
      //  -- Wrapper Layer Registers
      static const uint32_t VIDPC_BASE_ADDR = 0x43e00000;
      static const uint32_t VIDPC_HIGH_ADDR = 0x43e007ff;
      static const uint32_t VIDPC_BYTE_ADDR = 4;
      // Scaler / Frame Buffer Path 0
        // Total Boundary
      static const uint32_t SCFB0_BASE_ADDR = 0x43e08000;
      static const uint32_t SCFB0_HIGH_ADDR = 0x43e0ffff;
        // Scaler A
      static const uint32_t SCAS0_BASE_ADDR = 0x43e08000;
        // Scaler B
      static const uint32_t SCBS0_BASE_ADDR = 0x43e08800;
        // Raster Programming
      static const uint32_t SCRS0_BASE_ADDR = 0x43e09000;
        // Miscellaneous
      static const uint32_t SCMS0_BASE_ADDR = 0x43e09800;
        // Write Port 0
      static const uint32_t SCWA0_BASE_ADDR = 0x43e0a000;
        // Playout Programming
      static const uint32_t SCPL0_BASE_ADDR = 0x43e0a800;
        // Write Port 1
      static const uint32_t SCWB0_BASE_ADDR = 0x43e0b000;
        // Write Port 2
      static const uint32_t SCWC0_BASE_ADDR = 0x43e0b800;
        // Write Port 3
      static const uint32_t SCWD0_BASE_ADDR = 0x43e0c000;
      // Scaler / Frame Buffer Path 1
        // Total Boundary
      static const uint32_t SCFB1_BASE_ADDR = 0x43e10000;
      static const uint32_t SCFB1_HIGH_ADDR = 0x43e17fff;
        // Scaler A
      static const uint32_t SCAS1_BASE_ADDR = 0x43e10000;
        // Scaler B
      static const uint32_t SCBS1_BASE_ADDR = 0x43e10800;
        // Raster Programming
      static const uint32_t SCRS1_BASE_ADDR = 0x43e11000;
        // Miscellaneous
      static const uint32_t SCMS1_BASE_ADDR = 0x43e11800;
        // Write Port 0
      static const uint32_t SCWA1_BASE_ADDR = 0x43e12000;
        // Playout Programming
      static const uint32_t SCPL1_BASE_ADDR = 0x43e12800;
        // Write Port 1
      static const uint32_t SCWB1_BASE_ADDR = 0x43e13000;
        // Write Port 2
      static const uint32_t SCWC1_BASE_ADDR = 0x43e13800;
        // Write Port 3
      static const uint32_t SCWD1_BASE_ADDR = 0x43e14000;
      // Scaler / Frame Buffer Path 2
        // Total Boundary
      static const uint32_t SCFB2_BASE_ADDR = 0x43e18000;
      static const uint32_t SCFB2_HIGH_ADDR = 0x43e1ffff;
        // Scaler A
      static const uint32_t SCAS2_BASE_ADDR = 0x43e18000;
        // Scaler B
      static const uint32_t SCBS2_BASE_ADDR = 0x43e18800;
        // Raster Programming
      static const uint32_t SCRS2_BASE_ADDR = 0x43e19000;
        // Miscellaneous
      static const uint32_t SCMS2_BASE_ADDR = 0x43e19800;
        // Write Port 0
      static const uint32_t SCWA2_BASE_ADDR = 0x43e1a000;
        // Playout Programming
      static const uint32_t SCPL2_BASE_ADDR = 0x43e1a800;
        // Write Port 1
      static const uint32_t SCWB2_BASE_ADDR = 0x43e1b000;
        // Write Port 2
      static const uint32_t SCWC2_BASE_ADDR = 0x43e1b800;
        // Write Port 3
      static const uint32_t SCWD2_BASE_ADDR = 0x43e1c000;
      // Scaler / Frame Buffer Path 3
        // Total Boundary
      static const uint32_t SCFB3_BASE_ADDR = 0x43e20000;
      static const uint32_t SCFB3_HIGH_ADDR = 0x43e27fff;
        // Scaler A
      static const uint32_t SCAS3_BASE_ADDR = 0x43e20000;
        // Scaler B
      static const uint32_t SCBS3_BASE_ADDR = 0x43e20800;
        // Raster Programming
      static const uint32_t SCRS3_BASE_ADDR = 0x43e21000;
        // Miscellaneous
      static const uint32_t SCMS3_BASE_ADDR = 0x43e21800;
        // Write Port 0
      static const uint32_t SCWA3_BASE_ADDR = 0x43e22000;
        // Playout Programming
      static const uint32_t SCPL3_BASE_ADDR = 0x43e22800;
        // Write Port 1
      static const uint32_t SCWB3_BASE_ADDR = 0x43e23000;
        // Write Port 2
      static const uint32_t SCWC3_BASE_ADDR = 0x43e23800;
        // Write Port 3
      static const uint32_t SCWD3_BASE_ADDR = 0x43e24000;
      // Scaler / Frame Buffer Path 4
        // Total Boundary
      static const uint32_t SCFB4_BASE_ADDR = 0x43e28000;
      static const uint32_t SCFB4_HIGH_ADDR = 0x43e2ffff;
        // Scaler A
      static const uint32_t SCAS4_BASE_ADDR = 0x43e28000;
        // Scaler B
      static const uint32_t SCBS4_BASE_ADDR = 0x43e28800;
        // Raster Programming
      static const uint32_t SCRS4_BASE_ADDR = 0x43e29000;
        // Miscellaneous
      static const uint32_t SCMS4_BASE_ADDR = 0x43e29800;
        // Write Port 0
      static const uint32_t SCWA4_BASE_ADDR = 0x43e2a000;
        // Playout Programming
      static const uint32_t SCPL4_BASE_ADDR = 0x43e2a800;
        // Write Port 1
      static const uint32_t SCWB4_BASE_ADDR = 0x43e2b000;
        // Write Port 2
      static const uint32_t SCWC4_BASE_ADDR = 0x43e2b800;
        // Write Port 3
      static const uint32_t SCWD4_BASE_ADDR = 0x43e2c000;
      // Scaler / Frame Buffer Path 5
        // Total Boundary
      static const uint32_t SCFB5_BASE_ADDR = 0x43e30000;
      static const uint32_t SCFB5_HIGH_ADDR = 0x43e37fff;
        // Scaler A
      static const uint32_t SCAS5_BASE_ADDR = 0x43e30000;
        // Scaler B
      static const uint32_t SCBS5_BASE_ADDR = 0x43e30800;
        // Raster Programming
      static const uint32_t SCRS5_BASE_ADDR = 0x43e31000;
        // Miscellaneous
      static const uint32_t SCMS5_BASE_ADDR = 0x43e31800;
        // Write Port 0
      static const uint32_t SCWA5_BASE_ADDR = 0x43e32000;
        // Playout Programming
      static const uint32_t SCPL5_BASE_ADDR = 0x43e32800;
        // Write Port 1
      static const uint32_t SCWB5_BASE_ADDR = 0x43e33000;
        // Write Port 2
      static const uint32_t SCWC5_BASE_ADDR = 0x43e33800;
        // Write Port 3
      static const uint32_t SCWD5_BASE_ADDR = 0x43e34000;
      // Scaler / Frame Buffer Path 6
        // Total Boundary
      static const uint32_t SCFB6_BASE_ADDR = 0x43e38000;
      static const uint32_t SCFB6_HIGH_ADDR = 0x43e3ffff;
        // Scaler A
      static const uint32_t SCAS6_BASE_ADDR = 0x43e38000;
        // Scaler B
      static const uint32_t SCBS6_BASE_ADDR = 0x43e38800;
        // Raster Programming
      static const uint32_t SCRS6_BASE_ADDR = 0x43e39000;
        // Miscellaneous
      static const uint32_t SCMS6_BASE_ADDR = 0x43e39800;
        // Write Port 0
      static const uint32_t SCWA6_BASE_ADDR = 0x43e3a000;
        // Playout Programming
      static const uint32_t SCPL6_BASE_ADDR = 0x43e3a800;
        // Write Port 1
      static const uint32_t SCWB6_BASE_ADDR = 0x43e3b000;
        // Write Port 2
      static const uint32_t SCWC6_BASE_ADDR = 0x43e3b800;
        // Write Port 3
      static const uint32_t SCWD6_BASE_ADDR = 0x43e3c000;

    //M14 -- SDI-12G
    static const uint32_t SDI12G_BASE_ADDR = 0x43cd0000;
    static const uint32_t SDI12G_HIGH_ADDR = 0x43cd0fff;
    static const uint32_t SDI12G_BYTE_ADDR = 4;
    //M15 -- HDCP Crypto
    static const uint32_t HDCP_CRYPTO_BASE_ADDR = 0x43ce0000;
    static const uint32_t HDCP_CRYPTO_HIGH_ADDR = 0x43ce0fff;
    static const uint32_t HDCP_CRYPTO_BYTE_ADDR = 4;
    //M16 -- Axi Memory DMA 0
    static const uint32_t AXIDMA0_MEM_BASE_ADDR = 0x43cf0000;
    static const uint32_t AXIDMA0_MEM_HIGH_ADDR = 0x43cf0fff;
    static const uint32_t AXIDMA0_MEM_BYTE_ADDR = 4;
    //M17 -- Memtest HP
    static const uint32_t MTEST0_BASE_ADDR = 0x43d10000;
    static const uint32_t MTEST0_HIGH_ADDR = 0x43d10fff;
    static const uint32_t MTEST0_BYTE_ADDR = 4;
    //M18 -- Memtest HR
    static const uint32_t MTEST1_BASE_ADDR = 0x43d20000;
    static const uint32_t MTEST1_HIGH_ADDR = 0x43d20fff;
    static const uint32_t MTEST1_BYTE_ADDR = 4;
    //M19 -- Icron USB
    static const uint32_t USB_BASE_ADDR = 0x43d30000;
    static const uint32_t USB_HIGH_ADDR = 0x43d30fff;
    static const uint32_t USB_BYTE_ADDR = 4;
    //M20 -- Axi Memory DMA 1
    static const uint32_t AXIDMA1_MEM_BASE_ADDR = 0x43d40000;
    static const uint32_t AXIDMA1_MEM_HIGH_ADDR = 0x43d40fff;
    static const uint32_t AXIDMA1_MEM_BYTE_ADDR = 4;
    //M21 -- Audio Mixer 0
    static const uint32_t AMIXER0_BASE_ADDR = 0x43d50000;
    static const uint32_t AMIXER0_HIGH_ADDR = 0x43d50fff;
    static const uint32_t AMIXER0_BYTE_ADDR = 4;
    //M22 -- Audio Mixer 1
    static const uint32_t AMIXER1_BASE_ADDR = 0x43d60000;
    static const uint32_t AMIXER1_HIGH_ADDR = 0x43d60fff;
    static const uint32_t AMIXER1_BYTE_ADDR = 4;
    //M23 -- General Registers
    static const uint32_t GENREG_BASE_ADDR = 0x43d70000;
    static const uint32_t GENREG_HIGH_ADDR = 0x43d70fff;
    static const uint32_t GENREG_BYTE_ADDR = 4;
    //M24 -- PTP
    static const uint32_t PTP_BASE_ADDR = 0x43d80000;
    static const uint32_t PTP_HIGH_ADDR = 0x43d80fff;
    static const uint32_t PTP_BYTE_ADDR = 4;
    //M25 -- InterFPGA
    static const uint32_t INTER_BASE_ADDR = 0x43d90000;
    static const uint32_t INTER_HIGH_ADDR = 0x43d90fff;
    static const uint32_t INTER_BYTE_ADDR = 4;
    //M26 -- InterFPGA
    static const uint32_t INTER_IP_BASE_ADDR = 0x43da0000;
    static const uint32_t INTER_IP_HIGH_ADDR = 0x43da0fff;
    static const uint32_t INTER_IP_BYTE_ADDR = 4;
    //M27 -- ip_rx
    static const uint32_t IPRX_BASE_ADDR = 0x43db0000;
    static const uint32_t IPRX_HIGH_ADDR = 0x43db0fff;
    static const uint32_t IPRX_BYTE_ADDR = 4;
    //M28 -- ip_tx
    static const uint32_t IPTX_BASE_ADDR = 0x43dc0000;
    static const uint32_t IPTX_HIGH_ADDR = 0x43dc0fff;
    static const uint32_t IPTX_BYTE_ADDR = 4;
    //M29 -- Genlock
    static const uint32_t GENLOCK_BASE_ADDR = 0x43dd0000;
    static const uint32_t GENLOCK_HIGH_ADDR = 0x43dd0fff;
    static const uint32_t GENLOCK_BYTE_ADDR = 4;
    //M30 -- AXI DMA IP 0
    static const uint32_t AXIDMA0_IP_BASE_ADDR = 0x43de0000;
    static const uint32_t AXIDMA0_IP_HIGH_ADDR = 0x43de0fff;
    static const uint32_t AXIDMA0_IP_BYTE_ADDR = 4;
    //M31 -- AXI DMA IP 1
    static const uint32_t AXIDMA1_IP_BASE_ADDR = 0x43df0000;
    static const uint32_t AXIDMA1_IP_HIGH_ADDR = 0x43df0fff;
    static const uint32_t AXIDMA1_IP_BYTE_ADDR = 4;
#endif // ADDR_MAP_H
// vim:set sts=2 sw=2 expandtab fileformat=unix:
