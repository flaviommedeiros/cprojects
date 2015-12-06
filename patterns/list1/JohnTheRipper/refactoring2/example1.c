#ifdef _OPENMP
if (john_main_process)
#endif
		if (format->params.flags & FMT_OMP && ompt > 1)
			printf("(%dxOMP) ", ompt);
