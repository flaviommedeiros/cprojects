#ifndef NO_VM_COMPILED
if ( vm->compiled )
			r = VM_CallCompiled( vm, &a.callnum );
		else
#endif
			r = VM_CallInterpreted( vm, &a.callnum );
