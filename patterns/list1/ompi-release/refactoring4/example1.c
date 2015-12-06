#ifndef ROMIO_HAVE_AIO_CALLS_NEED_FILEDES
if (wr) err = aio_write(aiocbp);
    else err = aio_read(aiocbp);
