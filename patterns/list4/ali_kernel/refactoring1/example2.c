if (err < 0) {
			alc_free(codec);
			return err;
		}
#ifdef CONFIG_SND_HDA_ENABLE_REALTEK_QUIRKS
		else if (!err) {
			printk(KERN_INFO
			       "hda_codec: Cannot set up configuration "
			       "from BIOS.  Using 3-stack mode...\n");
			board_config = ALC880_3ST;
		}
#endif
