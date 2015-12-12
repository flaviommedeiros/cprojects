static struct mem_ops_privdata_s csi2_mem_data[]=
{
    {
#ifdef ENABLE_CACHE_MODE
        .task = NULL,
#endif
        .irq = -1,
        .dev_id = -1,        
        .hw_info = {0},
        .frame_rate = 0,
        .mirror = 0,
        .input = {0},
        .output = {0},
        .isr_tasklet = {0},
        .watchdog_cnt = 0,
        .wr_frame = NULL,
        .disable_ddr = 0,
        .reset_flag = 0,
        .done_flag = true,
        .context = NULL,
        .mipi_mem_skip = MIPI_SKIP_FRAME_NUM,
    },
};
