#if defined(RTAC1200HP)
if(unit==1)
#endif		
		if(get_radio(unit, 0))
			led_control(unit?LED_5G:LED_2G, LED_ON);	
		else
			led_control(unit?LED_5G:LED_2G, LED_OFF);
