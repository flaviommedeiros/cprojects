if (mod.outMod->CanWrite() >= buffered_bytes
#if SUPPORT_EQUALIZER
			<< mod.dsp_isactive()
#endif
		) {
			int t;
			buffered_bytes = ASAP_Generate(&asap, buffer, buffered_bytes, BITS_PER_SAMPLE);
			if (buffered_bytes <= 0) {
				mod.outMod->CanWrite();
				if (!mod.outMod->IsPlaying()) {
					PostMessage(mod.hMainWindow, WM_WA_MPEG_EOF, 0, 0);
					return 0;
				}
				Sleep(10);
				continue;
			}
			t = mod.outMod->GetWrittenTime();
			mod.SAAddPCMData(buffer, channels, BITS_PER_SAMPLE, t);
			mod.VSAAddPCMData(buffer, channels, BITS_PER_SAMPLE, t);
#if SUPPORT_EQUALIZER
			t = buffered_bytes / (channels * (BITS_PER_SAMPLE / 8));
			t = mod.dsp_dosamples((short *) buffer, t, BITS_PER_SAMPLE, channels, ASAP_SAMPLE_RATE);
			t *= channels * (BITS_PER_SAMPLE / 8);
			mod.outMod->Write((char *) buffer, t);
#else
			mod.outMod->Write((char *) buffer, buffered_bytes);
#endif
		}
		else
			Sleep(20);
