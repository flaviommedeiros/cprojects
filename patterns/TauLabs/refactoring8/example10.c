const static struct nmea_parser nmea_parsers[] = {
	{
		.prefix = "GGA",
		.handler = nmeaProcessGPGGA,
	},
	{
		.prefix = "VTG",
		.handler = nmeaProcessGPVTG,
	},
	{
		.prefix = "GSA",
		.handler = nmeaProcessGPGSA,
	},
	{
		.prefix = "RMC",
		.handler = nmeaProcessGPRMC,
	},
#if !defined(PIOS_GPS_MINIMAL)
	{
		.prefix = "ZDA",
		.handler = nmeaProcessGPZDA,
	},
	{
		.prefix = "GSV",
		.handler = nmeaProcessGPGSV,
	},
#endif //PIOS_GPS_MINIMAL
};
