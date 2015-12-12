static const zend_function_entry swoole_process_methods[] =
{
    PHP_ME(swoole_process, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(swoole_process, __destruct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
    PHP_ME(swoole_process, wait, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(swoole_process, signal, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(swoole_process, kill, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(swoole_process, daemon, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
#ifdef HAVE_CPU_AFFINITY
    PHP_ME(swoole_process, setaffinity, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
#endif
    PHP_ME(swoole_process, useQueue, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_process, start, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_process, write, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_process, close, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_process, read, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_process, push, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_process, pop, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_process, exit, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_process, exec, NULL, ZEND_ACC_PUBLIC)
    PHP_FALIAS(name, swoole_set_process_name, NULL)
    PHP_FE_END
};
