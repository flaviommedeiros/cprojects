#if defined(WANT_LOCAL_OMX) && 0
if ((eError = vc_OMX_GetHandle(pHandle, cComponentName, pAppData, pCallBacks)) != OMX_ErrorNone)
#endif
   {
      pComp = (OMX_COMPONENTTYPE *)malloc(sizeof(OMX_COMPONENTTYPE));
      if (!pComp)
      {
         vcos_assert(0);
         return OMX_ErrorInsufficientResources;
      }
      memset(pComp, 0, sizeof(OMX_COMPONENTTYPE));
      hHandle = (OMX_HANDLETYPE)pComp;
      pComp->nSize = sizeof(OMX_COMPONENTTYPE);
      pComp->nVersion.nVersion = OMX_VERSION;
      eError = vcil_out_create_component(ilcs_get_common(ilcs_service), hHandle, cComponentName);

      if (eError == OMX_ErrorNone) {
         // Check that all function pointers have been filled in.
         // All fields should be non-zero.
         int i;
         uint32_t *p = (uint32_t *) pComp;
         for(i=0; i<sizeof(OMX_COMPONENTTYPE)>>2; i++)
            if(*p++ == 0)
               eError = OMX_ErrorInvalidComponent;

         if(eError != OMX_ErrorNone && pComp->ComponentDeInit)
            pComp->ComponentDeInit(hHandle);
      }      

      if (eError == OMX_ErrorNone) {
         eError = pComp->SetCallbacks(hHandle,pCallBacks,pAppData);
         if (eError != OMX_ErrorNone)
            pComp->ComponentDeInit(hHandle);
      }
      if (eError == OMX_ErrorNone) {
         *pHandle = hHandle;
      }
      else {
         *pHandle = NULL;
         free(pComp);
      }
   }
