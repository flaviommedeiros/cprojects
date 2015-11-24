switch (signo)
        {
        case SIGILL:
            switch (info->si_code)
            {
#ifdef ILL_ILLOPC
            case ILL_ILLOPC: si_code_str = "Illegal opcode"; break;
#endif
#ifdef ILL_ILLOPN
            case ILL_ILLOPN: si_code_str = "Illegal operand"; break;
#endif
#ifdef ILL_ILLADR
            case ILL_ILLADR: si_code_str = "Illegal addressing mode"; break;
#endif
#ifdef ILL_ILLTRP
            case ILL_ILLTRP: si_code_str = "Illegal trap"; break;
#endif
#ifdef ILL_PRVOPC
            case ILL_PRVOPC: si_code_str = "Privileged opcode"; break;
#endif
#ifdef ILL_PRVREG
            case ILL_PRVREG: si_code_str = "Privileged register"; break;
#endif
#ifdef ILL_COPROC
            case ILL_COPROC: si_code_str = "Coprocessor error"; break;
#endif
#ifdef ILL_BADSTK
            case ILL_BADSTK: si_code_str = "Internal stack error"; break;
#endif
            }
            break;
        case SIGFPE:
            switch (info->si_code)
            {
#ifdef FPE_INTDIV
            case FPE_INTDIV: si_code_str = "Integer divide-by-zero"; break;
#endif
#ifdef FPE_INTOVF
            case FPE_INTOVF: si_code_str = "Integer overflow"; break;
#endif
            case FPE_FLTDIV: si_code_str = "Floating point divide-by-zero"; break;
            case FPE_FLTOVF: si_code_str = "Floating point overflow"; break;
            case FPE_FLTUND: si_code_str = "Floating point underflow"; break;
#ifdef FPE_FLTRES
            case FPE_FLTRES: si_code_str = "Floating point inexact result"; break;
#endif
#ifdef FPE_FLTINV
            case FPE_FLTINV: si_code_str = "Invalid floating point operation"; break;
#endif
#ifdef FPE_FLTSUB
            case FPE_FLTSUB: si_code_str = "Subscript out of range"; break;
#endif
            }
            break;
        case SIGSEGV:
            switch (info->si_code)
            {
#ifdef SEGV_MAPERR
            case SEGV_MAPERR: si_code_str = "Address not mapped"; break;
#endif
#ifdef SEGV_ACCERR
            case SEGV_ACCERR: si_code_str = "Invalid permissions"; break;
#endif
            }
            break;
        case SIGBUS:
            switch (info->si_code)
            {
#ifdef BUS_ADRALN
            case BUS_ADRALN: si_code_str = "Invalid address alignment"; break;
#endif
#ifdef BUS_ADRERR
            case BUS_ADRERR: si_code_str = "Non-existant physical address"; break;
#endif
#ifdef BUS_OBJERR
            case BUS_OBJERR: si_code_str = "Objet-specific hardware error"; break;
#endif
            }
            break;
        case SIGTRAP:
            switch (info->si_code)
            {
#ifdef TRAP_BRKPT
            case TRAP_BRKPT: si_code_str = "Process breakpoint"; break;
#endif
#ifdef TRAP_TRACE
            case TRAP_TRACE: si_code_str = "Process trace trap"; break;
#endif
            }
            break;
        case SIGCHLD:
            switch (info->si_code)
            {
#ifdef CLD_EXITED
            case CLD_EXITED: si_code_str = "Child has exited"; break;
#endif
#ifdef CLD_KILLED
            case CLD_KILLED: si_code_str = "Child has terminated abnormally and did not create a core file"; break;
#endif
#ifdef CLD_DUMPED
            case CLD_DUMPED: si_code_str = "Child has terminated abnormally and created a core file"; break;
#endif
#ifdef CLD_WTRAPPED
            case CLD_TRAPPED: si_code_str = "Traced child has trapped"; break;
#endif
#ifdef CLD_STOPPED
            case CLD_STOPPED: si_code_str = "Child has stopped"; break;
#endif
#ifdef CLD_CONTINUED
            case CLD_CONTINUED: si_code_str = "Stopped child has continued"; break;
#endif
            }
            break;
#ifdef SIGPOLL
        case SIGPOLL:
            switch (info->si_code)
            {
#ifdef POLL_IN
            case POLL_IN: si_code_str = "Data input available"; break;
#endif
#ifdef POLL_OUT
            case POLL_OUT: si_code_str = "Output buffers available"; break;
#endif
#ifdef POLL_MSG
            case POLL_MSG: si_code_str = "Input message available"; break;
#endif
#ifdef POLL_ERR
            case POLL_ERR: si_code_str = "I/O error"; break;
#endif
#ifdef POLL_PRI
            case POLL_PRI: si_code_str = "High priority input available"; break;
#endif
#ifdef POLL_HUP
            case POLL_HUP: si_code_str = "Device disconnected"; break;
#endif
            }
            break;
#endif /* SIGPOLL */
        default:
            switch (info->si_code)
            {
#ifdef SI_ASYNCNL
            case SI_ASYNCNL: si_code_str = "SI_ASYNCNL"; break;
#endif
#ifdef SI_SIGIO
            case SI_SIGIO: si_code_str = "Queued SIGIO"; break;
#endif
#ifdef SI_ASYNCIO
            case SI_ASYNCIO: si_code_str = "Asynchronous I/O request completed"; break;
#endif
#ifdef SI_MESGQ
            case SI_MESGQ: si_code_str = "Message queue state changed"; break;
#endif
            case SI_TIMER: si_code_str = "Timer expiration"; break;
            case SI_QUEUE: si_code_str = "Sigqueue() signal"; break;
            case SI_USER: si_code_str = "User function (kill, sigsend, abort, etc.)"; break;
#ifdef SI_KERNEL
            case SI_KERNEL: si_code_str = "Kernel signal"; break;
#endif
/* Dragonfly defines SI_USER and SI_UNDEFINED both as zero: */
/* For some reason, the PGI compiler will not let us combine these two
   #if tests into a single statement.  Sigh. */
#if defined(SI_UNDEFINED)
#if SI_UNDEFINED != SI_USER
            case SI_UNDEFINED: si_code_str = "Undefined code"; break;
#endif
#endif
            }
        }
