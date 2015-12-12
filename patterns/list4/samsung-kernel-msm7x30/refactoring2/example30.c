#ifdef CONFIG_MMC_EMBEDDED_SDIO
if (!func->card->host->embedded_sdio_data.funcs)
#endif
		sdio_free_func_cis(func);
