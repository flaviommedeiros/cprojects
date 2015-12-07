#ifdef HAVE_LONG_LONG_TYPE
if(p->flags & FLAGS_LONGLONG)
        *(LONG_LONG_TYPE *) p->data.ptr = (LONG_LONG_TYPE)done;
      else
#endif
        if(p->flags & FLAGS_LONG)
          *(long *) p->data.ptr = (long)done;
      else if(!(p->flags & FLAGS_SHORT))
        *(int *) p->data.ptr = (int)done;
      else
        *(short *) p->data.ptr = (short)done;
