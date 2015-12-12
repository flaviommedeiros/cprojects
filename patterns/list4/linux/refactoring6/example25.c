if( (!ivideo->sisvga_enabled)
#if !defined(__i386__) && !defined(__x86_64__)
			     || (sisfb_resetcard)
#endif
						 ) {
#ifdef CONFIG_FB_SIS_300
		if(ivideo->sisvga_engine == SIS_300_VGA) {
			if(ivideo->chip == SIS_300) {
				sisfb_post_sis300(pdev);
				ivideo->sisfb_can_post = 1;
			}
		}
#endif

#ifdef CONFIG_FB_SIS_315
		if(ivideo->sisvga_engine == SIS_315_VGA) {
			int result = 1;
		/*	if((ivideo->chip == SIS_315H)   ||
			   (ivideo->chip == SIS_315)    ||
			   (ivideo->chip == SIS_315PRO) ||
			   (ivideo->chip == SIS_330)) {
				sisfb_post_sis315330(pdev);
			} else */ if(ivideo->chip == XGI_20) {
				result = sisfb_post_xgi(pdev);
				ivideo->sisfb_can_post = 1;
			} else if((ivideo->chip == XGI_40) && ivideo->haveXGIROM) {
				result = sisfb_post_xgi(pdev);
				ivideo->sisfb_can_post = 1;
			} else {
				printk(KERN_INFO "sisfb: Card is not "
					"POSTed and sisfb can't do this either.\n");
			}
			if(!result) {
				printk(KERN_ERR "sisfb: Failed to POST card\n");
				ret = -ENODEV;
				goto error_3;
			}
		}
#endif
	}
