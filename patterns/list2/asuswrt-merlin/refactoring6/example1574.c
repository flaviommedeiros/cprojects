if (nvram_match("acs_dfs", "1")
#ifdef RTAC66U
			&& nvram_match("wl1_dfs", "1")
#endif
		)
		{
			/* exclude acsd from selecting chanspec 52, 52l, 52/80, 56, 56u, 56/80, 60, 60l, 60/80, 64, 64u, 64/80 */
			nvram_set("wl1_acs_excl_chans",
                                  "0xd034,0xe03a,0xd836,0xd038,0xe13a,0xd936,0xd03c,0xe23a,0xd83e,0xd040,0xe33a,0xd93e");
			dfs_in_use = 1;
		}
		else
		{	/* exclude acsd from selecting chanspec 52, 52l, 52/80, 56, 56u, 56/80, 60, 60l, 60/80, 64, 64u, 64/80, 100, 100l, 100/80, 104, 104u, 104/80, 108, 108l, 108/80, 112, 112u, 112/80, 116, 132, 132l, 136, 136u, 140 */
			nvram_set("wl1_acs_excl_chans",
				  "0xd034,0xe03a,0xd836,0xd038,0xe13a,0xd936,0xd03c,0xe23a,0xd83e,0xd040,0xe33a,0xd93e,0xd064,0xd866,0xe06a,0xd068,0xd966,0xe16a,0xd06c,0xd86e,0xe26a,0xd070,0xd96e,0xe36a,0xd074,0xd084,0xd886,0xd088,0xd986,0xd08c");
		}
