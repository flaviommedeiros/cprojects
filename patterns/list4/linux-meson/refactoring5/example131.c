#ifdef CONFIG_WFD
if ( _AES_ != padapter->securitypriv.dot11PrivacyAlgrthm ) {
			if ( padapter->wdinfo.wfd_tdls_weaksec == _TRUE)
				issue_tdls_setup_req(padapter, &txmgmt, _TRUE);
			else
				DBG_871X( "[%s] Current link is not AES, SKIP sending the tdls setup request!!\n", __FUNCTION__ );
		} else
#endif // CONFIG_WFD
		{
			issue_tdls_setup_req(padapter, &txmgmt, _TRUE);
		}
