switch(eid)
        {
            case DOT11F_EID_WPA:
            case DOT11F_EID_RSN:
#ifdef FEATURE_WLAN_WAPI
            case DOT11F_EID_WAPI:
#endif
                if(hdd_AddIwStreamEvent( IWEVGENIE,  elen+2, (char*)element, pscanInfo, last_event, current_event ) < 0 )
                    return -E2BIG;
                break;

            default:
                break;
        }
