struct LibraryFunction PlatformLibrary_flightbatterystate[] =
{
#ifndef NO_FP
	{ FlightBatteryState_Get,	"void FlightBatteryStateGet(FlightBatteryStateData *);" },
#endif
	{ NULL, NULL }
};
