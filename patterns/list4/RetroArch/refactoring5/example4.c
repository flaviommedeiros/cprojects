#ifdef HAVE_FBO
if (driver.video_poke && driver.video_poke->get_current_framebuffer)
      return driver.video_poke->get_current_framebuffer(driver.video_data);
   else
#endif
      return 0;
