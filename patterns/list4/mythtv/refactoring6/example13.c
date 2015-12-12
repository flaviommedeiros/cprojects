if (avctx->thread_safe_callbacks || (
#if FF_API_GET_BUFFER
        !avctx->get_buffer &&
#endif
        avctx->get_buffer2 == avcodec_default_get_buffer2)) {
FF_ENABLE_DEPRECATION_WARNINGS
        err = ff_get_buffer(avctx, f->f, flags);
    } else {
        pthread_mutex_lock(&p->progress_mutex);
        p->requested_frame = f->f;
        p->requested_flags = flags;
        p->state = STATE_GET_BUFFER;
        pthread_cond_broadcast(&p->progress_cond);

        while (p->state != STATE_SETTING_UP)
            pthread_cond_wait(&p->progress_cond, &p->progress_mutex);

        err = p->result;

        pthread_mutex_unlock(&p->progress_mutex);

    }
