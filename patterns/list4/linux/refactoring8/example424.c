static void afiucv_hs_callback_txnotify(struct sk_buff *, enum iucv_tx_notify);

/* Call Back functions */
static void iucv_callback_rx(struct iucv_path *, struct iucv_message *);
static void iucv_callback_txdone(struct iucv_path *, struct iucv_message *);
static void iucv_callback_connack(struct iucv_path *, u8 *);
static int iucv_callback_connreq(struct iucv_path *, u8 *, u8 *);
static void iucv_callback_connrej(struct iucv_path *, u8 *);
static void iucv_callback_shutdown(struct iucv_path *, u8 *);

static struct iucv_sock_list iucv_sk_list = {
	.lock = __RW_LOCK_UNLOCKED(iucv_sk_list.lock),
	.autobind_name = ATOMIC_INIT(0)
};

static struct iucv_handler af_iucv_handler = {
	.path_pending	  = iucv_callback_connreq,
	.path_complete	  = iucv_callback_connack,
	.path_severed	  = iucv_callback_connrej,
	.message_pending  = iucv_callback_rx,
	.message_complete = iucv_callback_txdone,
	.path_quiesced	  = iucv_callback_shutdown,
};

static inline void high_nmcpy(unsigned char *dst, char *src)
{
       memcpy(dst, src, 8);
}

static inline void low_nmcpy(unsigned char *dst, char *src)
{
       memcpy(&dst[8], src, 8);
}

static int afiucv_pm_prepare(struct device *dev)
{
#ifdef CONFIG_PM_DEBUG
	printk(KERN_WARNING "afiucv_pm_prepare\n");
#endif
	return 0;
}
