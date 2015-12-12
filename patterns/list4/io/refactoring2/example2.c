#ifdef IOSTATE_RECYCLING_ON
if(List_size(IOSTATE->recycledObjects) >= IOSTATE->maxRecycledObjects)
#endif
	{
		IoObject_dealloc(self);
		//CollectorMarker_free((CollectorMarker *)self);
	}
#ifdef IOSTATE_RECYCLING_ON
	else
	{
		//printf("recycling %p\n", (void *)self);
		IoObject_rawRemoveAllProtos(self);

		#ifdef IOOBJECT_PERSISTENCE
		IoObject_isDirty_(self, 0);
		#endif

		IoObject_hasDoneLookup_(self, 0);
		IoObject_isSymbol_(self, 0);
		IoObject_isLocals_(self, 0);
		IoObject_isActivatable_(self, 0);

		//if (IoObject_ownsSlots(self))
		{
			//IoObject_freeSlots(self);
			PHash_clean(IoObject_slots(self));
		}
		/*
		else
		{
			IoObject_slots_(self, NULL);
		}
		*/

		List_append_(IOSTATE->recycledObjects, self);
	}
