#ifdef MISSIONPACK
if ( s1->weapon == WP_PROX_LAUNCHER ) {
			AnglesToAxis( cent->lerpAngles, ent.axis );
		}
		else
#endif
		{
			RotateAroundDirection( ent.axis, s1->time );
		}
