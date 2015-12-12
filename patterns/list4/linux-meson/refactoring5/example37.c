#ifdef D2D3_SUPPORT
if (d2d3_enable) {
			local_buf_num = di_mem_size/(di_buf_size + dp_buf_size);
			dp_mem_start = di_mem_start + di_buf_size*local_buf_num;
		}
		else
#endif
		local_buf_num = di_mem_size/di_buf_size;
