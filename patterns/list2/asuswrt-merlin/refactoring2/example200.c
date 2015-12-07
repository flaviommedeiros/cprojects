#ifdef CONFIG_IDEDMA_ONLYDISK
if (drive->media == ide_disk)
#endif
					ide_set_dma(drive);
