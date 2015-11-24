#if OPAL_CUDA_SUPPORT
if (mca_pml_ob1_cuda_need_buffers(recvreq, btl))
#endif /* OPAL_CUDA_SUPPORT */
        {
            mca_pml_ob1_recv_request_ack(recvreq, &hdr->hdr_rndv, 0);
            return;
        }
