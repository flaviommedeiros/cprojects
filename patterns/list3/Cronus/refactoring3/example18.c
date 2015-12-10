switch( battle->get_current_skill(src) ) {
					case RK_DRAGONBREATH:// it can only hit traps in pvp/gvg maps
					case RK_DRAGONBREATH_WATER:
						if( !map->list[m].flag.pvp && !map->list[m].flag.gvg )
							break;
					case 0://you can hit them without skills
					case MA_REMOVETRAP:
					case HT_REMOVETRAP:
					case AC_SHOWER:
					case MA_SHOWER:
					case WZ_SIGHTRASHER:
					case WZ_SIGHTBLASTER:
					case SM_MAGNUM:
					case MS_MAGNUM:
					case RA_DETONATOR:
					case RA_SENSITIVEKEEN:
					case RK_STORMBLAST:
					case SR_RAMPAGEBLASTER:
					case NC_COLDSLOWER:
#ifdef RENEWAL
					case KN_BOWLINGBASH:
					case KN_SPEARSTAB:
					case LK_SPIRALPIERCE:
					case ML_SPIRALPIERCE:
					case MO_FINGEROFFENSIVE:
					case MO_INVESTIGATE:
					case MO_TRIPLEATTACK:
					case MO_EXTREMITYFIST:
					case CR_HOLYCROSS:
					case ASC_METEORASSAULT:
					case RG_RAID:
					case MC_CARTREVOLUTION:
					case HT_CLAYMORETRAP:
					case RA_ICEBOUNDTRAP:
					case RA_FIRINGTRAP:
#endif
						state |= BCT_ENEMY;
						strip_enemy = 0;
						break;
					default:
						return 0;
				}
