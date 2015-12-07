#ifdef USE_RBPS
if (iov->iov_base & RBP_SMALLBUF)
				memcpy(skb_put(skb, iov->iov_len),
					he_dev->rbps_virt[RBP_INDEX(iov->iov_base)].virt, iov->iov_len);
			else
#endif
				memcpy(skb_put(skb, iov->iov_len),
					he_dev->rbpl_virt[RBP_INDEX(iov->iov_base)].virt, iov->iov_len);
