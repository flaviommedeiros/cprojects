switch (cent->currentState.eType)
	{
	default:
		// test for actual bad entity type
		if (cent->currentState.eType >= ET_EVENTS)
		{
			CG_Error("Bad entity type: %i\n", cent->currentState.eType);
		}
		break;
	case ET_CONCUSSIVE_TRIGGER:
	case ET_CAMERA:
	case ET_INVISIBLE:
	case ET_PUSH_TRIGGER:
	case ET_TELEPORT_TRIGGER:
	case ET_OID_TRIGGER:
	case ET_AI_EFFECT:
	case ET_EXPLOSIVE_INDICATOR:
	case ET_CONSTRUCTIBLE_INDICATOR:
	case ET_TANK_INDICATOR:
	case ET_TANK_INDICATOR_DEAD:
	case ET_COMMANDMAP_MARKER:  // this one should _never_ reach the client
#ifdef VISIBLE_TRIGGERS
	case ET_TRIGGER_MULTIPLE:
	case ET_TRIGGER_FLAGONLY:
	case ET_TRIGGER_FLAGONLY_MULTIPLE:
#endif // VISIBLE_TRIGGERS
		break;
	case ET_SPEAKER:
		CG_Speaker(cent);
		break;
	case ET_GAMEMODEL:
	case ET_MG42_BARREL:
	case ET_FOOTLOCKER:
	case ET_GENERAL:
	case ET_AAGUN:
		CG_General(cent);
		break;
	case ET_CABINET_H:
		CG_Cabinet(cent, CT_HEALTH);
		break;
	case ET_CABINET_A:
		CG_Cabinet(cent, CT_AMMO);
		break;
	case ET_CORPSE:
	case ET_PLAYER:
		if (cg.showGameView && cg.filtercams)
		{
			break;
		}
		CG_Player(cent);
		break;
	case ET_ITEM:
		CG_Item(cent);
		break;
	case ET_MISSILE:
	case ET_FLAMEBARREL:
	case ET_FP_PARTS:
	case ET_FIRE_COLUMN:
	case ET_FIRE_COLUMN_SMOKE:
	case ET_EXPLO_PART:
	case ET_RAMJET:
		CG_Missile(cent);
		break;
	case ET_EXPLOSIVE:
		CG_Explosive(cent);
		break;
	case ET_CONSTRUCTIBLE:
		CG_Constructible(cent);
		break;
	case ET_TRAP:
		CG_Trap(cent);
		break;
	case ET_CONSTRUCTIBLE_MARKER:
	case ET_ALARMBOX:
	case ET_MOVER:
		CG_Mover(cent);
		break;
	case ET_PROP:
		CG_Prop(cent);
		break;
	case ET_BEAM:
		CG_Beam(cent);
		break;
	case ET_PORTAL:
		CG_Portal(cent);
		break;
	case ET_CORONA:
		CG_Corona(cent);
		break;
	case ET_BEAM_2:
		CG_Beam_2(cent);
		break;
	case ET_GAMEMANAGER:
		cgs.gameManager = cent;
		break;
	case ET_SMOKER:
		CG_Smoker(cent);
		break;
	}
