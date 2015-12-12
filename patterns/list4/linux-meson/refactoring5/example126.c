#ifdef CONFIG_WFD
if (_AES_ != padapter->securitypriv.dot11PrivacyAlgrthm) {
		/* Weak Security situation with AP. */
		if (0 == pwdinfo->wfd_tdls_weaksec) 	{
			/* Can't send the tdls setup request out!! */
			DBG_871X("[%s] Current link is not AES, "
				"SKIP sending the tdls setup request!!\n", __FUNCTION__);
		} else {
			issue_tdls_setup_req(padapter, &txmgmt, _TRUE);
		}
	} else
#endif /* CONFIG_WFD */
	{
		issue_tdls_setup_req(padapter, &txmgmt, _TRUE);
	}
