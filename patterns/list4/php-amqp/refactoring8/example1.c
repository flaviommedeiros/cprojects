zend_function_entry amqp_connection_class_functions[] = {
		PHP_ME(amqp_connection_class, __construct, 	arginfo_amqp_connection_class__construct,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, isConnected, 	arginfo_amqp_connection_class_isConnected,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, connect, 		arginfo_amqp_connection_class_connect, 		ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, pconnect, 	arginfo_amqp_connection_class_pconnect, 	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, pdisconnect, 	arginfo_amqp_connection_class_pdisconnect,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, disconnect, 	arginfo_amqp_connection_class_disconnect,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, reconnect, 	arginfo_amqp_connection_class_reconnect,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, preconnect, 	arginfo_amqp_connection_class_preconnect,	ZEND_ACC_PUBLIC)

		PHP_ME(amqp_connection_class, getLogin, 	arginfo_amqp_connection_class_getLogin,		ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, setLogin, 	arginfo_amqp_connection_class_setLogin,		ZEND_ACC_PUBLIC)

		PHP_ME(amqp_connection_class, getPassword, 	arginfo_amqp_connection_class_getPassword,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, setPassword, 	arginfo_amqp_connection_class_setPassword,	ZEND_ACC_PUBLIC)

		PHP_ME(amqp_connection_class, getHost, 		arginfo_amqp_connection_class_getHost,		ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, setHost, 		arginfo_amqp_connection_class_setHost,		ZEND_ACC_PUBLIC)

		PHP_ME(amqp_connection_class, getPort, 		arginfo_amqp_connection_class_getPort,		ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, setPort, 		arginfo_amqp_connection_class_setPort,		ZEND_ACC_PUBLIC)

		PHP_ME(amqp_connection_class, getVhost, 	arginfo_amqp_connection_class_getVhost,		ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, setVhost, 	arginfo_amqp_connection_class_setVhost,		ZEND_ACC_PUBLIC)

		PHP_ME(amqp_connection_class, getTimeout, 	arginfo_amqp_connection_class_getTimeout,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, setTimeout, 	arginfo_amqp_connection_class_setTimeout,	ZEND_ACC_PUBLIC)

		PHP_ME(amqp_connection_class, getReadTimeout, 	arginfo_amqp_connection_class_getReadTimeout,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, setReadTimeout, 	arginfo_amqp_connection_class_setReadTimeout,	ZEND_ACC_PUBLIC)

		PHP_ME(amqp_connection_class, getWriteTimeout, 	arginfo_amqp_connection_class_getWriteTimeout,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, setWriteTimeout, 	arginfo_amqp_connection_class_setWriteTimeout,	ZEND_ACC_PUBLIC)

		PHP_ME(amqp_connection_class, getUsedChannels, arginfo_amqp_connection_class_getUsedChannels,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, getMaxChannels,  arginfo_amqp_connection_class_getMaxChannels,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, isPersistent, 	arginfo_amqp_connection_class_isPersistent,		ZEND_ACC_PUBLIC)
#if AMQP_VERSION_MAJOR * 100 + AMQP_VERSION_MINOR * 10 + AMQP_VERSION_PATCH > 52
		PHP_ME(amqp_connection_class, getHeartbeatInterval,  arginfo_amqp_connection_class_getHeartbeatInterval,	ZEND_ACC_PUBLIC)
		PHP_ME(amqp_connection_class, getMaxFrameSize,  arginfo_amqp_connection_class_getMaxFrameSize,	ZEND_ACC_PUBLIC)
#endif
		{NULL, NULL, NULL}	/* Must be the last line in amqp_functions[] */
};
