#ifdef ADDR_NO_RANDOMIZE
if (personality (ADDR_NO_RANDOMIZE) == -1)
#endif
			system ("echo 0 > "RVAS);
