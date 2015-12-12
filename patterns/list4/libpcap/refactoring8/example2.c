static const struct config_table debug_tab[] = {
            { "PKT.DEBUG",       ARG_ATOI,   &pcap_pkt_debug    },
            { "PKT.VECTOR",      ARG_ATOX_W, NULL               },
            { "NDIS.DEBUG",      ARG_ATOI,   NULL               },
#ifdef USE_32BIT_DRIVERS
            { "3C503.DEBUG",     ARG_ATOI,   &ei_debug          },
            { "3C503.IO_BASE",   ARG_ATOX_W, &el2_dev.base_addr },
            { "3C503.MEMORY",    ARG_ATOX_W, &el2_dev.mem_start },
            { "3C503.IRQ",       ARG_ATOI,   &el2_dev.irq       },
            { "3C505.DEBUG",     ARG_ATOI,   NULL               },
            { "3C505.BASE",      ARG_ATOX_W, NULL               },
            { "3C507.DEBUG",     ARG_ATOI,   NULL               },
            { "3C509.DEBUG",     ARG_ATOI,   &el3_debug         },
            { "3C509.ILOOP",     ARG_ATOI,   &el3_max_loop      },
            { "3C529.DEBUG",     ARG_ATOI,   NULL               },
            { "3C575.DEBUG",     ARG_ATOI,   &debug_3c575       },
            { "3C59X.DEBUG",     ARG_ATOI,   &vortex_debug      },
            { "3C59X.IFACE0",    ARG_ATOI,   &vortex_options[0] },
            { "3C59X.IFACE1",    ARG_ATOI,   &vortex_options[1] },
            { "3C59X.IFACE2",    ARG_ATOI,   &vortex_options[2] },
            { "3C59X.IFACE3",    ARG_ATOI,   &vortex_options[3] },
            { "3C90X.DEBUG",     ARG_ATOX_W, &tc90xbc_debug     },
            { "ACCT.DEBUG",      ARG_ATOI,   &ethpk_debug       },
            { "CS89.DEBUG",      ARG_ATOI,   &cs89_debug        },
            { "RTL8139.DEBUG",   ARG_ATOI,   &rtl8139_debug     },
        /*  { "RTL8139.FDUPLEX", ARG_ATOI,   &rtl8139_options   }, */
            { "SMC.DEBUG",       ARG_ATOI,   &ei_debug          },
        /*  { "E100.DEBUG",      ARG_ATOI,   &e100_debug        }, */
            { "PCI.DEBUG",       ARG_ATOI,   &pci_debug         },
            { "BIOS32.DEBUG",    ARG_ATOI,   &bios32_debug      },
            { "IRQ.DEBUG",       ARG_ATOI,   &irq_debug         },
            { "TIMER.IRQ",       ARG_ATOI,   &timer_irq         },
#endif
            { NULL }
          };
