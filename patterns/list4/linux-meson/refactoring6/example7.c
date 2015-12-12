if (!(vf->type & (VIDTYPE_VIU_422 | VIDTYPE_VIU_444 | VIDTYPE_VIU_NV21)) || (vf->type & VIDTYPE_INTERLACE) || ppmgr_device.disable_prot
#ifdef CONFIG_POST_PROCESS_MANAGER_PPSCALER
                || amvideo_get_scaler_mode()
#endif
#ifdef CONFIG_V4L_AMLOGIC_VIDEO
                || ppmgr_device.receiver
#endif
                ) {
                    ppmgr_device.use_prot = 0;
                    set_video_angle(0);
                    //ppmgr_device.angle = ppmgr_device.global_angle;
                    ppmgr_device.videoangle = (ppmgr_device.angle + ppmgr_device.orientation) % 4;
                    set_property_change(1);
                } else {
                    ppmgr_device.use_prot = 1;
                    set_video_angle(ppmgr_device.global_angle);
                    //ppmgr_device.angle = 0;
                    ppmgr_device.videoangle = (ppmgr_device.angle + ppmgr_device.orientation) % 4;
                    set_property_change(1);
                }
