static consoleCommand_t commands[] =
{
	{ "testgun",             CG_TestGun_f            },
	{ "testmodel",           CG_TestModel_f          },
	{ "nextframe",           CG_TestModelNextFrame_f },
	{ "prevframe",           CG_TestModelPrevFrame_f },
	{ "nextskin",            CG_TestModelNextSkin_f  },
	{ "prevskin",            CG_TestModelPrevSkin_f  },
	{ "viewpos",             CG_Viewpos_f            },
	{ "+scores",             CG_ScoresDown_f         },
	{ "-scores",             CG_ScoresUp_f           },
	{ "zoomin",              CG_ZoomIn_f             },
	{ "zoomout",             CG_ZoomOut_f            },
	{ "weaplastused",        CG_LastWeaponUsed_f     },
	{ "weapnextinbank",      CG_NextWeaponInBank_f   },
	{ "weapprevinbank",      CG_PrevWeaponInBank_f   },
	{ "weapnext",            CG_NextWeapon_f         },
	{ "weapprev",            CG_PrevWeapon_f         },
	{ "weapalt",             CG_AltWeapon_f          },
	{ "weapon",              CG_Weapon_f             },
	{ "weaponbank",          CG_WeaponBank_f         },
	{ "fade",                CG_Fade_f               },

	{ "mp_QuickMessage",     CG_QuickMessage_f       },
	{ "mp_fireteammsg",      CG_QuickFireteams_f     },
	{ "mp_fireteamadmin",    CG_QuickFireteamAdmin_f },
	{ "wm_sayPlayerClass",   CG_SayPlayerClass_f     },
	{ "wm_ftsayPlayerClass", CG_FTSayPlayerClass_f   },


	{ "VoiceChat",           CG_VoiceChat_f          },
	{ "VoiceTeamChat",       CG_TeamVoiceChat_f      },

	// say, teamsay, etc
	{ "messageMode",         CG_MessageMode_f        },
	{ "messageMode2",        CG_MessageMode_f        },
	{ "messageMode3",        CG_MessageMode_f        },
	{ "messageSend",         CG_MessageSend_f        },

	{ "SetWeaponCrosshair",  CG_SetWeaponCrosshair_f },

	{ "VoiceFireTeamChat",   CG_BuddyVoiceChat_f     },

	{ "openlimbomenu",       CG_LimboMenu_f          },

	{ "+stats",              CG_StatsDown_f          },
	{ "-stats",              CG_StatsUp_f            },
	{ "+topshots",           CG_topshotsDown_f       },
	{ "-topshots",           CG_topshotsUp_f         },
	{ "+objectives",         CG_objectivesDown_f     },
	{ "-objectives",         CG_objectivesUp_f       },

	{ "autoRecord",          CG_autoRecord_f         },
	{ "autoScreenshot",      CG_autoScreenShot_f     },
	{ "currentTime",         CG_currentTime_f        },
	{ "keyoff",              CG_keyOff_f             },
	{ "keyon",               CG_keyOn_f              },
#ifdef FEATURE_MULTIVIEW
	{ "mvactivate",          CG_mvToggleAll_f        },
	{ "mvdel",               CG_mvDelete_f           },
	{ "mvhide",              CG_mvHideView_f         },
	{ "mvnew",               CG_mvNew_f              },
	{ "mvshow",              CG_mvShowView_f         },
	{ "mvswap",              CG_mvSwapViews_f        },
	{ "mvtoggle",            CG_mvToggleView_f       },
	{ "spechelp",            CG_toggleSpecHelp_f     },
#endif
	{ "statsdump",           CG_dumpStats_f          },
	{ "+vstr",               CG_vstrDown_f           },
	{ "-vstr",               CG_vstrUp_f             },

	{ "selectbuddy",         CG_SelectBuddy_f        },

	{ "MapZoomIn",           CG_AutomapZoomIn_f      },
	{ "MapZoomOut",          CG_AutomapZoomOut_f     },
	{ "+mapexpand",          CG_AutomapExpandDown_f  },
	{ "-mapexpand",          CG_AutomapExpandUp_f    },

	{ "generateTracemap",    CG_GenerateTracemap     },

	{ "ToggleAutoMap",       CG_ToggleAutomap_f      }, // toggle automap on/off

	{ "editSpeakers",        CG_EditSpeakers_f       },
	{ "dumpSpeaker",         CG_DumpSpeaker_f        },
	{ "modifySpeaker",       CG_ModifySpeaker_f      },
	{ "undoSpeaker",         CG_UndoSpeaker_f        },
	{ "cpm",                 CG_CPM_f                },
	{ "forcetapout",         CG_ForceTapOut_f        },
	{ "timerSet",            CG_TimerSet_f           },
	{ "timerReset",          CG_TimerReset_f         },
	{ "resetTimer",          CG_TimerReset_f         }, // keep ETPro compatibility
	{ "class",               CG_Class_f              },
	{ "readhuds",            CG_ReadHuds_f           },
};
