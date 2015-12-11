#ifdef QUAKEC
if (!BuiltinFunction(source))
#endif //QUAKC
			{
				//read the precompiler directive
				if (!PC_ReadDirective(source)) return qfalse;
				continue;
			}
