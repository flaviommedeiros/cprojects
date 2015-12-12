#ifndef SW_USE_RINGBUFFER
if (SwooleTG.factory_lock_target)
        {
            if (SwooleTG.factory_target_worker < 0)
            {
                target_worker_id = swServer_worker_schedule(serv, schedule_key);
                SwooleTG.factory_target_worker = target_worker_id;
            }
            else
            {
                target_worker_id = SwooleTG.factory_target_worker;
            }
        }
        else
#endif
        {
            target_worker_id = swServer_worker_schedule(serv, schedule_key);
        }
