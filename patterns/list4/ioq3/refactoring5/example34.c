#ifdef MISSIONPACK
if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.enemyTookTheFlagSound );
							else
#endif
							CG_AddBufferedSound( cgs.media.yourTeamTookEnemyFlagSound );
