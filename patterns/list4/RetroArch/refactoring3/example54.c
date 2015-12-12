switch (status)
   {
      case CELL_SYSUTIL_REQUEST_EXITGAME:
         gl->quitting = true;
         g_extern.lifecycle_mode_state &= ~((1ULL << MODE_MENU) | (1ULL << MODE_GAME));
         break;
#ifdef HAVE_OSKUTIL
      case CELL_SYSUTIL_OSKDIALOG_LOADED:
         break;
      case CELL_SYSUTIL_OSKDIALOG_INPUT_CANCELED:
         RARCH_LOG("CELL_SYSUTIL_OSKDIALOG_INPUT_CANCELED.\n");
         pOskAbort(); //fall-through
      case CELL_SYSUTIL_OSKDIALOG_FINISHED:
         if (status == CELL_SYSUTIL_OSKDIALOG_FINISHED)
            RARCH_LOG("CELL_SYSUTIL_OSKDIALOG_FINISHED.\n");

         pOskUnloadAsync(&osk->outputInfo);

         if (osk->outputInfo.result == CELL_OSKDIALOG_INPUT_FIELD_RESULT_OK)
         {
            RARCH_LOG("Setting MODE_OSK_ENTRY_SUCCESS.\n");
            g_extern.lifecycle_mode_state |= (1ULL << MODE_OSK_ENTRY_SUCCESS);
         }
         else
         {
            RARCH_LOG("Setting MODE_OSK_ENTRY_FAIL.\n");
            g_extern.lifecycle_mode_state |= (1ULL << MODE_OSK_ENTRY_FAIL);
         }

         osk->flags &= ~OSK_IN_USE;
         break;
      case CELL_SYSUTIL_OSKDIALOG_UNLOADED:
         RARCH_LOG("CELL_SYSUTIL_OSKDIALOG_UNLOADED.\n");
         sys_memory_container_destroy(osk->containerid);
         break;
#endif
   }
