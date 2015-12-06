#if !OMPI_ENABLE_THREAD_MULTIPLE
if( OPAL_UNLIKELY(NULL == sendreq) )
#endif  /* !OMPI_ENABLE_THREAD_MULTIPLE */
        {
            MCA_PML_OB1_SEND_REQUEST_ALLOC(comm, dst, sendreq);
            if (NULL == sendreq)
                return OMPI_ERR_TEMP_OUT_OF_RESOURCE;
#if !OMPI_ENABLE_THREAD_MULTIPLE
            mca_pml_ob1_sendreq = sendreq;
#endif  /* !OMPI_ENABLE_THREAD_MULTIPLE */
        }
