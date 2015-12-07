if (status->int_ == b_status->int_ && status->vit == b_status->vit
#ifdef RENEWAL
			&& status->dex == b_status->dex
#endif
			)
			status->mdef2 = status_calc_mdef2(bl, sc, b_status->mdef2);
		else
			status->mdef2 = status_calc_mdef2(bl, sc, b_status->mdef2 +(status->int_ - b_status->int_)
#ifdef RENEWAL
			+ (int)( ((float)status->dex/5 - (float)b_status->dex/5) + ((float)status->vit/5 - (float)b_status->vit/5) )
#else
			+ ((status->vit - b_status->vit)>>1)
#endif
			);
