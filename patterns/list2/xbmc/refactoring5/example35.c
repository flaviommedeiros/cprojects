#ifdef MNG_INCLUDE_ANG_PROPOSAL
if (pData->eImagetype == mng_it_ang)
    {
      pData->pCurraniobj = pData->pFirstaniobj;
    } else
#endif
    {                                  /* cleanup object 0 */
      mng_reset_object_details (pData, (mng_imagep)pData->pObjzero,
                                0, 0, 0, 0, 0, 0, 0, MNG_TRUE);
    }
