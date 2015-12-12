#if SYNC_FENCE_KHR_SHORTCUT == 1
if (sync_master->type != EGL_SYNC_FENCE_KHR)
#endif
   {
      RPC_CALL1(eglIntDestroySync_impl,
                thread,
                EGLINTDESTROYSYNC_ID,
                RPC_UINT(sync_master->serversync));
   }
