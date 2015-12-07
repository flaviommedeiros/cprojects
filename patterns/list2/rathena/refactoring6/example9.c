if (status->agi == b_status->agi
#ifdef RENEWAL
			&& status->luk == b_status->luk
#endif
			)
			status->flee = status_calc_flee(bl, sc, b_status->flee);
		else
			status->flee = status_calc_flee(bl, sc, b_status->flee +(status->agi - b_status->agi)
#ifdef RENEWAL
			+ (status->luk/5 - b_status->luk/5)
#endif
			);
