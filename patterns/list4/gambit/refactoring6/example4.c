if (
#ifdef USE_PUMPS
      InterlockedDecrement (&self->refcount) == 0
#else
      --self->refcount == 0
#endif
      )
    {
      e = ___device_release_virt (self);
      ___free_mem (self);
    }
