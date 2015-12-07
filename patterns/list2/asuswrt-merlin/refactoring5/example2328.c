#ifdef INT_COAL
if (coalesced)
                    ha->status = pcs->ext_status & 0xffff;
                else 
#endif
                    ha->status = readw(&dp6m_ptr->i960r.status);
