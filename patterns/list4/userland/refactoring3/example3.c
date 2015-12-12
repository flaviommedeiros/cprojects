switch(reason) {

#ifdef USE_VCHIQ_ARM
   case VCHIQ_SERVICE_OPENED:
      {
#ifdef _VIDEOCORE
         // We're on the VideoCore side and we've been connected to, so we need to spawn another
         // listening service.  Create another ILCS instance.
         ILCS_CONFIG_T config;
         ilcs_config(&config);
         ilcs_init(st->vchiq, NULL, &config, st->use_memmgr);
#else
         vcos_abort();
#endif
      }
      break;

   case VCHIQ_SERVICE_CLOSED:
      if(st && st->kill_service < CLOSED_CALLBACK)
      {
         st->kill_service = CLOSED_CALLBACK;
         ilcs_send_quit(st);
      }
      break;

   case VCHIQ_BULK_RECEIVE_ABORTED:
      // bulk rx only aborted if we're about to close the service,
      // so signal this now so that the person waiting for this
      // bulk rx can return a failure to the user
      st->kill_service = ABORTED_BULK;
      vcos_event_signal(&st->bulk_rx);
      break;
#endif

   case VCHIQ_MESSAGE_AVAILABLE:
      vchiu_queue_push(&st->queue, header);
      break;

   case VCHIQ_BULK_RECEIVE_DONE:
      vcos_event_signal(&st->bulk_rx);
      break;

   default:
      break;
   }
