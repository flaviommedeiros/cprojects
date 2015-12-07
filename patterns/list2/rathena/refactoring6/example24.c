if( SQL_SUCCESS != SqlStmt_Prepare(stmt, 
#ifdef VIP_ENABLE
			"UPDATE `%s` SET `userid`=?,`user_pass`=?,`sex`=?,`email`=?,`group_id`=?,`state`=?,`unban_time`=?,`expiration_time`=?,`logincount`=?,`lastlogin`=?,`last_ip`=?,`birthdate`=?,`character_slots`=?,`pincode`=?, `pincode_change`=?, `vip_time`=?, `old_group`=? WHERE `account_id` = '%d'",
#else
			"UPDATE `%s` SET `userid`=?,`user_pass`=?,`sex`=?,`email`=?,`group_id`=?,`state`=?,`unban_time`=?,`expiration_time`=?,`logincount`=?,`lastlogin`=?,`last_ip`=?,`birthdate`=?,`character_slots`=?,`pincode`=?, `pincode_change`=? WHERE `account_id` = '%d'",
#endif
			db->account_db, acc->account_id)
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt,  0, SQLDT_STRING,    (void*)acc->userid,           strlen(acc->userid))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt,  1, SQLDT_STRING,    (void*)acc->pass,             strlen(acc->pass))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt,  2, SQLDT_ENUM,      (void*)&acc->sex,             sizeof(acc->sex))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt,  3, SQLDT_STRING,    (void*)acc->email,            strlen(acc->email))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt,  4, SQLDT_INT,       (void*)&acc->group_id,        sizeof(acc->group_id))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt,  5, SQLDT_UINT,      (void*)&acc->state,           sizeof(acc->state))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt,  6, SQLDT_LONG,      (void*)&acc->unban_time,      sizeof(acc->unban_time))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt,  7, SQLDT_LONG,      (void*)&acc->expiration_time, sizeof(acc->expiration_time))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt,  8, SQLDT_UINT,      (void*)&acc->logincount,      sizeof(acc->logincount))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt,  9, SQLDT_STRING,    (void*)&acc->lastlogin,       strlen(acc->lastlogin))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt, 10, SQLDT_STRING,    (void*)&acc->last_ip,         strlen(acc->last_ip))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt, 11, SQLDT_STRING,    (void*)&acc->birthdate,       strlen(acc->birthdate))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt, 12, SQLDT_UCHAR,     (void*)&acc->char_slots,      sizeof(acc->char_slots))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt, 13, SQLDT_STRING,    (void*)&acc->pincode,         strlen(acc->pincode))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt, 14, SQLDT_LONG,      (void*)&acc->pincode_change,  sizeof(acc->pincode_change))
#ifdef VIP_ENABLE
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt, 15, SQLDT_LONG,      (void*)&acc->vip_time,        sizeof(acc->vip_time))
		||  SQL_SUCCESS != SqlStmt_BindParam(stmt, 16, SQLDT_INT,       (void*)&acc->old_group,       sizeof(acc->old_group))
#endif
		||  SQL_SUCCESS != SqlStmt_Execute(stmt)
		) {
			SqlStmt_ShowDebug(stmt);
			break;
		}
