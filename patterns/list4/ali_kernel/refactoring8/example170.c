static struct insn opcode[] = {
#ifdef CONFIG_64BIT
	{ "lmd", 0xef, INSTR_SS_RRRDRD3 },
#endif
	{ "spm", 0x04, INSTR_RR_R0 },
	{ "balr", 0x05, INSTR_RR_RR },
	{ "bctr", 0x06, INSTR_RR_RR },
	{ "bcr", 0x07, INSTR_RR_UR },
	{ "svc", 0x0a, INSTR_RR_U0 },
	{ "bsm", 0x0b, INSTR_RR_RR },
	{ "bassm", 0x0c, INSTR_RR_RR },
	{ "basr", 0x0d, INSTR_RR_RR },
	{ "mvcl", 0x0e, INSTR_RR_RR },
	{ "clcl", 0x0f, INSTR_RR_RR },
	{ "lpr", 0x10, INSTR_RR_RR },
	{ "lnr", 0x11, INSTR_RR_RR },
	{ "ltr", 0x12, INSTR_RR_RR },
	{ "lcr", 0x13, INSTR_RR_RR },
	{ "nr", 0x14, INSTR_RR_RR },
	{ "clr", 0x15, INSTR_RR_RR },
	{ "or", 0x16, INSTR_RR_RR },
	{ "xr", 0x17, INSTR_RR_RR },
	{ "lr", 0x18, INSTR_RR_RR },
	{ "cr", 0x19, INSTR_RR_RR },
	{ "ar", 0x1a, INSTR_RR_RR },
	{ "sr", 0x1b, INSTR_RR_RR },
	{ "mr", 0x1c, INSTR_RR_RR },
	{ "dr", 0x1d, INSTR_RR_RR },
	{ "alr", 0x1e, INSTR_RR_RR },
	{ "slr", 0x1f, INSTR_RR_RR },
	{ "lpdr", 0x20, INSTR_RR_FF },
	{ "lndr", 0x21, INSTR_RR_FF },
	{ "ltdr", 0x22, INSTR_RR_FF },
	{ "lcdr", 0x23, INSTR_RR_FF },
	{ "hdr", 0x24, INSTR_RR_FF },
	{ "ldxr", 0x25, INSTR_RR_FF },
	{ "lrdr", 0x25, INSTR_RR_FF },
	{ "mxr", 0x26, INSTR_RR_FF },
	{ "mxdr", 0x27, INSTR_RR_FF },
	{ "ldr", 0x28, INSTR_RR_FF },
	{ "cdr", 0x29, INSTR_RR_FF },
	{ "adr", 0x2a, INSTR_RR_FF },
	{ "sdr", 0x2b, INSTR_RR_FF },
	{ "mdr", 0x2c, INSTR_RR_FF },
	{ "ddr", 0x2d, INSTR_RR_FF },
	{ "awr", 0x2e, INSTR_RR_FF },
	{ "swr", 0x2f, INSTR_RR_FF },
	{ "lper", 0x30, INSTR_RR_FF },
	{ "lner", 0x31, INSTR_RR_FF },
	{ "lter", 0x32, INSTR_RR_FF },
	{ "lcer", 0x33, INSTR_RR_FF },
	{ "her", 0x34, INSTR_RR_FF },
	{ "ledr", 0x35, INSTR_RR_FF },
	{ "lrer", 0x35, INSTR_RR_FF },
	{ "axr", 0x36, INSTR_RR_FF },
	{ "sxr", 0x37, INSTR_RR_FF },
	{ "ler", 0x38, INSTR_RR_FF },
	{ "cer", 0x39, INSTR_RR_FF },
	{ "aer", 0x3a, INSTR_RR_FF },
	{ "ser", 0x3b, INSTR_RR_FF },
	{ "mder", 0x3c, INSTR_RR_FF },
	{ "mer", 0x3c, INSTR_RR_FF },
	{ "der", 0x3d, INSTR_RR_FF },
	{ "aur", 0x3e, INSTR_RR_FF },
	{ "sur", 0x3f, INSTR_RR_FF },
	{ "sth", 0x40, INSTR_RX_RRRD },
	{ "la", 0x41, INSTR_RX_RRRD },
	{ "stc", 0x42, INSTR_RX_RRRD },
	{ "ic", 0x43, INSTR_RX_RRRD },
	{ "ex", 0x44, INSTR_RX_RRRD },
	{ "bal", 0x45, INSTR_RX_RRRD },
	{ "bct", 0x46, INSTR_RX_RRRD },
	{ "bc", 0x47, INSTR_RX_URRD },
	{ "lh", 0x48, INSTR_RX_RRRD },
	{ "ch", 0x49, INSTR_RX_RRRD },
	{ "ah", 0x4a, INSTR_RX_RRRD },
	{ "sh", 0x4b, INSTR_RX_RRRD },
	{ "mh", 0x4c, INSTR_RX_RRRD },
	{ "bas", 0x4d, INSTR_RX_RRRD },
	{ "cvd", 0x4e, INSTR_RX_RRRD },
	{ "cvb", 0x4f, INSTR_RX_RRRD },
	{ "st", 0x50, INSTR_RX_RRRD },
	{ "lae", 0x51, INSTR_RX_RRRD },
	{ "n", 0x54, INSTR_RX_RRRD },
	{ "cl", 0x55, INSTR_RX_RRRD },
	{ "o", 0x56, INSTR_RX_RRRD },
	{ "x", 0x57, INSTR_RX_RRRD },
	{ "l", 0x58, INSTR_RX_RRRD },
	{ "c", 0x59, INSTR_RX_RRRD },
	{ "a", 0x5a, INSTR_RX_RRRD },
	{ "s", 0x5b, INSTR_RX_RRRD },
	{ "m", 0x5c, INSTR_RX_RRRD },
	{ "d", 0x5d, INSTR_RX_RRRD },
	{ "al", 0x5e, INSTR_RX_RRRD },
	{ "sl", 0x5f, INSTR_RX_RRRD },
	{ "std", 0x60, INSTR_RX_FRRD },
	{ "mxd", 0x67, INSTR_RX_FRRD },
	{ "ld", 0x68, INSTR_RX_FRRD },
	{ "cd", 0x69, INSTR_RX_FRRD },
	{ "ad", 0x6a, INSTR_RX_FRRD },
	{ "sd", 0x6b, INSTR_RX_FRRD },
	{ "md", 0x6c, INSTR_RX_FRRD },
	{ "dd", 0x6d, INSTR_RX_FRRD },
	{ "aw", 0x6e, INSTR_RX_FRRD },
	{ "sw", 0x6f, INSTR_RX_FRRD },
	{ "ste", 0x70, INSTR_RX_FRRD },
	{ "ms", 0x71, INSTR_RX_RRRD },
	{ "le", 0x78, INSTR_RX_FRRD },
	{ "ce", 0x79, INSTR_RX_FRRD },
	{ "ae", 0x7a, INSTR_RX_FRRD },
	{ "se", 0x7b, INSTR_RX_FRRD },
	{ "mde", 0x7c, INSTR_RX_FRRD },
	{ "me", 0x7c, INSTR_RX_FRRD },
	{ "de", 0x7d, INSTR_RX_FRRD },
	{ "au", 0x7e, INSTR_RX_FRRD },
	{ "su", 0x7f, INSTR_RX_FRRD },
	{ "ssm", 0x80, INSTR_S_RD },
	{ "lpsw", 0x82, INSTR_S_RD },
	{ "diag", 0x83, INSTR_RS_RRRD },
	{ "brxh", 0x84, INSTR_RSI_RRP },
	{ "brxle", 0x85, INSTR_RSI_RRP },
	{ "bxh", 0x86, INSTR_RS_RRRD },
	{ "bxle", 0x87, INSTR_RS_RRRD },
	{ "srl", 0x88, INSTR_RS_R0RD },
	{ "sll", 0x89, INSTR_RS_R0RD },
	{ "sra", 0x8a, INSTR_RS_R0RD },
	{ "sla", 0x8b, INSTR_RS_R0RD },
	{ "srdl", 0x8c, INSTR_RS_R0RD },
	{ "sldl", 0x8d, INSTR_RS_R0RD },
	{ "srda", 0x8e, INSTR_RS_R0RD },
	{ "slda", 0x8f, INSTR_RS_R0RD },
	{ "stm", 0x90, INSTR_RS_RRRD },
	{ "tm", 0x91, INSTR_SI_URD },
	{ "mvi", 0x92, INSTR_SI_URD },
	{ "ts", 0x93, INSTR_S_RD },
	{ "ni", 0x94, INSTR_SI_URD },
	{ "cli", 0x95, INSTR_SI_URD },
	{ "oi", 0x96, INSTR_SI_URD },
	{ "xi", 0x97, INSTR_SI_URD },
	{ "lm", 0x98, INSTR_RS_RRRD },
	{ "trace", 0x99, INSTR_RS_RRRD },
	{ "lam", 0x9a, INSTR_RS_AARD },
	{ "stam", 0x9b, INSTR_RS_AARD },
	{ "mvcle", 0xa8, INSTR_RS_RRRD },
	{ "clcle", 0xa9, INSTR_RS_RRRD },
	{ "stnsm", 0xac, INSTR_SI_URD },
	{ "stosm", 0xad, INSTR_SI_URD },
	{ "sigp", 0xae, INSTR_RS_RRRD },
	{ "mc", 0xaf, INSTR_SI_URD },
	{ "lra", 0xb1, INSTR_RX_RRRD },
	{ "stctl", 0xb6, INSTR_RS_CCRD },
	{ "lctl", 0xb7, INSTR_RS_CCRD },
	{ "cs", 0xba, INSTR_RS_RRRD },
	{ "cds", 0xbb, INSTR_RS_RRRD },
	{ "clm", 0xbd, INSTR_RS_RURD },
	{ "stcm", 0xbe, INSTR_RS_RURD },
	{ "icm", 0xbf, INSTR_RS_RURD },
	{ "mvn", 0xd1, INSTR_SS_L0RDRD },
	{ "mvc", 0xd2, INSTR_SS_L0RDRD },
	{ "mvz", 0xd3, INSTR_SS_L0RDRD },
	{ "nc", 0xd4, INSTR_SS_L0RDRD },
	{ "clc", 0xd5, INSTR_SS_L0RDRD },
	{ "oc", 0xd6, INSTR_SS_L0RDRD },
	{ "xc", 0xd7, INSTR_SS_L0RDRD },
	{ "mvck", 0xd9, INSTR_SS_RRRDRD },
	{ "mvcp", 0xda, INSTR_SS_RRRDRD },
	{ "mvcs", 0xdb, INSTR_SS_RRRDRD },
	{ "tr", 0xdc, INSTR_SS_L0RDRD },
	{ "trt", 0xdd, INSTR_SS_L0RDRD },
	{ "ed", 0xde, INSTR_SS_L0RDRD },
	{ "edmk", 0xdf, INSTR_SS_L0RDRD },
	{ "pku", 0xe1, INSTR_SS_L0RDRD },
	{ "unpku", 0xe2, INSTR_SS_L0RDRD },
	{ "mvcin", 0xe8, INSTR_SS_L0RDRD },
	{ "pka", 0xe9, INSTR_SS_L0RDRD },
	{ "unpka", 0xea, INSTR_SS_L0RDRD },
	{ "plo", 0xee, INSTR_SS_RRRDRD2 },
	{ "srp", 0xf0, INSTR_SS_LIRDRD },
	{ "mvo", 0xf1, INSTR_SS_LLRDRD },
	{ "pack", 0xf2, INSTR_SS_LLRDRD },
	{ "unpk", 0xf3, INSTR_SS_LLRDRD },
	{ "zap", 0xf8, INSTR_SS_LLRDRD },
	{ "cp", 0xf9, INSTR_SS_LLRDRD },
	{ "ap", 0xfa, INSTR_SS_LLRDRD },
	{ "sp", 0xfb, INSTR_SS_LLRDRD },
	{ "mp", 0xfc, INSTR_SS_LLRDRD },
	{ "dp", 0xfd, INSTR_SS_LLRDRD },
	{ "", 0, INSTR_INVALID }
};