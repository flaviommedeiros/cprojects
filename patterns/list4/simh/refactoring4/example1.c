#ifdef USE_VGI
if (rtn != MFDC_SECTOR_LEN)
#else
                            rtn = sim_fread(sdata.u.data, 1, 256, (pDrive->uptr)->fileref);
