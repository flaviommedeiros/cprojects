#ifdef HAVE_FBO
if (driver.video_poke && driver.video_poke->get_proc_address)
      return driver.video_poke->get_proc_address(driver.video_data, sym);
   else
#endif
      return NULL;
