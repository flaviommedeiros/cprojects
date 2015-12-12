#if 1
if (strcmp(rname, "\\\\?PnP?\\Notification") == 0)
        {
            LLOGLN(10, ("  out szReader       %s", rgReaderStates[index].szReader));
            dwCurrentState = GET_UINT32(msg, offset);
            rgReaderStates[index].dwCurrentState = dwCurrentState;
            offset += 4;
            LLOGLN(10, ("  out dwCurrentState 0x%8.8x", dwCurrentState));
            // disable PnP for now
            dwEventState = 4; // GET_UINT32(msg, offset);
            rgReaderStates[index].dwEventState = dwEventState;
            offset += 4;
            LLOGLN(10, ("  out dwEventState   0x%8.8x", dwEventState));
            cbAtr = GET_UINT32(msg, offset);
            rgReaderStates[index].cbAtr = cbAtr;
            offset += 4;
            LLOGLN(10, ("  out cbAtr          %d", cbAtr));
            memcpy(rgReaderStates[index].rgbAtr, msg + offset, 33);
            offset += 36;
        }
        else
#endif
        {
            LLOGLN(10, ("  out szReader       %s", rgReaderStates[index].szReader));
            dwCurrentState = GET_UINT32(msg, offset);
            rgReaderStates[index].dwCurrentState = dwCurrentState;
            offset += 4;
            LLOGLN(10, ("  out dwCurrentState 0x%8.8x", dwCurrentState));
            dwEventState = GET_UINT32(msg, offset);
            rgReaderStates[index].dwEventState = dwEventState;
            offset += 4;
            LLOGLN(10, ("  out dwEventState   0x%8.8x", dwEventState));
            cbAtr = GET_UINT32(msg, offset);
            rgReaderStates[index].cbAtr = cbAtr;
            offset += 4;
            LLOGLN(10, ("  out cbAtr          %d", cbAtr));
            memcpy(rgReaderStates[index].rgbAtr, msg + offset, 33);
            offset += 36;
        }
