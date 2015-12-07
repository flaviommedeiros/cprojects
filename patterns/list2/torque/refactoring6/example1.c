if ((errno == EAGAIN) ||

#ifdef  ERFLOCK
          (errno == ERFLOCK) ||
#endif
#ifdef  EQUSR
          (errno == EQUSR) ||
#endif
#ifdef  EQGRP
          (errno == EQGRP) ||
#endif
#ifdef  EQACT
          (errno == EQACT) ||
#endif
#ifdef  ENOSDS
          (errno == ENOSDS) ||
#endif
          (errno == ENOMEM) ||
          (errno == ENOLCK) ||
          (errno == ENOSPC) ||
          (errno == ENFILE) ||
          (errno == EDEADLK) ||
          (errno == EBUSY))
        {
        pjob->ji_qs.ji_un.ji_momt.ji_exitstat = JOB_EXEC_RETRY;
        *SC = JOB_EXEC_RETRY;
        }
      else
        {
        pjob->ji_qs.ji_un.ji_momt.ji_exitstat = JOB_EXEC_BADRESRT;
        *SC = JOB_EXEC_FAIL1;
        }
