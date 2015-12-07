#ifdef RTCONFIG_TFAT
if(!strncmp(type, "vfat", 4)){
				ret = eval("mount", "-t", "tfat", "-o", options, mnt_dev, mnt_dir);
				if(ret != 0){
					syslog(LOG_INFO, "USB %s(%s) failed to mount at the first try!" , mnt_dev, type);
					TRACE_PT("USB %s(%s) failed to mount at the first try!\n", mnt_dev, type);
				}
			}

			else
#endif
			{
				ret = mount(mnt_dev, mnt_dir, type, flags, options[0] ? options : "");
				if(ret != 0){
					if(strncmp(type, "ext", 3)){
						syslog(LOG_INFO, "USB %s(%s) failed to mount at the first try!", mnt_dev, type);
						TRACE_PT("USB %s(%s) failed to mount At the first try!\n", mnt_dev, type);
						logmessage("usb", "USB %s(%s) failed to mount At the first try!\n", mnt_dev, type);
					}
					else{
						if(!strcmp(type, "ext4")){
							snprintf(type, 16, "ext3");
							ret = mount(mnt_dev, mnt_dir, type, flags, options[0] ? options : "");
						}

						if(ret != 0 && !strcmp(type, "ext3")){
							snprintf(type, 16, "ext2");
							ret = mount(mnt_dev, mnt_dir, type, flags, options[0] ? options : "");
						}

						if(ret != 0 && !strcmp(type, "ext2")){
							snprintf(type, 16, "ext");
							ret = mount(mnt_dev, mnt_dir, type, flags, options[0] ? options : "");
						}

						if(ret != 0){
							syslog(LOG_INFO, "USB %s(ext) failed to mount at the first try!", mnt_dev);
							TRACE_PT("USB %s(ext) failed to mount at the first try!\n", mnt_dev);
							logmessage("usb", "USB %s(ext) failed to mount at the first try!\n", mnt_dev);
						}
					}
				}
			}
