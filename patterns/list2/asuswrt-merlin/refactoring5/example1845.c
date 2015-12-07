#ifdef kIOPMAcknowledgmentOptionSystemCapabilityRequirements
if (m->p->IOPMConnection)	// If lightweight-wake capability is available, use that
				{
				const CFDateRef WakeDate = CFDateCreate(NULL, CFAbsoluteTimeGetCurrent() + interval);
				if (!WakeDate) LogMsg("ScheduleNextWake: CFDateCreate failed");
				else
					{
					const mDNSs32     reqs         = kIOPMSystemPowerStateCapabilityNetwork;
					const CFNumberRef Requirements = CFNumberCreate(NULL, kCFNumberSInt32Type, &reqs);
					if (!Requirements) LogMsg("ScheduleNextWake: CFNumberCreate failed");
					else
						{
						const void *OptionKeys[2] = { CFSTR("WakeDate"), CFSTR("Requirements") };
						const void *OptionVals[2] = {        WakeDate,          Requirements   };
						opts = CFDictionaryCreate(NULL, (void*)OptionKeys, (void*)OptionVals, 2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
						if (!opts) LogMsg("ScheduleNextWake: CFDictionaryCreate failed");
						CFRelease(Requirements);
						}
					CFRelease(WakeDate);
					}
				LogSPS("AllowSleepNow: Will request lightweight wakeup in %d seconds", interval);
				}
			else 						// else schedule the wakeup using the old API instead to
#endif
				{
				// If we wake within +/- 30 seconds of our requested time we'll assume the system woke for us,
				// so we should put it back to sleep. To avoid frustrating the user, we always request at least
				// 60 seconds sleep, so if they immediately re-wake the system within seconds of it going to sleep,
				// we then shouldn't hit our 30-second window, and we won't attempt to re-sleep the machine.
				if (interval < 60) interval = 60;
	
				result = mDNSPowerRequest(1, interval);
	
				if (result == kIOReturnNotReady)
					{
					LogMsg("Requested wakeup in %d seconds unsuccessful; retrying with longer intervals", interval);
					// IOPMSchedulePowerEvent fails with kIOReturnNotReady (-536870184/0xe00002d8) if the
					// requested wake time is "too soon", but there's no API to find out what constitutes
					// "too soon" on any given OS/hardware combination, so if we get kIOReturnNotReady
					// we just have to iterate with successively longer intervals until it doesn't fail.
					// Additionally, if our power request is deemed "too soon" for the machine to get to
					// sleep and wake back up again, we attempt to cancel the sleep request, since the
					// implication is that the system won't manage to be awake again at the time we need it.
					do
						{
						interval += (interval < 20) ? 1 : ((interval+3) / 4);
						result = mDNSPowerRequest(1, interval);
						}
					while (result == kIOReturnNotReady);
					}
	
				if (result) LogMsg("AllowSleepNow: Requested wakeup in %d seconds unsuccessful: %d %X", interval, result, result);
				else LogSPS("AllowSleepNow: Requested wakeup in %d seconds", interval);
				m->p->WakeAtUTC = mDNSPlatformUTC() + interval;
				}
