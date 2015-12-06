switch (SectorAddress & MAL_MASK)
  {
    case INTERNAL_FLASH_BASE:
      pMAL_Read = FLASH_If_Read;
      break;

#ifdef SPARK_SFLASH_ENABLE
    case SPI_FLASH_BASE:
      pMAL_Read = SPI_If_Read;
      break;
#endif

    default:
      return 0;
  }
