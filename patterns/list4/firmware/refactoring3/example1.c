switch (SectorAddress & MAL_MASK)
  {
    case INTERNAL_FLASH_BASE:
      pMAL_Erase = FLASH_If_Erase;
      break;

#ifdef SPARK_SFLASH_ENABLE
    case SPI_FLASH_BASE:
      pMAL_Erase = SPI_If_Erase;
      break;
#endif

    default:
      return MAL_FAIL;
  }
