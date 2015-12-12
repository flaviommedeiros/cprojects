static struct ccid_operations *ccids[] = {
	&ccid2_ops,
#ifdef CONFIG_IP_DCCP_CCID3
	&ccid3_ops,
#endif
};
