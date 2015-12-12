switch (SectorAddress & MAL_MASK)
  {
    case INTERNAL_FLASH_BASE:
      x = 0;
      break;

#ifdef SPARK_SFLASH_ENABLE
    case SPI_FLASH_BASE:
      x = 1;
      break;
#endif
  }
