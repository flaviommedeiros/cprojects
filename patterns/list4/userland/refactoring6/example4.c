if (output
#if USE_CONTAINER
                || container
#endif
                )
            {
               mmal_buffer_header_mem_lock(buffer);
#if USE_CONTAINER
               test_container_write(container, buffer);
#else
               LOG_ERROR("Write %d bytes of data from %p", buffer->length, buffer->data);
               fwrite(buffer->data, 1, buffer->length, output);
#endif
               mmal_buffer_header_mem_unlock(buffer);
               packet_count++;
               if (packet_count > MAX_PACKET_COUNT)
               {
#if USE_CONTAINER
                  vc_container_close(container);
                  container = 0;
#else
                  fclose(output);
#endif
                  output = NULL;
                  fprintf(stderr, "All packets written\n");
               }
            }
