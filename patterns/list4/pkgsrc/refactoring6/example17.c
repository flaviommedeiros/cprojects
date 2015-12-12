if ((res =
#ifdef NET2_REGEX
			    resub(pt->rcmp,pt->nstr,outpt,endpt)
#else
			    resub(&(pt->rcmp),pm,pt->nstr,inpt, outpt,endpt)
#endif
			    ) < 0) {
				if (prnt)
					tty_warn(1, "Replacement name error %s",
					    name);
				return 1;
			}
