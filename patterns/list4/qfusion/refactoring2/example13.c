#ifdef HAVE_STAT
if(stat(oss_driver, &buf) == 0)
#endif
                AppendAllDevicesList(oss_device);
