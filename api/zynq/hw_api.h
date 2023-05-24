#ifndef HW_API_H
#define HW_API_H
#include <stdint.h>
#include "addr_map.h"
#include "hw_mmap_rw.h"
#include "zynq_hdmi.h"
#include "zynq_icron_usb.h"
#include "zynq_genreg.h"
#include "raster_parameters.h"
#include "zynq_locker.h"
#include "zynq_fpga_id.h"
#include "zynq_x7_xge_mac.h"
#include "zynq_x7_temac.h"
#include "zynq_axi_10g_intf.h"
#include "zynq_av_to_ip.h"
#include "zynq_ip_tx.h"
#include "zynq_ip_to_av.h"
#include "zynq_ip_rx.h"
#include "zynq_xbar_config.h"
#include "zynq_mem_test_wrapper.h"
#include "zynq_vid_scale.h"
#include "zynq_updown_scale_wport.h"
#include "zynq_updown_scale_dec_wport.h"
#include "zynq_playout_ctrl.h"
#include "zynq_raster_gen_prog.h"
#include "zynq_raster_gen_prog_vmix.h"
#include "zynq_video_processing_wrapper.h"
#include "zynq_updown_scale_wrapper.h"
#include "updown_scale_pre_and_post.h"
#include "updown_scale_dual_post.h"
#include "updown_scale_quad_dual_post.h"
#include "updown_scale_single_post.h"
#include "updown_scale_single_pre.h"
#include "zynq_x7drp_gtxch.h"
#include "zynq_axi_dma_memory.h"
#include "zynq_audio_mixer.h"
#include "zynq_interfpga.h"
#include "zynq_sdi_12g.h"
#include "zynq_genlock.h"
#include "bitmap_convert.h"

namespace HW_API {

    // Low level Interface functions
    // Addresses passed to these should be the addresses seen in the
    // data sheet / register pack.  Any base address / word length
    // conversion is handled by these functions
    // For 64 bit interfaces, locking the interface between the msb and lsb
    // is handled internally by these functions

    uint32_t readXGEDRPReg(uint32_t channel, uint32_t reg);
    void writeXGEDRPReg(uint32_t channel, uint32_t reg, uint32_t data);
    uint32_t readDRPNLReg(uint32_t reg);
    void writeDRPNLReg(uint32_t reg, uint32_t data);
    uint32_t readHDMIIPReg(uint32_t channel, uint32_t reg);
    void writeHDMIIPReg(uint32_t channel, uint32_t reg, uint32_t data);
    uint32_t readXGEMacReg(uint32_t channel, uint32_t reg);
    void writeXGEMacReg(uint32_t channel, uint32_t reg, uint32_t data);
    uint32_t readTEMACReg(uint32_t channel, uint32_t reg);
    void writeTEMACReg(uint32_t channel, uint32_t reg, uint32_t data);
    uint32_t readXGEIfReg(uint32_t reg);
    void writeXGEIfReg(uint32_t reg, uint32_t data);
    uint64_t readXGETxReg(uint32_t reg);
    void writeXGETxReg(uint32_t reg, uint64_t data);
    uint64_t readXGERxReg(uint32_t reg);
    void writeXGERxReg(uint32_t reg, uint64_t data);
    uint32_t readFPGAIDReg(uint32_t reg);
    void writeFPGAIDReg(uint32_t reg, uint32_t data);
    uint32_t readXBARCONFIGReg(uint32_t reg);
    void writeXBARCONFIGReg(uint32_t reg, uint32_t data);
    uint32_t readVidProcReg(uint32_t reg);
    void writeVidProcReg(uint32_t reg, uint32_t data);
    uint32_t readScalerReg(uint32_t channel, uint32_t component, uint32_t register_address);
    void writeScalerReg(uint32_t channel, uint32_t component, uint32_t register_address, uint32_t data);
    uint32_t readScalerAReg(uint32_t channel, uint32_t reg);
    void writeScalerAReg(uint32_t channel, uint32_t reg, uint32_t data);
    uint32_t readScalerBReg(uint32_t channel, uint32_t reg);
    void writeScalerBReg(uint32_t channel, uint32_t reg, uint32_t data);
    uint32_t readScaleRasterReg(uint32_t channel, uint32_t reg);
    void writeScaleRasterReg(uint32_t channel, uint32_t reg, uint32_t data);
    uint32_t readScaleMiscReg(uint32_t channel, uint32_t reg);
    void writeScaleMiscReg(uint32_t channel, uint32_t reg, uint32_t data);
    uint32_t readScalerWritePortReg(uint32_t channel, uint32_t reg);
    uint32_t readScalerWritePortReg(uint32_t channel, uint32_t tile, uint32_t reg);
    void writeScalerWritePortReg(uint32_t channel, uint32_t reg, uint32_t data);
    void writeScalerWritePortReg(uint32_t channel, uint32_t tile, uint32_t reg, uint32_t data);
    uint32_t readScalerDecWritePortReg(uint32_t channel, uint32_t reg);
    uint32_t readScalerDecWritePortReg(uint32_t channel, uint32_t tile, uint32_t reg);
    void writeScalerDecWritePortReg(uint32_t channel, uint32_t reg, uint32_t data);
    void writeScalerDecWritePortReg(uint32_t channel, uint32_t tile, uint32_t reg, uint32_t data);
    uint32_t readScalerPlayoutReg(uint32_t channel, uint32_t reg);
    void writeScalerPlayoutReg(uint32_t channel, uint32_t reg, uint32_t data);
    uint32_t readMemTestReg(uint32_t idx, uint32_t reg);
    void writeMemTestReg(uint32_t idx, uint32_t reg, uint32_t data);
    uint32_t readIcronUSBReg(uint32_t reg);
    void writeIcronUSBReg(uint32_t reg, uint32_t data);
    uint64_t readTICOENCReg(uint32_t reg);
    void writeTICOENCReg(uint32_t reg, uint64_t data);
    uint64_t readTICODECReg(uint32_t reg);
    void writeTICODECReg(uint32_t reg, uint64_t data);
    uint32_t readAudioMixerReg(uint32_t idx, uint32_t reg);
    void writeAudioMixerReg(uint32_t idx, uint32_t reg, uint32_t data);
    uint32_t readPTPReg(uint32_t reg);
    void writePTPReg(uint32_t reg, uint32_t data);
    uint32_t readGeneralReg(uint32_t reg);
    void writeGeneralReg(uint32_t reg, uint32_t data);
    uint32_t readInterfpgaReg(uint8_t idx, uint32_t reg);
    void writeInterfpgaReg(uint8_t idx, uint32_t reg, uint32_t data);
    uint32_t readIPRxReg(uint32_t reg);
    void writeIPRxReg(uint32_t reg, uint32_t data);
    uint32_t readIPTxReg(uint32_t reg);
    void writeIPTxReg(uint32_t reg, uint32_t data);
    uint32_t readAxiDmaIpReg(uint32_t index, uint32_t reg);
    void writeAxiDmaIpReg(uint32_t index, uint32_t reg, uint32_t data);
    uint32_t readAxiDmaMemReg(uint32_t index, uint32_t reg);
    void writeAxiDmaMemReg(uint32_t index, uint32_t reg, uint32_t data);
    uint32_t readSDI12GReg(uint32_t reg);
    void writeSDI12GReg(uint32_t reg, uint32_t data);
    uint32_t readGenlockReg(uint32_t reg);
    void writeGenlockReg(uint32_t reg, uint32_t data);

    // Genlock
    void initGenlock();
    bool getGenlockInitDone();
    int  setGenlockEnable();
    int  setGenlockDisable();
    int  getGenlockStatus(bool* present, bool* locked, char* standard);
    int  setGenlockHPhase(uint32_t hphase);
    int  setGenlockRefSourceDisable();
    int  setGenlockRefSource1();
    int  setGenlockRefSource2();
    int  setGenlockXOControl(bool enable);
    int  setGenlockXOSelect(bool xo);
    int  getGenlockXOSelect(bool* xo);
    int  getGenlockFreqError(uint32_t* freq_err);
    int  getGenlockPhaseError(uint32_t* phase_err);
    int  getGenlockMaxLevel(uint32_t* max_level);
    int  getGenlockMinLevel(uint32_t* min_level);
    int  getGenlockNominalFreqError(bool* nom_freq_err);
    int  getGenlockMeasuredFreq(uint32_t* freq_measured);

    // Low level mutexes
    // These will be used by other functions within the api
    // Manual use should be done with caution (make sure anything locked gets unlocked)

    // For 64-bit interfaces, these should be used to lock reads/writes to
    // a word.  (The low level interface functions above use these)
    int lockXGERxReadWord(bool lock);
    int lockXGETxReadWord(bool lock);
    int lockXGERxWriteWord(bool lock);
    int lockXGETxWriteWord(bool lock);

    // These should be used to lock interfaces for multiple reads/writes which
    // need to be atomic
    int lockXGEDRPChReg(uint32_t idx, bool lock);
    int lockXGEDRPCoReg(bool lock);
    int lockHDMIReg(uint32_t idx, bool lock);
    int lockXGEMReg(uint32_t idx, bool lock);
    int lockXGEIfReg(bool lock);
    int lockXGETxReg(bool lock);
    int lockXGERxReg(bool lock);
    int lockFPGAIDReg(bool lock);
    int lockXBARReg(bool lock);
    int lockScalerAReg(uint32_t idx, bool lock);
    int lockScalerBReg(uint32_t idx, bool lock);
    int lockScaleRasterReg(uint32_t idx, bool lock);
    int lockScaleMiscReg(uint32_t idx, bool lock);
    int lockScalerWritePortReg(uint32_t idx, bool lock);
    int lockScalerDecWritePortReg(uint32_t idx, bool lock);
    int lockScalerPlayoutReg(uint32_t idx, bool lock);
    int lockAxiMemoryDmaReg(bool lock);
    int lockMemTestReg(uint32_t idx, bool lock);
    int lockIcronUSBReg(bool lock);
    int lockTicoEncReg(bool lock);
    int lockTicoDecReg(bool lock);
    int lockPTPReg(bool lock);
    int lockIPRxReg(bool lock);
    int lockIPTxReg(bool lock);
    int lockSDI12GReg(bool lock);
    int lockGenlockReg(bool lock);

    // Sleep
    void hwSleep(uint64_t ns);

    // API/FPGA BIST
    void bistSleep();
    void bistMutex();
    void bistReg();
      // Amount of memory tested is (2**SDRAM_N_A_BITS)/(2**depth_div_exp)
    void bistMem(uint32_t bank, uint32_t depth_div_exp, bool quick);
    void bistMemAddrStress(uint32_t bank, uint32_t iterations, bool quick);
    void bistMemAddressHammer(uint32_t bank, uint32_t iterations);
    void bist10GEMac();
    void bist10GEMacLinkUp();
    void bistTEMAC();
    typedef enum e_XTxColourSpecification {
        C_UNSPECIFIED=0,
        C_SRGB,
        C_REC601,
        C_REC709,
        C_T800, // JPEG2000
        C_XYZ,  // D-Cinema Master
        C_REC2020,
        C_ST2084,
        NUM_COLOUR_SPECIFICATIONS
    } XTxColourSpecification;
    typedef enum e_XTxSampleStructure {
        S_422=0,
        S_444,
        S_4444,
        S_RESERVED,
        S_INIT,
        NUM_SAMPLE_STRUCTURES
    } XTxSampleStructure;
    typedef enum e_XTxElectroopticalTransferFunction {
        E_DEFAULT=0,
        E_SMPTE2084PQ,
        E_HLG,
        E_RESERVED,
        NUM_EOTF
    } XTxElectroopticalTransferFunction;
    typedef enum e_XTxColourSpace {
        X_DEFAULT=0,
        X_REC601,
        X_REC709,
        X_REC2020,
        NUM_COLOURSPACE
    } XTxColourSpace;
    void bist10GETx(uint32_t sfp_a, uint32_t sfp_b, bool srtp, uint32_t vstd=0, bool aspen422=true, bool aspen444=false, bool tico=true, bool smpte2110=false, bool audio=true, HW_API::XTxColourSpecification colour_spec_inp=HW_API::C_SRGB, HW_API::XTxSampleStructure smp_struct_inp=HW_API::S_444, bool meta=false, HW_API::XTxElectroopticalTransferFunction eotf=HW_API::E_DEFAULT, HW_API::XTxColourSpace colour_space=HW_API::X_REC709, bool usb=false);
    void bist10GERx(uint32_t sfp_a, uint32_t sfp_b, bool redundancy, bool srtp);
    void bist10GEUSB(uint32_t sfp_a, uint32_t sfp_b, bool redundancy, bool srtp);
    void bist10GEPCR(uint32_t sfp_a, uint32_t sfp_b, bool redundancy, bool srtp, bool remote=true);
    typedef enum e_bw_BIST {
      BW_1920_1080P60=0,
      BW_1920_1080I60,
      BW_3840_2160P30,
      BW_3840_2160P60,
      BW_1920_1080P30,
      BW_3840_2160P24,
      BW_3840_2160P23_98,
      BW_3840_2160P59_94,
      BW_3840_2160P29_98,
      BW_1920_1080P59_94,
      BW_1920_1200P60,
      BW_640_480P60,
      BW_1920_1080P24,
      BW_1280_720P60,
      NUM_BIST_BW
    } bwBIST;
    void bistScaler(uint32_t path, bwBIST in, bwBIST out);
    typedef enum e_scColourFormat_type{
      CSF_RGB = 0,
      CSF_YCRCB_444,
      CSF_YCRCB_422,
      CSF_YCRCB_420,
      CSF_YONLY,
      CSF_RGBA,
      CSF_YCRCBA_444,
      CSF_NUM_SUPPORTED,
      CSF_UNKNOWN
    } scColourFormat_type;
    void bistScaler(uint32_t path, bwBIST in, scColourFormat_type colour_inp, bwBIST out, scColourFormat_type colour_out);
    void bistGearboxRx(bwBIST bw, scColourFormat_type colour);
    void bistCapability();
    void bistHdmiTx(uint32_t txchan, HW_API::bwBIST bw_out, bool fractional=0, HW_API::scColourFormat_type colour=HW_API::CSF_RGB, uint32_t bits_per_component=8);
    void bistHdmiLoopback(uint32_t rxchan, uint32_t txchan, bwBIST bw);
    void bistHdmiLink(uint32_t rxchan, uint32_t txchan, bwBIST bw, uint32_t path, uint8_t* edid, bool fast);
    bool bistHdmiRxLinkError(uint32_t rxchan, bool fast);

    // AXI DMA Memory Interface
    void      initAxiDmaMemory();
    bool      getInitAxiDmaMemoryDone(uint32_t index);
    uint32_t  setAxiDmaMemoryDmaReadToDdrWrite(uint32_t index, uint32_t rd_src_addr, uint32_t wr_dst_addr, uint32_t wr_burst_size_in_bytes, uint32_t bytes_to_transfer);
      // Helper Functions
    uint32_t* convertMemoryFrame(uint32_t scaler_path, uint32_t height, uint32_t width, unsigned char* buffer_24, uint32_t* buf_size_p);
    uint32_t* writeAxiDmaMemoryConvertBmpFormat(uint32_t scaler_path, const char *bmp_file_input, const char *frame_file_output);
    uint32_t  getScalerFrameBufferPageAddress(uint32_t scaler_path, uint8_t page, uint8_t* ddr_bank, uint32_t* address);
    uint32_t  getScalerLossOfInputImageAddress(uint32_t scaler_path, uint8_t* ddr_bank, uint32_t* address);
    uint32_t  setScalerLossOfInputImage(uint32_t scaler_path, uint32_t ps_ddr_addr, uint32_t image_bytes);
    uint32_t  setScalerLossOfInputImageEnable(uint32_t scaler_path, bool enable);

    // FPGA Build ID
    // Init
    void initFPGABuildID();
    bool getFPGABuildIDInitDone();
      // Dump Build ID Information
    void dumpFPGABuildID();
    // Get FPGA Capability from FPGABuildID based on a string.
    int getFPGACapability(const char* parameter);
    bool getScalerArchMatch(const char* arch, uint32_t arch_type = 0);

    // XBAR
      // Get Audio XBAR Config
    int32_t getAudioXbarSel(uint32_t index);
      // Set Audio XBAR Config
    void setAudioXbarSel(uint32_t index, uint32_t sel);
      // Get Video XBAR Config
    int32_t getVideoXbarSel(uint32_t index);
      // Set Video XBAR Config
    void setVideoXbarSel(uint32_t index, uint32_t sel);
      // Get Metadata XBAR Config
    int32_t getMetaXbarSel(uint32_t index);
      // Set Metadata XBAR Config
    void setMetaXbarSel(uint32_t index, uint32_t sel);

    // Audio Presence
      // Initialization
    bool initAudPres();
      // Status read back
    int32_t getAudInStatus( uint32_t index, XBARCONFIG::audio_status_type* audio_status);
    int32_t getAudOutStatus(uint32_t index, XBARCONFIG::audio_status_type* audio_status);
      // Audio Gain
    void setAudInGain( uint32_t index, double gain);
    void setAudOutGain(uint32_t index, double gain);

    typedef enum e_TicoSubSampling_Mode {
        TICO_YCC422=0,
        TICO_YCC444,
        TICO_RGB,
        NUM_TICO_SUBSAMPLING_MODE
    } TicoSubSampling_Mode;
      // Tico Encoder
    void configTicoEnc(uint32_t index, uint32_t width, uint32_t height, uint64_t bitrate, uint32_t refresh_rate_num, uint32_t refresh_rate_den, uint32_t bit_depth=10, uint32_t lvl_weights=0, HW_API::TicoSubSampling_Mode subsample=HW_API::TICO_RGB, bool s2110=0, bool interlaced=0, bool legacy_cs=1);
    TICOtoIP::enc_status getTicoEncStatus(uint32_t index);
    void restartTicoEnc(uint32_t index);
    void enableTicoEnc(uint32_t index);
    void disableTicoEnc(uint32_t index);
      // Tico Decoder
    void configTicoDec(uint32_t index, uint32_t width, uint32_t height, uint32_t refresh_rate_num, uint32_t refresh_rate_den, uint32_t downscale=0);
    IPtoTICO::dec_status getTicoDecStatus(uint32_t index);
    void restartTicoDec(uint32_t index);

    typedef enum e_zynqAudioIn
    {
        AUD_IN_NULL=0,
        AUD_IN_I2S,
        AUD_IN_XGE0,
        AUD_IN_XGE1,
        AUD_IN_XGE2,
        AUD_IN_XGE3,
        AUD_IN_HDMI0,
        AUD_IN_HDMI1,
        AUD_IN_SRC0,
        AUD_IN_SRC1,
        AUD_IN_AMIXER0,   //10
        AUD_IN_AMIXER1,
        AUD_IN_INTER0,
        AUD_IN_INTER1,
        AUD_IN_INTER2,
        AUD_IN_INTER3,
        AUD_IN_SDI1,
        AUD_IN_SDI2,
        N_AUD_IN
    } zynqAudioIn;
    typedef enum e_zynqAudioOut
    {
        AUD_OUT_I2S0=0,
        AUD_OUT_XGE0,
        AUD_OUT_XGE1,
        AUD_OUT_XGE2,
        AUD_OUT_HDMI0,
        AUD_OUT_HDMI1,
        AUD_OUT_SRC0,
        AUD_OUT_SRC1,
        AUD_OUT_SPDIF0,
        AUD_OUT_SPDIF1,
        AUD_OUT_AMIXER0,   //10
        AUD_OUT_AMIXER1,
        AUD_OUT_AMIXER2,
        AUD_OUT_AMIXER3,
        AUD_OUT_AMIXER4,
        AUD_OUT_AMIXER5,
        AUD_OUT_AMIXER6,
        AUD_OUT_AMIXER7,
        AUD_OUT_INTER0,
        AUD_OUT_INTER1,
        AUD_OUT_INTER2,    //20
        AUD_OUT_INTER3,
        AUD_OUT_SDI1,
        AUD_OUT_SDI2,
        N_AUD_OUT
    } zynqAudioOut;

    typedef enum e_zynqVideoIn
    {
        VID_IN_NULL=0,
        VID_IN_HDMI0,
        VID_IN_HDMI1,
        VID_IN_XGE0,  // ASPEN/TICO
        VID_IN_XGE1,  // ASPEN/TICO
        VID_IN_XGE2,  // ASPEN/TICO
        VID_IN_XGE3,  // ASPEN/TICO
        VID_IN_XGE4,  // SMPTE 2110-20
        VID_IN_XGE5,  // SMPTE 2110-20
        VID_IN_INTER0,
        VID_IN_INTER1,  //10
        VID_IN_SCALER0,
        VID_IN_SCALER1,
        VID_IN_SCALER2,
        VID_IN_SCALER3,
        VID_IN_SDI1,
        VID_IN_SDI2,
        N_VID_IN
    } zynqVideoIn;
    typedef enum e_zynqVideoOut
    {
        VID_OUT_XGE0=0, // ASPEN
        VID_OUT_XGE1,   // ASPEN
        VID_OUT_XGE2,   // TICO
        VID_OUT_XGE3,   // TICO
        VID_OUT_XGE4,   // SMPTE 2110-20
        VID_OUT_XGE5,   // SMPTE 2110-20
        VID_OUT_INTER0,
        VID_OUT_INTER1,
        VID_OUT_SCALER0,
        VID_OUT_SCALER1,
        VID_OUT_SCALER2,  //10
        VID_OUT_SCALER3,
        VID_OUT_SCALER4,
        VID_OUT_SCALER5,
        VID_OUT_SCALER6,
        VID_OUT_SDI1,
        VID_OUT_SDI2,
        N_VID_OUT
    } zynqVideoOut;

    typedef enum e_zynqMetaIn
    {
        META_IN_NULL=0,
        META_IN_HDMI0,
        META_IN_HDMI1,
        META_IN_XGE0,
        META_IN_XGE1,
        META_IN_XGE2,
        META_IN_XGE3,
        META_IN_SCALER0,
        META_IN_SCALER1,
        META_IN_SCALER2,
        META_IN_SCALER3,
        META_IN_INTER0,
        META_IN_INTER1,
        N_META_IN
    } zynqMetaIn;
    typedef enum e_zynqMetaOut
    {
        META_OUT_SCALER0=0,
        META_OUT_SCALER1,
        META_OUT_SCALER2,
        META_OUT_SCALER3,
        META_OUT_XGE0,
        META_OUT_XGE1,
        META_OUT_INTER0,
        META_OUT_INTER1,
        N_META_OUT
    } zynqMetaOut;

    // Memory Test
    typedef enum e_MemTestType {
        MEM_TEST_TYPE_RANDOM=0,
        MEM_TEST_TYPE_BIT_WALK,
        MEM_TEST_TYPE_ADDR_EQ_DATA,
        MEM_TEST_TYPE_RANDOM_ONCE,
        MEM_TEST_TYPE_BIT_WALK_ONCE,
        MEM_TEST_TYPE_ADDR_STRESS,
        MEM_TEST_TYPE_ADDR_STRESS_ONCE,
        MEM_TEST_TYPE_ADDR_HAMMER,
        NUM_TEST_TYPES
    } MemTestType;
    // Init -- CALL THIS FIRST!
    void initMemoryTest(uint32_t bank);
    bool getMemoryTestInitDone(uint32_t bank);
    void dumpMemoryTestConfig(uint32_t bank);
    bool getMemoryTestReady(uint32_t bank);
    // Amount of memory tested is (2**SDRAM_N_A_BITS)/(2**depth_div_exp)
    // Returns true if passes
    bool runMemoryTest(uint32_t bank, uint32_t depth_div_exp, HW_API::MemTestType type);
    bool runMemoryAddressStressTest(uint32_t bank, uint32_t iterations, HW_API::MemTestType type);
    bool runMemoryAddressHammer(uint32_t bank, uint32_t iterations, HW_API::MemTestType type);
    bool getMemoryCalibrated(uint32_t bank);

    // 10GE Mac
    // Init -- CALL THIS FIRST!
    void init10GEMac(uint32_t channel);
    // Debug only
    bool get10GEMacInitDone(uint32_t channel);
    // MAC Statistics
    void dump10GEMacStatNames();
    uint64_t get10GEMacStatistic(uint32_t channel, uint32_t stat_index);
    // MAC Control
    void reset10GEMacRx(uint32_t channel);
    void reset10GEMacTx(uint32_t channel);
    bool get10GEMacRxEnable(uint32_t channel);
    void set10GEMacRxEnable(uint32_t channel, bool enable);
    bool get10GEMacTxEnable(uint32_t channel);
    void set10GEMacTxEnable(uint32_t channel, bool enable);
    bool get10GEMacFaultInhibit(uint32_t channel);
    void set10GEMacFaultInhibit(uint32_t channel, bool enable);
    // Low level MDIO Control
    bool get10GEMacMDIOEnable(uint32_t channel);
    void set10GEMacMDIOEnable(uint32_t channel, bool enable);
    void write10GEMacMDIO(uint32_t channel, uint32_t dev_addr, uint32_t reg_addr, uint16_t data);
    uint16_t read10GEMacMDIO(uint32_t channel, uint32_t dev_addr, uint32_t reg_addr);
    void read10GEMacMDIOInc(uint32_t channel, uint32_t dev_addr, uint32_t reg_addr, uint32_t count, uint16_t * data);
    // PHY Control
    bool get10GERxSignalDetect(uint32_t channel);
    bool get10GELinkUp(uint32_t channel);
    bool get10GELocalFault(uint32_t channel);
    bool get10GETransmitFault(uint32_t channel);
    bool get10GEReceiveFault(uint32_t channel);

    // 1G Mac
    // Init -- CALL THIS FIRST!
    void initTEMAC(uint32_t channel);
    // Debug only
    bool getTEMACInitDone(uint32_t channel);
    // MAC Statistics
    void dumpTEMACStatNames();
    uint64_t getTEMACStatistic(uint32_t channel, uint32_t stat_index);
    // MAC Control
    void resetTEMACRx(uint32_t channel);
    void resetTEMACTx(uint32_t channel);
    bool getTEMACRxEnable(uint32_t channel);
    void setTEMACRxEnable(uint32_t channel, bool enable);
    bool getTEMACTxEnable(uint32_t channel);
    void setTEMACTxEnable(uint32_t channel, bool enable);
    // Low level MDIO Control
    bool getTEMACMDIOEnable(uint32_t channel);
    void setTEMACMDIOEnable(uint32_t channel, bool enable);
    void writeTEMACMDIO(uint32_t channel, uint32_t reg_addr, uint16_t data);
    uint16_t readTEMACMDIO(uint32_t channel, uint32_t reg_addr);
    // PHY Control
    void set1GPHYisolate(uint32_t channel, bool isolate);
    void set1GUnidirectionalEnable(uint32_t channel, bool enable);
    void setEnableAutonegotiation(uint32_t channel, bool enable);
    void set1GSgmii(uint32_t channel, bool sgmii);
    bool get1GSgmii(uint32_t channel);
    bool get1GLinkUp(uint32_t channel);
    bool get1GRemoteFault(uint32_t channel);

    // 10GE Transceiver
    // Init -- CALL THIS FIRST!
    void init10GEXcvr(uint32_t channel);
    bool get10GEXcvrInitDone(uint32_t channel);
    uint32_t get10GEXcvrRxDataWidth(uint32_t channel);
    bool get10GEXcvrRxIntDataWidth(uint32_t channel);
    uint32_t get10GEXcvrRxOutDiv(uint32_t channel);
    void run10GERxEyeScan(uint32_t channel, uint32_t target_sample_time_ms=1, uint32_t h_gap=1, uint32_t v_gap=1);

    // 10GE Interface
    // Init -- CALL THIS FIRST!
    void init10GEIntf();
    bool get10GEIntfInitDone();
    // Daisy Chain Controls
    bool get10GEDaisyEnTx();
    void set10GEDaisyEnTx(bool enable);
    bool get10GEDaisyEnRx();
    void set10GEDaisyEnRx(bool enable);
    // Daisy Chain Status
    uint32_t get10GEDaisyDropCount(uint32_t index);
    uint32_t get10GERxDropCount(uint32_t index);
    uint32_t get10GERxMaxPacketLength(uint32_t index);
    // Bandwidth Monitor
    uint32_t get10GERxBandwidth(uint32_t index);
    uint32_t get10GETxBandwidth(uint32_t index);

    // IP Rx : IP Receiver

    typedef struct s_ibcStatus {
        bool ready;
        uint32_t empty;
        uint32_t error;
        bool sop;
        bool eop;
    } ibcStatus;

    typedef struct s_ibcPacket {
        uint32_t length;
        uint64_t data[255];
        uint32_t empty;
    } ibcPacket;

      // ** Mandatory!  Call this first!
    void initIPRx();
    bool getIPRxInitDone();

    void setRxDataAddrPort(uint32_t sfp, uint32_t channel, uint32_t ip_addr, uint16_t port, bool bypass);
    void setRxDataAddrPort(uint32_t sfp, uint32_t channel, uint32_t ip_addr, uint16_t port);
    void setRxDataBypass(uint32_t sfp, uint32_t channel, bool bypass);

    void setInBandControlIPAddress(uint32_t sfp, uint32_t addr_idx, uint32_t ip_addr, uint32_t ip_mask=0xffffffff);
    HW_API::ibcStatus getInBandControlStatus(uint32_t sfp);
    void getInBandControlPacket(uint32_t sfp, HW_API::ibcPacket * pkt, bool* ptp, uint64_t* ptp_sec, uint32_t* ptp_nsec);
    uint64_t getInBandControlData(uint32_t sfp);
    uint8_t getInBandControlDropCount(uint32_t sfp);
    void clearInBandControlDropCount(uint32_t sfp);
    uint8_t getInBandControlKeepCount(uint32_t sfp);
    void clearInBandControlKeepCount(uint32_t sfp);

    uint64_t getRxSFPInBandwidth(uint32_t sfp);

    void set10GRxKey(uint32_t sfp, uint32_t chan, uint32_t* key, uint8_t keyId);
    void unset10GRxKey(uint32_t sfp, uint32_t chan, uint8_t keyId);
    void getKeyStatus(uint32_t sfp, uint32_t chan, uint32_t* keyreq, uint32_t* srcIp, uint32_t* dstIp, uint32_t* dstPort);
    void getRTPPayloadType(uint32_t sfp, uint32_t chan, uint8_t* payloadType);
    void getSRTPState(uint32_t sfp, uint32_t chan, bool* is_srtp);

    // IP Tx : IP Transmitter

      // ** Mandatory!  Call this first!
    void initIPTx(uint32_t video_ppf=7);
    bool getIPTxInitDone();

    int  lockHost(bool lock); //set to true before writing host packet
                              //and false after
    void setHostPayload(uint32_t sfp, uint64_t data);
    void setHostCtrl(uint32_t sfp, uint8_t be, bool last, bool we, bool weop);
    bool getHostRdy(uint32_t sfp);
    void set10GTxKey(uint32_t sfp, uint32_t chan, uint32_t* key, uint8_t keyId);
    void unset10GTxKey(uint32_t sfp, uint32_t chan, uint8_t keyId);
    uint64_t getTxEncapBandwidth(uint32_t sfp);
    uint64_t getTxEncapTotalBandwidth(uint32_t sfp);

    // 10GE Tx
    typedef enum e_XTxVidBW {
        Vid_SD,
        Vid_HD,
        Vid_3G,
        NUM_XTXVID_BW
    } XTxVidBW;
    typedef struct s_XTxVidStandard {
        bool interlaced;
        XTxVidBW bw;
        bool hs_pol_high;
        bool vs_pol_high;
        XTxColourSpecification clr_spec;
        uint8_t cmp_size;
        XTxSampleStructure smp_struct;
        uint32_t sptl;
        uint32_t spal;
        uint32_t tlpf0;
        uint32_t tlpf1;
        uint32_t alpf0;
        uint32_t alpf1;
        uint32_t soha;
        uint32_t sova0;
        uint32_t sova1;
        uint32_t sova_ext0;
        uint32_t sova_ext1;
        uint32_t frame_rate_num;
        uint32_t frame_rate_den;
        uint32_t hs_start;
        uint32_t hs_stop;
        uint32_t vs_start0;
        uint32_t vs_start1;
        uint32_t vs_stop0;
        uint32_t vs_stop1;
        uint32_t vs_hpos0;
        uint32_t vs_hpos1;
        bool copyright;
        bool hpos_flag;
        XTxColourSpecification clr_spec_inp;
        XTxSampleStructure smp_struct_inp;
        XTxElectroopticalTransferFunction eotf;
        XTxColourSpace clr_space;
    } XTxVidStandard;
     typedef enum e_VideoType {
        VT_ASPEN422 = 0,
        VT_ASPEN444,
        VT_TICO,
        VT_ST2110,
        NUM_VIDTYPE
    } e_VideoType;
      // Initialize the path
      // ** Mandatory!  Call this first!
    void initAVtoIP();
    bool getAVtoIPInitDone();
      // Program PIDs
    void setVideoTxPID(uint32_t pid);
    void setVideoTxPID_Tico(uint32_t pid);
    void setAudioTxPID(uint32_t pid);
      // Program Video Standard
    void setVideoStandard(uint32_t vid, XTxVidStandard std);
      // Program IP Path
    void setSourceIPAddress(uint32_t sfp, uint32_t ip);
    void setSourceIPPort(uint32_t sfp, uint32_t port);
    void setSourceMACAddress(uint32_t sfp, uint64_t mac);
    void setTTL(uint32_t sfp, uint32_t chan, uint32_t ttl);
    void setDestinationMACAddress(uint32_t sfp, uint32_t chan, uint64_t mac);
    void setDestinationIPAddress(uint32_t sfp, uint32_t chan, uint32_t ip);
    void setDestinationPort(uint32_t sfp, uint32_t chan, uint32_t port);
    void setInterFPGAChannelEnable(uint32_t sfp, uint32_t chan, bool enable);
    void set10GETxEnable(uint32_t sfp, uint32_t chan, bool enable);
    void setAudioTxAES67PacketTime(uint32_t aud, uint32_t grp, bool p1ms);
    uint64_t getTxVidBandwidth(uint32_t vid);
    uint64_t getTxVidActBandwidth(uint32_t vid);
    uint64_t getTxVidTSBandwidth(uint32_t vid);
    uint64_t getTxVidTSTotalBandwidth(uint32_t vid);
    uint64_t getTxAudTSBandwidth(uint32_t aud);
    uint64_t getTxAudTSTotalBandwidth(uint32_t aud);
    uint64_t getTxMetaTSBandwidth(uint32_t meta);
    uint64_t getTxMetaTSTotalBandwidth(uint32_t meta);
    uint64_t getTxUSBTSBandwidth(uint32_t usb);
    uint64_t getTxUSBTSTotalBandwidth(uint32_t usb);
    uint64_t getTxEncapTSBandwidth(uint32_t sfp=0);
    uint64_t getTxEncapTSTotalBandwidth(uint32_t sfp=0);
    uint64_t getTxPayloadTSBandwidth(uint32_t sfp);
    uint64_t getTxPayloadTSTotalBandwidth(uint32_t sfp);
    void dumpTxVidRouteBandwidth(uint32_t sfp, uint32_t vid);
    void dumpTxAudRouteBandwidth(uint32_t sfp, uint32_t aud);
    void dumpTxMetaRouteBandwidth(uint32_t sfp, uint32_t meta);
    void dumpTxUSBRouteBandwidth(uint32_t sfp, uint32_t usb);
    void dumpTxVidSMPTE2110(uint32_t vid);
    bool getTxEncapOverflow(uint32_t sfp);
    uint32_t get10GTxUSBChannel(uint32_t usb);
     int32_t get10GTxVideoChannel(HW_API::e_VideoType vid_type, uint32_t vid);
    uint32_t get10GTxAudioChannel(uint32_t aud);
    uint32_t get10GTxMetaChannel(uint32_t meta);
    uint32_t get10GTxLowrateChannel(uint32_t lowrate);
    uint32_t get10GTxPCRChannel();

    // 10GE Rx
    typedef struct s_vidSTD {
        bool hs_pol_high;
        bool vs_pol_high;
        unsigned sptl;
        unsigned spal;
        unsigned tlpf0;
        unsigned tlpf1;
        unsigned alpf0;
        unsigned alpf1;
        unsigned soha;
        unsigned sova0;
        unsigned sova1;
        unsigned sova_ext0;
        unsigned sova_ext1;
        unsigned rate_num;
        unsigned rate_den;
        unsigned hs_start;
        unsigned hs_stop;
        unsigned vs_start0;
        unsigned vs_stop0;
        unsigned vs_start1;
        unsigned vs_stop1;
        unsigned vs_hpos0;
        unsigned vs_hpos1;
        bool copyright;
        unsigned stream_type;
    } vidSTD;

    // Call this first!
    void initIPtoAV();
    bool getIPtoAVInitDone();

    void setVidSFPChannel(uint32_t vid, uint32_t sfp, uint32_t channel, bool main=true);
    void setAudSFPChannel(uint32_t aud, uint32_t sfp, uint32_t channel, bool main=true);
    void setMetaSFPChannel(uint32_t meta, uint32_t sfp, uint32_t channel, bool main=true);
    void setUSBSFPChannel(uint32_t usb, uint32_t sfp, uint32_t channel, bool main=true);
    void setPCRSFPChannel(uint32_t sfp, uint32_t channel, bool main=true);
    void setVidRedundancy(uint32_t vid, bool redundancy);
    void setVidBnotA(uint32_t vid, bool b);
    bool getVidBnotA(uint32_t vid);
    void setAudRedundancy(uint32_t aud, bool redundancy);
    void setAudBnotA(uint32_t aud, bool b);
    bool getAudBnotA(uint32_t aud);
    void setMetaRedundancy(uint32_t meta, bool redundancy);
    void setMetaBnotA(uint32_t meta, bool b);
    bool getMetaBnotA(uint32_t meta);
    void setUSBRedundancy(uint32_t usb, bool redundancy);
    void setUSBBnotA(uint32_t usb, bool b);
    bool getUSBBnotA(uint32_t usb);
    void setPCRRedundancy(bool redundancy);
    void setPCRBnotA(bool b);
    bool getPCRBnotA();
    bool getVidStreamRTP(uint32_t vid, bool main=true);
    uint64_t getVidStreamRTPErrors(uint32_t vid, bool main=true);
    void setVidStreamEnable(uint32_t vid, bool enable, bool main=true);
    uint32_t getVidPIDDet(uint32_t vid, bool main=true);
    uint32_t getVidPPF(uint32_t vid, bool main=true);
    bool getAudStreamRTP(uint32_t aud, bool main=true);
    uint64_t getAudStreamRTPErrors(uint32_t aud, bool main=true);
    void setAudStreamEnable(uint32_t aud, bool enable, bool main=true);
    uint32_t getAudPIDDet(uint32_t aud, bool main=true);
    uint32_t getAudPPF(uint32_t aud, bool main=true);
    bool getMetaStreamRTP(uint32_t meta, bool main=true);
    uint64_t getMetaStreamRTPErrors(uint32_t meta, bool main=true);
    void setMetaStreamEnable(uint32_t meta, bool enable, bool main=true);
    bool getUSBStreamRTP(uint32_t usb, bool main=true);
    uint64_t getUSBStreamRTPErrors(uint32_t usb, bool main=true);
    void setUSBStreamEnable(uint32_t usb, bool enable, bool main=true);
    bool getPCRStreamRTP(bool main=true);
    uint64_t getPCRStreamRTPErrors(bool main=true);
    void setPCRStreamEnable(bool enable, bool main=true);
    void setVideoRxAspenPID(uint32_t vid, uint32_t pid);
    void setVideoRxTicoPID(uint32_t vid, uint32_t pid);
    void setVidFrameCount(uint32_t vid, uint32_t f0_cnt, uint32_t f1_cnt);
    int getVidColourSpecification(uint32_t vid, IPtoAVType::aspenColourSpecification* colourSpecification);
    int getVidElectroopticalTransferFunction(uint32_t vid, IPtoAVType::aspenElectroopticalTransferFunction* eotf);
    int getVidColourSpace(uint32_t vid, IPtoAVType::aspenColourSpace* colourSpace);
    int getVidSampleStructure(uint32_t vid, IPtoAVType::aspenSampleStructure* sampleStructure);
    int getVidFrameRate(uint32_t vid, float* framerate);
    int getVidSMPTE2110ASPL(uint32_t vid, uint16_t* aspl);
    int getVidSMPTE2110SamplesPerPixel(uint32_t vid, uint8_t* samples_per_pixel);
    int getVidSMPTE2110SampleWidth(uint32_t vid, uint8_t* sample_width);
    int getVidSMPTE2110RGB(uint32_t vid, bool* rgb);
    int getVidSMPTE2110Sampling(uint32_t vid, char* sampling);
    int getVidSMPTE2110Sampling(uint32_t vid, IPtoAVType::smpte2110_20_Sampling* sampling);
    int setVidSMPTE2110Config(uint32_t vid, uint16_t aspl, const char* sampling, uint8_t sample_width);
    int setVidSMPTE2110Config(uint32_t vid, uint16_t aspl, IPtoAVType::smpte2110_20_Sampling sampling, uint8_t sample_width);
    int getVidSMPTE2110Status(uint32_t vid, IPtoAVType::vid2110Status* status);
    HW_API::vidSTD getVidSTD(uint32_t vid);
    void dumpVidSTD(uint32_t vid);
    bool getAudioRxCompressed(uint32_t aud);
    uint32_t getAudioRxSamplingFrequency(uint32_t aud);
    bool getAudioRxHBR(uint32_t aud);
    uint8_t getAudioRxType(uint32_t aud, char* aud_type);
    uint8_t getAudioRxChans(uint32_t aud);
    void setAudioRxPID(uint32_t aud, uint32_t pid);
    void setAudioRxAES67Ctrl(uint32_t aud, uint32_t chans, uint32_t sf_hz);
    void setUseRemotePCR(bool remote);
    uint64_t getRxSFPTSBandwidth(uint32_t sfp);
    uint64_t getRxVidTSBandwidth(uint32_t vid, bool main=true);
    uint64_t getRxAudTSBandwidth(uint32_t aud, bool main=true);
    uint64_t getRxMetaTSBandwidth(uint32_t meta, bool main=true);
    uint64_t getRxUSBTSBandwidth(uint32_t usb, bool main=true);
    uint64_t getRxVidBandwidth(uint32_t vid);
    uint64_t getRxAudBandwidth(uint32_t aud);
    uint64_t getRxMetaBandwidth(uint32_t meta);
    uint64_t getRxUSBBandwidth(uint32_t usb);
    void dumpRxVidRouteBandwidth(uint32_t sfp, uint32_t vid);
    void dumpRxAudRouteBandwidth(uint32_t sfp, uint32_t aud);
    void dumpRxMetaRouteBandwidth(uint32_t sfp, uint32_t meta);
    void dumpRxUSBRouteBandwidth(uint32_t sfp, uint32_t usb);
    void allowDescramble10GERxVid(uint32_t vid, bool descramble);
     int32_t get10GRxVideoChannel(HW_API::e_VideoType, uint32_t vid);
    uint32_t get10GRxAudioChannel(uint32_t aud);
    uint32_t get10GRxMetaChannel(uint32_t meta);
    uint32_t get10GRxUSBChannel(uint32_t usb);
    uint32_t get10GRxLowrateChannel(uint32_t lowrate);
    uint32_t get10GRxPCRChannel();

    // Frame Buffer and Scaler
    typedef enum e_ScalerRotateAngle
    {
      ROT_INIT = 0,
      ROT_0,
      ROT_90,
      ROT_180,
      ROT_270,
      NUM_ROT_ANGLES
    } ScalerRotateAngle;
    typedef enum e_ScalerAspectMode
    {
      ASPECT_INIT = 0,
      ASPECT_NATIVE,
      ASPECT_FIT,
      ASPECT_ZOOM,
      ASPECT_FILL,
      NUM_ASPECT_MODES
    } ScalerAspectMode;
    typedef enum e_ScalerSwitchType {
        SWITCH_CLEAN=0,
        SWITCH_FADE,
        NUM_SWITCH_TYPES
    } ScalerSwitchType;
    typedef struct s_ScalerSettings {
        double crop_top;
        double crop_left;
        double crop_height;
        double crop_width;
        HW_API::ScalerAspectMode aspect_mode;
        uint32_t brdr_yg;
        uint32_t brdr_cbb;
        uint32_t brdr_crr;
    } ScalerSettings;
    typedef struct s_ScalerPipSettings {
        uint32_t pip_h_left;
        uint32_t pip_h_right;
        uint32_t pip_v_top;
        uint32_t pip_v_bottom;
    } ScalerPipSettings;
    typedef struct s_ScalerFrameRate {
        uint32_t frame_rate_num;
        uint32_t frame_rate_den;
    } ScalerFrameRate;
    typedef struct s_MixerColour {
        uint32_t sample_0;
        uint32_t sample_1;
        uint32_t sample_2;
        uint32_t sample_3;
    } MixerColour;
    typedef enum e_YCbCr422Colour {
        YCBCR422_BLACK=0,
        YCBCR422_GREY,
        YCBCR422_WHITE,
        NUM_YCBCR422_COLOURS
    } YCbCr422Colour;
    typedef enum e_YCbCr444Colour {
        YCBCR444_BLACK=0,
        YCBCR444_GREY,
        YCBCR444_WHITE,
        YCBCR444_YELLOW,
        YCBCR444_CYAN,
        YCBCR444_GREEN,
        YCBCR444_MAGENTA,
        YCBCR444_CARDINAL,
        YCBCR444_BLUE,
        YCBCR444_RED,
        NUM_YCBCR444_COLOURS
    } YCbCr444Colour;
    typedef enum e_RGB444Colour {
        RGB444_BLACK=0,
        RGB444_GREY,
        RGB444_WHITE,
        RGB444_YELLOW,
        RGB444_CYAN,
        RGB444_GREEN,
        RGB444_MAGENTA,
        RGB444_CARDINAL,
        RGB444_BLUE,
        RGB444_RED,
        NUM_RGB444_COLOURS
    } RGB444Colour;
    typedef enum e_OSDColour{
        OSD_BLACK=0,
        OSD_RED,
        OSD_BLUE,
        OSD_MAGENTA,
        OSD_GREEN,
        OSD_YELLOW,
        OSD_CYAN,
        OSD_WHITE,
        NUM_OSD_COLOURS
    } OSDColour;
    // Initialize the path
    // ** Mandatory, call this first!
    void initScalerPath(uint32_t path);
    int  getScalerPathArchType(uint32_t path);
    bool getScalerPathInitDone(uint32_t path);
    // Read Configuration
    bool getScalerYCbCrNotRGB(uint32_t path);
    uint32_t getScalerMaxASPL(uint32_t path);
    uint32_t getScalerMaxALPF(uint32_t path);
    uint32_t getScalerSDRAMRPortWidth(uint32_t path);
    uint32_t getScalerSDRAMRBurstLength(uint32_t path);
    uint32_t getScalerPixelsPerReadBurst(uint32_t path);
    uint32_t getScalerMaxReadBurstsPerLine(uint32_t path);
    uint8_t  getScalerLossOfInputImagePage(uint32_t path);
    // Route Video through Frame Buffer / Scaler
    void useScalerPath(uint32_t path, bool enable);
    // Set Raster phase (debug)
    void setScalerPhase(uint32_t path, uint32_t hphase, uint32_t vphase);
    // Dump path info
    void dumpScalerConfig(uint32_t path);
    void dumpScalerStatus(uint32_t path);
    void getBorderSettings(uint32_t path, MVScalerTopType::BorderSettings * border_settings, bool sel_scaler_b = true);
    void setBorderSettings(uint32_t path, MVScalerTopType::BorderSettings * border_settings, bool sel_scaler_b = true);
    void setBorderColour(uint32_t path, uint32_t yg, uint32_t cbb, uint32_t crr, bool sel_scaler_b = true);
    void getScalerSettings(uint32_t path, MVScalerTopType::ScalerSettings * scaler_settings, bool sel_scaler_b = true);
    // Switching Controls
    // Call startScalerSwitch, switchScalerInput finishScalerSwitch for
    // smooth switching based on the switch type, or just call the switch
    // function for a hard switch
      // Start a switch
    void startScalerSwitch(uint32_t path, HW_API::ScalerSwitchType switch_type);
      // Switch to HDMI input / update HDMI input resolution
    void switchScalerInput(uint32_t path,
                           RasterTypes::CVTParameters in_params,
                           HW_API::ScalerFrameRate in_rate,
                           HW_API::scColourFormat_type colour);
      // Switch to Aspen input / update Aspen input resolution
    void switchScalerInput(uint32_t path,
                           RasterTypes::AspenParameters in_params,
                           HW_API::ScalerFrameRate in_rate,
                           HW_API::scColourFormat_type colour);
      // Switch to generic input / update generic input resolution
    void switchScalerInput(uint32_t path,
                           RasterTypes::RasterParameters in_raster,
                           HW_API::ScalerFrameRate in_rate,
                           HW_API::scColourFormat_type colour);
      // Update path settings
    void switchScalerPathSettings(uint32_t path, HW_API::ScalerSettings * settings);
      // Finish current switch
    void finishScalerSwitch(uint32_t path, uint8_t ignoreNFrames=3);
    // Set Output Resolution
    // Output resolution changes are not clean
    void setScalerOutput(uint32_t path,
                         RasterTypes::CVTParameters out_params,
                         HW_API::ScalerFrameRate out_rate,
                         HW_API::scColourFormat_type colour);
    void setScalerOutput(uint32_t path,
                         RasterTypes::AspenParameters out_params,
                         HW_API::ScalerFrameRate out_rate,
                         HW_API::scColourFormat_type colour);
    void setScalerOutput(uint32_t path,
                         RasterTypes::RasterParameters out_raster,
                         HW_API::ScalerFrameRate out_rate,
                         HW_API::scColourFormat_type colour);
    void setScalerOutputPip(uint32_t path,
                          HW_API::ScalerPipSettings pip_settings,
                          RasterTypes::CVTParameters raster_out_params,
                          HW_API::ScalerFrameRate out_rate,
                          HW_API::scColourFormat_type colour);
    int  setScalerPipPath(uint32_t path,
                          HW_API::ScalerPipSettings pip_settings,
                          RasterTypes::CVTParameters raster_out_params,
                          HW_API::ScalerFrameRate out_rate,
                          HW_API::scColourFormat_type colour,
                          uint32_t locktype = 0);
    int setScalerPipPathLock(uint32_t scaler_path, uint32_t vidmix_idx, RasterTypes::CVTParameters vid_mix_raster_params, HW_API::ScalerFrameRate out_rate, uint32_t lock_type);
    int setScalerPipPathLock(uint32_t scaler_path, uint32_t vidmix_idx, RasterTypes::RasterParameters vid_mix_raster_params, HW_API::ScalerFrameRate out_rate, uint32_t lock_type);
    void getScalerPlayoutRaster(uint32_t path, RasterTypes::RasterParameters * out_raster);
    uint32_t getScalerVidInpBufferError(uint32_t path);
    // Sync Mask
    bool setScalerRasterSyncMaskWidth(uint32_t path, uint32_t mask_width);
    // Freeze Scaler Memory Ports
    void disableScalerReadPort(uint32_t path, bool disable);
    void disableScalerWritePort(uint32_t path, bool disable);
    void setScalerReadPage(uint32_t path, uint8_t page, bool lock);
    void setScalerReadPage(uint32_t path, uint8_t page, bool lock, bool use_b);
    bool getScalerFrameBufferUseB(uint32_t path);
    void setScalerFrameBufferUseB(uint32_t path, bool use_b);
    bool getScalerFrameBufferHalt(uint32_t path);
    // Loss of Input Colour
    void setLossofInputColour(uint32_t path, HW_API::YCbCr422Colour colour);
    void setLossofInputColour(uint32_t path, HW_API::YCbCr444Colour colour);
    void setLossofInputColour(uint32_t path, HW_API::RGB444Colour colour);
    void setLossofInputColour(uint32_t path, HW_API::MixerColour * colour);
    void setLossofInput(uint32_t path, bool lost);
    // Reference clock selection
    void setUseExternalClock(uint32_t path, bool use);
    bool getUseExternalClock(uint32_t path);
    void setRefClkenSource(uint32_t path, uint32_t source);
    uint32_t getRefClkenSource(uint32_t path);
    // Video Lock
    bool getScalerVidLockEnable(uint32_t path);
    void setScalerVidLockEnable(uint32_t path, bool enable);
    void getScalerVidLockLockType(uint32_t path, uint8_t* lock_type);
    void setScalerVidLockLockType(uint32_t path, uint8_t lock_type);
    void scalerVidLockRecenter(uint32_t path);
    bool setScalerRasterPhase(uint32_t path, int const out, int const hphase, int const vphase);
    void setScalerVidLockResyncPhase(uint32_t path, uint32_t phase);
    uint32_t getScalerVidLockResyncPhase(uint32_t path);
    void setScalerVidLockRateLimit(uint32_t path, uint32_t limit);
    uint32_t getScalerVidLockRateLimit(uint32_t path);
    // PTP Locking
    void getScalerPTPLock(uint32_t path, bool* enable);
    void setScalerPTPLock(uint32_t path, bool enable);
    void setScalerPTPPhase(uint32_t path);
    void setScalerPTPPhaseJam(uint32_t path);
    void setScalerPTPReferenceLockReset(uint32_t path);
    void getScalerPTPReferenceLockLocked(uint32_t path, bool* locked);
    void getScalerRxRTPOffset(uint32_t path, uint32_t* rxoffset);
    void setScalerRxRTPOffset(uint32_t path, uint32_t rxoffset);
    // Genlock Locking
    void getScalerGenlockLock(uint32_t path, bool* enable);
    void setScalerGenlockLock(uint32_t path, bool enable);
    void setScalerGenlockPhaseJam(uint32_t path);
    void setScalerGenlockReferenceLockReset(uint32_t path);
    void getScalerGenlockReferenceLockLocked(uint32_t path, bool* locked);
    // Debug / Test Functions
    // These don't need to be called during normal operation
    void setScalerOutputSimp(uint32_t path,
                             RasterTypes::CVTParameters out_params);
    void setScalerOutputSimp(uint32_t path,
                             RasterTypes::AspenParameters out_params);
    void setScalerOutputSimp(uint32_t path,
                             RasterTypes::RasterParameters out_raster);
    bool getScalerOutputOverflow(uint32_t path);
    bool getScalerOutputUnderflow(uint32_t path);
    uint32_t getScalerOutputBandwidth(uint32_t path);
    uint32_t getScalerInputRasterRate(uint32_t path);
    uint32_t getScalerOutputRasterRate(uint32_t path);
    uint32_t getScalerOutputHCount(uint32_t path);
    uint32_t getScalerOutputVCount(uint32_t path);
    uint32_t getScalerOutputTCount(uint32_t path);
    void dumpScalerDebugCounters(uint32_t path);
    void dumpScalerLockStatus(uint32_t path);
    void dumpScalerPTPStatus(uint32_t path);
    void dumpScalerPTPPlayoutTimingStats(uint32_t path);
    void dumpScalerReferenceLockStatus(uint32_t path);
    void dumpScalerOSDSettings(uint32_t path);
    void dumpScalerLockPhase(uint32_t path);
    uint32_t getScalerLockResyncCount(uint32_t path);
    uint32_t getScalerLockPhaseError(uint32_t path);

    // Video Processing Wrapper
    void initVidProc();
    bool getVidProcInitDone();
    void setVidProcMux(uint32_t vid_mix_idx, uint32_t vid_mix_mux_index);
    uint32_t getVidProcMux(uint32_t vid_mix_idx);
    void setVidProcPipArea(uint32_t idx, uint32_t h_start, uint32_t h_stop, uint32_t v_start_field0, uint32_t v_stop_field0, uint32_t v_start_field1, uint32_t v_stop_field1);
    void getVidProcPipArea(uint32_t idx, uint32_t* h_start, uint32_t* h_stop, uint32_t* v_start_field0, uint32_t* v_stop_field0, uint32_t* v_start_field1, uint32_t* v_stop_field1);
    void setPipEnable(uint32_t vid_mix_idx, uint32_t inp_idx, bool enable);
    void setPipEnableMask(uint32_t vid_mix_idx, uint32_t mask);
    uint32_t getPipEnable(uint32_t vid_mix_idx, uint32_t inp_idx);
    void setBldColorSpace(uint32_t vid_mix_idx, uint32_t fmt);
    uint32_t getBldColorSpace(uint32_t vid_mix_idx);
    void setMixOutSelect(uint32_t vid_mix_idx, uint32_t select);
    uint32_t getMixOutSelect(uint32_t vid_mix_idx);
    bool setVidProcRaster(RasterTypes::RasterParameters const &raster_params);
    bool setVidProcRaster(RasterTypes::AspenParameters const &raster_params);
    bool setVidProcRaster(RasterTypes::CVTParameters const &raster_params);
    bool setVidProcRaster(RasterTypes::SDIParameters const &raster_params);
    bool setVidProcRasterIdx(uint32_t vid_mix_idx,uint32_t raster_idx);
    bool setVidProcVidMixRasterPhase(uint32_t vid_mix_idx, uint32_t raster_num, uint32_t hphase, uint32_t vphase);
    bool setVidProcVidMixRasterSyncMaskWidth(uint32_t vid_mix_idx, uint32_t mask_width);
    void setVidProcScalerReferenceDiv(uint32_t sc_idx, uint32_t div);
    uint32_t getVidProcScalerReferenceDiv(uint32_t sc_idx);
    void setVidProcPipBorderColour(uint32_t idx, uint32_t colour_g_y, uint32_t colour_b_cb, uint32_t colour_r_cr);
    void getVidProcPipBorderColour(uint32_t idx, uint32_t* colour_g_y, uint32_t* colour_b_cb, uint32_t* colour_r_cr);
    uint32_t getVidProcScalerRasterSyncSource(uint32_t sc_idx);
    void setVidProcScalerRasterSyncSource(uint32_t sc_idx, uint32_t sync_source_idx);
    void setVidProcScalerRasterSyncSourceScRaster(uint32_t sc_idx,uint32_t sc_idx_source);
    void setVidProcScalerRasterSyncSourcePipMixer(uint32_t sc_idx, uint32_t vid_mix_idx);
    void setVidProcScalerRasterSyncSourceScPhase(uint32_t sc_idx, uint32_t sc_source_idx);
    void setVidProcScalerRasterSyncSourceDisable(uint32_t sc_idx);
    void setVidProcPipMixerRasterSyncSourceScRaster(uint32_t pip_idx,uint32_t sc_idx_source);
    void setVidProcPipMixerRasterSyncSourcePipMixer(uint32_t pip_idx, uint32_t vid_mix_idx);
    void setVidProcPipMixerRasterSyncSourceScPhase(uint32_t pip_idx, uint32_t sc_source_idx);
    void setVidProcPipMixerRasterSyncSourceDisable(uint32_t pip_idx);


    // HDMI
    void initHdmi(uint32_t chan);
    bool getHdmiInitDone(uint32_t chan);
    int getHdmiStateRunning(uint32_t chan, bool* running);
    int getHdmiMainLoopHeartbeat(uint32_t chan, uint32_t* mainLoopHeartbeat);
    uint8_t debugHdmiRead(uint32_t chan, uint32_t addr);
    void debugHdmiWrite(uint32_t chan, uint32_t addr, uint8_t data);
    void debugHdmiConfig(uint32_t chan);
    void debugHdmiConfigMemory(uint32_t chan);
    void debugHdmiConfigStatus(uint32_t chan);
    void debugHdmiConfigRx(uint32_t chan);
    void debugHdmiConfigRxStatus(uint32_t chan);
    void debugHdmiConfigTx(uint32_t chan);
    void debugHdmiConfigTxStatus(uint32_t chan);
    void debugHdmiCheckConfig(uint32_t chan);
    void debugHdmiWriteConfig(uint32_t chan);
    void debugHdmiSizeConfig(uint32_t chan);
    void debugHdmiClkDetFreq(uint32_t chan);
    void debugHdmiTxClkDetFreq(uint32_t chan);
    void debugHdmiRxHdcp14(uint32_t chan);
    void debugHdmiTxHdcp14(uint32_t chan);
    void debugHdmiRxHdcp22(uint32_t chan);
    void debugHdmiTxHdcp22(uint32_t chan);
    void debugHdmiRxLinkCounters(uint32_t chan);
    void debugHdmiRxLinkStatus(uint32_t chan);
    void setHdmiLoopbackMode(uint32_t chan, uint8_t mode);
    bool getHdmiRxIsConnected(uint32_t chan);
    bool getHdmiTxIsConnected(uint32_t chan);
    bool getHdmiRxStreamIsUp(uint32_t chan);
    bool getHdmiTxStreamIsUp(uint32_t chan);
    int getHdmiRxHotplugDetect(uint32_t chan, bool* enabled);
    int setHdmiRxHotplugDetect(uint32_t chan, bool enabled);
    int getHdmiTxEDID(uint32_t chan, uint8_t* edid, uint32_t* size, uint8_t* valid, uint8_t* edid_idx = NULL);
    int setHdmiRxEDID(uint32_t chan, uint8_t* edid, uint32_t size);
    int getHdmiTxHdmi20Capable(uint32_t chan, bool* capable);
    int getHdmiTxHdcp22Capable(uint32_t chan, bool* capable);
    int getHdmiTxTmdsClockRatio(uint32_t chan, bool* ratio);
    int getHdmiTxSinkClockRatio(uint32_t chan, bool* ratio);
    int getHdmiTxTmdsClockRatioReprogrammed(uint32_t chan, uint8_t* count);
    int setHdmiTxSetTmdsClockRatio(uint32_t chan);
    int getHdmiRxAudioChannels(uint32_t chan, uint8_t* chans);
    int getHdmiRxAudioSamplingFrequency(uint32_t chan, uint32_t* sf);
    int getHdmiRxAudioCompressed(uint32_t chan, uint8_t* compressed);
    int getHdmiRxAudioDataType(uint32_t chan, char* aud_type);
    int getHdmiRxAudioHBR(uint32_t chan, uint8_t* hbr);
    int getHdmiTxAudioSamplingFrequency(uint32_t chan, uint32_t* sf);
    int getHdmiTxAudioCompressed(uint32_t chan, bool* compressed);
    int getHdmiTxAudioSRC(uint32_t chan, bool* useSRC);
    int getHdmiTxAudioDrop(uint32_t chan, bool* drop);
    int getHdmiTxAudioHBR(uint32_t chan, uint8_t* hbr);
    int setHdmiTxAudioChannels(uint32_t chan, uint8_t chans);
    int setHdmiTxAudioMute(uint32_t chan, bool mute);
    int setHdmiTxAudioReset(uint32_t chan, bool reset);
    int setHdmiTxAudioCbits(uint32_t chan, bool restamp, bool professional);
    int setHdmiTxAudioForceSRC(uint32_t chan, bool forcesrc);
    int getHdmiRxAuxPacket(uint32_t chan, uint8_t* ptr, uint32_t* size);
    int setHdmiTxAuxPacket(uint32_t chan, uint8_t* ptr, uint32_t size);
    int getHdmiHDCPKeysPresent(uint32_t chan, bool* present);
    int getHdmiHDCPKeysLoaded(uint32_t chan, HDMI_Xil_Type::Key_type* status);
    int getHdmiHDCPEEPROMData(uint32_t chan, uint8_t* hdcp_eeprom_data);
    int setHdmiRxHDCPProtocol(uint32_t chan, HDMI_Xil_Type::HDCP_type hdcpProtocol);
    int getHdmiRxHDCPProtocol(uint32_t chan, HDMI_Xil_Type::HDCP_type* hdcpProtocol);
    int getHdmiRxHDCPIsAuthenticated(uint32_t chan, bool* isAuthenticated);
    int getHdmiRxHDCPIsEncrypted(uint32_t chan, bool* isEncrypted);
    int getHdmiRxTicoRequired(uint32_t chan, bool* ticoRequired, HDMI_Xil_Type::ColourFormat_type colourFormat, HDMI_Xil_Type::ColourDepth_type colourDepth, bool fractional = false);
    int getHdmiRxTMDS181BadState(uint32_t chan, bool* badState);
    int setHdmiTxHDCPProtocol(uint32_t chan, HDMI_Xil_Type::HDCP_type hdcpProtocol);
    int getHdmiTxHDCPProtocol(uint32_t chan, HDMI_Xil_Type::HDCP_type* hdcpProtocol);
    int getHdmiTxHDCPIsAuthenticated(uint32_t chan, bool* isAuthenticated);
    int getHdmiTxHDCPIsEncrypted(uint32_t chan, bool* isEncrypted);
    int setHdmiTxHDCPEnableEncryption(uint32_t chan, bool enableEncryption);
    int getHdmiTxHDCPAuthenticationRequest(uint32_t chan, bool* reqAuthentication);
    int setHdmiTxHDCPAuthenticationRequest(uint32_t chan, bool reqAuthentication);
    int getHdmiTxHDCPWaitingPeriod(uint32_t chan, uint32_t* waitingPeriod);
    int setHdmiTxHDCPWaitingPeriod(uint32_t chan, uint32_t waitingPeriod);
    int setHdmiTxHDCPMask(uint32_t chan, HDMI_Xil_Type::HDCPMask_type hdcpMask);
    int getHdmiTxHDCPMask(uint32_t chan, HDMI_Xil_Type::HDCPMask_type* hdcpMask);
    int getHdmiTxHDCPWaitCount(uint32_t chan, uint32_t* waitCount);
    int getHdmiTxHDCPBlank(uint32_t chan, bool* blank);
    int getHdmiRxVideoConfig(uint32_t chan, HDMI_Xil_Type::VideoStream_type* videoStream, HDMI_Xil_Type::VideoConfig_type* videoConfig);
    int setHdmiTxVideoConfig(uint32_t chan, HDMI_Xil_Type::VideoStream_type* videoStream, uint8_t videoIDCode, bool dviMode = false, uint8_t lte_340mcsc_scramble = 0, uint8_t max_tmds_character_rate = 120, uint8_t max_tmds_clock = 60, bool sendBasicInfoFrames = true, bool fractional = false);
    int getHdmiTxVideoConfig(uint32_t chan, HDMI_Xil_Type::VideoStream_type* videoStream, bool* dviMode);
    int getHdmiTxVideoConfigValid(uint32_t chan, HDMI_Xil_Type::VideoStream_type* videoStream, uint8_t videoIDCode, bool dviMode = false, uint8_t lte_340mcsc_scramble = 0, uint8_t max_tmds_character_rate = 120, uint8_t max_tmds_clock = 60, bool fractional = false);
    int getHdmiTxVideoConfig(uint32_t chan, HDMI_Xil_Type::VideoStream_type* videoStream, bool* dviMode);
    int setHdmiTxVideoLoopback(uint32_t chan);
    int getHdmiTxTmdsClockOff(uint32_t chan, bool* off);
    int getHdmiTxOff(uint32_t chan, bool* off);
    int setHdmiTxOff(uint32_t chan, bool off);
    int setHdmiRxOutputEnable(uint32_t chan);
    int getHdmiRxVideoFractional(uint32_t chan, bool* fractional);
    int getHdmiTxMetadataFlushedCount(uint32_t chan, uint16_t* count);
    int getHdmiTxMetadataDRMCount(uint32_t chan, uint16_t* count);
    int getHdmiTxMetadataHDR10PlusCount(uint32_t chan, uint16_t* count);
    int getHdmiTxMetadataDolbyCountMasked(uint32_t chan, uint16_t* count);
    int getHdmiTxMetadataDolbyCountSent(uint32_t chan, uint16_t* count);
    int getHdmiTxMetadataH14bDolbyCountMasked(uint32_t chan, uint16_t* count);
    int getHdmiTxMetadataH14bDolbyCountSent(uint32_t chan, uint16_t* count);
    int getHdmiTxMetadataGenericCount(uint32_t chan, uint16_t* count);
    int getHdmiTxMetadataDRM(uint32_t chan, HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type* drmInfoFrame);
    int getHdmiTxMetadataHDR10Plus(uint32_t chan, HDMI_Xil_Type::HDR10PlusInfoFrame_type* hdr10pInfoFrame);
    int getHdmiTxMetadataDolby(uint32_t chan, HDMI_Xil_Type::DolbyInfoFrame_type* dolbyInfoFrame);
    int getHdmiTxMetadataGenericBuffer(uint32_t chan, HDMI_Xil_Type::Aux_type* genericAuxBuffer);
    int getHdmiTxMetadataSent_localh14b_vsif(uint32_t chan, bool* sent);
    int getHdmiTxMetadataSent_remoteh14b_vsif(uint32_t chan, bool* sent);
    int getHdmiTxMetadataSent_dolby_h14b_vsif(uint32_t chan, bool* sent);
    int getHdmiTxMetadataSent_dolby_vsif(uint32_t chan, bool* sent);
    int getHdmiTxInfoFramesInitialized(uint32_t chan, bool* initialized);
    int getHdmiTxInfoFrameVSIFEnable(uint32_t chan, bool* enabled);
    int getHdmiTxInfoFrameDRMEnable(uint32_t chan, bool* enabled);
    int getHdmiTxInfoFrameHDR10PlusEnable(uint32_t chan, bool* enabled);
    int getHdmiTxInfoFrameDolbyEnable(uint32_t chan, bool* enabled);
    int getHdmiTxInfoFrameSPDEnable(uint32_t chan, bool* enabled);
    int getHdmiTxInfoFrameAudioMetadataEnable(uint32_t chan, bool* enabled);
    int getHdmiTxInfoFrameAudio(uint32_t chan, HDMI_Xil_Type::AudioInfoFrame_type* audioInfoFrame);
    int getHdmiTxInfoFrameAVI(uint32_t chan, HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type* aviInfoFrame);
    int getHdmiTxInfoFrameVSIF(uint32_t chan, HDMI_Xil_Type::VendorSpecificInfoFrame_type* vsifInfoFrame);
    int getHdmiTxInfoFrameDRM(uint32_t chan, HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type* drmInfoFrame);
    int getHdmiTxInfoFrameHDR10Plus(uint32_t chan, HDMI_Xil_Type::HDR10PlusInfoFrame_type* hdr10pInfoFrame);
    int getHdmiTxInfoFrameDolby(uint32_t chan, HDMI_Xil_Type::DolbyInfoFrame_type* dolbyInfoFrame);
    int getHdmiTxInfoFrameSPD(uint32_t chan, HDMI_Xil_Type::SourceProductDescriptorInfoFrame_type* spdInfoFrame);
    int getHdmiTxInfoFrameAudioMetadata(uint32_t chan, HDMI_Xil_Type::AudioMetadataPacket_type* audiometadataInfoFrame);
    int setHdmiTxInfoFramesInitialized(uint32_t chan);
    int setHdmiTxInfoFrameVSIFEnable(uint32_t chan, bool enabled);
    int setHdmiTxInfoFrameDRMEnable(uint32_t chan, bool enabled);
    int setHdmiTxInfoFrameHDR10PlusEnable(uint32_t chan, bool enabled);
    int setHdmiTxInfoFrameDolbyEnable(uint32_t chan, bool enabled);
    int setHdmiTxInfoFrameSPDEnable(uint32_t chan, bool enabled);
    int setHdmiTxInfoFrameAudioMetadataEnable(uint32_t chan, bool enabled);
    int setHdmiTxInfoFrameAudio(uint32_t chan, HDMI_Xil_Type::AudioInfoFrame_type* audioInfoFrame);
    int setHdmiTxInfoFrameAVI(uint32_t chan, HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type* aviInfoFrame);
    int setHdmiTxInfoFrameVSIF(uint32_t chan, HDMI_Xil_Type::VendorSpecificInfoFrame_type* vsifInfoFrame);
    int setHdmiTxInfoFrameDRM(uint32_t chan, HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type* drmInfoFrame);
    int setHdmiTxInfoFrameHDR10Plus(uint32_t chan, HDMI_Xil_Type::HDR10PlusInfoFrame_type* hdr10pInfoFrame);
    int setHdmiTxInfoFrameDolby(uint32_t chan, HDMI_Xil_Type::DolbyInfoFrame_type* dolbyInfoFrame);
    int setHdmiTxInfoFrameSPD(uint32_t chan, HDMI_Xil_Type::SourceProductDescriptorInfoFrame_type* spdInfoFrame);
    int setHdmiTxInfoFrameAudioMetadata(uint32_t chan, HDMI_Xil_Type::AudioMetadataPacket_type* audiometadataInfoFrame);
    int getHdmiRxInfoFrameAudio(uint32_t chan, HDMI_Xil_Type::AudioInfoFrame_type* audioInfoFrame);
    int getHdmiRxInfoFrameAVI(uint32_t chan, HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type* aviInfoFrame);
    int getHdmiRxInfoFrameVSIF(uint32_t chan, HDMI_Xil_Type::VendorSpecificInfoFrame_type* vsifInfoFrame);
    int getHdmiRxInfoFrameGCP(uint32_t chan, HDMI_Xil_Type::GeneralControlInfoFrame_type* gcpInfoFrame);
    int getHdmiRxInfoFrameDRM(uint32_t chan, HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type* drmInfoFrame);
    int getHdmiRxInfoFrameSPD(uint32_t chan, HDMI_Xil_Type::SourceProductDescriptorInfoFrame_type* spdInfoFrame);
    int getHdmiRxInfoFrameHDR10Plus(uint32_t chan, HDMI_Xil_Type::HDR10PlusInfoFrame_type* hdr10pInfoFrame);
    int getHdmiRxInfoFrameDolby(uint32_t chan, HDMI_Xil_Type::DolbyInfoFrame_type* dolbyInfoFrame);
    int getHdmiRxInfoFrameAudioMetadata(uint32_t chan, HDMI_Xil_Type::AudioMetadataPacket_type* audiometadataInfoFrame);
    int getHdmiRxMetadataCount(uint32_t chan, uint16_t* count);
    int getHdmiRxInfoFrameSPDAfterStreamUp(uint32_t chan, bool* spdAfterStreamUp);
    int getHdmiRxInfoFrameDolby14bCnt(uint32_t chan, uint8_t* dolby14bCnt);
    int getHdmiRxInfoFrameAudio_ChannelCount(HDMI_Xil_Type::AudioInfoFrame_type audioInfoFrame, uint8_t* cc);
    int getHdmiRxInfoFrameAudio_ChannelAllocation(HDMI_Xil_Type::AudioInfoFrame_type audioInfoFrame, uint8_t* ca);
    int getHdmiRxInfoFrameAVI_VIC(HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type aviInfoFrame, uint8_t* vic);
    int getHdmiRxInfoFrameVSIF_HDMI_VIC(HDMI_Xil_Type::VendorSpecificInfoFrame_type vsifInfoFrame, uint8_t* hdmi_vic);
    int getHdmiRxInfoFrameGCP_Clear_AVMUTE(HDMI_Xil_Type::GeneralControlInfoFrame_type gcpInfoFrame, uint8_t* clear_avmute);
    int getHdmiRxInfoFrameGCP_Set_AVMUTE(HDMI_Xil_Type::GeneralControlInfoFrame_type gcpInfoFrame, uint8_t* set_avmute);
    int setHdmiRxDisableDropErr(uint32_t chan, bool set);
    int setHdmiRxDisableHCountErr(uint32_t chan, bool set);
    int resetHdmiRxCounters(uint32_t chan);
    int getHdmiRxFrameCount(uint32_t chan, uint32_t* frames);
    int getHdmiRxDropErrCount(uint32_t chan, uint32_t* errors, uint16_t* line, uint16_t* hcount);
    int getHdmiRxHCountErrCount(uint32_t chan, uint32_t* errors, uint16_t* line, uint16_t* hcount);
    int getHdmiRxVCountErrCount(uint32_t chan, uint32_t* errors, uint16_t* vcount);
    int setHdmiRxLinkStatusInterval(uint32_t chan, uint32_t statusInterval);
    int getHdmiRxLinkStatusError(uint32_t chan, uint32_t* link0, uint32_t* link1, uint32_t* link2);
    int getHdmiTxSi570LockEnable(uint32_t chan, bool* enable);
    int setHdmiTxSi570LockEnable(uint32_t chan, bool enable);
    int getHdmiRxClockNoVideo(uint32_t chan, uint32_t* count);
    int getHdmiRxClockNoVideoThreshold(uint32_t chan, uint32_t* count);
    int setHdmiRxClockNoVideoThreshold(uint32_t chan, uint32_t count);
    // ICRON USB
    void initIcronUSB();
    bool getIcronUSBInitDone();
    int getIcronUSBGTXStatus(uint32_t* GTXStatus);
    int getIcronUSBLink(bool* link);
    int getIcronUSBHost(bool* host);
    int getIcronUSBVbusEn(bool* vbus_en);
    int getIcronUSBActivity(bool* activity);
    int getIcronUSBGMII(bool* gmii_rx, bool* gmii_tx);
    int getIcronUSBLinkState(IcronUSB::linkState* state);
    int getIcronUSBHostState(bool* state);
    int getIcronUSBVbusEnState(bool* state);
    int getIcronUSBActivityState(bool* state);
    int getIcronUSBGMIIState(bool* state_rx, bool* state_tx);
    int dumpIcronUSBStatus();
    int dumpIcronUSBStatusState();
    int dumpIcronUSBControl();
    int setIcronUSBProgB(bool prog_B);
    int setIcronUSBBootSel0(bool boot_sel0);
    int setIcronUSBMode(bool usbmode);
    int setIcronUSBPhyL2En(bool phyl2en);
    int setIcronUSBPairN(bool pairn);
    int setIcronUSBResetN(bool resetn);
    int setIcronUSBRexLexMode(bool rex_mode);
    int getIcronRxOffset(uint32_t* offset);
    int setIcronOffset(uint32_t offset);
    int getIcronOffset(uint32_t* offset);
    int setIcronLockedMode(bool enable);
    int getIcronLockedMode(bool* enable);
    int getIcronRxLocked(bool* locked);
    int getIcronRxFifoStatus(uint32_t* status);
    int getIcronTxFifoStatus(uint32_t* status);

    // Audio Mixer
    void initAMixer(uint8_t index, uint8_t InBits, uint8_t FlBits);
    bool getAMixerInitDone(uint8_t index);

    int getAMixerInvertControl(uint8_t index, uint8_t channel, uint8_t branch, bool *invert);
    int getAMixerInStream(uint8_t index, uint8_t channel, uint8_t branch, uint8_t *inStream);
    int getAMixerInChannel(uint8_t index, uint8_t channel, uint8_t branch, uint8_t *inChannel);
    int getAMixerGainCoefficient(uint8_t index, uint8_t channel, uint8_t branch, float *gain);
    int getAMixerCommandInput(uint8_t index, uint8_t channel, uint8_t branch, bool *invert, uint8_t *inStream, uint8_t *inChannel, float *gain);

    int setAMixerInvertControl(uint8_t index, uint8_t channel, uint8_t branch, bool invert);
    int setAMixerInStream(uint8_t index, uint8_t channel, uint8_t branch, uint8_t inStream);
    int setAMixerInChannel(uint8_t index, uint8_t channel, uint8_t branch, uint8_t inChannel);
    int setAMixerGainCoefficient(uint8_t index, uint8_t channel, uint8_t branch, float gain);
    int setAMixerCommandInput(uint8_t index, uint8_t channel, uint8_t branch, bool invert, uint8_t inStream, uint8_t inChannel, float gain);

    // OSD for Scalers
    // Update Settings
    int  setScalerOSDSettings(uint32_t path, MVScalerTopType::OSDSettings * osd_settings);
    void setScalerOSDSettings(uint32_t path, bool use_b, bool osd_enable,
                              uint32_t char_win_h_start, uint32_t char_win_v_start, uint32_t char_win_h_length, uint32_t char_win_v_lines,
                              uint32_t font_h_length, uint32_t font_v_lines, uint32_t font_v_start, uint32_t font_h_scale, uint32_t font_v_scale,
                              uint32_t font_alpha = 8, uint32_t bg_alpha = 8);
    // Char Table
    // Has one setable colour for all characters, default is white
    void setCharTable(uint32_t path, uint32_t idx, uint32_t addr_max, char * char_ptr, char colour = OSD_WHITE);
    // Has one setable colour per character
    void setCharTable(uint32_t path, uint32_t idx, uint32_t addr_max, char* char_ptr, char* colour_ptr);
    // Font Table
    void setFontTable(uint32_t path, uint32_t idx, uint32_t addr_max, uint32_t char_max, uint32_t *data);

    // General Register Functions
    void initGeneral();
    bool getGeneralInitDone();
    int getGeneralFPGAIndex(bool* index);
    int setGeneralFPGAIndex(bool index);
    int setGeneralFPGAReset(bool reset);
    int getGeneralHdmiInHPD(uint8_t index, bool* hpd);
    int getGeneralHdmiOutHPD(uint8_t index, bool* hpd);
    int getGeneralHdmiInCableDetect(uint8_t index, bool* cableDetect);
    int getGeneralHdmiInCableDetectMux(uint8_t index, bool* cableDetect);
    int getGeneralHdmiMuxSelect(uint8_t index, bool* select);
    int setGeneralHdmiMuxSelect(uint8_t index, bool select);
    int getGeneralHdmiOutDisable(uint8_t index, bool* disable);
    int setGeneralHdmiOutDisable(uint8_t index, bool disable);
    int getGeneralHdmiOut5VDisable(uint8_t index, bool* disable);
    int setGeneralHdmiOut5VDisable(uint8_t index, bool disable);
    int getGeneralHdmiBridgeReset(uint8_t index, bool* reset);
    int setGeneralHdmiBridgeReset(uint8_t index, bool reset);
    int getGeneralHdmiPause(bool* pause);
    int setGeneralHdmiPause(bool pause);
    int getGeneralHdmiReset(bool* reset);
    int setGeneralHdmiReset(bool reset);
    int getGeneralUsbReset(bool* reset);
    int setGeneralUsbReset(bool reset);
    int getGeneralXGEClkFrequency(uint32_t* frequency);
    int getGeneral125mhzClkFrequency(uint32_t* frequency);
    int getGeneral62m5hzClkFrequency(uint32_t* frequency);
    int getGeneral312m5hzClkFrequency(uint32_t* frequency);
    int getGeneral156m25hzClkFrequency(uint32_t* frequency);
    int getGeneralHdmiSouthTxClkFrequency(uint32_t* frequency);
    int getGeneralHdmiNorthTxClkFrequency(uint32_t* frequency);
    int getGeneralInterFPGAClkFrequency(uint32_t* frequency);
    int getGeneralDRUClkFrequency(uint32_t* frequency);
    int getGeneralReflockClkFrequency(uint32_t* frequency);
    int getGeneralMgt110Refclk1ClkFrequency(uint32_t* frequency);
    int getGeneralMgt112Refclk1ClkFrequency(uint32_t* frequency);
    int getGeneralUsbPhyMdio(uint32_t phy_addr, uint32_t reg_addr, uint32_t* status);
    int setGeneralUsbPhyMdio(uint32_t phy_addr, uint32_t reg_addr, uint32_t command);
    int getGeneralAnalogMute(bool* mute);
    int setGeneralAnalogMute(bool mute);
    int getGeneralUSBTxSrcSel(bool* src);
    int setGeneralUSBTxSrcSel(bool src);
    int getGeneralSPDIFMute(uint8_t index, bool* mute);
    int setGeneralSPDIFMute(uint8_t index, bool mute);
    int getGeneralI2CExpanderReset(bool* reset);
    int setGeneralI2CExpanderReset(bool reset);
    int getGeneralPbState(bool* pb);
    int getGeneralLedRgb(uint8_t* red, uint8_t* green, uint8_t* blue);
    int setGeneralLedRgb(uint8_t red, uint8_t green, uint8_t blue);
    int getGeneralSupply12vMonitor(uint8_t index, bool* monitor);
    int getGeneralSupplyOrFault(uint8_t index, bool* orfault);
    int getGeneralTRMSelect(bool* select);
    int setGeneralTRMSelect(bool select);
    int getGeneralXgeRxInvertPolarity(uint8_t index, bool* invert);
    int setGeneralXgeRxInvertPolarity(uint8_t index, bool invert);
    int getGeneralXgeTxInvertPolarity(uint8_t index, bool* invert);
    int setGeneralXgeTxInvertPolarity(uint8_t index, bool invert);
    int getGeneralSpiDisplay(uint8_t* data);
    int setGeneralSpiDisplay(uint8_t data);
    int getGeneralToggleSwitch(bool a_not_b, bool* toggle);
    int getGeneralLocalFault(bool* fault);
    int setGeneralLocalFault(bool fault);
    int getGeneralFanFail(bool* fail);
    // Allows DCXO to be specified. si570DefaultFrequency may be omitted if CY29411 is specified
    int initGeneralDCXO(uint8_t index, dcxo_ctrl::dcxo_select_type dcxo, uint32_t si570DefaultFrequency = 0);
    // DCXO determined automatically. si570DefaultFrequency required.
    int initGeneralDCXO(uint8_t index, uint32_t si570DefaultFrequency);
    int setGeneralDCXOClock(uint8_t index, uint32_t frequency, bool cy29411AcceptBestStableFreq = false);
    int setGeneralDCXOLockEnable(uint8_t index, bool value);
    int getGeneralDCXOLockEnable(uint8_t index, bool *value);
    int setGeneralDCXODone(uint8_t index, bool value);
    int getGeneralDCXODone(uint8_t index, bool* value);
    int readGeneralDCXOSelect(uint8_t index, bool* initialized, dcxo_ctrl::dcxo_select_type* dcxo);
    int readGeneralDCXOSettingsCY29411(uint8_t index, bool* valid, cy29411_ctrl::cy29411_settings_type* settings);
    int readGeneralDCXOSettingsSi570(uint8_t index, bool* valid, si570_ctrl::si570_settings_type* settings);

    // InterFPGA Functions

    typedef enum e_interfpgaMgtQuad {
        INTERFPGA_MGT111=0,
        INTERFPGA_MGT109,
        NUM_INTERFPGA_QUADS
    } interfpgaMgtQuad;
    uint8_t mapInterfpgaQuadToIndex(uint8_t quad);
    void initInterfpga(uint8_t quad);
    bool getInterfpgaInitDone(uint8_t quad);
    int getInterfpgaLinkStatus(uint8_t quad, uint8_t chan, bool* status);
    int getInterfpgaLaneStatus(uint8_t quad, uint8_t chan, uint8_t* status);
    int getInterfpgaSoftErrorStatus(uint8_t quad, uint8_t chan, bool* error);
    int getInterfpgaHardErrorStatus(uint8_t quad, uint8_t chan, bool* error);
    int setInterfpgaReset(uint8_t quad, uint8_t chan, bool reset);
    int getInterfpgaIpLinkStatus(uint8_t quad, uint8_t chan, bool* status);
    int getInterfpgaIpLaneStatus(uint8_t quad, uint8_t chan, uint8_t* status);
    int getInterfpgaIpSoftErrorStatus(uint8_t quad, uint8_t chan, bool* error);
    int getInterfpgaIpHardErrorStatus(uint8_t quad, uint8_t chan, bool* error);
    int setInterfpgaIpReset(uint8_t quad, uint8_t chan, bool reset);
    int getInterfpgaTxcErrorCnt(uint8_t quad, uint8_t chan);
    int resetInterfpgaTxcErrorCnt(uint8_t quad, uint8_t chan, bool reset);
    int getInterfpgaTxaErrorCnt(uint8_t quad, uint8_t chan);
    int resetInterfpgaTxaErrorCnt(uint8_t quad, uint8_t chan, bool reset);
    int getInterfpgaTxmErrorCnt(uint8_t quad, uint8_t chan);
    int resetInterfpgaTxmErrorCnt(uint8_t quad, uint8_t chan, bool reset);
    int getInterfpgaTxuErrorCnt(uint8_t quad, uint8_t chan);
    int resetInterfpgaTxuErrorCnt(uint8_t quad, uint8_t chan, bool reset);
    int getInterfpgaTxvErrorCnt(uint8_t quad, uint8_t chan);
    int resetInterfpgaTxvErrorCnt(uint8_t quad, uint8_t chan, bool reset);

    // 12G SDI
    void initSDI12G();
    bool getSDI12GInitDone();
    int  getSDI12GYasCodeFractional(bool fractional, SDI_12G::sdi_yas_code_type input_yascode, SDI_12G::sdi_yas_code_type* output_yascode);
    void getSDI12GPTPLock(bool* enable);
    void setSDI12GPTPLock(bool enable);
    void setSDI12GPTPReferenceLockReset();
    void getSDI12GPTPReferenceLockLocked(bool* locked);
    void getSDI12GGenlockLock(bool* enable);
    void setSDI12GGenlockLock(bool enable);
    void setSDI12GGenlockReferenceLockReset();
    void getSDI12GGenlockReferenceLockLocked(bool* locked);
    void dumpSDI12GReferenceLockStatus();
    int  getSDI12G148M500HzClockFrequency(uint32_t* clockFrequency);
    int  getSDI12G148M350HzClockFrequency(uint32_t* clockFrequency);
    int  getSDI12GFractional(bool* fractional);
    int  setSDI12GFractional(bool fractional, bool force = false);
    // Allows DCXO to be specified. si570DefaultFrequency may be omitted if CY29411 is specified.
    int  initSDI12GDCXO(uint8_t index, dcxo_ctrl::dcxo_select_type dcxo, uint32_t si570DefaultFrequency = 0);
    // DCXO determined automatically. si570DefaultFrequency required.
    int  initSDI12GDCXO(uint8_t index, uint32_t si570DefaultFrequency);
    int  setSDI12GDCXOClock(uint8_t index, uint32_t frequency);
    int  setSDI12GDCXOLockEnable(uint8_t index, bool value);
    int  getSDI12GDCXOLockEnable(uint8_t index, bool* value);
    int  setSDI12GDCXODone(uint8_t index, bool value);
    int  getSDI12GDCXODone(uint8_t index, bool* value);
    int  readSDI12GDCXOSettings(uint8_t index, bool* valid, si570_ctrl::si570_settings_type* settings);
    int  getSDI12GPTPEnable(bool* enable);
    int  setSDI12GPTPEnable(bool enable);
    int  getSDI12GGenlockEnable(bool* enable);
    int  setSDI12GGenlockEnable(bool enable);
    int  getSDI12GReferenceLockError(uint32_t* error);
    int  getSDI12GReferenceLockLocked(bool* locked);
    int  setSDI12GReferenceLockReset();
    int  setSDI12GRxReset(uint32_t chan, bool reset);
    int  setSDI12GTxReset(uint32_t chan, bool reset);
    int  setSDI12GRxGTXReset(uint32_t chan, bool reset);
    int  setSDI12GTxGTXReset(uint32_t chan, bool reset);
    int  getSDI12GRxDetectDisable(uint32_t chan, bool* disable);
    int  setSDI12GRxDetectDisable(uint32_t chan, bool disable);
    int  getSDI12GRxForcedMode(uint32_t chan, uint8_t* mode);
    int  setSDI12GRxForcedMode(uint32_t chan, uint8_t mode);
    int  getSDI12GStatus(uint32_t chan, SDI_12G::sdi_status_type* SdiStatus);
    int  getSDI12GRxRaster(uint32_t chan, SDI_12G::sdi_rx_raster_type* SdiRxRaster);
    int  getSDI12GRxRasterError(uint32_t chan, SDI_12G::sdi_rx_raster_error_type* SdiRxRasterError);
    int  getSDI12GRxAudioInformation(uint32_t chan, SDI_12G::sdi_rx_audio_information_type* SdiRxAudioInformation);
    int  getSDI12GRxAudioGroupPresent(uint32_t chan, uint32_t group, bool* SdiRxAudioGroupPresent);
    int  getSDI12GRxAudioGroupError(uint32_t chan, uint32_t group, bool* SdiRxAudioGroupError);
    int  getSDI12GRxAudioGroupRate(uint32_t chan, uint32_t group, SDI_12G::sdi_rx_audio_rate* SdiRxAudioGroupRate);
    int  getSDI12GRxAudioChannelActive(uint32_t chan, uint32_t channel, bool* SdiRxAudioChannelActive);
    int  getSDI12GRxVPIDY(uint32_t chan, uint32_t* SdiRxVPID);
    int  getSDI12GRxVPIDC(uint32_t chan, uint32_t* SdiRxVPID);
    int  setSDI12GRxCRCErrorClear(uint32_t chan);
    int  getSDI12GRxCRCErrorCount(uint32_t chan, uint32_t* SdiRxCRCErrorCount);
    int  getSDI12GTxYasCode(uint32_t chan, SDI_12G::sdi_yas_code_type* SdiTxYasCode);
    int  setSDI12GTxYasCode(uint32_t chan, SDI_12G::sdi_yas_code_type SdiTxYasCode);
    int  setSDI12GTxMuxSelect(uint32_t chan, uint8_t SdiTxMuxSelect);
    int  setSDI12GTxAudioGroupEnable(uint32_t chan, uint32_t group, bool SdiTxAudioGroupEnable);
    int  setSDI12GTxAudioChannelEnable(uint32_t chan, uint32_t channel, bool SdiTxAudioChannelEnable);
    int  getSDI12GTxVpidData(uint32_t chan, uint32_t* SdiTxVpidData);
    int  setSDI12GTxVpidData(uint32_t chan, uint32_t SdiTxVpidData);
    int  setSDI12GTxVpidInsertLine(uint32_t chan, uint16_t SdiTxVpidInsertLineField0, uint16_t SdiTxVpidInsertLineField1);
    int  getSDI12GTxStatus(uint32_t chan, SDI_12G::sdi_tx_status_type* SdiTxStatus);
    int  getSDI12GTx2SIEnable(uint32_t chan, bool* SdiTx2SIEnable);
    int  setSDI12GTx2SIEnable(uint32_t chan, bool SdiTx2SIEnable);
    int  getSDI12GTx2SIBypass(uint32_t chan, bool* SdiTx2SIBypass);
    int  setSDI12GTx2SIBypass(uint32_t chan, bool SdiTx2SIBypass);
    int  getSDI12GRx2SIEnable(uint32_t chan, bool* SdiRx2SIEnable);
    int  getSDI12GRx2SIBypass(uint32_t chan, bool* SdiRx2SIBypass);
    int  setSDI12GRx2SIBypass(uint32_t chan, bool SdiRx2SIBypass);
    int  getSDI12GRxActiveStreams(uint32_t chan, uint8_t* SdiRxActiveStreams);
    int  getSDI12GRxUsrclockFrequency(uint32_t chan, uint32_t* clockFrequency);
    int  getSDI12GTxUsrclockFrequency(uint32_t chan, uint32_t* clockFrequency);

    // Definitions to match hardware instantiations.
    const uint32_t N_SCALER_PATHS = 2;
    const uint32_t N_FRAME_BUFFER_PATHS = 2;
    const uint32_t N_PIP_SCALER_PATHS = 3;
    const uint32_t N_PIP_VIDEO_MIXER = 1;
    const uint32_t N_TOTAL_10GE_CHANNELS = 4;
    const uint32_t N_10GE_CHANNELS = 4;
    const uint32_t N_HDMI_CHANS = 2;
    const uint32_t N_MEM_BANKS = 2;
    const uint32_t N_SDI_12G = 2;

    // Scaler raster phase adjusted pixels to arrive in pip video mixer in time for output. Experimental and measured result of delay.
    const uint32_t pip_scaler_raster_buffer_phase = 64;
    // Scaler raster phase for pip paths to support additional buffering requirements to handle 4K60 half horizontal system
    const uint32_t pip_scaler_raster_buffer_phase_pip_path_high_rate = 1090;
     // Single scaler paths pixel clock rate limit
    const uint32_t pip_scaler_path_pixel_clock_limit = 297000000;

    //SCALER
    static const uint32_t SC_NUM_PATHS = N_SCALER_PATHS+N_FRAME_BUFFER_PATHS+N_PIP_SCALER_PATHS;
    static const uint32_t SC_WIDTH_COMPONENT = 11;
    typedef enum e_ScComponentIdx {
        SC_COMP_IDX_SCALER_A=0,
        SC_COMP_IDX_SCALER_B,
        SC_COMP_IDX_RASTER,
        SC_COMP_IDX_MISC,
        SC_COMP_IDX_WPORT_0,
        SC_COMP_IDX_PLAYOUT,
        SC_COMP_IDX_WPORT_1,
        SC_COMP_IDX_WPORT_2,
        SC_COMP_IDX_WPORT_3,
        SC_NUM_COMPONENTS
    } ScComponentIdx;

    // Scaler Frame Buffer Array Remap
    static const uint32_t SC_BASE_ADDR[HW_API::SC_NUM_PATHS][HW_API::SC_NUM_COMPONENTS] =
    { // Scaler 0
      { SCAS0_BASE_ADDR,  // scaler a
        SCBS0_BASE_ADDR,  // scaler b
        SCRS0_BASE_ADDR,  // scaler raster programming
        SCMS0_BASE_ADDR,  // miscellaneous
        SCWA0_BASE_ADDR,  // write port 0
        SCPL0_BASE_ADDR,  // playout programming
        SCWB0_BASE_ADDR,  // write port 1
        SCWC0_BASE_ADDR,  // write port 2
        SCWD0_BASE_ADDR}, // write port 3
      // Scaler 1
      { SCAS1_BASE_ADDR,  // scaler a
        SCBS1_BASE_ADDR,  // scaler b
        SCRS1_BASE_ADDR,  // scaler raster programming
        SCMS1_BASE_ADDR,  // miscellaneous
        SCWA1_BASE_ADDR,  // write port 0
        SCPL1_BASE_ADDR,  // playout programming
        SCWB1_BASE_ADDR,  // write port 1
        SCWC1_BASE_ADDR,  // write port 2
        SCWD1_BASE_ADDR}, // write port 3
      // Scaler 2
      { SCAS2_BASE_ADDR,  // scaler a
        SCBS2_BASE_ADDR,  // scaler b
        SCRS2_BASE_ADDR,  // scaler raster programming
        SCMS2_BASE_ADDR,  // miscellaneous
        SCWA2_BASE_ADDR,  // write port 0
        SCPL2_BASE_ADDR,  // playout programming
        SCWB2_BASE_ADDR,  // write port 1
        SCWC2_BASE_ADDR,  // write port 2
        SCWD2_BASE_ADDR}, // write port 3
      // Scaler 3
      { SCAS3_BASE_ADDR,  // scaler a
        SCBS3_BASE_ADDR,  // scaler b
        SCRS3_BASE_ADDR,  // scaler raster programming
        SCMS3_BASE_ADDR,  // miscellaneous
        SCWA3_BASE_ADDR,  // write port 0
        SCPL3_BASE_ADDR,  // playout programming
        SCWB3_BASE_ADDR,  // write port 1
        SCWC3_BASE_ADDR,  // write port 2
        SCWD3_BASE_ADDR}, // write port 3
      // Scaler 4
      { SCAS4_BASE_ADDR,  // scaler a
        SCBS4_BASE_ADDR,  // scaler b
        SCRS4_BASE_ADDR,  // scaler raster programming
        SCMS4_BASE_ADDR,  // miscellaneous
        SCWA4_BASE_ADDR,  // write port 0
        SCPL4_BASE_ADDR,  // playout programming
        SCWB4_BASE_ADDR,  // write port 1
        SCWC4_BASE_ADDR,  // write port 2
        SCWD4_BASE_ADDR}, // write port 3
      // Scaler 5
      { SCAS5_BASE_ADDR,  // scaler a
        SCBS5_BASE_ADDR,  // scaler b
        SCRS5_BASE_ADDR,  // scaler raster programming
        SCMS5_BASE_ADDR,  // miscellaneous
        SCWA5_BASE_ADDR,  // write port 0
        SCPL5_BASE_ADDR,  // playout programming
        SCWB5_BASE_ADDR,  // write port 1
        SCWC5_BASE_ADDR,  // write port 2
        SCWD5_BASE_ADDR}, // write port 3
      // Scaler 6
      { SCAS6_BASE_ADDR,  // scaler a
        SCBS6_BASE_ADDR,  // scaler b
        SCRS6_BASE_ADDR,  // scaler raster programming
        SCMS6_BASE_ADDR,  // miscellaneous
        SCWA6_BASE_ADDR,  // write port 0
        SCPL6_BASE_ADDR,  // playout programming
        SCWB6_BASE_ADDR,  // write port 1
        SCWC6_BASE_ADDR,  // write port 2
        SCWD6_BASE_ADDR}  // write port 3
    };
    static const uint32_t SC_HIGH_ADDR[HW_API::SC_NUM_PATHS][HW_API::SC_NUM_COMPONENTS] =
    { { SC_BASE_ADDR[0][0]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1, // scaler a
        SC_BASE_ADDR[0][1]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1, // scaler b
        SC_BASE_ADDR[0][2]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1, // scaler raster programming
        SC_BASE_ADDR[0][3]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1, // miscellaneous
        SC_BASE_ADDR[0][4]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1, // write port 0
        SC_BASE_ADDR[0][5]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1, // playout programming
        SC_BASE_ADDR[0][6]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1, // write port 1
        SC_BASE_ADDR[0][7]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1, // write port 2
        SC_BASE_ADDR[0][8]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1  // write port 3
      },
      { SC_BASE_ADDR[1][0]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[1][1]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[1][2]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[1][3]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[1][4]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[1][5]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[1][6]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[1][7]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[1][8]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1
      },
      { SC_BASE_ADDR[2][0]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[2][1]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[2][2]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[2][3]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[2][4]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[2][5]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[2][6]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[2][7]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[2][8]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1
      },
      { SC_BASE_ADDR[3][0]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[3][1]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[3][2]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[3][3]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[3][4]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[3][5]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[3][6]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[3][7]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[3][8]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1
      },
      { SC_BASE_ADDR[4][0]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[4][1]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[4][2]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[4][3]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[4][4]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[4][5]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[4][6]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[4][7]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[4][8]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1
      },
      { SC_BASE_ADDR[5][0]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[5][1]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[5][2]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[5][3]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[5][4]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[5][5]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[5][6]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[5][7]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[5][8]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1
      },
      { SC_BASE_ADDR[6][0]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[6][1]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[6][2]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[6][3]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[6][4]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[6][5]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[6][6]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[6][7]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1,
        SC_BASE_ADDR[6][8]+(2<<(HW_API::SC_WIDTH_COMPONENT-1))-1
      }
    };
    static const uint32_t SC_BYTE_ADDR[HW_API::SC_NUM_PATHS][HW_API::SC_NUM_COMPONENTS] =
    { { 4, // scaler a
        4, // scaler b
        4, // scaler raster programming
        4, // miscellaneous
        4, // write port 0
        4, // playout programming
        4, // write port 1
        4, // write port 2
        4  // write port 3
      },
      {4,4,4,4,4,4,4,4,4},
      {4,4,4,4,4,4,4,4,4},
      {4,4,4,4,4,4,4,4,4},
      {4,4,4,4,4,4,4,4,4},
      {4,4,4,4,4,4,4,4,4},
      {4,4,4,4,4,4,4,4,4}
    };


    // XGE
    const uint32_t N_XGE = 2;
    const uint32_t N_XGE_INTER_IP_RX = 2;
    const uint32_t N_XGE_INTER_IP_TX = 1;

    // XGE RX
    const uint32_t N_XGE_RX_VID_ASPENTICO = 4; // 4:2:2/4:4:4/TICO is autodetected
    const uint32_t N_XGE_RX_VID_SMPTE2110 = 2;
    const uint32_t N_XGE_RX_VID = N_XGE_RX_VID_ASPENTICO + N_XGE_RX_VID_SMPTE2110;
    const uint32_t N_XGE_RX_AUD = 4;
    const uint32_t N_XGE_RX_AUD_CH = 2;
    const uint32_t N_XGE_RX_META = 4;
    const uint32_t N_XGE_RX_PCR = 1;
    const uint32_t N_XGE_RX_USB = 1;
    const uint32_t N_XGE_RX_LOWRATE = 0;
    const uint32_t N_XGE_RX = N_XGE+N_XGE_INTER_IP_RX;
    const uint32_t IP_CAM_DEPTH = 9;
    const uint32_t N_CHANNELS_RX = 16;

    // XGE TX
    const uint32_t N_XGE_TX_VID_ASPEN422 = 2;
    const uint32_t N_XGE_TX_VID_ASPEN444 = 2;
    const uint32_t N_XGE_TX_VID_TICO = 2;
    const uint32_t N_XGE_TX_VID_SMPTE2110 = 2;
    const uint32_t N_XGE_TX_VID = N_XGE_TX_VID_ASPEN422 +
                                  N_XGE_TX_VID_ASPEN444 +
                                  N_XGE_TX_VID_TICO +
                                  N_XGE_TX_VID_SMPTE2110;
    const uint32_t N_XGE_TX_AUD = 3;
    const uint32_t N_XGE_TX_AUD_CH = 2;
    const uint32_t N_XGE_TX_AUD_STR = (N_XGE_TX_AUD_CH+3)/4;
    const uint32_t N_XGE_TX_META = 2;
    const uint32_t N_XGE_TX_USB = 1;
    const uint32_t N_XGE_TX_LOWRATE = 0;
    const uint32_t N_XGE_TX_PCR = 0;
    const uint32_t N_XGE_TX = N_XGE+N_XGE_INTER_IP_TX;
    const uint32_t N_CHANNELS_TX = 16;

    // XBAR parameters - Update the enumerations to correctly change these values.
    const uint32_t N_AUD_XBAR_IN       = N_AUD_IN;
    const uint32_t N_AUD_XBAR_OUT      = N_AUD_OUT;
    const uint32_t N_VID_XBAR_IN       = N_VID_IN;
    const uint32_t N_VID_XBAR_OUT      = N_VID_OUT;
    const uint32_t N_META_XBAR_IN      = N_META_IN;
    const uint32_t N_META_XBAR_OUT     = N_META_OUT;

    // Presence Detection parameters
    const uint32_t THRESH_WIDTH        = 18;
    const uint32_t UNDER_DUR_WIDTH     = 20;
    const uint32_t UNDER_THRESH        = 828;   // -50 dBFS
    const uint32_t UNDER_DURATION      = 96000; // 2 seconds

    // Constant video parameters
    const uint32_t CORE_CLK_FREQ_HZ    = 200000000;
    const uint32_t PIXELS_PER_CLOCK    = 4;
    const uint32_t BITS_PER_PIXEL      = 30;
    const uint32_t ASPEN_TX_BUS_WIDTH  = 32;

    // Constant Audio Mixer parameters
    const uint8_t  INTEGER_BITS        = 4;
    const uint8_t  FLOAT_BITS          = 12;
    const uint8_t  OUTPUT_CHAN_ID      = 2;
    const uint8_t  MIXER_BRANCH        = 16;
    const uint32_t NUM_MIXERS          = 2;
}
#endif // HW_API_H
// vim:set sts=2 sw=2 expandtab fileformat=unix:
