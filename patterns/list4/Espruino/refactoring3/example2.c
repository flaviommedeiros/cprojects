switch (task.type) {
    case UET_WAKEUP : jsiConsolePrintf("WAKEUP\n"); break;
    case UET_SET : jsiConsolePrintf("SET ");
    for (i=0;i<UTILTIMERTASK_PIN_COUNT;i++)
      jsiConsolePrintf("%p=%d,", task.data.set.pins[i],  (task.data.set.value>>i)&1);
    jsiConsolePrintf("\n");
    break;
#ifndef SAVE_ON_FLASH
    case UET_WRITE_BYTE : jsiConsolePrintf("WRITE_BYTE\n"); break;
    case UET_READ_BYTE : jsiConsolePrintf("READ_BYTE\n"); break;
    case UET_WRITE_SHORT : jsiConsolePrintf("WRITE_SHORT\n"); break;
    case UET_READ_SHORT : jsiConsolePrintf("READ_SHORT\n"); break;
#endif
    case UET_EXECUTE : jsiConsolePrintf("EXECUTE %x\n", task.data.execute); break;
    default : jsiConsolePrintf("Unknown type %d\n", task.type); break;
    }
