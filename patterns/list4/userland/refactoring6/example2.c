if (target == EGL_NATIVE_PIXMAP_KHR
#ifdef EGL_BRCM_image_wrap
            || target == EGL_IMAGE_WRAP_BRCM
#endif
#ifdef EGL_BRCM_image_wrap_bcg
            || target == EGL_IMAGE_WRAP_BRCM_BCG
#endif
#if EGL_ANDROID_image_native_buffer
            || target == EGL_NATIVE_BUFFER_ANDROID
            || target == EGL_IMAGE_BRCM_RAW_PIXELS
#endif
            || target == EGL_IMAGE_BRCM_MULTIMEDIA
            || target == EGL_IMAGE_BRCM_MULTIMEDIA_Y
            || target == EGL_IMAGE_BRCM_MULTIMEDIA_U
            || target == EGL_IMAGE_BRCM_MULTIMEDIA_V
            || target == EGL_IMAGE_BRCM_DUPLICATE
            ) {
            context = NULL;
            ctx_error = ctx != EGL_NO_CONTEXT;
         } else {
            context = client_egl_get_context(thread, process, ctx);
            ctx_error = !context;
         }
