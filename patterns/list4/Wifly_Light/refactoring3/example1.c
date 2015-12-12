switch (pCmd->cmd) {
    case CLEAR_SCRIPT:
        //Trace_String("Clearing script buffer;");
        gScriptBuf.isClearing = TRUE;
        return OK;

    case LOOP_ON:
        gScriptBuf.loopStart[gScriptBuf.loopDepth] = gScriptBuf.write;
        gScriptBuf.loopDepth++;
        return ScriptCtrl_Write(pCmd);

    case LOOP_OFF:
        {
            gScriptBuf.loopDepth--;
            uns8 loopStart = gScriptBuf.loopStart[gScriptBuf.loopDepth];
            pCmd->data.loopEnd.startIndex = ScriptBufInc(loopStart);
            pCmd->data.loopEnd.depth = gScriptBuf.loopDepth;
            uns8 numLoops = pCmd->data.loopEnd.numLoops;
            pCmd->data.loopEnd.counter = numLoops;
            /*Trace_String("Add LOOP_OFF: ");
               Trace_Hex(gScriptBuf.write);
               Trace_Hex(pCmd->data.loopEnd.startIndex);
               Trace_Hex(pCmd->data.loopEnd.depth);
               Trace_Hex(pCmd->data.loopEnd.counter);
               Trace_String(";");*/
            uns8 retVal = ScriptCtrl_Write(pCmd);
#ifdef cc3200
            Eeprom_Save(true);
#endif
            return retVal;
        }

    case WAIT:
        return ScriptCtrl_Write(pCmd);

#ifndef cc3200
    case START_BL:
        CommandIO_CreateResponse(&g_ResponseBuf, START_BL, OK);
        CommandIO_SendResponse(&g_ResponseBuf);
        Platform_EnableBootloaderAutostart();
        softReset();
        /* never reach this */
        return OK;

#endif /* cc3200 */
#ifdef __CC8E__
    case GET_RTC:
        return OK;

    case SET_RTC:
        g_RtcTime.tm_year = pCmd->data.set_rtc.tm_year;
        g_RtcTime.tm_mon = pCmd->data.set_rtc.tm_mon;
        g_RtcTime.tm_mday = pCmd->data.set_rtc.tm_mday;
        g_RtcTime.tm_wday = pCmd->data.set_rtc.tm_wday;
        g_RtcTime.tm_hour = pCmd->data.set_rtc.tm_hour;
        g_RtcTime.tm_min = pCmd->data.set_rtc.tm_min;
        g_RtcTime.tm_sec = pCmd->data.set_rtc.tm_sec;
        Rtc_Ctl(RTC_SET_TIME, &g_RtcTime);
        return OK;

#endif /* #ifdef __CC8E__ */
    case SET_COLOR_DIRECT:
        Ledstrip_SetColorDirect((uns8*)&pCmd->data.set_color_direct.ptr_led_array);
        return NO_RESPONSE;

#ifdef __CC8E__
    case GET_CYCLETIME:
        return OK;

    case GET_TRACE:
        return OK;

#endif /* #ifdef __CC8E__ */
    case GET_FW_VERSION:
        return OK;

    case SET_FADE:
        return ScriptCtrl_Write(pCmd);

    case SET_GRADIENT:
        return ScriptCtrl_Write(pCmd);

    case GET_LED_TYP:
        return OK;

    default:
        return BAD_COMMAND_CODE;
    }
