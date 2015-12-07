#ifndef MNG_NO_16BIT_SUPPORT
if (pData->bIsRGBA16)                /* 16-bit buffer ? */
  {
    pTemp = pData->pPrevrow + (iX << 3);

    for (iZ = (pData->iDestr - pData->iDestl); iZ > 0; iZ--)
    {
      MNG_COPY (pWork, pTemp, 8);

      pWork += 8;
      pTemp += 8;
      iX++;
                                       /* reached end of bkgd-image line ? */
      if (iX >= pData->iBackimgwidth)
      {
        iX    = 0;
        pTemp = pData->pPrevrow;
      }
    }
  }
  else
#endif
  {
    pTemp = pData->pPrevrow + (iX << 2);

    for (iZ = (pData->iDestr - pData->iDestl); iZ > 0; iZ--)
    {
      MNG_COPY (pWork, pTemp, 4);

      pWork += 4;
      pTemp += 4;
      iX++;
                                       /* reached end of bkgd-image line ? */
      if (iX >= pData->iBackimgwidth)
      {
        iX    = 0;
        pTemp = pData->pPrevrow;
      }
    }
  }
