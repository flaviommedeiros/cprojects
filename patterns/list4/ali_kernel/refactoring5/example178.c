#ifdef ZM_DONT_COPY_RX_BUFFER
if (rxBufPoolIndex == 0)
                {
                    new_buf = skb_clone(buf, GFP_ATOMIC);

                    new_buf->data = &(buf->data[chk_idx+4]);
                    new_buf->len = pkt_len;
                }
                else
                {
        #endif
                /* Allocate a skb buffer */
                new_buf = dev_alloc_skb(ZM_MAX_RX_BUFFER_SIZE);

                /* Set skb buffer length */
            #ifdef NET_SKBUFF_DATA_USES_OFFSET
                new_buf->tail = 0;
                new_buf->len = 0;
            #else
                new_buf->tail = new_buf->data;
                new_buf->len = 0;
            #endif

                skb_put(new_buf, pkt_len);

                /* Copy the buffer */
                memcpy(new_buf->data, &(buf->data[chk_idx+4]), pkt_len);

        #ifdef ZM_DONT_COPY_RX_BUFFER
                }
