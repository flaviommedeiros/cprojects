#ifdef CURL_SWS_FORK_ENABLED
if(use_fork) {
      /* The fork enabled version just forks off the child and don't care
         about it anymore, so don't assume otherwise. Beware and don't do
         this at home. */
      rc = fork();
      if(-1 == rc) {
        printf("MAJOR ERROR: fork() failed!\n");
        break;
      }
    }
    else
      /* not a fork, just set rc so the following proceeds nicely */
      rc = 0;
