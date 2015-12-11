switch(mod) {
		case MOD_SHOTGUN: return "Shotgun";
		case MOD_GAUNTLET: return "Gauntlet";
		case MOD_MACHINEGUN: return "Machinegun";
		case MOD_GRENADE:
		case MOD_GRENADE_SPLASH: return "Grenade Launcher";
		case MOD_ROCKET:
		case MOD_ROCKET_SPLASH: return "Rocket Launcher";
		case MOD_PLASMA:
		case MOD_PLASMA_SPLASH: return "Plasmagun";
		case MOD_RAILGUN: return "Railgun";
		case MOD_LIGHTNING: return "Lightning Gun";
		case MOD_BFG:
		case MOD_BFG_SPLASH: return "BFG10K";
#ifdef MISSIONPACK
		case MOD_NAIL: return "Nailgun";
		case MOD_CHAINGUN: return "Chaingun";
		case MOD_PROXIMITY_MINE: return "Proximity Launcher";
		case MOD_KAMIKAZE: return "Kamikaze";
		case MOD_JUICED: return "Prox mine";
#endif
		case MOD_GRAPPLE: return "Grapple";
		default: return "[unknown weapon]";
	}
