#ifdef CONFIG_SPI_QUP
if (lcdc_spi_client)
#endif
			schedule_work(&disp_on_delayed_work);
