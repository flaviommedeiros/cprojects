switch (inst.PIDs[i]) {
			case TXPIDSETTINGS_PIDS_ROLLRATEKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollRatePID[STABILIZATIONSETTINGS_ROLLRATEPID_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLRATEKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollRatePID[STABILIZATIONSETTINGS_ROLLRATEPID_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLRATEKD:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollRatePID[STABILIZATIONSETTINGS_ROLLRATEPID_KD], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLRATEILIMIT:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollRatePID[STABILIZATIONSETTINGS_ROLLRATEPID_ILIMIT], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLATTITUDEKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollPI[STABILIZATIONSETTINGS_ROLLPI_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLATTITUDEKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollPI[STABILIZATIONSETTINGS_ROLLPI_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLATTITUDEILIMIT:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollPI[STABILIZATIONSETTINGS_ROLLPI_ILIMIT], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHRATEKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchRatePID[STABILIZATIONSETTINGS_PITCHRATEPID_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHRATEKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchRatePID[STABILIZATIONSETTINGS_PITCHRATEPID_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHRATEKD:
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchRatePID[STABILIZATIONSETTINGS_PITCHRATEPID_KD], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHRATEILIMIT:
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchRatePID[STABILIZATIONSETTINGS_PITCHRATEPID_ILIMIT], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHATTITUDEKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchPI[STABILIZATIONSETTINGS_PITCHPI_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHATTITUDEKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchPI[STABILIZATIONSETTINGS_PITCHPI_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHATTITUDEILIMIT:
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchPI[STABILIZATIONSETTINGS_PITCHPI_ILIMIT], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHRATEKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollRatePID[STABILIZATIONSETTINGS_ROLLRATEPID_KP], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchRatePID[STABILIZATIONSETTINGS_PITCHRATEPID_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHRATEKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollRatePID[STABILIZATIONSETTINGS_ROLLRATEPID_KI], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchRatePID[STABILIZATIONSETTINGS_PITCHRATEPID_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHRATEKD:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollRatePID[STABILIZATIONSETTINGS_ROLLRATEPID_KD], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchRatePID[STABILIZATIONSETTINGS_PITCHRATEPID_KD], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHRATEILIMIT:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollRatePID[STABILIZATIONSETTINGS_ROLLRATEPID_ILIMIT], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchRatePID[STABILIZATIONSETTINGS_PITCHRATEPID_ILIMIT], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHATTITUDEKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollPI[STABILIZATIONSETTINGS_ROLLPI_KP], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchPI[STABILIZATIONSETTINGS_PITCHPI_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHATTITUDEKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollPI[STABILIZATIONSETTINGS_ROLLPI_KI], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchPI[STABILIZATIONSETTINGS_PITCHPI_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHATTITUDEILIMIT:
				stabilizationSettingsNeedsUpdate |= update(&stab.RollPI[STABILIZATIONSETTINGS_ROLLPI_ILIMIT], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.PitchPI[STABILIZATIONSETTINGS_PITCHPI_ILIMIT], value);
				break;
			case TXPIDSETTINGS_PIDS_YAWRATEKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.YawRatePID[STABILIZATIONSETTINGS_YAWRATEPID_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_YAWRATEKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.YawRatePID[STABILIZATIONSETTINGS_YAWRATEPID_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_YAWRATEKD:
				stabilizationSettingsNeedsUpdate |= update(&stab.YawRatePID[STABILIZATIONSETTINGS_YAWRATEPID_KD], value);
				break;
			case TXPIDSETTINGS_PIDS_YAWRATEILIMIT:
				stabilizationSettingsNeedsUpdate |= update(&stab.YawRatePID[STABILIZATIONSETTINGS_YAWRATEPID_ILIMIT], value);
				break;
			case TXPIDSETTINGS_PIDS_YAWATTITUDEKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.YawPI[STABILIZATIONSETTINGS_YAWPI_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_YAWATTITUDEKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.YawPI[STABILIZATIONSETTINGS_YAWPI_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_YAWATTITUDEILIMIT:
				stabilizationSettingsNeedsUpdate |= update(&stab.YawPI[STABILIZATIONSETTINGS_YAWPI_ILIMIT], value);
				break;
			case TXPIDSETTINGS_PIDS_GYROCUTOFF:
				stabilizationSettingsNeedsUpdate |= update(&stab.GyroCutoff, value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLVBARSENSITIVITY:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarSensitivity[STABILIZATIONSETTINGS_VBARSENSITIVITY_ROLL], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHVBARSENSITIVITY:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarSensitivity[STABILIZATIONSETTINGS_VBARSENSITIVITY_PITCH], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHVBARSENSITIVITY:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarSensitivity[STABILIZATIONSETTINGS_VBARSENSITIVITY_ROLL], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarSensitivity[STABILIZATIONSETTINGS_VBARSENSITIVITY_PITCH], value);
				break;
			
			case TXPIDSETTINGS_PIDS_YAWVBARSENSITIVITY:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarSensitivity[STABILIZATIONSETTINGS_VBARSENSITIVITY_YAW], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLVBARKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarRollPID[STABILIZATIONSETTINGS_VBARROLLPID_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLVBARKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarRollPID[STABILIZATIONSETTINGS_VBARROLLPID_KI], value);
				break;	
			case TXPIDSETTINGS_PIDS_ROLLVBARKD:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarRollPID[STABILIZATIONSETTINGS_VBARROLLPID_KD], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHVBARKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarPitchPID[STABILIZATIONSETTINGS_VBARPITCHPID_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHVBARKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarPitchPID[STABILIZATIONSETTINGS_VBARPITCHPID_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_PITCHVBARKD:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarPitchPID[STABILIZATIONSETTINGS_VBARPITCHPID_KD], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHVBARKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarRollPID[STABILIZATIONSETTINGS_VBARROLLPID_KP], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarPitchPID[STABILIZATIONSETTINGS_VBARPITCHPID_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHVBARKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarRollPID[STABILIZATIONSETTINGS_VBARROLLPID_KI], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarPitchPID[STABILIZATIONSETTINGS_VBARPITCHPID_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_ROLLPITCHVBARKD:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarRollPID[STABILIZATIONSETTINGS_VBARROLLPID_KD], value);
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarPitchPID[STABILIZATIONSETTINGS_VBARPITCHPID_KD], value);
				break;
			case TXPIDSETTINGS_PIDS_YAWVBARKP:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarYawPID[STABILIZATIONSETTINGS_VBARYAWPID_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_YAWVBARKI:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarYawPID[STABILIZATIONSETTINGS_VBARYAWPID_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_YAWVBARKD:
				stabilizationSettingsNeedsUpdate |= update(&stab.VbarYawPID[STABILIZATIONSETTINGS_VBARYAWPID_KD], value);
				break;
#ifdef UAVOBJ_INIT_vtolpathfollowersettings
			case TXPIDSETTINGS_PIDS_HORIZONTALPOSKP:
				vtolPathFollowerSettingsNeedsUpdate |= update(&vtolPathFollowerSettingsData.HorizontalPosPI[VTOLPATHFOLLOWERSETTINGS_HORIZONTALPOSPI_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_HORIZONTALPOSKI:
				vtolPathFollowerSettingsNeedsUpdate |= update(&vtolPathFollowerSettingsData.HorizontalPosPI[VTOLPATHFOLLOWERSETTINGS_HORIZONTALPOSPI_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_HORIZONTALPOSILIMIT:
				vtolPathFollowerSettingsNeedsUpdate |= update(&vtolPathFollowerSettingsData.HorizontalPosPI[VTOLPATHFOLLOWERSETTINGS_HORIZONTALPOSPI_ILIMIT], value);
				break;
			case TXPIDSETTINGS_PIDS_HORIZONTALVELKP:
				vtolPathFollowerSettingsNeedsUpdate |= update(&vtolPathFollowerSettingsData.HorizontalVelPID[VTOLPATHFOLLOWERSETTINGS_HORIZONTALVELPID_KP], value);
				break;
			case TXPIDSETTINGS_PIDS_HORIZONTALVELKI:
				vtolPathFollowerSettingsNeedsUpdate |= update(&vtolPathFollowerSettingsData.HorizontalVelPID[VTOLPATHFOLLOWERSETTINGS_HORIZONTALVELPID_KI], value);
				break;
			case TXPIDSETTINGS_PIDS_HORIZONTALVELKD:
				vtolPathFollowerSettingsNeedsUpdate |= update(&vtolPathFollowerSettingsData.HorizontalVelPID[VTOLPATHFOLLOWERSETTINGS_HORIZONTALVELPID_KD], value);
				break;
#endif /* UAVOBJ_INIT_vtolpathfollowersettings */
			default:
				// Previously this would assert.  But now the
				// object may be missing and it's not worth a
				// crash.
				break;
			}
