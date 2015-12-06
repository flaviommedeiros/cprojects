switch(accelDataSettings) {
			case MODULESETTINGS_FRSKYACCELDATA_ACCELS: {
				if (AccelsHandle() != NULL) {
					AccelsxGet(&accX);
					AccelsyGet(&accY);
					AccelszGet(&accZ);
				}
				break;
			}
#ifndef SMALLF1
			case MODULESETTINGS_FRSKYACCELDATA_NEDACCELS: {
				if (NedAccelHandle() != NULL) {
					NedAccelNorthGet(&accX);
					NedAccelEastGet(&accY);
					NedAccelDownGet(&accZ);
				}
				break;
			}
			case MODULESETTINGS_FRSKYACCELDATA_NEDVELOCITY: {
				if (VelocityActualHandle() != NULL) {
					VelocityActualNorthGet(&accX);
					VelocityActualEastGet(&accY);
					VelocityActualDownGet(&accZ);
					accX *= GRAVITY / 10.0f;
					accY *= GRAVITY / 10.0f;
					accZ *= GRAVITY / 10.0f;
				}
				break;
			}
#endif
			case MODULESETTINGS_FRSKYACCELDATA_ATTITUDEANGLES: {
				if (AttitudeActualHandle() != NULL) {
					AttitudeActualRollGet(&accX);
					AttitudeActualPitchGet(&accY);
					AttitudeActualYawGet(&accZ);
					accX *= GRAVITY / 10.0f;
					accY *= GRAVITY / 10.0f;
					accZ *= GRAVITY / 10.0f;
				}
				break;
			}
			}
