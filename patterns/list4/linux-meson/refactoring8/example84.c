static am_csi2_t am_csi2_para[] =
{
    {
        //inited when probe
        .id = -1,
        .pdev = NULL,
#ifdef CONFIG_MEM_MIPI
        .irq = -1,
#endif
        .pbufAddr = 0x81000000,
        .decbuf_size = 0x70000,

        //inited when start csi2
        .client = NULL,
        .ui_val = 0,
        .hs_freq = 0,
        .clock_lane_mode = 0,
        .mirror = 0,
        .frame_rate = 0,
        .status = AM_CSI2_FLAG_NULL,

        .output = {0},
        .input = {0},
        .ops = NULL,
    },
};
