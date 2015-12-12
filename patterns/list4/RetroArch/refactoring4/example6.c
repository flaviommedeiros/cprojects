#ifdef __cplusplus
if (FAILED(IDirectInput8_CreateDevice(g_ctx, inst->guidInstance, pad, NULL)))
#else
   if (FAILED(IDirectInput8_CreateDevice(g_ctx, &inst->guidInstance, pad, NULL)))
#endif
      return DIENUM_CONTINUE;
