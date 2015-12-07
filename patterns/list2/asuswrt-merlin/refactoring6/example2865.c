if ( ( descp->BUF_CNT == HFS_TYPE )
#if (HCF_TYPE) & HCF_TYPE_CCX
			 || ( descp->BUF_CNT == HFS_DAT )
#endif // HCF_TYPE_CCX
		) { // perform decapsulation if needed
			descp->next_desc_addr->buf_phys_addr -= HCF_DASA_SIZE;
			descp->next_desc_addr->BUF_CNT 		 += HCF_DASA_SIZE;
		}
