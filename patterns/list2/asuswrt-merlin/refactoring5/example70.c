#ifdef RTCONFIG_WIRELESSREPEATER
if(sw_mode == SW_MODE_REPEATER || sw_mode == SW_MODE_HOTSPOT)
			sprintf(buf, "%s%s%s%s%s%s%s" ,buf , "Connection: close\r\n", "Location:http://", dut_addr, "/QIS_default.cgi?flag=sitesurvey", "\r\nContent-Type: text/plain\r\n", "\r\n<html></html>\r\n");
		else
		
#endif
			sprintf(buf, "%s%s%s%s%s%s%s" ,buf , "Connection: close\r\n", "Location:http://", dut_addr, "/QIS_default.cgi?flag=welcome", "\r\nContent-Type: text/plain\r\n", "\r\n<html></html>\r\n");
