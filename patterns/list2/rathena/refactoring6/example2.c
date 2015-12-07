if( sd
		&& (drop_rate <= sd->state.autoloot || pc_isautolooting(sd, ditem->item_data.nameid))
		&& (battle_config.idle_no_autoloot == 0 || DIFF_TICK(last_tick, sd->idletime) < battle_config.idle_no_autoloot)
		&& (battle_config.homunculus_autoloot?1:!flag)
#ifdef AUTOLOOT_DISTANCE
		&& sd->bl.m == md->bl.m
		&& check_distance_blxy(&sd->bl, dlist->x, dlist->y, AUTOLOOT_DISTANCE)
#endif
	) {	//Autoloot.
		struct party_data *p = party_search(sd->status.party_id);

		if (party_share_loot(party_search(sd->status.party_id),
			sd, &ditem->item_data, sd->status.char_id) == 0
		) {
			ers_free(item_drop_ers, ditem);
			return;
		}

		if ((itemdb_search(ditem->item_data.nameid))->flag.broadcast &&
			(!p || !(p->party.item&2)) // Somehow, if party's pickup distribution is 'Even Share', no announcemet
			)
			intif_broadcast_obtain_special_item(sd, ditem->item_data.nameid, md->mob_id, ITEMOBTAIN_TYPE_MONSTER_ITEM);
	}
