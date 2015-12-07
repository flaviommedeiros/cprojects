if ((err = snd_interwave_detect(iwcard, gus, dev
#ifdef SNDRV_STB
            , &i2c_bus
#endif
	    )) < 0)
		return err;
