#ifdef SDIO_STA_STBITERR
while(!__HAL_SD_SDIO_GET_FLAG(hsd, SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DATAEND | SDIO_FLAG_STBITERR))
#else /* SDIO_STA_STBITERR not defined */
    while(!__HAL_SD_SDIO_GET_FLAG(hsd, SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DATAEND))
#endif /* SDIO_STA_STBITERR */
    {
      if (__HAL_SD_SDIO_GET_FLAG(hsd, SDIO_FLAG_RXFIFOHF))
      {
        /* Read data from SDIO Rx FIFO */
        for (count = 0; count < 8; count++)
        {
          *(tempbuff + count) = SDIO_ReadFIFO(hsd->Instance);
        }
        
        tempbuff += 8;
      }
    }
