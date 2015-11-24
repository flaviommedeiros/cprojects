static const char *minion_modules[] = {
#if MINION_ROCKCHIP == 0
	"i2c-dev",
	"i2c-bcm2708",
	"spidev",
	"spi-bcm2708",
#endif
	NULL
};
