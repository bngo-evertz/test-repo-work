#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <arpa/inet.h>
#include <limits>

#include "hw_api.h"
#include "zynq_font_table.h"

/* -- Typedefs and Constants -- */

typedef struct s_subCommand {
    const char *command;
    int (*function)(int n, char *s[]);
} SubCommand;

/* -- Subcommands -- */

static int
execBuildInfo(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s sw\n", s[0]);
        printf("       %s fpga\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        if (!strcmp(s[1], "sw")) {
            printf("SW Identification Information:\n");
            printf("  Build Time: ");
            printf("%s | %s\n",__DATE__,__TIME__);
            pvalid = true;
        } else if (!strcmp(s[1], "fpga")) {
            HW_API::initFPGABuildID();
            HW_API::dumpFPGABuildID();
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

uint8_t Edid[256] = {
    0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,  0x16, 0x8c, 0x87, 0x08, 0x67, 0x45, 0x23, 0x01,
    0x01, 0x1d, 0x01, 0x03, 0x80, 0xa0, 0x5a, 0x78,  0x0a, 0x08, 0xa5, 0xa2, 0x57, 0x4f, 0xa2, 0x28,
    0x0f, 0x50, 0x54, 0xff, 0xee, 0x80, 0xd1, 0xc0,  0xd1, 0x00, 0x81, 0xc0, 0x81, 0x00, 0xa9, 0x40,
    0x3b, 0x40, 0x90, 0x19, 0x81, 0x99, 0x08, 0xe8,  0x00, 0x30, 0xf2, 0x70, 0x5a, 0x80, 0xb0, 0x58,
    0x8a, 0x00, 0xa0, 0x5a, 0x00, 0x00, 0x00, 0x1e,  0x02, 0x3a, 0x80, 0x18, 0x71, 0x38, 0x2d, 0x40,
    0x58, 0x2c, 0x45, 0x00, 0xa0, 0x5a, 0x00, 0x00,  0x00, 0x1e, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x4d,
    0x4d, 0x41, 0x31, 0x30, 0x47, 0x2d, 0x54, 0x52,  0x4d, 0x34, 0x4b, 0x0a, 0x00, 0x00, 0x00, 0xfd,
    0x00, 0x18, 0x4b, 0x0f, 0x51, 0x1e, 0x00, 0x0a,  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x1b,
    0x02, 0x03, 0x3e, 0x71, 0x5a, 0x03, 0x04, 0x10,  0x12, 0x13, 0x1f, 0x20, 0x21, 0x22, 0x5a, 0x5d,
    0x5e, 0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65,  0x66, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x23,
    0x09, 0x7f, 0x07, 0x83, 0x01, 0x00, 0x00, 0x6e,  0x03, 0x0c, 0x00, 0x10, 0x00, 0x18, 0x3c, 0x20,
    0x00, 0x80, 0x01, 0x02, 0x03, 0x04, 0x67, 0xd8,  0x5d, 0xc4, 0x01, 0x78, 0x88, 0x00, 0x08, 0xe8,
    0x00, 0x30, 0xf2, 0x70, 0x5a, 0x80, 0xb0, 0x58,  0x8a, 0x00, 0x20, 0xc2, 0x31, 0x00, 0x00, 0x1e,
    0x02, 0x3a, 0x80, 0x18, 0x71, 0x38, 0x2d, 0x40,  0x58, 0x2c, 0x45, 0x00, 0x20, 0xc2, 0x31, 0x00,
    0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x95
};

static int
execBIST(int n, char *s[])
{
    bool pvalid = false;
    if (n == 1) {
        printf("Usage: %s sleep\n", s[0]);
        printf("       %s mutex\n", s[0]);
        printf("       %s reg\n", s[0]);
        printf("       %s mem <bank> <fast> <depth_div>\n", s[0]);
        printf("       %s mem_addrstress <bank> <fast> <depth_div>\n", s[0]);
        printf("       %s mem_hammer <bank> <iterations>\n", s[0]);
        printf("       %s xge_mac\n", s[0]);
        printf("       %s xge_link\n", s[0]);
        printf("       %s temac\n", s[0]);
        printf("       %s xge_rx <sfp_a> <sfp_b> <redun> <srtp>\n", s[0]);
        printf("       %s xge_tx <sfp_a> <sfp_b> <srtp> [bw]\n", s[0]);
        printf("       %s xge_tx <sfp_a> <sfp_b> <srtp> [bw] [aspen422] [aspen444] [tico] [smpte2110] [audio] [source colour] [meta] [eotf] [colour_space] [usb]\n", s[0]);
        printf("       %s xge_usb <sfp_a> <sfp_b> <redun>\n", s[0]);
        printf("       %s xge_pcr <sfp_a> <sfp_b> <redun> <srtp> [remote]\n", s[0]);
        printf("       %s scaler <path> <bw>\n", s[0]);
        printf("       %s scaler <path> <bwin> <colour_inp> <bwout> <colour_out> <lock_enable>\n", s[0]);
        printf("       %s gearboxrx <bw>\n", s[0]);
        printf("       %s capability\n", s[0]);
        printf("       %s hdmi_tx <txchan> <bw> <colour> <fractional>\n", s[0]);
        printf("       %s hdmi_loopback <rxchan> <txchan> <bw>\n", s[0]);
        printf("       %s hdmi_link <rxchan> <txchan> <bw> <path> <fast>\n", s[0]);
        printf("       %s hdmi_rxlinkerror <rxchan> <fast>\n", s[0]);
        printf("\n");
        printf("   where sfp          = sfp idx (0-1)\n");
        printf("         bank         = memory bank (0 = HP, 1 = HR)\n");
        printf("         fast         = fast vs slow memory suites (0-1)\n");
        printf("         depth_div    = mem test depth div exponent\n");
        printf("         iterations   = number of iterations to run the stress test\n");
        printf("         rxchan       = hdmi rx index\n");
        printf("         txchan       = hdmi tx index\n");
        printf("         path         = video path index\n");
        printf("         interlaced   = interlace flag (0-1)\n");
        printf("         redun        = redundancy enable (0-1)\n");
        printf("         bw           = 0 = 1080p60, 1 = 1080i60, 2 = 2160p30, 3 = 2160p60, 4 = 1080p30, 5 = 2160p24, 6 = 2160p23.98, 7 = 2160p59.94, 8 = 2160p29.98, 9 = 1080p59.94\n");
        printf("         colour       = 0 = rgb, 1 = ycc444, 2 = ycc422\n");
        printf("         eotf         = 0 = default, 1 = pq, 2 = hlg\n");
        printf("         colour_space = 0 = default, 1 = 601, 2 = 709, 3 = 2020\n");
        printf("         lock_enable  = 0 = no lock, 1 = scaler output tracks input rate and phase\n");
        printf("         fractional   = 0 = non-fractional (ie 60 Hz), 1 = fractional (ie 59.94 Hz\n");
        printf("         aspen422     = 0 = disabled, 1 = enabled (optional, but if used aspen422,aspen444,tico,audio must all be specified)\n");
        printf("         aspen444     = 0 = disabled, 1 = enabled (optional, but if used aspen422,aspen444,tico,audio must all be specified)\n");
        printf("         tico         = 0 = disabled, 1 = enabled (optional, but if used aspen422,aspen444,tico,audio must all be specified)\n");
        printf("         audio        = 0 = disabled, 1 = enabled (optional, but if used aspen422,aspen444,tico,audio must all be specified)\n");
        printf("         rxIp         = specifies 239.0.4.x (optional, but if specified both rxIp and txIp must be\n");
        printf("         txIp         = specifies 239.0.4.x (optional, but if specified both rxIp and txIp must be\n");
        pvalid = true;
    } else if (n == 2) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "sleep")) {
            HW_API::bistSleep();
            pvalid = true;
        } else if (!strcmp(s[1], "mutex")) {
            HW_API::bistMutex();
            pvalid = true;
        } else if (!strcmp(s[1], "reg")) {
            HW_API::bistReg();
            pvalid = true;
        } else if (!strcmp(s[1], "xge_mac")) {
            HW_API::bist10GEMac();
            pvalid = true;
        } else if (!strcmp(s[1], "xge_link")) {
            HW_API::bist10GEMacLinkUp();
            pvalid = true;
        } else if (!strcmp(s[1], "temac")) {
            HW_API::bistTEMAC();
            pvalid = true;
        } else if (!strcmp(s[1], "capability")) {
            HW_API::bistCapability();
            pvalid = true;
        }
    } else if (n == 3) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "gearboxrx")) {
            uint32_t bw = strtoul(s[2], NULL, 0)%HW_API::NUM_BIST_BW;
            HW_API::bistGearboxRx((HW_API::bwBIST)bw, HW_API::CSF_RGB);
            pvalid = true;
        }
    } else if (n == 4) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "scaler")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            uint32_t bw = strtoul(s[3], NULL, 0)%HW_API::NUM_BIST_BW;
            HW_API::bistScaler(path, (HW_API::bwBIST)bw, HW_API::CSF_RGB, (HW_API::bwBIST)bw, HW_API::CSF_RGB);
            pvalid = true;
        } else if (!strcmp(s[1], "mem_hammer")) {
            uint32_t bank = strtoul(s[2], NULL, 0);
            uint32_t iterations = strtoul(s[3], NULL, 0);
            HW_API::bistMemAddressHammer(bank, iterations);
            pvalid = true;
        } else if (!strcmp(s[1], "hdmi_rxlinkerror")) {
            uint32_t rxchan = strtoul(s[2], NULL, 0);
            uint32_t fast = strtoul(s[3], NULL, 0);
            HW_API::bistHdmiRxLinkError(rxchan, fast);
            pvalid = true;
        }
    } else if (n == 5) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "mem")) {
            uint32_t bank = strtoul(s[2], NULL, 0);
            uint32_t fast = strtoul(s[3], NULL, 0);
            uint32_t depth_div = strtoul(s[4], NULL, 0);
            HW_API::bistMem(bank, depth_div, (fast > 0));
            pvalid = true;
        } else if (!strcmp(s[1], "mem_addrstress")) {
            uint32_t bank = strtoul(s[2], NULL, 0);
            uint32_t fast = strtoul(s[3], NULL, 0);
            uint32_t depth_div = strtoul(s[4], NULL, 0);
            HW_API::bistMemAddrStress(bank, depth_div, (fast > 0));
            pvalid = true;
        } else if (!strcmp(s[1], "xge_tx")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t srtp = strtoul(s[4], NULL, 0);
            // Defaults to 4K30, aspen422, tico, audio
            HW_API::bist10GETx(sfp_a, sfp_b, srtp);
            pvalid = true;
        } else if(!strcmp(s[1], "hdmi_loopback")) {
            uint32_t rxchan = strtoul(s[2], NULL, 0);
            uint32_t txchan = strtoul(s[3], NULL, 0);
            uint32_t bw = strtoul(s[4], NULL, 0)%HW_API::NUM_BIST_BW;
            HW_API::bistHdmiLoopback(rxchan, txchan, (HW_API::bwBIST)bw);
            pvalid = true;
        }
    } else if (n == 6) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "xge_rx")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t redun = strtoul(s[4], NULL, 0);
            uint32_t srtp = strtoul(s[5], NULL, 0);
            HW_API::bist10GERx(sfp_a, sfp_b, redun, srtp);
            pvalid = true;
        } else if (!strcmp(s[1], "xge_tx")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t srtp = strtoul(s[4], NULL, 0);
            uint32_t vstd = strtoul(s[5], NULL, 0);
            // Defaults to aspen422, audio
            HW_API::bist10GETx(sfp_a,sfp_b,srtp,vstd);
            pvalid = true;
        } else if (!strcmp(s[1], "xge_usb")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t redun = strtoul(s[4], NULL, 0);
            uint32_t srtp = strtoul(s[5], NULL, 0);
            HW_API::bist10GEUSB(sfp_a, sfp_b, redun, srtp);
            pvalid = true;
        } else if (!strcmp(s[1], "xge_pcr")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t redun = strtoul(s[4], NULL, 0);
            uint32_t srtp = strtoul(s[5], NULL, 0);
            HW_API::bist10GEPCR(sfp_a, sfp_b, redun, srtp);
            pvalid = true;
        } else if(!strcmp(s[1], "hdmi_tx")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            uint32_t bw = strtoul(s[3], NULL, 0)%HW_API::NUM_BIST_BW;
            uint32_t colour = strtoul(s[4], NULL, 0);
            bool fractional = strtoul(s[5], NULL, 0);
            HW_API::bistHdmiTx(path, (HW_API::bwBIST)bw, fractional, (HW_API::scColourFormat_type)colour);
            pvalid = true;
        }
    } else if (n == 7) {
        HW_API::initFPGABuildID();
        if(!strcmp(s[1], "hdmi_link")) {
            uint32_t rxchan = strtoul(s[2], NULL, 0);
            uint32_t txchan = strtoul(s[3], NULL, 0);
            uint32_t bw = strtoul(s[4], NULL, 0)%HW_API::NUM_BIST_BW;
            uint32_t path = strtoul(s[5], NULL, 0);
            bool fast = (bool)strtoul(s[6], NULL, 0);
            HW_API::bistHdmiLink(rxchan, txchan, (HW_API::bwBIST)bw, path, Edid, fast);
            pvalid = true;
        } else if (!strcmp(s[1], "xge_pcr")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t redun = strtoul(s[4], NULL, 0);
            uint32_t srtp = strtoul(s[5], NULL, 0);
            bool remote = strtoul(s[6], NULL, 0);
            HW_API::bist10GEPCR(sfp_a, sfp_b, redun, srtp, remote);
            pvalid = true;
        }
    } else if (n == 8) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "scaler")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            uint32_t bw_in = strtoul(s[3], NULL, 0)%HW_API::NUM_BIST_BW;
            uint32_t colour_inp = strtoul(s[4], NULL, 0);
            uint32_t bw_out = strtoul(s[5], NULL, 0)%HW_API::NUM_BIST_BW;
            uint32_t colour_out = strtoul(s[6], NULL, 0);
            uint32_t lock = strtoul(s[7], NULL, 0)%HW_API::NUM_BIST_BW;
            uint8_t hdmi_idx;
            HW_API::bistScaler(path, (HW_API::bwBIST)bw_in, (HW_API::scColourFormat_type)colour_inp, (HW_API::bwBIST)bw_out, (HW_API::scColourFormat_type)colour_out);
            printf("Lock Enable = %s\n", lock?"true":"false");
            // Check if Scaler is associated with a HDMI output. (Checking if path is above number of HDMI outputs)
            if ((path+1) <= ((uint32_t)HW_API::getFPGACapability("INC_HDMI_NORTH_TX") + (uint32_t)HW_API::getFPGACapability("INC_HDMI_SOUTH_TX"))){
              hdmi_idx = path;
              HW_API::initHdmi(hdmi_idx);
              HW_API::setHdmiTxSi570LockEnable(hdmi_idx, lock);
              if (lock) {
                printf("Enable Locking on HDMI Output %u\n", hdmi_idx);
              }
            }
            HW_API::setScalerVidLockEnable(path, lock);
            pvalid = true;
        }
    } else if (n == 11) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "xge_tx")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t srtp = strtoul(s[4], NULL, 0);
            uint32_t vstd = strtoul(s[5], NULL, 0);
            uint32_t aspen422 = strtoul(s[6], NULL, 0)%2;
            uint32_t aspen444 = strtoul(s[7], NULL, 0)%2;
            uint32_t tico = strtoul(s[8], NULL, 0)%2;
            uint32_t smpte2110 = strtoul(s[9], NULL, 0)%2;
            uint32_t audio = strtoul(s[10], NULL, 0)%2;
            HW_API::bist10GETx(sfp_a,sfp_b,srtp,vstd,aspen422,aspen444,tico,smpte2110,audio);
            pvalid = true;
        }
    } else if (n == 13) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "xge_tx")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t srtp = strtoul(s[4], NULL, 0);
            uint32_t vstd = strtoul(s[5], NULL, 0);
            uint32_t aspen422 = strtoul(s[6], NULL, 0)%2;
            uint32_t aspen444 = strtoul(s[7], NULL, 0)%2;
            uint32_t tico = strtoul(s[8], NULL, 0)%2;
            uint32_t smpte2110 = strtoul(s[9], NULL, 0)%2;
            uint32_t audio = strtoul(s[10], NULL, 0)%2;
            uint8_t colour = strtoul(s[11], NULL, 0);
            uint32_t meta = strtoul(s[12], NULL, 0)%2;
            HW_API::XTxColourSpecification clr_spec_inp;
            HW_API::XTxSampleStructure smp_struct_inp;
            switch(colour) {
              case 1:
                clr_spec_inp = HW_API::C_REC709;
                smp_struct_inp = HW_API::S_444;
                break;
              case 2:
                clr_spec_inp = HW_API::C_REC709;
                smp_struct_inp = HW_API::S_422;
                break;
              case 0:
              default:
                clr_spec_inp = HW_API::C_SRGB;
                smp_struct_inp = HW_API::S_444;
                break;
            }
            HW_API::bist10GETx(sfp_a,sfp_b,srtp,vstd,aspen422,aspen444,tico,smpte2110,audio,clr_spec_inp,smp_struct_inp,meta);
            pvalid = true;
        }
    } else if (n == 14) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "xge_tx")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t srtp = strtoul(s[4], NULL, 0);
            uint32_t vstd = strtoul(s[5], NULL, 0);
            uint32_t aspen422 = strtoul(s[6], NULL, 0)%2;
            uint32_t aspen444 = strtoul(s[7], NULL, 0)%2;
            uint32_t tico = strtoul(s[8], NULL, 0)%2;
            uint32_t smpte2110 = strtoul(s[9], NULL, 0)%2;
            uint32_t audio = strtoul(s[10], NULL, 0)%2;
            uint8_t colour = strtoul(s[11], NULL, 0);
            uint32_t meta = strtoul(s[12], NULL, 0)%2;
            uint8_t eotf = strtoul(s[13], NULL, 0);
            HW_API::XTxColourSpecification clr_spec_inp;
            HW_API::XTxSampleStructure smp_struct_inp;
            switch(colour) {
              case 1:
                clr_spec_inp = HW_API::C_REC709;
                smp_struct_inp = HW_API::S_444;
                break;
              case 2:
                clr_spec_inp = HW_API::C_REC709;
                smp_struct_inp = HW_API::S_422;
                break;
              case 0:
              default:
                clr_spec_inp = HW_API::C_SRGB;
                smp_struct_inp = HW_API::S_444;
                break;
            }
            HW_API::bist10GETx(sfp_a,sfp_b,srtp,vstd,aspen422,aspen444,tico,smpte2110,audio,clr_spec_inp,smp_struct_inp,meta,(HW_API::XTxElectroopticalTransferFunction)eotf);
            pvalid = true;
        }
    } else if (n == 15) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "xge_tx")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t srtp = strtoul(s[4], NULL, 0);
            uint32_t vstd = strtoul(s[5], NULL, 0);
            uint32_t aspen422 = strtoul(s[6], NULL, 0)%2;
            uint32_t aspen444 = strtoul(s[7], NULL, 0)%2;
            uint32_t tico = strtoul(s[8], NULL, 0)%2;
            uint32_t smpte2110 = strtoul(s[9], NULL, 0)%2;
            uint32_t audio = strtoul(s[10], NULL, 0)%2;
            uint8_t colour = strtoul(s[11], NULL, 0);
            uint32_t meta = strtoul(s[12], NULL, 0)%2;
            uint8_t eotf = strtoul(s[13], NULL, 0);
            uint8_t cspace = strtoul(s[14], NULL, 0);
            HW_API::XTxColourSpecification clr_spec_inp;
            HW_API::XTxSampleStructure smp_struct_inp;
            switch(colour) {
              case 1:
                clr_spec_inp = HW_API::C_REC709;
                smp_struct_inp = HW_API::S_444;
                break;
              case 2:
                clr_spec_inp = HW_API::C_REC709;
                smp_struct_inp = HW_API::S_422;
                break;
              case 0:
              default:
                clr_spec_inp = HW_API::C_SRGB;
                smp_struct_inp = HW_API::S_444;
                break;
            }
            HW_API::bist10GETx(sfp_a,sfp_b,srtp,vstd,aspen422,aspen444,tico,smpte2110,audio,clr_spec_inp,smp_struct_inp,meta,(HW_API::XTxElectroopticalTransferFunction)eotf,(HW_API::XTxColourSpace)cspace);
            pvalid = true;
        }
    } else if (n == 16) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "xge_tx")) {
            uint32_t sfp_a = strtoul(s[2], NULL, 0);
            uint32_t sfp_b = strtoul(s[3], NULL, 0);
            uint32_t srtp = strtoul(s[4], NULL, 0);
            uint32_t vstd = strtoul(s[5], NULL, 0);
            uint32_t aspen422 = strtoul(s[6], NULL, 0)%2;
            uint32_t aspen444 = strtoul(s[7], NULL, 0)%2;
            uint32_t tico = strtoul(s[8], NULL, 0)%2;
            uint32_t smpte2110 = strtoul(s[9], NULL, 0)%2;
            uint32_t audio = strtoul(s[10], NULL, 0)%2;
            uint8_t colour = strtoul(s[11], NULL, 0);
            uint32_t meta = strtoul(s[12], NULL, 0)%2;
            uint8_t eotf = strtoul(s[13], NULL, 0);
            uint8_t cspace = strtoul(s[14], NULL, 0);
            uint32_t usb = strtoul(s[15], NULL, 0);
            HW_API::XTxColourSpecification clr_spec_inp;
            HW_API::XTxSampleStructure smp_struct_inp;
            switch(colour) {
              case 1:
                clr_spec_inp = HW_API::C_REC709;
                smp_struct_inp = HW_API::S_444;
                break;
              case 2:
                clr_spec_inp = HW_API::C_REC709;
                smp_struct_inp = HW_API::S_422;
                break;
              case 0:
              default:
                clr_spec_inp = HW_API::C_SRGB;
                smp_struct_inp = HW_API::S_444;
                break;
            }
            HW_API::bist10GETx(sfp_a,sfp_b,srtp,vstd,aspen422,aspen444,tico,smpte2110,audio,clr_spec_inp,smp_struct_inp,meta,(HW_API::XTxElectroopticalTransferFunction)eotf,(HW_API::XTxColourSpace)cspace,usb);
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGEDRPRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> <read_addr>\n", s[0]);
        printf("       %s <channel> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0)%HW_API::N_TOTAL_10GE_CHANNELS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        HW_API::initFPGABuildID();
        if (ch >= HW_API::N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
        {
          printf("INC_TEST_XGE feature is required but not enabled!\n");
        } else {
          uint32_t data = HW_API::readXGEDRPReg(ch, addr);
          printf("XGE DRP %u Register %u == 0x%08x\n", ch, addr, data);
        }
        pvalid = true;
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0)%HW_API::N_TOTAL_10GE_CHANNELS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::initFPGABuildID();
        if (ch >= HW_API::N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
        {
          printf("INC_TEST_XGE feature is required but not enabled!\n");
        } else {
          HW_API::writeXGEDRPReg(ch, addr, data);
          printf("XGE DRP %u Register %u => 0x%08x\n", ch, addr, data);
        }
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execDRPNLRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readDRPNLReg(addr);
        printf("DRPNL Register %u == 0x%08x\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeDRPNLReg(addr, data);
        printf("DRPNL Register %u => 0x%08x\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execHDMIIPRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> <read_addr>\n", s[0]);
        printf("       %s <channel> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_HDMI_CHANS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readHDMIIPReg(ch, addr);
        printf("HDMI IP %u Register 0x%x == 0x%08x\n", ch, addr, data);
        pvalid = true;
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_HDMI_CHANS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeHDMIIPReg(ch, addr, data);
        printf("HDMI IP %u Register 0x%x => 0x%08x\n", ch, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGEMacRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> <read_addr>\n", s[0]);
        printf("       %s <channel> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        HW_API::initFPGABuildID();
        if (ch >= HW_API::N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
        {
          printf("INC_TEST_XGE feature is required but not enabled!\n");
        } else {
          uint32_t data = HW_API::readXGEMacReg(ch, addr);
          printf("XGE MAC %u Register 0x%x == 0x%08x\n", ch, addr, data);
        }
        pvalid = true;
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::initFPGABuildID();
        if (ch >= HW_API::N_10GE_CHANNELS && HW_API::getFPGACapability("INC_TEST_XGE") <= 0)
        {
          printf("INC_TEST_XGE feature is required but not enabled!\n");
        } else {
          HW_API::writeXGEMacReg(ch, addr, data);
          printf("XGE MAC %u Register 0x%x => 0x%08x\n", ch, addr, data);
        }
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGEIfRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readXGEIfReg(addr);
        printf("XGE Interface Register %u == 0x%08x\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeXGEIfReg(addr, data);
        printf("XGE Interface Register %u => 0x%08x\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGETxRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint64_t data = HW_API::readXGETxReg(addr);
        printf("XGE Tx Register %u == 0x%016llx\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint64_t data = strtoull(s[2], NULL, 0);
        HW_API::writeXGETxReg(addr, data);
        printf("XGE Tx Register %u => 0x%016llx\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGERxRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint64_t data = HW_API::readXGERxReg(addr);
        printf("XGE Rx Register %u == 0x%016llx\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint64_t data = strtoull(s[2], NULL, 0);
        HW_API::writeXGERxReg(addr, data);
        printf("XGE Rx Register %u => 0x%016llx\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGEIPTxRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readIPTxReg(addr);
        printf("XGE IPTx Register %u == 0x%016x (%u)\n", addr, data, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeIPTxReg(addr, data);
        printf("XGE IPTx Register %u => 0x%016x (%u)\n", addr, data, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGEIPRxRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readIPRxReg(addr);
        printf("XGE IPRx Register %u == 0x%016x (%u)\n", addr, data, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeIPRxReg(addr, data);
        printf("XGE IPRx Register %u => 0x%016x (%u)\n", addr, data, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execFPGAIDRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readFPGAIDReg(addr);
        printf("FPGA ID Register %u == 0x%08x\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeFPGAIDReg(addr, data);
        printf("FPGA ID Register %u => 0x%08x\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXBARCONFIGRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readXBARCONFIGReg(addr);
        printf("XBAR Config Register %u == 0x%08x\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeXBARCONFIGReg(addr, data);
        printf("XBAR Config Register %u => 0x%08x\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execSCARW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> <read_addr>\n", s[0]);
        printf("       %s <channel> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readScalerAReg(ch, addr);
        printf("Scaler A %u Register 0x%x == 0x%08x\n", ch, addr, data);
        pvalid = true;
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeScalerAReg(ch, addr, data);
        printf("Scaler A %u Register 0x%x => 0x%08x\n", ch, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execSCBRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> <read_addr>\n", s[0]);
        printf("       %s <channel> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readScalerBReg(ch, addr);
        printf("Scaler B %u Register 0x%x == 0x%08x\n", ch, addr, data);
        pvalid = true;
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeScalerBReg(ch, addr, data);
        printf("Scaler B %u Register 0x%x => 0x%08x\n", ch, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execSCRSRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> <read_addr>\n", s[0]);
        printf("       %s <channel> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readScaleRasterReg(ch, addr);
        printf("Scaler Raster %u Register 0x%x == 0x%08x\n", ch, addr, data);
        pvalid = true;
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeScaleRasterReg(ch, addr, data);
        printf("Scaler Raster %u Register 0x%x => 0x%08x\n", ch, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execSCMSRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> <read_addr>\n", s[0]);
        printf("       %s <channel> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readScaleMiscReg(ch, addr);
        printf("Scaler Misc %u Register 0x%x == 0x%08x\n", ch, addr, data);
        pvalid = true;
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeScaleMiscReg(ch, addr, data);
        printf("Scaler Misc %u Register 0x%x => 0x%08x\n", ch, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execSCWPRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> <read_addr>\n", s[0]);
        printf("       %s <channel> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readScalerWritePortReg(ch, addr);
        printf("Scaler Write Port %u Register 0x%x == 0x%08x\n", ch, addr, data);
        pvalid = true;
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeScalerWritePortReg(ch, addr, data);
        printf("Scaler Write Port %u Register 0x%x => 0x%08x\n", ch, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execSCPLRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> <read_addr>\n", s[0]);
        printf("       %s <channel> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readScalerPlayoutReg(ch, addr);
        printf("Scaler Playout %u Register 0x%x == 0x%08x\n", ch, addr, data);
        pvalid = true;
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_SCALER_PATHS+HW_API::N_FRAME_BUFFER_PATHS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeScalerPlayoutReg(ch, addr, data);
        printf("Scaler Playout %u Register 0x%x => 0x%08x\n", ch, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execGenlockRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readGenlockReg(addr);
        printf("Genlock Register %u == 0x%08x\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeGenlockReg(addr, data);
        printf("Genlock Register %u => 0x%08x\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execMTestRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readMemTestReg(0, addr);
        printf("Memory Test Register %u == 0x%08x\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeMemTestReg(0, addr, data);
        printf("Memory Test Register %u => 0x%08x\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execIcronUSBRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readIcronUSBReg(addr);
        printf("Icron USB Register %u == 0x%08x\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeIcronUSBReg(addr, data);
        printf("Icron USB Register %u => 0x%08x\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execAMixerRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> <read_addr>\n", s[0]);
        printf("       %s <channel> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::NUM_MIXERS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readAudioMixerReg(ch, addr);
        printf("Audio Mixer %u Register 0x%x == 0x%08x\n", ch, addr, data);
        pvalid = true;
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::NUM_MIXERS;
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeAudioMixerReg(ch, addr, data);
        printf("Audio Mixer %u Register 0x%x => 0x%08x\n", ch, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execPTPRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readPTPReg(addr);
        printf("PTP Register %u == 0x%08x\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writePTPReg(addr, data);
        printf("PTP Register %u => 0x%08x\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execGeneralRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readGeneralReg(addr);
        printf("General Register %u == 0x%08x\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeGeneralReg(addr, data);
        printf("General Register %u => 0x%08x\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execInterRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <quad> <read_addr>\n", s[0]);
        printf("       %s <quad> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint8_t quad = strtoul(s[1], NULL, 0);
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readInterfpgaReg(HW_API::mapInterfpgaQuadToIndex(quad), addr);
        printf("InterFPGA Quad %u Register %u == 0x%08x\n", quad, addr, data);
        pvalid = true;
    } else if (n == 4) {
        uint8_t quad = strtoul(s[1], NULL, 0);
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeInterfpgaReg(HW_API::mapInterfpgaQuadToIndex(quad), addr, data);
        printf("InterFPGA Quad %u Register %u => 0x%08x\n", quad, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execSDI12GRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <read_addr>\n", s[0]);
        printf("       %s <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = HW_API::readSDI12GReg(addr);
        printf("SDI 12G Register %u == 0x%08x\n", addr, data);
        pvalid = true;
    } else if (n == 3) {
        uint32_t addr = strtoul(s[1], NULL, 0);
        uint32_t data = strtoul(s[2], NULL, 0);
        HW_API::writeSDI12GReg(addr, data);
        printf("SDI 12G Register %u => 0x%08x\n", addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execAxiDmaIpRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <index> <read_addr>\n", s[0]);
        printf("       %s <index> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t index = strtoul(s[1], NULL, 0);
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readAxiDmaIpReg(index, addr);
        printf("AXI DMA %u IP Register %u == 0x%08x / %u\n", index, addr, data, data);
        pvalid = true;
    } else if (n == 4) {
        uint32_t index = strtoul(s[1], NULL, 0);
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeAxiDmaIpReg(index, addr, data);
        printf("AXI DMA %u IP Register %u => 0x%08x\n", index, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execAxiDmaMemRW(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <index> <read_addr>\n", s[0]);
        printf("       %s <index> <write_addr> <write_value>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t index = strtoul(s[1], NULL, 0);
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = HW_API::readAxiDmaMemReg(index, addr);
        printf("AXI DMA %u Mem Register %u == 0x%08x / %u\n", index, addr, data, data);
        pvalid = true;
    } else if (n == 4) {
        uint32_t index = strtoul(s[1], NULL, 0);
        uint32_t addr = strtoul(s[2], NULL, 0);
        uint32_t data = strtoul(s[3], NULL, 0);
        HW_API::writeAxiDmaMemReg(index, addr, data);
        printf("AXI DMA %u Mem Register %u => 0x%08x\n", index, addr, data);
        pvalid = true;
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execMTest(int n, char *s[])
{
    bool pvalid = false;

    if ((n == 1) || (n == 2)) {
        printf("Usage: %s config <bank>\n", s[0]);
        printf("       %s ready <bank>\n", s[0]);
        printf("       %s calib <bank>\n", s[0]);
        printf("       %s run  <bank> <depth_div> <type>\n", s[0]);
        printf("\n");
        printf("   where bank      = memory bank (HP = 0, HR = 1)\n");
        printf("         depth_div = test depth div exponent\n");
        printf("         type      = test type (0..4)\n");
        pvalid = true;
    } else if (n == 3) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "config")) {
            uint32_t bank = strtoul(s[2], NULL, 0);
            HW_API::initMemoryTest(bank);
            HW_API::dumpMemoryTestConfig(bank);
            pvalid = true;
        } else if (!strcmp(s[1], "ready")) {
            uint32_t bank = strtoul(s[2], NULL, 0);
            HW_API::initMemoryTest(bank);
            printf("Memory Test is %s.\n",
                HW_API::getMemoryTestReady(bank)?"Ready":"Not Ready");
            pvalid = true;
        } else if (!strcmp(s[1], "calib")) {
            uint32_t bank = strtoul(s[2], NULL, 0);
            HW_API::initMemoryTest(bank);
            printf("Memory is %s.\n",
                HW_API::getMemoryCalibrated(bank)?"Calibrated":"NOT Calibrated");
            pvalid = true;
        }
    } else if (n == 5) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "run")) {
            uint32_t bank = strtoul(s[2], NULL, 0);
            uint32_t depth_div_exp = strtoul(s[3], NULL, 0);
            uint32_t type = strtoul(s[4], NULL, 0);
            type %= 5;
            HW_API::initMemoryTest(bank);
            HW_API::runMemoryTest(bank, depth_div_exp, (HW_API::MemTestType)type);
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGEMac(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> init\n", s[0]);
        printf("       %s <channel> stat names\n", s[0]);
        printf("       %s <channel> stat <stat_index>\n", s[0]);
        printf("       %s <channel> mac enable\n", s[0]);
        printf("       %s <channel> mdio enable\n", s[0]);
        printf("       %s <channel> mdio enable <0/1>\n", s[0]);
        printf("       %s <channel> mdio write <dev> <reg> <data>\n", s[0]);
        printf("       %s <channel> mdio read <dev> <reg>\n", s[0]);
        printf("       %s <channel> signal\n", s[0]);
        printf("       %s <channel> link\n", s[0]);
        printf("       %s <channel> simplex <0-disable/1-enable>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        if (!strcmp(s[2], "init")) {
            HW_API::initFPGABuildID();
            HW_API::init10GEMac(ch);
            pvalid = true;
        } else if (!strcmp(s[2], "signal")) {
            HW_API::initFPGABuildID();
            HW_API::init10GEMac(ch);
            printf("Mac %u Signal = %u\n",ch,HW_API::get10GERxSignalDetect(ch));
            pvalid = true;
        } else if (!strcmp(s[2], "link")) {
            HW_API::initFPGABuildID();
            HW_API::init10GEMac(ch);
            printf("Mac %u Link = %u\n",ch,HW_API::get10GELinkUp(ch));
            pvalid = true;
        }
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        if (!strcmp(s[2], "stat")) {
            if (!strcmp(s[3], "names")) {
                HW_API::initFPGABuildID();
                HW_API::init10GEMac(ch);
                HW_API::dump10GEMacStatNames();
                pvalid = true;
            } else {
                uint32_t stat_reg = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::init10GEMac(ch);
                uint64_t stat = HW_API::get10GEMacStatistic(ch,stat_reg);
                printf("Mac %u, Stat %u = %llu\n",ch,stat_reg,stat);
                pvalid = true;
            }
        } else if (!strcmp(s[2], "mac")) {
            if (!strcmp(s[3], "enable")) {
                HW_API::initFPGABuildID();
                HW_API::init10GEMac(ch);
                printf("Mac %u RX is %s\n",ch,HW_API::get10GEMacRxEnable(ch)?"Enabled":"Disabled");
                printf("Mac %u TX is %s\n",ch,HW_API::get10GEMacTxEnable(ch)?"Enabled":"Disabled");
                pvalid = true;
            }
        } else if (!strcmp(s[2], "mdio")) {
            if (!strcmp(s[3], "enable")) {
                HW_API::initFPGABuildID();
                HW_API::init10GEMac(ch);
                printf("MDIO %u is %s\n",ch,HW_API::get10GEMacMDIOEnable(ch)?"Enabled":"Disabled");
                pvalid = true;
            }
        } else if (!strcmp(s[2], "simplex")) {
            uint32_t enable      = strtoul(s[3], NULL, 0);
            uint32_t always_on   = 1;
            HW_API::initFPGABuildID();
            HW_API::init10GEMac(ch);
            HW_API::set10GEMacTxEnable(ch, always_on);
            printf("Set XGE MAC %u TX-Enable\n", ch);
            HW_API::set10GEMacFaultInhibit(ch, enable);
            printf("Set XGE MAC %u Fault-Inhibit %s\n", ch, (enable == 1)?"Enabled":"Disabled");
            pvalid = true;
        }
    } else if (n == 5) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        if (!strcmp(s[2], "mdio")) {
            if (!strcmp(s[3], "enable")) {
                uint32_t en   = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::init10GEMac(ch);
                HW_API::set10GEMacMDIOEnable(ch,(en > 0));
                pvalid = true;
            }
        }
    } else if (n == 6) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        if (!strcmp(s[2], "mdio")) {
            if (!strcmp(s[3], "read")) {
                uint32_t dev   = strtoul(s[4], NULL, 0);
                uint32_t reg   = strtoul(s[5], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::init10GEMac(ch);
                uint16_t data = HW_API::read10GEMacMDIO(ch,dev,reg);
                printf("MDIO %u Register %u.%u == %04x\n",ch,dev,reg,data);
                pvalid = true;
            }
        }
    } else if (n == 7) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        if (!strcmp(s[2], "mdio")) {
            if (!strcmp(s[3], "write")) {
                uint32_t dev   = strtoul(s[4], NULL, 0);
                uint32_t reg   = strtoul(s[5], NULL, 0);
                uint16_t data  = strtoul(s[6], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::init10GEMac(ch);
                HW_API::write10GEMacMDIO(ch,dev,reg,data);
                printf("MDIO %u Register %u.%u => %04x\n",ch,dev,reg,data);
                pvalid = true;
            }
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execTEMAC(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> init\n", s[0]);
        printf("       %s <channel> stat names\n", s[0]);
        printf("       %s <channel> stat <stat_index>\n", s[0]);
        printf("       %s <channel> mac enable\n", s[0]);
        printf("       %s <channel> mdio enable\n", s[0]);
        printf("       %s <channel> mdio enable <0/1>\n", s[0]);
        printf("       %s <channel> mdio write <reg> <data>\n", s[0]);
        printf("       %s <channel> mdio read <reg>\n", s[0]);
        printf("       %s <channel> sgmii <0/1>\n", s[0]);
        printf("       %s <channel> link\n", s[0]);
        printf("       %s <channel> simplex <0-disable/1-enable>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        if (!strcmp(s[2], "init")) {
            HW_API::initFPGABuildID();
            HW_API::initTEMAC(ch);
            pvalid = true;
        } else if (!strcmp(s[2], "sgmii")) {
            HW_API::initFPGABuildID();
            HW_API::initTEMAC(ch);
            printf("PHY %u SGMII = %u\n",ch,HW_API::get1GSgmii(ch));
            pvalid = true;
        } else if (!strcmp(s[2], "link")) {
            HW_API::initFPGABuildID();
            HW_API::initTEMAC(ch);
            printf("Mac %u Link = %u\n",ch,HW_API::get1GLinkUp(ch));
            pvalid = true;
        }
    } else if (n == 4) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        if (!strcmp(s[2], "stat")) {
            if (!strcmp(s[3], "names")) {
                HW_API::initFPGABuildID();
                HW_API::initTEMAC(ch);
                HW_API::dumpTEMACStatNames();
                pvalid = true;
            } else {
                uint32_t stat_reg = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initTEMAC(ch);
                uint64_t stat = HW_API::getTEMACStatistic(ch,stat_reg);
                printf("Mac %u, Stat %u = %llu\n",ch,stat_reg,stat);
                pvalid = true;
            }
        } else if (!strcmp(s[2], "mac")) {
            if (!strcmp(s[3], "enable")) {
                HW_API::initFPGABuildID();
                HW_API::initTEMAC(ch);
                printf("Mac %u RX is %s\n",ch,HW_API::getTEMACRxEnable(ch)?"Enabled":"Disabled");
                printf("Mac %u TX is %s\n",ch,HW_API::getTEMACTxEnable(ch)?"Enabled":"Disabled");
                pvalid = true;
            }
        } else if (!strcmp(s[2], "mdio")) {
            if (!strcmp(s[3], "enable")) {
                HW_API::initFPGABuildID();
                HW_API::initTEMAC(ch);
                printf("MDIO %u is %s\n",ch,HW_API::getTEMACMDIOEnable(ch)?"Enabled":"Disabled");
                pvalid = true;
            }
        } else if (!strcmp(s[2], "sgmii")) {
            uint32_t sgmii = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initTEMAC(ch);
            HW_API::set1GSgmii(ch,sgmii);
            printf("PHY %u SGMII = %u\n",ch,sgmii);
            pvalid = true;
        } else if (!strcmp(s[2], "simplex")) {
            uint32_t enable  = strtoul(s[3], NULL, 0);
            uint32_t disable = (enable == 1)? 0:1;
            uint32_t always_on   = 1;
            HW_API::initFPGABuildID();
            HW_API::initTEMAC(ch);
            HW_API::setTEMACTxEnable(ch, always_on);
            printf("Set GE MAC %u TX-Enable\n", ch);
            HW_API::set1GSgmii(ch,enable);
            printf("Set GE PHY %u SGMII %s\n",ch, (enable == 1)?"Enabled":"Disabled");
            HW_API::setEnableAutonegotiation(ch, disable);
            HW_API::set1GUnidirectionalEnable(ch, enable);
            printf("Set GE PHY %u Auto-Neg %s and Unidirectional %s\n", ch, (enable == 1)?"Disabled":"Enabled",(enable == 1)?"Enabled":"Disabled");
            pvalid = true;
        }
    } else if (n == 5) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        if (!strcmp(s[2], "mdio")) {
            if (!strcmp(s[3], "enable")) {
                uint32_t en   = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initTEMAC(ch);
                HW_API::setTEMACMDIOEnable(ch,(en > 0));
                pvalid = true;
            } else if (!strcmp(s[3], "read")) {
                uint32_t reg   = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initTEMAC(ch);
                uint16_t data = HW_API::readTEMACMDIO(ch,reg);
                printf("MDIO %u Register %u == %04x\n",ch,reg,data);
                pvalid = true;
            }
        }
    } else if (n == 6) {
        uint32_t ch   = strtoul(s[1], NULL, 0);
        ch %= HW_API::N_TOTAL_10GE_CHANNELS;
        if (!strcmp(s[2], "mdio")) {
            if (!strcmp(s[3], "write")) {
                uint32_t reg   = strtoul(s[4], NULL, 0);
                uint16_t data  = strtoul(s[5], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initTEMAC(ch);
                HW_API::writeTEMACMDIO(ch,reg,data);
                printf("MDIO %u Register %u => %04x\n",ch,reg,data);
                pvalid = true;
            }
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGEXcvr(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s <channel> init\n", s[0]);
        printf("       %s <channel> info\n", s[0]);
        printf("       %s <channel> eye_scan <time> <h_gap> <v_gap>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        if (!strcmp(s[2], "init")) {
            uint32_t ch = strtoul(s[1], NULL, 0)%HW_API::N_TOTAL_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::init10GEXcvr(ch);
            pvalid = true;
        } else if (!strcmp(s[2], "info")) {
            uint32_t ch = strtoul(s[1], NULL, 0)%HW_API::N_TOTAL_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::init10GEXcvr(ch);
            printf("XGE Transceiver Channel %u:\n", ch);
            printf("  Rx Data Width = %u\n", HW_API::get10GEXcvrRxDataWidth(ch));
            printf("  Rx Int Data Width = %u\n", HW_API::get10GEXcvrRxIntDataWidth(ch));
            printf("  Rx Out Div = %u\n", HW_API::get10GEXcvrRxOutDiv(ch));
            pvalid = true;
        }
    } else if (n == 6) {
        if (!strcmp(s[2], "eye_scan")) {
            uint32_t ch = strtoul(s[1], NULL, 0)%HW_API::N_TOTAL_10GE_CHANNELS;
            uint32_t time = strtoul(s[3], NULL, 0);
            uint32_t h_gap = strtoul(s[4], NULL, 0);
            uint32_t v_gap = strtoul(s[5], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::init10GEXcvr(ch);
            HW_API::run10GERxEyeScan(ch, time, h_gap, v_gap);
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGEIf(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s init\n", s[0]);
        printf("       %s daisy tx\n", s[0]);
        printf("       %s daisy tx <0/1>\n", s[0]);
        printf("       %s daisy rx\n", s[0]);
        printf("       %s daisy rx <0/1>\n", s[0]);
        printf("       %s daisy_drop_count <idx>\n", s[0]);
        printf("       %s rx_drop_count <idx>\n", s[0]);
        printf("       %s rx_pkt_len <idx>\n", s[0]);
        printf("       %s rx_bandwidth <idx>\n", s[0]);
        printf("       %s tx_bandwidth <idx>\n", s[0]);
        printf("\n");
        printf("   where idx = sfp idx (0-1)\n");
        pvalid = true;
    } else if (n == 2) {
        if (!strcmp(s[1], "init")) {
            HW_API::initFPGABuildID();
            HW_API::init10GEIntf();
            pvalid = true;
        }
    } else if (n == 3) {
        if (!strcmp(s[1], "daisy")) {
            if (!strcmp(s[2], "tx")) {
                HW_API::initFPGABuildID();
                HW_API::init10GEIntf();
                printf("Tx Daisy Chain is %s\n",HW_API::get10GEDaisyEnTx()?"Enabled":"Disabled");
                pvalid = true;
            } else if (!strcmp(s[2], "rx")) {
                HW_API::initFPGABuildID();
                HW_API::init10GEIntf();
                printf("Rx Daisy Chain is %s\n",HW_API::get10GEDaisyEnRx()?"Enabled":"Disabled");
                pvalid = true;
            }
        } else if (!strcmp(s[1], "daisy_drop_count")) {
            uint32_t idx = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::init10GEIntf();
            printf("Daisy Chain %u Drop Count = %u\n",idx,HW_API::get10GEDaisyDropCount(idx));
            pvalid = true;
        } else if (!strcmp(s[1], "rx_drop_count")) {
            uint32_t idx = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::init10GEIntf();
            printf("10G Rx %u Drop Count = %u\n",idx,HW_API::get10GERxDropCount(idx));
            pvalid = true;
        } else if (!strcmp(s[1], "rx_pkt_len")) {
            uint32_t idx = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::init10GEIntf();
            printf("10G Rx %u Max Packet Length = %u\n",idx,HW_API::get10GERxMaxPacketLength(idx));
            pvalid = true;
        } else if (!strcmp(s[1], "rx_bandwidth")) {
            uint32_t idx = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::init10GEIntf();
            printf("10G Rx %u Bandwidth = %u\n",idx,HW_API::get10GERxBandwidth(idx));
            pvalid = true;
        } else if (!strcmp(s[1], "tx_bandwidth")) {
            uint32_t idx = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::init10GEIntf();
            printf("10G Tx %u Bandwidth = %u\n",idx,HW_API::get10GETxBandwidth(idx));
            pvalid = true;
        }
    } else if (n == 4) {
        if (!strcmp(s[1], "daisy")) {
            if (!strcmp(s[2], "tx")) {
                uint32_t en = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::init10GEIntf();
                HW_API::set10GEDaisyEnTx(en  > 0);
                pvalid = true;
            } else if (!strcmp(s[2], "rx")) {
                uint32_t en = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::init10GEIntf();
                HW_API::set10GEDaisyEnRx(en  > 0);
                pvalid = true;
            }
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGERx(int n, char *s[])
{
    bool pvalid = false;
    if (n == 1) {
        printf("Usage: %s std <idx>\n", s[0]);
        printf("       %s audio compressed <aud_idx>\n", s[0]);
        printf("       %s audio samplingfreq <aud_idx>\n", s[0]);
        printf("       %s audio hbr <aud_idx>\n", s[0]);
        printf("       %s audio type <aud_idx>\n", s[0]);
        printf("       %s audio status <aud_idx>\n", s[0]);
        printf("       %s vbw <sfp> <idx>\n", s[0]);
        printf("       %s abw <sfp> <idx>\n", s[0]);
        printf("       %s mbw <sfp> <idx>\n", s[0]);
        printf("       %s ubw <sfp> <idx>\n", s[0]);
        printf("       %s aspenpid <idx> <pid>\n", s[0]);
        printf("       %s ticopid <idx> <pid>\n", s[0]);
        printf("       %s descr <idx> <1/0>\n", s[0]);
        printf("       %s piddet <idx> <1/0>\n", s[0]);
        printf("       %s ibc_dbg <sfp>\n", s[0]);
        printf("       %s rtp_err vid <idx>\n", s[0]);
        printf("       %s rtp_err aud <idx>\n", s[0]);
        printf("       %s rtp_err usb <idx>\n", s[0]);
        printf("       %s rtp_err meta <idx>\n", s[0]);
        printf("       %s enable <idx> <aud/vid/meta> <enable>\n", s[0]);
        printf("       %s smpte2110 <idx> <aspl> <sampling> <depth>\n", s[0]);
        printf("       %s aes67 <aud_idx> <chans> <sf_hz>\n", s[0]);
        printf("       %s addr <sfp> <chan> <addr byte0> <addr byte1> <addr byte2> <addr byte3> <port> [bypass]\n", s[0]);
        printf("       %s vidchan <sfp> <idx> <chan>\n", s[0]);
        printf("       %s audchan <sfp> <idx> <chan>\n", s[0]);
        printf("       %s metachan <sfp> <idx> <chan>\n", s[0]);
        printf("       %s usbchan <sfp> <idx> <chan>\n", s[0]);
        printf("       %s redundancy <idx> <aud/vid/meta> <enable>\n", s[0]);
        printf("       %s key <sfp> <chan> <keyid> <key0> <key1> <key2> <key3>\n", s[0]);
        printf("       %s unset <sfp> <chan> <keyid>\n", s[0]);
        printf("       %s ptype <sfp> <chan>\n", s[0]);
        printf("       %s is_srtp <sfp> <chan>\n", s[0]);
        printf("\n");
        printf("   where idx     = video idx (0-%u)\n", (HW_API::N_XGE_RX_VID-1));
        printf("   where aud_idx = audio idx (0-%u)\n", (HW_API::N_XGE_RX_AUD-1));
        printf("   where sfp     = sfp idx (0-%u)\n", (HW_API::N_10GE_CHANNELS-1));
        pvalid = true;
    } else if (n == 3) {
        if (!strcmp(s[1], "std")) {
            uint32_t idx = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            HW_API::dumpVidSTD(idx);
            pvalid = true;
        } else if (!strcmp(s[1], "ibc_dbg")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::initIPRx();
            printf("SFP %u IBC Drop Count = %u\n",
                sfp, (unsigned)HW_API::getInBandControlDropCount(sfp));
            HW_API::clearInBandControlDropCount(sfp);
            printf("SFP %u IBC Keep Count = %u\n",
                sfp, (unsigned)HW_API::getInBandControlKeepCount(sfp));
            HW_API::clearInBandControlKeepCount(sfp);
            pvalid = true;
        } else if (!strcmp(s[1], "bw")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::initIPRx();
            printf("SFP %u Rx Bandwidth = %u\n", sfp, (unsigned)HW_API::getRxSFPInBandwidth(sfp));
            pvalid = true;
        }
    } else if (n == 4) {
        if (!strcmp(s[1], "audio")) {
            uint32_t chan_unsafe = strtoul(s[3], NULL, 0);
            uint32_t chan = chan_unsafe % HW_API::N_XGE_RX_AUD;
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            if (!strcmp(s[2], "compressed")) {
              bool compressed = HW_API::getAudioRxCompressed(chan);
              printf("Audio stream %u Compressed Status: %u\n", chan, compressed);
              pvalid = true;
            } else if (!strcmp(s[2], "samplingfreq")) {
              uint32_t sf = HW_API::getAudioRxSamplingFrequency(chan);
              printf("Audio stream %u Sampling Frequency: %u\n", chan, sf);
              pvalid = true;
            } else if (!strcmp(s[2], "hbr")) {
              bool hbr = HW_API::getAudioRxHBR(chan);
              printf("Audio stream %u HBR: %u\n", chan, hbr);
              pvalid = true;
            } else if (!strcmp(s[2], "type")) {
              char data_type[256];
              uint8_t type = HW_API::getAudioRxType(chan, data_type);
              printf("Audio stream %u Type: %u - %s\n", chan, type, data_type);
              pvalid = true;
            } else if (!strcmp(s[2], "chans")) {
              uint8_t aud_chans = HW_API::getAudioRxChans(chan);
              printf("Audio stream %u Channels: %u\n", chan, aud_chans);
              pvalid = true;
            } else if (!strcmp(s[2], "status")) {
              bool compressed = HW_API::getAudioRxCompressed(chan);
              uint32_t sf = HW_API::getAudioRxSamplingFrequency(chan);
              bool hbr = HW_API::getAudioRxHBR(chan);
              char data_type[256];
              uint8_t type = HW_API::getAudioRxType(chan, data_type);
              uint8_t aud_chans = HW_API::getAudioRxChans(chan);
              printf("Audio stream %u Compressed Status : %u\n", chan, compressed);
              printf("Audio stream %u Sampling Frequency: %u\n", chan, sf);
              printf("Audio stream %u HBR:                %u\n", chan, hbr);
              printf("Audio stream %u Type:               %u - %s\n", chan, type, data_type);
              printf("Audio stream %u Channels:           %u\n", chan, aud_chans);
              pvalid = true;
            }
        } else if (!strcmp(s[1], "vbw")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t vid = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            HW_API::dumpRxVidRouteBandwidth(sfp, vid);
            pvalid = true;
        } else if (!strcmp(s[1], "abw")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t aud = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            HW_API::dumpRxAudRouteBandwidth(sfp, aud);
            pvalid = true;
        } else if (!strcmp(s[1], "mbw")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t meta = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            HW_API::dumpRxMetaRouteBandwidth(sfp, meta);
            pvalid = true;
        } else if (!strcmp(s[1], "ubw")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t usb = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            HW_API::dumpRxUSBRouteBandwidth(sfp, usb);
            pvalid = true;
        } else if (!strcmp(s[1], "aspenpid")) {
            uint32_t idx = strtoul(s[2], NULL, 0);
            uint32_t pid = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            HW_API::setVideoRxAspenPID(idx, pid);
            pvalid = true;
        } else if (!strcmp(s[1], "ticopid")) {
            uint32_t idx = strtoul(s[2], NULL, 0);
            uint32_t pid = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            HW_API::setVideoRxTicoPID(idx, pid);
            pvalid = true;
        } else if (!strcmp(s[1], "descr")) {
            uint32_t idx = strtoul(s[2], NULL, 0);
            bool descr = (strtoul(s[3], NULL, 0)%2) == 1;
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            HW_API::allowDescramble10GERxVid(idx, descr);
            pvalid = true;
        } else if (!strcmp(s[1], "piddet")) {
            uint32_t vid = strtoul(s[2], NULL, 0);
            bool main = (strtoul(s[3], NULL, 0)%2) == 1;
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            uint32_t pid = HW_API::getVidPIDDet(vid, main);
            printf("Detected PID: %u\n", pid);
            pvalid = true;
        } else if (!strcmp(s[1], "ptype")) {
            uint32_t sfp = strtoul(s[2], NULL, 0);
            uint32_t chan = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPRx();
            uint8_t ptype = 0;
            HW_API::getRTPPayloadType(sfp, chan, &ptype);
            printf("RTP payload type: %u\n", ptype);
            pvalid = true;
        } else if (!strcmp(s[1], "is_srtp")) {
            uint32_t sfp = strtoul(s[2], NULL, 0);
            uint32_t chan = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPRx();
            bool is_srtp = false;
            HW_API::getSRTPState(sfp, chan, &is_srtp);
            printf("SRTP state: %u\n", is_srtp);
            pvalid = true;
        }
    } else if (n == 5) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "enable")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool en = strtoul(s[4], NULL, 0);
            HW_API::initIPtoAV();
            if (!strcmp(s[3], "aud")) {
                HW_API::setAudStreamEnable(chan,en);
            } else if (!strcmp(s[3], "meta")) {
                HW_API::setMetaStreamEnable(chan,en);
            } else { // vid
                HW_API::setVidStreamEnable(chan,en);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "redundancy")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool en = strtoul(s[4], NULL, 0);
            HW_API::initIPtoAV();
            if (!strcmp(s[3], "aud")) {
                HW_API::setAudRedundancy(chan,en);
            } else if (!strcmp(s[3], "meta")) {
                HW_API::setMetaRedundancy(chan,en);
            } else { // vid
                HW_API::setVidRedundancy(chan,en);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "aes67")) {
            uint32_t aud = strtoul(s[2], NULL, 0);
            uint32_t chans = strtoul(s[3], NULL, 0);
            uint32_t sf_hz = strtoul(s[4], NULL, 0);
            HW_API::initIPtoAV();
            HW_API::setAudioRxAES67Ctrl(aud, chans, sf_hz);
            pvalid = true;
        } else if (!strcmp(s[1], "unset")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t chan = strtoul(s[3], NULL, 0);
            uint32_t keyid = strtoul(s[4], NULL, 0);
            HW_API::initIPRx();
            HW_API::unset10GRxKey(sfp, chan, keyid);
            pvalid = true;
        } else if (!strcmp(s[1], "vidchan")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t idx = strtoul(s[3], NULL, 0);
            uint32_t chan = strtoul(s[4], NULL, 0);
            HW_API::initIPtoAV();
            HW_API::setVidSFPChannel(idx, sfp, chan, true);
            pvalid = true;
        } else if (!strcmp(s[1], "audchan")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t idx = strtoul(s[3], NULL, 0);
            uint32_t chan = strtoul(s[4], NULL, 0);
            HW_API::initIPtoAV();
            HW_API::setAudSFPChannel(idx, sfp, chan, true);
            pvalid = true;
        } else if (!strcmp(s[1], "metachan")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t idx = strtoul(s[3], NULL, 0);
            uint32_t chan = strtoul(s[4], NULL, 0);
            HW_API::initIPtoAV();
            HW_API::setMetaSFPChannel(idx, sfp, chan, true);
            pvalid = true;
        } else if (!strcmp(s[1], "usbchan")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t idx = strtoul(s[3], NULL, 0);
            uint32_t chan = strtoul(s[4], NULL, 0);
            HW_API::initIPtoAV();
            HW_API::setUSBSFPChannel(idx, sfp, chan, true);
            pvalid = true;
        } else if (!strcmp(s[1], "rtp_err")) {
            if (!strcmp(s[2], "vid")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                bool main = (strtoul(s[4], NULL, 0)%2) == 1;
                HW_API::initFPGABuildID();
                HW_API::initIPtoAV();
                uint64_t rtp_err = HW_API::getVidStreamRTPErrors(idx, main);
                printf("Vid %u RTP Error Count = %llu\n", idx, rtp_err);
                pvalid = true;
            } else if (!strcmp(s[2], "aud")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                bool main = (strtoul(s[4], NULL, 0)%2) == 1;
                HW_API::initFPGABuildID();
                HW_API::initIPtoAV();
                uint64_t rtp_err = HW_API::getAudStreamRTPErrors(idx, main);
                printf("Aud %u RTP Error Count = %llu\n", idx, rtp_err);
                pvalid = true;
            } else if (!strcmp(s[2], "meta")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                bool main = (strtoul(s[4], NULL, 0)%2) == 1;
                HW_API::initFPGABuildID();
                HW_API::initIPtoAV();
                uint64_t rtp_err = HW_API::getMetaStreamRTPErrors(idx, main);
                printf("Meta %u RTP Error Count = %llu\n", idx, rtp_err);
                pvalid = true;
            } else if (!strcmp(s[2], "usb")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                bool main = (strtoul(s[4], NULL, 0)%2) == 1;
                HW_API::initFPGABuildID();
                HW_API::initIPtoAV();
                uint64_t rtp_err = HW_API::getUSBStreamRTPErrors(idx, main);
                printf("USB %u RTP Error Count = %llu\n", idx, rtp_err);
                pvalid = true;
            }
        }
    } else if (n == 6) {
        if (!strcmp(s[1], "smpte2110")) {
            uint32_t idx         = strtoul(s[2], NULL, 0);
            uint16_t aspl        = strtoul(s[3], NULL, 0);
            uint8_t sampling     = strtoul(s[4], NULL, 0);
            uint8_t sample_width = strtoul(s[5], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPtoAV();
            const char *sampling_mode;
            const char *sampling_rgb  = "RGB";
            const char *sampling_y444 = "YCbCr-4:4:4";
            const char *sampling_y422 = "YCbCr-4:2:2";
            if (sampling == 0) {
                sampling_mode = sampling_rgb;
            } else if (sampling == 1) {
                sampling_mode = sampling_y444;
            } else { // (sampling == 2)
                sampling_mode = sampling_y422;
            }
            HW_API::setVidSMPTE2110Config(idx, aspl, sampling_mode, sample_width);
            printf("SMPTE 2110-20 Video %u set to ASPL = %u, Sampling = %s, Depth = %u\n", idx, aspl, sampling_mode, sample_width);
            pvalid = true;
        }
    } else if (n == 9) {
        if (!strcmp(s[1], "key")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t chan = strtoul(s[3], NULL, 0);
            uint32_t keyid = strtoul(s[4], NULL, 0);
            uint32_t key[] = {strtoul(s[5], NULL, 0),
                              strtoul(s[6], NULL, 0),
                              strtoul(s[7], NULL, 0),
                              strtoul(s[8], NULL, 0)};
            HW_API::initFPGABuildID();
            HW_API::initIPRx();
            HW_API::set10GRxKey(sfp, chan, key, keyid);
            pvalid = true;
        } else if (!strcmp(s[1], "addr")) {
            uint32_t sfp = strtoul(s[2], NULL, 0);
            uint32_t chan = strtoul(s[3], NULL, 0);
            uint8_t addr0 = strtoul(s[4], NULL, 0);
            uint8_t addr1 = strtoul(s[5], NULL, 0);
            uint8_t addr2 = strtoul(s[6], NULL, 0);
            uint8_t addr3 = strtoul(s[7], NULL, 0);
            uint16_t port  = strtoul(s[8], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPRx();
            HW_API::setRxDataAddrPort(sfp, chan, addr0 << 24 | addr1 << 16 | addr2 << 8 | addr3, port);
            pvalid = true;
        }
    } else if (n == 10) {
        if (!strcmp(s[1], "addr")) {
            uint32_t sfp = strtoul(s[2], NULL, 0);
            uint32_t chan = strtoul(s[3], NULL, 0);
            uint8_t addr0 = strtoul(s[4], NULL, 0);
            uint8_t addr1 = strtoul(s[5], NULL, 0);
            uint8_t addr2 = strtoul(s[6], NULL, 0);
            uint8_t addr3 = strtoul(s[7], NULL, 0);
            uint16_t port  = strtoul(s[8], NULL, 0);
            uint8_t bypass = strtoul(s[9], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPRx();
            HW_API::setRxDataAddrPort(sfp, chan, addr0 << 24 | addr1 << 16 | addr2 << 8 | addr3, port, bypass);
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXGETx(int n, char *s[])
{
    bool pvalid = false;
    if (n == 1) {
        printf("Usage: %s vbw <sfp> <idx>\n", s[0]);
        printf("       %s abw <sfp> <idx>\n", s[0]);
        printf("       %s mbw <sfp> <idx>\n", s[0]);
        printf("       %s ubw <sfp> <idx>\n", s[0]);
        printf("       %s enable <sfp> <idx> <aud/aspen422/aspen444/tico/smpte2110/meta> <enable>\n", s[0]);
        printf("       %s addr <sfp> <idx> <aud/aspen422/aspen444/tico/smpte2110/meta> <addr byte0> <addr byte1> <addr byte2> <addr byte3> <port>\n", s[0]);
        printf("       %s vstd <idx> <vstd>\n", s[0]);
        printf("       %s vstd <idx> <vstd> <colour inp> <colour out>\n", s[0]);
        printf("       %s vstd <idx> <vstd> <colour inp> <colour out> <comp size>\n", s[0]);
        printf("       %s overflow <idx>\n", s[0]);
        printf("       %s key <sfp> <chan> <keyid> <key0> <key1> <key2> <key3>\n", s[0]);
        printf("       %s key <sfp> <usb/aspen422/aspen444/tico/st2110/aud/meta/lowrate> <chan> <keyid> <key0> <key1> <key2> <key3>\n", s[0]);
        printf("       %s unset <sfp> <chan> <keyid>\n", s[0]);
        printf("       %s unset <sfp> <usb/aspen422/aspen444/tico/st2110/aud/meta/lowrate> <chan> <keyid>\n", s[0]);
        printf("       %s ptime <aud> <grp> <pt1ms>\n", s[0]);
        printf("       %s smpte2110 <idx>\n", s[0]);
        printf("\n");
        printf("   where idx = video idx (0-%u)\n", (HW_API::N_XGE_TX_VID-1));
        printf("         sfp = sfp idx (0-%u)\n", (HW_API::N_10GE_CHANNELS-1));
        printf("         vstd = 0 = 4K30, 1 = 1080P60\n");
        printf("         colour =  0=RGB444, 1=YCC444, 2=YCC422\n");
        printf("         comp size = 8, 10\n");
        pvalid = true;
    } else if (n == 3) {
        if (!strcmp(s[1], "overflow")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            bool overflow = HW_API::getTxEncapOverflow(sfp);
            printf("SFP %u Encapsulation Overflow: %s.\n", sfp, (overflow ? "true" : "false"));
            pvalid = true;
        } else if (!strcmp(s[1], "smpte2110")) {
            uint32_t vid = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            HW_API::initIPTx(7);
            HW_API::dumpTxVidSMPTE2110(vid);
            pvalid = true;
        }
    } else if (n == 4) {
        if (!strcmp(s[1], "vbw")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t vid = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            HW_API::initIPTx(7);
            HW_API::dumpTxVidRouteBandwidth(sfp, vid);
            pvalid = true;
        } else if (!strcmp(s[1], "abw")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t aud = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            HW_API::initIPTx(7);
            HW_API::dumpTxAudRouteBandwidth(sfp, aud);
            pvalid = true;
        } else if (!strcmp(s[1], "mbw")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t meta = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            HW_API::initIPTx(7);
            HW_API::dumpTxMetaRouteBandwidth(sfp, meta);
            pvalid = true;
        } else if (!strcmp(s[1], "ubw")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t usb = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            HW_API::initIPTx(7);
            HW_API::dumpTxUSBRouteBandwidth(sfp, usb);
            pvalid = true;
        } else if (!strcmp(s[1], "vstd")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint32_t vstd = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            if (vstd==0) { // 4K30
                HW_API::XTxVidStandard std;
                std.interlaced = false;
                std.bw = (HW_API::Vid_3G);
                std.hs_pol_high = true;
                std.vs_pol_high = true;
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
                std.clr_spec_inp = HW_API::C_SRGB;  // Currently assumes RGB444 Source
                std.cmp_size = 10;
                std.smp_struct_inp = HW_API::S_444;
                if (chan < 2) { // ASPEN422
                  std.clr_spec = HW_API::C_REC2020;
                  std.smp_struct = HW_API::S_422;
                } else { // ASPEN444
                  std.clr_spec = HW_API::C_SRGB; // This probably should be C_REC2020 colour space but that has implicit assumption of YCbCr so use sRGB instead...
                  std.smp_struct = HW_API::S_444;
                }
                HW_API::setVideoStandard(chan,std);
            } else if (vstd==1) { // 1080P60
                HW_API::XTxVidStandard std;
                std.interlaced = false;
                std.bw = (HW_API::Vid_HD);
                std.hs_pol_high = true;
                std.vs_pol_high = true;
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
                std.clr_spec_inp = HW_API::C_SRGB;
                std.cmp_size = 10;
                std.smp_struct_inp = HW_API::S_444;
                if (chan < 2) { // ASPEN422
                  std.clr_spec = HW_API::C_REC709;
                  std.smp_struct = HW_API::S_422;
                } else { // ASPEN444
                  std.clr_spec = HW_API::C_SRGB; // This probably should be C_REC709 colour space but that has implicit assumption of YCbCr so use sRGB instead...
                  std.smp_struct = HW_API::S_444;
                }
                HW_API::setVideoStandard(chan,std);
            } else { // unsupported
                printf("Undefined video standard! Only 4K30 (vstd=0) and 1080P60 (vstd=1) are supported here \n");
            }
            pvalid = true;
        }
    } else if (n == 5) {
        if (!strcmp(s[1], "unset")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t chan = strtoul(s[3], NULL, 0);
            uint32_t keyid = strtoul(s[4], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPTx(7);
            HW_API::unset10GTxKey(sfp, chan, keyid);
            pvalid = true;
        } else if (!strcmp(s[1], "ptime")) {
            uint32_t aud = strtoul(s[2], NULL, 0);
            uint32_t grp = strtoul(s[3], NULL, 0);
            bool p1ms = strtoul(s[4], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            HW_API::initIPTx(7);
            HW_API::setAudioTxAES67PacketTime(aud, grp, p1ms);
            pvalid = true;
        }
    } else if (n == 6) {
        if (!strcmp(s[1], "enable")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t chan = strtoul(s[3], NULL, 0);
            bool en = strtoul(s[5], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            HW_API::initIPTx(7);
            if (!strcmp(s[4], "aud")) {
                HW_API::set10GETxEnable(sfp,HW_API::get10GTxAudioChannel(chan),en);
            } else if (!strcmp(s[4], "meta")) {
                HW_API::set10GETxEnable(sfp,HW_API::get10GTxMetaChannel(chan),en);
            } else if (!strcmp(s[4], "aspen422")) {
                HW_API::set10GETxEnable(sfp,HW_API::get10GTxVideoChannel(HW_API::VT_ASPEN422,chan),en);
            } else if (!strcmp(s[4], "aspen444")) {
                HW_API::set10GETxEnable(sfp,HW_API::get10GTxVideoChannel(HW_API::VT_ASPEN444,chan),en);
            } else if (!strcmp(s[4], "tico")) {
                HW_API::set10GETxEnable(sfp,HW_API::get10GTxVideoChannel(HW_API::VT_TICO,chan),en);
            } else { // smpte2110
                HW_API::set10GETxEnable(sfp,HW_API::get10GTxVideoChannel(HW_API::VT_ST2110,chan),en);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "vstd")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint32_t vstd = strtoul(s[3], NULL, 0);
            uint32_t colour_inp = strtoul(s[4], NULL, 0);
            uint32_t colour_out = strtoul(s[5], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            HW_API::XTxVidStandard std;

            if (colour_inp == 0) {
              std.clr_spec_inp = HW_API::C_SRGB;
              std.smp_struct_inp = HW_API::S_444;
            } else if (colour_inp == 1) {
              std.clr_spec_inp = HW_API::C_REC709;
              std.smp_struct_inp = HW_API::S_444;
            } else if (colour_inp == 2) {
              std.clr_spec_inp = HW_API::C_REC709;
              std.smp_struct_inp = HW_API::S_422;
            }
            if (colour_out == 0) {
              std.clr_spec = HW_API::C_SRGB;
              std.smp_struct = HW_API::S_444;
            } else if (colour_out == 1) {
              std.clr_spec = HW_API::C_REC709;
              std.smp_struct = HW_API::S_444;
            } else if (colour_out == 2) {
              std.clr_spec = HW_API::C_REC709;
              std.smp_struct = HW_API::S_422;
            }
            std.cmp_size = 10;

            if (vstd==0) { // 4K30
                std.interlaced = false;
                std.bw = (HW_API::Vid_3G);
                std.hs_pol_high = true;
                std.vs_pol_high = true;
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
                HW_API::setVideoStandard(chan,std);
            } else if (vstd==1) { // 1080P60
                std.interlaced = false;
                std.bw = (HW_API::Vid_HD);
                std.hs_pol_high = true;
                std.vs_pol_high = true;
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
                HW_API::setVideoStandard(chan,std);
            } else { // unsupported
                printf("Undefined video standard! Only 4K30 (vstd=0) and 1080P60 (vstd=1) are supported here \n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "unset")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t chanid = 0;
            uint32_t chan = strtoul(s[4], NULL, 0);
            uint32_t keyid = strtoul(s[5], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            HW_API::initIPTx(7);
            if (!strcmp(s[3], "usb")) {
              chanid = HW_API::get10GTxUSBChannel(chan);
            } else if (!strcmp(s[3], "aspen422")) {
              chanid = HW_API::get10GTxVideoChannel(HW_API::VT_ASPEN422, chan);
            } else if (!strcmp(s[3], "aspen444")) {
              chanid = HW_API::get10GTxVideoChannel(HW_API::VT_ASPEN444, chan);
            } else if (!strcmp(s[3], "tico")) {
              chanid = HW_API::get10GTxVideoChannel(HW_API::VT_TICO, chan);
            } else if (!strcmp(s[3], "st2110")) {
              chanid = HW_API::get10GTxVideoChannel(HW_API::VT_ST2110, chan);
            } else if (!strcmp(s[3], "aud")) {
              chanid = HW_API::get10GTxAudioChannel(chan);
            } else if (!strcmp(s[3], "meta")) {
              chanid = HW_API::get10GTxMetaChannel(chan);
            } else if (!strcmp(s[3], "lowrate")) {
              chanid = HW_API::get10GTxLowrateChannel(chan);
            }
            HW_API::unset10GTxKey(sfp, chanid, keyid);
            pvalid = true;
        }
    } else if (n == 7) {
        if (!strcmp(s[1], "vstd")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint32_t vstd = strtoul(s[3], NULL, 0);
            uint32_t colour_inp = strtoul(s[4], NULL, 0);
            uint32_t colour_out = strtoul(s[5], NULL, 0);
            uint32_t comp_size  = strtoul(s[6], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initAVtoIP();
            HW_API::XTxVidStandard std;

            if (colour_inp == 0) {
              std.clr_spec_inp = HW_API::C_SRGB;
              std.smp_struct_inp = HW_API::S_444;
            } else if (colour_inp == 1) {
              std.clr_spec_inp = HW_API::C_REC709;
              std.smp_struct_inp = HW_API::S_444;
            } else if (colour_inp == 2) {
              std.clr_spec_inp = HW_API::C_REC709;
              std.smp_struct_inp = HW_API::S_422;
            }
            if (colour_out == 0) {
              std.clr_spec = HW_API::C_SRGB;
              std.smp_struct = HW_API::S_444;
            } else if (colour_out == 1) {
              std.clr_spec = HW_API::C_REC709;
              std.smp_struct = HW_API::S_444;
            } else if (colour_out == 2) {
              std.clr_spec = HW_API::C_REC709;
              std.smp_struct = HW_API::S_422;
            }
            std.cmp_size = comp_size;

            if (vstd==0) { // 4K30
                std.interlaced = false;
                std.bw = (HW_API::Vid_3G);
                std.hs_pol_high = true;
                std.vs_pol_high = true;
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
                HW_API::setVideoStandard(chan,std);
            } else if (vstd==1) { // 1080P60
                std.interlaced = false;
                std.bw = (HW_API::Vid_HD);
                std.hs_pol_high = true;
                std.vs_pol_high = true;
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
                HW_API::setVideoStandard(chan,std);
            } else { // unsupported
                printf("Undefined video standard! Only 4K30 (vstd=0) and 1080P60 (vstd=1) are supported here \n");
            }
            pvalid = true;
        }
    } else if (n == 9) {
        if (!strcmp(s[1], "key")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t chan = strtoul(s[3], NULL, 0);
            uint32_t keyid = strtoul(s[4], NULL, 0);
            uint32_t key[] = {strtoul(s[5], NULL, 0),
                              strtoul(s[6], NULL, 0),
                              strtoul(s[7], NULL, 0),
                              strtoul(s[8], NULL, 0)};
            HW_API::initFPGABuildID();
            HW_API::initIPTx(7);
            HW_API::set10GTxKey(sfp, chan, key, keyid);
            pvalid = true;
        }
    } else if (n == 10) {
        if (!strcmp(s[1], "addr")) {
            uint32_t sfp = strtoul(s[2], NULL, 0);
            uint32_t chan = strtoul(s[3], NULL, 0);
            uint8_t addr0 = strtoul(s[5], NULL, 0);
            uint8_t addr1 = strtoul(s[6], NULL, 0);
            uint8_t addr2 = strtoul(s[7], NULL, 0);
            uint8_t addr3 = strtoul(s[8], NULL, 0);
            uint32_t addr = addr0 << 24 | addr1 << 16 | addr2 << 8 | addr3 << 0;
            uint16_t port  = strtoul(s[9], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPTx(7);
            if (!strcmp(s[4], "aud")) {
                HW_API::setDestinationIPAddress(sfp, HW_API::get10GTxAudioChannel(chan), addr);
                HW_API::setDestinationPort(sfp, HW_API::get10GTxAudioChannel(chan), port);
            } else if (!strcmp(s[4], "meta")) {
                HW_API::setDestinationIPAddress(sfp, HW_API::get10GTxMetaChannel(chan), addr);
                HW_API::setDestinationPort(sfp, HW_API::get10GTxMetaChannel(chan), port);
            } else if (!strcmp(s[4], "aspen422")) {
                HW_API::setDestinationIPAddress(sfp, HW_API::get10GTxVideoChannel(HW_API::VT_ASPEN422,chan), addr);
                HW_API::setDestinationPort(sfp, HW_API::get10GTxVideoChannel(HW_API::VT_ASPEN422,chan), port);
            } else if (!strcmp(s[4], "aspen444")) {
                HW_API::setDestinationIPAddress(sfp, HW_API::get10GTxVideoChannel(HW_API::VT_ASPEN444,chan), addr);
                HW_API::setDestinationPort(sfp, HW_API::get10GTxVideoChannel(HW_API::VT_ASPEN444,chan), port);
            } else if (!strcmp(s[4], "tico")) {
                HW_API::setDestinationIPAddress(sfp, HW_API::get10GTxVideoChannel(HW_API::VT_TICO,chan), addr);
                HW_API::setDestinationPort(sfp, HW_API::get10GTxVideoChannel(HW_API::VT_TICO,chan), port);
            } else { // smpte2110
                HW_API::setDestinationIPAddress(sfp, HW_API::get10GTxVideoChannel(HW_API::VT_ST2110,chan), addr);
                HW_API::setDestinationPort(sfp, HW_API::get10GTxVideoChannel(HW_API::VT_ST2110,chan), port);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "key")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t chanid = 0;
            uint32_t chan = strtoul(s[4], NULL, 0);
            uint32_t keyid = strtoul(s[5], NULL, 0);
            uint32_t key[] = {strtoul(s[6], NULL, 0),
                              strtoul(s[7], NULL, 0),
                              strtoul(s[8], NULL, 0),
                              strtoul(s[9], NULL, 0)};
            HW_API::initFPGABuildID();
            HW_API::initIPTx(7);
            if (!strcmp(s[3], "usb")) {
              chanid = HW_API::get10GTxUSBChannel(chan);
            } else if (!strcmp(s[3], "aspen422")) {
              chanid = HW_API::get10GTxVideoChannel(HW_API::VT_ASPEN422, chan);
            } else if (!strcmp(s[3], "aspen444")) {
              chanid = HW_API::get10GTxVideoChannel(HW_API::VT_ASPEN444, chan);
            } else if (!strcmp(s[3], "tico")) {
              chanid = HW_API::get10GTxVideoChannel(HW_API::VT_TICO, chan);
            } else if (!strcmp(s[3], "st2110")) {
              chanid = HW_API::get10GTxVideoChannel(HW_API::VT_ST2110, chan);
            } else if (!strcmp(s[3], "aud")) {
              chanid = HW_API::get10GTxAudioChannel(chan);
            } else if (!strcmp(s[3], "meta")) {
              chanid = HW_API::get10GTxMetaChannel(chan);
            } else if (!strcmp(s[3], "lowrate")) {
              chanid = HW_API::get10GTxLowrateChannel(chan);
            }
            HW_API::set10GTxKey(sfp, chanid, key, keyid);
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static const uint32_t IBC_PACKET_LENGTH = 6;

static const uint64_t IBC_PACKET_DATA[IBC_PACKET_LENGTH] = {
    // Big endian
    0xffffffffffffffff, // Destination MAC: ff:ff:ff:ff:ff:ff, Source MAC: ff:ff:ff:ff:ff:ff
    0xffffffff08060001, // Type: ARP, Hardware Type: Ethernet
    0x080006040001ffff, // Protocol Type: IPv4, Hardware Size: 6, Protocol Size: 4, Opcode: Request, Sender MAC: ff:ff:ff:ff:ff:ff
    0xffffffffEF010101, // Sender IP: 239.1.1.1
    0x000000000000EF01, // Destination MAC: 00:00:00:00:00:00, Destination IP: 239.1.1.1
    0x0101000000000000,
};

static const uint8_t IBC_PACKET_VALID[IBC_PACKET_LENGTH] = {
    0xff,
    0xff,
    0xff,
    0xff,
    0xff,
    0xff
};

uint64_t reverseEndian(uint64_t data) {
    uint64_t ret = data;
    ret = (0xffffffff00000000&ret) >> 32 | (0x00000000ffffffff&ret) << 32;
    ret = (0xffff0000ffff0000&ret) >> 16 | (0x0000ffff0000ffff&ret) << 16;
    ret = (0xff00ff00ff00ff00&ret) >> 8  | (0x00ff00ff00ff00ff&ret) <<  8;
    return ret;
}

uint32_t reverseEndian(uint32_t data) {
    uint64_t ret = data;
    ret = (0xffff0000&ret) >> 16 | (0x0000ffff&ret) << 16;
    ret = (0xff00ff00&ret) >> 8  | (0x00ff00ff&ret) <<  8;
    return ret;
}

static int
execIBCTest(int n, char *s[])
{
    bool pvalid = false;
    if (n == 1 || n == 2) {
        printf("Usage: %s rx <sfp> <ip_addr>\n", s[0]);
        printf("       %s rx <sfp>\n", s[0]);
        printf("       %s tx <sfp>\n", s[0]);
        printf("       %s tx <sfp> <count> <burstsize>\n", s[0]);
        printf("\n");
        printf("where count = number of packets to send\n");
        printf("      burstsize = number of packets to buffer and send at a time\n");
        pvalid = true;
    } else if (n == 3) {
        if (!strcmp(s[1], "tx")) {
            uint32_t ibc_test_count = 0;
            bool eop;
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::initIPTx(7);
            HW_API::lockHost(true);
            if(!HW_API::getHostRdy(sfp)) {
                printf("ERROR: Host not ready!\n");
                HW_API::lockHost(false);
                return 0;
            }
            printf("IBC: %u.\n", ibc_test_count);
            for (uint32_t i = 0; i < IBC_PACKET_LENGTH; i++) {
                uint64_t IBC_PACKET_DATA_TO_SEND;
                if ( i == 0 )
                {
                    IBC_PACKET_DATA_TO_SEND = 0xFFFFFFFFFFFF0000 + ibc_test_count;
                } else {
                    IBC_PACKET_DATA_TO_SEND = IBC_PACKET_DATA[i];
                }
                printf("IBC: 0x%016llx.\n", reverseEndian(IBC_PACKET_DATA_TO_SEND));
                HW_API::lockHost(false);
                HW_API::setHostPayload(sfp, reverseEndian(IBC_PACKET_DATA_TO_SEND));
                eop = (i == IBC_PACKET_LENGTH-1);
                HW_API::setHostCtrl(sfp, IBC_PACKET_VALID[i], eop, true, eop);
            }
            printf("Host Packet Sent!\n");
            HW_API::lockHost(false);
            pvalid = true;
        } else if (!strcmp(s[1], "rx")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            HW_API::initFPGABuildID();
            HW_API::initIPRx();
            HW_API::ibcPacket pkt;
            bool ptp = false;
            uint64_t ptp_sec = 0;
            uint32_t ptp_nsec = 0;
            HW_API::getInBandControlPacket(sfp,&pkt,&ptp,&ptp_sec,&ptp_nsec);
            if (pkt.length == 0){
                printf("No packet found\n");
            } else {
                for (uint32_t i = 0; i < pkt.length; i++) {
                   printf("IBC Rx Word   == 0x%016llx\n", pkt.data[i]);
                }
                printf("IBC Rx Empty  == %u\n", pkt.empty);
                printf("IBC Rx Length == %u\n", pkt.length);
                printf("IBC Rx PTP == %u\n", ptp);
                printf("IBC Rx PTP sec == %llu\n", ptp_sec);
                printf("IBC Rx PTP nsec == %u\n", ptp_nsec);
            }
            pvalid = true;
        }
    } else if (n == 4) {
        if (!strcmp(s[1], "rx")) {
            struct in_addr addr;
            int rv = inet_pton(AF_INET, s[3], &addr);
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            if (rv == 1){
                HW_API::initFPGABuildID();
                HW_API::initIPRx();
                HW_API::setInBandControlIPAddress(sfp, 0, reverseEndian(addr.s_addr));
                printf("Set IBC Addr => 0x%0x\n", reverseEndian(addr.s_addr));
                pvalid = true;
            }
        } else if (!strcmp(s[1], "tx")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t count = strtoul(s[3], NULL, 0);
            for (uint32_t ibc_test_count = 0; ibc_test_count < count; ibc_test_count++) {
                bool eop;
                HW_API::initFPGABuildID();
                HW_API::initIPTx(7);
                HW_API::lockHost(true);
                if(!HW_API::getHostRdy(sfp)) {
                    printf("ERROR: Host not ready!\n");
                    HW_API::lockHost(false);
                    return 0;
                }
                printf("IBC: %u.\n", ibc_test_count);
                for (uint32_t i = 0; i < IBC_PACKET_LENGTH; i++) {
                    uint64_t IBC_PACKET_DATA_TO_SEND;
                    if ( i == 0 )
                    {
                        IBC_PACKET_DATA_TO_SEND = 0xFFFFFFFFFFFF0000 + ibc_test_count;
                    } else {
                        IBC_PACKET_DATA_TO_SEND = IBC_PACKET_DATA[i];
                    }
                    printf("IBC: 0x%016llx.\n", reverseEndian(IBC_PACKET_DATA_TO_SEND));
                    HW_API::lockHost(false);
                    HW_API::setHostPayload(sfp, reverseEndian(IBC_PACKET_DATA_TO_SEND));
                    eop = (i == IBC_PACKET_LENGTH-1);
                    HW_API::setHostCtrl(sfp, IBC_PACKET_VALID[i], eop, true, eop);
                }
                printf("Host Packet Sent!\n");
                HW_API::lockHost(false);
                pvalid = true;
            }
        }
    } else if (n == 5) {
        if (!strcmp(s[1], "tx")) {
            uint32_t sfp = strtoul(s[2], NULL, 0)%HW_API::N_10GE_CHANNELS;
            uint32_t count = strtoul(s[3], NULL, 0);
            uint32_t burstsize = strtoul(s[4], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initIPTx(7);
            if(!HW_API::getHostRdy(sfp)) {
                printf("ERROR: Host not ready!\n");
                return 0;
            }
            HW_API::lockHost(true);
            for (uint32_t ibc_test_count = 0; ibc_test_count < count; ibc_test_count++) {
                printf("IBC: %u.\n", ibc_test_count);
                for (uint32_t i = 0; i < IBC_PACKET_LENGTH; i++) {
                    uint64_t IBC_PACKET_DATA_TO_SEND;
                    if ( i == 0 )
                    {
                        IBC_PACKET_DATA_TO_SEND = 0xFFFFFFFFFFFF0000 + ibc_test_count;
                    } else {
                        IBC_PACKET_DATA_TO_SEND = IBC_PACKET_DATA[i];
                    }
                    printf("IBC: 0x%016llx.\n", reverseEndian(IBC_PACKET_DATA_TO_SEND));
                    HW_API::lockHost(false);
                    HW_API::setHostPayload(sfp, reverseEndian(IBC_PACKET_DATA_TO_SEND));
                    bool eop = (i == IBC_PACKET_LENGTH-1);
                    bool eob = (i == IBC_PACKET_LENGTH-1) &&  // last word
                               ((ibc_test_count%burstsize) == (burstsize-1) || // last packet in burst
                                (ibc_test_count == (count-1))); // last packet to be sent
                    printf("eop = %u, eob = %u\n", eop, eob);
                    HW_API::setHostCtrl(sfp, IBC_PACKET_VALID[i], eop, true, eob);
                }
                printf("Host Packet Sent!\n");
                pvalid = true;
            }
            HW_API::lockHost(false);
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execScaler(int n, char *s[])
{
    bool pvalid = false;
    if (n == 1) {
        printf("Usage: %s init <path>\n", s[0]);
        printf("       %s use <path> <0/1>\n", s[0]);
        printf("       %s config <path>\n", s[0]);
        printf("       %s status <path>\n", s[0]);
        printf("       %s debug <path>\n", s[0]);
        printf("       %s switch <path> start <type>\n", s[0]);
        printf("       %s switch <path> stop\n", s[0]);
        printf("       %s disable <path> <r/w>\n", s[0]);
        printf("       %s enable  <path> <r/w>\n", s[0]);
        printf("       %s lock <path> <page>\n", s[0]);
        printf("       %s unlock <path>\n", s[0]);
        printf("       %s prog <path> <appl_in> <tppl_in>\n", s[0]);
        printf("               <hs_width_in> <hs_front_porch_in> <hs_back_porch_in>\n");
        printf("               <alpf_0_in> <alpf_1_in> <tlpf_0_in> <tlpf_1_in>\n");
        printf("               <vs_width_in> <vs_front_porch_in> <vs_back_porch_in>\n");
        printf("               <frame_rate_num_inp> <frame_rate_den_inp>\n");
        printf("               <colour_inp>\n");
        printf("               <appl_out> <tppl_out>\n");
        printf("               <hs_width_out> <hs_front_porch_out> <hs_back_porch_out>\n");
        printf("               <alpf_0_out> <alpf_1_out> <tlpf_0_out> <tlpf_1_out>\n");
        printf("               <vs_width_out> <vs_front_porch_out> <vs_back_porch_out>\n");
        printf("               <frame_rate_num_out> <frame_rate_den_out>\n");
        printf("               <colour_out>\n");
        printf("               <crop_top> <crop_left> <crop_height> <crop_width>\n");
        printf("               <brdr_yg> <brdr_cbb> <brdr_crr>\n");
        printf("               <aspect_mode>\n");
        printf("       %s prog <path> <appl_in> <tppl_in>\n", s[0]);
        printf("               <hs_width_in> <hs_front_porch_in> <hs_back_porch_in>\n");
        printf("               <alpf_0_in> <alpf_1_in> <tlpf_0_in> <tlpf_1_in>\n");
        printf("               <vs_width_in> <vs_front_porch_in> <vs_back_porch_in>\n");
        printf("               <frame_rate_num_inp> <frame_rate_den_inp>\n");
        printf("               <colour_inp>\n");
        printf("               <appl_out> <tppl_out>\n");
        printf("               <hs_width_out> <hs_front_porch_out> <hs_back_porch_out>\n");
        printf("               <alpf_0_out> <alpf_1_out> <tlpf_0_out> <tlpf_1_out>\n");
        printf("               <vs_width_out> <vs_front_porch_out> <vs_back_porch_out>\n");
        printf("               <frame_rate_num_out> <frame_rate_den_out>\n");
        printf("               <colour_out>\n");
        printf("               <crop_top> <crop_left> <crop_height> <crop_width>\n");
        printf("               <pip_h_left> <pip_h_right> <pip_v_top> <pip_v_bottom>\n");
        printf("               <brdr_yg> <brdr_cbb> <brdr_crr>\n");
        printf("               <aspect_mode>\n");
        printf("       %s prog_pip <path> <appl_in> <tppl_in>\n", s[0]);
        printf("               <hs_width_in> <hs_front_porch_in> <hs_back_porch_in>\n");
        printf("               <alpf_0_in> <alpf_1_in> <tlpf_0_in> <tlpf_1_in>\n");
        printf("               <vs_width_in> <vs_front_porch_in> <vs_back_porch_in>\n");
        printf("               <frame_rate_num_inp> <frame_rate_den_inp>\n");
        printf("               <colour_inp>\n");
        printf("               <appl_out> <tppl_out>\n");
        printf("               <hs_width_out> <hs_front_porch_out> <hs_back_porch_out>\n");
        printf("               <alpf_0_out> <alpf_1_out> <tlpf_0_out> <tlpf_1_out>\n");
        printf("               <vs_width_out> <vs_front_porch_out> <vs_back_porch_out>\n");
        printf("               <frame_rate_num_out> <frame_rate_den_out>\n");
        printf("               <colour_out>\n");
        printf("               <crop_top> <crop_left> <crop_height> <crop_width>\n");
        printf("               <pip_h_left> <pip_h_right> <pip_v_top> <pip_v_bottom>\n");
        printf("               <brdr_yg> <brdr_cbb> <brdr_crr>\n");
        printf("               <aspect_mode>\n");
        printf("               [lock_mode]\n");
        printf("       %s prog_pip_lock <path> <lock_mode>\n", s[0]);
        printf("               <appl_out> <tppl_out>\n");
        printf("               <hs_width_out> <hs_front_porch_out> <hs_back_porch_out>\n");
        printf("               <alpf_0_out> <alpf_1_out> <tlpf_0_out> <tlpf_1_out>\n");
        printf("               <vs_width_out> <vs_front_porch_out> <vs_back_porch_out>\n");
        printf("               <frame_rate_num_out> <frame_rate_den_out>\n");
        printf("                   note : use the pip mixer raster paramters\n");
        printf("       %s loi <path> <enable>\n", s[0]);
        printf("       %s loi <path> <colour>\n", s[0]);
        printf("       %s loi <path> <space> <colour>\n", s[0]);
        printf("       %s loi <path> <s0> <s1> <s2> <s3>\n", s[0]);
        printf("       %s loii <path> <enable>\n", s[0]);
        printf("              When enabled, moves the scaler read page to the Loss of Input Image address, run finish switch to reenable output\n");
        printf("       %s extclk <path> [0/1]\n", s[0]);
        printf("       %s ref <path> [source]\n", s[0]);
        printf("       %s reflock <path>\n", s[0]);
        printf("       %s vidlock -> Sub-Menu\n", s[0]);
        printf("       %s ptp     -> Sub-Menu\n", s[0]);
        printf("       %s genlock -> Sub-Menu\n", s[0]);
        printf("\n");
        printf("   where path       = scaler path idx (0-%u)\n", (HW_API::N_SCALER_PATHS-1));
        printf("         type       = scaler switch type (0-%u)\n", HW_API::NUM_SWITCH_TYPES);
        printf("         aspect_mode= scaler aspect ratio mode (0-%u)\n", HW_API::NUM_ASPECT_MODES);
        printf("         lock_mode  = scaler lock mode (0-%u)\n", UpDownScaleWrapperType::NUM_LOCKTYPE);
        printf("                      0 - No lock, 1 - Vid Lock, 2- PTP lock, 3 - Genlock\n");
        printf("         colour_inp = 0 = RGB, 1 = YCC444, 2 = YCC422\n");
        printf("         colour_out = 0 = RGB, 1 = YCC444, 2 = YCC422\n");
        printf("         page       = page index (0-3)\n");
        printf("         colour     = w,e,k,y,c,g,m,R,b,r\n");
        printf("         s0-3       = manual sample colours\n");
        pvalid = true;
    } else if (n == 2) {
        if (!strcmp(s[1], "vidlock")) {
            printf("Usage:\n");
            printf("       %s %s lock_type <path> <lock_type>\n", s[0], s[1]);
            printf("                 lock_type  : 0 = no lock , 1 = ratelock, 2= phase lock \n");
            printf("                 turning on the phaselock will force the ratelock to be enabled as well\n");
            printf("       %s %s status <path>\n", s[0], s[1]);
            printf("       %s %s status phase_error <path> \n", s[0], s[1]);
            printf("       %s %s status resync_count <path> \n", s[0], s[1]);
            printf("       %s %s resync phase <path> \n", s[0], s[1]);
            printf("       %s %s resync <path> <resync_phase>\n", s[0], s[1]);
            printf("       %s %s ratelimit <path>\n", s[0], s[1]);
            printf("       %s %s ratelimit <path> <rate_limit>\n", s[0], s[1]);
            printf("   where resync_phase = A threshold measured in 200M clocks of phase difference between\n");
            printf("                        input and output start of frame actives, used to trip a raster resync request\n");
            printf("                        Setting to 0 disables output raster resync requests\n");
            printf("         rate_limit   = Limit range in 18bit space around current filtered control output that\n");
            printf("                        the ratelock counter is allowed to move\n");
            pvalid = true;
        } else if (!strcmp(s[1], "ptp")) {
            printf("Usage:\n");
            printf("       %s %s <path> [0/1]\n", s[0], s[1]);
            printf("       %s %s sync <path>\n", s[0], s[1]);
            printf("       %s %s jam <path>\n", s[0], s[1]);
            printf("       %s %s locked <path>\n", s[0], s[1]);
            printf("       %s %s lockreset <path>\n", s[0], s[1]);
            printf("       %s %s stats <path>\n", s[0], s[1]);
            pvalid = true;
        } else if (!strcmp(s[1], "genlock")) {
            printf("Usage:\n");
            printf("       %s %s <path> [0/1]\n", s[0], s[1]);
            printf("       %s %s jam <path>\n", s[0], s[1]);
            printf("       %s %s locked <path>\n", s[0], s[1]);
            printf("       %s %s lockreset <path>\n", s[0], s[1]);
            pvalid = true;
        }
    } else if (n == 3) {
        if (!strcmp(s[1], "init")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            pvalid = true;
        } else if (!strcmp(s[1], "config")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            HW_API::dumpScalerConfig(path);
            pvalid = true;
        } else if (!strcmp(s[1], "status")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            HW_API::dumpScalerStatus(path);
            pvalid = true;
        } else if (!strcmp(s[1], "extclk")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            bool use_ext_clk = HW_API::getUseExternalClock(path);
            if (use_ext_clk) {
              printf("Scaler %u using EXTERNAL clock\n", path);
            } else {
              printf("Scaler %u using INTERNAL clock\n", path);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "debug")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            bool oflow = HW_API::getScalerOutputOverflow(path);
            bool uflow = HW_API::getScalerOutputUnderflow(path);
            uint32_t bw = HW_API::getScalerOutputBandwidth(path);
            uint32_t in_rate = HW_API::getScalerInputRasterRate(path);
            uint32_t out_rate = HW_API::getScalerOutputRasterRate(path);
            uint32_t hsize = HW_API::getScalerOutputHCount(path);
            uint32_t vsize = HW_API::getScalerOutputVCount(path);
            uint32_t tsize = HW_API::getScalerOutputTCount(path);
            printf("Scaler Debug:\n");
            printf("  Output FIFO Overflow  = %u\n", oflow);
            printf("  Output FIFO Underflow = %u\n", uflow);
            printf("  Playout Bandwidth     = %u\n", bw);
            printf("  Input rate            = %u\n", in_rate);
            printf("  Output rate           = %u\n", out_rate);
            printf("  Playout H Count       = %u\n", hsize);
            printf("  Playout V Count       = %u\n", vsize);
            printf("  Playout T Count       = %u\n", tsize);
            HW_API::dumpScalerDebugCounters(path);
            HW_API::dumpScalerLockStatus(path);
            pvalid = true;
        } else if (!strcmp(s[1], "unlock")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            HW_API::setScalerReadPage(path, 0, false);
            pvalid = true;
        } else if (!strcmp(s[1], "ref")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            uint32_t source = HW_API::getRefClkenSource(path);
            printf("Scaler %u reference clock source: %u\n", path, source);
            pvalid = true;
        } else if (!strcmp(s[1], "reflock")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            HW_API::dumpScalerReferenceLockStatus(path);
            pvalid = true;
        } else if (!strcmp(s[1], "lock_ratelimit")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path); // This sets the RateLimiter to default value
            printf("Video Lock %u Rate Limiter is set to %u\n", path, HW_API::getScalerVidLockRateLimit(path));
            pvalid = true;
        } else if (!strcmp(s[1], "ptp")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            bool enable;
            HW_API::getScalerPTPLock(path, &enable);
            printf("PTP Lock %u Enable = %u\n", path, enable);
            HW_API::dumpScalerPTPStatus(path);
            pvalid = true;
        } else if (!strcmp(s[1], "genlock")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            bool enable;
            HW_API::getScalerGenlockLock(path, &enable);
            printf("Genlock Lock %u Enable = %u\n", path, enable);
            pvalid = true;
        } else if (!strcmp(s[1], "vidinp_buf_err")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path); // This sets the RateLimiter to default value
            printf("Video Input Buffer Error Register of Scaler %u reports as %u\n", path, HW_API::getScalerVidInpBufferError(path));
            pvalid = true;
        }
    } else if (n == 4) {
        if (!strcmp(s[1], "use")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            uint32_t en = strtoul(s[3], NULL, 0)%2;
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            HW_API::useScalerPath(path, (en > 0));
            pvalid = true;
        } else if (!strcmp(s[1], "switch")) {
            if (!strcmp(s[3], "stop")) {
                uint32_t path = strtoul(s[2], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::finishScalerSwitch(path);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "disable")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            if (!strcmp(s[3], "r")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::disableScalerReadPort(path, true);
                pvalid = true;
            } else if (!strcmp(s[3], "w")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::disableScalerWritePort(path, true);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "enable")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            if (!strcmp(s[3], "r")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::disableScalerReadPort(path, false);
                pvalid = true;
            } else if (!strcmp(s[3], "w")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::disableScalerWritePort(path, false);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "lock")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            uint32_t page = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            HW_API::setScalerReadPage(path, page, true);
            pvalid = true;
        } else if (!strcmp(s[1], "loi")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            if (!strcmp(s[3], "w")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::setLossofInputColour(path, HW_API::YCBCR422_WHITE);
                pvalid = true;
            } else if (!strcmp(s[3], "e")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::setLossofInputColour(path, HW_API::YCBCR422_GREY);
                pvalid = true;
            } else if (!strcmp(s[3], "k")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                pvalid = true;
            } else {
                uint32_t en = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::setLossofInput(path, en == 1);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "loii")) {
            if (!strcmp(s[1], "loii")) {
              HW_API::initFPGABuildID();
              uint32_t  scaler_path = strtoul(s[2], NULL, 0);
              bool      enable      = strtoul(s[3], NULL, 0);
              HW_API::initScalerPath(scaler_path);
              HW_API::setScalerLossOfInputImageEnable(scaler_path, enable);
              printf("%s Scaler %u Loss of Input Image.\n", enable?"Enabling":"Disabling", scaler_path);
              pvalid = true;
            }
        } else if (!strcmp(s[1], "extclk")) {
            uint8_t path = strtoul(s[2], NULL, 0);
            uint8_t use_ext_clk = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            HW_API::setUseExternalClock(path, use_ext_clk);
            if (use_ext_clk) {
              printf("Scaler %u set to EXTERNAL clock\n", path);
            } else {
              printf("Scaler %u set to INTERNAL clock\n", path);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "ref")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            uint32_t source = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            HW_API::setRefClkenSource(path,source);
            printf("Set scaler %u reference clock source to: %u\n", path, source);
            pvalid = true;
        } else if (!strcmp(s[1], "vidlock")) {
            if (!strcmp(s[2], "status")) {
                uint32_t path = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::dumpScalerLockStatus(path);
                pvalid = true;
            } else if (!strcmp(s[2], "ratelimit")) {
                uint32_t path = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path); // This sets the RateLimiter to default value
                printf("Video Lock %u Rate Limiter is set to %u\n", path, HW_API::getScalerVidLockRateLimit(path));
                pvalid = true;
            }
        } else if (!strcmp(s[1], "ptp")) {
            if (!strcmp(s[2], "sync")) {
              uint32_t path = strtoul(s[3], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              HW_API::setScalerPTPPhase(path);
              printf("Scaler %u PTP phase sync time recalculated.\n", path);
              pvalid = true;
            } else if (!strcmp(s[2], "jam")) {
              uint32_t path = strtoul(s[3], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              HW_API::setScalerPTPPhaseJam(path);
              printf("Scaler %u output raster phase jammed to known PTP phase.\n", path);
              pvalid = true;
            } else if (!strcmp(s[2], "locked")) {
              uint32_t path = strtoul(s[3], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              bool locked;
              HW_API::getScalerPTPReferenceLockLocked(path,&locked);
              if (locked) {
                printf("Scaler %u output reference PTP locked!\n", path);
              } else {
                printf("Scaler %u output reference PTP *NOT* locked!\n", path);
              }
              pvalid = true;
            } else if (!strcmp(s[2], "lockreset")) {
              uint32_t path = strtoul(s[3], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              HW_API::setScalerPTPReferenceLockReset(path);
              printf("Scaler %u output reference PTP locking reset.\n", path);
              pvalid = true;
            } else if (!strcmp(s[2], "stats")) {
              uint32_t path = strtoul(s[3], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              HW_API::dumpScalerPTPPlayoutTimingStats(path);
              pvalid = true;
            } else {
              uint32_t path = strtoul(s[2], NULL, 0);
              bool enable = (bool)strtoul(s[3], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              HW_API::setScalerPTPLock(path, enable);
              pvalid = true;
            }
        } else if (!strcmp(s[1], "genlock")) {
            if (!strcmp(s[2], "jam")) {
              uint32_t path = strtoul(s[3], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              HW_API::setScalerGenlockPhaseJam(path);
              printf("Scaler %u output raster phase jammed to known Genlock phase.\n", path);
              pvalid = true;
            } else if (!strcmp(s[2], "locked")) {
              uint32_t path = strtoul(s[3], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              bool locked;
              HW_API::getScalerGenlockReferenceLockLocked(path,&locked);
              if (locked) {
                printf("Scaler %u output reference Genlock locked!\n", path);
              } else {
                printf("Scaler %u output reference Genlock *NOT* locked!\n", path);
              }
              pvalid = true;
            } else if (!strcmp(s[2], "lockreset")) {
              uint32_t path = strtoul(s[3], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              HW_API::setScalerGenlockReferenceLockReset(path);
              printf("Scaler %u output reference Genlock locking reset.\n", path);
              pvalid = true;
            } else {
              uint32_t path = strtoul(s[2], NULL, 0);
              bool enable = (bool)strtoul(s[3], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              HW_API::setScalerGenlockLock(path, enable);
              pvalid = true;
            }
        }
    } else if (n == 5) {
        if (!strcmp(s[1], "switch")) {
            if (!strcmp(s[3], "start")) {
                uint32_t path = strtoul(s[2], NULL, 0);
                uint32_t type = strtoul(s[4], NULL, 0)%(HW_API::NUM_SWITCH_TYPES);
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::startScalerSwitch(path, (HW_API::ScalerSwitchType)type);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "loi")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            uint32_t space = strtoul(s[3], NULL, 0);
            if (!strcmp(s[4], "w")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_WHITE);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_WHITE);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_WHITE);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_WHITE);
                    break;
                }
                pvalid = true;
            } else if (!strcmp(s[4], "e")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_GREY);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_GREY);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_GREY);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_GREY);
                    break;
                }
                pvalid = true;
            } else if (!strcmp(s[4], "k")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_BLACK);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_BLACK);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                }
                pvalid = true;
            } else if (!strcmp(s[4], "y")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_YELLOW);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_YELLOW);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                }
                pvalid = true;
            } else if (!strcmp(s[4], "c")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_CYAN);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_CYAN);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                }
                pvalid = true;
            } else if (!strcmp(s[4], "g")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_GREEN);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_GREEN);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                }
                pvalid = true;
            } else if (!strcmp(s[4], "m")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_MAGENTA);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_MAGENTA);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                }
                pvalid = true;
            } else if (!strcmp(s[4], "R")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_CARDINAL);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_CARDINAL);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                }
                pvalid = true;
            } else if (!strcmp(s[4], "b")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_BLUE);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_BLUE);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                }
                pvalid = true;
            } else if (!strcmp(s[4], "r")) {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_RED);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_RED);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                }
                pvalid = true;
            } else {
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                switch(space) {
                  case 0:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                  case 1:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR444_BLACK);
                    break;
                  case 2:
                    HW_API::setLossofInputColour(path, HW_API::RGB444_BLACK);
                    break;
                  default:
                    HW_API::setLossofInputColour(path, HW_API::YCBCR422_BLACK);
                    break;
                }
                pvalid = true;
            }
        } else if (!strcmp(s[1], "ptp")) {
            if (!strcmp(s[2], "rxoffset")) {
              uint32_t path = strtoul(s[3], NULL, 0);
              uint32_t rxoffset = strtoul(s[4], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);
              HW_API::setScalerRxRTPOffset(path, rxoffset);
              printf("Set scaler %u PTP RX Offset to %u\n", path, rxoffset);
              pvalid = true;
            }
        } else if (!strcmp(s[1], "vidlock")) {
            if (!strcmp(s[2], "lock_type")) {
              uint8_t path = strtoul(s[3], NULL, 0);
              uint8_t hdmi_idx;
              uint8_t lock_type = strtoul(s[4], NULL, 0);
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(path);

              // Check if Scaler is associated with a HDMI output. (Checking if path is above number of HDMI outputs)
              if ((path+1) <= ((uint8_t)HW_API::getFPGACapability("INC_HDMI_NORTH_TX") + (uint8_t)HW_API::getFPGACapability("INC_HDMI_SOUTH_TX"))){
                // Remap the single North HDMI case
                if (path == 0 && (HW_API::getFPGACapability("INC_HDMI_SOUTH_TX") == 0) && (HW_API::getFPGACapability("INC_HDMI_NORTH_TX") > 0)){
                    hdmi_idx = 1;
                } else {
                    hdmi_idx = path;
                }
                HW_API::initHdmi(hdmi_idx);
                if (lock_type == 0){
                  printf("Disable locking on HDMI Output %u\n", hdmi_idx);
                  HW_API::setHdmiTxSi570LockEnable(hdmi_idx, false);
                } else {
                  printf("Enable locking on HDMI Output %u\n", hdmi_idx);
                  HW_API::setHdmiTxSi570LockEnable(hdmi_idx, true);
                }
              }
              HW_API::setScalerVidLockLockType(path, lock_type);
              printf("Video Lock %u locktype set to %u\n", path, lock_type);
              //HW_API::setScalerRasterVPhasetoActive(path,true);
              pvalid = true;
          } else if (!strcmp(s[2], "status")) {
              if (!strcmp(s[3], "phase_error")) {
                uint8_t path = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                HW_API::dumpScalerLockPhase(path);
                pvalid = true;
              } else if (!strcmp(s[3], "resync_count")) {
                uint8_t path = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path);
                uint32_t count = HW_API::getScalerLockResyncCount(path);
                printf("Current Phase Resync Count = %u\n", count);
                pvalid = true;
              }
          } else if (!strcmp(s[2], "resync")) {
              if (!strcmp(s[3], "phase")) {
                uint8_t path = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path); // This sets the Phase to default (0x20000 at time of writing)
                printf("Video Lock %u Resync Phase Threshold is set to %u\n", path, HW_API::getScalerVidLockResyncPhase(path));
                pvalid = true;
              } else {
                uint32_t path = strtoul(s[3], NULL, 0);
                uint32_t phase = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initScalerPath(path); // This sets the Phase to default (0x20000 at time of writing)
                HW_API::setScalerVidLockResyncPhase(path,phase);
                pvalid = true;
              }
          } else if (!strcmp(s[2], "ratelimit")) {
            uint8_t path = strtoul(s[3], NULL, 0);
            uint32_t limit = strtoul(s[4], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path); // This sets the Phase to default (0x20000 at time of writing)
            HW_API::setScalerVidLockRateLimit(path,limit);
            printf("Setting Video Lock %u Rate Limiter is set to %u\n", path, limit);
            pvalid = true;
          }
        }
    } else if (n == 6) {
        if (!strcmp(s[1], "raster_phase")) {
            uint32_t path   = strtoul(s[2], NULL, 0);
            uint32_t out    = strtoul(s[3], NULL, 0);
            uint32_t hphase  = strtoul(s[4], NULL, 0);
            uint32_t vphase  = strtoul(s[5], NULL, 0);
            HW_API::setScalerRasterPhase(path,out,hphase,vphase);
            pvalid = true;
        }
    } else if (n == 7) {
        if (!strcmp(s[1], "loi")) {
            uint32_t path = strtoul(s[2], NULL, 0);
            HW_API::MixerColour colour;
            colour.sample_0 = strtoul(s[3], NULL, 0);
            colour.sample_1 = strtoul(s[4], NULL, 0);
            colour.sample_2 = strtoul(s[5], NULL, 0);
            colour.sample_3 = strtoul(s[6], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initScalerPath(path);
            HW_API::setLossofInputColour(path, &colour);
            pvalid = true;
        }
    } else if (n == 18) {
        if (!strcmp(s[1], "prog_pip_lock")) {
            uint32_t path               = strtoul(s[ 2], NULL, 0);
            uint32_t lock_mode          = strtoul(s[ 3], NULL, 0);
            uint32_t appl_out           = strtoul(s[ 4], NULL, 0);
            uint32_t tppl_out           = strtoul(s[ 5], NULL, 0);
            uint32_t hs_width_out       = strtoul(s[ 6], NULL, 0);
            uint32_t hs_front_porch_out = strtoul(s[ 7], NULL, 0);
            uint32_t hs_back_porch_out  = strtoul(s[ 8], NULL, 0);
            uint32_t alpf_0_out         = strtoul(s[ 9], NULL, 0);
            uint32_t alpf_1_out         = strtoul(s[10], NULL, 0);
            uint32_t tlpf_0_out         = strtoul(s[11], NULL, 0);
            uint32_t tlpf_1_out         = strtoul(s[12], NULL, 0);
            uint32_t vs_width_out       = strtoul(s[13], NULL, 0);
            uint32_t vs_front_porch_out = strtoul(s[14], NULL, 0);
            uint32_t vs_back_porch_out  = strtoul(s[15], NULL, 0);
            uint32_t frame_rate_num_out = strtoul(s[16], NULL, 0);
            uint32_t frame_rate_den_out = strtoul(s[17], NULL, 0);

            RasterTypes::CVTParameters out_params;
            HW_API::ScalerFrameRate out_rate;
            out_params.appl           = appl_out;
            out_params.tppl           = tppl_out;
            out_params.hs_width       = hs_width_out;
            out_params.hs_front_porch = hs_front_porch_out;
            out_params.hs_back_porch  = hs_back_porch_out;
            out_params.alpf[0]        = alpf_0_out;
            out_params.alpf[1]        = alpf_1_out;
            out_params.tlpf[0]        = tlpf_0_out;
            out_params.tlpf[1]        = tlpf_1_out;
            out_params.vs_width       = vs_width_out;
            out_params.vs_front_porch = vs_front_porch_out;
            out_params.vs_back_porch  = vs_back_porch_out;
            out_rate.frame_rate_num   = frame_rate_num_out;
            out_rate.frame_rate_den   = frame_rate_den_out;

            HW_API::initFPGABuildID();
            HW_API::initVidProc();
            HW_API::initScalerPath(path);
            int result = -1;

            // Product specific RS4K
            if (path == 0) {
              result = HW_API::setScalerPipPathLock(path, 0, out_params, out_rate, lock_mode);
            }
            if (result == 0) {
              printf("Success\n");
            } else {
              printf("Failed\n");
            }
            pvalid = true;
        }
    } else if (n == 41) {
        if (!strcmp(s[1], "prog")) {
            uint32_t path               = strtoul(s[2], NULL, 0);
            uint32_t appl_in            = strtoul(s[3], NULL, 0);
            uint32_t tppl_in            = strtoul(s[4], NULL, 0);
            uint32_t hs_width_in        = strtoul(s[5], NULL, 0);
            uint32_t hs_front_porch_in  = strtoul(s[6], NULL, 0);
            uint32_t hs_back_porch_in   = strtoul(s[7], NULL, 0);
            uint32_t alpf_0_in          = strtoul(s[8], NULL, 0);
            uint32_t alpf_1_in          = strtoul(s[9], NULL, 0);
            uint32_t tlpf_0_in          = strtoul(s[10], NULL, 0);
            uint32_t tlpf_1_in          = strtoul(s[11], NULL, 0);
            uint32_t vs_width_in        = strtoul(s[12], NULL, 0);
            uint32_t vs_front_porch_in  = strtoul(s[13], NULL, 0);
            uint32_t vs_back_porch_in   = strtoul(s[14], NULL, 0);
            uint32_t frame_rate_num_inp = strtoul(s[15], NULL, 0);
            uint32_t frame_rate_den_inp = strtoul(s[16], NULL, 0);
            uint32_t colour_inp         = strtoul(s[17], NULL, 0);

            uint32_t appl_out           = strtoul(s[18], NULL, 0);
            uint32_t tppl_out           = strtoul(s[19], NULL, 0);
            uint32_t hs_width_out       = strtoul(s[20], NULL, 0);
            uint32_t hs_front_porch_out = strtoul(s[21], NULL, 0);
            uint32_t hs_back_porch_out  = strtoul(s[22], NULL, 0);
            uint32_t alpf_0_out         = strtoul(s[23], NULL, 0);
            uint32_t alpf_1_out         = strtoul(s[24], NULL, 0);
            uint32_t tlpf_0_out         = strtoul(s[25], NULL, 0);
            uint32_t tlpf_1_out         = strtoul(s[26], NULL, 0);
            uint32_t vs_width_out       = strtoul(s[27], NULL, 0);
            uint32_t vs_front_porch_out = strtoul(s[28], NULL, 0);
            uint32_t vs_back_porch_out  = strtoul(s[29], NULL, 0);
            uint32_t frame_rate_num_out = strtoul(s[30], NULL, 0);
            uint32_t frame_rate_den_out = strtoul(s[31], NULL, 0);
            uint32_t colour_out         = strtoul(s[32], NULL, 0);

            uint32_t crop_top           = strtoul(s[33], NULL, 0);
            uint32_t crop_left          = strtoul(s[34], NULL, 0);
            uint32_t crop_height        = strtoul(s[35], NULL, 0);
            uint32_t crop_width         = strtoul(s[36], NULL, 0);
            uint32_t brdr_yg            = strtoul(s[37], NULL, 0);
            uint32_t brdr_cbb           = strtoul(s[38], NULL, 0);
            uint32_t brdr_crr           = strtoul(s[39], NULL, 0);
            uint32_t mode               = strtoul(s[40], NULL, 0)%HW_API::NUM_ASPECT_MODES;

            RasterTypes::CVTParameters in_params;
            HW_API::ScalerFrameRate in_rate;
            RasterTypes::CVTParameters out_params;
            HW_API::ScalerFrameRate out_rate;
            HW_API::ScalerSettings settings;

            in_params.appl            = appl_in;
            in_params.tppl            = tppl_in;
            in_params.hs_width        = hs_width_in;
            in_params.hs_front_porch  = hs_front_porch_in;
            in_params.hs_back_porch   = hs_back_porch_in;
            in_params.alpf[0]         = alpf_0_in;
            in_params.alpf[1]         = alpf_1_in;
            in_params.tlpf[0]         = tlpf_0_in;
            in_params.tlpf[1]         = tlpf_1_in;
            in_params.vs_width        = vs_width_in;
            in_params.vs_front_porch  = vs_front_porch_in;
            in_params.vs_back_porch   = vs_back_porch_in;
            in_rate.frame_rate_num    = frame_rate_num_inp;
            in_rate.frame_rate_den    = frame_rate_den_inp;

            out_params.appl           = appl_out;
            out_params.tppl           = tppl_out;
            out_params.hs_width       = hs_width_out;
            out_params.hs_front_porch = hs_front_porch_out;
            out_params.hs_back_porch  = hs_back_porch_out;
            out_params.alpf[0]        = alpf_0_out;
            out_params.alpf[1]        = alpf_1_out;
            out_params.tlpf[0]        = tlpf_0_out;
            out_params.tlpf[1]        = tlpf_1_out;
            out_params.vs_width       = vs_width_out;
            out_params.vs_front_porch = vs_front_porch_out;
            out_params.vs_back_porch  = vs_back_porch_out;
            out_rate.frame_rate_num   = frame_rate_num_out;
            out_rate.frame_rate_den   = frame_rate_den_out;

            settings.crop_top         = (double)crop_top;
            settings.crop_left        = (double)crop_left;
            settings.crop_height      = (double)crop_height;
            settings.crop_width       = (double)crop_width;
            settings.aspect_mode      = (HW_API::ScalerAspectMode)mode;
            settings.brdr_yg          = brdr_yg;
            settings.brdr_cbb         = brdr_cbb;
            settings.brdr_crr         = brdr_crr;

            printf("Setting Scaler with:\n");

            printf(" appl_in             = %u\n", in_params.appl            );
            printf(" tppl_in             = %u\n", in_params.tppl            );
            printf(" hs_width_in         = %u\n", in_params.hs_width        );
            printf(" hs_front_porch_in   = %u\n", in_params.hs_front_porch  );
            printf(" hs_back_porch_in    = %u\n", in_params.hs_back_porch   );
            printf(" alpf_0_in           = %u\n", in_params.alpf[0]         );
            printf(" alpf_1_in           = %u\n", in_params.alpf[1]         );
            printf(" tlpf_0_in           = %u\n", in_params.tlpf[0]         );
            printf(" tlpf_1_in           = %u\n", in_params.tlpf[1]         );
            printf(" vs_width_in         = %u\n", in_params.vs_width        );
            printf(" vs_front_porch_in   = %u\n", in_params.vs_front_porch  );
            printf(" vs_back_porch_in    = %u\n", in_params.vs_back_porch   );
            printf(" inp frame_rate_num  = %u\n", in_rate.frame_rate_num    );
            printf(" inp frame_rate_den  = %u\n", in_rate.frame_rate_den    );
            printf(" input colour        = %u\n", colour_inp                );

            printf(" appl_out            = %u\n", out_params.appl           );
            printf(" tppl_out            = %u\n", out_params.tppl           );
            printf(" hs_width_out        = %u\n", out_params.hs_width       );
            printf(" hs_front_porch_out  = %u\n", out_params.hs_front_porch );
            printf(" hs_back_porch_out   = %u\n", out_params.hs_back_porch  );
            printf(" alpf_0_out          = %u\n", out_params.alpf[0]        );
            printf(" alpf_1_out          = %u\n", out_params.alpf[1]        );
            printf(" tlpf_0_out          = %u\n", out_params.tlpf[0]        );
            printf(" tlpf_1_out          = %u\n", out_params.tlpf[1]        );
            printf(" vs_width_out        = %u\n", out_params.vs_width       );
            printf(" vs_front_porch_out  = %u\n", out_params.vs_front_porch );
            printf(" vs_back_porch_out   = %u\n", out_params.vs_back_porch  );
            printf(" out frame_rate_num  = %u\n", out_rate.frame_rate_num   );
            printf(" out frame_rate_den  = %u\n", out_rate.frame_rate_den   );
            printf(" output colour       = %u\n", colour_out                );

            printf(" crop_top            = %f\n", settings.crop_top         );
            printf(" crop_left           = %f\n", settings.crop_left        );
            printf(" crop_height         = %f\n", settings.crop_height      );
            printf(" crop_width          = %f\n", settings.crop_width       );
            printf(" aspect_mode         = %u\n", settings.aspect_mode      );
            printf(" brdr_yg             = %u\n", settings.brdr_yg          );
            printf(" brdr_cbb            = %u\n", settings.brdr_cbb         );
            printf(" brdr_crr            = %u\n", settings.brdr_crr         );

            HW_API::initFPGABuildID();
            HW_API::initVidProc();
            HW_API::initScalerPath(path);
            HW_API::switchScalerInput(path, in_params, in_rate, (HW_API::scColourFormat_type)colour_inp);
            HW_API::switchScalerPathSettings(path, &settings);
            HW_API::setScalerOutput(path, out_params, out_rate, (HW_API::scColourFormat_type)colour_out);
            HW_API::useScalerPath(path, true);
            HW_API::dumpScalerConfig(path);
            HW_API::dumpScalerStatus(path);
            pvalid = true;
        }
    } else if (n == 45) {
        if (!strcmp(s[1], "prog")) {
            uint32_t path               = strtoul(s[2], NULL, 0);
            uint32_t appl_in            = strtoul(s[3], NULL, 0);
            uint32_t tppl_in            = strtoul(s[4], NULL, 0);
            uint32_t hs_width_in        = strtoul(s[5], NULL, 0);
            uint32_t hs_front_porch_in  = strtoul(s[6], NULL, 0);
            uint32_t hs_back_porch_in   = strtoul(s[7], NULL, 0);
            uint32_t alpf_0_in          = strtoul(s[8], NULL, 0);
            uint32_t alpf_1_in          = strtoul(s[9], NULL, 0);
            uint32_t tlpf_0_in          = strtoul(s[10], NULL, 0);
            uint32_t tlpf_1_in          = strtoul(s[11], NULL, 0);
            uint32_t vs_width_in        = strtoul(s[12], NULL, 0);
            uint32_t vs_front_porch_in  = strtoul(s[13], NULL, 0);
            uint32_t vs_back_porch_in   = strtoul(s[14], NULL, 0);
            uint32_t frame_rate_num_inp = strtoul(s[15], NULL, 0);
            uint32_t frame_rate_den_inp = strtoul(s[16], NULL, 0);
            uint32_t colour_inp         = strtoul(s[17], NULL, 0);

            uint32_t appl_out           = strtoul(s[18], NULL, 0);
            uint32_t tppl_out           = strtoul(s[19], NULL, 0);
            uint32_t hs_width_out       = strtoul(s[20], NULL, 0);
            uint32_t hs_front_porch_out = strtoul(s[21], NULL, 0);
            uint32_t hs_back_porch_out  = strtoul(s[22], NULL, 0);
            uint32_t alpf_0_out         = strtoul(s[23], NULL, 0);
            uint32_t alpf_1_out         = strtoul(s[24], NULL, 0);
            uint32_t tlpf_0_out         = strtoul(s[25], NULL, 0);
            uint32_t tlpf_1_out         = strtoul(s[26], NULL, 0);
            uint32_t vs_width_out       = strtoul(s[27], NULL, 0);
            uint32_t vs_front_porch_out = strtoul(s[28], NULL, 0);
            uint32_t vs_back_porch_out  = strtoul(s[29], NULL, 0);
            uint32_t frame_rate_num_out = strtoul(s[30], NULL, 0);
            uint32_t frame_rate_den_out = strtoul(s[31], NULL, 0);
            uint32_t colour_out         = strtoul(s[32], NULL, 0);

            uint32_t crop_top           = strtoul(s[33], NULL, 0);
            uint32_t crop_left          = strtoul(s[34], NULL, 0);
            uint32_t crop_height        = strtoul(s[35], NULL, 0);
            uint32_t crop_width         = strtoul(s[36], NULL, 0);

            uint32_t pip_h_left         = strtoul(s[37], NULL, 0);
            uint32_t pip_h_right        = strtoul(s[38], NULL, 0);
            uint32_t pip_v_top          = strtoul(s[39], NULL, 0);
            uint32_t pip_v_bottom       = strtoul(s[40], NULL, 0);

            uint32_t brdr_yg            = strtoul(s[41], NULL, 0);
            uint32_t brdr_cbb           = strtoul(s[42], NULL, 0);
            uint32_t brdr_crr           = strtoul(s[43], NULL, 0);
            uint32_t mode               = strtoul(s[44], NULL, 0)%HW_API::NUM_ASPECT_MODES;

            RasterTypes::CVTParameters in_params;
            HW_API::ScalerFrameRate in_rate;
            RasterTypes::CVTParameters out_params;
            HW_API::ScalerFrameRate out_rate;
            HW_API::ScalerPipSettings pip_settings;
            HW_API::ScalerSettings settings;

            in_params.appl            = appl_in;
            in_params.tppl            = tppl_in;
            in_params.hs_width        = hs_width_in;
            in_params.hs_front_porch  = hs_front_porch_in;
            in_params.hs_back_porch   = hs_back_porch_in;
            in_params.alpf[0]         = alpf_0_in;
            in_params.alpf[1]         = alpf_1_in;
            in_params.tlpf[0]         = tlpf_0_in;
            in_params.tlpf[1]         = tlpf_1_in;
            in_params.vs_width        = vs_width_in;
            in_params.vs_front_porch  = vs_front_porch_in;
            in_params.vs_back_porch   = vs_back_porch_in;
            in_rate.frame_rate_num    = frame_rate_num_inp;
            in_rate.frame_rate_den    = frame_rate_den_inp;

            out_params.appl           = appl_out;
            out_params.tppl           = tppl_out;
            out_params.hs_width       = hs_width_out;
            out_params.hs_front_porch = hs_front_porch_out;
            out_params.hs_back_porch  = hs_back_porch_out;
            out_params.alpf[0]        = alpf_0_out;
            out_params.alpf[1]        = alpf_1_out;
            out_params.tlpf[0]        = tlpf_0_out;
            out_params.tlpf[1]        = tlpf_1_out;
            out_params.vs_width       = vs_width_out;
            out_params.vs_front_porch = vs_front_porch_out;
            out_params.vs_back_porch  = vs_back_porch_out;
            out_rate.frame_rate_num   = frame_rate_num_out;
            out_rate.frame_rate_den   = frame_rate_den_out;

            settings.crop_top         = (double)crop_top;
            settings.crop_left        = (double)crop_left;
            settings.crop_height      = (double)crop_height;
            settings.crop_width       = (double)crop_width;
            settings.aspect_mode      = (HW_API::ScalerAspectMode)mode;
            settings.brdr_yg          = brdr_yg;
            settings.brdr_cbb         = brdr_cbb;
            settings.brdr_crr         = brdr_crr;

            pip_settings.pip_h_left   = pip_h_left    ;
            pip_settings.pip_h_right  = pip_h_right   ;
            pip_settings.pip_v_top    = pip_v_top     ;
            pip_settings.pip_v_bottom = pip_v_bottom  ;

            printf("Setting Scaler with:\n");

            printf(" appl_in             = %u\n", in_params.appl            );
            printf(" tppl_in             = %u\n", in_params.tppl            );
            printf(" hs_width_in         = %u\n", in_params.hs_width        );
            printf(" hs_front_porch_in   = %u\n", in_params.hs_front_porch  );
            printf(" hs_back_porch_in    = %u\n", in_params.hs_back_porch   );
            printf(" alpf_0_in           = %u\n", in_params.alpf[0]         );
            printf(" alpf_1_in           = %u\n", in_params.alpf[1]         );
            printf(" tlpf_0_in           = %u\n", in_params.tlpf[0]         );
            printf(" tlpf_1_in           = %u\n", in_params.tlpf[1]         );
            printf(" vs_width_in         = %u\n", in_params.vs_width        );
            printf(" vs_front_porch_in   = %u\n", in_params.vs_front_porch  );
            printf(" vs_back_porch_in    = %u\n", in_params.vs_back_porch   );
            printf(" inp frame_rate_num  = %u\n", in_rate.frame_rate_num    );
            printf(" inp frame_rate_den  = %u\n", in_rate.frame_rate_den    );
            printf(" input colour        = %u\n", colour_inp                );

            printf(" appl_out            = %u\n", out_params.appl           );
            printf(" tppl_out            = %u\n", out_params.tppl           );
            printf(" hs_width_out        = %u\n", out_params.hs_width       );
            printf(" hs_front_porch_out  = %u\n", out_params.hs_front_porch );
            printf(" hs_back_porch_out   = %u\n", out_params.hs_back_porch  );
            printf(" alpf_0_out          = %u\n", out_params.alpf[0]        );
            printf(" alpf_1_out          = %u\n", out_params.alpf[1]        );
            printf(" tlpf_0_out          = %u\n", out_params.tlpf[0]        );
            printf(" tlpf_1_out          = %u\n", out_params.tlpf[1]        );
            printf(" vs_width_out        = %u\n", out_params.vs_width       );
            printf(" vs_front_porch_out  = %u\n", out_params.vs_front_porch );
            printf(" vs_back_porch_out   = %u\n", out_params.vs_back_porch  );
            printf(" out frame_rate_num  = %u\n", out_rate.frame_rate_num   );
            printf(" out frame_rate_den  = %u\n", out_rate.frame_rate_den   );
            printf(" output colour       = %u\n", colour_out                );

            printf(" crop_top            = %f\n", settings.crop_top         );
            printf(" crop_left           = %f\n", settings.crop_left        );
            printf(" crop_height         = %f\n", settings.crop_height      );
            printf(" crop_width          = %f\n", settings.crop_width       );
            printf(" aspect_mode         = %u\n", settings.aspect_mode      );
            printf(" brdr_yg             = %u\n", settings.brdr_yg          );
            printf(" brdr_cbb            = %u\n", settings.brdr_cbb         );
            printf(" brdr_crr            = %u\n", settings.brdr_crr         );

            printf(" pip_h_left          = %u\n", pip_settings.pip_h_left    );
            printf(" pip_h_right         = %u\n", pip_settings.pip_h_right   );
            printf(" pip_v_top           = %u\n", pip_settings.pip_v_top     );
            printf(" pip_v_bottom        = %u\n", pip_settings.pip_v_bottom  );

            HW_API::initFPGABuildID();
            HW_API::initVidProc();
            HW_API::initScalerPath(path);
            HW_API::switchScalerInput(path, in_params, in_rate, (HW_API::scColourFormat_type)colour_inp);
            HW_API::switchScalerPathSettings(path, &settings);
            HW_API::setScalerOutputPip(path, pip_settings, out_params, out_rate, (HW_API::scColourFormat_type)colour_out);

            HW_API::useScalerPath(path, true);
            HW_API::dumpScalerConfig(path);
            HW_API::dumpScalerStatus(path);
            pvalid = true;
        } else if (!strcmp(s[1], "prog_pip")) {
            uint32_t path               = strtoul(s[2], NULL, 0);
            uint32_t appl_in            = strtoul(s[3], NULL, 0);
            uint32_t tppl_in            = strtoul(s[4], NULL, 0);
            uint32_t hs_width_in        = strtoul(s[5], NULL, 0);
            uint32_t hs_front_porch_in  = strtoul(s[6], NULL, 0);
            uint32_t hs_back_porch_in   = strtoul(s[7], NULL, 0);
            uint32_t alpf_0_in          = strtoul(s[8], NULL, 0);
            uint32_t alpf_1_in          = strtoul(s[9], NULL, 0);
            uint32_t tlpf_0_in          = strtoul(s[10], NULL, 0);
            uint32_t tlpf_1_in          = strtoul(s[11], NULL, 0);
            uint32_t vs_width_in        = strtoul(s[12], NULL, 0);
            uint32_t vs_front_porch_in  = strtoul(s[13], NULL, 0);
            uint32_t vs_back_porch_in   = strtoul(s[14], NULL, 0);
            uint32_t frame_rate_num_inp = strtoul(s[15], NULL, 0);
            uint32_t frame_rate_den_inp = strtoul(s[16], NULL, 0);
            uint32_t colour_inp         = strtoul(s[17], NULL, 0);

            uint32_t appl_out           = strtoul(s[18], NULL, 0);
            uint32_t tppl_out           = strtoul(s[19], NULL, 0);
            uint32_t hs_width_out       = strtoul(s[20], NULL, 0);
            uint32_t hs_front_porch_out = strtoul(s[21], NULL, 0);
            uint32_t hs_back_porch_out  = strtoul(s[22], NULL, 0);
            uint32_t alpf_0_out         = strtoul(s[23], NULL, 0);
            uint32_t alpf_1_out         = strtoul(s[24], NULL, 0);
            uint32_t tlpf_0_out         = strtoul(s[25], NULL, 0);
            uint32_t tlpf_1_out         = strtoul(s[26], NULL, 0);
            uint32_t vs_width_out       = strtoul(s[27], NULL, 0);
            uint32_t vs_front_porch_out = strtoul(s[28], NULL, 0);
            uint32_t vs_back_porch_out  = strtoul(s[29], NULL, 0);
            uint32_t frame_rate_num_out = strtoul(s[30], NULL, 0);
            uint32_t frame_rate_den_out = strtoul(s[31], NULL, 0);
            uint32_t colour_out         = strtoul(s[32], NULL, 0);

            uint32_t crop_top           = strtoul(s[33], NULL, 0);
            uint32_t crop_left          = strtoul(s[34], NULL, 0);
            uint32_t crop_height        = strtoul(s[35], NULL, 0);
            uint32_t crop_width         = strtoul(s[36], NULL, 0);

            uint32_t pip_h_left         = strtoul(s[37], NULL, 0);
            uint32_t pip_h_right        = strtoul(s[38], NULL, 0);
            uint32_t pip_v_top          = strtoul(s[39], NULL, 0);
            uint32_t pip_v_bottom       = strtoul(s[40], NULL, 0);

            uint32_t brdr_yg            = strtoul(s[41], NULL, 0);
            uint32_t brdr_cbb           = strtoul(s[42], NULL, 0);
            uint32_t brdr_crr           = strtoul(s[43], NULL, 0);
            uint32_t mode               = strtoul(s[44], NULL, 0)%HW_API::NUM_ASPECT_MODES;

            RasterTypes::CVTParameters in_params;
            HW_API::ScalerFrameRate in_rate;
            RasterTypes::CVTParameters out_params;
            HW_API::ScalerFrameRate out_rate;
            HW_API::ScalerPipSettings pip_settings;
            HW_API::ScalerSettings settings;

            in_params.appl            = appl_in;
            in_params.tppl            = tppl_in;
            in_params.hs_width        = hs_width_in;
            in_params.hs_front_porch  = hs_front_porch_in;
            in_params.hs_back_porch   = hs_back_porch_in;
            in_params.alpf[0]         = alpf_0_in;
            in_params.alpf[1]         = alpf_1_in;
            in_params.tlpf[0]         = tlpf_0_in;
            in_params.tlpf[1]         = tlpf_1_in;
            in_params.vs_width        = vs_width_in;
            in_params.vs_front_porch  = vs_front_porch_in;
            in_params.vs_back_porch   = vs_back_porch_in;
            in_rate.frame_rate_num    = frame_rate_num_inp;
            in_rate.frame_rate_den    = frame_rate_den_inp;

            out_params.appl           = appl_out;
            out_params.tppl           = tppl_out;
            out_params.hs_width       = hs_width_out;
            out_params.hs_front_porch = hs_front_porch_out;
            out_params.hs_back_porch  = hs_back_porch_out;
            out_params.alpf[0]        = alpf_0_out;
            out_params.alpf[1]        = alpf_1_out;
            out_params.tlpf[0]        = tlpf_0_out;
            out_params.tlpf[1]        = tlpf_1_out;
            out_params.vs_width       = vs_width_out;
            out_params.vs_front_porch = vs_front_porch_out;
            out_params.vs_back_porch  = vs_back_porch_out;
            out_rate.frame_rate_num   = frame_rate_num_out;
            out_rate.frame_rate_den   = frame_rate_den_out;

            settings.crop_top         = (double)crop_top;
            settings.crop_left        = (double)crop_left;
            settings.crop_height      = (double)crop_height;
            settings.crop_width       = (double)crop_width;
            settings.aspect_mode      = (HW_API::ScalerAspectMode)mode;
            settings.brdr_yg          = brdr_yg;
            settings.brdr_cbb         = brdr_cbb;
            settings.brdr_crr         = brdr_crr;

            pip_settings.pip_h_left   = pip_h_left    ;
            pip_settings.pip_h_right  = pip_h_right   ;
            pip_settings.pip_v_top    = pip_v_top     ;
            pip_settings.pip_v_bottom = pip_v_bottom  ;

            printf("Setting Scaler with:\n");

            printf(" appl_in             = %u\n", in_params.appl            );
            printf(" tppl_in             = %u\n", in_params.tppl            );
            printf(" hs_width_in         = %u\n", in_params.hs_width        );
            printf(" hs_front_porch_in   = %u\n", in_params.hs_front_porch  );
            printf(" hs_back_porch_in    = %u\n", in_params.hs_back_porch   );
            printf(" alpf_0_in           = %u\n", in_params.alpf[0]         );
            printf(" alpf_1_in           = %u\n", in_params.alpf[1]         );
            printf(" tlpf_0_in           = %u\n", in_params.tlpf[0]         );
            printf(" tlpf_1_in           = %u\n", in_params.tlpf[1]         );
            printf(" vs_width_in         = %u\n", in_params.vs_width        );
            printf(" vs_front_porch_in   = %u\n", in_params.vs_front_porch  );
            printf(" vs_back_porch_in    = %u\n", in_params.vs_back_porch   );
            printf(" inp frame_rate_num  = %u\n", in_rate.frame_rate_num    );
            printf(" inp frame_rate_den  = %u\n", in_rate.frame_rate_den    );
            printf(" input colour        = %u\n", colour_inp                );

            printf(" appl_out            = %u\n", out_params.appl           );
            printf(" tppl_out            = %u\n", out_params.tppl           );
            printf(" hs_width_out        = %u\n", out_params.hs_width       );
            printf(" hs_front_porch_out  = %u\n", out_params.hs_front_porch );
            printf(" hs_back_porch_out   = %u\n", out_params.hs_back_porch  );
            printf(" alpf_0_out          = %u\n", out_params.alpf[0]        );
            printf(" alpf_1_out          = %u\n", out_params.alpf[1]        );
            printf(" tlpf_0_out          = %u\n", out_params.tlpf[0]        );
            printf(" tlpf_1_out          = %u\n", out_params.tlpf[1]        );
            printf(" vs_width_out        = %u\n", out_params.vs_width       );
            printf(" vs_front_porch_out  = %u\n", out_params.vs_front_porch );
            printf(" vs_back_porch_out   = %u\n", out_params.vs_back_porch  );
            printf(" out frame_rate_num  = %u\n", out_rate.frame_rate_num   );
            printf(" out frame_rate_den  = %u\n", out_rate.frame_rate_den   );
            printf(" output colour       = %u\n", colour_out                );

            printf(" crop_top            = %f\n", settings.crop_top         );
            printf(" crop_left           = %f\n", settings.crop_left        );
            printf(" crop_height         = %f\n", settings.crop_height      );
            printf(" crop_width          = %f\n", settings.crop_width       );
            printf(" aspect_mode         = %u\n", settings.aspect_mode      );
            printf(" brdr_yg             = %u\n", settings.brdr_yg          );
            printf(" brdr_cbb            = %u\n", settings.brdr_cbb         );
            printf(" brdr_crr            = %u\n", settings.brdr_crr         );

            printf(" pip_h_left          = %u\n", pip_settings.pip_h_left    );
            printf(" pip_h_right         = %u\n", pip_settings.pip_h_right   );
            printf(" pip_v_top           = %u\n", pip_settings.pip_v_top     );
            printf(" pip_v_bottom        = %u\n", pip_settings.pip_v_bottom  );

            HW_API::initFPGABuildID();
            HW_API::initVidProc();
            HW_API::initScalerPath(path);
            HW_API::switchScalerInput(path, in_params, in_rate, (HW_API::scColourFormat_type)colour_inp);
            HW_API::switchScalerPathSettings(path, &settings);
            int result = HW_API::setScalerPipPath(path, pip_settings, out_params, out_rate, (HW_API::scColourFormat_type)colour_out);
            if (result == 0) {
              printf("Success\n");
            } else {
              printf("Failed\n");
            }

            HW_API::useScalerPath(path, true);
            HW_API::dumpScalerConfig(path);
            HW_API::dumpScalerStatus(path);
            pvalid = true;
        }
    } else if (n == 46) {
      if (!strcmp(s[1], "prog_pip")) {
            uint32_t path               = strtoul(s[2], NULL, 0);
            uint32_t appl_in            = strtoul(s[3], NULL, 0);
            uint32_t tppl_in            = strtoul(s[4], NULL, 0);
            uint32_t hs_width_in        = strtoul(s[5], NULL, 0);
            uint32_t hs_front_porch_in  = strtoul(s[6], NULL, 0);
            uint32_t hs_back_porch_in   = strtoul(s[7], NULL, 0);
            uint32_t alpf_0_in          = strtoul(s[8], NULL, 0);
            uint32_t alpf_1_in          = strtoul(s[9], NULL, 0);
            uint32_t tlpf_0_in          = strtoul(s[10], NULL, 0);
            uint32_t tlpf_1_in          = strtoul(s[11], NULL, 0);
            uint32_t vs_width_in        = strtoul(s[12], NULL, 0);
            uint32_t vs_front_porch_in  = strtoul(s[13], NULL, 0);
            uint32_t vs_back_porch_in   = strtoul(s[14], NULL, 0);
            uint32_t frame_rate_num_inp = strtoul(s[15], NULL, 0);
            uint32_t frame_rate_den_inp = strtoul(s[16], NULL, 0);
            uint32_t colour_inp         = strtoul(s[17], NULL, 0);

            uint32_t appl_out           = strtoul(s[18], NULL, 0);
            uint32_t tppl_out           = strtoul(s[19], NULL, 0);
            uint32_t hs_width_out       = strtoul(s[20], NULL, 0);
            uint32_t hs_front_porch_out = strtoul(s[21], NULL, 0);
            uint32_t hs_back_porch_out  = strtoul(s[22], NULL, 0);
            uint32_t alpf_0_out         = strtoul(s[23], NULL, 0);
            uint32_t alpf_1_out         = strtoul(s[24], NULL, 0);
            uint32_t tlpf_0_out         = strtoul(s[25], NULL, 0);
            uint32_t tlpf_1_out         = strtoul(s[26], NULL, 0);
            uint32_t vs_width_out       = strtoul(s[27], NULL, 0);
            uint32_t vs_front_porch_out = strtoul(s[28], NULL, 0);
            uint32_t vs_back_porch_out  = strtoul(s[29], NULL, 0);
            uint32_t frame_rate_num_out = strtoul(s[30], NULL, 0);
            uint32_t frame_rate_den_out = strtoul(s[31], NULL, 0);
            uint32_t colour_out         = strtoul(s[32], NULL, 0);

            uint32_t crop_top           = strtoul(s[33], NULL, 0);
            uint32_t crop_left          = strtoul(s[34], NULL, 0);
            uint32_t crop_height        = strtoul(s[35], NULL, 0);
            uint32_t crop_width         = strtoul(s[36], NULL, 0);

            uint32_t pip_h_left         = strtoul(s[37], NULL, 0);
            uint32_t pip_h_right        = strtoul(s[38], NULL, 0);
            uint32_t pip_v_top          = strtoul(s[39], NULL, 0);
            uint32_t pip_v_bottom       = strtoul(s[40], NULL, 0);

            uint32_t brdr_yg            = strtoul(s[41], NULL, 0);
            uint32_t brdr_cbb           = strtoul(s[42], NULL, 0);
            uint32_t brdr_crr           = strtoul(s[43], NULL, 0);

            uint32_t aspect_mode        = strtoul(s[44], NULL, 0)%HW_API::NUM_ASPECT_MODES;

            uint32_t lock_mode          = strtoul(s[45], NULL, 0);

            RasterTypes::CVTParameters in_params;
            HW_API::ScalerFrameRate in_rate;
            RasterTypes::CVTParameters out_params;
            HW_API::ScalerFrameRate out_rate;
            HW_API::ScalerPipSettings pip_settings;
            HW_API::ScalerSettings settings;

            in_params.appl            = appl_in;
            in_params.tppl            = tppl_in;
            in_params.hs_width        = hs_width_in;
            in_params.hs_front_porch  = hs_front_porch_in;
            in_params.hs_back_porch   = hs_back_porch_in;
            in_params.alpf[0]         = alpf_0_in;
            in_params.alpf[1]         = alpf_1_in;
            in_params.tlpf[0]         = tlpf_0_in;
            in_params.tlpf[1]         = tlpf_1_in;
            in_params.vs_width        = vs_width_in;
            in_params.vs_front_porch  = vs_front_porch_in;
            in_params.vs_back_porch   = vs_back_porch_in;
            in_rate.frame_rate_num    = frame_rate_num_inp;
            in_rate.frame_rate_den    = frame_rate_den_inp;

            out_params.appl           = appl_out;
            out_params.tppl           = tppl_out;
            out_params.hs_width       = hs_width_out;
            out_params.hs_front_porch = hs_front_porch_out;
            out_params.hs_back_porch  = hs_back_porch_out;
            out_params.alpf[0]        = alpf_0_out;
            out_params.alpf[1]        = alpf_1_out;
            out_params.tlpf[0]        = tlpf_0_out;
            out_params.tlpf[1]        = tlpf_1_out;
            out_params.vs_width       = vs_width_out;
            out_params.vs_front_porch = vs_front_porch_out;
            out_params.vs_back_porch  = vs_back_porch_out;
            out_rate.frame_rate_num   = frame_rate_num_out;
            out_rate.frame_rate_den   = frame_rate_den_out;

            settings.crop_top         = (double)crop_top;
            settings.crop_left        = (double)crop_left;
            settings.crop_height      = (double)crop_height;
            settings.crop_width       = (double)crop_width;
            settings.aspect_mode      = (HW_API::ScalerAspectMode)aspect_mode;
            settings.brdr_yg          = brdr_yg;
            settings.brdr_cbb         = brdr_cbb;
            settings.brdr_crr         = brdr_crr;

            pip_settings.pip_h_left   = pip_h_left    ;
            pip_settings.pip_h_right  = pip_h_right   ;
            pip_settings.pip_v_top    = pip_v_top     ;
            pip_settings.pip_v_bottom = pip_v_bottom  ;

            printf("Setting Scaler with:\n");

            printf(" appl_in             = %u\n", in_params.appl            );
            printf(" tppl_in             = %u\n", in_params.tppl            );
            printf(" hs_width_in         = %u\n", in_params.hs_width        );
            printf(" hs_front_porch_in   = %u\n", in_params.hs_front_porch  );
            printf(" hs_back_porch_in    = %u\n", in_params.hs_back_porch   );
            printf(" alpf_0_in           = %u\n", in_params.alpf[0]         );
            printf(" alpf_1_in           = %u\n", in_params.alpf[1]         );
            printf(" tlpf_0_in           = %u\n", in_params.tlpf[0]         );
            printf(" tlpf_1_in           = %u\n", in_params.tlpf[1]         );
            printf(" vs_width_in         = %u\n", in_params.vs_width        );
            printf(" vs_front_porch_in   = %u\n", in_params.vs_front_porch  );
            printf(" vs_back_porch_in    = %u\n", in_params.vs_back_porch   );
            printf(" inp frame_rate_num  = %u\n", in_rate.frame_rate_num    );
            printf(" inp frame_rate_den  = %u\n", in_rate.frame_rate_den    );
            printf(" input colour        = %u\n", colour_inp                );

            printf(" appl_out            = %u\n", out_params.appl           );
            printf(" tppl_out            = %u\n", out_params.tppl           );
            printf(" hs_width_out        = %u\n", out_params.hs_width       );
            printf(" hs_front_porch_out  = %u\n", out_params.hs_front_porch );
            printf(" hs_back_porch_out   = %u\n", out_params.hs_back_porch  );
            printf(" alpf_0_out          = %u\n", out_params.alpf[0]        );
            printf(" alpf_1_out          = %u\n", out_params.alpf[1]        );
            printf(" tlpf_0_out          = %u\n", out_params.tlpf[0]        );
            printf(" tlpf_1_out          = %u\n", out_params.tlpf[1]        );
            printf(" vs_width_out        = %u\n", out_params.vs_width       );
            printf(" vs_front_porch_out  = %u\n", out_params.vs_front_porch );
            printf(" vs_back_porch_out   = %u\n", out_params.vs_back_porch  );
            printf(" out frame_rate_num  = %u\n", out_rate.frame_rate_num   );
            printf(" out frame_rate_den  = %u\n", out_rate.frame_rate_den   );
            printf(" output colour       = %u\n", colour_out                );

            printf(" crop_top            = %f\n", settings.crop_top         );
            printf(" crop_left           = %f\n", settings.crop_left        );
            printf(" crop_height         = %f\n", settings.crop_height      );
            printf(" crop_width          = %f\n", settings.crop_width       );
            printf(" aspect_mode         = %u\n", settings.aspect_mode      );
            printf(" brdr_yg             = %u\n", settings.brdr_yg          );
            printf(" brdr_cbb            = %u\n", settings.brdr_cbb         );
            printf(" brdr_crr            = %u\n", settings.brdr_crr         );

            printf(" pip_h_left          = %u\n", pip_settings.pip_h_left    );
            printf(" pip_h_right         = %u\n", pip_settings.pip_h_right   );
            printf(" pip_v_top           = %u\n", pip_settings.pip_v_top     );
            printf(" pip_v_bottom        = %u\n", pip_settings.pip_v_bottom  );

            HW_API::initFPGABuildID();
            HW_API::initVidProc();
            HW_API::initScalerPath(path);
            HW_API::switchScalerInput(path, in_params, in_rate, (HW_API::scColourFormat_type)colour_inp);
            HW_API::switchScalerPathSettings(path, &settings);
            int result = HW_API::setScalerPipPath(path, pip_settings, out_params, out_rate, (HW_API::scColourFormat_type)colour_out, lock_mode);
            if (result == 0) {
              printf("Success\n");
            } else {
              printf("Failed\n");
            }

            HW_API::useScalerPath(path, true);
            HW_API::dumpScalerConfig(path);
            HW_API::dumpScalerStatus(path);
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid. Args = %u\n", n);
    }
    return 0;
}

static int
execHdmi(int n, char *s[])
{
    bool pvalid = false;
    if (n == 1) {
        printf("Usage: %s loopback <rxchan> <txchan>\n", s[0]);
        printf("       %s settx <txchan> <bw> <colour_format_id> <fractional> [bits_per_component]\n", s[0]);
        printf("       %s isconnected <rx/tx> <chan>\n", s[0]);
        printf("       %s isstreamup <rx/tx> <chan>\n", s[0]);
        printf("       %s edid <txchan>\n", s[0]);
        printf("       %s edid default <rxchan>\n", s[0]);
        printf("       %s edid clone <rxchan> <txchan>\n", s[0]);
        printf("       %s audchans <txchan> <audchans>\n", s[0]);
        printf("       %s mute <txchan>\n", s[0]);
        printf("       %s txaudrst <txchan> <reset>\n", s[0]);
        printf("       %s txaudcbits <txchan> <restamp> <professional>\n", s[0]);
        printf("       %s unmute <txchan>\n", s[0]);
        printf("       %s read <chan> <addr>\n", s[0]);
        printf("       %s write <chan> <addr> <data>\n", s[0]);
        printf("       %s dumpconfig <chan>\n", s[0]);
        printf("       %s dumpmemory <chan>\n", s[0]);
        printf("       %s dumpstatus <chan>\n", s[0]);
        printf("       %s dumprx <chan>\n", s[0]);
        printf("       %s dumprxstatus <chan>\n", s[0]);
        printf("       %s dumptx <chan>\n", s[0]);
        printf("       %s dumptxstatus <chan>\n", s[0]);
        printf("       %s dumprxtx <chan>\n", s[0]);
        printf("       %s checkconfig <chan>\n", s[0]);
        printf("       %s writeconfig <chan>\n", s[0]);
        printf("       %s sizeconfig <chan>\n", s[0]);
        printf("       %s txinfo <chan>\n", s[0]);
        printf("       %s txratio <chan>\n", s[0]);
        printf("       %s txoff <chan> [off]\n", s[0]);
        printf("       %s txtmdsoff <chan>\n", s[0]);
        printf("       %s txclocks <chan>\n", s[0]);
        printf("       %s txlock <chan> [enable]\n", s[0]);
        printf("       %s clocks <chan>\n", s[0]);
        printf("       %s rxack <chan>\n", s[0]);
        printf("       %s rxlink <chan> [cycles]\n", s[0]);
        printf("       %s rxhpd <chan> [0/1]\n", s[0]);
        printf("       %s rxdisabledroperr <chan> <0/1>\n", s[0]);
        printf("       %s rxdisablehcounterr <chan> <0/1>\n", s[0]);
        printf("       %s resetrxcounters <chan>\n", s[0]);
        printf("       %s rxcounters <chan>\n", s[0]);
        printf("       %s rxclocknovideo <chan>\n", s[0]);
        printf("       %s rxclocknovideothreshold <chan> [threshold]\n", s[0]);
        printf("       %s ticorequired <rxchan> <colourformat>\n", s[0]);
        printf("       %s tmds181badstate <rxchan>\n", s[0]);
        printf("       %s rxauxpkt <chan>\n", s[0]);
        printf("       %s heartbeat <chan>\n", s[0]);
        printf("       %s running <chan>\n", s[0]);
        printf("       %s hdcp -> Sub-Menu\n", s[0]);
        printf("       %s rxinfoframe -> Sub-Menu\n", s[0]);
        printf("       %s txinfoframe -> Sub-Menu\n", s[0]);
        printf("       %s rxmetadata -> Sub-Menu\n", s[0]);
        printf("       %s txmetadata -> Sub-Menu\n", s[0]);
        printf("       %s rxaudio -> Sub-Menu\n", s[0]);
        printf("       %s txaudio -> Sub-Menu\n", s[0]);
        printf("\n");
        printf("   where:\n");
        printf("   rxchan/txchan/chan = channel idx (0-1)\n");
        printf("   bw :\n");
        printf("              0 = 1920 x 1080 p 60\n");
        printf("              1 = 1920 x 1080 i 60\n");
        printf("              2 = 3840 x 2160 p 30\n");
        printf("              3 = 3840 x 2160 p 60\n");
        printf("   colour_format_id :\n");
        printf("              0 = RGB  (444)\n");
        printf("              1 = YCrCb 444\n");
        printf("              2 = YCrCb 422\n");
        printf("   bits_per_component = 8,10,12,16\n");
        pvalid = true;
    } else if (n == 2) {
        if (!strcmp(s[1], "hdcp")) {
            printf("Usage:\n");
            printf("       %s %s info <rx/tx> <chan>\n", s[0], s[1]);
            printf("       %s %s protocol <rx/tx> <chan>\n", s[0], s[1]);
            printf("       %s %s protocol rx <chan> <protocol>\n", s[0], s[1]);
            printf("       %s %s encrypt <txchan> <0/1>\n", s[0], s[1]);
            printf("       %s %s auth <txchan> <0/1>\n", s[0], s[1]);
            printf("       %s %s waitingperiod <txchan> [cycles]\n", s[0], s[1]);
            printf("       %s %s waitcount <txchan>\n", s[0], s[1]);
            printf("       %s %s blank <txchan>\n", s[0], s[1]);
            printf("       %s %s mask <txchan> [colour]\n", s[0], s[1]);
            printf("       %s %s debug <rx/tx> <chan>\n", s[0], s[1]);
            printf("       %s %s keyspresent <chan>\n", s[0], s[1]);
            printf("       %s %s keysloaded <chan>\n", s[0], s[1]);
            printf("   where rxchan/txchan/chan = channel idx (0-1)\n");
            printf("         protocol = 0 = NONE, 1 = HDCP14, 2 = HDCP22\n");
            printf("         colour = 0 = Black, 1 = White, 2 = Red, 3 = Green, 4 = Blue, 5 = Noise\n");
            pvalid = true;
        } else if (!strcmp(s[1], "rxinfoframe")) {
            printf("Usage:\n");
            printf("       %s %s audio  <chan>\n", s[0], s[1]);
            printf("       %s %s avi    <chan>\n", s[0], s[1]);
            printf("       %s %s vsif   <chan>\n", s[0], s[1]);
            printf("       %s %s gcp    <chan>\n", s[0], s[1]);
            printf("       %s %s drm    <chan>\n", s[0], s[1]);
            printf("       %s %s hdr10p <chan>\n", s[0], s[1]);
            printf("       %s %s dolby  <chan>\n", s[0], s[1]);
            printf("       %s %s spd    <chan>\n", s[0], s[1]);
            printf("       %s %s am     <chan>\n", s[0], s[1]);
            printf("   where chan = channel idx (0-1)\n");
            printf("\n");
            pvalid = true;
        } else if (!strcmp(s[1], "txinfoframe")) {
            printf("Usage:\n");
            printf("       %s %s init   <chan>\n", s[0], s[1]);
            printf("       %s %s audio  <chan>\n", s[0], s[1]);
            printf("       %s %s avi    <chan>\n", s[0], s[1]);
            printf("       %s %s vsif   <chan>\n", s[0], s[1]);
            printf("       %s %s drm    <chan>\n", s[0], s[1]);
            printf("       %s %s hdr10p <chan>\n", s[0], s[1]);
            printf("       %s %s dolby  <chan>\n", s[0], s[1]);
            printf("       %s %s spd    <chan>\n", s[0], s[1]);
            printf("       %s %s am     <chan>\n", s[0], s[1]);
            printf("       %s %s vsifenable <chan> [0/1]\n", s[0], s[1]);
            printf("       %s %s drmenable <chan> [0/1]\n", s[0], s[1]);
            printf("       %s %s hdr10penable <chan> [0/1]\n", s[0], s[1]);
            printf("       %s %s dolbyenable <chan> [0/1]\n", s[0], s[1]);
            printf("       %s %s spdenable <chan> [0/1]\n", s[0], s[1]);
            printf("       %s %s audiometadataenable <chan> [0/1]\n", s[0], s[1]);
            printf("       %s %s audio <chan> <CC> <SF> <CA> <DM_INH>\n", s[0], s[1]);
            printf("                                     <LSV> <LFEPBL>\n");
            printf("       %s %s avi   <chan> <Y> <A> <B> <S> <C> <M>\n", s[0], s[1]);
            printf("                                     <R> <ITC> <EC> <Q> <SC>\n");
            printf("                                     <VIC> <YQ> <CN> <PR>\n");
            printf("                                     <ETB> <SBB> <ELB> <SRB>\n");
            printf("       %s %s vsif  <chan> <HDMI_Video_Format> <HDMI_VIC>\n", s[0], s[1]);
            printf("       %s %s drm   <chan> <EOTF> <SMD_ID>\n", s[0], s[1]);
            printf("                            <DP_X0> <DP_X1> <DP_X2>\n");
            printf("                            <DP_Y0> <DP_Y1> <DP_Y2>\n");
            printf("                            <WP_X> <WP_Y> <Min_DML> <Max_DML>\n");
            printf("                            <Max_CLL> <Max_FALL>\n");
            printf("       %s %s spd   <chan> <Vendor> <Product> <SI>\n", s[0], s[1]);
            printf("   where chan = channel idx (0-1)\n");
            printf("\n");
            printf("   For Audio:\n");
            printf("       CT     = Audio Coding Type                  (0x0-0xF)\n");
            printf("       CC     = Audio Channel Count                (0x0-0x7)\n");
            printf("       SF     = Sample Frequency                   (0x0-0x7)\n");
            printf("       SS     = Sample Size                        (0x0-0x3)\n");
            printf("       CXT    = Coding Extension Type              (0x0-0xA)\n");
            printf("       CA     = Channel Allocation                 (0x0-0x31)\n");
            printf("       DM_INH = Down-mix Inhibit Flag              (0x0-0x1)\n");
            printf("       LSV    = Level Shift Values                 (0x0-0xF)\n");
            printf("       LFEPBL = LFE Playback Level                 (0x0-0x2)\n");
            printf("   For AVI:\n");
            printf("       Y      = RGB/Y422/Y444/Y420                 (0x0-0x3)\n");
            printf("       A      = Active Formate Information Present (0x0-0x1)\n");
            printf("       B      = Bar Data Present                   (0x0-0x3)\n");
            printf("       S      = Scan Information                   (0x0-0x2)\n");
            printf("       C      = Colourimetry                       (0x0-0x3)\n");
            printf("       M      = Picture Aspect Ratio               (0x0-0x2)\n");
            printf("       R      = Active Portion Aspect Ratio        (0x8-0xB)\n");
            printf("       ITC    = IT Content                         (0x0-0x1)\n");
            printf("       EC     = Extended Colourimetry              (0x0-0x6)\n");
            printf("       Q      = RGB Quantization Range             (0x0-0x2)\n");
            printf("       SC     = Non-Uniform Picture Scaling        (0x0-0x3)\n");
            printf("       VIC    = Video Identification Code          (0x0-0x6B)\n");
            printf("       YQ     = YCC Quantization Range             (0x0-0x1)\n");
            printf("       CN     = Content Type                       (0x0-0x3)\n");
            printf("       PR     = Pixel Replication                  (0x0-0x9)\n");
            printf("       ETB    = Line Number of End of Top Bar      (0-2250)\n");
            printf("       SBB    = Line Number of Start of Bottom Bar (0-2250)\n");
            printf("       ELB    = Pixel Number of End of Left Bar    (0-5500)\n");
            printf("       SRB    = Pixel Number of Start of Right Bar (0-5500)\n");
            printf("   For VSIF: (no 3D support)\n");
            printf("       HDMI_Video_Format = None/HDMI_VIC           (0x0-0x1)\n");
            printf("       HDMI_VIC          = Extended Resolution VIC (0x1-0x4)\n");
            printf("   For DRM:\n");
            printf("       EOTF    = Electro-Optical Transfer Function (0x0-0x3)\n");
            printf("       SMD_ID  = Static Metadata Descriptor ID     (0x0)\n");
            printf("       DP_Xx   = Display Primaries X (x)           (0x0-0xFFFF)\n");
            printf("       DP_Yx   = Display Primaries Y (x)           (0x0-0xFFFF)\n");
            printf("       WP_X    = White Point X                     (0x0-0xFFFF)\n");
            printf("       WP_Y    = White Point Y                     (0x0-0xFFFF)\n");
            printf("       Min_DML = Min Display Mastering Luminance   (0x0-0xFFFF)\n");
            printf("       Max_DML = Max Display Mastering Luminance   (0x0-0xFFFF)\n");
            printf("       Max_CLL = Max Content Light Level           (0x0-0xFFFF)\n");
            printf("       Max_FALL= Max Frame Average Light Level     (0x0-0xFFFF)\n");
            printf("   For SPD:\n");
            printf("       Vendor      = Vendor Name                   [8 chars]\n");
            printf("       Product     = Product Description           [16 chars]\n");
            printf("       Source Info = Source Information            (0x0-0xE)\n");
            printf("\n");
            printf("   Refer to CEA-861-F Section 6.4 and 6.6 for definitions of these values.\n");
            printf("   Refer to HDMI Specification 1.4b for definitions of the VSIF.\n");
            printf("   Refer to CEA-861.3 Section 3.2 for definitions of the DRM.\n");
            printf("\n");
            pvalid = true;
        } else if (!strcmp(s[1], "rxmetadata")) {
            printf("Usage:\n");
            printf("       %s %s count   <chan>\n", s[0], s[1]);
            pvalid = true;
        } else if (!strcmp(s[1], "txmetadata")) {
            printf("Usage:\n");
            printf("       %s %s count   <chan>\n", s[0], s[1]);
            printf("       %s %s drm     <chan>\n", s[0], s[1]);
            printf("       %s %s hdr10p  <chan>\n", s[0], s[1]);
            printf("       %s %s dolby   <chan>\n", s[0], s[1]);
            printf("       %s %s generic <chan>\n", s[0], s[1]);
            printf("       %s %s sent    <chan>\n", s[0], s[1]);
            pvalid = true;
        } else if (!strcmp(s[1], "rxaudio")) {
            printf("Usage:\n");
            printf("       %s %s channels <rxchan>\n", s[0], s[1]);
            printf("       %s %s sf <rxchan>\n", s[0], s[1]);
            printf("       %s %s compressed <rxchan>\n", s[0], s[1]);
            printf("       %s %s datatype <rxchan>\n", s[0], s[1]);
            printf("   where rxchan = channel idx (0-1)\n");
            pvalid = true;
        } else if (!strcmp(s[1], "txaudio")) {
            printf("Usage:\n");
            printf("       %s %s sf <txchan>\n", s[0], s[1]);
            printf("       %s %s compressed <txchan>\n", s[0], s[1]);
            printf("       %s %s src <txchan>\n", s[0], s[1]);
            printf("       %s %s drop <txchan>\n", s[0], s[1]);
            printf("       %s %s forcesrc <txchan> <0/1>\n", s[0], s[1]);
            printf("   where txchan = channel idx (0-1)\n");
            pvalid = true;
        }
    } else if (n == 3) {
        if (!strcmp(s[1], "edid")) {
            uint32_t txchan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(txchan);
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            uint8_t edid[256];
            uint32_t size;
            uint8_t valid;
            HW_API::getHdmiTxEDID(txchan, edid, &size, &valid);
            printf("Channel %u EDID Valid: %s.\n", txchan, (valid ? "true" : "false"));
            printf("Channel %u EDID Size:  %u.\n", txchan, size);
            for (uint32_t i = 0; i < 256; i++) {
              printf("%02x", edid[i]);
              if (i % 16 == 15) printf("\n");
              else if (i % 16 == 7) printf("  ");
              else printf(" ");
            }
            if (size % 16 != 15) printf("\n");
            pvalid = true;
        } else if (!strcmp(s[1], "mute")) {
            uint32_t txchan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(txchan);
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            HW_API::setHdmiTxAudioMute(txchan, true);
            pvalid = true;
        } else if (!strcmp(s[1], "unmute")) {
            uint32_t txchan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(txchan);
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            HW_API::setHdmiTxAudioMute(txchan, false);
            pvalid = true;
        } else if (!strcmp(s[1], "dumpconfig")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiConfig(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "dumpmemory")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiConfigMemory(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "dumpstatus")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiConfigStatus(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "dumprx")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiConfigRx(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "dumprxstatus")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiConfigRxStatus(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "dumptx")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiConfigTx(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "dumptxstatus")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiConfigTxStatus(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "dumprxtx")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiConfigRx(chan);
            HW_API::debugHdmiConfigTx(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "rxauxpkt")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint8_t AuxBuffer[36];
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            /* Check that Rx is Connected and StreamIsUp */
            if (!HW_API::getHdmiRxIsConnected(chan)) {
              printf("Channel %u Rx cable not connected!\n", chan);
              return 0;
            }
            if (!HW_API::getHdmiRxStreamIsUp(chan)) {
              printf("Channel %u Rx stream is not up!\n", chan);
              return 0;
            }
            for (int j = 0; j < NUM_AUX_BUFFER; j++){
              if (HW_API::getHdmiRxAuxPacket(chan, AuxBuffer, (uint32_t*)36) == 0){ //SUCCESS
                printf("Rx Aux Packet[%d]: \n", j);
                for (int i = 0; i < 36; i++){
                  printf("%x ", AuxBuffer[i]);
                }
                printf("Done\n");
                printf("\n");
              } else {
                printf("No Data.\n");
              }
            }
            pvalid = true;
        } else if (!strcmp(s[1], "checkconfig")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiCheckConfig(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "writeconfig")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiWriteConfig(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "sizeconfig")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiSizeConfig(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "clocks")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiClkDetFreq(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "txclocks")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            for (int i=0;i<1000;i++)
            {
              usleep(10);
              HW_API::debugHdmiTxClkDetFreq(chan);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxack")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::setHdmiRxOutputEnable(chan);
            pvalid = true;
        } else if (!strcmp(s[1], "running")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            bool running;
            HW_API::getHdmiStateRunning(chan, &running);
            printf("Channel %u MicroBlaze Running: %s\n", chan, (running ? "true" : "false"));
            pvalid = true;
        } else if (!strcmp(s[1], "heartbeat")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            uint32_t heartbeat;
            HW_API::getHdmiMainLoopHeartbeat(chan, &heartbeat);
            printf("Channel %u Main Loop Heartbeat: %d\n", chan, heartbeat);
            pvalid = true;
        } else if (!strcmp(s[1], "rxlink")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            uint32_t link0;
            uint32_t link1;
            uint32_t link2;
            HW_API::getHdmiRxLinkStatusError(chan, &link0, &link1, &link2);
            printf("Channel %u Rx Link Error:\n", chan);
            printf("  Rx Link 0 Error: %d\n", link0);
            printf("  Rx Link 1 Error: %d\n", link1);
            printf("  Rx Link 2 Error: %d\n", link2);
            pvalid = true;
        } else if (!strcmp(s[1], "resetrxcounters")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::resetHdmiRxCounters(chan);
            printf("Channel %u Rx counters reset\n", chan);
            pvalid = true;
        } else if (!strcmp(s[1], "rxcounters")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            uint32_t frameCount;
            uint32_t dropErrCount;
            uint16_t dropErrLine;
            uint16_t dropErrHcount;
            uint32_t hcountErrCount;
            uint16_t hcountErrLine;
            uint16_t hcountErrHCount;
            uint32_t vcountErrCount;
            uint16_t vcountErrVCount;
            HW_API::getHdmiRxFrameCount(chan, &frameCount);
            HW_API::getHdmiRxDropErrCount(chan, &dropErrCount, &dropErrLine, &dropErrHcount);
            HW_API::getHdmiRxHCountErrCount(chan, &hcountErrCount, &hcountErrLine, &hcountErrHCount);
            HW_API::getHdmiRxVCountErrCount(chan, &vcountErrCount, &vcountErrVCount);
            printf("Channel %u Rx Counters:\n", chan);
            printf("  Frame counter: %u\n", frameCount);
            printf("  Drop error counter (line, hcount): %u (%u, %u)\n", dropErrCount, dropErrLine, dropErrHcount);
            printf("  HCount error counter (line, hcount): %u (%u, %u)\n", hcountErrCount, hcountErrLine, hcountErrHCount);
            printf("  VCount error counter (line): %u (%u)\n", vcountErrCount, vcountErrVCount);
            pvalid = true;
        } else if (!strcmp(s[1], "rxhpd")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            bool enabled;
            HW_API::getHdmiRxHotplugDetect(chan, &enabled);
            printf("Channel %u Rx Hotplug Detect: %u.\n", chan, enabled);
            pvalid = true;
        } else if (!strcmp(s[1], "tmds181badstate")) {
            uint32_t rxchan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(rxchan);
            /* Check that Rx is Connected */
            if (!HW_API::getHdmiRxIsConnected(rxchan)) {
              printf("Channel %u Rx cable not connected!\n", rxchan);
              return 0;
            }
            bool badState;
            HW_API::getHdmiRxTMDS181BadState(rxchan,&badState);
            printf("Channel %u TMDS181 is in a Bad State: %s.\n", rxchan, (badState ? "True" : "False"));
            pvalid = true;
        } else if (!strcmp(s[1], "rxclocknovideo")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            uint32_t count;
            HW_API::getHdmiRxClockNoVideo(chan, &count);
            printf("Channel %u Rx Clock No Video: %u.\n", chan, count);
            pvalid = true;
        } else if (!strcmp(s[1], "rxclocknovideothreshold")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            uint32_t count;
            HW_API::getHdmiRxClockNoVideoThreshold(chan, &count);
            printf("Channel %u Rx Clock No Video Threshold: %u.\n", chan, count);
            pvalid = true;
        } else if (!strcmp(s[1], "txlock")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            bool lock;
            HW_API::getHdmiTxSi570LockEnable(chan, &lock);
            printf("Channel %u Tx Lock Enable: %u.\n", chan, lock);
            pvalid = true;
        } else if (!strcmp(s[1], "txinfo")) {
            uint32_t txchan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(txchan);
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            bool hdmi20;
            bool hdcp22;
            bool tmdsratio;
            bool sinkratio;
            uint8_t count;
            HW_API::getHdmiTxHdmi20Capable(txchan, &hdmi20);
            HW_API::getHdmiTxHdcp22Capable(txchan, &hdcp22);
            HW_API::getHdmiTxTmdsClockRatio(txchan, &tmdsratio);
            HW_API::getHdmiTxSinkClockRatio(txchan, &sinkratio);
            HW_API::getHdmiTxTmdsClockRatioReprogrammed(txchan, &count);
            printf("Channel %u Tx Info:\n", txchan);
            printf("  HDMI 2.0 Capable:   %u\n", hdmi20);
            printf("  HDCP 2.2 Capable:   %u\n", hdcp22);
            printf("  TMDS Clock Ratio:   %u\n", tmdsratio);
            printf("  Sink Clock Ratio:   %u\n", sinkratio);
            printf("  Ratio Reprogrammed: %u\n", count);
            pvalid = true;
        } else if (!strcmp(s[1], "txratio")) {
            uint32_t txchan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(txchan);
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            HW_API::setHdmiTxSetTmdsClockRatio(txchan);
            printf("Channel %u Tx TMDS Clock Ratio Reprogrammed.\n", txchan);
            pvalid = true;
        } else if (!strcmp(s[1], "txoff")) {
            uint32_t txchan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(txchan);
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            bool off;
            HW_API::getHdmiTxOff(txchan, &off);
            printf("Channel %u TxOff: %u.\n", txchan, off);
            pvalid = true;
        } else if (!strcmp(s[1], "txtmdsoff")) {
            uint32_t txchan = strtoul(s[2], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(txchan);
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            bool off;
            HW_API::getHdmiTxTmdsClockOff(txchan, &off);
            printf("Channel %u TxTMDSOff: %u\n", txchan, off);
            pvalid = true;
        }
    } else if (n == 4) {
        if (!strcmp(s[1], "loopback")) {
            uint32_t rxchan = strtoul(s[2], NULL, 0);
            uint32_t txchan;
            bool loopback = (strtol(s[3], NULL, 0) == -1);
            if (loopback) {
              txchan = rxchan;
            } else {
              txchan = strtoul(s[3], NULL, 0);
            }
            HW_API::initFPGABuildID();
            HW_API::initHdmi(rxchan);
            HW_API::initHdmi(txchan);
            /* Check that Rx is Connected and StreamIsUp */
            if (!HW_API::getHdmiRxIsConnected(rxchan)) {
              printf("Channel %u Rx cable not connected!\n", rxchan);
              return 0;
            }
            if (!HW_API::getHdmiRxStreamIsUp(rxchan)) {
              printf("Channel %u Rx stream is not up!\n", rxchan);
              return 0;
            }
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            HDMI_Xil_Type::VideoStream_type videostream;
            HDMI_Xil_Type::VideoConfig_type videoconfig;
            if (HW_API::getHdmiRxVideoConfig(rxchan, &videostream, &videoconfig) != HDMI_Xil_Type::RET_SUCCESS) {
              printf("getHdmiRxVideoConfig failed!\n");
              return 0;
            }
            if (HW_API::getHdmiTxVideoConfigValid(txchan, &videostream, videoconfig.VideoIDCode) != HDMI_Xil_Type::RET_SUCCESS) {
              printf("WARNING: getHdmiTxVideoConfigValid failed!\n");
            }
            if (loopback) {
              // Copy the Video Stream and Config verbatim as we assume no buffering with clock forwarding.
              HW_API::setHdmiLoopbackMode(rxchan, 1);
              if (HW_API::setHdmiTxVideoLoopback(rxchan) != HDMI_Xil_Type::RET_SUCCESS) {
                printf("setHdmiTxVideoLoopback failed!\n");
                return 0;
              }
            } else {
              // Copy the Video Stream and generate the Config.
              HW_API::setHdmiLoopbackMode(rxchan, 0);
              if (HW_API::setHdmiTxVideoConfig(txchan, &videostream, videoconfig.VideoIDCode) != HDMI_Xil_Type::RET_SUCCESS) {
                printf("setHdmiTxVideoConfig failed!\n");
                return 0;
              }
            }
            HW_API::setHdmiRxOutputEnable(rxchan);
            printf("Channel %u Tx loopback from channel %u Rx!\n", txchan, rxchan);
            pvalid = true;
        } else if (!strcmp(s[1], "txaudrst")) {
            uint32_t txchan = strtoul(s[2], NULL, 0);
            bool reset = strtoul(s[3], NULL, 0) ? true : false;
            HW_API::initFPGABuildID();
            HW_API::initHdmi(txchan);
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            HW_API::setHdmiTxAudioReset(txchan, reset);
            pvalid = true;
        } else if (!strcmp(s[1], "isconnected")) {
            uint32_t chan = strtoul(s[3], NULL, 0);
            if (!strcmp(s[2], "rx")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                if (HW_API::getHdmiRxIsConnected(chan)) {
                  printf("Channel %u Rx cable connected.\n", chan);
                } else {
                  printf("Channel %u Rx cable not connected!\n", chan);
                }
                pvalid = true;
            } else if (!strcmp(s[2], "tx")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                if (HW_API::getHdmiTxIsConnected(chan)) {
                  printf("Channel %u Tx cable connected.\n", chan);
                } else {
                  printf("Channel %u Tx cable not connected!\n", chan);
                }
                pvalid = true;
            }
        } else if (!strcmp(s[1], "isstreamup")) {
            uint32_t chan = strtoul(s[3], NULL, 0);
            if (!strcmp(s[2], "rx")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                if (HW_API::getHdmiRxStreamIsUp(chan)) {
                  printf("Channel %u Rx stream is up.\n", chan);
                } else {
                  printf("Channel %u Rx stream is not up!\n", chan);
                }
                pvalid = true;
            } else if (!strcmp(s[2], "tx")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                if (HW_API::getHdmiTxStreamIsUp(chan)) {
                  printf("Channel %u Tx stream is up.\n", chan);
                } else {
                  printf("Channel %u Tx stream is not up!\n", chan);
                }
                pvalid = true;
            }
        } else if (!strcmp(s[1], "rxaudio")) {
            uint32_t chan = strtoul(s[3], NULL, 0);
            if (!strcmp(s[2], "channels")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                /* Check that Rx is Connected and StreamIsUp */
                if (!HW_API::getHdmiRxIsConnected(chan)) {
                  printf("Channel %u Rx cable not connected!\n", chan);
                  return 0;
                }
                if (!HW_API::getHdmiRxStreamIsUp(chan)) {
                  printf("Channel %u Rx stream is not up!\n", chan);
                  return 0;
                }
                uint8_t channels;
                HW_API::getHdmiRxAudioChannels(chan, &channels);
                printf("Channel %u Audio Channels: %u\n", chan, channels);
                pvalid = true;
            } else if (!strcmp(s[2], "sf")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                /* Check that Rx is Connected and StreamIsUp */
                if (!HW_API::getHdmiRxIsConnected(chan)) {
                  printf("Channel %u Rx cable not connected!\n", chan);
                  return 0;
                }
                if (!HW_API::getHdmiRxStreamIsUp(chan)) {
                  printf("Channel %u Rx stream is not up!\n", chan);
                  return 0;
                }
                uint32_t sf;
                HW_API::getHdmiRxAudioSamplingFrequency(chan, &sf);
                printf("Channel %u Audio Sampling Frequency: %u\n", chan, sf);
                pvalid = true;
            } else if (!strcmp(s[2], "compressed")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                /* Check that Rx is Connected and StreamIsUp */
                if (!HW_API::getHdmiRxIsConnected(chan)) {
                  printf("Channel %u Rx cable not connected!\n", chan);
                  return 0;
                }
                if (!HW_API::getHdmiRxStreamIsUp(chan)) {
                  printf("Channel %u Rx stream is not up!\n", chan);
                  return 0;
                }
                uint8_t compressed;
                HW_API::getHdmiRxAudioCompressed(chan, &compressed);
                printf("Channel %u Audio Compressed: %u\n", chan, compressed);
                pvalid = true;
            } else if (!strcmp(s[2], "datatype")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                /* Check that Rx is Connected and StreamIsUp */
                if (!HW_API::getHdmiRxIsConnected(chan)) {
                  printf("Channel %u Rx cable not connected!\n", chan);
                  return 0;
                }
                if (!HW_API::getHdmiRxStreamIsUp(chan)) {
                  printf("Channel %u Rx stream is not up!\n", chan);
                  return 0;
                }
                char data_type[256];
                HW_API::getHdmiRxAudioDataType(chan, data_type);
                printf("Channel %u Audio Data Type: %s\n", chan, data_type);
                pvalid = true;
            } else if (!strcmp(s[2], "hbr")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                if (!HW_API::getHdmiRxIsConnected(chan)) {
                  printf("Rx not connected!\n");
                  return 0;
                }
                uint8_t hbr;
                HW_API::getHdmiRxAudioHBR(chan, &hbr);
                printf("Channel %u Audio HBR: %u\n", chan, hbr);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "txaudio")) {
            uint32_t chan = strtoul(s[3], NULL, 0);
            if (!strcmp(s[2], "sf")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                /* Check that Tx is Connected and StreamIsUp */
                if (!HW_API::getHdmiTxIsConnected(chan)) {
                  printf("Channel %u Tx cable not connected!\n", chan);
                  return 0;
                }
                if (!HW_API::getHdmiTxStreamIsUp(chan)) {
                  printf("Channel %u Tx stream is not up!\n", chan);
                  return 0;
                }
                uint32_t sf;
                HW_API::getHdmiTxAudioSamplingFrequency(chan, &sf);
                printf("Channel %u Audio Sampling Frequency: %u\n", chan, sf);
                pvalid = true;
            } else if (!strcmp(s[2], "compressed")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                /* Check that Tx is Connected and StreamIsUp */
                if (!HW_API::getHdmiTxIsConnected(chan)) {
                  printf("Channel %u Tx cable not connected!\n", chan);
                  return 0;
                }
                if (!HW_API::getHdmiTxStreamIsUp(chan)) {
                  printf("Channel %u Tx stream is not up!\n", chan);
                  return 0;
                }
                bool compressed;
                HW_API::getHdmiTxAudioCompressed(chan, &compressed);
                printf("Channel %u Audio Compressed: %u\n", chan, compressed);
                pvalid = true;
            } else if (!strcmp(s[2], "src")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                /* Check that Tx is Connected and StreamIsUp */
                if (!HW_API::getHdmiTxIsConnected(chan)) {
                  printf("Channel %u Tx cable not connected!\n", chan);
                  return 0;
                }
                if (!HW_API::getHdmiTxStreamIsUp(chan)) {
                  printf("Channel %u Tx stream is not up!\n", chan);
                  return 0;
                }
                bool src;
                HW_API::getHdmiTxAudioSRC(chan, &src);
                printf("Channel %u using SRC: %u\n", chan, src);
                pvalid = true;
            } else if (!strcmp(s[2], "drop")) {
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                /* Check that Tx is Connected and StreamIsUp */
                if (!HW_API::getHdmiTxIsConnected(chan)) {
                  printf("Channel %u Tx cable not connected!\n", chan);
                  return 0;
                }
                if (!HW_API::getHdmiTxStreamIsUp(chan)) {
                  printf("Channel %u Tx stream is not up!\n", chan);
                  return 0;
                }
                bool drop;
                HW_API::getHdmiTxAudioDrop(chan, &drop);
                printf("Channel %u dropping data: %u\n", chan, drop);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "audchans")) {
            uint32_t txchan = strtoul(s[2], NULL, 0);
            uint32_t audchans = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(txchan);
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            if (HW_API::setHdmiTxAudioChannels(txchan, audchans)) {
              printf("Channel %u Tx audchans out of range!\n", txchan);
              return 0;
            };
            printf("Channel %u Audio Channels:%u\n", txchan, audchans);
            pvalid = true;
        } else if (!strcmp(s[1], "read")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint32_t addr = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            uint8_t ret = HW_API::debugHdmiRead(chan, addr);
            printf("Config[%d][%d] = %x\n", chan, addr, ret);
            pvalid = true;
        } else if (!strcmp(s[1], "hdcp")) {
            if (!strcmp(s[2], "keyspresent")) {
                bool present;
                uint32_t txchan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(txchan);
                HW_API::getHdmiHDCPKeysPresent(txchan, &present);
                if (present) {
                  printf("Channel %u HDCP keys: PRESENT\n", txchan);
                } else {
                  printf("Channel %u HDCP keys: NOT PRESENT\n", txchan);
                }
                pvalid = true;
            } else if (!strcmp(s[2], "keysloaded")) {
                HDMI_Xil_Type::Key_type status;
                uint32_t txchan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(txchan);
                HW_API::getHdmiHDCPKeysLoaded(txchan, &status);
                switch (status) {
                  case HDMI_Xil_Type::KEYS_INIT :
                    printf("Channel %u HDCP keys loaded: NOT LOADED\n", txchan);
                    break;
                  case HDMI_Xil_Type::KEYS_LOADED :
                    printf("Channel %u HDCP keys loaded: SUCCESS\n", txchan);
                    break;
                  case HDMI_Xil_Type::KEYS_FAILED :
                    printf("Channel %u HDCP keys loaded: FAILED\n", txchan);
                    break;
                  default :
                    printf("Channel %u HDCP keys loaded: ERROR\n", txchan);
                    break;
                }
                pvalid = true;
            } else if (!strcmp(s[2], "waitingperiod")) {
                uint32_t txchan = strtoul(s[3], NULL, 0);
                uint32_t waitingPeriod;
                HW_API::initFPGABuildID();
                HW_API::initHdmi(txchan);
                /* Check that Tx is Connected and StreamIsUp */
                if (!HW_API::getHdmiTxIsConnected(txchan)) {
                  printf("Channel %u Tx cable not connected!\n", txchan);
                  return 0;
                }
                if (!HW_API::getHdmiTxStreamIsUp(txchan)) {
                  printf("Channel %u Tx stream is not up!\n", txchan);
                  return 0;
                }
                HW_API::getHdmiTxHDCPWaitingPeriod(txchan, &waitingPeriod);
                printf("Channel %u HDCP Waiting Period: %d\n", txchan, waitingPeriod);
                pvalid = true;
            } else if (!strcmp(s[2], "waitcount")) {
                uint32_t txchan = strtoul(s[3], NULL, 0);
                uint32_t waitCount = 0;
                HW_API::initFPGABuildID();
                HW_API::initHdmi(txchan);
                /* Check that Tx is Connected and StreamIsUp */
                if (!HW_API::getHdmiTxIsConnected(txchan)) {
                  printf("Channel %u Tx cable not connected!\n", txchan);
                  return 0;
                }
                if (!HW_API::getHdmiTxStreamIsUp(txchan)) {
                  printf("Channel %u Tx stream is not up!\n", txchan);
                  return 0;
                }
                HW_API::getHdmiTxHDCPWaitCount(txchan, &waitCount);
                printf("Channel %u HDCP Wait Count: %d\n", txchan, waitCount);
                pvalid = true;
            } else if (!strcmp(s[2], "blank")) {
                uint32_t txchan = strtoul(s[3], NULL, 0);
                bool blank;
                HW_API::initFPGABuildID();
                HW_API::initHdmi(txchan);
                /* Check that Tx is Connected and StreamIsUp */
                if (!HW_API::getHdmiTxIsConnected(txchan)) {
                  printf("Channel %u Tx cable not connected!\n", txchan);
                  return 0;
                }
                if (!HW_API::getHdmiTxStreamIsUp(txchan)) {
                  printf("Channel %u Tx stream is not up!\n", txchan);
                  return 0;
                }
                HW_API::getHdmiTxHDCPBlank(txchan, &blank);
                printf("Channel %u HDCP Blank: %d\n", txchan, blank);
                pvalid = true;
            } else if (!strcmp(s[2], "mask")) {
                uint32_t txchan = strtoul(s[3], NULL, 0);
                HDMI_Xil_Type::HDCPMask_type hdcpMask;
                HW_API::initFPGABuildID();
                HW_API::initHdmi(txchan);
                HW_API::getHdmiTxHDCPMask(txchan, &hdcpMask);
                printf("Channel %u HDCP Mask: %d\n", txchan, hdcpMask);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "rxinfoframe")) {
            uint32_t chan = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            /* Check that Rx is Connected and StreamIsUp */
            if (!HW_API::getHdmiRxIsConnected(chan)) {
              printf("Channel %u Rx cable not connected!\n", chan);
              return 0;
            }
            if (!HW_API::getHdmiRxStreamIsUp(chan)) {
              printf("Channel %u Rx stream is not up!\n", chan);
              return 0;
            }
            if (!strcmp(s[2], "audio")) {
                HDMI_Xil_Type::AudioInfoFrame_type audioInfoFrame;
                HW_API::getHdmiRxInfoFrameAudio(chan, &audioInfoFrame);
                printf("Channel %u Rx Audio InfoFrame:\n", chan);
                printf("Type    = 0x%02x\n", audioInfoFrame.Type);
                printf("Version = 0x%02x\n", audioInfoFrame.Version);
                printf("Length  = 0x%02x\n", audioInfoFrame.Length);
                printf("CT      = %u\n", audioInfoFrame.CT);
                printf("CC      = %u\n", audioInfoFrame.CC);
                printf("SF      = %u\n", audioInfoFrame.SF);
                printf("SS      = %u\n", audioInfoFrame.SS);
                printf("CXT     = %u\n", audioInfoFrame.CXT);
                printf("CA      = %u\n", audioInfoFrame.CA);
                printf("DM_INH  = %u\n", audioInfoFrame.DM_INH);
                printf("LSV     = %u\n", audioInfoFrame.LSV);
                printf("LFEPBL  = %u\n", audioInfoFrame.LFEPBL);
                pvalid = true;
            } else if (!strcmp(s[2], "avi")) {
                HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type aviInfoFrame;
                HW_API::getHdmiRxInfoFrameAVI(chan, &aviInfoFrame);
                printf("Channel %u Rx AVI InfoFrame:\n", chan);
                printf("Type    = 0x%02x\n", aviInfoFrame.Type);
                printf("Version = 0x%02x\n", aviInfoFrame.Version);
                printf("Length  = 0x%02x\n", aviInfoFrame.Length);
                printf("Y       = %u\n", aviInfoFrame.Y);
                printf("A       = %u\n", aviInfoFrame.A);
                printf("B       = %u\n", aviInfoFrame.B);
                printf("S       = %u\n", aviInfoFrame.S);
                printf("C       = %u\n", aviInfoFrame.C);
                printf("M       = %u\n", aviInfoFrame.M);
                printf("R       = %u\n", aviInfoFrame.R);
                printf("ITC     = %u\n", aviInfoFrame.ITC);
                printf("EC      = %u\n", aviInfoFrame.EC);
                printf("Q       = %u\n", aviInfoFrame.Q);
                printf("SC      = %u\n", aviInfoFrame.SC);
                printf("VIC     = %u\n", aviInfoFrame.VIC);
                printf("YQ      = %u\n", aviInfoFrame.YQ);
                printf("CN      = %u\n", aviInfoFrame.CN);
                printf("PR      = %u\n", aviInfoFrame.PR);
                printf("ETB     = %u\n", aviInfoFrame.ETB);
                printf("SBB     = %u\n", aviInfoFrame.SBB);
                printf("ELB     = %u\n", aviInfoFrame.ELB);
                printf("SRB     = %u\n", aviInfoFrame.SRB);
                pvalid = true;
            } else if (!strcmp(s[2], "vsif")) {
                HDMI_Xil_Type::VendorSpecificInfoFrame_type vsifInfoFrame;
                HW_API::getHdmiRxInfoFrameVSIF(chan, &vsifInfoFrame);
                printf("Channel %u Rx Vendor Specific InfoFrame:\n", chan);
                printf("Type     = 0x%02x\n", vsifInfoFrame.Type);
                printf("Version  = 0x%02x\n", vsifInfoFrame.Version);
                printf("Length   = 0x%02x\n", vsifInfoFrame.Length);
                printf("IEEE_RI  = 0x%06x\n", vsifInfoFrame.IEEE_Registration_Identifier);
                printf("HDMI_VF  = %u\n", vsifInfoFrame.HDMI_Video_Format);
                printf("HDMI_VIC = %u\n", vsifInfoFrame.HDMI_VIC);
                printf("S 3D     = %u\n", vsifInfoFrame.Structure_3D);
                printf("Ext 3D   = %u\n", vsifInfoFrame.Ext_Data_3D);
                pvalid = true;
            } else if (!strcmp(s[2], "gcp")) {
                HDMI_Xil_Type::GeneralControlInfoFrame_type gcpInfoFrame;
                HW_API::getHdmiRxInfoFrameGCP(chan, &gcpInfoFrame);
                printf("Channel %u Rx General Control InfoFrame:\n", chan);
                printf("Type          = 0x%02x\n", gcpInfoFrame.Type);
                printf("Clear_AVMUTE  = %u\n", gcpInfoFrame.Clear_AVMUTE);
                printf("Set_AVMUTE    = %u\n", gcpInfoFrame.Set_AVMUTE);
                printf("PP            = %u\n", gcpInfoFrame.PP);
                printf("CD            = %u\n", gcpInfoFrame.CD);
                printf("Default_Phase = %u\n", gcpInfoFrame.Default_Phase);
                pvalid = true;
            } else if (!strcmp(s[2], "drm")) {
                HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type drmInfoFrame;
                HW_API::getHdmiRxInfoFrameDRM(chan, &drmInfoFrame);
                printf("Channel %u Rx Dynamic Range Mastering InfoFrame:\n", chan);
                printf("Type                 = 0x%02x\n", drmInfoFrame.Type);
                printf("Version              = 0x%02x\n", drmInfoFrame.Version);
                printf("Length               = 0x%02x\n", drmInfoFrame.Length);
                printf("EOTF                 = 0x%02x\n", drmInfoFrame.EOTF);
                printf("SMD ID               = 0x%02x\n", drmInfoFrame.Static_Metadata_Descriptor_ID);
                printf("Display Primaries X0 = 0x%02x\n", drmInfoFrame.Display_Primaries_X[0]);
                printf("Display Primaries X1 = 0x%02x\n", drmInfoFrame.Display_Primaries_X[1]);
                printf("Display Primaries X2 = 0x%02x\n", drmInfoFrame.Display_Primaries_X[2]);
                printf("Display Primaries Y0 = 0x%02x\n", drmInfoFrame.Display_Primaries_Y[0]);
                printf("Display Primaries Y1 = 0x%02x\n", drmInfoFrame.Display_Primaries_Y[1]);
                printf("Display Primaries Y2 = 0x%02x\n", drmInfoFrame.Display_Primaries_Y[2]);
                printf("White Point X        = 0x%02x\n", drmInfoFrame.White_Point_X);
                printf("White Point Y        = 0x%02x\n", drmInfoFrame.White_Point_Y);
                printf("Min DM Luminance     = 0x%02x\n", drmInfoFrame.Min_Display_Mastering_Luminance);
                printf("Max DM Luminance     = 0x%02x\n", drmInfoFrame.Max_Display_Mastering_Luminance);
                printf("Max Content LL       = 0x%02x\n", drmInfoFrame.Maximum_Frame_Average_Light_Level);
                printf("Max Frame Average LL = 0x%02x\n", drmInfoFrame.Maximum_Frame_Average_Light_Level);
                pvalid = true;
            } else if (!strcmp(s[2], "spd")) {
                HDMI_Xil_Type::SourceProductDescriptorInfoFrame_type spdInfoFrame;
                HW_API::getHdmiRxInfoFrameSPD(chan, &spdInfoFrame);
                printf("Channel %u Rx Source Product Description InfoFrame:\n", chan);
                printf("Type     = 0x%02x\n", spdInfoFrame.Type);
                printf("Version  = 0x%02x\n", spdInfoFrame.Version);
                printf("Length   = 0x%02x\n", spdInfoFrame.Length);
                printf("Vendor   = ");
                for (uint8_t i=0;i<8;i++) printf("%c", (spdInfoFrame.Vendor_Name_Character[i] & 0x7F));
                printf("\n");
                printf("Product  = ");
                for (uint8_t i=0;i<16;i++) printf("%c", (spdInfoFrame.Product_Description_Character[i]) & 0x7F);
                printf("\n");
                printf("Src Info = %u\n", spdInfoFrame.Source_Information);
                pvalid = true;
            } else if (!strcmp(s[2], "hdr10p")) {
                HDMI_Xil_Type::HDR10PlusInfoFrame_type hdr10pInfoFrame;
                HW_API::getHdmiRxInfoFrameHDR10Plus(chan, &hdr10pInfoFrame);
                printf("Channel %u Rx HDR10+ InfoFrame:\n", chan);
                printf("Type     = 0x%02x\n", hdr10pInfoFrame.Type);
                printf("Version  = 0x%02x\n", hdr10pInfoFrame.Version);
                printf("Length   = 0x%02x\n", hdr10pInfoFrame.Length);
                printf("IEEE_RI  = 0x%06x\n", hdr10pInfoFrame.IEEE_Registration_Identifier);
                printf("App Ver  = 0x%01x\n", hdr10pInfoFrame.Application_Version);
                printf("TSD ML   = 0x%02x\n", hdr10pInfoFrame.TSD_Max_Luminance);
                printf("Ave MRGB = 0x%02x\n", hdr10pInfoFrame.Average_MaxRGB);
                printf("DV[0]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[0]);
                printf("DV[1]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[1]);
                printf("DV[2]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[2]);
                printf("DV[3]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[3]);
                printf("DV[4]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[4]);
                printf("DV[5]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[5]);
                printf("DV[6]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[6]);
                printf("DV[7]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[7]);
                printf("DV[8]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[8]);
                printf("Num BCA  = 0x%02x\n", hdr10pInfoFrame.Num_Bezier_Curve_Anchors);
                printf("KneeP_X  = 0x%03x\n", hdr10pInfoFrame.Knee_Point_X);
                printf("KneeP_Y  = 0x%03x\n", hdr10pInfoFrame.Knee_Point_Y);
                printf("BCA[0]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[0]);
                printf("BCA[1]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[1]);
                printf("BCA[2]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[2]);
                printf("BCA[3]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[3]);
                printf("BCA[4]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[4]);
                printf("BCA[5]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[5]);
                printf("BCA[6]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[6]);
                printf("BCA[7]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[7]);
                printf("BCA[8]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[8]);
                printf("GO Flag  = 0x%01x\n", hdr10pInfoFrame.Graphics_Overlay_Flag);
                printf("VSIF TM  = 0x%01x\n", hdr10pInfoFrame.VSIF_Timing_Mode);
                pvalid = true;
            } else if (!strcmp(s[2], "dolby")) {
                HDMI_Xil_Type::DolbyInfoFrame_type dolbyInfoFrame;
                HW_API::getHdmiRxInfoFrameDolby(chan, &dolbyInfoFrame);
                printf("Channel %u Rx Dolby InfoFrame:\n", chan);
                printf("Type      = 0x%02x\n", dolbyInfoFrame.Type);
                printf("Version   = 0x%02x\n", dolbyInfoFrame.Version);
                printf("Length    = 0x%02x\n", dolbyInfoFrame.Length);
                printf("IEEE_RI   = 0x%06x\n", dolbyInfoFrame.IEEE_Registration_Identifier);
                printf("Src DM V  = 0x%01x\n", dolbyInfoFrame.Source_DM_Version);
                printf("VS10 type = 0x%02x\n", dolbyInfoFrame.Dolby_Vision_VS10_Signal_Type);
                printf("Low lat   = 0x%02x\n", dolbyInfoFrame.Low_latency);
                printf("Backlt    = 0x%02x\n", dolbyInfoFrame.Backlt_Ctrl_MD_Present);
                printf("Aux MD    = 0x%02x\n", dolbyInfoFrame.Auxiliary_MD_Present);
                printf("L11 MD    = 0x%02x\n", dolbyInfoFrame.L11_MD_Present);
                printf("BT2020    = 0x%02x\n", dolbyInfoFrame.BT2020_Container);
                printf("Eff PQ h  = 0x%02x\n", dolbyInfoFrame.Eff_tmax_PQ_hi);
                printf("Eff PQ l  = 0x%02x\n", dolbyInfoFrame.Eff_tmax_PQ_low);
                printf("Aux rmode = 0x%02x\n", dolbyInfoFrame.Auxiliary_runmode);
                printf("Aux rver  = 0x%02x\n", dolbyInfoFrame.Auxiliary_runversion);
                printf("Aux debug = 0x%02x\n", dolbyInfoFrame.Auxiliary_debug);
                printf("Cntnt typ = 0x%02x\n", dolbyInfoFrame.Content_type);
                printf("CrF       = 0x%03x\n", dolbyInfoFrame.CrF);
                printf("Int Wpnt  = 0x%03x\n", dolbyInfoFrame.Intended_White_Point);
                printf("L11 b2    = 0x%02x\n", dolbyInfoFrame.L11_byte2);
                printf("L11 b3    = 0x%02x\n", dolbyInfoFrame.L11_byte3);
                pvalid = true;
            } else if (!strcmp(s[2], "am")) {
                HDMI_Xil_Type::AudioMetadataPacket_type audiometadataInfoFrame;
                HW_API::getHdmiRxInfoFrameAudioMetadata(chan, &audiometadataInfoFrame);
                printf("Channel %u Rx Audio Metadata Packet:\n", chan);
                printf("Type      = 0x%02x\n", audiometadataInfoFrame.Type);
                printf("3D Audio  = %u\n", audiometadataInfoFrame.Audio_3D);
                printf("N Views   = %u\n", audiometadataInfoFrame.Number_Audio_Views);
                printf("N Streams = %u\n", audiometadataInfoFrame.Number_Audio_Streams);
                printf("3D CC     = 0x%02x\n", audiometadataInfoFrame.CC_3D);
                printf("ACAT      = 0x%01x\n", audiometadataInfoFrame.ACAT);
                printf("3D CA     = 0x%02x\n", audiometadataInfoFrame.CA_3D);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "txinfoframe")) {
            if (!strcmp(s[2], "init")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HW_API::setHdmiTxInfoFramesInitialized(chan);
                printf("Channel %u InfoFrames Initialized.\n", chan);
                pvalid = true;
            } else if (!strcmp(s[2], "vsifenable")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                bool enabled;
                HW_API::getHdmiTxInfoFrameVSIFEnable(chan, &enabled);
                printf("Channel %u InfoFrames VSIF Enable: %s.\n", chan, (enabled ? "True" : "False"));
                pvalid = true;
            } else if (!strcmp(s[2], "drmenable")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                bool enabled;
                HW_API::getHdmiTxInfoFrameDRMEnable(chan, &enabled);
                printf("Channel %u InfoFrames DRM Enable: %s.\n", chan, (enabled ? "True" : "False"));
                pvalid = true;
            } else if (!strcmp(s[2], "audio")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::AudioInfoFrame_type audioInfoFrame;
                HW_API::getHdmiTxInfoFrameAudio(chan, &audioInfoFrame);
                printf("Channel %u Tx Audio InfoFrame:\n", chan);
                printf("Type    = 0x%02x\n", audioInfoFrame.Type);
                printf("Version = 0x%02x\n", audioInfoFrame.Version);
                printf("Length  = 0x%02x\n", audioInfoFrame.Length);
                printf("CT      = %u\n", audioInfoFrame.CT);
                printf("CC      = %u\n", audioInfoFrame.CC);
                printf("SF      = %u\n", audioInfoFrame.SF);
                printf("SS      = %u\n", audioInfoFrame.SS);
                printf("CXT     = %u\n", audioInfoFrame.CXT);
                printf("CA      = %u\n", audioInfoFrame.CA);
                printf("DM_INH  = %u\n", audioInfoFrame.DM_INH);
                printf("LSV     = %u\n", audioInfoFrame.LSV);
                printf("LFEPBL  = %u\n", audioInfoFrame.LFEPBL);
                pvalid = true;
            } else if (!strcmp(s[2], "avi")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type aviInfoFrame;
                HW_API::getHdmiTxInfoFrameAVI(chan, &aviInfoFrame);
                printf("Channel %u Tx AVI InfoFrame:\n", chan);
                printf("Type    = 0x%02x\n", aviInfoFrame.Type);
                printf("Version = 0x%02x\n", aviInfoFrame.Version);
                printf("Length  = 0x%02x\n", aviInfoFrame.Length);
                printf("Y       = %u\n", aviInfoFrame.Y);
                printf("A       = %u\n", aviInfoFrame.A);
                printf("B       = %u\n", aviInfoFrame.B);
                printf("S       = %u\n", aviInfoFrame.S);
                printf("C       = %u\n", aviInfoFrame.C);
                printf("M       = %u\n", aviInfoFrame.M);
                printf("R       = %u\n", aviInfoFrame.R);
                printf("ITC     = %u\n", aviInfoFrame.ITC);
                printf("EC      = %u\n", aviInfoFrame.EC);
                printf("Q       = %u\n", aviInfoFrame.Q);
                printf("SC      = %u\n", aviInfoFrame.SC);
                printf("VIC     = %u\n", aviInfoFrame.VIC);
                printf("YQ      = %u\n", aviInfoFrame.YQ);
                printf("CN      = %u\n", aviInfoFrame.CN);
                printf("PR      = %u\n", aviInfoFrame.PR);
                printf("ETB     = %u\n", aviInfoFrame.ETB);
                printf("SBB     = %u\n", aviInfoFrame.SBB);
                printf("ELB     = %u\n", aviInfoFrame.ELB);
                printf("SRB     = %u\n", aviInfoFrame.SRB);
                pvalid = true;
            } else if (!strcmp(s[2], "vsif")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::VendorSpecificInfoFrame_type vsifInfoFrame;
                HW_API::getHdmiTxInfoFrameVSIF(chan, &vsifInfoFrame);
                printf("Channel %u Tx Vendor Specific InfoFrame:\n", chan);
                printf("Type     = 0x%02x\n", vsifInfoFrame.Type);
                printf("Version  = 0x%02x\n", vsifInfoFrame.Version);
                printf("Length   = 0x%02x\n", vsifInfoFrame.Length);
                printf("IEEE RI  = 0x%06x\n", vsifInfoFrame.IEEE_Registration_Identifier);
                printf("HDMI VF  = %u\n", vsifInfoFrame.HDMI_Video_Format);
                printf("HDMI_VIC = %u\n", vsifInfoFrame.HDMI_VIC);
                printf("S 3D     = %u\n", vsifInfoFrame.Structure_3D);
                printf("Ext 3D   = %u\n", vsifInfoFrame.Ext_Data_3D);
                pvalid = true;
            } else if (!strcmp(s[2], "drm")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type drmInfoFrame;
                HW_API::getHdmiTxInfoFrameDRM(chan, &drmInfoFrame);
                printf("Channel %u Tx Dynamic Range Mastering InfoFrame:\n", chan);
                printf("Type                 = 0x%02x\n", drmInfoFrame.Type);
                printf("Version              = 0x%02x\n", drmInfoFrame.Version);
                printf("Length               = 0x%02x\n", drmInfoFrame.Length);
                printf("EOTF                 = 0x%02x\n", drmInfoFrame.EOTF);
                printf("SMD ID               = 0x%02x\n", drmInfoFrame.Static_Metadata_Descriptor_ID);
                printf("Display Primaries X0 = 0x%02x\n", drmInfoFrame.Display_Primaries_X[0]);
                printf("Display Primaries X1 = 0x%02x\n", drmInfoFrame.Display_Primaries_X[1]);
                printf("Display Primaries X2 = 0x%02x\n", drmInfoFrame.Display_Primaries_X[2]);
                printf("Display Primaries Y0 = 0x%02x\n", drmInfoFrame.Display_Primaries_Y[0]);
                printf("Display Primaries Y1 = 0x%02x\n", drmInfoFrame.Display_Primaries_Y[1]);
                printf("Display Primaries Y2 = 0x%02x\n", drmInfoFrame.Display_Primaries_Y[2]);
                printf("White Point X        = 0x%02x\n", drmInfoFrame.White_Point_X);
                printf("White Point Y        = 0x%02x\n", drmInfoFrame.White_Point_Y);
                printf("Min DM Luminance     = 0x%02x\n", drmInfoFrame.Min_Display_Mastering_Luminance);
                printf("Max DM Luminance     = 0x%02x\n", drmInfoFrame.Max_Display_Mastering_Luminance);
                printf("Max Content LL       = 0x%02x\n", drmInfoFrame.Maximum_Frame_Average_Light_Level);
                printf("Max Frame Average LL = 0x%02x\n", drmInfoFrame.Maximum_Frame_Average_Light_Level);
                pvalid = true;
            } else if (!strcmp(s[2], "spd")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::SourceProductDescriptorInfoFrame_type spdInfoFrame;
                HW_API::getHdmiTxInfoFrameSPD(chan, &spdInfoFrame);
                printf("Channel %u Tx Source Product Description InfoFrame:\n", chan);
                printf("Type     = 0x%02x\n", spdInfoFrame.Type);
                printf("Version  = 0x%02x\n", spdInfoFrame.Version);
                printf("Length   = 0x%02x\n", spdInfoFrame.Length);
                printf("Vendor   = ");
                for (uint8_t i=0;i<8;i++) printf("%c", (spdInfoFrame.Vendor_Name_Character[i] & 0x7F));
                printf("\n");
                printf("Product  = ");
                for (uint8_t i=0;i<16;i++) printf("%c", (spdInfoFrame.Product_Description_Character[i]) & 0x7F);
                printf("\n");
                printf("Src Info = %u\n", spdInfoFrame.Source_Information);
                pvalid = true;
            } else if (!strcmp(s[2], "hdr10p")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::HDR10PlusInfoFrame_type hdr10pInfoFrame;
                HW_API::getHdmiTxInfoFrameHDR10Plus(chan, &hdr10pInfoFrame);
                printf("Channel %u Tx HDR10+ InfoFrame:\n", chan);
                printf("Type     = 0x%02x\n", hdr10pInfoFrame.Type);
                printf("Version  = 0x%02x\n", hdr10pInfoFrame.Version);
                printf("Length   = 0x%02x\n", hdr10pInfoFrame.Length);
                printf("IEEE_RI  = 0x%06x\n", hdr10pInfoFrame.IEEE_Registration_Identifier);
                printf("App Ver  = 0x%01x\n", hdr10pInfoFrame.Application_Version);
                printf("TSD ML   = 0x%02x\n", hdr10pInfoFrame.TSD_Max_Luminance);
                printf("Ave MRGB = 0x%02x\n", hdr10pInfoFrame.Average_MaxRGB);
                printf("DV[0]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[0]);
                printf("DV[1]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[1]);
                printf("DV[2]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[2]);
                printf("DV[3]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[3]);
                printf("DV[4]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[4]);
                printf("DV[5]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[5]);
                printf("DV[6]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[6]);
                printf("DV[7]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[7]);
                printf("DV[8]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[8]);
                printf("Num BCA  = 0x%02x\n", hdr10pInfoFrame.Num_Bezier_Curve_Anchors);
                printf("KneeP_X  = 0x%03x\n", hdr10pInfoFrame.Knee_Point_X);
                printf("KneeP_Y  = 0x%03x\n", hdr10pInfoFrame.Knee_Point_Y);
                printf("BCA[0]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[0]);
                printf("BCA[1]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[1]);
                printf("BCA[2]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[2]);
                printf("BCA[3]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[3]);
                printf("BCA[4]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[4]);
                printf("BCA[5]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[5]);
                printf("BCA[6]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[6]);
                printf("BCA[7]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[7]);
                printf("BCA[8]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[8]);
                printf("GO Flag  = 0x%01x\n", hdr10pInfoFrame.Graphics_Overlay_Flag);
                printf("VSIF TM  = 0x%01x\n", hdr10pInfoFrame.VSIF_Timing_Mode);
                pvalid = true;
            } else if (!strcmp(s[2], "dolby")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::DolbyInfoFrame_type dolbyInfoFrame;
                HW_API::getHdmiTxInfoFrameDolby(chan, &dolbyInfoFrame);
                printf("Channel %u Tx Dolby InfoFrame:\n", chan);
                printf("Type      = 0x%02x\n", dolbyInfoFrame.Type);
                printf("Version   = 0x%02x\n", dolbyInfoFrame.Version);
                printf("Length    = 0x%02x\n", dolbyInfoFrame.Length);
                printf("IEEE_RI   = 0x%06x\n", dolbyInfoFrame.IEEE_Registration_Identifier);
                printf("Src DM V  = 0x%01x\n", dolbyInfoFrame.Source_DM_Version);
                printf("VS10 type = 0x%02x\n", dolbyInfoFrame.Dolby_Vision_VS10_Signal_Type);
                printf("Low lat   = 0x%02x\n", dolbyInfoFrame.Low_latency);
                printf("Backlt    = 0x%02x\n", dolbyInfoFrame.Backlt_Ctrl_MD_Present);
                printf("Aux MD    = 0x%02x\n", dolbyInfoFrame.Auxiliary_MD_Present);
                printf("L11 MD    = 0x%02x\n", dolbyInfoFrame.L11_MD_Present);
                printf("BT2020    = 0x%02x\n", dolbyInfoFrame.BT2020_Container);
                printf("Eff PQ h  = 0x%02x\n", dolbyInfoFrame.Eff_tmax_PQ_hi);
                printf("Eff PQ l  = 0x%02x\n", dolbyInfoFrame.Eff_tmax_PQ_low);
                printf("Aux rmode = 0x%02x\n", dolbyInfoFrame.Auxiliary_runmode);
                printf("Aux rver  = 0x%02x\n", dolbyInfoFrame.Auxiliary_runversion);
                printf("Aux debug = 0x%02x\n", dolbyInfoFrame.Auxiliary_debug);
                printf("Cntnt typ = 0x%02x\n", dolbyInfoFrame.Content_type);
                printf("CrF       = 0x%03x\n", dolbyInfoFrame.CrF);
                printf("Int Wpnt  = 0x%03x\n", dolbyInfoFrame.Intended_White_Point);
                printf("L11 b2    = 0x%02x\n", dolbyInfoFrame.L11_byte2);
                printf("L11 b3    = 0x%02x\n", dolbyInfoFrame.L11_byte3);
                pvalid = true;
            } else if (!strcmp(s[2], "am")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::AudioMetadataPacket_type audiometadataInfoFrame;
                HW_API::getHdmiTxInfoFrameAudioMetadata(chan, &audiometadataInfoFrame);
                printf("Channel %u Tx Audio Metadata Packet:\n", chan);
                printf("Type      = 0x%02x\n", audiometadataInfoFrame.Type);
                printf("3D Audio  = %u\n", audiometadataInfoFrame.Audio_3D);
                printf("N Views   = %u\n", audiometadataInfoFrame.Number_Audio_Views);
                printf("N Streams = %u\n", audiometadataInfoFrame.Number_Audio_Streams);
                printf("3D CC     = 0x%02x\n", audiometadataInfoFrame.CC_3D);
                printf("ACAT      = 0x%01x\n", audiometadataInfoFrame.ACAT);
                printf("3D CA     = 0x%02x\n", audiometadataInfoFrame.CA_3D);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "rxmetadata")) {
            if (!strcmp(s[2], "count")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                uint16_t count;
                uint8_t dolby_count;
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HW_API::getHdmiRxMetadataCount(chan, &count);
                HW_API::getHdmiRxInfoFrameDolby14bCnt(chan, &dolby_count);
                printf("Channel %u Rx Metadata Counts:\n", chan);
                printf("HDMI 1.4b VSIF (Dolby) = %u\n", dolby_count);
                printf("All                    = %u\n", count);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "txmetadata")) {
            if (!strcmp(s[2], "count")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                uint16_t count_flushed;
                uint16_t count_drm;
                uint16_t count_hdr10p;
                uint16_t count_dolby_masked;
                uint16_t count_dolby_sent;
                uint16_t count_h14b_dolby_masked;
                uint16_t count_h14b_dolby_sent;
                uint16_t count_generic;
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HW_API::getHdmiTxMetadataFlushedCount(chan, &count_flushed);
                HW_API::getHdmiTxMetadataDRMCount(chan, &count_drm);
                HW_API::getHdmiTxMetadataHDR10PlusCount(chan, &count_hdr10p);
                HW_API::getHdmiTxMetadataDolbyCountMasked(chan, &count_dolby_masked);
                HW_API::getHdmiTxMetadataDolbyCountSent(chan, &count_dolby_sent);
                HW_API::getHdmiTxMetadataH14bDolbyCountMasked(chan, &count_h14b_dolby_masked);
                HW_API::getHdmiTxMetadataH14bDolbyCountSent(chan, &count_h14b_dolby_sent);
                HW_API::getHdmiTxMetadataGenericCount(chan, &count_generic);
                printf("Channel %u Tx Metadata Counts:\n", chan);
                printf("Flushed     = %u\n", count_flushed);
                printf("DRM         = %u\n", count_drm);
                printf("HDR10+      = %u\n", count_hdr10p);
                printf("Dolby       = %u sent\n", count_dolby_sent);
                printf("Dolby       = %u masked\n", count_dolby_masked);
                printf("H14b Dolby  = %u sent\n", count_h14b_dolby_sent);
                printf("H14b Dolby  = %u masked\n", count_h14b_dolby_masked);
                printf("Generic     = %u\n", count_generic);
                pvalid = true;
            } else if (!strcmp(s[2], "drm")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type drmInfoFrame;
                HW_API::getHdmiTxMetadataDRM(chan, &drmInfoFrame);
                printf("Channel %u Tx Dynamic Range Mastering Metadata:\n", chan);
                printf("Type                 = 0x%02x\n", drmInfoFrame.Type);
                printf("Version              = 0x%02x\n", drmInfoFrame.Version);
                printf("Length               = 0x%02x\n", drmInfoFrame.Length);
                printf("EOTF                 = 0x%02x\n", drmInfoFrame.EOTF);
                printf("SMD ID               = 0x%02x\n", drmInfoFrame.Static_Metadata_Descriptor_ID);
                printf("Display Primaries X0 = 0x%02x\n", drmInfoFrame.Display_Primaries_X[0]);
                printf("Display Primaries X1 = 0x%02x\n", drmInfoFrame.Display_Primaries_X[1]);
                printf("Display Primaries X2 = 0x%02x\n", drmInfoFrame.Display_Primaries_X[2]);
                printf("Display Primaries Y0 = 0x%02x\n", drmInfoFrame.Display_Primaries_Y[0]);
                printf("Display Primaries Y1 = 0x%02x\n", drmInfoFrame.Display_Primaries_Y[1]);
                printf("Display Primaries Y2 = 0x%02x\n", drmInfoFrame.Display_Primaries_Y[2]);
                printf("White Point X        = 0x%02x\n", drmInfoFrame.White_Point_X);
                printf("White Point Y        = 0x%02x\n", drmInfoFrame.White_Point_Y);
                printf("Min DM Luminance     = 0x%02x\n", drmInfoFrame.Min_Display_Mastering_Luminance);
                printf("Max DM Luminance     = 0x%02x\n", drmInfoFrame.Max_Display_Mastering_Luminance);
                printf("Max Content LL       = 0x%02x\n", drmInfoFrame.Maximum_Frame_Average_Light_Level);
                printf("Max Frame Average LL = 0x%02x\n", drmInfoFrame.Maximum_Frame_Average_Light_Level);
                pvalid = true;
            } else if (!strcmp(s[2], "hdr10p")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::HDR10PlusInfoFrame_type hdr10pInfoFrame;
                HW_API::getHdmiTxMetadataHDR10Plus(chan, &hdr10pInfoFrame);
                printf("Channel %u Tx HDR10+ Metadata:\n", chan);
                printf("Type     = 0x%02x\n", hdr10pInfoFrame.Type);
                printf("Version  = 0x%02x\n", hdr10pInfoFrame.Version);
                printf("Length   = 0x%02x\n", hdr10pInfoFrame.Length);
                printf("IEEE_RI  = 0x%06x\n", hdr10pInfoFrame.IEEE_Registration_Identifier);
                printf("App Ver  = 0x%01x\n", hdr10pInfoFrame.Application_Version);
                printf("TSD ML   = 0x%02x\n", hdr10pInfoFrame.TSD_Max_Luminance);
                printf("Ave MRGB = 0x%02x\n", hdr10pInfoFrame.Average_MaxRGB);
                printf("DV[0]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[0]);
                printf("DV[1]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[1]);
                printf("DV[2]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[2]);
                printf("DV[3]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[3]);
                printf("DV[4]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[4]);
                printf("DV[5]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[5]);
                printf("DV[6]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[6]);
                printf("DV[7]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[7]);
                printf("DV[8]    = 0x%02x\n", hdr10pInfoFrame.Distribution_Values[8]);
                printf("Num BCA  = 0x%02x\n", hdr10pInfoFrame.Num_Bezier_Curve_Anchors);
                printf("KneeP_X  = 0x%03x\n", hdr10pInfoFrame.Knee_Point_X);
                printf("KneeP_Y  = 0x%03x\n", hdr10pInfoFrame.Knee_Point_Y);
                printf("BCA[0]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[0]);
                printf("BCA[1]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[1]);
                printf("BCA[2]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[2]);
                printf("BCA[3]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[3]);
                printf("BCA[4]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[4]);
                printf("BCA[5]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[5]);
                printf("BCA[6]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[6]);
                printf("BCA[7]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[7]);
                printf("BCA[8]   = 0x%02x\n", hdr10pInfoFrame.Bezier_Curve_Anchors[8]);
                printf("GO Flag  = 0x%01x\n", hdr10pInfoFrame.Graphics_Overlay_Flag);
                printf("VSIF TM  = 0x%01x\n", hdr10pInfoFrame.VSIF_Timing_Mode);
                pvalid = true;
            } else if (!strcmp(s[2], "dolby")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::DolbyInfoFrame_type dolbyInfoFrame;
                HW_API::getHdmiTxMetadataDolby(chan, &dolbyInfoFrame);
                printf("Channel %u Tx Dolby Metadata:\n", chan);
                printf("Type      = 0x%02x\n", dolbyInfoFrame.Type);
                printf("Version   = 0x%02x\n", dolbyInfoFrame.Version);
                printf("Length    = 0x%02x\n", dolbyInfoFrame.Length);
                printf("IEEE_RI   = 0x%06x\n", dolbyInfoFrame.IEEE_Registration_Identifier);
                printf("Src DM V  = 0x%01x\n", dolbyInfoFrame.Source_DM_Version);
                printf("VS10 type = 0x%02x\n", dolbyInfoFrame.Dolby_Vision_VS10_Signal_Type);
                printf("Low lat   = 0x%02x\n", dolbyInfoFrame.Low_latency);
                printf("Backlt    = 0x%02x\n", dolbyInfoFrame.Backlt_Ctrl_MD_Present);
                printf("Aux MD    = 0x%02x\n", dolbyInfoFrame.Auxiliary_MD_Present);
                printf("L11 MD    = 0x%02x\n", dolbyInfoFrame.L11_MD_Present);
                printf("BT2020    = 0x%02x\n", dolbyInfoFrame.BT2020_Container);
                printf("Eff PQ h  = 0x%02x\n", dolbyInfoFrame.Eff_tmax_PQ_hi);
                printf("Eff PQ l  = 0x%02x\n", dolbyInfoFrame.Eff_tmax_PQ_low);
                printf("Aux rmode = 0x%02x\n", dolbyInfoFrame.Auxiliary_runmode);
                printf("Aux rver  = 0x%02x\n", dolbyInfoFrame.Auxiliary_runversion);
                printf("Aux debug = 0x%02x\n", dolbyInfoFrame.Auxiliary_debug);
                printf("Cntnt typ = 0x%02x\n", dolbyInfoFrame.Content_type);
                printf("CrF       = 0x%03x\n", dolbyInfoFrame.CrF);
                printf("Int Wpnt  = 0x%03x\n", dolbyInfoFrame.Intended_White_Point);
                printf("L11 b2    = 0x%02x\n", dolbyInfoFrame.L11_byte2);
                printf("L11 b3    = 0x%02x\n", dolbyInfoFrame.L11_byte3);
                pvalid = true;
            } else if (!strcmp(s[2], "generic")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::Aux_type genericAuxBuffer;
                HW_API::getHdmiTxMetadataGenericBuffer(chan, &genericAuxBuffer);
                printf("Channel %u Tx Generic Metadata:\n", chan);
                for (uint8_t i=0;i<sizeof(HDMI_Xil_Type::Aux_type);i++) {
                  printf("%02x ", ((uint8_t*)&(genericAuxBuffer))[i]);
                }
                printf("\n");
                pvalid = true;
            } else if (!strcmp(s[2], "sent")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                bool lh14b_vsif;
                bool rh14b_vsif;
                bool dolby_h14b_vsif;
                bool dolby_vsif;
                HW_API::getHdmiTxMetadataSent_localh14b_vsif(chan, &lh14b_vsif);
                HW_API::getHdmiTxMetadataSent_remoteh14b_vsif(chan, &rh14b_vsif);
                HW_API::getHdmiTxMetadataSent_dolby_h14b_vsif(chan, &dolby_h14b_vsif);
                HW_API::getHdmiTxMetadataSent_dolby_vsif(chan, &dolby_vsif);
                printf("Channel %u Dolby Vision InfoFrame detect:\n", chan);
                printf("HDMI 1.4b VSIF (local)        = %u\n", lh14b_vsif);
                printf("HDMI 1.4b VSIF (remote)       = %u\n", rh14b_vsif);
                printf("HDMI 1.4b VSIF (remote,Dolby) = %u\n", dolby_h14b_vsif);
                printf("Dolby VSIF                    = %u\n", dolby_vsif);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "ticorequired")) {
            uint32_t rxchan = strtoul(s[2], NULL, 0);
            HDMI_Xil_Type::ColourFormat_type colourFormat = (HDMI_Xil_Type::ColourFormat_type) strtoul(s[3], NULL, 0);
            HDMI_Xil_Type::ColourDepth_type colourDepth = HDMI_Xil_Type::BPC_10; //ASPEN is always 10bit.
            HW_API::initFPGABuildID();
            HW_API::initHdmi(rxchan);
            /* Check that Rx is Connected and StreamIsUp */
            if (!HW_API::getHdmiRxIsConnected(rxchan)) {
              printf("Channel %u Rx cable not connected!\n", rxchan);
              return 0;
            }
            if (!HW_API::getHdmiRxStreamIsUp(rxchan)) {
              printf("Channel %u Rx stream is not up!\n", rxchan);
              return 0;
            }
            bool ticoRequired;
            if(HW_API::getHdmiRxTicoRequired(rxchan,&ticoRequired,colourFormat,colourDepth) != HDMI_Xil_Type::RET_SUCCESS) {
              printf("Rx TICO Required Calculation Error.\n");
              return 0;
            };
            printf("Channel %u TICO Required: %s.\n", rxchan, (ticoRequired ? "True" : "False"));
            pvalid = true;
        } else if (!strcmp(s[1], "rxlink")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint32_t statusInterval = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::setHdmiRxLinkStatusInterval(chan,statusInterval);
            pvalid = true;
        } else if (!strcmp(s[1], "rxdisabledroperr")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool set = strtoul(s[3], NULL, 0) ? true : false;
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::setHdmiRxDisableDropErr(chan,set);
            pvalid = true;
        } else if (!strcmp(s[1], "rxdisablehcounterr")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool set = strtoul(s[3], NULL, 0) ? true : false;
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::setHdmiRxDisableHCountErr(chan,set);
            pvalid = true;
        } else if (!strcmp(s[1], "rxhpd")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool enabled = strtoul(s[3], NULL, 0) ? true : false;
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::setHdmiRxHotplugDetect(chan, enabled);
            pvalid = true;
        } else if (!strcmp(s[1], "rxclocknovideothreshold")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint32_t count = strtoul(s[3], NULL, 0);
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::setHdmiRxClockNoVideoThreshold(chan, count);
            pvalid = true;
        } else if (!strcmp(s[1], "edid")) {
            if (!strcmp(s[2], "default")) {
                uint32_t rxchan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(rxchan);
                /* Check that Rx is Connected */
                if (!HW_API::getHdmiRxIsConnected(rxchan)) {
                  printf("Channel %u Rx cable not connected!\n", rxchan);
                  return 0;
                }
                if (HW_API::setHdmiRxEDID(rxchan, Edid, sizeof(Edid)) != HDMI_Xil_Type::RET_SUCCESS) {
                  printf("setHdmiRxEDID failed!\n");
                  return 0;
                }
                pvalid = true;
            }
        } else if (!strcmp(s[1], "txlock")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool lock = static_cast<bool>(strtoul(s[3], NULL, 0));
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::setHdmiTxSi570LockEnable(chan, lock);
            pvalid = true;
        } else if (!strcmp(s[1], "txoff")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool off = static_cast<bool>(strtoul(s[3], NULL, 0));
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::setHdmiTxOff(chan, off);
            pvalid = true;
        }
    } else if (n == 5) {
        if (!strcmp(s[1], "edid")) {
            if (!strcmp(s[2], "clone")) {
                uint32_t rxchan = strtoul(s[3], NULL, 0);
                uint32_t txchan = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(rxchan);
                HW_API::initHdmi(txchan);
                /* Check that Rx is Connected */
                if (!HW_API::getHdmiRxIsConnected(rxchan)) {
                  printf("Channel %u Rx cable not connected!\n", rxchan);
                  return 0;
                }
                /* Check that Tx is Connected */
                if (!HW_API::getHdmiTxIsConnected(txchan)) {
                  printf("Channel %u Tx cable not connected!\n", txchan);
                  return 0;
                }
                uint8_t edid[256];
                uint32_t size;
                uint8_t valid;
                if (HW_API::getHdmiTxEDID(txchan, edid, &size, &valid) != HDMI_Xil_Type::RET_SUCCESS) {
                  printf("getHdmiTxEDID failed!\n");
                  return 0;
                }
                if (HW_API::setHdmiRxEDID(rxchan, edid, size) != HDMI_Xil_Type::RET_SUCCESS) {
                  printf("setHdmiRxEDID failed!\n");
                  return 0;
                }
                pvalid = true;
            }
        } else if (!strcmp(s[1], "hdcp")) {
            if (!strcmp(s[2], "info")) {
                uint32_t chan = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                if (!strcmp(s[3], "rx")) {
                  /* Check that Rx is Connected and StreamIsUp */
                  if (!HW_API::getHdmiRxIsConnected(chan)) {
                    printf("Channel %u Rx cable not connected!\n", chan);
                    return 0;
                  }
                  if (!HW_API::getHdmiRxStreamIsUp(chan)) {
                    printf("Channel %u Rx stream is not up!\n", chan);
                    return 0;
                  }
                  HDMI_Xil_Type::HDCP_type hdcpprotocol;
                  bool isAuth, isEncrypted;
                  if (HW_API::getHdmiRxHDCPProtocol(chan, &hdcpprotocol) != HDMI_Xil_Type::RET_SUCCESS) {
                    printf("getHdmiRxHDCPProtocol failed!\n");
                    return 0;
                  }
                  if (HW_API::getHdmiRxHDCPIsAuthenticated(chan, &isAuth) != HDMI_Xil_Type::RET_SUCCESS) {
                    printf("getHdmiRxHDCPIsAuthenticated failed!\n");
                    return 0;
                  }
                  if (HW_API::getHdmiRxHDCPIsEncrypted(chan, &isEncrypted) != HDMI_Xil_Type::RET_SUCCESS) {
                    printf("getHdmiRxHDCPIsEncrypted failed!\n");
                    return 0;
                  }
                  if (hdcpprotocol == HDMI_Xil_Type::HDCP_14) {
                    printf("Protocol: HDCP 1.4\n");
                    printf("Authenticated: %d\n", isAuth);
                    printf("Encrypted: %d\n", isEncrypted);
                  } else if (hdcpprotocol == HDMI_Xil_Type::HDCP_22) {
                    printf("Protocol: HDCP 2.2\n");
                    printf("Authenticated: %d\n", isAuth);
                    printf("Encrypted: %d\n", isEncrypted);
                  } else {
                    printf("Protocol: None\n");
                  }
                } else if (!strcmp(s[3], "tx")) {
                  /* Check that Tx is Connected and StreamIsUp */
                  if (!HW_API::getHdmiTxIsConnected(chan)) {
                    printf("Channel %u Tx cable not connected!\n", chan);
                    return 0;
                  }
                  if (!HW_API::getHdmiTxStreamIsUp(chan)) {
                    printf("Channel %u Tx stream is not up!\n", chan);
                    return 0;
                  }
                  HDMI_Xil_Type::HDCP_type hdcpprotocol;
                  bool isAuth, isEncrypted;
                  if (HW_API::getHdmiTxHDCPProtocol(chan, &hdcpprotocol) != HDMI_Xil_Type::RET_SUCCESS) {
                    printf("getHdmiTxHDCPProtocol failed!\n");
                    return 0;
                  }
                  if (HW_API::getHdmiTxHDCPIsAuthenticated(chan, &isAuth) != HDMI_Xil_Type::RET_SUCCESS) {
                    printf("getHdmiTxHDCPIsAuthenticated failed!\n");
                    return 0;
                  }
                  if (HW_API::getHdmiTxHDCPIsEncrypted(chan, &isEncrypted) != HDMI_Xil_Type::RET_SUCCESS) {
                    printf("getHdmiTxHDCPIsEncrypted failed!\n");
                    return 0;
                  }
                  if (hdcpprotocol == HDMI_Xil_Type::HDCP_14) {
                    printf("Protocol: HDCP 1.4\n");
                    printf("Authenticated: %d\n", isAuth);
                    printf("Encrypted: %d\n", isEncrypted);
                  } else if (hdcpprotocol == HDMI_Xil_Type::HDCP_22) {
                    printf("Protocol: HDCP 2.2\n");
                    printf("Authenticated: %d\n", isAuth);
                    printf("Encrypted: %d\n", isEncrypted);
                  } else {
                    printf("Protocol: None\n");
                  }
                }
                pvalid = true;
            } else if (!strcmp(s[2], "protocol")) {
                uint32_t chan = strtoul(s[4], NULL, 0);
                HDMI_Xil_Type::HDCP_type hdcpprotocol;
                if (!strcmp(s[3], "rx")) {
                  HW_API::initFPGABuildID();
                  HW_API::initHdmi(chan);
                  HW_API::getHdmiRxHDCPProtocol(chan, &hdcpprotocol);
                } else if (!strcmp(s[3], "tx")) {
                  HW_API::initFPGABuildID();
                  HW_API::initHdmi(chan);
                  HW_API::getHdmiTxHDCPProtocol(chan, &hdcpprotocol);
                }
                if (hdcpprotocol == HDMI_Xil_Type::HDCP_14) {
                  printf("Protocol: HDCP 1.4\n");
                } else if (hdcpprotocol == HDMI_Xil_Type::HDCP_22) {
                  printf("Protocol: HDCP 2.2\n");
                } else {
                  printf("Protocol: None\n");
                }
                pvalid = true;
            } else if (!strcmp(s[2], "debug")) {
                uint32_t chan = strtoul(s[4], NULL, 0);
                if (!strcmp(s[3], "rx")) {
                  HW_API::initFPGABuildID();
                  HW_API::initHdmi(chan);
                  HW_API::debugHdmiRxHdcp14(chan);
                  HW_API::debugHdmiRxHdcp22(chan);
                } else if (!strcmp(s[3], "tx")) {
                  HW_API::initFPGABuildID();
                  HW_API::initHdmi(chan);
                  HW_API::debugHdmiTxHdcp14(chan);
                  HW_API::debugHdmiTxHdcp22(chan);
                }
                pvalid = true;
            } else if (!strcmp(s[2], "auth")) {
                uint32_t txchan = strtoul(s[3], NULL, 0);
                bool enable = strtoul(s[4], NULL, 0)%2;
                HW_API::initFPGABuildID();
                HW_API::initHdmi(txchan);
                HW_API::setHdmiTxHDCPAuthenticationRequest(txchan, enable);
                pvalid = true;
            } else if (!strcmp(s[2], "encrypt")) {
                uint32_t txchan = strtoul(s[3], NULL, 0);
                bool enable = strtoul(s[4], NULL, 0)%2;
                HW_API::initFPGABuildID();
                HW_API::initHdmi(txchan);
                HW_API::setHdmiTxHDCPEnableEncryption(txchan, enable);
                pvalid = true;
            } else if (!strcmp(s[2], "waitingperiod")) {
                uint32_t txchan = strtoul(s[3], NULL, 0);
                uint32_t waitingPeriod = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(txchan);
                HW_API::setHdmiTxHDCPWaitingPeriod(txchan, waitingPeriod);
                pvalid = true;
            } else if (!strcmp(s[2], "mask")) {
                uint32_t txchan = strtoul(s[3], NULL, 0);
                HDMI_Xil_Type::HDCPMask_type hdcpMask = (HDMI_Xil_Type::HDCPMask_type)strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(txchan);
                HW_API::setHdmiTxHDCPMask(txchan, hdcpMask);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "write")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint32_t addr = strtoul(s[3], NULL, 0);
            uint8_t data = strtoul(s[4], NULL, 0)%256;
            HW_API::initFPGABuildID();
            HW_API::initHdmi(chan);
            HW_API::debugHdmiWrite(chan, addr, data);
            printf("Config[%d][%d] = %x\n", chan, addr, data);
            pvalid = true;
        } else if (!strcmp(s[1], "txaudcbits")) {
            uint32_t txchan = strtoul(s[2], NULL, 0);
            bool restamp = strtoul(s[3], NULL, 0) ? true : false;
            bool professional = strtoul(s[4], NULL, 0) ? true : false;
            HW_API::initFPGABuildID();
            HW_API::initHdmi(txchan);
            /* Check that Tx is Connected */
            if (!HW_API::getHdmiTxIsConnected(txchan)) {
              printf("Channel %u Tx cable not connected!\n", txchan);
              return 0;
            }
            HW_API::setHdmiTxAudioCbits(txchan, restamp, professional);
            pvalid = true;
        } else if (!strcmp(s[1], "txaudio")) {
            uint32_t chan = strtoul(s[3], NULL, 0);
            if (!strcmp(s[2], "forcesrc")) {
                bool force = strtoul(s[4], NULL, 0)>0;
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                /* Check that Tx is Connected and StreamIsUp */
                if (!HW_API::getHdmiTxIsConnected(chan)) {
                  printf("Channel %u Tx cable not connected!\n", chan);
                  return 0;
                }
                if (!HW_API::getHdmiTxStreamIsUp(chan)) {
                  printf("Channel %u Tx stream is not up!\n", chan);
                  return 0;
                }
                HW_API::setHdmiTxAudioForceSRC(chan, force);
                if (force)
                  printf("Channel %u Forcing SRC\n", chan);
                else
                  printf("Channel %u Automatic SRC\n", chan);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "txinfoframe")) {
            if (!strcmp(s[2], "vsifenable")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                bool enabled = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HW_API::setHdmiTxInfoFrameVSIFEnable(chan, enabled);
                pvalid = true;
            } else if (!strcmp(s[2], "drmenable")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                bool enabled = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HW_API::setHdmiTxInfoFrameDRMEnable(chan, enabled);
                pvalid = true;
            } else if (!strcmp(s[2], "hdr10penable")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                bool enabled = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HW_API::setHdmiTxInfoFrameHDR10PlusEnable(chan, enabled);
                pvalid = true;
            } else if (!strcmp(s[2], "dolbyenable")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                bool enabled = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HW_API::setHdmiTxInfoFrameDolbyEnable(chan, enabled);
                pvalid = true;
            } else if (!strcmp(s[2], "spdenable")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                bool enabled = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HW_API::setHdmiTxInfoFrameSPDEnable(chan, enabled);
                pvalid = true;
            } else if (!strcmp(s[2], "amenable")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                bool enabled = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HW_API::setHdmiTxInfoFrameAudioMetadataEnable(chan, enabled);
                pvalid = true;
            }
        }
    } else if (n == 6) {
        if (!strcmp(s[1], "hdcp")) {
            if (!strcmp(s[2], "protocol")) {
                uint32_t chan = strtoul(s[4], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::HDCP_type hdcpprotocol = (HDMI_Xil_Type::HDCP_type)strtoul(s[5], NULL, 0);
                if (!strcmp(s[3], "rx")) {
                  HW_API::setHdmiRxHDCPProtocol(chan, hdcpprotocol);
                //} else if (!strcmp(s[3], "tx")) {
                //  HW_API::setHdmiTxHDCPProtocol(chan, hdcpprotocol);
                }
                pvalid = true;
            }
        } else if(!strcmp(s[1], "settx")){
          uint32_t txchan = strtoul(s[2], NULL, 0);
          uint32_t bw = strtoul(s[3], NULL, 0)%HW_API::NUM_BIST_BW;
          uint32_t colour = strtoul(s[4], NULL, 0);
          bool fractional = strtoul(s[5], NULL, 0);
          HW_API::initFPGABuildID();
          HW_API::initHdmi(txchan);
          /* Check that Tx is Connected */
          if (!HW_API::getHdmiTxIsConnected(txchan)) {
            printf("Channel %u Tx cable not connected!\n", txchan);
            return 0;
          }
          HW_API::bistHdmiTx(txchan, (HW_API::bwBIST)bw, fractional, (HW_API::scColourFormat_type)colour);
          pvalid = true;
        } else if (!strcmp(s[1], "txinfoframe")) {
            if (!strcmp(s[2], "vsif")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::VendorSpecificInfoFrame_type vsifInfoFrame;
                memset(&vsifInfoFrame,0,sizeof(HDMI_Xil_Type::VendorSpecificInfoFrame_type));
                vsifInfoFrame.Type              = 0x81;
                vsifInfoFrame.Version           = 0x01;
                vsifInfoFrame.Length            = 0x04;
                vsifInfoFrame.HDMI_Video_Format = strtoul(s[4], NULL, 0);
                vsifInfoFrame.HDMI_VIC          = strtoul(s[5], NULL, 0);
                HW_API::setHdmiTxInfoFrameVSIF(chan, &vsifInfoFrame);
                printf("Channel %u Vendor Specific InfoFrame Set.\n", chan);
                pvalid = true;
            }
        }
    } else if (n == 7) {
        if (!strcmp(s[1], "settx")){
          uint32_t txchan = strtoul(s[2], NULL, 0);
          uint32_t bw = strtoul(s[3], NULL, 0)%HW_API::NUM_BIST_BW;
          uint32_t colour = strtoul(s[4], NULL, 0);
          bool fractional = strtoul(s[5], NULL, 0);
          uint32_t bits_per_component = strtoul(s[6], NULL, 0);
          HW_API::initFPGABuildID();
          HW_API::initHdmi(txchan);

          /* Check that Tx is Connected */
          if (!HW_API::getHdmiTxIsConnected(txchan)) {
            printf("Channel %u Tx cable not connected!\n", txchan);
            return 0;
          }
          HW_API::bistHdmiTx(txchan, (HW_API::bwBIST)bw, fractional, (HW_API::scColourFormat_type)colour, bits_per_component);
          pvalid = true;
        } else if (!strcmp(s[1], "txinfoframe")) {
            if (!strcmp(s[2], "spd")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::SourceProductDescriptorInfoFrame_type spdInfoFrame;
                memset(&spdInfoFrame,0,sizeof(HDMI_Xil_Type::SourceProductDescriptorInfoFrame_type));
                spdInfoFrame.Type                          = 0x83;
                spdInfoFrame.Version                       = 0x01;
                spdInfoFrame.Length                        = 0x19;
                for (uint8_t i=0;i<8;i++) (spdInfoFrame.Vendor_Name_Character[i] = s[4][i]);
                for (uint8_t i=0;i<16;i++) (spdInfoFrame.Product_Description_Character[i] = s[5][i]);
                spdInfoFrame.Source_Information            = strtoul(s[6], NULL, 0);
                HW_API::setHdmiTxInfoFrameSPD(chan, &spdInfoFrame);
                printf("Channel %u Source Product Descriptor InfoFrame Set.\n", chan);
                pvalid = true;
            }
        }
    } else if (n == 10) {
        if (!strcmp(s[1], "txinfoframe")) {
            if (!strcmp(s[2], "audio")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::AudioInfoFrame_type audioInfoFrame;
                memset(&audioInfoFrame,0,sizeof(HDMI_Xil_Type::AudioInfoFrame_type));
                audioInfoFrame.Type    = 0x84;
                audioInfoFrame.Version = 0x01;
                audioInfoFrame.Length  = 0x0A;
                audioInfoFrame.CC      = strtoul(s[4], NULL, 0);
                audioInfoFrame.SF      = strtoul(s[5], NULL, 0);
                audioInfoFrame.CA      = strtoul(s[6], NULL, 0);
                audioInfoFrame.DM_INH  = strtoul(s[7], NULL, 0);
                audioInfoFrame.LSV     = strtoul(s[8], NULL, 0);
                audioInfoFrame.LFEPBL  = strtoul(s[9], NULL, 0);
                HW_API::setHdmiTxInfoFrameAudio(chan, &audioInfoFrame);
                printf("Channel %u Audio InfoFrame Set.\n", chan);
                pvalid = true;
            }
        }
    } else if (n == 18) {
        if (!strcmp(s[1], "txinfoframe")) {
            if (!strcmp(s[2], "drm")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type drmInfoFrame;
                memset(&drmInfoFrame,0,sizeof(HDMI_Xil_Type::DynamicRangeMasteringInfoFrame_type));
                drmInfoFrame.Type    = 0x87;
                drmInfoFrame.Version = 0x01;
                drmInfoFrame.Length  = 0x1A;
                drmInfoFrame.EOTF                              = strtoul(s[4], NULL, 0);
                drmInfoFrame.Static_Metadata_Descriptor_ID     = strtoul(s[5], NULL, 0);
                drmInfoFrame.Display_Primaries_X[0]            = strtoul(s[6], NULL, 0);
                drmInfoFrame.Display_Primaries_X[1]            = strtoul(s[7], NULL, 0);
                drmInfoFrame.Display_Primaries_X[2]            = strtoul(s[8], NULL, 0);
                drmInfoFrame.Display_Primaries_Y[0]            = strtoul(s[9], NULL, 0);
                drmInfoFrame.Display_Primaries_Y[1]            = strtoul(s[10], NULL, 0);
                drmInfoFrame.Display_Primaries_Y[2]            = strtoul(s[11], NULL, 0);
                drmInfoFrame.White_Point_X                     = strtoul(s[12], NULL, 0);
                drmInfoFrame.White_Point_Y                     = strtoul(s[13], NULL, 0);
                drmInfoFrame.Min_Display_Mastering_Luminance   = strtoul(s[14], NULL, 0);
                drmInfoFrame.Max_Display_Mastering_Luminance   = strtoul(s[15], NULL, 0);
                drmInfoFrame.Maximum_Frame_Average_Light_Level = strtoul(s[16], NULL, 0);
                drmInfoFrame.Maximum_Frame_Average_Light_Level = strtoul(s[17], NULL, 0);
                HW_API::setHdmiTxInfoFrameDRM(chan, &drmInfoFrame);
                printf("Channel %u DRM InfoFrame Set.\n", chan);
                pvalid = true;
            }
        }
    } else if (n == 23) {
        if (!strcmp(s[1], "txinfoframe")) {
            if (!strcmp(s[2], "avi")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::initHdmi(chan);
                HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type aviInfoFrame;
                memset(&aviInfoFrame,0,sizeof(HDMI_Xil_Type::AuxiliaryVideoInformationInfoFrame_type));
                aviInfoFrame.Type    = 0x82;
                aviInfoFrame.Version = 0x02;
                aviInfoFrame.Length  = 0x0D;
                aviInfoFrame.Y       = strtoul(s[4], NULL, 0);
                aviInfoFrame.A       = strtoul(s[5], NULL, 0);
                aviInfoFrame.B       = strtoul(s[6], NULL, 0);
                aviInfoFrame.S       = strtoul(s[7], NULL, 0);
                aviInfoFrame.C       = strtoul(s[8], NULL, 0);
                aviInfoFrame.M       = strtoul(s[9], NULL, 0);
                aviInfoFrame.R       = strtoul(s[10], NULL, 0);
                aviInfoFrame.ITC     = strtoul(s[11], NULL, 0);
                aviInfoFrame.EC      = strtoul(s[12], NULL, 0);
                aviInfoFrame.Q       = strtoul(s[13], NULL, 0);
                aviInfoFrame.SC      = strtoul(s[14], NULL, 0);
                aviInfoFrame.VIC     = strtoul(s[15], NULL, 0);
                aviInfoFrame.YQ      = strtoul(s[16], NULL, 0);
                aviInfoFrame.CN      = strtoul(s[17], NULL, 0);
                aviInfoFrame.PR      = strtoul(s[18], NULL, 0);
                aviInfoFrame.ETB     = strtoul(s[19], NULL, 0);
                aviInfoFrame.SBB     = strtoul(s[20], NULL, 0);
                aviInfoFrame.ELB     = strtoul(s[21], NULL, 0);
                aviInfoFrame.SRB     = strtoul(s[22], NULL, 0);
                HW_API::setHdmiTxInfoFrameAVI(chan, &aviInfoFrame);
                printf("Channel %u AVI InfoFrame Set.\n", chan);
                pvalid = true;
            }
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execXBARCONFIG(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s audio\n", s[0]);
        printf("Usage: %s video\n", s[0]);
        printf("Usage: %s meta\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        printf("   To read:  %s %s <index>\n", s[0], s[1]);
        printf("   To write: %s %s <index> <sel>\n", s[0], s[1]);
        printf("\n");
        if (!strcmp(s[1], "audio")) {
            printf("   where index = output index (0 to %d)\n", (HW_API::N_AUD_XBAR_OUT-1));
            printf("     and   sel = input index (0 to %d)\n",(HW_API::N_AUD_XBAR_IN-1));
        } else if (!strcmp(s[1], "video")) {
            printf("   where index = output index (0 to %d)\n", (HW_API::N_VID_XBAR_OUT-1));
            printf("     and   sel = input index (0 to %d)\n", (HW_API::N_VID_XBAR_IN-1));
        } else if (!strcmp(s[1], "meta")) {
            printf("   where index = output index (0 to %d)\n", (HW_API::N_META_XBAR_OUT-1));
            printf("     and   sel = input index (0 to %d)\n", (HW_API::N_META_XBAR_IN-1));
        }
    } else if (n == 3) {
        uint32_t index = strtoul(s[2], NULL, 0);
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "audio")) {
            int32_t sel = HW_API::getAudioXbarSel(index);
            if (sel >= 0) {
                printf("Audio output %u is sourced from input %d.\n", index, sel);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "video")) {
            int32_t sel = HW_API::getVideoXbarSel(index);
            if (sel >= 0) {
                printf("Video output %u is sourced from input %u.\n", index, sel);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "meta")) {
            int32_t sel = HW_API::getMetaXbarSel(index);
            if (sel >= 0) {
                printf("Meta output %u is sourced from input %u.\n", index, sel);
                pvalid = true;
            }
        }
    } else if (n == 4) {
        uint32_t index = strtoul(s[2], NULL, 0);
        uint32_t sel = strtoul(s[3], NULL, 0);
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "audio")) {
            printf("Selecting Audio input %u as source for Audio output %u.\n", sel, index);
            HW_API::setAudioXbarSel(index, sel);
            pvalid = true;
        } else if (!strcmp(s[1], "video")) {
            printf("Selecting Video input %u as source for Video output %u.\n", sel, index);
            HW_API::setVideoXbarSel(index, sel);
            pvalid = true;
        } else if (!strcmp(s[1], "meta")) {
            printf("Selecting Meta input %u as source for Meta output %u.\n", sel, index);
            HW_API::setMetaXbarSel(index, sel);
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execAUDSTATUS(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: \n");
        printf("      To initialize: %s init\n", s[0]);
        printf("      To read input status:  %s input <index> (0 to %d)\n", s[0], (HW_API::N_AUD_XBAR_IN-1));
        printf("      To read output status: %s output <index> (0 to %d)\n", s[0], (HW_API::N_AUD_XBAR_OUT-1));
        pvalid = true;
    } else if (n == 2) {
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "init")) {
            printf("Initializing audio presence detection with known good config...\n");
            if (HW_API::initAudPres()) {
                printf("Done.\n");
            }
            pvalid = true;
        }
    } else if (n == 3) {
        uint32_t index = strtoul(s[2], NULL, 0);
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "input")) {
            if (index < HW_API::N_AUD_XBAR_IN) {
                XBARCONFIG::audio_status_type audio_status;
                int32_t ret = HW_API::getAudInStatus(index, &audio_status);
                if (ret >= 0) {
                    printf("Audio presence:   %s, %08x.\n", (audio_status.presence ? "true" : "false"), audio_status.presence);
                    printf("Audio compressed: %s.\n", (audio_status.compressed ? "true" : "false"));
                    printf("Audio HBR:        %s.\n", (audio_status.hbr ? "true" : "false"));
                    printf("Audio SF:         %01x.\n", (audio_status.sf));
                }
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "output")) {
            if (index < HW_API::N_AUD_XBAR_OUT) {
                XBARCONFIG::audio_status_type audio_status;
                int32_t ret = HW_API::getAudOutStatus(index, &audio_status);
                if (ret >= 0) {
                    printf("Audio presence:   %s, %08x.\n", (audio_status.presence ? "true" : "false"), audio_status.presence);
                    printf("Audio compressed: %s.\n", (audio_status.compressed ? "true" : "false"));
                    printf("Audio HBR:        %s.\n", (audio_status.hbr ? "true" : "false"));
                    printf("Audio SF:         %01x.\n", (audio_status.sf));
                }
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execAUDGAIN(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: \n");
        printf("  To set input gain:  %s input <index> (0 to %d)  <gain>\n", s[0], (HW_API::N_AUD_XBAR_IN-1));
        printf("  To set output gain: %s output <index> (0 to %d) <gain>\n", s[0], (HW_API::N_AUD_XBAR_OUT-1));
        printf("  where gain is in percentage with respect to unity (0 -> 400)\n");
        pvalid = true;
    } else if (n == 4) {
        uint32_t index = strtoul(s[2], NULL, 0);
        double gain = (double)strtoul(s[3], NULL, 0);
        HW_API::initFPGABuildID();
        if (!strcmp(s[1], "input")) {
            if (index < HW_API::N_AUD_XBAR_IN) {
                HW_API::setAudInGain(index, gain);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "output")) {
            if (index < HW_API::N_AUD_XBAR_OUT) {
                HW_API::setAudOutGain(index, gain);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execTico(int n, char *s[])
{
    bool pvalid = false;
    if (n == 1) {
        printf("Usage: %s enc config  <idx> (0-%u) width height bitrate refresh_rate_num refresh_rate_den [bit_depth] [lvl_weights] [subsample_mode] [s2110] [interlaced]\n", s[0], (HW_API::N_XGE_TX_VID_TICO-1));
        printf("       %s enc status  <idx> (0-%u)\n", s[0], (HW_API::N_XGE_TX_VID_TICO-1));
        printf("       %s enc restart <idx> (0-%u)\n", s[0], (HW_API::N_XGE_TX_VID_TICO-1));
        printf("       %s enc enable  <idx> (0-%u)\n", s[0], (HW_API::N_XGE_TX_VID_TICO-1));
        printf("       %s enc disable <idx> (0-%u)\n", s[0], (HW_API::N_XGE_TX_VID_TICO-1));
        printf("       %s dec config  <idx> (0-%u) width height refresh_rate_num refresh_rate_den [downscale]\n", s[0], (HW_API::N_XGE_RX_VID_ASPENTICO-1));
        printf("       %s dec status  <idx> (0-%u)\n", s[0], (HW_API::N_XGE_RX_VID_ASPENTICO-1));
        printf("       %s dec restart <idx> (0-%u)\n", s[0], (HW_API::N_XGE_TX_VID_TICO-1));
        printf("  where width is the number of active pixels per line,\n");
        printf("  height is the number of active lines per field,\n");
        printf("  and bitrate is in bits per second\n");
        printf("  where:\n");
        printf("        subsample_mode: 0 = YCbCr422, 1 = YCbCr444, 2 = RGB (444)\n");
        printf("        downscale: 0 = original, 1 = div2, 2 = div4\n");
        printf("        s2110        = configure S2110-22 header (0(no)-1(yes))\n");
        printf("        interlaced   = interlace flag (0-1)\n");
        pvalid = true;
    } else if (n == 4) {
        if (!strcmp(s[1], "enc")) {
            if (!strcmp(s[2], "status")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                TICOtoIP::enc_status status = HW_API::getTicoEncStatus(idx);
                printf("debug flags:\n");
                printf("    ts_ready_err:            %d\n", (status.ts_ready_err ? 1 : 0));
                printf("    ts_valid_err:            %d\n", (status.ts_valid_err ? 1 : 0));
                printf("    ts_align_err:            %d\n", (status.ts_align_err ? 1 : 0));
                printf("    vid_first_line_err:      %d\n", (status.vid_first_line_err ? 1 : 0));
                printf("    vid_last_line_late_err:  %d\n", (status.vid_last_line_late_err ? 1 : 0));
                printf("    vid_last_line_early_err: %d\n", (status.vid_last_line_early_err ? 1 : 0));
                printf("    vid_first_pix_err:       %d\n", (status.vid_first_pix_err ? 1 : 0));
                printf("    vid_last_pix_late_err:   %d\n", (status.vid_last_pix_late_err ? 1 : 0));
                printf("    vid_last_pix_early_err:  %d\n", (status.vid_last_pix_early_err ? 1 : 0));
                printf("    vid_handshake_err:       %d\n", (status.vid_handshake_err ? 1 : 0));
                printf("    vid_align_err:           %d\n", (status.vid_align_err ? 1 : 0));
                printf("    vid_sof_data_valid_err:  %d\n", (status.vid_sof_data_valid_err ? 1 : 0));
                printf("    vid_sof_ready_err:       %d\n", (status.vid_sof_ready_err ? 1 : 0));
                printf("    vid_sof_valid_err:       %d\n", (status.vid_sof_valid_err ? 1 : 0));
                printf("    path_oflow_err:          %d\n", (status.path_oflow_err ? 1 : 0));
                pvalid = true;
            } else if (!strcmp(s[2], "restart")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::restartTicoEnc(idx);
                pvalid = true;
            } else if (!strcmp(s[2], "enable")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::enableTicoEnc(idx);
                pvalid = true;
            } else if (!strcmp(s[2], "disable")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::disableTicoEnc(idx);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "dec")) {
            if (!strcmp(s[2], "status")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                IPtoTICO::dec_status status = HW_API::getTicoDecStatus(idx);
                printf("debug flags:\n");
                printf("    vid_pl_buf_oflow: %d\n", (status.vid_pl_buf_oflow ? 1 : 0));
                printf("    path_oflow_err:   %d\n", (status.path_oflow_err ? 1 : 0));
                printf("    pes_pkt_hdr_err:  %d\n", (status.pes_pkt_hdr_err ? 1 : 0));
                printf("    ts_ready_err:     %d\n", (status.ts_ready_err ? 1 : 0));
                printf("    ts_valid_err:     %d\n", (status.ts_valid_err ? 1 : 0));
                printf("    ts_sync_err:      %d\n", (status.ts_sync_err ? 1 : 0));
                printf("    ts_align_err:     %d\n", (status.ts_align_err ? 1 : 0));
                printf("    ts_tei_err:       %d\n", (status.ts_tei_err ? 1 : 0));
                pvalid = true;
            } else if (!strcmp(s[2], "restart")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::restartTicoDec(idx);
                pvalid = true;
            }
        }
    } else if (n == 8) {
        if (!strcmp(s[1], "dec")) {
            if (!strcmp(s[2], "config")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                uint32_t width = strtoul(s[4], NULL, 0);
                uint32_t height = strtoul(s[5], NULL, 0);
                uint32_t refresh_rate_num = strtoul(s[6], NULL, 0);
                uint32_t refresh_rate_den = strtoul(s[7], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::configTicoDec(idx, width, height, refresh_rate_num, refresh_rate_den);
                pvalid = true;
            }
        }
    } else if (n == 9) {
        if (!strcmp(s[1], "enc")) {
            if (!strcmp(s[2], "config")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                uint32_t width = strtoul(s[4], NULL, 0);
                uint32_t height = strtoul(s[5], NULL, 0);
                uint64_t bitrate = strtoull(s[6], NULL, 0);
                uint32_t refresh_rate_num = strtoul(s[7], NULL, 0);
                uint32_t refresh_rate_den = strtoul(s[8], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::configTicoEnc(idx, width, height, bitrate, refresh_rate_num, refresh_rate_den);
                pvalid = true;
            }
        } else if (!strcmp(s[1], "dec")) {
            if (!strcmp(s[2], "config")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                uint32_t width = strtoul(s[4], NULL, 0);
                uint32_t height = strtoul(s[5], NULL, 0);
                uint32_t refresh_rate_num = strtoul(s[6], NULL, 0);
                uint32_t refresh_rate_den = strtoul(s[7], NULL, 0);
                uint32_t downscale = strtoul(s[8], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::configTicoDec(idx, width, height, refresh_rate_num, refresh_rate_den, downscale);
                pvalid = true;
            }
        }
    } else if (n == 10) {
        if (!strcmp(s[1], "enc")) {
            if (!strcmp(s[2], "config")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                uint32_t width = strtoul(s[4], NULL, 0);
                uint32_t height = strtoul(s[5], NULL, 0);
                uint64_t bitrate = strtoull(s[6], NULL, 0);
                uint32_t refresh_rate_num = strtoul(s[7], NULL, 0);
                uint32_t refresh_rate_den = strtoul(s[8], NULL, 0);
                uint32_t bit_depth = strtoul(s[9], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::configTicoEnc(idx, width, height, bitrate, refresh_rate_num, refresh_rate_den, bit_depth);
                pvalid = true;
            }
        }
    } else if (n == 11) {
        if (!strcmp(s[1], "enc")) {
            if (!strcmp(s[2], "config")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                uint32_t width = strtoul(s[4], NULL, 0);
                uint32_t height = strtoul(s[5], NULL, 0);
                uint64_t bitrate = strtoull(s[6], NULL, 0);
                uint32_t refresh_rate_num = strtoul(s[7], NULL, 0);
                uint32_t refresh_rate_den = strtoul(s[8], NULL, 0);
                uint32_t bit_depth = strtoul(s[9], NULL, 0);
                uint32_t lvl_weights = strtoul(s[10], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::configTicoEnc(idx, width, height, bitrate, refresh_rate_num, refresh_rate_den, bit_depth, lvl_weights);
                pvalid = true;
            }
        }
    } else if (n == 12) {
        if (!strcmp(s[1], "enc")) {
            if (!strcmp(s[2], "config")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                uint32_t width = strtoul(s[4], NULL, 0);
                uint32_t height = strtoul(s[5], NULL, 0);
                uint64_t bitrate = strtoull(s[6], NULL, 0);
                uint32_t refresh_rate_num = strtoul(s[7], NULL, 0);
                uint32_t refresh_rate_den = strtoul(s[8], NULL, 0);
                uint32_t bit_depth = strtoul(s[9], NULL, 0);
                uint32_t lvl_weights = strtoul(s[10], NULL, 0);
                uint8_t subsample = strtoul(s[11], NULL, 0)%HW_API::NUM_TICO_SUBSAMPLING_MODE;
                HW_API::initFPGABuildID();
                HW_API::configTicoEnc(idx, width, height, bitrate, refresh_rate_num, refresh_rate_den, bit_depth, lvl_weights,(HW_API::TicoSubSampling_Mode)subsample);
                pvalid = true;
            }
        }
    } else if (n == 14) {
        if (!strcmp(s[1], "enc")) {
            if (!strcmp(s[2], "config")) {
                uint32_t idx = strtoul(s[3], NULL, 0);
                uint32_t width = strtoul(s[4], NULL, 0);
                uint32_t height = strtoul(s[5], NULL, 0);
                uint64_t bitrate = strtoull(s[6], NULL, 0);
                uint32_t refresh_rate_num = strtoul(s[7], NULL, 0);
                uint32_t refresh_rate_den = strtoul(s[8], NULL, 0);
                uint32_t bit_depth = strtoul(s[9], NULL, 0);
                uint32_t lvl_weights = strtoul(s[10], NULL, 0);
                uint8_t subsample = strtoul(s[11], NULL, 0)%HW_API::NUM_TICO_SUBSAMPLING_MODE;
                uint32_t s2110 = strtoul(s[12], NULL, 0);
                uint32_t interlaced = strtoul(s[13], NULL, 0);
                HW_API::initFPGABuildID();
                HW_API::configTicoEnc(idx, width, height, bitrate, refresh_rate_num, refresh_rate_den, bit_depth, lvl_weights,(HW_API::TicoSubSampling_Mode)subsample, s2110, interlaced);
                pvalid = true;
            }
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execAMixer(int n, char *s[])
{
  bool pvalid = false;
  if(n == 1){ // one parameter provided --> hw audio_mixer
    printf("Usage:  %s invert <index> <channel> <branch> [invert]\n", s[0]); // read: n=4, write: n=5
    printf("        %s inStream <index> <channel> <branch> [inStream]\n", s[0]); // read: n=4, write: n=5
    printf("        %s inChannel <index> <channel> <branch> [inChannel]\n", s[0]); // read: n=4, write: n=5
    printf("        %s gain <index> <channel> <branch> [gain]\n", s[0]); // read: n=4, write: n=5
    printf("        %s set <index> <channel> <branch> <invert> <inStream> <inChannel> <gain>\n", s[0]); // write: n=8
    printf("        %s dump <index>\n", s[0]); // nested for loop
    pvalid = true;
  } else if (n == 5){
    uint8_t index = strtoul(s[2], NULL, 0);
    uint8_t channel = strtoul(s[3], NULL, 0);
    uint8_t branch = strtoul(s[4], NULL, 0);
    if(!strcmp(s[1], "invert"))
    {
      bool invert;
      HW_API::initFPGABuildID();
      HW_API::initAMixer(index, HW_API::INTEGER_BITS, HW_API::FLOAT_BITS);
      int ret = HW_API::getAMixerInvertControl(index, channel, branch, &invert);
      if (ret == -1)
      {
        printf("Channel value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -2)
      {
        printf("Branch value out of bounds!\n");
        pvalid = true;
      }
      else
      {
        printf("Read invert with index: %u, channel: %u, branch: %u, invert = %u\n", index, channel, branch, invert);
        pvalid = true;
      }
    } else if(!strcmp(s[1], "inStream")){
      uint8_t inStream;
      HW_API::initFPGABuildID();
      HW_API::initAMixer(index, HW_API::INTEGER_BITS, HW_API::FLOAT_BITS);
      int ret = HW_API::getAMixerInStream(index, channel, branch, &inStream);
      if (ret == -1)
      {
        printf("Channel value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -2)
      {
        printf("Branch value out of bounds!\n");
        pvalid = true;
      }
      else
      {
        printf("Read inStream with index: %u, channel: %u, branch: %u, inStream = %u\n", index, channel, branch, inStream);
        pvalid = true;
      }
    } else if(!strcmp(s[1], "inChannel")){
      uint8_t inChannel;
      HW_API::initFPGABuildID();
      HW_API::initAMixer(index, HW_API::INTEGER_BITS, HW_API::FLOAT_BITS);
      int ret = HW_API::getAMixerInChannel(index, channel, branch, &inChannel);
      if (ret == -1)
      {
        printf("Channel value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -2)
      {
        printf("Branch value out of bounds!\n");
        pvalid = true;
      }
      else
      {
        printf("Read inChannel with index: %u, channel: %u, branch: %u, inChannel = %u\n", index, channel, branch, inChannel);
        pvalid = true;
      }
    } else if(!strcmp(s[1], "gain")){
      float gain;
      HW_API::initFPGABuildID();
      HW_API::initAMixer(index, HW_API::INTEGER_BITS, HW_API::FLOAT_BITS);
      int ret = HW_API::getAMixerGainCoefficient(index, channel, branch, &gain);
      if (ret == -1)
      {
        printf("Channel value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -2)
      {
        printf("Branch value out of bounds!\n");
        pvalid = true;
      }
      else
      {
        printf("Read gain with index: %u, channel: %u, branch: %u, gain = %f\n", index, channel, branch, gain);
        pvalid = true;
      }
    }
  } else if (n == 6){
    uint8_t index = strtoul(s[2], NULL, 0);
    uint8_t channel = strtoul(s[3], NULL, 0);
    uint8_t branch = strtoul(s[4], NULL, 0);
    if(!strcmp(s[1], "invert")){
      bool invert = static_cast<bool> (strtoul(s[5], NULL, 0));
      HW_API::initFPGABuildID();
      HW_API::initAMixer(index, HW_API::INTEGER_BITS, HW_API::FLOAT_BITS);
      int ret = HW_API::setAMixerInvertControl(index, channel, branch, invert);
      if (ret == -1)
      {
        printf("Channel value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -2)
      {
        printf("Branch value out of bounds!\n");
        pvalid = true;
      }
      else
      {
        printf("Write invert with index: %u, channel: %u, branch: %u, invert: %u\n", index, channel, branch, invert);
        pvalid = true;
      }
    } else if (!strcmp(s[1], "inStream")){
      uint8_t inStream = strtoul(s[5], NULL, 0);
      HW_API::initFPGABuildID();
      HW_API::initAMixer(index, HW_API::INTEGER_BITS, HW_API::FLOAT_BITS);
      int ret = HW_API::setAMixerInStream(index, channel, branch, inStream);
      if (ret == -1)
      {
        printf("Channel value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -2)
      {
        printf("Branch value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -3)
      {
        printf("Input stream value out of bounds!\n");
        pvalid = true;
      }
      else
      {
        printf("Write inStream with index: %u, channel: %u, branch: %u, inStream: %u\n", index, channel, branch, inStream);
        pvalid = true;
      }
    } else if(!strcmp(s[1], "inChannel")){
      uint8_t inChannel = strtoul(s[5], NULL, 0);
      HW_API::initFPGABuildID();
      HW_API::initAMixer(index, HW_API::INTEGER_BITS, HW_API::FLOAT_BITS);
      int ret = HW_API::setAMixerInChannel(index, channel, branch, inChannel);
      if (ret == -1)
      {
        printf("Channel value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -2)
      {
        printf("Branch value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -4)
      {
        printf("Input channel value out of bounds!\n");
        pvalid = true;
      }
      else
      {
        printf("Write inChannel with index: %u, channel: %u, branch: %u, inChannel: %u\n", index, channel, branch, inChannel);
        pvalid = true;
      }
    } else if (!strcmp(s[1], "gain")){
      float gain = strtof(s[5], NULL);
      HW_API::initFPGABuildID();
      HW_API::initAMixer(index, HW_API::INTEGER_BITS, HW_API::FLOAT_BITS);
      int ret = HW_API::setAMixerGainCoefficient(index, channel, branch, gain);
      if (ret == -1)
      {
        printf("Channel value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -2)
      {
        printf("Branch value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -5)
      {
        printf("Gain value out of bounds!\n");
        pvalid = true;
      }
      else
      {
        printf("Write gain with index: %u, channel: %u, branch: %u, gain: %f\n", index, channel, branch, gain);
        pvalid = true;
      }
    }
  } else if (n == 9){
    uint8_t index = strtoul(s[2], NULL, 0);
    uint8_t channel = strtoul(s[3], NULL, 0);
    uint8_t branch = strtoul(s[4], NULL, 0);
    uint8_t invert = strtoul(s[5], NULL, 0);
    uint8_t inStream = strtoul(s[6], NULL, 0);
    uint8_t inChannel = strtoul(s[7], NULL, 0);
    float gain = strtof(s[8], NULL);
    if(!strcmp(s[1], "set"))
    {
      HW_API::initFPGABuildID();
      HW_API::initAMixer(index, HW_API::INTEGER_BITS, HW_API::FLOAT_BITS);
      int ret = HW_API::setAMixerCommandInput(index, channel, branch, invert, inStream, inChannel, gain);
      if (ret == -1)
      {
        printf("Channel value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -2)
      {
        printf("Branch value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -3)
      {
        printf("Input stream value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -4)
      {
        printf("Input channel value out of bounds!\n");
        pvalid = true;
      }
      else if(ret == -5)
      {
        printf("Gain value out of bounds!\n");
        pvalid = true;
      }
      else
      {
        printf("Set with index: %u, channel: %u, branch: %u, invert: %u, inStream: %u, inChannel: %u, gain: %f\n", index, channel, branch, invert, inStream, inChannel, gain);
        pvalid = true;
      }
    }
  } else if (n == 3)
  {
    if (!strcmp(s[1], "dump")){
      uint8_t index = strtoul(s[2], NULL, 0);
      uint8_t channel = HW_API::OUTPUT_CHAN_ID; // constant value for channel that matches hardware
      uint8_t branch = HW_API::MIXER_BRANCH; // constant value for branch that matches hardware
      bool invert;
      uint8_t inStream;
      uint8_t inChannel;
      float gain;
      HW_API::initFPGABuildID();
      HW_API::initAMixer(index, HW_API::INTEGER_BITS, HW_API::FLOAT_BITS);
      printf("Audio Mixer Index: %u\n", index);
      for(int i=0; i<channel; i++){ // iterating on output channel id
        for(int j=0; j<branch; j++){ // iterating on mixer branch
          HW_API::getAMixerCommandInput(index, i, j, &invert, &inStream, &inChannel, &gain);
          printf("channel: %u, branch: %2u, invert = %d, inStream = %d, inChannel = %2d, gain = %9.6f\n", i, j, invert, inStream, inChannel, gain);
          pvalid = true;
        }
      }
    }
  }
  if(!pvalid)
  {
    printf("Invalid\n");
  }
  return 0;
}

static int
execOSD(int n, char *s[])
{
  HW_API::initFPGABuildID();
  bool pvalid = false;
  if(n == 1){
    printf("USAGE:  %s settings <path> <EnableOSD>\n", s[0]);
    printf("                    <CharWinHStart> <CharWinVStart> <CharWinHLength> <CharWinVLines>\n");
    printf("                    <FontHLength> <FontVLines> <FontVStart> <FontHScale> <FontVScale>\n");
    printf("                    <FontAlpha> <BgAlpha> <bw_in> <colour_inp> <bw_out> <colour_out>\n");
    printf("        %s setting  <path> <use_b> <EnableOSD>\n", s[0]);
    printf("                    <CharWinHStart> <CharWinVStart> <CharWinHLength> <CharWinVLines>\n");
    printf("                    <FontHLength> <FontVLines> <FontVStart> <FontHScale> <FontVScale>\n");
    printf("                    <bw_in> <colour_inp> <bw_out> <colour_out> [FontAlpha] [BgAlpha]\n");
    printf("        %s char_colour <path> <idx> <addr_max> <char_ptr> [colour]\n", s[0]);
    printf("        %s char_colours <path> <idx> <addr_max> <char_ptr> <colour_ptr>\n", s[0]);
    printf("        %s font <path> <idx> <addr_max> <char_max>\n", s[0]);
    printf("\n");
    printf("  where path           = video path index\n");
    printf("        use_b          = index within scaler\n");
    printf("        idx            = scaler index\n");
    printf("        EnableOSD      = 0 = disabled, 1 = enabled\n");
    printf("        CharWinHStart  = starting H location of character window\n");
    printf("        CharWinVStart  = starting V location of character window\n");
    printf("        CharWinHLength = number of characters per line\n");
    printf("        CharWinVLines  = number of character lines\n");
    printf("        FontHLength    = number of H pixels per character in current font set\n");
    printf("        FontVLines     = number of V pixels per character in current font set\n");
    printf("        FontVStart     = number of lines into the font to start\n");
    printf("        FontHScale     = font scale H value from 0 to 7, where 0 = no scale factor\n");
    printf("        FontVScale     = font scale V value from 0 to 7, where 0 = no scale factor\n");
    printf("        FontAlpha      = alpha value for font, where FontAlpha has no intensity at 0\n");
    printf("        BgAlpha        = alpha value for background, where BgAlpha has no intensity at 0\n");
    printf("        addr_max       = max address of characters\n");
    printf("        char_ptr       = characters to be displayed\n");
    printf("        colour         = colour value from 0 to 7\n");
    printf("        colour_ptr     = colour value from 0 to 7 per character\n");
    printf("        char_max       = max number of characters in current font set\n");
    printf("        bw_in          = 0 = 1080p60, 1 = 1080i60, 2 = 2160p30, 3 = 2160p60\n");
    printf("        bw_out         = 0 = 1080p60, 1 = 1080i60, 2 = 2160p30, 3 = 2160p60\n");
    printf("        colour_inp     = 0 = RGB, 1 = YCC444, 2 = YCC422\n");
    printf("        colour_out     = 0 = RGB, 1 = YCC444, 2 = YCC422\n");
    printf("\n");
    printf("  NOTE: FONT TABLE ONLY SUPPORTS 64 PRINTABLE CHARACTERS WHICH RANGE FROM 32 TO 95 IN ASCII TABLE.\n");
    pvalid = true;
  } else if (n == 6)
  {
    if(!strcmp(s[1], "char_colour")){
      uint32_t path = strtoul(s[2], NULL, 0);
      uint32_t idx = strtoul(s[3], NULL, 0);
      uint32_t addr_max = strtoul(s[4], NULL, 0);
      char *char_ptr = s[5];
      // allocate an array that can hold 256 elements
      char char_array[256];
      // set the bytes of char_array starting at address of char_array to the value of 0
      memset(char_array, 0 , sizeof(char_array));
      // Check if user input exceeds the allocated char_array limit
      if(strlen(char_ptr) > 256)
      {
        printf("ERROR: INPUT EXCEEDS CHARACTER LIMIT! INPUT WILL BE TRUNCATED TO CHARACTER LIMIT!\n");
      }
      for(uint32_t i = 0; ((i<strlen(char_ptr)) & (i<256)); i++){
        char_array[i] = static_cast<char>(char_ptr[i] - 32);
      }
      HW_API::initScalerPath(path);
      HW_API::setCharTable(path, idx, addr_max, char_array);
      printf("SET Default Characters Colour: path = %u, idx = %u, addr_max = %u, char = %s, colour = WHITE.\n", path, idx, addr_max, char_ptr);
      pvalid = true;
    }
    else if(!strcmp(s[1], "font")){
      uint32_t path = strtoul(s[2], NULL, 0);
      uint32_t idx = strtoul(s[3], NULL, 0);
      uint32_t addr_max = strtoul(s[4], NULL, 0);
      uint32_t char_max = strtoul(s[5], NULL, 0);
      uint32_t *data = (uint32_t*)font13x13::font13x13_basic[0];
      HW_API::initScalerPath(path);
      HW_API::setFontTable(path, idx, addr_max, char_max, data);
      printf("SET Font Table: path = %u, idx = %u, addr_max= %u , char_max = %u.\n", path, idx, addr_max, char_max);
      pvalid = true;
    }
  } else if (n == 7)
  {
    if(!strcmp(s[1], "char_colour")){
      uint32_t path = strtoul(s[2], NULL, 0);
      uint32_t idx = strtoul(s[3], NULL, 0);
      uint32_t addr_max = strtoul(s[4], NULL, 0);
      char *char_ptr = s[5];
      // allocate an array that can hold 256 elements
      char char_array[256];
      // set the bytes of char_array starting at address of char_array to the value of 0
      memset(char_array, 0 , sizeof(char_array));
      // Check if user input exceeds the allocated char_array limit
      if(strlen(char_ptr) > 256)
      {
        printf("ERROR: INPUT EXCEEDS CHARACTER LIMIT! INPUT WILL BE TRUNCATED TO CHARACTER LIMIT!\n");
      }
      for(uint32_t i = 0; ((i<strlen(char_ptr)) & (i<256)); i++){
        char_array[i] = static_cast<char>(char_ptr[i] - 32);
      }
      char colour = static_cast<char>(strtoul(s[6], NULL, 0));
      HW_API::initScalerPath(path);
      HW_API::setCharTable(path, idx, addr_max, char_array, colour);
      printf("SET Characters Colour: path = %u, idx = %u, addr_max = %u, char = %s, colour = %d.\n", path, idx, addr_max, char_ptr, colour);
      pvalid = true;
    }
    else if(!strcmp(s[1], "char_colours")){
      uint32_t path = strtoul(s[2], NULL, 0);
      uint32_t idx = strtoul(s[3], NULL, 0);
      uint32_t addr_max = strtoul(s[4], NULL, 0);
      char *char_ptr = s[5];
      char *colour_ptr = s[6];
      // allocate an array that can hold 256 elements
      char char_array[256];
      // set the bytes of char_array starting at address of char_array to the value of 0
      memset(char_array, 0 , sizeof(char_array));
      // Check if user input exceeds the allocated char_array limit
      if(strlen(char_ptr) > 256)
      {
        printf("ERROR: INPUT EXCEEDS CHARACTER LIMIT! INPUT WILL BE TRUNCATED TO CHARACTER LIMIT!\n");
      }
      for(uint32_t i = 0; ((i<strlen(char_ptr)) & (i<256)); i++){
        char_array[i] = static_cast<char>(char_ptr[i] - 32);
      }
      HW_API::initScalerPath(path);
      HW_API::setCharTable(path, idx, addr_max, char_array, colour_ptr);
      printf("SET Charaters Colours: path = %u, idx = %u, addr_max = %u, char = %s, colours = %s.\n", path, idx, addr_max, char_ptr, colour_ptr);
      pvalid = true;
    }
  } else if (n == 18){
    if(!strcmp(s[1], "setting")){
      uint32_t path = strtoul(s[2], NULL, 0);
      uint32_t use_b = strtoul(s[3], NULL, 0);
      uint32_t OSDEnable = strtoul(s[4], NULL, 0);
      uint32_t CharWinHStart = strtoul(s[5], NULL, 0);
      uint32_t CharWinVStart = strtoul(s[6], NULL, 0);
      uint32_t CharWinHLength = strtoul(s[7], NULL, 0) -1;
      uint32_t CharWinVLines = strtoul(s[8], NULL, 0) -1;
      uint32_t FontHLength = strtoul(s[9], NULL, 0) -1;
      uint32_t FontVLines = strtoul(s[10], NULL, 0) -1;
      uint32_t FontVStart = strtoul(s[11], NULL, 0) -1;
      uint32_t FontHScale = strtoul(s[12], NULL, 0);
      uint32_t FontVScale = strtoul(s[13], NULL, 0);
      uint32_t bw_in  = strtoul(s[14], NULL, 0)%HW_API::NUM_BIST_BW;
      uint32_t colour_inp = strtoul(s[15], NULL, 0);
      uint32_t bw_out = strtoul(s[16], NULL, 0)%HW_API::NUM_BIST_BW;
      uint32_t colour_out = strtoul(s[17], NULL, 0);
      HW_API::initScalerPath(path);
      HW_API::bistScaler(path, (HW_API::bwBIST)bw_in, (HW_API::scColourFormat_type)colour_inp, (HW_API::bwBIST)bw_out, (HW_API::scColourFormat_type)colour_out);
      HW_API::setScalerOSDSettings(path, use_b, OSDEnable,
                                   CharWinHStart, CharWinVStart, CharWinHLength, CharWinVLines,
                                   FontHLength, FontVLines, FontVStart, FontHScale, FontVScale);
      HW_API::dumpScalerOSDSettings(path);
      pvalid = true;
    }
  } else if (n == 19)
  {
    if(!strcmp(s[1], "settings")){
      uint32_t path = strtoul(s[2], NULL, 0);
      MVScalerTopType::OSDSettings osdsettings;
      osdsettings.osd_enable = strtoul(s[3], NULL, 0);
      osdsettings.char_win_h_start = strtoul(s[4], NULL, 0);
      osdsettings.char_win_v_start = strtoul(s[5], NULL, 0);
      // User supplies 1-based values, ex: char_win_h_length = 4, while hardware expects 0-based values.
      // As a result, char_win_h_length = 4 would need to be passed in as char_win_h_length = 3.
      osdsettings.char_win_h_length = strtoul(s[6], NULL, 0) -1;
      osdsettings.char_win_v_lines = strtoul(s[7], NULL, 0) -1;
      osdsettings.font_h_length = strtoul(s[8], NULL, 0) -1;
      osdsettings.font_v_lines = strtoul(s[9], NULL, 0) -1;
      osdsettings.font_v_start = strtoul(s[10], NULL, 0) -1;
      osdsettings.font_h_scale = strtoul(s[11], NULL, 0);
      osdsettings.font_v_scale = strtoul(s[12], NULL, 0);
      osdsettings.font_alpha = strtoul(s[13], NULL, 0);
      osdsettings.bg_alpha = strtoul(s[14], NULL, 0);
      uint32_t bw_in  = strtoul(s[15], NULL, 0)%HW_API::NUM_BIST_BW;
      uint8_t colour_inp  = strtoul(s[16], NULL, 0);
      uint32_t bw_out = strtoul(s[17], NULL, 0)%HW_API::NUM_BIST_BW;
      uint8_t colour_out  = strtoul(s[18], NULL, 0);
      HW_API::initScalerPath(path);
      HW_API::bistScaler(path, (HW_API::bwBIST)bw_in, (HW_API::scColourFormat_type)colour_inp, (HW_API::bwBIST)bw_out, (HW_API::scColourFormat_type)colour_out);
      int ret = HW_API::setScalerOSDSettings(path, &osdsettings);
      if (ret == -1)
      {
        printf("FontAlpha and BgAlpha are out of bounds!\n");
        pvalid = true;
      }
      else if ( ret == -2)
      {
        printf("FontAlpha is out of bounds!\n");
        pvalid = true;
      }
      else if ( ret == -3)
      {
        printf("BgAlpha is out of bounds!\n");
        pvalid = true;
      }
      else
      {
        HW_API::dumpScalerOSDSettings(path);
        pvalid = true;
      }
    }
  } else if (n == 20)
  {
    if(!strcmp(s[1], "setting")){
      uint32_t path = strtoul(s[2], NULL, 0);
      uint32_t use_b = strtoul(s[3], NULL, 0);
      uint32_t OSDEnable = strtoul(s[4], NULL, 0);
      uint32_t CharWinHStart = strtoul(s[5], NULL, 0);
      uint32_t CharWinVStart = strtoul(s[6], NULL, 0);
      uint32_t CharWinHLength = strtoul(s[7], NULL, 0) -1;
      uint32_t CharWinVLines = strtoul(s[8], NULL, 0) -1;
      uint32_t FontHLength = strtoul(s[9], NULL, 0) -1;
      uint32_t FontVLines = strtoul(s[10], NULL, 0) -1;
      uint32_t FontVStart = strtoul(s[11], NULL, 0) -1;
      uint32_t FontHScale = strtoul(s[12], NULL, 0);
      uint32_t FontVScale = strtoul(s[13], NULL, 0);
      uint32_t bw_in  = strtoul(s[14], NULL, 0)%HW_API::NUM_BIST_BW;
      uint32_t colour_inp = strtoul(s[15], NULL, 0);
      uint32_t bw_out = strtoul(s[16], NULL, 0)%HW_API::NUM_BIST_BW;
      uint32_t colour_out = strtoul(s[17], NULL, 0);
      uint32_t FontAlpha  = strtoul(s[18], NULL, 0);
      uint32_t BgAlpha    = strtoul(s[19], NULL, 0);
      HW_API::initScalerPath(path);
      HW_API::bistScaler(path, (HW_API::bwBIST)bw_in, (HW_API::scColourFormat_type)colour_inp, (HW_API::bwBIST)bw_out, (HW_API::scColourFormat_type)colour_out);
      HW_API::setScalerOSDSettings(path, use_b, OSDEnable,
                                   CharWinHStart, CharWinVStart, CharWinHLength, CharWinVLines, FontHLength,
                                   FontVLines, FontVStart, FontHScale, FontVScale,
                                   FontAlpha, BgAlpha);
      HW_API::dumpScalerOSDSettings(path);
      pvalid = true;
    }
  }
  if(!pvalid)
  {
    printf("Invalid\n");
  }
  return 0;
}

static int
execIcron(int n, char *s[])
{
    bool pvalid = false;
    if (n == 1) {
        printf("Usage: %s gtxstatus\n", s[0]);
        printf("       %s link\n", s[0]);
        printf("       %s host\n", s[0]);
        printf("       %s vbus_en\n", s[0]);
        printf("       %s activity\n", s[0]);
        printf("       %s gmii\n", s[0]);
        printf("       %s status\n", s[0]);
        printf("       %s state\n", s[0]);
        printf("       %s control\n", s[0]);
        printf("       %s progb <0/1>    (1=set)\n", s[0]);
        printf("       %s bootsel0 <0/1> (1=set)\n", s[0]);
        printf("       %s usbmode <0/1>  (0=low/full/high, 1=low/full)\n", s[0]);
        printf("       %s phyl2en <0/1>  (0=network, 1=direct)\n", s[0]);
        printf("       %s pairn <0/1>    (1=pair)\n", s[0]);
        printf("       %s resetn <0/1>   (1=reset)\n", s[0]);
        printf("       %s rexlex <0/1>   (1=rex, 0=lex)\n", s[0]);
        printf("       %s offset [offset]\n", s[0]);
        printf("       %s lockmode [enable]\n", s[0]);
        printf("       %s rxlocked\n", s[0]);
        printf("       %s rxfifo\n", s[0]);
        printf("       %s txfifo\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        HW_API::initFPGABuildID();
        HW_API::initIcronUSB();
        if (!strcmp(s[1], "gtxstatus")) {
            uint32_t status = 0;
            HW_API::initIcronUSB();
            HW_API::getIcronUSBGTXStatus(&status);
            printf("GTX Status: 0x%x\n", status);
            pvalid = true;
        } else if (!strcmp(s[1], "link")) {
            IcronUSB::linkState state;
            if (HW_API::getIcronUSBLinkState(&state) == 0) {
              printf("Icron Link:     ");
              if (state == IcronUSB::LINK_DISCONNECTED) {
                printf("DISCONNECTED.\n");
              } else if (state == IcronUSB::LINK_CONNECTED) {
                printf("CONNECTED.\n");
              } else if (state == IcronUSB::LINK_SEARCHING) {
                printf("SEARCHING.\n");
              } else if (state == IcronUSB::LINK_PAIRING) {
                printf("PAIRING.\n");
              }
            }
            pvalid = true;
        } else if (!strcmp(s[1], "host")) {
            bool state;
            if (HW_API::getIcronUSBHostState(&state) == 0) {
              printf("Icron Host:     %s.\n", state ? "CONNECTED" : "DISCONNECTED");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "vbus_en")) {
            bool state;
            if (HW_API::getIcronUSBVbusEnState(&state) == 0) {
              printf("Icron Vbus:     %s.\n", state ? "ENABLED" : "DISABLED");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "activity")) {
            bool state;
            if (HW_API::getIcronUSBActivityState(&state) == 0) {
              printf("Icron Activity: %s.\n", state ? "ACTIVE" : "INACTIVE");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "gmii")) {
            bool state_rx, state_tx;
            if (HW_API::getIcronUSBGMIIState(&state_rx, &state_tx) == 0) {
              printf("Icron GMII_RX:  %s.\n", state_rx ? "ACTIVE" : "INACTIVE");
              printf("Icron GMII_TX:  %s.\n", state_tx ? "ACTIVE" : "INACTIVE");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "status")) {
            HW_API::dumpIcronUSBStatus();
            pvalid = true;
        } else if (!strcmp(s[1], "state")) {
            HW_API::dumpIcronUSBStatusState();
            pvalid = true;
        } else if (!strcmp(s[1], "control")) {
            HW_API::dumpIcronUSBControl();
            pvalid = true;
        } else if (!strcmp(s[1], "offset")) {
            uint32_t rxoffset;
            uint32_t offset;
            bool locked;
            HW_API::getIcronRxOffset(&rxoffset);
            HW_API::getIcronOffset(&offset);
            HW_API::getIcronRxLocked(&locked);
            printf("Rx offset:      %d\n", rxoffset);
            printf("Offset:         %u\n", offset);
            printf("PCR locked:     %u\n", locked);
            pvalid = true;
        } else if (!strcmp(s[1], "lockmode")) {
            bool enable;
            HW_API::getIcronLockedMode(&enable);
            printf("Locked mode enable: %u\n", enable);
            pvalid = true;
        } else if (!strcmp(s[1], "rxlocked")) {
            bool locked;
            HW_API::getIcronRxLocked(&locked);
            printf("Rx PCR locked: %u\n", locked);
            pvalid = true;
        } else if (!strcmp(s[1], "rxfifo")) {
            uint32_t status;
            HW_API::getIcronRxFifoStatus(&status);
            printf("Rx FIFO Status: %u\n", status);
            pvalid = true;
        } else if (!strcmp(s[1], "txfifo")) {
            uint32_t status;
            HW_API::getIcronTxFifoStatus(&status);
            printf("Tx FIFO Status: %u\n", status);
            pvalid = true;
        }
    } else if (n == 3) {
        HW_API::initFPGABuildID();
        HW_API::initIcronUSB();
        if (!strcmp(s[1], "progb")) {
            bool value = strtoul(s[2], NULL, 0);
            if (HW_API::setIcronUSBProgB(value) == 0) {
              printf("Set Icron PROG_B to %u.\n", value);
            } else {
              printf("Failed to set Icron PROG_B to %u!\n", value);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "bootsel0")) {
            bool value = strtoul(s[2], NULL, 0);
            if (HW_API::setIcronUSBBootSel0(value) == 0) {
              printf("Set Icron BOOT_SEL0 to %u.\n", value);
            } else {
              printf("Failed to set Icron BOOT_SEL0 to %u!\n", value);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "usbmode")) {
            bool value = strtoul(s[2], NULL, 0);
            if (HW_API::setIcronUSBMode(value) == 0) {
              printf("Set Icron USBMODE to %u.\n", value);
            } else {
              printf("Failed to set Icron USBMODE to %u!\n", value);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "phyl2en")) {
            bool value = strtoul(s[2], NULL, 0);
            if (HW_API::setIcronUSBPhyL2En(value) == 0) {
              printf("Set Icron PHYL2EN to %u.\n", value);
            } else {
              printf("Failed to set Icron PHYL2EN to %u!\n", value);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "pairn")) {
            bool value = strtoul(s[2], NULL, 0);
            if (HW_API::setIcronUSBPairN(value) == 0) {
              printf("Set Icron PAIRn to %u.\n", value);
            } else {
              printf("Failed to set Icron PAIRn to %u!\n", value);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "resetn")) {
            bool value = strtoul(s[2], NULL, 0);
            if (HW_API::setIcronUSBResetN(value) == 0) {
              printf("Set Icron RESETn to %u.\n", value);
            } else {
              printf("Failed to set Icron RESETn to %u!\n", value);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rexlex")) {
            bool value = strtoul(s[2], NULL, 0);
            if (HW_API::setIcronUSBRexLexMode(value) == 0) {
              printf("Set Icron Rex Not Lex to %u.\n", value);
            } else {
              printf("Failed to set Icron Rex Not Lex to %u!\n", value);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "offset")) {
            uint32_t rxoffset;
            uint32_t offset = strtoul(s[2], NULL, 0);
            bool locked;
            HW_API::getIcronRxOffset(&rxoffset);
            HW_API::setIcronOffset(offset);
            HW_API::getIcronRxLocked(&locked);
            printf("Rx offset:      %d\n", rxoffset);
            printf("Offset:         %u\n", offset);
            printf("PCR locked:     %u\n", locked);
            pvalid = true;
        } else if (!strcmp(s[1], "lockmode")) {
            bool enable = strtoul(s[2], NULL, 0);
            HW_API::setIcronLockedMode(enable);
            printf("Locked mode enable: %u\n", enable);
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execGen(int n, char *s[])
{
  bool pvalid = false;
  if (n == 1) {
    printf("Usage:\n");
    printf("FPGA Index:\n");
    printf("       %s index [idx]\n", s[0]);
    printf("FPGA Reset:\n");
    printf("       %s reset\n", s[0]);
    printf("Clock Measures:\n");
    printf("       %s clocks\n", s[0]);
    printf("HDMI:\n");
    printf("       %s mbpause [pause]\n", s[0]);
    printf("       %s mbreset [reset]\n", s[0]);
    printf("       %s rxhpd  <idx>\n", s[0]);
    printf("       %s txhpd  <idx>\n", s[0]);
    printf("       %s cabledetect <idx>\n", s[0]);
    printf("       %s cabledetectmux <idx>\n", s[0]);
    printf("       %s mux <idx> [sel]\n", s[0]);
    printf("       %s disable <idx> [disable]\n", s[0]);
    printf("       %s disable5v <idx> [disable]\n", s[0]);
    printf("       %s bridgereset <idx> [reset]\n", s[0]);
    printf("USB:\n");
    printf("       %s usbreset [rst]\n", s[0]);
    printf("       %s usbtxsrc [src]\n", s[0]);
    printf("ICRON MDIO:\n");
    printf("       %s mdio <phy_addr> <reg_addr> [command]\n", s[0]);
    printf("Audio:\n");
    printf("       %s analog [mute]\n", s[0]);
    printf("       %s spdif <idx> [mute]\n", s[0]);
    printf("I2C Expander:\n");
    printf("       %s i2c [reset]\n", s[0]);
    printf("Board Level Components:\n");
    printf("       %s pb\n", s[0]);
    printf("       %s ledrgb [red] [green] [blue]\n", s[0]);
    printf("       %s toggle\n", s[0]);
    printf("       %s fanfail\n", s[0]);
    printf("       %s spidisplay [data]\n", s[0]);
    printf("Power Supply:\n");
    printf("       %s 12vmon <idx> [monitor]\n", s[0]);
    printf("       %s orfault <idx> [orfault]\n", s[0]);
    printf("       %s fault [fault]\n", s[0]);
    printf("Board Configuration:\n");
    printf("       %s trm [select]\n", s[0]);
    printf("       %s xgepolarity <rx/tx> [index] [invert]\n", s[0]);
    printf("XO Programming:\n");
    printf("       %s dcxo <index>\n", s[0]);
    printf("       %s dcxo setDone <index> <done>\n", s[0]);
    printf("       %s dcxo setClock <index> <frequencyHz> [accept-best-stable-freq]\n", s[0]);
    printf("       %s dcxo setLock <index> <lock>\n", s[0]);
    pvalid = true;
  } else if (n == 2) {
    HW_API::initFPGABuildID();
    if (!strcmp(s[1], "index")) {
      bool index;
      HW_API::initGeneral();
      HW_API::getGeneralFPGAIndex(&index);
      printf("FPGA Index: %u.\n", index);
      pvalid = true;
    } else if (!strcmp(s[1], "reset")) {
      HW_API::initGeneral();
      HW_API::setGeneralFPGAReset(true);
      pvalid = true;
    } else if (!strcmp(s[1], "clocks")) {
      uint32_t clkfreq;
      HW_API::initGeneral();
      HW_API::getGeneralXGEClkFrequency(&clkfreq);
      printf("CLK_XGE           = %u Hz.\n", clkfreq);
      HW_API::getGeneral62m5hzClkFrequency(&clkfreq);
      printf("CLK_62M5Hz        = %u Hz.\n", clkfreq);
      HW_API::getGeneral125mhzClkFrequency(&clkfreq);
      printf("CLK_125MHz        = %u Hz.\n", clkfreq);
      HW_API::getGeneral156m25hzClkFrequency(&clkfreq);
      printf("CLK_156.25MHz     = %u Hz.\n", clkfreq);
      HW_API::getGeneral312m5hzClkFrequency(&clkfreq);
      printf("CLK_312.5MHz      = %u Hz.\n", clkfreq);
      HW_API::getGeneralHdmiSouthTxClkFrequency(&clkfreq);
      printf("CLK_HDMI_SOUTH_TX = %u Hz.\n", clkfreq);
      HW_API::getGeneralHdmiNorthTxClkFrequency(&clkfreq);
      printf("CLK_HDMI_NORTH_TX = %u Hz.\n", clkfreq);
      HW_API::getGeneralInterFPGAClkFrequency(&clkfreq);
      printf("CLK_INTERFPGA     = %u Hz.\n", clkfreq);
      HW_API::getGeneralDRUClkFrequency(&clkfreq);
      printf("CLK_DRU           = %u Hz.\n", clkfreq);
      HW_API::getGeneralReflockClkFrequency(&clkfreq);
      printf("CLK_REFLOCK       = %u Hz.\n", clkfreq);
      HW_API::getGeneralMgt110Refclk1ClkFrequency(&clkfreq);
      printf("CLK_MGT110_REFCLK1= %u Hz.\n", clkfreq);
      HW_API::getGeneralMgt112Refclk1ClkFrequency(&clkfreq);
      printf("CLK_MGT112_REFCLK1= %u Hz.\n", clkfreq);
      pvalid = true;
    } else if (!strcmp(s[1], "mbpause")) {
      bool pause;
      HW_API::initGeneral();
      HW_API::getGeneralHdmiPause(&pause);
      printf("HDMI MicroBlaze Pause: %u.\n", pause);
      pvalid = true;
    } else if (!strcmp(s[1], "mbreset")) {
      bool reset;
      HW_API::initGeneral();
      HW_API::getGeneralHdmiReset(&reset);
      printf("HDMI MicroBlaze Reset: %u.\n", reset);
      pvalid = true;
    } else if (!strcmp(s[1], "usbreset")) {
      bool reset;
      HW_API::initGeneral();
      HW_API::getGeneralUsbReset(&reset);
      printf("USB Reset: %u.\n", reset);
      pvalid = true;
    } else if (!strcmp(s[1], "usbtxsrc")) {
      bool src;
      HW_API::initGeneral();
      HW_API::getGeneralUSBTxSrcSel(&src);
      printf("USB TX Source Selection: %u.\n", src);
      pvalid = true;
    } else if (!strcmp(s[1], "analog")) {
      bool mute;
      HW_API::initGeneral();
      HW_API::getGeneralAnalogMute(&mute);
      printf("Analog Audio Mute: %u.\n", mute);
      pvalid = true;
    } else if (!strcmp(s[1], "i2c")) {
      bool reset;
      HW_API::initGeneral();
      HW_API::getGeneralI2CExpanderReset(&reset);
      printf("I2C Expander Reset: %u.\n", reset);
      pvalid = true;
    } else if (!strcmp(s[1], "pb")) {
      bool pb;
      HW_API::initGeneral();
      HW_API::getGeneralI2CExpanderReset(&pb);
      printf("Push button state: %u.\n", pb);
      pvalid = true;
    } else if (!strcmp(s[1], "ledrgb")) {
      uint8_t red;
      uint8_t green;
      uint8_t blue;
      HW_API::initGeneral();
      HW_API::getGeneralLedRgb(&red, &green, &blue);
      printf("LED values: red = %u, green = %u, blue = %u.\n", red, green, blue);
      pvalid = true;
    } else if (!strcmp(s[1], "trm")) {
      bool select;
      HW_API::initGeneral();
      HW_API::getGeneralTRMSelect(&select);
      printf("TRM Select: %u.\n", select);
      pvalid = true;
    } else if (!strcmp(s[1], "spidisplay")) {
      uint8_t data;
      HW_API::initGeneral();
      HW_API::getGeneralSpiDisplay(&data);
      printf("SPI Display: %u.\n", data);
      pvalid = true;
    } else if (!strcmp(s[1], "toggle")) {
      bool toggleA;
      bool toggleB;
      HW_API::initGeneral();
      HW_API::getGeneralToggleSwitch(true,  &toggleA);
      HW_API::getGeneralToggleSwitch(false, &toggleB);
      printf("Toggle Switch: %u/%u.\n", toggleA, toggleB);
      pvalid = true;
    } else if (!strcmp(s[1], "fault")) {
      bool fault;
      HW_API::initGeneral();
      HW_API::getGeneralLocalFault(&fault);
      printf("Local Fault: %u.\n", fault);
      pvalid = true;
    } else if (!strcmp(s[1], "fanfail")) {
      bool fail;
      HW_API::initGeneral();
      HW_API::getGeneralFanFail(&fail);
      printf("I2C Fan Fail: %u.\n", fail);
      pvalid = true;
    }
  } else if (n == 3) {
    if (!strcmp(s[1], "index")) {
      bool index = strtoul(s[2], NULL, 0);
      HW_API::initGeneral();
      int ret = HW_API::setGeneralFPGAIndex(index);
      if (ret >= 0) {
        printf("Set FPGA Index: %u.\n", index);
      } else {
        printf("Failed to set FPGA Index! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "mbpause")) {
      bool pause = strtoul(s[2], NULL, 0);
      HW_API::initGeneral();
      int ret = HW_API::setGeneralHdmiPause(pause);
      if (ret >= 0) {
        printf("Set HDMI MicroBlaze Pause: %u.\n", pause);
      } else {
        printf("Failed to set HDMI MicroBlaze Pause! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "mbreset")) {
      bool reset = strtoul(s[2], NULL, 0);
      HW_API::initGeneral();
      int ret = HW_API::setGeneralHdmiReset(reset);
      if (ret >= 0) {
        printf("Set HDMI MicroBlaze Reset: %u.\n", reset);
      } else {
        printf("Failed to set HDMI MicroBlaze Reset! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "rxhpd")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool hpd;
      HW_API::initGeneral();
      int ret = HW_API::getGeneralHdmiInHPD(idx, &hpd);
      if (ret >= 0) {
        printf("HDMI Rx HPD index: %u, hpd: %u.\n", idx, hpd);
      } else {
        printf("HDMI Rx HPD index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "txhpd")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool hpd;
      HW_API::initGeneral();
      int ret = HW_API::getGeneralHdmiOutHPD(idx, &hpd);
      if (ret >= 0) {
        printf("HDMI Tx HPD index: %u, hpd = %u.\n", idx, hpd);
      } else {
        printf("HDMI Tx HPD index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "cabledetect")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool detect;
      HW_API::initGeneral();
      int ret = HW_API::getGeneralHdmiInCableDetect(idx, &detect);
      if (ret >= 0) {
        printf("HDMI Source Detect index: %u, detect = %u.\n", idx, detect);
      } else {
        printf("HDMI source detect index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "cabledetectmux")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool detect;
      HW_API::initGeneral();
      int ret = HW_API::getGeneralHdmiInCableDetectMux(idx, &detect);
      if (ret >= 0) {
        printf("HDMI Source Detect index: %u, detect = %u.\n", idx, detect);
      } else {
        printf("HDMI source detect index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "mux")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool select;
      HW_API::initGeneral();
      int ret = HW_API::getGeneralHdmiMuxSelect(idx, &select);
      if (ret >= 0) {
        printf("HDMI Mux Selection index: %u, select = %u.\n", idx, select);
      } else {
        printf("HDMI mux index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "disable")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool disable;
      HW_API::initGeneral();
      int ret = HW_API::getGeneralHdmiOutDisable(idx, &disable);
      if (ret >= 0) {
        printf("HDMI Disable index: %u, disable = %u.\n", idx, disable);
      } else {
        printf("HDMI index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "disable5v")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool disable;
      HW_API::initGeneral();
      int ret = HW_API::getGeneralHdmiOut5VDisable(idx, &disable);
      if (ret >= 0) {
        printf("HDMI 5V Disable index: %u, disable = %u.\n", idx, disable);
      } else {
        printf("HDMI index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "bridgereset")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool reset;
      HW_API::initGeneral();
      int ret = HW_API::getGeneralHdmiBridgeReset(idx, &reset);
      if (ret >= 0) {
        printf("HDMI Bridge Reset index: %u, reset = %u.\n", idx, reset);
      } else {
        printf("HDMI bridge reset index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "reset")) {
      bool reset = strtoul(s[2], NULL, 0);
      HW_API::initGeneral();
      HW_API::setGeneralUsbReset(reset);
      printf("Set USB HUB Reset = %u.\n", reset);
      pvalid = true;
    } else if (!strcmp(s[1], "usbtxsrc")) {
      bool src = strtoul(s[2], NULL, 0);
      HW_API::initGeneral();
      HW_API::setGeneralUSBTxSrcSel(src);
      printf("Set USB TX Source Selection: %u.\n", src);
      pvalid = true;
    } else if (!strcmp(s[1], "analog")) {
      bool mute = strtoul(s[2], NULL, 0);
      HW_API::initGeneral();
      HW_API::setGeneralAnalogMute(mute);
      printf("Set Analog Audio Mute: %u.\n", mute);
      pvalid = true;
    } else if (!strcmp(s[1], "spdif")) {
      uint8_t index = strtoul(s[2], NULL, 0);
      bool mute;
      HW_API::initGeneral();
      HW_API::getGeneralSPDIFMute(index, &mute);
      printf("SPDIF Audio %u Mute: %u.\n", index, mute);
      pvalid = true;
    } else if (!strcmp(s[1], "i2c")) {
      bool reset = strtoul(s[2], NULL, 0);
      HW_API::initGeneral();
      HW_API::setGeneralI2CExpanderReset(reset);
      printf("Set I2C Expander Reset: %u.\n", reset);
      pvalid = true;
    } else if (!strcmp(s[1], "12vmon")) {
      uint8_t index = strtoul(s[2], NULL, 0);
      bool monitor;
      HW_API::initGeneral();
      int ret = HW_API::getGeneralSupply12vMonitor(index, &monitor);
      if (ret >= 0 ){
        printf("Power supply %u 12V monitor: %u.\n", index, monitor);
      } else {
        printf("Power supply index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "orfault")) {
      uint8_t index = strtoul(s[2], NULL, 0);
      bool orfault;
      HW_API::initGeneral();
      int ret = HW_API::getGeneralSupplyOrFault(index, &orfault);
      if (ret >= 0 ) {
        printf("Power supply %u or fault: %u.\n", index, orfault);
      } else {
        printf("Power supply index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "trm")) {
      bool select = strtoul(s[2], NULL, 0);
      HW_API::initGeneral();
      HW_API::setGeneralTRMSelect(select);
      printf("Set TRM Select: %u.\n", select);
      pvalid = true;
    } else if (!strcmp(s[1], "spidisplay")) {
      uint8_t data = strtoul(s[2], NULL, 0);
      HW_API::initGeneral();
      HW_API::setGeneralSpiDisplay(data);
      printf("Set SPI Display: %u.\n", data);
      pvalid = true;
    } else if (!strcmp(s[1], "fault")) {
      bool fault = strtoul(s[2], NULL, 0);
      HW_API::initGeneral();
      HW_API::setGeneralLocalFault(fault);
      printf("Set Local Fault: %u.\n", fault);
      pvalid = true;
    } else if (!strcmp(s[1], "xgepolarity")) {
      if (!strcmp(s[2], "rx")) {
        uint8_t index;
        bool invert;
        HW_API::initGeneral();
        index = 0;
        HW_API::getGeneralXgeRxInvertPolarity(index, &invert);
        printf("XGE Rx %u Polarity Inverted: %u.\n", index, invert);
        index = 1;
        HW_API::getGeneralXgeRxInvertPolarity(index, &invert);
        printf("XGE Rx %u Polarity Inverted: %u.\n", index, invert);
        index = 2;
        HW_API::getGeneralXgeRxInvertPolarity(index, &invert);
        printf("XGE Rx %u Polarity Inverted: %u.\n", index, invert);
        index = 3;
        HW_API::getGeneralXgeRxInvertPolarity(index, &invert);
        printf("XGE Rx %u Polarity Inverted: %u.\n", index, invert);
        pvalid = true;
      } else if (!strcmp(s[2], "tx")) {
        uint8_t index;
        bool invert;
        HW_API::initGeneral();
        index = 0;
        HW_API::getGeneralXgeTxInvertPolarity(index, &invert);
        printf("XGE Tx %u Polarity Inverted: %u.\n", index, invert);
        index = 1;
        HW_API::getGeneralXgeTxInvertPolarity(index, &invert);
        printf("XGE Tx %u Polarity Inverted: %u.\n", index, invert);
        index = 2;
        HW_API::getGeneralXgeTxInvertPolarity(index, &invert);
        printf("XGE Tx %u Polarity Inverted: %u.\n", index, invert);
        index = 3;
        HW_API::getGeneralXgeTxInvertPolarity(index, &invert);
        printf("XGE Tx %u Polarity Inverted: %u.\n", index, invert);
        pvalid = true;
      }
    } else if (!strcmp(s[1], "dcxo")) {
      uint8_t index = strtoul(s[2], NULL, 0);
      int32_t ret = 0;
      bool done;
      HW_API::initGeneral();
      ret += HW_API::getGeneralDCXODone(index, &done);
      if (ret >= 0 ) {
        printf("Getting DCXO Values for index %u:\n", index);
        printf("  Done: %u.\n",done);
      } else {
        printf("Index out of bounds!\n");
      }
      pvalid = true;
    }
  } else if (n == 4) {
    if (!strcmp(s[1], "mux")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool select = (bool)strtoul(s[3], NULL, 0);
      HW_API::initGeneral();
      int ret = HW_API::setGeneralHdmiMuxSelect(idx, select);
      if (ret >= 0) {
        printf("Set HDMI Mux Selection index: %u, select = %u.\n", idx, select);
      } else {
        printf("HDMI mux select is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "disable")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool disable = strtoul(s[3], NULL, 0);
      HW_API::initGeneral();
      int ret = HW_API::setGeneralHdmiOutDisable(idx, disable);
      if (ret >= 0) {
        printf("Set HDMI Disable with index: %u, disable = %u.\n", idx, disable);
      } else {
        printf("HDMI index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "disable5v")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool disable = strtoul(s[3], NULL, 0);
      HW_API::initGeneral();
      int ret = HW_API::setGeneralHdmiOut5VDisable(idx, disable);
      if (ret >= 0) {
        printf("Set HDMI Disable with index: %u, disable = %u.\n", idx, disable);
      } else {
        printf("HDMI index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "bridgereset")) {
      uint8_t idx = strtoul(s[2], NULL, 0);
      bool reset = (bool)strtoul(s[3], NULL, 0);
      HW_API::initGeneral();
      int ret = HW_API::setGeneralHdmiBridgeReset(idx, reset);
      if (ret >= 0) {
        printf("Set HDMI Bridge Reset index: %u, reset = %u.\n", idx, reset);
      } else {
        printf("HDMI bridge reset index is out of range! Error code: %i.\n", ret);
      }
      pvalid = true;
    } else if (!strcmp(s[1], "mdio")) {
      uint32_t phy_addr = strtoul(s[2], NULL, 0);
      uint32_t reg_addr = strtoul(s[3], NULL, 0);
      HW_API::initGeneral();
      uint32_t status;
      HW_API::getGeneralUsbPhyMdio(phy_addr, reg_addr, &status);
      printf("ICRON MDIO: phy_addr = 0x%x, reg_addr = 0x%x, status = 0x%x.\n", phy_addr, reg_addr, status);
      pvalid = true;
    } else if (!strcmp(s[1], "spdif")) {
      uint8_t index = strtoul(s[2], NULL, 0);
      bool mute = strtoul(s[3], NULL, 0);
      HW_API::initGeneral();
      HW_API::setGeneralSPDIFMute(index, mute);
      printf("Set SPDIF Audio %u Mute: %u.\n", index, mute);
      pvalid = true;
    } else if (!strcmp(s[1], "xgepolarity")) {
      if (!strcmp(s[2], "rx")) {
        uint8_t index = strtoul(s[3], NULL, 0);
        bool invert;
        HW_API::initGeneral();
        HW_API::getGeneralXgeRxInvertPolarity(index, &invert);
        printf("XGE Rx %u Polarity Inverted: %u.\n", index, invert);
        pvalid = true;
      } else if (!strcmp(s[2], "tx")) {
        uint8_t index = strtoul(s[3], NULL, 0);
        bool invert;
        HW_API::initGeneral();
        HW_API::getGeneralXgeTxInvertPolarity(index, &invert);
        printf("XGE Tx %u Polarity Inverted: %u.\n", index, invert);
        pvalid = true;
      }
    }
  } else if (n == 5) {
    if (!strcmp(s[1], "mdio")) {
      uint32_t phy_addr = strtoul(s[2], NULL, 0);
      uint32_t reg_addr = strtoul(s[3], NULL, 0);
      uint32_t command = strtoul(s[4], NULL, 0);
      HW_API::initGeneral();
      HW_API::setGeneralUsbPhyMdio(phy_addr, reg_addr, command);
      printf("ICRON MDIO: phy_addr = 0x%x, reg_addr = 0x%x, command = 0x%x.\n", phy_addr, reg_addr, command);
      pvalid = true;
    } else if (!strcmp(s[1], "ledrgb")) {
      uint8_t red = strtoul(s[2], NULL, 0);
      uint8_t green = strtoul(s[3], NULL, 0);;
      uint8_t blue = strtoul(s[4], NULL, 0);;
      HW_API::initGeneral();
      HW_API::setGeneralLedRgb(red, green, blue);
      printf("Set LED: red = %u, green = %u, blue = %u.\n", red, green, blue);
      pvalid = true;
    } else if (!strcmp(s[1], "xgepolarity")) {
      if (!strcmp(s[2], "rx")) {
        uint8_t index = strtoul(s[3], NULL, 0);
        bool invert = strtoul(s[4], NULL, 0);
        HW_API::initGeneral();
        HW_API::setGeneralXgeRxInvertPolarity(index, invert);
        printf("Set XGE Rx %u Polarity Inverted: %u.\n", index, invert);
        pvalid = true;
      } else if (!strcmp(s[2], "tx")) {
        uint8_t index = strtoul(s[3], NULL, 0);
        bool invert = strtoul(s[4], NULL, 0);
        HW_API::initGeneral();
        HW_API::setGeneralXgeTxInvertPolarity(index, invert);
        printf("Set XGE Tx %u Polarity Inverted: %u.\n", index, invert);
        pvalid = true;
      }
    } else if (!strcmp(s[1], "dcxo")) {
      HW_API::initGeneral();
      if (!strcmp(s[2], "setDone")) {
        uint8_t index = strtoul(s[3], NULL, 0);
        bool done = strtoul(s[4], NULL, 0);
        int32_t ret = 0;
        ret += HW_API::setGeneralDCXODone(index, done);
        if (ret >= 0 ) {
          printf("Setting DCXO Values for index %u:\n", index);
          printf("  Done: %u.\n",done);
        } else {
          printf("Index out of bounds!\n");
        }
        pvalid = true;
      } else if (!strcmp(s[2], "setClock")) {
        uint8_t index = strtoul(s[3], NULL, 0);
        uint32_t frequency = strtoul(s[4], NULL, 0);
        uint32_t si570DefaultFrequency = 74250000;
        int32_t ret = 0;
        ret += HW_API::initGeneralDCXO(index, si570DefaultFrequency);
        if (ret >= 0) {
          ret += HW_API::setGeneralDCXOClock(index, frequency);
          if (ret >= 0) {
            dcxo_ctrl::dcxo_select_type dcxo;
            cy29411_ctrl::cy29411_settings_type cy29411_settings;
            si570_ctrl::si570_settings_type si570_settings;
            bool valid;
            HW_API::readGeneralDCXOSelect(index, &valid, &dcxo);
            if (valid) {
              if (dcxo == dcxo_ctrl::SELECT_SI570) {
                HW_API::readGeneralDCXOSettingsSi570(index, &valid, &si570_settings);
                printf("Si570 Settings:\n");
                printf("  FXTAL:     %llu\n", si570_settings.FXTAL);
                printf("  RFREQ:     %llu\n", si570_settings.RFREQ);
                printf("  frequency: %u\n",   si570_settings.frequency);
                printf("  N1:        %u\n",   si570_settings.N1);
                printf("  HSDIV:     %u\n",   si570_settings.HSDIV);
              } else {
                HW_API::readGeneralDCXOSettingsCY29411(index, &valid, &cy29411_settings);
                printf("CY29411 Settings:\n");
                printf("  DIVO: %u\n",        cy29411_settings.DIVO);
                printf("  DIVN_INT: %u\n",    cy29411_settings.DIVN_INT);
                printf("  DIVN_FRAC: 0x%x\n", cy29411_settings.DIVN_FRAC);
                printf("  ICP_BIN: %u\n",     cy29411_settings.ICP_BIN);
                printf("  ICP_OFFSET: %u\n",  cy29411_settings.ICP_OFFSET);
                printf("  PLL_MODE: %u\n",    cy29411_settings.PLL_MODE);
              }
              if (valid) {
                printf("DCXO frequency:\n");
                printf("  Clock: %u.\n",frequency);
              } else {
                printf("An error occured!");
              }
            } else {
              printf("DCXO is not initialized!\n");
            }
          } else if (ret == -1) {
            printf("Index out of bounds!\n");
          } else if (ret == -4) {
            printf("Provided frequency is in a disallowed spur!\n");
          } else {
            printf("Failed to set DCXO to provided frequency!\n");
          }
        } else {
          printf("Index out of bounds!\n");
        }
        pvalid = true;
      }

    }
  } else if (n == 6) {
    if (!strcmp(s[1], "dcxo") && !strcmp(s[2], "setClock")) {
      HW_API::initGeneral();
      uint8_t index = strtoul(s[3], NULL, 0);
      uint32_t frequency = strtoul(s[4], NULL, 0);
      bool acceptBestStableFreq = strtoul(s[5], NULL, 0);
      uint32_t si570DefaultFrequency = 74250000;
      int32_t ret = 0;
      ret += HW_API::initGeneralDCXO(index, si570DefaultFrequency);
      if (ret >= 0) {
        ret += HW_API::setGeneralDCXOClock(index, frequency, acceptBestStableFreq);
        if (ret >= 0) {
          dcxo_ctrl::dcxo_select_type dcxo;
          cy29411_ctrl::cy29411_settings_type cy29411_settings;
          si570_ctrl::si570_settings_type si570_settings;
          bool valid;
          HW_API::readGeneralDCXOSelect(index, &valid, &dcxo);
          if (valid) {
            if (dcxo == dcxo_ctrl::SELECT_SI570) {
              HW_API::readGeneralDCXOSettingsSi570(index, &valid, &si570_settings);
              printf("Si570 Settings:\n");
              printf("  FXTAL:     %llu\n", si570_settings.FXTAL);
              printf("  RFREQ:     %llu\n", si570_settings.RFREQ);
              printf("  frequency: %u\n",   si570_settings.frequency);
              printf("  N1:        %u\n",   si570_settings.N1);
              printf("  HSDIV:     %u\n",   si570_settings.HSDIV);
            } else {
              HW_API::readGeneralDCXOSettingsCY29411(index, &valid, &cy29411_settings);
              printf("CY29411 Settings:\n");
              printf("  DIVO: %u\n",        cy29411_settings.DIVO);
              printf("  DIVN_INT: %u\n",    cy29411_settings.DIVN_INT);
              printf("  DIVN_FRAC: 0x%x\n", cy29411_settings.DIVN_FRAC);
              printf("  ICP_BIN: %u\n",     cy29411_settings.ICP_BIN);
              printf("  ICP_OFFSET: %u\n",  cy29411_settings.ICP_OFFSET);
              printf("  PLL_MODE: %u\n",    cy29411_settings.PLL_MODE);
            }
            if (valid) {
              printf("DCXO frequency:\n");
              printf("  Clock: %u.\n",frequency);
            } else {
              printf("An error occured!");
            }
          } else {
            printf("DCXO is not initialized!\n");
          }
        } else if (ret == -1) {
          printf("Index out of bounds!\n");
        } else if (ret == -4) {
          printf("Provided frequency is in a disallowed spur!\n");
        } else {
          printf("Failed to set DCXO to provided frequency!\n");
        }
      } else {
        printf("Index out of bounds!\n");
      }
      pvalid = true;
    }
  }
  if (!pvalid) {
      printf("Invalid\n");
  }
  return 0;
}

static int
execInter(int n, char *s[])
{
  bool pvalid = false;
  if (n == 1) {
    printf("Usage: %s reset <quad> <chan> <reset>\n", s[0]);
    printf("       %s linkup <quad> <chan>\n", s[0]);
    printf("       %s laneup <quad> <chan>\n", s[0]);
    printf("       %s softerr <quad> <chan>\n", s[0]);
    printf("       %s harderr <quad> <chan>\n", s[0]);
    printf("       %s ipreset <quad> <chan> <reset>\n", s[0]);
    printf("       %s iplinkup <quad> <chan>\n", s[0]);
    printf("       %s iplaneup <quad> <chan>\n", s[0]);
    printf("       %s ipsofterr <quad> <chan>\n", s[0]);
    printf("       %s ipharderr <quad> <chan>\n", s[0]);
    printf("       %s ckeofwerr <chan> [reset]\n", s[0]);
    printf("       %s audofwerr <chan> [reset]\n", s[0]);
    printf("       %s metaofwerr <chan> [reset]\n", s[0]);
    printf("       %s usbofwerr <chan> [reset]\n", s[0]);
    printf("       %s vidofwerr <chan> [reset]\n", s[0]);
    pvalid = true;
  } else if (n == 3) {
    HW_API::initFPGABuildID();
    if (!strcmp(s[1], "ckeofwerr")) {
      uint8_t quad = 111;
      uint8_t chan = strtoul(s[2], NULL, 0);
      uint8_t error_cnt;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      error_cnt = HW_API::getInterfpgaTxcErrorCnt(HW_API::mapInterfpgaQuadToIndex(quad), chan);
      printf("Clock_en TX channel %u overflow error is: %u\n", chan, error_cnt);
      pvalid = true;
    } else if (!strcmp(s[1], "audofwerr")) {
      uint8_t quad = 111;
      uint8_t chan = strtoul(s[2], NULL, 0);
      uint8_t error_cnt;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      error_cnt = HW_API::getInterfpgaTxaErrorCnt(HW_API::mapInterfpgaQuadToIndex(quad), chan);
      printf("Audio TX channel %u overflow error is: %u\n", chan, error_cnt);
      pvalid = true;
    } else if (!strcmp(s[1], "metaofwerr")) {
      uint8_t quad = 111;
      uint8_t chan = strtoul(s[2], NULL, 0);
      uint8_t error_cnt;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      error_cnt = HW_API::getInterfpgaTxmErrorCnt(HW_API::mapInterfpgaQuadToIndex(quad), chan);
      printf("Meta TX channel %u overflow error is: %u\n", chan, error_cnt);
      pvalid = true;
    } else if (!strcmp(s[1], "usbofwerr")) {
      uint8_t quad = 111;
      uint8_t chan = strtoul(s[2], NULL, 0);
      uint8_t error_cnt;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      error_cnt = HW_API::getInterfpgaTxuErrorCnt(HW_API::mapInterfpgaQuadToIndex(quad), chan);
      printf("USB TX channel %u overflow error is: %u\n", chan, error_cnt);
      pvalid = true;
    } else if (!strcmp(s[1], "vidofwerr")) {
      uint8_t quad = 111;
      uint8_t chan = strtoul(s[2], NULL, 0);
      uint8_t error_cnt;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      error_cnt = HW_API::getInterfpgaTxvErrorCnt(HW_API::mapInterfpgaQuadToIndex(quad), chan);
      printf("Video TX channel %u overflow error is: %u\n", chan, error_cnt);
      pvalid = true;
    }
  } else if (n == 4) {
    HW_API::initFPGABuildID();
    if (!strcmp(s[1], "linkup")) {
      uint8_t quad = strtoul(s[2], NULL, 0);
      uint8_t chan = strtoul(s[3], NULL, 0);
      bool status;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::getInterfpgaLinkStatus(HW_API::mapInterfpgaQuadToIndex(quad), chan, &status);
      printf("Quad %u channel %u link status: %u\n", quad, chan, status);
      pvalid = true;
    } else if (!strcmp(s[1], "laneup")) {
      uint8_t quad = strtoul(s[2], NULL, 0);
      uint8_t chan = strtoul(s[3], NULL, 0);
      uint8_t status;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::getInterfpgaLaneStatus(HW_API::mapInterfpgaQuadToIndex(quad), chan, &status);
      printf("Quad %u channel %u lane 0 status: %u\n", quad, chan, status&1);
      printf("Quad %u channel %u lane 1 status: %u\n", quad, chan, (status>>1)&1);
      pvalid = true;
    } else if (!strcmp(s[1], "softerr")) {
      uint8_t quad = strtoul(s[2], NULL, 0);
      uint8_t chan = strtoul(s[3], NULL, 0);
      bool error;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::getInterfpgaSoftErrorStatus(HW_API::mapInterfpgaQuadToIndex(quad), chan, &error);
      printf("Quad %u channel %u soft error: %u\n", quad, chan, error);
      pvalid = true;
    } else if (!strcmp(s[1], "harderr")) {
      uint8_t quad = strtoul(s[2], NULL, 0);
      uint8_t chan = strtoul(s[3], NULL, 0);
      bool error;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::getInterfpgaHardErrorStatus(HW_API::mapInterfpgaQuadToIndex(quad), chan, &error);
      printf("Quad %u channel %u hard error: %u\n", quad, chan, error);
      pvalid = true;
    } else if (!strcmp(s[1], "iplinkup")) {
      uint8_t quad = strtoul(s[2], NULL, 0);
      uint8_t chan = strtoul(s[3], NULL, 0);
      bool status;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::getInterfpgaIpLinkStatus(HW_API::mapInterfpgaQuadToIndex(quad), chan, &status);
      printf("Quad %u IP Channel %u link status: %u\n", quad, chan, status);
      pvalid = true;
    } else if (!strcmp(s[1], "iplaneup")) {
      uint8_t quad = strtoul(s[2], NULL, 0);
      uint8_t chan = strtoul(s[3], NULL, 0);
      uint8_t status;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::getInterfpgaIpLaneStatus(HW_API::mapInterfpgaQuadToIndex(quad), chan, &status);
      printf("Quad %u IP Channel %u lane 0 status: %u\n", quad, chan, status&1);
      pvalid = true;
    } else if (!strcmp(s[1], "ipsofterr")) {
      uint8_t quad = strtoul(s[2], NULL, 0);
      uint8_t chan = strtoul(s[3], NULL, 0);
      bool error;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::getInterfpgaIpSoftErrorStatus(HW_API::mapInterfpgaQuadToIndex(quad), chan, &error);
      printf("Quad %u IP Channel %u soft error: %u\n", quad, chan, error);
      pvalid = true;
    } else if (!strcmp(s[1], "ipharderr")) {
      uint8_t quad = strtoul(s[2], NULL, 0);
      uint8_t chan = strtoul(s[3], NULL, 0);
      bool error;
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::getInterfpgaIpHardErrorStatus(HW_API::mapInterfpgaQuadToIndex(quad), chan, &error);
      printf("Quad %u IP Channel %u hard error: %u\n", quad, chan, error);
      pvalid = true;
    } else if (!strcmp(s[1], "ckeofwerr")) {
      uint8_t quad = 111;
      uint8_t chan = strtoul(s[2], NULL, 0);
      bool reset = (bool)strtoul(s[3], NULL, 0);
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::resetInterfpgaTxcErrorCnt(HW_API::mapInterfpgaQuadToIndex(quad), chan, reset);
      printf("Clock_en TX channel %u overflow error counter reset is: %u\n", chan, reset);
      pvalid = true;
    } else if (!strcmp(s[1], "audofwerr")) {
      uint8_t quad = 111;
      uint8_t chan = strtoul(s[2], NULL, 0);
      bool reset = (bool)strtoul(s[3], NULL, 0);
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::resetInterfpgaTxaErrorCnt(HW_API::mapInterfpgaQuadToIndex(quad), chan, reset);
      printf("Audio TX channel %u overflow error counter reset is: %u\n", chan, reset);
      pvalid = true;
    } else if (!strcmp(s[1], "metaofwerr")) {
      uint8_t quad = 111;
      uint8_t chan = strtoul(s[2], NULL, 0);
      bool reset = (bool)strtoul(s[3], NULL, 0);
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::resetInterfpgaTxmErrorCnt(HW_API::mapInterfpgaQuadToIndex(quad), chan, reset);
      printf("Meta TX channel %u overflow error counter reset is: %u\n", chan, reset);
      pvalid = true;
    } else if (!strcmp(s[1], "usbofwerr")) {
      uint8_t quad = 111;
      uint8_t chan = strtoul(s[2], NULL, 0);
      bool reset = (bool)strtoul(s[3], NULL, 0);
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::resetInterfpgaTxuErrorCnt(HW_API::mapInterfpgaQuadToIndex(quad), chan, reset);
      printf("USB TX channel %u overflow error counter reset is: %u\n", chan, reset);
      pvalid = true;
    } else if (!strcmp(s[1], "vidofwerr")) {
      uint8_t quad = 111;
      uint8_t chan = strtoul(s[2], NULL, 0);
      bool reset = (bool)strtoul(s[3], NULL, 0);
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::resetInterfpgaTxvErrorCnt(HW_API::mapInterfpgaQuadToIndex(quad), chan, reset);
      printf("Video TX channel %u overflow error counter reset is: %u\n", chan, reset);
      pvalid = true;
    }
  } else if (n == 5) {
    HW_API::initFPGABuildID();
    if (!strcmp(s[1], "reset")) {
      uint8_t quad = strtoul(s[2], NULL, 0);
      uint8_t chan = strtoul(s[3], NULL, 0);
      bool reset = (bool)strtoul(s[4], NULL, 0);
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::setInterfpgaReset(HW_API::mapInterfpgaQuadToIndex(quad), chan, reset);
      printf("Quad %u channel %u reset state: %u\n", quad, chan, reset);
      pvalid = true;
    } else if (!strcmp(s[1], "ipreset")) {
      uint8_t quad = strtoul(s[2], NULL, 0);
      uint8_t chan = strtoul(s[3], NULL, 0);
      bool reset = (bool)strtoul(s[4], NULL, 0);
      HW_API::initInterfpga(HW_API::mapInterfpgaQuadToIndex(quad));
      HW_API::setInterfpgaIpReset(HW_API::mapInterfpgaQuadToIndex(quad), chan, reset);
      printf("Quad %u IP Channel %u reset state: %u\n", quad, chan, reset);
      pvalid = true;
    }
  }
  if (!pvalid) {
      printf("Invalid\n");
  }
  return 0;
}

static int
execSDI12G(int n, char *s[])
{
    bool pvalid = false;
    HW_API::initFPGABuildID();
    HW_API::initSDI12G();

    if (n == 1) {
        printf("Usage: %s status <chan>\n", s[0]);
        printf("       %s rxraster <rxchan>\n", s[0]);
        printf("       %s rxrastererror <rxchan>\n", s[0]);
        printf("       %s rxvpid <rxchan>\n", s[0]);
        printf("       %s rxcrc <rxchan>\n", s[0]);
        printf("       %s rxcrcclear <rxchan>\n", s[0]);
        printf("       %s rxactivestreams <rxchan>\n", s[0]);
        printf("       %s rx2si <rxchan>\n", s[0]);
        printf("       %s rx2sibypass <rxchan> <enable>\n", s[0]);
        printf("       %s txstatus <txchan>\n", s[0]);
        printf("       %s txyascode <txchan> [<clock> <link> <format>]\n", s[0]);
        printf("       %s txmux <txchan> <output_select>\n", s[0]);
        printf("       %s txvpid <txchan>\n", s[0]);
        printf("       %s txvpiddata <txchan> <vpid>\n", s[0]);
        printf("       %s txvpidline <txchan> <line_f0> <line_f1>\n", s[0]);
        printf("       %s txgenlock <txchan> <standard>\n", s[0]);
        printf("       %s txvidlock <txchan> <mask>\n", s[0]);
        printf("       %s tx2si <txchan> [enable]\n", s[0]);
        printf("       %s tx2sibypass <txchan> <enable>\n", s[0]);
        printf("       %s sync <txchan>\n", s[0]);
        printf("       %s refclock\n", s[0]);
        printf("       %s txusrclock <txchan>\n", s[0]);
        printf("       %s rxusrclock <rxchan>\n", s[0]);
        printf("       %s fractional [enable] [force]\n", s[0]);
        printf("       %s rxreset <chan> <reset>\n", s[0]);
        printf("       %s txreset <chan> <reset>\n", s[0]);
        printf("       %s rxgtxreset <chan> <reset>\n", s[0]);
        printf("       %s txgtxreset <chan> <reset>\n", s[0]);
        printf("       %s rxdetectdisable <chan> [disable]\n", s[0]);
        printf("       %s rxforcedmode <chan> [mode]\n", s[0]);
        printf("       %s dcxo <index>\n", s[0]);
        printf("       %s dcxo setDone <index> <done>\n", s[0]);
        printf("       %s dcxo setClock <index> <frequencyHz> [accept-best-stable-freq]\n", s[0]);
        printf("       %s dcxo setLock <index> <lock>\n", s[0]);
        printf("       %s reflock\n", s[0]);
        printf("       %s rxaudio -> Sub-Menu\n", s[0]);
        printf("       %s txaudio -> Sub-Menu\n", s[0]);
        printf("       %s ptp     -> Sub-Menu\n", s[0]);
        printf("       %s genlock -> Sub-Menu\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        if (!strcmp(s[1], "rxaudio")) {
            printf("Usage:\n");
            printf("       %s %s info          <rxchan>\n", s[0], s[1]);
            printf("       %s %s grouppresent  <rxchan>\n", s[0], s[1]);
            printf("       %s %s grouperror    <rxchan>\n", s[0], s[1]);
            printf("       %s %s grouprate     <rxchan>\n", s[0], s[1]);
            printf("       %s %s channelactive <rxchan>\n", s[0], s[1]);
            pvalid = true;
        } else if (!strcmp(s[1], "txaudio")) {
            printf("Usage:\n");
            printf("       %s %s groupenable   <txchan> <group>   <0/1>\n", s[0], s[1]);
            printf("       %s %s channelenable <txchan> <channel> <0/1>\n", s[0], s[1]);
            pvalid = true;
        } else if (!strcmp(s[1], "ptp")) {
            printf("Usage:\n");
            printf("       %s %s <0/1>\n", s[0], s[1]);
            printf("       %s %s locked\n", s[0], s[1]);
            printf("       %s %s lockreset\n", s[0], s[1]);
            pvalid = true;
        } else if (!strcmp(s[1], "genlock")) {
            printf("Usage:\n");
            printf("       %s %s <0/1>\n", s[0], s[1]);
            printf("       %s %s locked\n", s[0], s[1]);
            printf("       %s %s lockreset\n", s[0], s[1]);
            pvalid = true;
        } else if (!strcmp(s[1], "refclock")) {
            uint32_t clockFrequency;
            int32_t ret = HW_API::getSDI12G148M350HzClockFrequency(&clockFrequency);
            if (ret >= 0 ) {
                printf("SDI Reference Clock Frequency: %u.\n", clockFrequency);
            } else {
                printf("Error Reading Clock Frequency!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "fractional")) {
            bool fractional;
            int32_t ret = HW_API::getSDI12GFractional(&fractional);
            if (ret >= 0 ) {
                printf("SDI 12G Fractional: %u.\n", fractional);
            } else {
                printf("Error Reading 12G Fractional!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "reflock")) {
            HW_API::dumpSDI12GReferenceLockStatus();
            pvalid = true;
        }
    } else if (n == 3) {
        uint32_t chan = strtoul(s[2], NULL, 0);
        if (!strcmp(s[1], "status")) {
            SDI_12G::sdi_status_type SdiStatus;
            int32_t ret = HW_API::getSDI12GStatus(chan, &SdiStatus);
            if (ret >= 0) {
                printf("SDI Chan %u Status:\n", chan);
                printf("  QPLL Unlocked:     %s.\n", (SdiStatus.qpll_unlocked ? "true" : "false"));
                printf("  CPLL Unlocked:     %s.\n", (SdiStatus.cpll_unlocked ? "true" : "false"));
                printf("  Tx Fabric Reset:   %s.\n", (SdiStatus.tx_fabric_reset ? "true" : "false"));
                printf("  Tx Overflow:       %s.\n", (SdiStatus.tx_overflow ? "true" : "false"));
                printf("  Tx Underflow:      %s.\n", (SdiStatus.tx_underflow ? "true" : "false"));
                printf("  Rx M:              %x.\n", SdiStatus.rx_m);
                printf("  Tx M:              %x.\n", SdiStatus.tx_m);
                printf("  Rx Mode:           %x.\n", SdiStatus.rx_mode);
                printf("  Tx Mode:           %x.\n", SdiStatus.tx_mode);
                printf("  Tx Mode Level B    %s.\n", (SdiStatus.tx_mode_levelb ? "true" : "false"));
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "fractional")) {
            bool fractional = (bool) strtoul(s[2], NULL, 0);
            int32_t ret = 0;
            ret += HW_API::setSDI12GFractional(fractional);
            if (ret >= 0) {
                printf("SDI 12G Fractional set to: %x.\n", fractional);
            } else {
                printf("Error setting 12G Fractional!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "ptp")) {
            if (!strcmp(s[2], "locked")) {
              bool locked;
              HW_API::getSDI12GPTPReferenceLockLocked(&locked);
              if (locked) {
                printf("SDI 12G reference PTP locked!\n");
              } else {
                printf("SDI 12G reference PTP *NOT* locked!\n");
              }
              pvalid = true;
            } else if (!strcmp(s[2], "lockreset")) {
              HW_API::setSDI12GPTPReferenceLockReset();
              printf("SDI 12G PTP locking reset.\n");
              pvalid = true;
            } else {
              bool enable = (bool)strtoul(s[2], NULL, 0);
              HW_API::setSDI12GPTPLock(enable);
              pvalid = true;
            }
        } else if (!strcmp(s[1], "genlock")) {
            if (!strcmp(s[2], "locked")) {
              bool locked;
              HW_API::getSDI12GGenlockReferenceLockLocked(&locked);
              if (locked) {
                printf("SDI 12G reference Genlock locked!\n");
              } else {
                printf("SDI 12G reference Genlock *NOT* locked!\n");
              }
              pvalid = true;
            } else if (!strcmp(s[2], "lockreset")) {
              HW_API::setSDI12GGenlockReferenceLockReset();
              printf("SDI 12G Genlock locking reset.\n");
              pvalid = true;
            } else {
              bool enable = (bool)strtoul(s[2], NULL, 0);
              HW_API::setSDI12GGenlockLock(enable);
              pvalid = true;
            }
        } else if (!strcmp(s[1], "rxraster")) {
            SDI_12G::sdi_rx_raster_type SdiRxRaster;
            int32_t ret = HW_API::getSDI12GRxRaster(chan, &SdiRxRaster);
            if (ret >= 0) {
                printf("SDI Rx Chan %u Raster:\n", chan);
                printf("  ASPL:              %u.\n", SdiRxRaster.aspl);
                printf("  TSPL:              %u.\n", SdiRxRaster.tspl);
                printf("  ALPF0:             %u.\n", SdiRxRaster.alpf0);
                printf("  ALPF1:             %u.\n", SdiRxRaster.alpf1);
                printf("  TLPF0:             %u.\n", SdiRxRaster.tlpf0);
                printf("  TLPF1:             %u.\n", SdiRxRaster.tlpf1);
                printf("  Interlaced:        %u.\n", SdiRxRaster.interlaced);
                printf("  V Active Start F0: %u.\n", SdiRxRaster.v_active_start_f0);
                printf("  V Active Start F1: %u.\n", SdiRxRaster.v_active_start_f1);
                printf("  Frame Period:      %u (%.2f Hz).\n", SdiRxRaster.frame_period, (float)27000000/SdiRxRaster.frame_period);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxrastererror")) {
            SDI_12G::sdi_rx_raster_error_type SdiRxRasterError;
            int32_t ret = HW_API::getSDI12GRxRasterError(chan, &SdiRxRasterError);
            if (ret >= 0) {
                printf("SDI Rx Chan %u Raster Error:\n", chan);
                printf("  SAV Error:             %s.\n", (SdiRxRasterError.rx_sav_error ? "true" : "false"));
                printf("  EAV Error:             %s.\n", (SdiRxRasterError.rx_eav_error ? "true" : "false"));
                printf("  XYZ Error:             %s.\n", (SdiRxRasterError.rx_xyz_error ? "true" : "false"));
                printf("  H Count Overflow:      %s.\n", (SdiRxRasterError.rx_h_cnt_overflow ? "true" : "false"));
                printf("  V Count Overflow:      %s.\n", (SdiRxRasterError.rx_v_cnt_overflow ? "true" : "false"));
                printf("  ALPF Count Overflow:   %s.\n", (SdiRxRasterError.rx_alpf_cnt_overflow ? "true" : "false"));
                printf("  TLPF Count Overflow:   %s.\n", (SdiRxRasterError.rx_tlpf_cnt_overflow ? "true" : "false"));
                printf("  HD V Count Error:      %s.\n", (SdiRxRasterError.rx_hd_v_cnt_error ? "true" : "false"));
                printf("  ASPL Not Stable:       %s.\n", (SdiRxRasterError.rx_aspl_not_stable ? "true" : "false"));
                printf("  TSPL Not Stable:       %s.\n", (SdiRxRasterError.rx_tspl_not_stable ? "true" : "false"));
                printf("  ALPF Not Stable:       %s.\n", (SdiRxRasterError.rx_alpf_not_stable ? "true" : "false"));
                printf("  TLPF Not Stable:       %s.\n", (SdiRxRasterError.rx_tlpf_not_stable ? "true" : "false"));
                printf("  Interlaced Not Stable: %s.\n", (SdiRxRasterError.rx_interlaced_not_stable ? "true" : "false"));
                printf("  V Active Not Stable:   %s.\n", (SdiRxRasterError.rx_vact_not_stable ? "true" : "false"));
                printf("  Standard Change:       %s.\n", (SdiRxRasterError.rx_standard_change ? "true" : "false"));
                printf("  Video Not Present:     %s.\n", (SdiRxRasterError.rx_video_not_present ? "true" : "false"));
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxvpid")) {
            uint32_t SdiRxVPIDY;
            uint32_t SdiRxVPIDC;
            int32_t ret = 0;
            ret += HW_API::getSDI12GRxVPIDY(chan, &SdiRxVPIDY);
            ret += HW_API::getSDI12GRxVPIDC(chan, &SdiRxVPIDC);
            if (ret >= 0) {
                printf("SDI Rx Chan %u VPIDs:\n", chan);
                printf("  Y VPID: %08x.\n", SdiRxVPIDY);
                printf("  C VPID: %08x.\n", SdiRxVPIDC);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxcrc")) {
            uint32_t SdiRxCRCErrorCount;
            int32_t ret = 0;
            ret += HW_API::getSDI12GRxCRCErrorCount(chan, &SdiRxCRCErrorCount);
            if (ret >= 0) {
                printf("SDI Rx Chan %u CRC Count: %u\n", chan, SdiRxCRCErrorCount);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxcrcclear")) {
            int32_t ret = 0;
            ret += HW_API::setSDI12GRxCRCErrorClear(chan);
            if (ret >= 0) {
                printf("SDI Rx Chan %u CRC Count Cleared.\n", chan);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxactivestreams")) {
            uint8_t SdiRxActiveStreams;
            int32_t ret = 0;
            ret += HW_API::getSDI12GRxActiveStreams(chan, &SdiRxActiveStreams);
            if (ret >= 0) {
                printf("SDI Rx Chan %u Active Streams: %u\n", chan, SdiRxActiveStreams);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rx2si")) {
            bool SdiRx2SIEnable;
            bool SdiRx2SIBypass;
            int32_t ret = 0;
            ret += HW_API::getSDI12GRx2SIEnable(chan, &SdiRx2SIEnable);
            ret += HW_API::getSDI12GRx2SIBypass(chan, &SdiRx2SIBypass);
            if (ret >= 0) {
                printf("SDI Rx Chan %u 2SI:\n", chan);
                printf("  Enable: %u\n", SdiRx2SIEnable);
                printf("  Bypass: %u\n", SdiRx2SIBypass);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "tx2si")) {
            bool SdiTx2SIEnable;
            bool SdiTx2SIBypass;
            int32_t ret = 0;
            ret += HW_API::getSDI12GTx2SIEnable(chan, &SdiTx2SIEnable);
            ret += HW_API::getSDI12GTx2SIBypass(chan, &SdiTx2SIBypass);
            if (ret >= 0) {
                printf("SDI Tx Chan %u 2SI:\n", chan);
                printf("  Enable: %u\n", SdiTx2SIEnable);
                printf("  Bypass: %u\n", SdiTx2SIBypass);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "txvpid")) {
            uint32_t SdiTxVpidData;
            int32_t ret = 0;
            ret += HW_API::getSDI12GTxVpidData(chan, &SdiTxVpidData);
            if (ret >= 0) {
                printf("SDI Tx Chan %u VPID: %08x.\n", chan, SdiTxVpidData);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "txstatus")) {
            SDI_12G::sdi_tx_status_type SdiTxStatus;
            int32_t ret = HW_API::getSDI12GTxStatus(chan, &SdiTxStatus);
            if (ret >= 0) {
                printf("SDI Tx Chan %u Status:\n", chan);
                printf("  Standard Changed: %s.\n", (SdiTxStatus.standard_changed ? "true" : "false"));
                printf("  FIFO Full:        %s.\n", (SdiTxStatus.fifo_full ? "true" : "false"));
                printf("  FIFO Bad Lock:    %s.\n", (SdiTxStatus.fifo_badlock ? "true" : "false"));
                printf("  Force Re-lock:    %s.\n", (SdiTxStatus.force_relock ? "true" : "false"));
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxusrclock")) {
            uint32_t clockFrequency;
            int32_t ret = HW_API::getSDI12GRxUsrclockFrequency(chan, &clockFrequency);
            if (ret >= 0) {
                printf("SDI Rx Chan %u Rx Usrclock Frequency: %u\n", chan, clockFrequency);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "txusrclock")) {
            uint32_t clockFrequency;
            int32_t ret = HW_API::getSDI12GTxUsrclockFrequency(chan, &clockFrequency);
            if (ret >= 0) {
                printf("SDI Tx Chan %u Tx Usrclock Frequency: %u\n", chan, clockFrequency);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "txyascode")) {
            SDI_12G::sdi_yas_code_type SdiTxYasCode;
            int32_t ret = HW_API::getSDI12GTxYasCode(chan, &SdiTxYasCode);
            if (ret >= 0) {
                printf("SDI Tx Chan %u Tx YAS Code:\n", chan);
                printf("  YAS Clock Code:  %u.\n", SdiTxYasCode.yas_clock_code);
                printf("  YAS Link Code:   %u.\n", SdiTxYasCode.yas_link_code);
                printf("  YAS Format Code: %u.\n", SdiTxYasCode.yas_format_code);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxdetectdisable")) {
            bool disable;
            int32_t ret = HW_API::getSDI12GRxDetectDisable(chan, &disable);
            if (ret >= 0) {
                printf("SDI Rx Chan %u Detect Disable: %s\n", chan, (disable ? "true" : "false"));
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxforcedmode")) {
            uint8_t mode;
            int32_t ret = HW_API::getSDI12GRxForcedMode(chan, &mode);
            if (ret >= 0) {
                printf("SDI Rx Chan %u Forced Mode: %x.\n", chan, mode);
                printf("0: HD, 1: SD, 2: 3G, 4: 6G, 5: 12G Integer, 6: 12G Fractional.\n");
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "dcxo")) {
            uint8_t index = strtoul(s[2], NULL, 0);
            int32_t ret = 0;
            bool done;
            bool lock;
            ret += HW_API::getSDI12GDCXODone(index, &done);
            ret += HW_API::getSDI12GDCXOLockEnable(index, &lock);
            if (ret >= 0 ) {
                printf("Getting SDI DCXO Values for index %u:\n", index);
                printf("  Done: %u.\n",done);
                printf("  Lock: %u.\n",lock);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        }
    } else if (n == 4) {
        if (!strcmp(s[1], "rxaudio")) {
            if (!strcmp(s[2], "info")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                SDI_12G::sdi_rx_audio_information_type SdiRxAudioInformation;
                int32_t ret = HW_API::getSDI12GRxAudioInformation(chan, &SdiRxAudioInformation);
                if (ret >= 0 ) {
                    printf("SDI Rx Chan %u Audio Information:\n", chan);
                    printf("  Group    1 Present: %s.\n", (SdiRxAudioInformation.group1_present ? "true" : "false"));
                    printf("  Group    1 Error:   %s.\n", (SdiRxAudioInformation.group1_error   ? "true" : "false"));
                    printf("  Group    1 Rate:    %u.\n", (SdiRxAudioInformation.group1_rate));
                    printf("  Group    2 Present: %s.\n", (SdiRxAudioInformation.group2_present ? "true" : "false"));
                    printf("  Group    2 Error:   %s.\n", (SdiRxAudioInformation.group2_error   ? "true" : "false"));
                    printf("  Group    2 Rate:    %u.\n", (SdiRxAudioInformation.group2_rate));
                    printf("  Group    3 Present: %s.\n", (SdiRxAudioInformation.group3_present ? "true" : "false"));
                    printf("  Group    3 Error:   %s.\n", (SdiRxAudioInformation.group3_error   ? "true" : "false"));
                    printf("  Group    3 Rate:    %u.\n", (SdiRxAudioInformation.group3_rate));
                    printf("  Group    4 Present: %s.\n", (SdiRxAudioInformation.group4_present ? "true" : "false"));
                    printf("  Group    4 Error:   %s.\n", (SdiRxAudioInformation.group4_error   ? "true" : "false"));
                    printf("  Group    4 Rate:    %u.\n", (SdiRxAudioInformation.group4_rate));
                    printf("  Channel  1 Active:  %s.\n", (SdiRxAudioInformation.channel1_active ? "true" : "false"));
                    printf("  Channel  2 Active:  %s.\n", (SdiRxAudioInformation.channel2_active ? "true" : "false"));
                    printf("  Channel  3 Active:  %s.\n", (SdiRxAudioInformation.channel3_active ? "true" : "false"));
                    printf("  Channel  4 Active:  %s.\n", (SdiRxAudioInformation.channel4_active ? "true" : "false"));
                    printf("  Channel  5 Active:  %s.\n", (SdiRxAudioInformation.channel5_active ? "true" : "false"));
                    printf("  Channel  6 Active:  %s.\n", (SdiRxAudioInformation.channel6_active ? "true" : "false"));
                    printf("  Channel  7 Active:  %s.\n", (SdiRxAudioInformation.channel7_active ? "true" : "false"));
                    printf("  Channel  8 Active:  %s.\n", (SdiRxAudioInformation.channel8_active ? "true" : "false"));
                    printf("  Channel  9 Active:  %s.\n", (SdiRxAudioInformation.channel9_active ? "true" : "false"));
                    printf("  Channel 10 Active:  %s.\n", (SdiRxAudioInformation.channel10_active ? "true" : "false"));
                    printf("  Channel 11 Active:  %s.\n", (SdiRxAudioInformation.channel11_active ? "true" : "false"));
                    printf("  Channel 12 Active:  %s.\n", (SdiRxAudioInformation.channel12_active ? "true" : "false"));
                    printf("  Channel 13 Active:  %s.\n", (SdiRxAudioInformation.channel13_active ? "true" : "false"));
                    printf("  Channel 14 Active:  %s.\n", (SdiRxAudioInformation.channel14_active ? "true" : "false"));
                    printf("  Channel 15 Active:  %s.\n", (SdiRxAudioInformation.channel15_active ? "true" : "false"));
                    printf("  Channel 16 Active:  %s.\n", (SdiRxAudioInformation.channel16_active ? "true" : "false"));
                } else {
                    printf("Index out of bounds!\n");
                }
                pvalid = true;
            }
        } else if (!strcmp(s[1], "txmux")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint8_t SdiTxMuxSelect;
            SdiTxMuxSelect  = (uint8_t) strtoul(s[3], NULL, 0);
            int32_t ret = HW_API::setSDI12GTxMuxSelect(chan, SdiTxMuxSelect);
            if (ret >= 0 ) {
                printf("Setting SDI Chan %u TxMux to Input %u.\n", chan, SdiTxMuxSelect);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "txvpiddata")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint32_t SdiTxVpidData;
            SdiTxVpidData = (uint32_t) strtoul(s[3], NULL, 0);
            int32_t ret = HW_API::setSDI12GTxVpidData(chan, SdiTxVpidData);
            if (ret >= 0 ) {
                printf("Setting SDI Chan %u Tx VPID Data to 0x%x.\n", chan, SdiTxVpidData);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "txgenlock")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            if (!strcmp(s[3], "0")) {
              // Disable
              HW_API::setSDI12GGenlockLock(false);
              pvalid = true;
            } else if (!strcmp(s[3], "1080p60")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 242, 2);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "1080p59")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 1030, 1124);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "1080p50")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 994, 0);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "1080p30")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 222, 3);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "1080p29")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 64, 2);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "1080p25")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 705, 2);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "1080i60")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 223, 1);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "1080i59")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 65, 0);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "1080i50")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 706, 0);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "720p60")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 783, 3);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "720p59")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 350, 2);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else if (!strcmp(s[3], "720p50")) {
              HW_API::initFPGABuildID();
              HW_API::initScalerPath(chan);
              HW_API::setScalerPhase(chan, 3, 2);
              HW_API::setScalerGenlockLock(chan, true);
              HW_API::setSDI12GGenlockLock(true);
              HW_API::setScalerGenlockPhaseJam(chan);
              pvalid = true;
            } else {
              pvalid = false;
            }
            if (pvalid) {
                printf("Setting SDI Chan %u genlock enable to %s.\n", chan, s[3]);
            } else if (pvalid) {
                printf("Index out of bounds!\n");
            }
        } else if (!strcmp(s[1], "fractional")) {
            bool fractional = (bool) strtoul(s[2], NULL, 0);
            bool force = (bool) strtoul(s[3], NULL, 0);
            int32_t ret = 0;
            ret += HW_API::setSDI12GFractional(fractional, force);
            if (ret >= 0) {
                printf("SDI 12G Fractional set to: %x.\n", fractional);
            } else {
                printf("Error setting 12G Fractional!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rx2sibypass")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool SdiRx2SIBypass = (bool) strtoul(s[3], NULL, 0);
            int32_t ret = 0;
            ret += HW_API::setSDI12GRx2SIBypass(chan,SdiRx2SIBypass);
            if (ret >= 0) {
                printf("SDI Rx Chan %u 2SI Bypass set to: %x.\n", chan, SdiRx2SIBypass);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "tx2si")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool SdiTx2SIEnable = (bool) strtoul(s[3], NULL, 0);
            int32_t ret = 0;
            ret += HW_API::setSDI12GTx2SIEnable(chan,SdiTx2SIEnable);
            if (ret >= 0) {
                printf("SDI Tx Chan %u 2SI Enable set to: %x.\n", chan, SdiTx2SIEnable);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "tx2sibypass")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool SdiTx2SIBypass = (bool) strtoul(s[3], NULL, 0);
            int32_t ret = 0;
            ret += HW_API::setSDI12GTx2SIBypass(chan,SdiTx2SIBypass);
            if (ret >= 0) {
                printf("SDI Tx Chan %u 2SI Bypass set to: %x.\n", chan, SdiTx2SIBypass);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxreset")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool reset = (bool) strtoul(s[3], NULL, 0);
            int32_t ret = 0;
            ret += HW_API::setSDI12GRxReset(chan,reset);
            if (ret >= 0) {
                printf("SDI Rx Chan %u Reset set to: %x.\n", chan, reset);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "txreset")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool reset = (bool) strtoul(s[3], NULL, 0);
            int32_t ret = 0;
            ret += HW_API::setSDI12GTxReset(chan,reset);
            if (ret >= 0) {
                printf("SDI Tx Chan %u Reset set to: %x.\n", chan, reset);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxgtxreset")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool reset = (bool) strtoul(s[3], NULL, 0);
            int32_t ret = 0;
            ret += HW_API::setSDI12GRxGTXReset(chan,reset);
            if (ret >= 0) {
                printf("SDI Rx Chan %u GTX Reset set to: %x.\n", chan, reset);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "txgtxreset")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool reset = (bool) strtoul(s[3], NULL, 0);
            int32_t ret = 0;
            ret += HW_API::setSDI12GTxGTXReset(chan,reset);
            if (ret >= 0) {
                printf("SDI Tx Chan %u GTX Reset set to: %x.\n", chan, reset);
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxdetectdisable")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            bool disable = (bool) strtoul(s[3], NULL, 0);
            int32_t ret = HW_API::setSDI12GRxDetectDisable(chan, disable);
            if (ret >= 0) {
                printf("SDI Rx Chan %u Detect Disable set to: %s\n", chan, (disable ? "true" : "false"));
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "rxforcedmode")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint8_t mode = (uint8_t) strtoul(s[3], NULL, 0);
            int32_t ret = HW_API::setSDI12GRxForcedMode(chan, mode);
            if (ret >= 0) {
                printf("SDI Rx Chan %u Forced Mode set to: %x.\n", chan, mode);
                printf("0: HD, 1: SD, 2: 3G, 4: 6G, 5: 12G Integer, 6: 12G Fractional.\n");
            } else {
                printf("Index out of bounds!\n");
            }
            pvalid = true;
        }
    } else if (n == 5) {
        if (!strcmp(s[1], "rxaudio")) {
            if (!strcmp(s[2], "grouppresent")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                uint32_t group = strtoul(s[4], NULL, 0);
                bool SdiRxAudioGroupPresent;
                int32_t ret = HW_API::getSDI12GRxAudioGroupPresent(chan, group, &SdiRxAudioGroupPresent);
                if (ret >= 0 ) {
                    printf("SDI Rx Chan %u Audio Group %u Present: %s.\n", chan, group, (SdiRxAudioGroupPresent ? "true" : "false"));
                } else if (ret == -1){
                    printf("Index out of bounds!\n");
                } else if (ret == -2){
                    printf("Group out of bounds!\n");
                }
                pvalid = true;
            } else if (!strcmp(s[2], "grouperror")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                uint32_t group = strtoul(s[4], NULL, 0);
                bool SdiRxAudioGroupError;
                int32_t ret = HW_API::getSDI12GRxAudioGroupError(chan, group, &SdiRxAudioGroupError);
                if (ret >= 0 ) {
                    printf("SDI Rx Chan %u Audio Group %u Error: %s.\n", chan, group, (SdiRxAudioGroupError ? "true" : "false"));
                } else if (ret == -1){
                    printf("Index out of bounds!\n");
                } else if (ret == -2){
                    printf("Group out of bounds!\n");
                }
                pvalid = true;
            } else if (!strcmp(s[2], "grouprate")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                uint32_t group = strtoul(s[4], NULL, 0);
                SDI_12G::sdi_rx_audio_rate SdiRxAudioGroupRate;
                int32_t ret = HW_API::getSDI12GRxAudioGroupRate(chan, group, &SdiRxAudioGroupRate);
                if (ret >= 0 ) {
                    printf("SDI Rx Chan %u Audio Group %u Rate: %u.\n", chan, group, SdiRxAudioGroupRate);
                    printf("  Rate:0=48k,1=async48k,2=44k1,3=async44k1,4=32k,5=async32k,6,7=freerun.\n");
                } else if (ret == -1){
                    printf("Index out of bounds!\n");
                } else if (ret == -2){
                    printf("Group out of bounds!\n");
                }
                pvalid = true;
            } else if (!strcmp(s[2], "channelactive")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                uint32_t channel = strtoul(s[4], NULL, 0);
                bool SdiRxAudioChannelActive;
                int32_t ret = HW_API::getSDI12GRxAudioChannelActive(chan, channel, &SdiRxAudioChannelActive);
                if (ret >= 0 ) {
                    printf("SDI Rx Chan %u Audio Channel %u Active: %s.\n", chan, channel, (SdiRxAudioChannelActive ? "true" : "false"));
                } else if (ret == -1){
                    printf("Index out of bounds!\n");
                } else if (ret == -2){
                    printf("Channel out of bounds!\n");
                }
                pvalid = true;
            }
        } else if (!strcmp(s[1], "txvpidline")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            uint16_t SdiTxVpidLineF0;
            uint16_t SdiTxVpidLineF1;
            SdiTxVpidLineF0 = (uint16_t) strtoul(s[3], NULL, 0);
            SdiTxVpidLineF1 = (uint16_t) strtoul(s[4], NULL, 0);
            int32_t ret = HW_API::setSDI12GTxVpidInsertLine(chan, SdiTxVpidLineF0, SdiTxVpidLineF1);
            if (ret >= 0 ) {
                printf("Setting SDI Chan %u Tx VPID Line to %u:%u.\n", chan, SdiTxVpidLineF0, SdiTxVpidLineF1);
            } else if (ret == -1){
                printf("Channel out of bounds!\n");
            } else if (ret == -2){
                printf("Line is out of bounds (above 1125)!\n");
            } else if (ret == -3){
                printf("Line is <= 0! If progressive, set F1=F0.\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "dcxo")) {
            if (!strcmp(s[2], "setDone")) {
                uint8_t index = strtoul(s[3], NULL, 0);
                bool done = strtoul(s[4], NULL, 0);
                int32_t ret = 0;
                ret += HW_API::setSDI12GDCXODone(index, done);
                if (ret >= 0 ) {
                    printf("Setting SDI DCXO Values for index %u:\n", index);
                    printf("  Done: %u.\n",done);
                } else {
                    printf("Index out of bounds!\n");
                }
                pvalid = true;
            } else if (!strcmp(s[2], "setClock")) {
                uint8_t index = strtoul(s[3], NULL, 0);
                uint32_t frequency = strtoul(s[4], NULL, 0);
                uint32_t si570DefaultFrequency = 74250000;
                int32_t ret = 0;
                HW_API::setSDI12GDCXOLockEnable(index, 0);
                ret += HW_API::initSDI12GDCXO(index, si570DefaultFrequency);
                if (ret >= 0) {
                    ret += HW_API::setSDI12GDCXOClock(index, frequency);
                    if (ret >= 0) {
                        si570_ctrl::si570_settings_type si570_settings;
                        bool valid;
                        HW_API::readSDI12GDCXOSettings(index, &valid, &si570_settings);
                        if (valid) {
                            printf("Si570 Settings:\n");
                            printf("  FXTAL:     %llu\n", si570_settings.FXTAL);
                            printf("  RFREQ:     %llu\n", si570_settings.RFREQ);
                            printf("  frequency: %u\n",   si570_settings.frequency);
                            printf("  N1:        %u\n",   si570_settings.N1);
                            printf("  HSDIV:     %u\n",   si570_settings.HSDIV);
                        }
                        if (valid) {
                            printf("DCXO frequency:\n");
                            printf("  Clock: %u.\n",frequency);
                        } else {
                            printf("An error occured");
                        }
                    } else if (ret == -1) {
                        printf("Index out of bounds!\n");
                    } else if (ret == -4) {
                        printf("Provided frequency is in a disallowed spur!\n");
                    } else {
                        printf("Failed to set DCXO to provided frequency!\n");
                    }
                } else {
                    printf("Index out of bounds!\n");
                }
                pvalid = true;
            } else if (!strcmp(s[2], "setLock")) {
                uint8_t index = strtoul(s[3], NULL, 0);
                bool lock = strtoul(s[4], NULL, 0);
                int32_t ret = 0;
                ret += HW_API::setSDI12GDCXOLockEnable(index, lock);
                if (ret >= 0) {
                    printf("Setting SDI SI570 Values for index %u:\n", index);
                    printf("  Lock: %u.\n", lock);
                } else {
                    printf("Index out of bounds!\n");
                }
                pvalid = true;
            }
        }
    } else if (n == 6) {
        if (!strcmp(s[1], "txyascode")) {
            uint32_t chan = strtoul(s[2], NULL, 0);
            SDI_12G::sdi_yas_code_type SdiTxYasCode;
            SdiTxYasCode.yas_clock_code  = (SDI_12G::sdi_yas_clock_code) strtoul(s[3], NULL, 0);
            SdiTxYasCode.yas_link_code   = (SDI_12G::sdi_yas_link_code)  strtoul(s[4], NULL, 0);
            SdiTxYasCode.yas_format_code = (SDI_12G::sdi_yas_format_code)strtoul(s[5], NULL, 0);
            int32_t ret = HW_API::setSDI12GTxYasCode(chan, SdiTxYasCode);
            if (ret >= 0 ) {
                printf("Setting Tx SDI Chan %u TxYasCode to %u %u %u.\n", chan,
                                                                       SdiTxYasCode.yas_clock_code,
                                                                       SdiTxYasCode.yas_link_code,
                                                                       SdiTxYasCode.yas_format_code);
            } else if (ret == -1) {
                printf("Index out of bounds!\n");
            } else if (ret == -2) {
                printf("YAS Clock Code Invalid!\n");
            } else if (ret == -3) {
                printf("YAS Link Code Invalid!\n");
            } else if (ret == -4) {
                printf("YAS Format Code Invalid!\n");
            } else if (ret == -5) {
                printf("YAS Code Not Valid For Fractional Mode. No Fractional Pair Exists!\n");
            } else if (ret == -6) {
                printf("YAS Code Not Valid For Fractional Mode. Fractional Pair Possible!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "txaudio")) {
            if (!strcmp(s[2], "groupenable")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                uint32_t group = strtoul(s[4], NULL, 0);
                bool SdiTxAudioGroupEnable = strtoul(s[5], NULL, 0);
                int32_t ret = HW_API::setSDI12GTxAudioGroupEnable(chan, group, SdiTxAudioGroupEnable);
                if (ret >= 0 ) {
                    printf("Setting SDI Tx Chan %u Audio Group %u Enable to: %s.\n", chan, group, (SdiTxAudioGroupEnable ? "true" : "false"));
                } else if (ret == -1){
                    printf("Index out of bounds!\n");
                } else if (ret == -2){
                    printf("Group out of bounds!\n");
                }
                pvalid = true;
            } else if (!strcmp(s[2], "channelenable")) {
                uint32_t chan = strtoul(s[3], NULL, 0);
                uint32_t channel = strtoul(s[4], NULL, 0);
                bool SdiTxAudioChannelEnable = strtoul(s[5], NULL, 0);
                int32_t ret = HW_API::setSDI12GTxAudioChannelEnable(chan, channel, SdiTxAudioChannelEnable);
                if (ret >= 0 ) {
                    printf("Setting SDI Tx Chan %u Audio Channel %u Enable to: %s.\n", chan, channel, (SdiTxAudioChannelEnable ? "true" : "false"));
                } else if (ret == -1){
                    printf("Index out of bounds!\n");
                } else if (ret == -2){
                    printf("Channel out of bounds!\n");
                }
                pvalid = true;
            }
        } else if (!strcmp(s[1], "dcxo")) {
            if (!strcmp(s[2], "setClock")) {
                uint8_t index = strtoul(s[3], NULL, 0);
                uint32_t frequency = strtoul(s[4], NULL, 0);
                uint32_t si570DefaultFrequency = 74250000;
                int32_t ret = 0;
                HW_API::setSDI12GDCXOLockEnable(index, 0);
                ret += HW_API::initSDI12GDCXO(index, si570DefaultFrequency);
                if (ret >= 0) {
                    ret = HW_API::setSDI12GDCXOClock(index, frequency);
                    if (ret >= 0) {
                        si570_ctrl::si570_settings_type si570_settings;
                        bool valid;
                        HW_API::readSDI12GDCXOSettings(index, &valid, &si570_settings);
                        if (valid) {
                            printf("Si570 Settings:\n");
                            printf("  FXTAL:     %llu\n", si570_settings.FXTAL);
                            printf("  RFREQ:     %llu\n", si570_settings.RFREQ);
                            printf("  frequency: %u\n",   si570_settings.frequency);
                            printf("  N1:        %u\n",   si570_settings.N1);
                            printf("  HSDIV:     %u\n",   si570_settings.HSDIV);
                        }
                        if (valid) {
                            printf("DCXO frequency:\n");
                            printf("  Clock: %u.\n",frequency);
                        } else {
                            printf("An error occured");
                        }
                    } else if (ret == -1) {
                        printf("Index out of bounds!\n");
                    } else if (ret == -4) {
                        printf("Provided frequency is in a disallowed spur!\n");
                    } else {
                        printf("Failed to set DCXO to provided frequency!\n");
                    }
                } else {
                    printf("Index out of bounds!\n");
                }
                pvalid = true;
            }
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}


static int
execGenlock(int n, char *s[])
{
    bool pvalid = false;
    HW_API::initFPGABuildID();

    if (n == 1) {
        printf("Usage: %s init\n", s[0]);
        printf("       %s enable\n", s[0]);
        printf("       %s disable\n", s[0]);
        printf("       %s ref <0 (disable),1,2>\n", s[0]);
        printf("       %s select [0/1]\n", s[0]);
        printf("       %s phase <hphase>\n", s[0]);
        printf("       %s status\n", s[0]);
        pvalid = true;
    } else if (n == 2) {
        if (!strcmp(s[1], "init")) {
            HW_API::initGenlock();
            printf("Initialized genlock!\n");
            pvalid = true;
        } else if (!strcmp(s[1], "enable")) {
            HW_API::initGenlock();
            HW_API::setGenlockEnable();
            printf("Genlock Enabled!\n");
            pvalid = true;
        } else if (!strcmp(s[1], "disable")) {
            HW_API::initGenlock();
            HW_API::setGenlockDisable();
            printf("Genlock Disabled!\n");
            pvalid = true;
        } else if (!strcmp(s[1], "status")) {
            HW_API::initGenlock();
            bool present, locked, nom_freq_err;
            char standard[16];
            uint32_t freq_err, phase_err, max_level, min_level, freq_measured;
            HW_API::getGenlockFreqError(&freq_err);
            HW_API::getGenlockPhaseError(&phase_err);
            HW_API::getGenlockMaxLevel(&max_level);
            HW_API::getGenlockMinLevel(&min_level);
            HW_API::getGenlockStatus(&present, &locked, standard);
            HW_API::getGenlockNominalFreqError(&nom_freq_err);
            HW_API::getGenlockMeasuredFreq(&freq_measured);
            printf("Status:           %s\n", present?"PRESENT":"MISSING");
            printf("Lock:             %s\n", locked?"LOCKED":"UNLOCKED");
            printf("Standard:         %s\n", standard);
            printf("Frequency Error:  %i\n", freq_err);
            printf("Phase Error:      %i\n", phase_err);
            printf("Max Level:        %u\n", max_level);
            printf("Min Level:        %u\n", min_level);
            printf("Nominal Freq:     %s\n", nom_freq_err?"ERROR":"OK");
            printf("Measured Freq:    %u\n", freq_measured);
            pvalid = true;
        } else if (!strcmp(s[1], "select")) {
            HW_API::initGenlock();
            bool xo;
            HW_API::getGenlockXOSelect(&xo);
            printf("Genlock XO Select:%u\n", xo);
            pvalid = true;
        }
    } else if (n == 3) {
        if (!strcmp(s[1], "ref")) {
            uint32_t ref = strtoul(s[2], NULL, 0);
            HW_API::initGenlock();
            if (ref == 1) {
              HW_API::setGenlockRefSource1();
              printf("Set Genlock reference to 1!\n");
            } else if (ref == 2) {
              HW_API::setGenlockRefSource2();
              printf("Set Genlock reference to 2!\n");
            } else {
              HW_API::setGenlockRefSourceDisable();
              printf("Disabled Both Genlock references!\n");
            }
            pvalid = true;
        } else if (!strcmp(s[1], "phase")) {
            HW_API::initGenlock();
            uint32_t phase = strtoul(s[2], NULL, 0);
            HW_API::setGenlockHPhase(phase);
            printf("Setting genlock hphase to %u!\n", phase);
            pvalid = true;
        } else if (!strcmp(s[1], "select")) {
            HW_API::initGenlock();
            bool xo = strtoul(s[2], NULL, 0);
            HW_API::setGenlockXOSelect(xo);
            printf("Setting genlock XO Select to %u!\n", xo);
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execVidProc(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: \n");
        printf("    %s sc_rw  <sc_path_idx> <sc_comp_idx> <reg> [write_data]\n", s[0]);
        printf("          development generic updown scaler register interface \n");
        printf("    %s vp_rw  <reg> [write_data]\n", s[0]);
        printf("          development generic video processing register interface \n");
        printf("\n");
        printf("    %s pip_region    <sc_pip_path_idx> <pip_h_start> <pip_h_stop> <pip_v_start> <pip_v_stop>\n", s[0]);
        printf("    %s pip_region    <sc_pip_path_idx> <pip_h_start> <pip_h_stop> <pip_v_start0> <pip_v_stop0> <pip_v_start1> <pip_v_stop1>\n", s[0]);
        printf("          coords are 0 based, active region, internally divided by product pixel width\n");
        printf("    %s pip_en        <vid_mix_idx> <vid_mix_inp_idx> [0/1]\n", s[0]);
        printf("    %s pip_en_mask   <vid_mix_idx> <mask>\n", s[0]);
        printf("    %s mixer_out_sel <vid_mix_idx> <select>\n", s[0]);
        printf("    %s blend_color   <vid_mix_idx> <color_fmt>\n", s[0]);
        printf("\n");
        printf("    %s vidmux <vid_mix_idx> [vid_mix_mux_index]\n", s[0]);
        printf("          used to switch video processing video mux output port source signal\n");
        printf("\n");
        printf("    %s vidmix_raster    <vid_mix_idx> [raster_idx]\n", s[0]);
        printf("    %s vidmix_phase     <vid_mix_idx> <output_raster_num> <h_phase> <v_phase>\n", s[0]);
        printf("    %s vidmix_sync_mask <vid_mix_idx> <mask>      *** does not function manually needs raster in memory ***\n", s[0]);
        printf("    %s vidmix_border_colour <vid_mix_idx> <G/Y> <B/Cb> <R/Cr>\n", s[0]);
        printf("    %s sc_ref_div       <sc_path_idx> [0/1]\n", s[0]);
        printf("    %s sc_sync_mask     <sc_idx> <mask>           *** does not function manually needs raster in memory ***\n", s[0]);
        printf("\n");
        printf("    %s sync_source   <idx> [sync_source_idx]\n", s[0]);
        printf("                      general sync mux setup for scalers and video mixers\n");
        printf("\n");
        printf("    %s sc_sync_sc_raster_source   <sc_idx> <sc_idx>\n", s[0]);
        printf("    %s sc_sync_vidmix_source      <sc_idx> <vid_mix_idx>\n", s[0]);
        printf("    %s sc_sync_sc_phase_source    <sc_idx> <sc_idx>\n", s[0]);
        printf("    %s sc_sync_disable            <sc_idx>\n", s[0]);
        printf("    %s vidmix_sync_sc_raster_source   <pip_idx> <sc_idx>\n", s[0]);
        printf("    %s vidmix_sync_vidmix_source      <pip_idx> <vid_mix_idx>\n", s[0]);
        printf("    %s vidmix_sync_sc_phase_source    <pip_idx> <sc_idx>\n", s[0]);
        printf("    %s vidmix_sync_disable            <pip_idx>\n", s[0]);
        printf("\n");
        printf("    %s sc_raster_phase  <sc_idx> <output_raster_num> <h_phase> <v_phase>\n", s[0]);
        printf("\n");
        printf("where :\n");
        printf("    sc_path_idx   = scaler path idx (0-%u)\n", (HW_API::SC_NUM_PATHS-1));
        printf("    sc_comp_idx   = scaler path idx (0-%u)\n", (HW_API::SC_NUM_COMPONENTS-1));
        printf("                      0 scaler_a  \n");
        printf("                      1 scaler_b  \n");
        printf("                      2 raster    \n");
        printf("                      3 misc      \n");
        printf("                      4 wport_0   \n");
        printf("                      5 playout   \n");
        printf("                      6 wport_1   \n");
        printf("                      7 wport_2   \n");
        printf("                      8 wport_3   \n");
        printf("    vid_mix_mux_index   =  0  Primary Scaler Output  - No pip (video mix)\n");
        printf("                                  example 1st Video Mux this would be 1st scaler output\n");
        printf("                           1  Video Mix (PIP) Output\n");
        printf("                           2+  Pip Scaler Path outputs (debug)\n");
        printf("\n");
        printf("   vidmix_border_colour\n");
        printf("                           8 bit colour values\n");
        printf("\n");
        printf("   select               = 0 = mixer output, 1 = blender output\n");
        printf("   color_fmt            = 0 = unsiged color format,e.g. RGB or Biased-YCbCr, 1 = signed YCbCr format\n");
        printf("\n");
        printf("    raster_idx          = 0 = 1080p60, 1 = 1080i60, 2 = 2160p30, 3 = 2160p60, 4 = 1080p30, 5 = 2160p24, 6 = 2160p23.98, 7 = 2160p59.94, 8 = 2160p29.98, 9 = 1080p59.94\n, 10 = 1920x1200p60, 11 = 640x480p");
        printf("                             Just raster shapes, frame rates are not used\n");
        printf("\n");
        printf("    sync_source_idx     indexs based on number of updown scalers, then mixers, then scalers again for phase lock resyncs\n");
        printf("                           example Sync Sources Example (1 Scaler, 3 Pip Scalers, 1 PiP Mixer)\n");
        printf("                               0   None                                                       \n");
        printf("                               1   Scaler 0 Raster Sync Out  (Raster position 0,0)            \n");
        printf("                               2   PiP Scaler 1 Raster Sync Out                               \n");
        printf("                               3   PiP Scaler 2 Raster Sync Out                               \n");
        printf("                               4   PiP Scaler 3 Raster Sync Out                               \n");
        printf("                               5   PiP Mixer 0 Raster Sync Out                                \n");
        printf("                               6   Scaler 0 Phase Lock ReSync Out                             \n");
        printf("                               7   PiP Scaler 1 Phase Lock ReSync Out                         \n");
        printf("                               8   PiP Scaler 2 Phase Lock ReSync Out                         \n");
        printf("                               9   PiP Scaler 3 Phase Lock ReSync Out                         \n");
        printf("\n");
        pvalid = true;
    } else if (n == 3) {
        if (!strcmp(s[1], "vp_rw")) {
            uint32_t reg          = strtoul(s[2], NULL, 0);
            uint32_t data;
            HW_API::initVidProc();
            data = HW_API::readVidProcReg(reg);
            printf("Read Video Proc Register %u == 0x%08x\n", reg, data);
            pvalid = true;
        } else if (!strcmp(s[1], "vidmux")) {
            uint32_t vid_mix_idx  = strtoul(s[2], NULL, 0);
            uint32_t mux;
            HW_API::initVidProc();
            mux = HW_API::getVidProcMux(vid_mix_idx);
            printf("Read Video Proc Mux %u == %u\n", vid_mix_idx, mux);
            pvalid = true;
        } else if (!strcmp(s[1], "sc_ref_div")) {
            uint32_t sc_path_idx  = strtoul(s[2], NULL, 0);
            uint32_t div;
            HW_API::initVidProc();
            div = HW_API::getVidProcScalerReferenceDiv(sc_path_idx);
            if (div == 1) {
              printf("Scaler %u Reference Rate is divided by 2\n",sc_path_idx);
            } else {
              printf("Scaler %u Reference Rate is not divided\n",sc_path_idx);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "sync_source")) {
            uint32_t sc_idx           = strtoul(s[2], NULL, 0);
            HW_API::initVidProc();
            uint32_t reg = HW_API::getVidProcScalerRasterSyncSource(sc_idx);
            printf("Scaler path %u raster synch source = %u\n",sc_idx,reg);
            pvalid = true;
        } else if (!strcmp(s[1], "sc_sync_disable")) {
            uint32_t sc_idx           = strtoul(s[2], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcScalerRasterSyncSourceDisable(sc_idx);
            pvalid = true;
        } else if (!strcmp(s[1], "vidmix_sync_disable")) {
            uint32_t idx           = strtoul(s[2], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcPipMixerRasterSyncSourceDisable(idx);
            pvalid = true;
        }
    } else if (n == 4) {
        if (!strcmp(s[1], "vp_rw")) {
            uint32_t reg          = strtoul(s[2], NULL, 0);
            uint32_t data         = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::writeVidProcReg(reg,data);
            printf("Write Video Proc Register %u == 0x%08x\n", reg, data);
            pvalid = true;
        } else if (!strcmp(s[1], "vidmux")) {
            uint32_t vid_mix_idx  = strtoul(s[2], NULL, 0);
            uint32_t vid_mix_mux_index  = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcMux(vid_mix_idx,vid_mix_mux_index);
            printf("Write Video Proc Mux %u == %u\n", vid_mix_idx, vid_mix_mux_index);
            pvalid = true;
        } else if (!strcmp(s[1], "vidmix_raster")) {
            uint32_t vid_mix_idx  = strtoul(s[2], NULL, 0);
            uint32_t raster_idx   = strtoul(s[3], NULL, 0);
            if (vid_mix_idx>0) {
              printf("\n Vid Mix Index >0 not yet supported\n");
              vid_mix_idx = 0;
            }
            HW_API::initVidProc();
            HW_API::setVidProcRasterIdx(vid_mix_idx,raster_idx);
            pvalid = true;
        } else if (!strcmp(s[1], "pip_en")) {
            uint32_t vid_mix_idx      = strtoul(s[2], NULL, 0);
            uint32_t vid_mix_inp_idx  = strtoul(s[3], NULL, 0);
            if (vid_mix_idx>0) {
              printf("\n Vid Mix Index >0 not yet supported\n");
              vid_mix_idx = 0;
            }
            HW_API::initVidProc();
            if (HW_API::getPipEnable(vid_mix_idx, vid_mix_inp_idx)){
              printf("vid_mix_idx %u vid_mix_inp_idx %u is enabled.\n",vid_mix_idx,vid_mix_inp_idx);
            } else {
              printf("vid_mix_idx %u vid_mix_inp_idx %u is disabled.\n",vid_mix_idx,vid_mix_inp_idx);
            }
            pvalid = true;
        } else if (!strcmp(s[1], "sc_ref_div")) {
            uint32_t sc_path_idx  = strtoul(s[2], NULL, 0);
            uint32_t div          = strtoul(s[3], NULL, 0)%2;
            HW_API::initVidProc();
            HW_API::setVidProcScalerReferenceDiv(sc_path_idx,div);
            pvalid = true;
        } else if (!strcmp(s[1], "vidmix_sync_mask")) {
            uint32_t vid_mix_idx  = strtoul(s[2], NULL, 0);
            uint32_t mask         = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcVidMixRasterSyncMaskWidth(vid_mix_idx,mask);
            pvalid = true;
        } else if (!strcmp(s[1], "sc_sync_mask")) {
            uint32_t sc_mix_idx   = strtoul(s[2], NULL, 0);
            uint32_t mask         = strtoul(s[3], NULL, 0);
            HW_API::setScalerRasterSyncMaskWidth(sc_mix_idx,mask);
            pvalid = true;
        } else if (!strcmp(s[1], "sync_source")) {
            uint32_t sc_idx           = strtoul(s[2], NULL, 0);
            uint32_t sync_source_idx  = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcScalerRasterSyncSource(sc_idx,sync_source_idx);
            pvalid = true;
        } else if (!strcmp(s[1], "sc_sync_sc_raster_source")) {
            uint32_t sc_idx           = strtoul(s[2], NULL, 0);
            uint32_t sc_idx_source    = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcScalerRasterSyncSourceScRaster(sc_idx,sc_idx_source);
            pvalid = true;
        } else if (!strcmp(s[1], "sc_sync_vidmix_source")) {
            uint32_t sc_idx           = strtoul(s[2], NULL, 0);
            uint32_t vid_mix_idx      = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcScalerRasterSyncSourcePipMixer(sc_idx,vid_mix_idx);
            pvalid = true;
        } else if (!strcmp(s[1], "sc_sync_sc_phase_source")) {
            uint32_t sc_idx           = strtoul(s[2], NULL, 0);
            uint32_t sc_idx_source    = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcScalerRasterSyncSourceScPhase(sc_idx,sc_idx_source);
            pvalid = true;
        } else if (!strcmp(s[1], "vidmix_sync_sc_raster_source")) {
            uint32_t pip_idx           = strtoul(s[2], NULL, 0);
            uint32_t sc_idx_source    = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcPipMixerRasterSyncSourceScRaster(pip_idx,sc_idx_source);
            pvalid = true;
        } else if (!strcmp(s[1], "vidmix_sync_vidmix_source")) {
            uint32_t pip_idx           = strtoul(s[2], NULL, 0);
            uint32_t vid_mix_idx      = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcPipMixerRasterSyncSourcePipMixer(pip_idx,vid_mix_idx);
            pvalid = true;
        } else if (!strcmp(s[1], "vidmix_sync_sc_phase_source")) {
            uint32_t pip_idx           = strtoul(s[2], NULL, 0);
            uint32_t sc_idx_source    = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcPipMixerRasterSyncSourceScPhase(pip_idx,sc_idx_source);
            pvalid = true;
        } else if (!strcmp(s[1], "pip_en_mask")) {
            uint32_t vid_mix_idx   = strtoul(s[2], NULL, 0);
            uint32_t vid_mix_mask  = strtoul(s[3], NULL, 0);
            if (vid_mix_idx>0) {
              printf("\n Vid Mix Index >0 not yet supported\n");
              vid_mix_idx = 0;
            }
            HW_API::initVidProc();
            HW_API::setPipEnableMask(vid_mix_idx, vid_mix_mask);
            pvalid = true;
        } else if (!strcmp(s[1], "mixer_out_sel")) {
            uint32_t vid_mix_idx   = strtoul(s[2], NULL, 0);
            uint32_t select        = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setMixOutSelect(vid_mix_idx, select);
            pvalid = true;
        } else if (!strcmp(s[1], "blend_color")) {
            uint32_t vid_mix_idx   = strtoul(s[2], NULL, 0);
            uint32_t color_fmt     = strtoul(s[3], NULL, 0);
            HW_API::initVidProc();
            HW_API::setBldColorSpace(vid_mix_idx, color_fmt);
            pvalid = true;
        }
    } else if (n == 5) {
        if (!strcmp(s[1], "sc_rw")) {
            uint32_t sc_path_idx  = strtoul(s[2], NULL, 0)%(HW_API::SC_NUM_PATHS-1);
            uint32_t sc_comp_idx  = strtoul(s[3], NULL, 0)%(HW_API::SC_NUM_COMPONENTS);
            uint32_t reg          = strtoul(s[4], NULL, 0);
            uint32_t data = HW_API::readScalerReg(sc_path_idx, sc_comp_idx, reg);
            printf("Read Scaler Path %u Component %u Register %u == 0x%08x , %u\n", sc_path_idx, sc_comp_idx, reg, data, data);
            pvalid = true;
        } else if (!strcmp(s[1], "pip_en")) {
            uint32_t vid_mix_idx      = strtoul(s[2], NULL, 0);
            uint32_t vid_mix_inp_idx  = strtoul(s[3], NULL, 0);
            uint32_t vid_mix_inp_en   = strtoul(s[4], NULL, 0)%2;
            if (vid_mix_idx>0) {
              printf("\n Vid Mix Index >0 not yet supported\n");
              vid_mix_idx = 0;
            }
            HW_API::initVidProc();
            HW_API::setPipEnable(vid_mix_idx, vid_mix_inp_idx, vid_mix_inp_en);
            pvalid = true;
        }
    } else if (n == 6) {
        if (!strcmp(s[1], "sc_rw")) {
            uint32_t sc_path_idx  = strtoul(s[2], NULL, 0)%(HW_API::SC_NUM_PATHS-1);
            uint32_t sc_comp_idx  = strtoul(s[3], NULL, 0)%(HW_API::SC_NUM_COMPONENTS);
            uint32_t reg          = strtoul(s[4], NULL, 0);
            uint32_t data         = strtoul(s[5], NULL, 0);
            HW_API::writeScalerReg(sc_path_idx, sc_comp_idx, reg, data);
            printf("Write Scaler Path %u Component %u Register %u == 0x%08x , %u\n", sc_path_idx, sc_comp_idx, reg, data, data);
            pvalid = true;
        } else if (!strcmp(s[1], "vidmix_phase")) {
            uint32_t vid_mix_idx        = strtoul(s[2], NULL, 0)%1;
            uint32_t output_raster_num  = strtoul(s[3], NULL, 0)%2;
            uint32_t h_phase            = strtoul(s[4], NULL, 0);
            uint32_t v_phase            = strtoul(s[5], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcVidMixRasterPhase(vid_mix_idx, output_raster_num, h_phase, v_phase);
            pvalid = true;
        } else if (!strcmp(s[1], "sc_raster_phase")) {
            uint32_t path   = strtoul(s[2], NULL, 0);
            uint32_t out    = strtoul(s[3], NULL, 0)%2;
            uint32_t hphase  = strtoul(s[4], NULL, 0);
            uint32_t vphase  = strtoul(s[5], NULL, 0);
            HW_API::initVidProc();
            HW_API::initScalerPath(path);
            HW_API::setScalerRasterPhase(path,out,hphase,vphase);
            pvalid = true;
        } else if (!strcmp(s[1], "vidmix_border_colour")) {
            uint32_t vid_mix_idx  = strtoul(s[2], NULL, 0);
            uint32_t colour_g_y   = strtoul(s[3], NULL, 0);
            uint32_t colour_b_cb  = strtoul(s[4], NULL, 0);
            uint32_t colour_r_cr  = strtoul(s[5], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcPipBorderColour(vid_mix_idx, colour_g_y, colour_b_cb, colour_r_cr);
            pvalid = true;
        }
    } else if (n == 7) {
        if (!strcmp(s[1], "pip_region")) {
            uint32_t idx          = strtoul(s[2], NULL, 0);
            uint32_t h_start      = strtoul(s[3], NULL, 0);
            uint32_t h_stop       = strtoul(s[4], NULL, 0);
            uint32_t v_start      = strtoul(s[5], NULL, 0);
            uint32_t v_stop       = strtoul(s[6], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcPipArea(idx, h_start, h_stop, v_start, v_stop, v_start, v_stop);
            printf("PIP Region (Progressive) set to %u,%u to %u,%u\n\n", h_start, v_start, h_stop, v_stop);
            pvalid = true;
        }
    } else if (n == 9) {
        if (!strcmp(s[1], "pip_region")) {
            uint32_t idx          = strtoul(s[2], NULL, 0);
            uint32_t h_start      = strtoul(s[3], NULL, 0);
            uint32_t h_stop       = strtoul(s[4], NULL, 0);
            uint32_t v_start0     = strtoul(s[5], NULL, 0);
            uint32_t v_stop0      = strtoul(s[6], NULL, 0);
            uint32_t v_start1     = strtoul(s[7], NULL, 0);
            uint32_t v_stop1      = strtoul(s[8], NULL, 0);
            HW_API::initVidProc();
            HW_API::setVidProcPipArea(idx,h_start, h_stop, v_start0, v_stop0, v_start1, v_stop1);
            printf("PIP Region (Interlaced) set to Field 0 = %u,%u to %u,%u  Field 1 = %u,%u to %u,%u \n\n", h_start, v_start0, h_stop, v_stop0, h_start, v_start1, h_stop, v_stop1);
            pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

static int
execAxiDma(int n, char *s[])
{
    bool pvalid = false;

    if (n == 1) {
        printf("Usage: %s address <scaler_path>\n", s[0]);
        printf("       %s convert <scaler_path> <bmp_file_input> <frame_file_output>\n", s[0]);
        printf("       %s transfer <index> <rd_src_addr> <wr_dst_addr> <wr_burst_size_in_bytes> <bytes_to_transfer>\n", s[0]);
        printf("       %s loii <scaler_path> <ps_ddr_addr> <image_bytes>\n", s[0]);
        printf("       %s loii <scaler_path> <enable>\n", s[0]);
        pvalid = true;
    } else if (n == 3) {
        if (!strcmp(s[1], "address")) {
          HW_API::initFPGABuildID();
          HW_API::initAxiDmaMemory();
          uint32_t scaler_path = strtoul(s[2], NULL, 0);
          HW_API::initScalerPath(scaler_path);
          uint8_t ddr_bank;
          uint32_t address;
          HW_API::getScalerLossOfInputImageAddress(scaler_path, &ddr_bank, &address);
          printf("Scaler %u Loss of Input Image Bank: %u, Address: 0x%x\n", scaler_path, ddr_bank, address);
          pvalid = true;
        }
    } else if (n == 4) {
        if (!strcmp(s[1], "loii")) {
          HW_API::initFPGABuildID();
          HW_API::initAxiDmaMemory();
          uint32_t scaler_path = strtoul(s[2], NULL, 0);
          HW_API::initScalerPath(scaler_path);
          bool enable = strtoul(s[3], NULL, 0);
          HW_API::setScalerLossOfInputImageEnable(scaler_path, enable);
          printf("%s Scaler %u Loss of Input Image.\n", enable?"Enabling":"Disabling", scaler_path);
          pvalid = true;
        }
    } else if (n == 5) {
        if (!strcmp(s[1], "convert")) {
          HW_API::initFPGABuildID();
          HW_API::initAxiDmaMemory();
          uint32_t scaler_path = strtoul(s[2], NULL, 0);
          HW_API::initScalerPath(scaler_path);
          const char* bmp_file_input = s[3];
          const char* frame_file_output = s[4];
          HW_API::writeAxiDmaMemoryConvertBmpFormat(scaler_path, bmp_file_input, frame_file_output);
          printf("Convert BMP file = %s, into scaler %u buffer frame file = %s \n", bmp_file_input, scaler_path, frame_file_output);
          pvalid = true;
        } else if (!strcmp(s[1], "loii")) {
          HW_API::initFPGABuildID();
          HW_API::initAxiDmaMemory();
          uint32_t scaler_path = strtoul(s[2], NULL, 0);
          HW_API::initScalerPath(scaler_path);
          uint32_t ps_ddr_addr = strtoul(s[3], NULL, 0);
          uint32_t image_bytes = strtoul(s[4], NULL, 0);
          HW_API::setScalerLossOfInputImage(scaler_path, ps_ddr_addr, image_bytes);
          printf("Tranferring Scaler %u Loss of Input Image from PS DDR Address: 0x%x, Image Bytes: 0x%x\n", scaler_path, ps_ddr_addr, image_bytes);
          pvalid = true;
        }
    } else if (n == 7) {
        if (!strcmp(s[1], "transfer")) {
          HW_API::initFPGABuildID();
          HW_API::initAxiDmaMemory();
          uint32_t index = strtoul(s[2], NULL, 0);
          uint32_t rd_src_addr = strtoul(s[3], NULL, 0);
          uint32_t wr_dst_addr = strtoul(s[4], NULL, 0);
          uint32_t wr_burst_size_in_bytes = strtoul(s[5], NULL, 0);
          uint32_t bytes_to_transfer = strtoul(s[6], NULL, 0);
          HW_API::setAxiDmaMemoryDmaReadToDdrWrite(index, rd_src_addr, wr_dst_addr, wr_burst_size_in_bytes, bytes_to_transfer);
          printf("Configure AXI DMA %u read to DDR write with rd_src_addr = 0x%08x, wr_dst_addr = 0x%08x, wr_burst_size_in_bytes = 0x%08x, bytes_to_transfer = 0x%08x\n", index, rd_src_addr, wr_dst_addr, wr_burst_size_in_bytes, bytes_to_transfer);
          pvalid = true;
        }
    }
    if (!pvalid) {
        printf("Invalid\n");
    }
    return 0;
}

/* -- Subcommand List -- */

static SubCommand cmds[] = {
    {"build_info", execBuildInfo},
    {"bist", execBIST},
    {"xge_drp_rw", execXGEDRPRW},
    {"drpnl_rw", execDRPNLRW},
    {"hdmi_ip_rw", execHDMIIPRW},
    {"xge_mac_rw", execXGEMacRW},
    {"xge_if_rw", execXGEIfRW},
    {"xge_tx_rw", execXGETxRW},
    {"xge_rx_rw", execXGERxRW},
    {"xge_iptx_rw", execXGEIPTxRW},
    {"xge_iprx_rw", execXGEIPRxRW},
    {"fpga_id_rw", execFPGAIDRW},
    {"xbar_config_rw", execXBARCONFIGRW},
    {"sc_a_rw", execSCARW},
    {"sc_b_rw", execSCBRW},
    {"sc_rs_rw", execSCRSRW},
    {"sc_ms_rw", execSCMSRW},
    {"sc_wp_rw", execSCWPRW},
    {"sc_pl_rw", execSCPLRW},
    {"mtest_rw", execMTestRW},
    {"icron_usb_rw", execIcronUSBRW},
    {"audio_mixer_rw", execAMixerRW},
    {"ptp_rw", execPTPRW},
    {"gen_rw", execGeneralRW},
    {"inter_rw", execInterRW},
    {"sdi_12g_rw", execSDI12GRW},
    {"genlock_rw", execGenlockRW},
    {"axidma_ip_rw", execAxiDmaIpRW},
    {"axidma_mem_rw", execAxiDmaMemRW},
    {"mtest", execMTest},
    {"temac", execTEMAC},
    {"xge_mac", execXGEMac},
    {"xge_xcvr", execXGEXcvr},
    {"xge_if", execXGEIf},
    {"xge_rx", execXGERx},
    {"xge_tx", execXGETx},
    {"ibc_test", execIBCTest},
    {"scale", execScaler},
    {"hdmi", execHdmi},
    {"xbar_config", execXBARCONFIG},
    {"audio_status", execAUDSTATUS},
    {"audio_gain", execAUDGAIN},
    {"tico", execTico},
    {"audio_mixer", execAMixer},
    {"osd", execOSD},
    {"icron", execIcron},
    {"gen", execGen},
    {"inter", execInter},
    {"sdi_12g", execSDI12G},
    {"genlock", execGenlock},
    {"vid_proc", execVidProc},
    {"axidma", execAxiDma},
    {NULL, 0}
};

/* -- Main Control -- */

int
hw_main(int argc, char *argv[]) {
    int stat = 1;

    // Check arguments
    if (argc <= 1) {
        printf("\n");
        printf("Usage: hw <subcommand> [options]\n");
        printf("\n");
        printf("  Valid subcommands are:\n\n");

        SubCommand *cmd;
        for (cmd = cmds; cmd->command != NULL; cmd++) {
            printf("    %s\n", cmd->command);
        }
        printf("\n");
        return stat;
    }

    // Command Parsing
    SubCommand *cmd = cmds;

    while (cmd->command) {
        if (!strcmp(cmd->command, argv[1])) {
            //found command
            stat = cmd->function(argc-1, argv+1);
            break;
        }
        cmd++;
    }

    if (stat != 0) {
        printf("Invalid subcommand\n");
    }

    return stat;


}

// vim:set sts=2 sw=2 expandtab fileformat=unix:
