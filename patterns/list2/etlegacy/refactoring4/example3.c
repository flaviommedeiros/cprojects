#if DEFINEHASHING
if (PC_FindHashedDefine(source->definehash, t->string))
#else
			if (PC_FindDefine(source->defines, t->string))
#endif //DEFINEHASHING
			{
				v->intvalue   = 1;
				v->floatvalue = 1;
			}
			else
			{
				v->intvalue   = 0;
				v->floatvalue = 0;
			}
