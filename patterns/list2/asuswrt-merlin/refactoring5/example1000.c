#ifdef CONFIG_MIPS_ATLAS
if (line == 1) {
			speed = saa9730_kgdb_hook(speed);
			generic_putDebugChar = saa9730_putDebugChar;
			generic_getDebugChar = saa9730_getDebugChar;
		}
		else
#endif
		{
			speed = rs_kgdb_hook(line, speed);
			generic_putDebugChar = rs_putDebugChar;
			generic_getDebugChar = rs_getDebugChar;
		}
