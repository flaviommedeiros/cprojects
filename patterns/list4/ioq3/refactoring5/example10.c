#ifdef MISSIONPACK
if (!strcmp(buf, "sound/items/kamikazerespawn.wav" )) {
				//the kamikaze respawned so dont avoid it
				BotDontAvoid(bs, "Kamikaze");
			}
			else
#endif
				if (!strcmp(buf, "sound/items/poweruprespawn.wav")) {
				//powerup respawned... go get it
				BotGoForPowerups(bs);
			}
