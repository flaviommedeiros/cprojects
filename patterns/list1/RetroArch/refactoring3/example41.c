switch(type)
   {
      case DATA_TYPE_NONE:
         break;
      case DATA_TYPE_FILE:
         queue = rarch_main_data_nbio_get_msg_queue_ptr();
         fill_pathname_join_delim(new_msg, msg, msg2, '|', sizeof(new_msg));
         break;
      case DATA_TYPE_IMAGE:
         queue = rarch_main_data_nbio_image_get_msg_queue_ptr();
         fill_pathname_join_delim(new_msg, msg, msg2, '|', sizeof(new_msg));
         break;
#ifdef HAVE_NETWORKING
      case DATA_TYPE_HTTP:
         queue = rarch_main_data_http_get_msg_queue_ptr();
         fill_pathname_join_delim(new_msg, msg, msg2, '|', sizeof(new_msg));
         break;
#endif
#ifdef HAVE_OVERLAY
      case DATA_TYPE_OVERLAY:
         fill_pathname_join_delim(new_msg, msg, msg2, '|', sizeof(new_msg));
         break;
#endif
#ifdef HAVE_LIBRETRODB
      case DATA_TYPE_DB:
         queue = rarch_main_data_db_get_msg_queue_ptr();
         fill_pathname_join_delim(new_msg, msg, msg2, '|', sizeof(new_msg));
         break;
#endif
   }
