if(vchi_bulk_queue_receive( vc_filesys_client.open_handle,
#if VCHI_BULK_ALIGN > 1
                                        align_bytes ? vc_filesys_client.bulk_buffer : bulk_addr,
#else
                                        bulk_addr,
#endif
                                        (bulk_sectors*FILESERV_SECTOR_LENGTH), VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE, NULL) != 0)
               break;
