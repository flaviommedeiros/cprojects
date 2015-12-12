switch (SectorAddress & MAL_MASK)
  {
    case INTERNAL_FLASH_BASE:
      pMAL_Write = FLASH_If_Write;
      break;

#ifdef SPARK_SFLASH_ENABLE
    case SPI_FLASH_BASE:
      pMAL_Write = SPI_If_Write;
      break;
#endif

    default:
      return MAL_FAIL;
  }
