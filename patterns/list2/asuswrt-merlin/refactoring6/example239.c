if(!strstr(file, ".cgi") && !strstr(file, "syslog.txt") && !(strstr(file,"uploadIconFile.tar")) && !(strstr(file,"backup_jffs.tar")) && !(strstr(file,"networkmap.tar")) && !(strstr(file,".CFG")) && !(strstr(file,".log")) && !check_if_file_exist(file)
#ifdef RTCONFIG_USB_MODEM
					&& !strstr(file, "modemlog.txt")
#endif
#ifdef RTCONFIG_DSL_TCLINUX
					&& !strstr(file, "TCC.log")
#endif
					){
				send_error( 404, "Not Found", (char*) 0, "File not found." );
				return;
			}
