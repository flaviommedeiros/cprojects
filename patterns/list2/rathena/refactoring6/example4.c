if( sc->data[SC_ENERGYCOAT] && (skill_id == GN_HELLS_PLANT_ATK ||
#ifdef RENEWAL
			((flag&BF_WEAPON || flag&BF_MAGIC) && skill_id != WS_CARTTERMINATION)
#else
			(flag&BF_WEAPON && skill_id != WS_CARTTERMINATION)
#endif
			) )
		{
			struct status_data *status = status_get_status_data(bl);
			int per = 100*status->sp / status->max_sp -1; //100% should be counted as the 80~99% interval
			per /=20; //Uses 20% SP intervals.
			//SP Cost: 1% + 0.5% per every 20% SP
			if (!status_charge(bl, 0, (10+5*per)*status->max_sp/1000))
				status_change_end(bl, SC_ENERGYCOAT, INVALID_TIMER);
			damage -= damage * 6 * (1 + per) / 100; //Reduction: 6% + 6% every 20%
		}
