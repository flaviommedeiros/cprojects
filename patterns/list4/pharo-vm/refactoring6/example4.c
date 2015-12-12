if (res == WAIT_TIMEOUT
#if !defined(_WIN32_WCE) // for pulsing by timeSetEvent below
		 || res == WAIT_OBJECT_0
#endif
		   )
			heartbeat();
		else if (res == WAIT_FAILED)
			abortMessage(TEXT("Fatal: WaitForSingleObject(beatSemaphore) %ld"),
						 GetLastError());
		else
			printLastError(TEXT("beatThreadStateMachine WaitForSingleObject"));
