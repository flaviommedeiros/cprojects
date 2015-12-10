switch(skill_id) {
			case MO_FINGEROFFENSIVE:
				if(sd) {
					if (battle_config.finger_offensive_type)
						wd.div_ = 1;
					else
						wd.div_ = sd->spiritball_old;
				}
				break;
			case HT_PHANTASMIC:
				//Since these do not consume ammo, they need to be explicitly set as arrow attacks.
				flag.arrow = 1;
				break;
#ifndef RENEWAL
			case PA_SHIELDCHAIN:
			case CR_SHIELDBOOMERANG:
#endif
			case LG_SHIELDPRESS:
			case LG_EARTHDRIVE:
				flag.weapon = 0;
				break;

			case KN_PIERCE:
			case ML_PIERCE:
				wd.div_= (wd.div_>0?tstatus->size+1:-(tstatus->size+1));
				break;

			case TF_DOUBLE: //For NPC used skill.
			case GS_CHAINACTION:
				wd.type = BDT_MULTIHIT;
				break;

			case GS_GROUNDDRIFT:
			case KN_SPEARSTAB:
			case KN_BOWLINGBASH:
			case MS_BOWLINGBASH:
			case MO_BALKYOUNG:
			case TK_TURNKICK:
				wd.blewcount=0;
				break;

			case KN_AUTOCOUNTER:
				wd.flag=(wd.flag&~BF_SKILLMASK)|BF_NORMAL;
				break;

			case NPC_CRITICALSLASH:
			case LG_PINPOINTATTACK:
				flag.cri = 1; //Always critical skill.
				break;

			case LK_SPIRALPIERCE:
				if (!sd) wd.flag=(wd.flag&~(BF_RANGEMASK|BF_WEAPONMASK))|BF_LONG|BF_MISC;
				break;

			//When in banding, the number of hits is equal to the number of Royal Guards in banding.
			case LG_HESPERUSLIT:
				if( sc && sc->data[SC_BANDING] && sc->data[SC_BANDING]->val2 > 3 )
					wd.div_ = sc->data[SC_BANDING]->val2;
				break;

			case MO_INVESTIGATE:
				flag.pdef = flag.pdef2 = 2;
				break;

			case RA_AIMEDBOLT:
				if( tsc && (tsc->data[SC_WUGBITE] || tsc->data[SC_ANKLESNARE] || tsc->data[SC_ELECTRICSHOCKER]) )
					wd.div_ = tstatus->size + 2 + ( (rnd()%100 < 50-tstatus->size*10) ? 1 : 0 );
				break;

			case NPC_EARTHQUAKE:
				wd.flag = (wd.flag&~(BF_WEAPON)) | BF_MAGIC;
				break;
#ifdef RENEWAL
			case MO_EXTREMITYFIST:
			case GS_PIERCINGSHOT:
			case AM_ACIDTERROR:
			case AM_DEMONSTRATION:
			case NJ_ISSEN:
			case PA_SACRIFICE:
				flag.distinct = 1;
				break;
			case GN_CARTCANNON:
			case PA_SHIELDCHAIN:
			case GS_MAGICALBULLET:
			case NJ_SYURIKEN:
			case KO_BAKURETSU:
				flag.distinct = 1;
				/* Fall through */
			case NJ_KUNAI:
			case HW_MAGICCRASHER:
				flag.tdef = 1;
				break;
#endif
		}
