static struct clk_lookup pxa25x_clkregs[] = {
	INIT_CLKREG(&clk_pxa25x_lcd, "pxa2xx-fb", NULL),
	INIT_CLKREG(&clk_pxa25x_ffuart, "pxa2xx-uart.0", NULL),
	INIT_CLKREG(&clk_pxa25x_btuart, "pxa2xx-uart.1", NULL),
	INIT_CLKREG(&clk_pxa25x_stuart, "pxa2xx-uart.2", NULL),
	INIT_CLKREG(&clk_pxa25x_usb, "pxa25x-udc", NULL),
	INIT_CLKREG(&clk_pxa25x_mmc, "pxa2xx-mci.0", NULL),
	INIT_CLKREG(&clk_pxa25x_i2c, "pxa2xx-i2c.0", NULL),
	INIT_CLKREG(&clk_pxa25x_ssp, "pxa25x-ssp.0", NULL),
	INIT_CLKREG(&clk_pxa25x_nssp, "pxa25x-nssp.1", NULL),
	INIT_CLKREG(&clk_pxa25x_assp, "pxa25x-nssp.2", NULL),
	INIT_CLKREG(&clk_pxa25x_pwm0, "pxa25x-pwm.0", NULL),
	INIT_CLKREG(&clk_pxa25x_pwm1, "pxa25x-pwm.1", NULL),
	INIT_CLKREG(&clk_pxa25x_i2s, "pxa2xx-i2s", NULL),
	INIT_CLKREG(&clk_pxa25x_stuart, "pxa2xx-ir", "UARTCLK"),
	INIT_CLKREG(&clk_pxa25x_ficp, "pxa2xx-ir", "FICPCLK"),
	INIT_CLKREG(&clk_pxa25x_ac97, NULL, "AC97CLK"),
	INIT_CLKREG(&clk_pxa25x_gpio11, NULL, "GPIO11_CLK"),
	INIT_CLKREG(&clk_pxa25x_gpio12, NULL, "GPIO12_CLK"),
	INIT_CLKREG(&clk_pxa25x_mem, "pxa2xx-pcmcia", NULL),
#ifdef CONFIG_CPU_PXA26x
	INIT_CLKREG(&clk_dummy, "pxa26x-gpio", NULL),
#else
	INIT_CLKREG(&clk_dummy, "pxa25x-gpio", NULL),
#endif
	INIT_CLKREG(&clk_dummy, "sa1100-rtc", NULL),
};
