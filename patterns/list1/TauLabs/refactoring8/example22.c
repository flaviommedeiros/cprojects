class DynamicImages {
 public:
  explicit DynamicImages(mach_port_t task);

  ~DynamicImages() {
    for (int i = 0; i < GetImageCount(); ++i) {
      delete image_list_[i];
    }
  }

  // Returns the number of dynamically loaded mach-o images.
  int GetImageCount() const {return static_cast<int>(image_list_.size());}

  // Returns an individual image.
  DynamicImage *GetImage(int i) {
    if (i < (int)image_list_.size()) {
      return image_list_[i];
    }
    return NULL;
  }

  // Returns the image corresponding to the main executable.
  DynamicImage *GetExecutableImage();
  int GetExecutableImageIndex();

  // Returns the task which we're looking at.
  mach_port_t GetTask() const {return task_;}

  // CPU type of the task
  cpu_type_t GetCPUType() {return cpu_type_;}

  // Return true if the task is a 64-bit architecture.
  bool Is64Bit() { return (GetCPUType() & CPU_ARCH_ABI64) == CPU_ARCH_ABI64; }

  // Determine the CPU type of the task being dumped.
  static cpu_type_t DetermineTaskCPUType(task_t task);

  // Get the native CPU type of this task.
  static cpu_type_t GetNativeCPUType() {
#if defined(__i386__)
    return CPU_TYPE_I386;
#elif defined(__x86_64__)
    return CPU_TYPE_X86_64;
#elif defined(__ppc__)
    return CPU_TYPE_POWERPC;
#elif defined(__ppc64__)
    return CPU_TYPE_POWERPC64;
#elif defined(__arm__)
    return CPU_TYPE_ARM;
#elif defined(__arm64__)
    return CPU_TYPE_ARM64;
#else
#error "GetNativeCPUType not implemented for this architecture"
#endif
  }

 private:
  template<typename MachBits>
  friend void ReadImageInfo(DynamicImages& images, uint64_t image_list_address);

  bool IsOurTask() {return task_ == mach_task_self();}

  // Initialization
  void ReadImageInfoForTask();
  uint64_t GetDyldAllImageInfosPointer();

  mach_port_t              task_;
  cpu_type_t               cpu_type_;  // CPU type of task_
  vector<DynamicImageRef>  image_list_;
}
