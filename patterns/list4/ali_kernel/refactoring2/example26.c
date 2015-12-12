#ifdef INT_COAL
if (!coalesced)
#endif                          
            {
                writeb(0xff, &dp6m_ptr->i960r.edoor_reg);
                writeb(0, &dp6m_ptr->i960r.sema1_reg);
            }
