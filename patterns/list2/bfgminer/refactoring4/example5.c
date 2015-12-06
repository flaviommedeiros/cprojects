#ifdef WIN32
if (adapters[j].iBusNumber < adapters[i].iBusNumber)
#else
				if (adapters[j].iBusNumber > adapters[i].iBusNumber)
#endif
					virtual_gpu++;
