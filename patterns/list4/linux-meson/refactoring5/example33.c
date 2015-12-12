#ifdef On_Chip_EDID
if(EDIDdev == ExtEDID)
        EDID_Reading=EDID_READ_BYTE(EXT_EDIDADR, i+(uBlock*0x80), 0x10,  &rEDID[i], EDIDdev);
        else
        #endif
        EDID_Reading=EDID_READ_BYTE(EDIDADR, i+(uBlock*0x80), 0x10,  &rEDID[i], EDIDdev);
