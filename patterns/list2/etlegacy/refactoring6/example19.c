if (cg.snap->ps.persistant[PERS_TEAM] == ci->team || cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR || cg.snap->ps.pm_type == PM_INTERMISSION
#if FEATURE_MULTIVIEW
	         || CG_mvMergedClientLocate(score->client)
#endif
	         )
	{
		CG_DrawPic(tempx - 3, y - 12, 14, 14, cgs.media.skillPics[SkillNumForClass(ci->cls)]);

		if (cgs.clientinfo[ci->clientNum].rank > 0)
		{
			CG_DrawPic(tempx + 13, y - 12, 16, 16, rankicons[cgs.clientinfo[ci->clientNum].rank][cgs.clientinfo[ci->clientNum].team == TEAM_AXIS ? 1 : 0][0].shader);
		}
	}
