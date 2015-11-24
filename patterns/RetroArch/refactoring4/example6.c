#ifdef OSX_PPC
if (OpenAComponent(comp, &dev->dev) != noErr)
#else
   if (AudioComponentInstanceNew(comp, &dev->dev) != noErr)
#endif
      goto error;
