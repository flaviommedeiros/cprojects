switch(c->cmd) {
#ifdef WITH_LF
		case CMD_SET_LF_SAMPLING_CONFIG:
			setSamplingConfig((sample_config *) c->d.asBytes);
			break;
		case CMD_ACQUIRE_RAW_ADC_SAMPLES_125K:
			cmd_send(CMD_ACK,SampleLF(c->arg[0]),0,0,0,0);
			break;
		case CMD_MOD_THEN_ACQUIRE_RAW_ADC_SAMPLES_125K:
			ModThenAcquireRawAdcSamples125k(c->arg[0],c->arg[1],c->arg[2],c->d.asBytes);
			break;
		case CMD_LF_SNOOP_RAW_ADC_SAMPLES:
			cmd_send(CMD_ACK,SnoopLF(),0,0,0,0);
			break;
		case CMD_HID_DEMOD_FSK:
			CmdHIDdemodFSK(c->arg[0], 0, 0, 1);
			break;
		case CMD_HID_SIM_TAG:
			CmdHIDsimTAG(c->arg[0], c->arg[1], 1);
			break;
		case CMD_FSK_SIM_TAG:
			CmdFSKsimTAG(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_ASK_SIM_TAG:
			CmdASKsimTag(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_PSK_SIM_TAG:
			CmdPSKsimTag(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_HID_CLONE_TAG:
			CopyHIDtoT55x7(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes[0]);
			break;
		case CMD_IO_DEMOD_FSK:
			CmdIOdemodFSK(c->arg[0], 0, 0, 1);
			break;
		case CMD_IO_CLONE_TAG:
			CopyIOtoT55x7(c->arg[0], c->arg[1]);
			break;
		case CMD_EM410X_DEMOD:
			CmdEM410xdemod(c->arg[0], 0, 0, 1);
			break;
		case CMD_EM410X_WRITE_TAG:
			WriteEM410x(c->arg[0], c->arg[1], c->arg[2]);
			break;
		case CMD_READ_TI_TYPE:
			ReadTItag();
			break;
		case CMD_WRITE_TI_TYPE:
			WriteTItag(c->arg[0],c->arg[1],c->arg[2]);
			break;
		case CMD_SIMULATE_TAG_125K:
			LED_A_ON();
			SimulateTagLowFrequency(c->arg[0], c->arg[1], 1);
			LED_A_OFF();
			break;
		case CMD_LF_SIMULATE_BIDIR:
			SimulateTagLowFrequencyBidir(c->arg[0], c->arg[1]);
			break;
		case CMD_INDALA_CLONE_TAG:
			CopyIndala64toT55x7(c->arg[0], c->arg[1]);					
			break;
		case CMD_INDALA_CLONE_TAG_L:
			CopyIndala224toT55x7(c->d.asDwords[0], c->d.asDwords[1], c->d.asDwords[2], c->d.asDwords[3], c->d.asDwords[4], c->d.asDwords[5], c->d.asDwords[6]);
			break;
		case CMD_T55XX_READ_BLOCK:
			T55xxReadBlock(c->arg[0], c->arg[1], c->arg[2]);
			break;
		case CMD_T55XX_WRITE_BLOCK:
			T55xxWriteBlock(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes[0]);
			break;
		case CMD_T55XX_WAKEUP:
			T55xxWakeUp(c->arg[0]);
			break;
		case CMD_T55XX_RESET_READ:
			T55xxResetRead();
			break;
		case CMD_PCF7931_READ:
			ReadPCF7931();
			break;
		case CMD_PCF7931_WRITE:
			WritePCF7931(c->d.asBytes[0],c->d.asBytes[1],c->d.asBytes[2],c->d.asBytes[3],c->d.asBytes[4],c->d.asBytes[5],c->d.asBytes[6], c->d.asBytes[9], c->d.asBytes[7]-128,c->d.asBytes[8]-128, c->arg[0], c->arg[1], c->arg[2]);
			break;
		case CMD_EM4X_READ_WORD:
			EM4xReadWord(c->arg[1], c->arg[2],c->d.asBytes[0]);
			break;
		case CMD_EM4X_WRITE_WORD:
			EM4xWriteWord(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes[0]);
			break;
		case CMD_AWID_DEMOD_FSK: // Set realtime AWID demodulation
			CmdAWIDdemodFSK(c->arg[0], 0, 0, 1);
			break;
		case CMD_VIKING_CLONE_TAG:
			CopyVikingtoT55xx(c->arg[0], c->arg[1], c->arg[2]);
			break;
#endif

#ifdef WITH_HITAG
		case CMD_SNOOP_HITAG: // Eavesdrop Hitag tag, args = type
			SnoopHitag(c->arg[0]);
			break;
		case CMD_SIMULATE_HITAG: // Simulate Hitag tag, args = memory content
			SimulateHitagTag((bool)c->arg[0],(byte_t*)c->d.asBytes);
			break;
		case CMD_READER_HITAG: // Reader for Hitag tags, args = type and function
			ReaderHitag((hitag_function)c->arg[0],(hitag_data*)c->d.asBytes);
			break;
#endif

#ifdef WITH_ISO15693
		case CMD_ACQUIRE_RAW_ADC_SAMPLES_ISO_15693:
			AcquireRawAdcSamplesIso15693();
			break;
		case CMD_RECORD_RAW_ADC_SAMPLES_ISO_15693:
			RecordRawAdcSamplesIso15693();
			break;
			
		case CMD_ISO_15693_COMMAND:
			DirectTag15693Command(c->arg[0],c->arg[1],c->arg[2],c->d.asBytes);
			break;
					
		case CMD_ISO_15693_FIND_AFI:
			BruteforceIso15693Afi(c->arg[0]);
			break;	
			
		case CMD_ISO_15693_DEBUG:
			SetDebugIso15693(c->arg[0]);
			break;

		case CMD_READER_ISO_15693:
			ReaderIso15693(c->arg[0]);
			break;
		case CMD_SIMTAG_ISO_15693:
			SimTagIso15693(c->arg[0], c->d.asBytes);
			break;
#endif

#ifdef WITH_LEGICRF
		case CMD_SIMULATE_TAG_LEGIC_RF:
			LegicRfSimulate(c->arg[0], c->arg[1], c->arg[2]);
			break;

		case CMD_WRITER_LEGIC_RF:
			LegicRfWriter(c->arg[1], c->arg[0]);
			break;

		case CMD_READER_LEGIC_RF:
			LegicRfReader(c->arg[0], c->arg[1]);
			break;
#endif

#ifdef WITH_ISO14443b
		case CMD_READ_SRI512_TAG:
			ReadSTMemoryIso14443b(0x0F);
			break;
		case CMD_READ_SRIX4K_TAG:
			ReadSTMemoryIso14443b(0x7F);
			break;
		case CMD_SNOOP_ISO_14443B:
			SnoopIso14443b();
			break;
		case CMD_SIMULATE_TAG_ISO_14443B:
			SimulateIso14443bTag();
			break;
		case CMD_ISO_14443B_COMMAND:
			SendRawCommand14443B(c->arg[0],c->arg[1],c->arg[2],c->d.asBytes);
			break;
#endif

#ifdef WITH_ISO14443a
		case CMD_SNOOP_ISO_14443a:
			SnoopIso14443a(c->arg[0]);
			break;
		case CMD_READER_ISO_14443a:
			ReaderIso14443a(c);
			break;
		case CMD_SIMULATE_TAG_ISO_14443a:
			SimulateIso14443aTag(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);  // ## Simulate iso14443a tag - pass tag type & UID
			break;
			
		case CMD_EPA_PACE_COLLECT_NONCE:
			EPA_PACE_Collect_Nonce(c);
			break;
		case CMD_EPA_PACE_REPLAY:
			EPA_PACE_Replay(c);
			break;
			
		case CMD_READER_MIFARE:
			ReaderMifare(c->arg[0]);
			break;
		case CMD_MIFARE_READBL:
			MifareReadBlock(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_MIFAREU_READBL:
			MifareUReadBlock(c->arg[0],c->arg[1], c->d.asBytes);
			break;
		case CMD_MIFAREUC_AUTH:
			MifareUC_Auth(c->arg[0],c->d.asBytes);
			break;
		case CMD_MIFAREU_READCARD:
			MifareUReadCard(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_MIFAREUC_SETPWD: 
			MifareUSetPwd(c->arg[0], c->d.asBytes);
			break;
		case CMD_MIFARE_READSC:
			MifareReadSector(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_MIFARE_WRITEBL:
			MifareWriteBlock(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		//case CMD_MIFAREU_WRITEBL_COMPAT:
			//MifareUWriteBlockCompat(c->arg[0], c->d.asBytes);
			//break;
		case CMD_MIFAREU_WRITEBL:
			MifareUWriteBlock(c->arg[0], c->arg[1], c->d.asBytes);
			break;
		case CMD_MIFARE_NESTED:
			MifareNested(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_MIFARE_CHKKEYS:
			MifareChkKeys(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_SIMULATE_MIFARE_CARD:
			Mifare1ksim(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		
		// emulator
		case CMD_MIFARE_SET_DBGMODE:
			MifareSetDbgLvl(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_MIFARE_EML_MEMCLR:
			MifareEMemClr(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_MIFARE_EML_MEMSET:
			MifareEMemSet(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_MIFARE_EML_MEMGET:
			MifareEMemGet(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_MIFARE_EML_CARDLOAD:
			MifareECardLoad(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
			
		// Work with "magic Chinese" card
		case CMD_MIFARE_CSETBLOCK:
			MifareCSetBlock(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_MIFARE_CGETBLOCK:
			MifareCGetBlock(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_MIFARE_CIDENT:
			MifareCIdent();
			break;
			
		// mifare sniffer
		case CMD_MIFARE_SNIFFER:
			SniffMifare(c->arg[0]);
			break;

#endif

#ifdef WITH_ICLASS
		// Makes use of ISO14443a FPGA Firmware
		case CMD_SNOOP_ICLASS:
			SnoopIClass();
			break;
		case CMD_SIMULATE_TAG_ICLASS:
			SimulateIClass(c->arg[0], c->arg[1], c->arg[2], c->d.asBytes);
			break;
		case CMD_READER_ICLASS:
			ReaderIClass(c->arg[0]);
			break;
		case CMD_READER_ICLASS_REPLAY:
			ReaderIClass_Replay(c->arg[0], c->d.asBytes);
			break;
		case CMD_ICLASS_EML_MEMSET:
			emlSet(c->d.asBytes,c->arg[0], c->arg[1]);
			break;
		case CMD_ICLASS_WRITEBLOCK:
			iClass_WriteBlock(c->arg[0], c->d.asBytes);
			break;
		case CMD_ICLASS_READCHECK:  // auth step 1
			iClass_ReadCheck(c->arg[0], c->arg[1]);
			break;
		case CMD_ICLASS_READBLOCK:
			iClass_ReadBlk(c->arg[0]);
			break;
		case CMD_ICLASS_AUTHENTICATION: //check
			iClass_Authentication(c->d.asBytes);
			break;
		case CMD_ICLASS_DUMP:
			iClass_Dump(c->arg[0], c->arg[1]);
			break;
		case CMD_ICLASS_CLONE:
			iClass_Clone(c->arg[0], c->arg[1], c->d.asBytes);
			break;
#endif
#ifdef WITH_HFSNOOP
		case CMD_HF_SNIFFER:
			HfSnoop(c->arg[0], c->arg[1]);
			break;
#endif

		case CMD_BUFF_CLEAR:
			BigBuf_Clear();
			break;

		case CMD_MEASURE_ANTENNA_TUNING:
			MeasureAntennaTuning();
			break;

		case CMD_MEASURE_ANTENNA_TUNING_HF:
			MeasureAntennaTuningHf();
			break;

		case CMD_LISTEN_READER_FIELD:
			ListenReaderField(c->arg[0]);
			break;

		case CMD_FPGA_MAJOR_MODE_OFF:		// ## FPGA Control
			FpgaWriteConfWord(FPGA_MAJOR_MODE_OFF);
			SpinDelay(200);
			LED_D_OFF(); // LED D indicates field ON or OFF
			break;

		case CMD_DOWNLOAD_RAW_ADC_SAMPLES_125K:

			LED_B_ON();
			uint8_t *BigBuf = BigBuf_get_addr();
			for(size_t i=0; i<c->arg[1]; i += USB_CMD_DATA_SIZE) {
				size_t len = MIN((c->arg[1] - i),USB_CMD_DATA_SIZE);
				cmd_send(CMD_DOWNLOADED_RAW_ADC_SAMPLES_125K,i,len,BigBuf_get_traceLen(),BigBuf+c->arg[0]+i,len);
			}
			// Trigger a finish downloading signal with an ACK frame
			cmd_send(CMD_ACK,1,0,BigBuf_get_traceLen(),getSamplingConfig(),sizeof(sample_config));
			LED_B_OFF();
			break;

		case CMD_DOWNLOADED_SIM_SAMPLES_125K: {
			uint8_t *b = BigBuf_get_addr();
			memcpy(b+c->arg[0], c->d.asBytes, USB_CMD_DATA_SIZE);
			cmd_send(CMD_ACK,0,0,0,0,0);
			break;
		}	
		case CMD_READ_MEM:
			ReadMem(c->arg[0]);
			break;

		case CMD_SET_LF_DIVISOR:
		  	FpgaDownloadAndGo(FPGA_BITSTREAM_LF);
			FpgaSendCommand(FPGA_CMD_SET_DIVISOR, c->arg[0]);
			break;

		case CMD_SET_ADC_MUX:
			switch(c->arg[0]) {
				case 0: SetAdcMuxFor(GPIO_MUXSEL_LOPKD); break;
				case 1: SetAdcMuxFor(GPIO_MUXSEL_LORAW); break;
				case 2: SetAdcMuxFor(GPIO_MUXSEL_HIPKD); break;
				case 3: SetAdcMuxFor(GPIO_MUXSEL_HIRAW); break;
			}
			break;

		case CMD_VERSION:
			SendVersion();
			break;
		case CMD_STATUS:
			SendStatus();
			break;
		case CMD_PING:
			cmd_send(CMD_ACK,0,0,0,0,0);
			break;
#ifdef WITH_LCD
		case CMD_LCD_RESET:
			LCDReset();
			break;
		case CMD_LCD:
			LCDSend(c->arg[0]);
			break;
#endif
		case CMD_SETUP_WRITE:
		case CMD_FINISH_WRITE:
		case CMD_HARDWARE_RESET:
			usb_disable();
			SpinDelay(1000);
			SpinDelay(1000);
			AT91C_BASE_RSTC->RSTC_RCR = RST_CONTROL_KEY | AT91C_RSTC_PROCRST;
			for(;;) {
				// We're going to reset, and the bootrom will take control.
			}
			break;

		case CMD_START_FLASH:
			if(common_area.flags.bootrom_present) {
				common_area.command = COMMON_AREA_COMMAND_ENTER_FLASH_MODE;
			}
			usb_disable();
			AT91C_BASE_RSTC->RSTC_RCR = RST_CONTROL_KEY | AT91C_RSTC_PROCRST;
			for(;;);
			break;

		case CMD_DEVICE_INFO: {
			uint32_t dev_info = DEVICE_INFO_FLAG_OSIMAGE_PRESENT | DEVICE_INFO_FLAG_CURRENT_MODE_OS;
			if(common_area.flags.bootrom_present) dev_info |= DEVICE_INFO_FLAG_BOOTROM_PRESENT;
			cmd_send(CMD_DEVICE_INFO,dev_info,0,0,0,0);	
			break;
		}
		default:
			Dbprintf("%s: 0x%04x","unknown command:",c->cmd);
			break;
	}
