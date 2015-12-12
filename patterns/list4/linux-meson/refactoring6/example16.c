if ((unlikely(pcr_sync_stat != PCR_SYNC_HI)) &&
#ifndef CALC_CACHED_TIME
		((((ab_level + (ab_size >> PCR_DETECT_MARGIN_SHIFT_AUDIO_HI)) > ab_size) ||
                ((vb_level + (vb_size >> PCR_DETECT_MARGIN_SHIFT_VIDEO_HI)) > vb_size)))
#else
		((pts_cached_time(PTS_TYPE_VIDEO)>=PTS_CACHED_NORMAL_HI_TIME) && (pts_cached_time(PTS_TYPE_AUDIO)>=PTS_CACHED_NORMAL_HI_TIME))
#endif
		) {

        WRITE_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0,  READ_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0) &
                       (~((1 << 31) | (TOGGLE_MODE_LOW_HIGH << 28))));
        WRITE_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0,  READ_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0) | (TOGGLE_MODE_NORMAL_HIGH << 28));
        WRITE_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0,  READ_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0) | (1 << 31));
#ifdef MODIFY_TIMESTAMP_INC_WITH_PLL
	{
		u32 inc, M_nom, N_nom;

		M_nom = READ_MPEG_REG(HHI_AUD_PLL_CNTL) & 0x1ff;
		N_nom = (READ_MPEG_REG(HHI_AUD_PLL_CNTL) >> 9) & 0x1f;

		inc = (M_nom*(NORMAL_TOGGLE_TIME+1)+(M_nom+M_HIGH_DIFF)*(HIGH_TOGGLE_TIME+1))*PLL_FACTOR/((NORMAL_TOGGLE_TIME+HIGH_TOGGLE_TIME+2)*M_nom);
		set_timestamp_inc_factor(inc);
		printk("pll high inc: %d factor: %d\n", inc, PLL_FACTOR);
	}
#endif
        pcr_sync_stat = PCR_SYNC_HI;
        printk("pcr_sync_stat = PCR_SYNC_HI\n");
        if ((ab_level + (ab_size >> PCR_DETECT_MARGIN_SHIFT_AUDIO_HI)) > ab_size) {
            pcr_recover_trigger |= (1 << PCR_TRIGGER_AUDIO);
            printk("audio: 0x%x+0x%x > 0x%x, vb_level 0x%x\n", ab_level, (ab_size >> PCR_DETECT_MARGIN_SHIFT_AUDIO_HI), ab_size, vb_level);
        }
        if ((vb_level + (vb_size >> PCR_DETECT_MARGIN_SHIFT_VIDEO_HI)) > vb_size) {
            pcr_recover_trigger |= (1 << PCR_TRIGGER_VIDEO);
            printk("video: 0x%x+0x%x > 0x%x, ab_level 0x%x\n", vb_level, (vb_size >> PCR_DETECT_MARGIN_SHIFT_VIDEO_HI), vb_size, ab_level);
        }
    } else if (
    		((pcr_sync_stat == PCR_SYNC_LO) &&
#ifndef CALC_CACHED_TIME
                (((!(pcr_recover_trigger & (1 << PCR_TRIGGER_AUDIO))) || (ab_level > (ab_size >> PCR_MAINTAIN_MARGIN_SHIFT_AUDIO)))
                &&
                ((!(pcr_recover_trigger & (1 << PCR_TRIGGER_VIDEO))) || ((vb_level + (vb_size >> PCR_MAINTAIN_MARGIN_SHIFT_VIDEO)) > vb_size)))
#else
		((pts_cached_time(PTS_TYPE_VIDEO)>=PTS_CACHED_LO_NORMAL_TIME) || (pts_cached_time(PTS_TYPE_AUDIO)>=PTS_CACHED_LO_NORMAL_TIME))
#endif
		)
               ||
               ((pcr_sync_stat == PCR_SYNC_HI) &&
#ifndef CALC_CACHED_TIME
                ((!(pcr_recover_trigger & (1 << PCR_TRIGGER_AUDIO))) || ((ab_level + (ab_size >> PCR_MAINTAIN_MARGIN_SHIFT_AUDIO)) < ab_size))
                &&
                ((!(pcr_recover_trigger & (1 << PCR_TRIGGER_VIDEO))) || (vb_level < (vb_size >> PCR_MAINTAIN_MARGIN_SHIFT_VIDEO)))
#else
		((pts_cached_time(PTS_TYPE_VIDEO)<PTS_CACHED_HI_NORMAL_TIME) || (pts_cached_time(PTS_TYPE_AUDIO)<PTS_CACHED_HI_NORMAL_TIME))
#endif
		)) {

        WRITE_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0,  READ_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0) &
                       (~((1 << 31) | (TOGGLE_MODE_LOW_HIGH << 28))));
        WRITE_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0,  READ_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0) | (TOGGLE_MODE_FIXED << 28));
        WRITE_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0,  READ_MPEG_REG(HHI_AUD_PLL_MOD_CNTL0) | (1 << 31));

#ifdef MODIFY_TIMESTAMP_INC_WITH_PLL
	{
		set_timestamp_inc_factor(PLL_FACTOR);
		printk("pll normal inc:%d\n", PLL_FACTOR);
	}
#endif

        pcr_sync_stat = PCR_SYNC_UNSET;
        pcr_recover_trigger = 0;
        printk("pcr_sync_stat = PCR_SYNC_UNSET ab_level: 0x%x, vb_level: 0x%x\n", ab_level, vb_level);
    }
