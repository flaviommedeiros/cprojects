if(strncmp(port, CPU_PORT, 1) != 0
#ifdef RTAC87U
			&& strncmp(port, RGMII_PORT, 1) != 0
#endif
		){
			if (robo_ioctl_len(fd, 0 /* robord */, MIB_P0_PAGE + atoi(port), MIB_RX_REG, &value, 8) < 0)
				_dprintf("et ioctl SIOCGETCROBORD failed!\n");
			else{
				*rx = *rx + value;
			}
		}
