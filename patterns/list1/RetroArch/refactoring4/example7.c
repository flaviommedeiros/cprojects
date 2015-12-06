#ifdef __cplusplus
if (FAILED(DirectInput8Create(
      GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8,
      (void**)&g_dinput_ctx, NULL)))
#else
   if (FAILED(DirectInput8Create(
      GetModuleHandle(NULL), DIRECTINPUT_VERSION, &IID_IDirectInput8,
      (void**)&g_dinput_ctx, NULL)))
#endif
   {
      RARCH_ERR("Failed to init DirectInput.\n");
      return false;
   }
