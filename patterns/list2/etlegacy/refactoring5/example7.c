#ifndef DEBUG_STATS
if (g_gamestate.integer == GS_PLAYING)
#endif
			{
				if (self->s.density & 8)
				{
					ent->client->sess.aWeaponStats[BG_WeapStatForWeapon(WP_MOBILE_BROWNING)].atts++;
				}
				else
				{
					ent->client->sess.aWeaponStats[BG_WeapStatForWeapon(WP_MOBILE_MG42)].atts++;
				}
			}
