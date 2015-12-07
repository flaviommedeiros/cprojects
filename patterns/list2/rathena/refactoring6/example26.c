if( SQL_ERROR == Sql_Query(sql_handle, "SELECT `char_id`,`account_id`,`char_num`,`name`,`class`,"
		"`base_level`,`job_level`,`base_exp`,`job_exp`,`zeny`,`str`,`agi`,`vit`,`int`,`dex`,`luk`,"
		"`max_hp`,`hp`,`max_sp`,`sp`,`status_point`,`skill_point`,`option`,`karma`,`manner`,`party_id`,"
		"`guild_id`,`pet_id`,`homun_id`,`elemental_id`,`hair`,`hair_color`,`clothes_color`,`weapon`,"
		"`shield`,`head_top`,`head_mid`,`head_bottom`,`robe`,`last_map`,`last_x`,`last_y`,`save_map`,"
		"`save_x`,`save_y`,`partner_id`,`online`,`father`,`mother`,`child`,`fame`,`rename`,`delete_date`,"
		"`moves`,`unban_time`,`font`"
#if PACKETVER >= 20141016
		",`sex`"
#endif
		" FROM `%s` LIMIT 1;", schema_config.char_db) ){
		Sql_ShowDebug(sql_handle);
		return false;
	}
