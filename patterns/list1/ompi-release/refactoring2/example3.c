#if !OMPI_ENABLE_THREAD_MULTIPLE
if( OPAL_UNLIKELY(NULL == recvreq) )
#endif  /* !OMPI_ENABLE_THREAD_MULTIPLE */
        {
            MCA_PML_OB1_RECV_REQUEST_ALLOC(recvreq);
            if (NULL == recvreq)
                return OMPI_ERR_TEMP_OUT_OF_RESOURCE;
#if !OMPI_ENABLE_THREAD_MULTIPLE
            mca_pml_ob1_recvreq = recvreq;
#endif  /* !OMPI_ENABLE_THREAD_MULTIPLE */
        }
