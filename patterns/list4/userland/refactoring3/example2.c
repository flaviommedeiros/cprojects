switch (context->type) {
#ifndef NO_OPENVG
   case OPENVG:
      RPC_CALL1(eglIntDestroyVG_impl,
                thread,
                EGLINTDESTROYVG_ID,
                RPC_UINT(context->servercontext));
      RPC_FLUSH(thread);
      vg_client_state_free((VG_CLIENT_STATE_T *)context->state);
      break;
#endif
   case OPENGL_ES_11:
   case OPENGL_ES_20:
       RPC_CALL1(eglIntDestroyGL_impl,
                thread,
                EGLINTDESTROYGL_ID,
                RPC_UINT(context->servercontext));
      RPC_FLUSH(thread);
      glxx_client_state_free((GLXX_CLIENT_STATE_T *)context->state);
      break;
   default:
      UNREACHABLE();
   }
