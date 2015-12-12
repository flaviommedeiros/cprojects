#ifdef SW_USE_RINGBUFFER
if (task->info.type == SW_EVENT_PACKAGE)
    {
        swPackage package;
        memcpy(&package, task->data, sizeof(package));
        swReactorThread *thread = swServer_get_thread(SwooleG.serv, task->info.from_id);
        thread->buffer_input->free(thread->buffer_input, package.data);
        swWarn("[1]received the wrong data[%d bytes] from socket#%d", package.length, fd);
    }
    else
#endif
    {
        swWarn("[1]received the wrong data[%d bytes] from socket#%d", task->info.len, fd);
    }
