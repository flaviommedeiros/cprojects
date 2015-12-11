switch (mod) {
		case MOD_GRAPPLE:
			message = "was caught by";
			break;
		case MOD_GAUNTLET:
			message = "was pummeled by";
			break;
		case MOD_MACHINEGUN:
			message = "was machinegunned by";
			break;
		case MOD_SHOTGUN:
			message = "was gunned down by";
			break;
		case MOD_GRENADE:
			message = "ate";
			message2 = "'s grenade";
			break;
		case MOD_GRENADE_SPLASH:
			message = "was shredded by";
			message2 = "'s shrapnel";
			break;
		case MOD_ROCKET:
			message = "ate";
			message2 = "'s rocket";
			break;
		case MOD_ROCKET_SPLASH:
			message = "almost dodged";
			message2 = "'s rocket";
			break;
		case MOD_PLASMA:
			message = "was melted by";
			message2 = "'s plasmagun";
			break;
		case MOD_PLASMA_SPLASH:
			message = "was melted by";
			message2 = "'s plasmagun";
			break;
		case MOD_RAILGUN:
			message = "was railed by";
			break;
		case MOD_LIGHTNING:
			message = "was electrocuted by";
			break;
		case MOD_BFG:
		case MOD_BFG_SPLASH:
			message = "was blasted by";
			message2 = "'s BFG";
			break;
#ifdef MISSIONPACK
		case MOD_NAIL:
			message = "was nailed by";
			break;
		case MOD_CHAINGUN:
			message = "got lead poisoning from";
			message2 = "'s Chaingun";
			break;
		case MOD_PROXIMITY_MINE:
			message = "was too close to";
			message2 = "'s Prox Mine";
			break;
		case MOD_KAMIKAZE:
			message = "falls to";
			message2 = "'s Kamikaze blast";
			break;
		case MOD_JUICED:
			message = "was juiced by";
			break;
#endif
		case MOD_TELEFRAG:
			message = "tried to invade";
			message2 = "'s personal space";
			break;
		default:
			message = "was killed by";
			break;
		}
