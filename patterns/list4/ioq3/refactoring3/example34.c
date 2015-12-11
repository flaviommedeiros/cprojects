switch(rnd) {
		case 0: return "Gauntlet";
		case 1: return "Shotgun";
		case 2: return "Machinegun";
		case 3: return "Grenade Launcher";
		case 4: return "Rocket Launcher";
		case 5: return "Plasmagun";
		case 6: return "Railgun";
		case 7: return "Lightning Gun";
#ifdef MISSIONPACK
		case 8: return "Nailgun";
		case 9: return "Chaingun";
		case 10: return "Proximity Launcher";
#endif
		default: return "BFG10K";
	}
