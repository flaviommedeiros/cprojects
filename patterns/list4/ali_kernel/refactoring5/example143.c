#ifdef QOS_DLS_SUPPORT
if (pEntry->ValidAsDls == TRUE)
				pEntry->PortSecured = WPA_802_1X_PORT_SECURED;
			else
#endif //QOS_DLS_SUPPORT
#endif // CONFIG_STA_SUPPORT //
				pEntry->PortSecured = WPA_802_1X_PORT_NOT_SECURED;
