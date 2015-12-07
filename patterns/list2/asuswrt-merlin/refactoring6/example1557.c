if (note->descsz == sizeof (pstatus_t)
#if defined (HAVE_PXSTATUS_T)
      || note->descsz == sizeof (pxstatus_t)
#endif
      )
    {
      pstatus_t pstat;

      memcpy (&pstat, note->descdata, sizeof (pstat));

      elf_tdata (abfd)->core_pid = pstat.pr_pid;
    }
#if defined (HAVE_PSTATUS32_T)
  else if (note->descsz == sizeof (pstatus32_t))
    {
      /* 64-bit host, 32-bit corefile */
      pstatus32_t pstat;

      memcpy (&pstat, note->descdata, sizeof (pstat));

      elf_tdata (abfd)->core_pid = pstat.pr_pid;
    }
