#   ifndef NO_GETENV_WIN32
if (GetEnvironmentVariable(TEXT("GC_LOG_FILE"), pathBuf,
                                 _MAX_PATH + 1) - 1U < (DWORD)_MAX_PATH) {
        appendToFile = TRUE;
      } else
#   endif
    /* else */ {
      /* Env var not found or its value too long.       */
#     ifdef OLD_WIN32_LOG_FILE
        logPath = TEXT(GC_LOG_STD_NAME);
#     else
        int len = (int)GetModuleFileName(NULL /* hModule */, pathBuf,
                                         _MAX_PATH + 1);
        /* If GetModuleFileName() has failed then len is 0. */
        if (len > 4 && pathBuf[len - 4] == (TCHAR)'.') {
          len -= 4; /* strip executable file extension */
        }
        BCOPY(TEXT(".") TEXT(GC_LOG_STD_NAME), &pathBuf[len],
              sizeof(TEXT(".") TEXT(GC_LOG_STD_NAME)));
#     endif
    }
