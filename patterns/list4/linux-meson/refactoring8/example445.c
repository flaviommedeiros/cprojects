static struct clk_lookup s3c64xx_clk_lookup[] = {
	CLKDEV_INIT(NULL, "clk_uart_baud2", &clk_p),
	CLKDEV_INIT(NULL, "clk_uart_baud3", &clk_sclk_uclk.clk),
	CLKDEV_INIT("s3c-sdhci.0", "mmc_busclk.0", &clk_hsmmc0),
	CLKDEV_INIT("s3c-sdhci.1", "mmc_busclk.0", &clk_hsmmc1),
	CLKDEV_INIT("s3c-sdhci.2", "mmc_busclk.0", &clk_hsmmc2),
	CLKDEV_INIT("s3c-sdhci.0", "mmc_busclk.2", &clk_sclk_mmc0.clk),
	CLKDEV_INIT("s3c-sdhci.1", "mmc_busclk.2", &clk_sclk_mmc1.clk),
	CLKDEV_INIT("s3c-sdhci.2", "mmc_busclk.2", &clk_sclk_mmc2.clk),
	CLKDEV_INIT(NULL, "spi_busclk0", &clk_p),
	CLKDEV_INIT("s3c6410-spi.0", "spi_busclk1", &clk_sclk_spi0.clk),
	CLKDEV_INIT("s3c6410-spi.0", "spi_busclk2", &clk_48m_spi0),
	CLKDEV_INIT("s3c6410-spi.1", "spi_busclk1", &clk_sclk_spi1.clk),
	CLKDEV_INIT("s3c6410-spi.1", "spi_busclk2", &clk_48m_spi1),
	CLKDEV_INIT("samsung-i2s.0", "i2s_opclk0", &clk_i2s0),
	CLKDEV_INIT("samsung-i2s.0", "i2s_opclk1", &clk_audio_bus0.clk),
	CLKDEV_INIT("samsung-i2s.1", "i2s_opclk0", &clk_i2s1),
	CLKDEV_INIT("samsung-i2s.1", "i2s_opclk1", &clk_audio_bus1.clk),
#ifdef CONFIG_CPU_S3C6410
	CLKDEV_INIT("samsung-i2s.2", "i2s_opclk0", &clk_i2s2),
	CLKDEV_INIT("samsung-i2s.2", "i2s_opclk1", &clk_audio_bus2.clk),
#endif
};
