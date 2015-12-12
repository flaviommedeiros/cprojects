if (!device_create(unifi_class,
#ifdef SDIO_EXPORTS_STRUCT_DEVICE
                       priv->unifi_device,
#else
                       NULL,
#endif /* SDIO_EXPORTS_STRUCT_DEVICE */
                       devno, priv, "unifiudi%d", bus_id)) {
        device_destroy(unifi_class, priv->unifi_cdev.dev);
        cdev_del(&priv->unifiudi_cdev);
        cdev_del(&priv->unifi_cdev);
        return -EINVAL;
    }
