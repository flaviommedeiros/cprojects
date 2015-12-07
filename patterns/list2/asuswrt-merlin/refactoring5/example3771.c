#ifdef TO_DO_LIST
if(Adapter->bInHctTest)
	{
		RT_TRACE(COMP_PHY, "Rtl819XMACPHY_ArrayDTM\n");
		dwArrayLen = MACPHY_ArrayLengthDTM;
		pdwArray = Rtl819XMACPHY_ArrayDTM;
	}
	else if(priv->bTXPowerDataReadFromEEPORM)
#endif
	 if(priv->bTXPowerDataReadFromEEPORM)
	{
		RT_TRACE(COMP_PHY, "Rtl819XMACPHY_Array_PG\n");
		dwArrayLen = MACPHY_Array_PGLength;
		pdwArray = Rtl819XMACPHY_Array_PG;

	}
	else
	{
		RT_TRACE(COMP_PHY,"Read rtl819XMACPHY_Array\n");
		dwArrayLen = MACPHY_ArrayLength;
		pdwArray = Rtl819XMACPHY_Array;
	}
