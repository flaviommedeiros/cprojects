if(
				AllocFunction!=GC_malloc_uncollectable
#ifdef ATOMIC_UNCOLLECTABLE
				&& AllocFunction!=GC_malloc_atomic_uncollectable
#endif
			){
				ret2=GC_amiga_rec_alloc(size,AllocFunction,0);
			}else{
				ret2=(*AllocFunction)(size);
#ifdef GC_AMIGA_PRINTSTATS
				if((char *)ret2<chipmax || ret2==NULL){
					nsucc++;
					nsucc2+=size;
					ncur0++;
				}else{
					succ++;
					succ2+=size;
					cur0++;
				}
#endif
			}
