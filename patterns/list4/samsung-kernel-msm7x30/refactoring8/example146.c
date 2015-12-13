unsigned char phonecall_headset[] = {
#ifdef CONFIG_USA_MODEL_SGH_I727
	0x80, 0x1C, 0x00, 0x00, 											  //; 0x801C:VoiceProcessingOn,0x0000 : off 0x0001:On
	0x80, 0x17, 0x00, 0x02, 0x80,0x18, 0x00, 0x03, 		//; 0x8017:SetAlgorithmParmID, 0x0002:Microphone Configuration, 0x8018:SetAlgorithmParm, 0x0003:1-mic MD
	0x80, 0x26, 0x00, 0x1A, 							//; 0x8026:SelectRouting, 0x001A:(26)
	0x80, 0x1B, 0x00, 0x00, 							//;port a left in gain 0db
	0x80, 0x1B, 0x01, 0xA6, 							//;port a right -90db
	0x80, 0x15, 0x04, 0x00, 							//; port c left out odb
	0x80, 0x15, 0x05, 0x00, 							//; port c Rout 0db
	0x80, 0x1B, 0x02, 0x00, 							//; Port B Lin 0db
	0x80, 0x1B, 0x03, 0x00, 							//; Port B Rin 0db
	0x80, 0x15, 0x06, 0x00, 							//; Port D Lout 0db
	0x80, 0x15, 0x07, 0x00, 							//; Port D Rout 0db
	0x80, 0x17, 0x00, 0x4B, 0x80, 0x18, 0x00, 0x04,		// ; NS level 4
	0x80, 0x17, 0x00, 0x15, 0x80, 0x18, 0x00, 0x00,		// ;side tone OFF
	0x80, 0x17, 0x00, 0x03, 0x80, 0x18, 0x00, 0x00,		// ; AEC OFF
	0x80, 0x17, 0x00, 0x04, 0x80, 0x18, 0x00, 0x00,		// ; Tx AGC Off
	0x80, 0x17, 0x00, 0x28, 0x80, 0x18, 0x00, 0x00,		// ; Rx AGC Off
	0x80, 0x17, 0x00, 0x09, 0x80, 0x18, 0x00, 0x00,		// ; VEQ OFF
	0x80, 0x17, 0x00, 0x0E, 0x80, 0x18, 0x00, 0x02,		// ;Rx NS On
	0x80, 0x17, 0x00, 0x20, 0x80, 0x18, 0x00, 0x00,		// ; Tx post EQ off
	0x80, 0x17, 0x00, 0x1F, 0x80, 0x18, 0x00, 0x00,		// ; Rx post EQ off
	0x80, 0x17, 0x00, 0x1A, 0x80, 0x18, 0x00, 0x00,		// ; Tx comport noise off
	0x80, 0x17, 0x00, 0x4F, 0x80, 0x18, 0x00, 0x00,		// ;BWE OFF
#else
	0x80, 0x1C, 0x00, 0x00, 							//; 0x801C:VoiceProcessingOn, 0x0001:On
	0x80, 0x17, 0x00, 0x02, 0x80,0x18, 0x00, 0x03, 		//; 0x8017:SetAlgorithmParmID, 0x0002:Microphone Configuration, 0x8018:SetAlgorithmParm, 0x0003:1-mic MD
	0x80, 0x26, 0x00, 0x1A, 							//; 0x8026:SelectRouting, 0x001A:(26)
	0x80, 0x1B, 0x00, 0x00, 							//;port a left in gain 0db
	0x80, 0x1B, 0x01, 0xA6, 							//;port a right -90db
	0x80, 0x15, 0x04, 0x00, 							//; port c left out odb
	0x80, 0x15, 0x05, 0x00, 							//; port c Rout 0db
	0x80, 0x1B, 0x02, 0x00, 							//; Port B Lin 0db
	0x80, 0x1B, 0x03, 0x00, 							//; Port B Rin 0db
	0x80, 0x15, 0x06, 0x00, 							//; Port D Lout 0db
	0x80, 0x15, 0x07, 0x00, 							//; Port D Rout 0db
	0x80, 0x17, 0x00, 0x4B, 0x80, 0x18, 0x00, 0x04,		// ; NS level 4
	0x80, 0x17, 0x00, 0x15, 0x80, 0x18, 0x00, 0x00,		// ;side tone OFF
	0x80, 0x17, 0x00, 0x03, 0x80, 0x18, 0x00, 0x00,		// ; AEC OFF
	0x80, 0x17, 0x00, 0x04, 0x80, 0x18, 0x00, 0x00,		// ; Tx AGC Off
	0x80, 0x17, 0x00, 0x28, 0x80, 0x18, 0x00, 0x00,		// ; Rx AGC Off
	0x80, 0x17, 0x00, 0x09, 0x80, 0x18, 0x00, 0x00,		// ; VEQ OFF
	0x80, 0x17, 0x00, 0x0E, 0x80, 0x18, 0x00, 0x02,		// ;Rx NS On
	0x80, 0x17, 0x00, 0x20, 0x80, 0x18, 0x00, 0x00,		// ; Tx post EQ off
	0x80, 0x17, 0x00, 0x1F, 0x80, 0x18, 0x00, 0x00,		// ; Rx post EQ off
	0x80, 0x17, 0x00, 0x1A, 0x80, 0x18, 0x00, 0x00,		// ; Tx comport noise off
	0x80, 0x17, 0x00, 0x4F, 0x80, 0x18, 0x00, 0x00,		// ;BWE OFF
#endif
};