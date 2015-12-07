if(isStorageDevice(device_name)
#ifdef BCM_MMC
			|| isMMCDevice(device_name)
#endif
			){
		// Get USB node.
		if(get_usb_node_by_device(device_name, usb_node, 32) == NULL){
			usb_dbg("(%s): Fail to get usb node.\n", device_name);
			free_disk_data(&follow_disk_info);
			return NULL;
		}

		if(get_path_by_node(usb_node, port_path, 8) == NULL){
			usb_dbg("(%s): Fail to get usb path.\n", usb_node);
			free_disk_data(&follow_disk_info);
			return NULL;
		}

		// Get USB port.
		if(get_usb_port_by_string(usb_node, buf, 64) == NULL){
			usb_dbg("Fail to get usb port: %s.\n", usb_node);
			free_disk_data(&follow_disk_info);
			return NULL;
		}

		len = strlen(buf);
		if(len > 0){
			port = (char *)malloc(8);
			if(port == NULL){
				usb_dbg("No memory!!(port)\n");
				free_disk_data(&follow_disk_info);
				return NULL;
			}
			memset(port, 0, 8);
			strncpy(port, port_path, 8);

			follow_disk_info->port = port;
		}

		// start get vendor.
		get_disk_vendor(device_name, buf, 64);

		len = strlen(buf);
		if(len > 0){
			vendor = (char *)malloc(len+1);
			if(vendor == NULL){
				usb_dbg("No memory!!(vendor)\n");
				free_disk_data(&follow_disk_info);
				return NULL;
			}
			strncpy(vendor, buf, len);
			vendor[len] = 0;
			strntrim(vendor);

			follow_disk_info->vendor = vendor;
		}

		// start get model.
		get_disk_model(device_name, buf, 64);

		len = strlen(buf);
		if(len > 0){
			model = (char *)malloc(len+1);
			if(model == NULL){
				usb_dbg("No memory!!(model)\n");
				free_disk_data(&follow_disk_info);
				return NULL;
			}
			strncpy(model, buf, len);
			model[len] = 0;
			strntrim(model);

			follow_disk_info->model = model;
		}

		// get USB's tag
		memset(buf, 0, 64);
		len = 0;
		ptr = buf;
		if(vendor != NULL){
			len += strlen(vendor);
			strcpy(ptr, vendor);
			ptr += len;
		}
		if(model != NULL){
			if(len > 0){
				++len; // Add a space between vendor and model.
				strcpy(ptr, " ");
				++ptr;
			}
			len += strlen(model);
			strcpy(ptr, model);
			ptr += len;
		}

		if(len > 0){
			follow_disk_info->tag = (char *)malloc(len+1);
			if(follow_disk_info->tag == NULL){
				usb_dbg("No memory!!(follow_disk_info->tag)\n");
				free_disk_data(&follow_disk_info);
				return NULL;
			}
			strcpy(follow_disk_info->tag, buf);
			follow_disk_info->tag[len] = 0;
		}
		else{
#ifdef BCM_MMC
			if(isMMCDevice(device_name))
				len = strlen(DEFAULT_MMC_TAG);
			else
#endif
				len = strlen(DEFAULT_USB_TAG);

			follow_disk_info->tag = (char *)malloc(len+1);
			if(follow_disk_info->tag == NULL){
				usb_dbg("No memory!!(follow_disk_info->tag)\n");
				free_disk_data(&follow_disk_info);
				return NULL;
			}
#ifdef BCM_MMC
			if(isMMCDevice(device_name))
				strcpy(follow_disk_info->tag, DEFAULT_MMC_TAG);
			else
#endif
				strcpy(follow_disk_info->tag, DEFAULT_USB_TAG);
			follow_disk_info->tag[len] = 0;
		}

		follow_partition_list = &(follow_disk_info->partitions);
		while(*follow_partition_list != NULL)
			follow_partition_list = &((*follow_partition_list)->next);

		new_partition_info = create_partition(device_name, follow_partition_list);
		if(new_partition_info != NULL){
			new_partition_info->disk = follow_disk_info;

			++(follow_disk_info->partition_number);
			++(follow_disk_info->mounted_number);
			if(!strcmp(new_partition_info->device, follow_disk_info->device))
				new_partition_info->size_in_kilobytes = follow_disk_info->size_in_kilobytes-4;
		}
	}
