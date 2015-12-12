#ifndef STACK_POP_CALLBACK
if(!IoObject_isReferenced(blockLocals) && !IoObject_isReferenced(callObject))
	{
		CollectorMarker_remove((CollectorMarker *)blockLocals);
		IoObject_free(blockLocals);

		CollectorMarker_remove((CollectorMarker *)callObject);
		IoObject_free(callObject);
		//IoObject_freeIfUnreferenced(blockLocals);
		//IoObject_freeIfUnreferenced(callObject);
	}
	else
#endif
	{
		// since the callObject doesn't IOREF its blockLocals pointer
		if (IoObject_isReferenced(callObject))
		{
			IoObject_isReferenced_(blockLocals, 1);
		}
	}
