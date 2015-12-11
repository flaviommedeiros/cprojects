#ifdef QUAKEC
if (!QuakeCMacro(source))
#endif //QUAKEC
			{
				//read the precompiler directive
				if (!PC_ReadDollarDirective(source)) return qfalse;
				continue;
			}
