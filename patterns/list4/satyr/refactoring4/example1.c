#if _ELFUTILS_PREREQ(0, 158)
if (dwfl_core_file_report(ch->dwfl, ch->eh, exe_file) == -1)
#else
    if (dwfl_core_file_report(ch->dwfl, ch->eh) == -1)
#endif
    {
        set_error_dwfl("dwfl_core_file_report");
        goto fail_dwfl;
    }
