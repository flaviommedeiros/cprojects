struct reglink regtable[] = {
    { QBMAPBASE, QBMAPBASE+QBMAPSIZE, &qbmap_rd, &qbmap_wr },
    { ROMBASE, ROMBASE+ROMSIZE+ROMSIZE, &rom_rd, NULL },
    { NVRBASE, NVRBASE+NVRASIZE, &nvr_rd, &nvr_wr },
    { KABASE, KABASE+KASIZE, &ka_rd, &ka_wr },
#if !defined(VAX_620)
    { QVMBASE, QVMBASE+QVMSIZE, &vc_mem_rd, &vc_mem_wr },
#endif
    { QBMBASE, QBMBASE+QBMSIZE, &qbmem_rd, &qbmem_wr },
    { 0, 0, NULL, NULL }
    };
