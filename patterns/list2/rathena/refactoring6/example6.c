if(sc->data[SC_AURABLADE]
#ifndef RENEWAL
				&& skill_id != LK_SPIRALPIERCE && skill_id != ML_SPIRALPIERCE
#endif
		) {
			int lv = sc->data[SC_AURABLADE]->val1;
#ifdef RENEWAL
			lv *= ((skill_id == LK_SPIRALPIERCE || skill_id == ML_SPIRALPIERCE)?wd.div_:1); // +100 per hit in lv 5
#endif
			ATK_ADD(wd.damage, wd.damage2, 20*lv);
		}
