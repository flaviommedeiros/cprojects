#ifdef _IS_WINDOWS_
if (aXferEvent[hand])                       // if this 1401 has an open event handle
    {
        CloseHandle(aXferEvent[hand]);          // close down the handle
        aXferEvent[hand] = NULL;                // and mark it as gone
    }
