if (cg_nopredict.integer
#ifdef ALLOW_GSYNC
	    || cg_synchronousClients.integer
#endif // ALLOW_GSYNC
	    )
	{
		CG_Text_Paint_Ext(ax, ay, cg_fontScaleTP.value, cg_fontScaleTP.value, colorWhite, "snc", 0, 0, ITEM_TEXTSTYLE_SHADOWED, &cgs.media.limboFont2);
	}
