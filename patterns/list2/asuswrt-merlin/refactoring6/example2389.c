if (note->descsz != sizeof (lwpstat)
#if defined (HAVE_LWPXSTATUS_T)
      && note->descsz != sizeof (lwpxstatus_t)
#endif
      )
    return TRUE;
