#ifdef VISIBLE_TRIGGERS
if (ent->eType == ET_TRIGGER_MULTIPLE || ent->eType == ET_TRIGGER_FLAGONLY || ent->eType == ET_TRIGGER_FLAGONLY_MULTIPLE)
			{
			}
			else
#endif // VISIBLE_TRIGGERS
			{
				// expand the bbox a bit
				VectorSet(mins, mins[0] - 48, mins[1] - 48, mins[2] - 48);
				VectorSet(maxs, maxs[0] + 48, maxs[1] + 48, maxs[2] + 48);
			}
