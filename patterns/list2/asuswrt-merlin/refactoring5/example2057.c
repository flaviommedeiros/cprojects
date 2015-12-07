#ifdef CONFIG_INET_GRO
if (atomic_read(&gro_timer_init)) {
				spin_lock_bh(&gro_lock);
				napi_gro_receive(&gro_napi, skb);
				spin_unlock_bh(&gro_lock);
			}
			else
#endif /* CONFIG_INET_GRO */
			__netif_receive_skb(skb);
