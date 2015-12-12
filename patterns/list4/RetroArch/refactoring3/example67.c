switch (info->type)
   {
      case RARCH_STATE_CAPTURE:
         uniform->value = fetch(info);
         break;

      case RARCH_STATE_CAPTURE_PREV:
         if (info->prev[0] != fetch(info))
         {
            info->prev[1] = info->prev[0];
            info->prev[0] = fetch(info);
         }
         uniform->value = info->prev[1];
         break;

      case RARCH_STATE_TRANSITION:
         if (info->old_value != fetch(info))
         {
            info->old_value = fetch(info);
            info->frame_count = frame_count;
         }
         uniform->value = info->frame_count;
         break;

      case RARCH_STATE_TRANSITION_COUNT:
         if (info->old_value != fetch(info))
         {
            info->old_value = fetch(info);
            info->transition_count++;
         }
         uniform->value = info->transition_count;
         break;

      case RARCH_STATE_TRANSITION_PREV:
         if (info->old_value != fetch(info))
         {
            info->old_value = fetch(info);
            info->frame_count_prev = info->frame_count;
            info->frame_count = frame_count;
         }
         uniform->value = info->frame_count_prev;
         break;
      
#ifdef HAVE_PYTHON
      case RARCH_STATE_PYTHON:
         uniform->value = py_state_get(info->py, info->id, frame_count);
         break;
#endif
      
      default:
         break;
   }
