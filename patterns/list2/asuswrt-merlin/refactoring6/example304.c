if (F_ISSET(pip, VRFY_IS_ALLZEROES)
#ifndef HAVE_FTRUNCATE
		    && i <= vdp->meta_last_pgno
#endif
		    ) {
			EPRINT((env,
			    "Page %lu: totally zeroed page", (u_long)i));
			isbad = 1;
		}
