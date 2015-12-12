#ifdef SUPPORT_REPEATER
if(bHDCPMode & HDCP_REPEATER)
            {
                SetIntMask3(0,B_ECCERR|B_R_AUTH_DONE|B_R_AUTH_START);
        	}
        	else
        #endif // SUPPORT_REPEATER
        	{
                SetIntMask3(~(B_R_AUTH_DONE|B_R_AUTH_START),B_ECCERR);
        	}
