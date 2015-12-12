static const zend_function_entry swoole_client_methods[] =
{
    PHP_ME(swoole_client, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(swoole_client, __destruct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
    PHP_ME(swoole_client, set, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, connect, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, recv, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, send, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, sendfile, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, sendto, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, sleep, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, wakeup, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, isConnected, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, getsockname, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, getpeername, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, close, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_client, on, NULL, ZEND_ACC_PUBLIC)
#ifdef SWOOLE_SOCKETS_SUPPORT
    PHP_ME(swoole_client, getSocket, NULL, ZEND_ACC_PUBLIC)
#endif
    PHP_FE_END
};
