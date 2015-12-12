pageConfig_t    g_addrDescriptor[SII_CRA_MAX_DEVICE_INSTANCES][SII_CRA_DEVICE_PAGE_COUNT] =
{
#if (FPGA_BUILD_NEW == 1)

    // Instance 0
    {
    { DEV_I2C_2,        DEV_PAGE_PP_0   },    // System Control and Status
    { DEV_I2C_2,        DEV_PAGE_PP_1   },    // MHL
    { DEV_I2C_2,        DEV_PAGE_PP_2   },    // System Control and Status
    { DEV_I2C_2,        DEV_PAGE_PP_3   },    // not used
    { DEV_I2C_2,        DEV_PAGE_PP_4   },    // not used
    { DEV_I2C_2,        DEV_PAGE_PP_5   },    // not used
    { DEV_I2C_2,        DEV_PAGE_PP_6   },    // not used
    { DEV_I2C_2,        DEV_PAGE_PP_7   },    // not used
    { DEV_I2C_2,        DEV_PAGE_PP_8   },    // CPI
    { DEV_I2C_2,        DEV_PAGE_PP_9   },    // Video RGB2xvYCC Reg and rvs control / VSI control and status
    { DEV_I2C_2,        DEV_PAGE_PP_A   },    // not used
    { DEV_I2C_2,        DEV_PAGE_PP_B   },    // not used
    { DEV_I2C_2,        DEV_PAGE_PP_C   },    // CBUS
    { DEV_I2C_2,        DEV_PAGE_HEAC   },    // HEAC
    { DEV_I2C_2,        DEV_PAGE_OSD    },    // OSD
    { DEV_I2C_2_OFFSET,   0x0000 + DEV_PAGE_AUDIO },    // Audio Extraction instance 1
    }
	
#else

    // Instance 0
    {
    { DEV_I2C_0,        DEV_PAGE_PP_0   },    // System Control and Status
    { DEV_I2C_0,        DEV_PAGE_PP_1   },    // MHL
    { DEV_I2C_0,        DEV_PAGE_PP_2   },    // System Control and Status
    { DEV_I2C_0,        DEV_PAGE_PP_3   },    // not used
    { DEV_I2C_0,        DEV_PAGE_PP_4   },    // not used
    { DEV_I2C_0,        DEV_PAGE_PP_5   },    // not used
    { DEV_I2C_0,        DEV_PAGE_PP_6   },    // not used
    { DEV_I2C_0,        DEV_PAGE_PP_7   },    // not used
    { DEV_I2C_0,        DEV_PAGE_PP_8   },    // CPI
    { DEV_I2C_0,        DEV_PAGE_PP_9   },    // Video RGB2xvYCC Reg and rvs control / VSI control and status
    { DEV_I2C_0,        DEV_PAGE_PP_A   },    // not used
    { DEV_I2C_0,        DEV_PAGE_PP_B   },    // not used
    { DEV_I2C_0,        DEV_PAGE_PP_C   },    // CBUS
    { DEV_I2C_0,        DEV_PAGE_HEAC   },    // HEAC
    { DEV_I2C_0,        DEV_PAGE_OSD    },    // OSD
    { DEV_I2C_0_OFFSET,   0x0000 + DEV_PAGE_AUDIO },    // Audio Extraction instance 1
    }

#endif
};
