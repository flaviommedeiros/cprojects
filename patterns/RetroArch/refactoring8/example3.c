static int exynos_realloc_buffer(struct exynos_data *pdata,
      enum exynos_buffer_type type, unsigned size)
{
   struct exynos_bo *buf = pdata->buf[type];

   if (!buf)
      return -1;

   if (size > buf->size)
   {
      unsigned i;

#if (EXYNOS_GFX_DEBUG_LOG == 1)
      RARCH_LOG("[video_exynos]: reallocating %s buffer (%u -> %u bytes)\n",
            exynos_buffer_name(type), buf->size, size);
#endif

      exynos_bo_destroy(buf);
      buf = exynos_create_mapped_buffer(pdata->device, size);

      if (!buf)
      {
         RARCH_ERR("[video_exynos]: reallocation failed\n");
         return -1;
      }

      pdata->buf[type] = buf;

      /* Map new GEM buffer to the G2D images backed by it. */
      for (i = 0; i < EXYNOS_IMAGE_COUNT; ++i)
      {
         if (defaults[i].buf_type == type)
            pdata->src[i]->bo[0] = buf->handle;
      }
   }

   return 0;
}
