#ifdef HAVE_BSV_MOVIE
if (cnt == 0 || g_extern.bsv.movie)
#else
      if (cnt == 0)
#endif
      {
         pretro_serialize(g_extern.state_buf, g_extern.state_size);
         state_manager_push(g_extern.state_manager, g_extern.state_buf);
      }
