#if defined(CONFIG_IMQ) || defined(CONFIG_IMQ_MODULE)
if (!(skb->imq_flags & IMQ_F_ENQUEUE))
#endif
			dev_queue_xmit_nit(skb, dev);
