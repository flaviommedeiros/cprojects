switch (type) {
#ifndef NO_OPENVG
   case OPENVG:
   {
      VG_CLIENT_SHARED_STATE_T *shared_state;
      if (share_context) {
         shared_state = ((VG_CLIENT_STATE_T *)share_context->state)->shared_state;
         vg_client_shared_state_acquire(shared_state);
      } else {
         shared_state = vg_client_shared_state_alloc();
         if (!shared_state) {
            khrn_platform_free(context);
            return 0;
         }
      }

      context->state = vg_client_state_alloc(shared_state);
      vg_client_shared_state_release(shared_state);
      if (!context->state) {
         khrn_platform_free(context);
         return 0;
      }

      {
      CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
         /* uint64_t pid = khronos_platform_get_process_id(); */ /* unused */
      context->servercontext = RPC_UINT_RES(RPC_CALL2_RES(eglIntCreateVG_impl,
                                                             thread,
                                                             EGLINTCREATEVG_ID,
                                                             share_context ? share_context->servercontext : 0,
                                                          share_context ? share_context->type : OPENVG/*ignored*/));
      }
      if (!context->servercontext) {
         vg_client_state_free((VG_CLIENT_STATE_T *)context->state);
         khrn_platform_free(context);
         return 0;
      }

      break;
   }
#endif /* NO_OPENVG */
   case OPENGL_ES_11:
   {
      GLXX_CLIENT_STATE_T *state = (GLXX_CLIENT_STATE_T *)khrn_platform_malloc(sizeof(GLXX_CLIENT_STATE_T), "GLXX_CLIENT_STATE_T");
      if (!state) {
         khrn_platform_free(context);
         return 0;
      }

      context->state = state;
      if (gl11_client_state_init(state)) {
         CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
         context->servercontext = RPC_UINT_RES(RPC_CALL2_RES(eglIntCreateGLES11_impl,
                                                             thread,
                                                             EGLINTCREATEGLES11_ID,
                                                             share_context ? share_context->servercontext : 0,
                                                             share_context ? share_context->type : OPENGL_ES_11/*ignored*/));
         if (!context->servercontext) {
            glxx_client_state_free(state);
            khrn_platform_free(context);
            return 0;
         }
      }
      break;
   }
   case OPENGL_ES_20:
   {
      GLXX_CLIENT_STATE_T *state = (GLXX_CLIENT_STATE_T *)khrn_platform_malloc(sizeof(GLXX_CLIENT_STATE_T), "GLXX_CLIENT_STATE_T");
      if (!state) {
         khrn_platform_free(context);
         return 0;
      }

      context->state = state;

      if (gl20_client_state_init(state)) {
         CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
         context->servercontext = RPC_UINT_RES(RPC_CALL2_RES(eglIntCreateGLES20_impl,
                                                             thread,
                                                             EGLINTCREATEGLES20_ID,
                                                             share_context ? share_context->servercontext : 0,
                                                             share_context ? share_context->type : OPENGL_ES_20/*ignored*/));
         if (!context->servercontext) {
            glxx_client_state_free(state);
            khrn_platform_free(context);
            return 0;
         }
      }
      break;
   }
   default:
      UNREACHABLE();
      break;
   }
