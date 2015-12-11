if (!BotCTFCarryingFlag(bs)
#ifdef MISSIONPACK
				&& !Bot1FCTFCarryingFlag(bs)
				&& !BotHarvesterCarryingCubes(bs)
#endif
				) {
				trap_EA_Use(bs->client);
			}
