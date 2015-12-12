static const struct iw_priv_args r8192_private_args[] = {

	{
		SIOCIWFIRSTPRIV + 0x0,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "badcrc"
	},

	{
		SIOCIWFIRSTPRIV + 0x1,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "activescan"

	},
	{
		SIOCIWFIRSTPRIV + 0x2,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "rawtx"
	}
#ifdef JOHN_IOCTL
	,
	{
		SIOCIWFIRSTPRIV + 0x3,
                IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "readRF"
	}
	,
	{
		SIOCIWFIRSTPRIV + 0x4,
                IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "writeRF"
	}
	,
	{
		SIOCIWFIRSTPRIV + 0x5,
                IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "readBB"
	}
	,
	{
		SIOCIWFIRSTPRIV + 0x6,
                IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "writeBB"
	}
        ,
        {
                SIOCIWFIRSTPRIV + 0x7,
                IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "readnicb"
        }
        ,
        {
                SIOCIWFIRSTPRIV + 0x8,
                IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "writenicb"
        }
        ,
        {
                SIOCIWFIRSTPRIV + 0x9,
                IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "apinfo"
        }

#endif
	,
	{
		SIOCIWFIRSTPRIV + 0x3,
		IW_PRIV_TYPE_INT | IW_PRIV_SIZE_FIXED | 1, 0, "forcereset"
	}

	,
	{
		SIOCIWFIRSTPRIV + 0x5,
		IW_PRIV_TYPE_NONE, IW_PRIV_TYPE_INT|IW_PRIV_SIZE_FIXED|1,
		"firm_ver"
	}
};
