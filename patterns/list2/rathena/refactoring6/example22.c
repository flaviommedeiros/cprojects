if( SQL_ERROR == Sql_Query(sql_handle,
#ifdef VIP_ENABLE
		"SELECT `account_id`,`userid`,`user_pass`,`sex`,`email`,`group_id`,`state`,`unban_time`,`expiration_time`,`logincount`,`lastlogin`,`last_ip`,`birthdate`,`character_slots`,`pincode`, `pincode_change`, `vip_time`, `old_group` FROM `%s` WHERE `account_id` = %d",
#else
		"SELECT `account_id`,`userid`,`user_pass`,`sex`,`email`,`group_id`,`state`,`unban_time`,`expiration_time`,`logincount`,`lastlogin`,`last_ip`,`birthdate`,`character_slots`,`pincode`, `pincode_change` FROM `%s` WHERE `account_id` = %d",
#endif
		db->account_db, account_id )
	) {
		Sql_ShowDebug(sql_handle);
		return false;
	}
