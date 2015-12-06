switch (ent->eType)
		{
		case ET_ITEM:
		case ET_PUSH_TRIGGER:
		case ET_TELEPORT_TRIGGER:
		case ET_CONCUSSIVE_TRIGGER:
		case ET_OID_TRIGGER:
#ifdef VISIBLE_TRIGGERS
		case ET_TRIGGER_MULTIPLE:
		case ET_TRIGGER_FLAGONLY:
		case ET_TRIGGER_FLAGONLY_MULTIPLE:
#endif // VISIBLE_TRIGGERS
			cg_triggerEntities[cg_numTriggerEntities] = cent;
			cg_numTriggerEntities++;
			continue;
		case ET_CONSTRUCTIBLE:
			cg_triggerEntities[cg_numTriggerEntities] = cent;
			cg_numTriggerEntities++;
			break;
		default:
			break;
		}
