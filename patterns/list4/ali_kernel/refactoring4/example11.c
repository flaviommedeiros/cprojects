#ifdef HAVE_PCI_ERS
if (adapter->config_space == NULL)
#else
	WARN_ON(adapter->config_space != NULL);
