if (
#ifndef MNG_SKIPCHUNK_FRAM
       (pData->iFramemode == 4) ||    /* insert background layer after a new frame */
#endif
        (!pData->iLayerseq))           /* and certainly before the very first layer */
      iRetcode = load_bkgdlayer (pData);
