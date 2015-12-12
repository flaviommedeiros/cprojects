switch (num) {
#ifdef SIGHUP
  case SIGHUP: return "sighup";
#endif
#ifdef SIGINT
  case SIGINT: return "sigint";
#endif
#ifdef SIGQUIT
  case SIGQUIT: return "sigquit";
#endif
#ifdef SIGILL
  case SIGILL: return "sigill";
#endif
#ifdef SIGTRAP
  case SIGTRAP: return "sigtrap";
#endif
#ifdef SIGABRT
  case SIGABRT: return "sigabrt";
#endif
#ifdef SIGIOT
# if SIGIOT != SIGABRT
  case SIGIOT: return "sigiot";
# endif
#endif
#ifdef SIGBUS
  case SIGBUS: return "sigbus";
#endif
#ifdef SIGFPE
  case SIGFPE: return "sigfpe";
#endif
#ifdef SIGKILL
  case SIGKILL: return "sigkill";
#endif
#ifdef SIGUSR1
  case SIGUSR1: return "sigusr1";
#endif
#ifdef SIGSEGV
  case SIGSEGV: return "sigsegv";
#endif
#ifdef SIGUSR2
  case SIGUSR2: return "sigusr2";
#endif
#ifdef SIGPIPE
  case SIGPIPE: return "sigpipe";
#endif
#ifdef SIGALRM
  case SIGALRM: return "sigalrm";
#endif
#ifdef SIGTERM
  case SIGTERM: return "sigterm";
#endif
#ifdef SIGCHLD
  case SIGCHLD: return "sigchld";
#endif
#ifdef SIGSTKFLT
  case SIGSTKFLT: return "sigstkflt";
#endif
#ifdef SIGCONT
  case SIGCONT: return "sigcont";
#endif
#ifdef SIGSTOP
  case SIGSTOP: return "sigstop";
#endif
#ifdef SIGTSTP
  case SIGTSTP: return "sigtstp";
#endif
#ifdef SIGBREAK
  case SIGBREAK: return "sigbreak";
#endif
#ifdef SIGTTIN
  case SIGTTIN: return "sigttin";
#endif
#ifdef SIGTTOU
  case SIGTTOU: return "sigttou";
#endif
#ifdef SIGURG
  case SIGURG: return "sigurg";
#endif
#ifdef SIGXCPU
  case SIGXCPU: return "sigxcpu";
#endif
#ifdef SIGXFSZ
  case SIGXFSZ: return "sigxfsz";
#endif
#ifdef SIGVTALRM
  case SIGVTALRM: return "sigvtalrm";
#endif
#ifdef SIGPROF
  case SIGPROF: return "sigprof";
#endif
#ifdef SIGWINCH
  case SIGWINCH: return "sigwinch";
#endif
#ifdef SIGIO
  case SIGIO: return "sigio";
#endif
#ifdef SIGPOLL
# if SIGPOLL != SIGIO
  case SIGPOLL: return "sigpoll";
# endif
#endif
#ifdef SIGLOST
  case SIGLOST: return "siglost";
#endif
#ifdef SIGPWR
# if SIGPWR != SIGLOST
  case SIGPWR: return "sigpwr";
# endif
#endif
#ifdef SIGSYS
  case SIGSYS: return "sigsys";
#endif
  }
