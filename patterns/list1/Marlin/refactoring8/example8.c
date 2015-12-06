class SdBaseFile {
 public:
  /** Create an instance. */
  SdBaseFile() : writeError(false), type_(FAT_FILE_TYPE_CLOSED) {}
  SdBaseFile(const char* path, uint8_t oflag);
  ~SdBaseFile() {if(isOpen()) close();}
  /**
   * writeError is set to true if an error occurs during a write().
   * Set writeError to false before calling print() and/or write() and check
   * for true after calls to print() and/or write().
   */
  bool writeError;
  //----------------------------------------------------------------------------
  // helpers for stream classes
  /** get position for streams
   * \param[out] pos struct to receive position
   */
  void getpos(fpos_t* pos);
  /** set position for streams
   * \param[out] pos struct with value for new position
   */
  void setpos(fpos_t* pos);
  //----------------------------------------------------------------------------
  bool close();
  bool contiguousRange(uint32_t* bgnBlock, uint32_t* endBlock);
  bool createContiguous(SdBaseFile* dirFile,
          const char* path, uint32_t size);
  /** \return The current cluster number for a file or directory. */
  uint32_t curCluster() const {return curCluster_;}
  /** \return The current position for a file or directory. */
  uint32_t curPosition() const {return curPosition_;}
  /** \return Current working directory */
  static SdBaseFile* cwd() {return cwd_;}
  /** Set the date/time callback function
   *
   * \param[in] dateTime The user's call back function.  The callback
   * function is of the form:
   *
   * \code
   * void dateTime(uint16_t* date, uint16_t* time) {
   *   uint16_t year;
   *   uint8_t month, day, hour, minute, second;
   *
   *   // User gets date and time from GPS or real-time clock here
   *
   *   // return date using FAT_DATE macro to format fields
   *   *date = FAT_DATE(year, month, day);
   *
   *   // return time using FAT_TIME macro to format fields
   *   *time = FAT_TIME(hour, minute, second);
   * }
   * \endcode
   *
   * Sets the function that is called when a file is created or when
   * a file's directory entry is modified by sync(). All timestamps,
   * access, creation, and modify, are set when a file is created.
   * sync() maintains the last access date and last modify date/time.
   *
   * See the timestamp() function.
   */
  static void dateTimeCallback(
    void (*dateTime)(uint16_t* date, uint16_t* time)) {
    dateTime_ = dateTime;
  }
  /**  Cancel the date/time callback function. */
  static void dateTimeCallbackCancel() {dateTime_ = 0;}
  bool dirEntry(dir_t* dir);
  static void dirName(const dir_t& dir, char* name);
  bool exists(const char* name);
  int16_t fgets(char* str, int16_t num, char* delim = 0);
  /** \return The total number of bytes in a file or directory. */
  uint32_t fileSize() const {return fileSize_;}
  /** \return The first cluster number for a file or directory. */
  uint32_t firstCluster() const {return firstCluster_;}
  bool getFilename(char* name);
  /** \return True if this is a directory else false. */
  bool isDir() const {return type_ >= FAT_FILE_TYPE_MIN_DIR;}
  /** \return True if this is a normal file else false. */
  bool isFile() const {return type_ == FAT_FILE_TYPE_NORMAL;}
  /** \return True if this is an open file/directory else false. */
  bool isOpen() const {return type_ != FAT_FILE_TYPE_CLOSED;}
  /** \return True if this is a subdirectory else false. */
  bool isSubDir() const {return type_ == FAT_FILE_TYPE_SUBDIR;}
  /** \return True if this is the root directory. */
  bool isRoot() const {
    return type_ == FAT_FILE_TYPE_ROOT_FIXED || type_ == FAT_FILE_TYPE_ROOT32;
  }
  void ls( uint8_t flags = 0, uint8_t indent = 0);
  bool mkdir(SdBaseFile* dir, const char* path, bool pFlag = true);
  // alias for backward compactability
  bool makeDir(SdBaseFile* dir, const char* path) {
    return mkdir(dir, path, false);
  }
  bool open(SdBaseFile* dirFile, uint16_t index, uint8_t oflag);
  bool open(SdBaseFile* dirFile, const char* path, uint8_t oflag);
  bool open(const char* path, uint8_t oflag = O_READ);
  bool openNext(SdBaseFile* dirFile, uint8_t oflag);
  bool openRoot(SdVolume* vol);
  int peek();
  static void printFatDate(uint16_t fatDate);
  static void printFatTime( uint16_t fatTime);
  bool printName();
  int16_t read();
  int16_t read(void* buf, uint16_t nbyte);
  int8_t readDir(dir_t* dir, char* longFilename);
  static bool remove(SdBaseFile* dirFile, const char* path);
  bool remove();
  /** Set the file's current position to zero. */
  void rewind() {seekSet(0);}
  bool rename(SdBaseFile* dirFile, const char* newPath);
  bool rmdir();
  // for backward compatibility
  bool rmDir() {return rmdir();}
  bool rmRfStar();
  /** Set the files position to current position + \a pos. See seekSet().
   * \param[in] offset The new position in bytes from the current position.
   * \return true for success or false for failure.
   */
  bool seekCur(int32_t offset) {
    return seekSet(curPosition_ + offset);
  }
  /** Set the files position to end-of-file + \a offset. See seekSet().
   * \param[in] offset The new position in bytes from end-of-file.
   * \return true for success or false for failure.
   */
  bool seekEnd(int32_t offset = 0) {return seekSet(fileSize_ + offset);}
  bool seekSet(uint32_t pos);
  bool sync();
  bool timestamp(SdBaseFile* file);
  bool timestamp(uint8_t flag, uint16_t year, uint8_t month, uint8_t day,
          uint8_t hour, uint8_t minute, uint8_t second);
  /** Type of file.  You should use isFile() or isDir() instead of type()
   * if possible.
   *
   * \return The file or directory type.
   */
  uint8_t type() const {return type_;}
  bool truncate(uint32_t size);
  /** \return SdVolume that contains this file. */
  SdVolume* volume() const {return vol_;}
  int16_t write(const void* buf, uint16_t nbyte);
//------------------------------------------------------------------------------
 private:
  // allow SdFat to set cwd_
  friend class SdFat;
  // global pointer to cwd dir
  static SdBaseFile* cwd_;
  // data time callback function
  static void (*dateTime_)(uint16_t* date, uint16_t* time);
  // bits defined in flags_
  // should be 0X0F
  static uint8_t const F_OFLAG = (O_ACCMODE | O_APPEND | O_SYNC);
  // sync of directory entry required
  static uint8_t const F_FILE_DIR_DIRTY = 0X80;

  // private data
  uint8_t   flags_;         // See above for definition of flags_ bits
  uint8_t   fstate_;        // error and eof indicator
  uint8_t   type_;          // type of file see above for values
  uint32_t  curCluster_;    // cluster for current file position
  uint32_t  curPosition_;   // current file position in bytes from beginning
  uint32_t  dirBlock_;      // block for this files directory entry
  uint8_t   dirIndex_;      // index of directory entry in dirBlock
  uint32_t  fileSize_;      // file size in bytes
  uint32_t  firstCluster_;  // first cluster of file
  SdVolume* vol_;           // volume where file is located

  /** experimental don't use */
  bool openParent(SdBaseFile* dir);
  // private functions
  bool addCluster();
  bool addDirCluster();
  dir_t* cacheDirEntry(uint8_t action);
  int8_t lsPrintNext( uint8_t flags, uint8_t indent);
  static bool make83Name(const char* str, uint8_t* name, const char** ptr);
  bool mkdir(SdBaseFile* parent, const uint8_t dname[11]);
  bool open(SdBaseFile* dirFile, const uint8_t dname[11], uint8_t oflag);
  bool openCachedEntry(uint8_t cacheIndex, uint8_t oflags);
  dir_t* readDirCache();
//------------------------------------------------------------------------------
// to be deleted
  static void printDirName( const dir_t& dir,
    uint8_t width, bool printSlash);
//------------------------------------------------------------------------------
// Deprecated functions  - suppress cpplint warnings with NOLINT comment
#if ALLOW_DEPRECATED_FUNCTIONS && !defined(DOXYGEN)
 public:
  /** \deprecated Use:
   * bool contiguousRange(uint32_t* bgnBlock, uint32_t* endBlock);
   * \param[out] bgnBlock the first block address for the file.
   * \param[out] endBlock the last  block address for the file.
   * \return true for success or false for failure.
   */
  bool contiguousRange(uint32_t& bgnBlock, uint32_t& endBlock) {  // NOLINT
    return contiguousRange(&bgnBlock, &endBlock);
  }
 /** \deprecated Use:
   * bool createContiguous(SdBaseFile* dirFile,
   *   const char* path, uint32_t size)
   * \param[in] dirFile The directory where the file will be created.
   * \param[in] path A path with a valid DOS 8.3 file name.
   * \param[in] size The desired file size.
   * \return true for success or false for failure.
   */
  bool createContiguous(SdBaseFile& dirFile,  // NOLINT
    const char* path, uint32_t size) {
    return createContiguous(&dirFile, path, size);
  }
  /** \deprecated Use:
   * static void dateTimeCallback(
   *   void (*dateTime)(uint16_t* date, uint16_t* time));
   * \param[in] dateTime The user's call back function.
   */
  static void dateTimeCallback(
    void (*dateTime)(uint16_t& date, uint16_t& time)) {  // NOLINT
    oldDateTime_ = dateTime;
    dateTime_ = dateTime ? oldToNew : 0;
  }
  /** \deprecated Use: bool dirEntry(dir_t* dir);
   * \param[out] dir Location for return of the file's directory entry.
   * \return true for success or false for failure.
   */
  bool dirEntry(dir_t& dir) {return dirEntry(&dir);}  // NOLINT
  /** \deprecated Use:
   * bool mkdir(SdBaseFile* dir, const char* path);
   * \param[in] dir An open SdFat instance for the directory that will contain
   * the new directory.
   * \param[in] path A path with a valid 8.3 DOS name for the new directory.
   * \return true for success or false for failure.
   */
  bool mkdir(SdBaseFile& dir, const char* path) {  // NOLINT
    return mkdir(&dir, path);
  }
  /** \deprecated Use:
   * bool open(SdBaseFile* dirFile, const char* path, uint8_t oflag);
   * \param[in] dirFile An open SdFat instance for the directory containing the
   * file to be opened.
   * \param[in] path A path with a valid 8.3 DOS name for the file.
   * \param[in] oflag Values for \a oflag are constructed by a bitwise-inclusive
   * OR of flags O_READ, O_WRITE, O_TRUNC, and O_SYNC.
   * \return true for success or false for failure.
   */
  bool open(SdBaseFile& dirFile, // NOLINT
    const char* path, uint8_t oflag) {
    return open(&dirFile, path, oflag);
  }
  /** \deprecated  Do not use in new apps
   * \param[in] dirFile An open SdFat instance for the directory containing the
   * file to be opened.
   * \param[in] path A path with a valid 8.3 DOS name for a file to be opened.
   * \return true for success or false for failure.
   */
  bool open(SdBaseFile& dirFile, const char* path) {  // NOLINT
    return open(dirFile, path, O_RDWR);
  }
  /** \deprecated Use:
   * bool open(SdBaseFile* dirFile, uint16_t index, uint8_t oflag);
   * \param[in] dirFile An open SdFat instance for the directory.
   * \param[in] index The \a index of the directory entry for the file to be
   * opened.  The value for \a index is (directory file position)/32.
   * \param[in] oflag Values for \a oflag are constructed by a bitwise-inclusive
   * OR of flags O_READ, O_WRITE, O_TRUNC, and O_SYNC.
   * \return true for success or false for failure.
   */
  bool open(SdBaseFile& dirFile, uint16_t index, uint8_t oflag) {  // NOLINT
    return open(&dirFile, index, oflag);
  }
  /** \deprecated Use: bool openRoot(SdVolume* vol);
   * \param[in] vol The FAT volume containing the root directory to be opened.
   * \return true for success or false for failure.
   */
  bool openRoot(SdVolume& vol) {return openRoot(&vol);}  // NOLINT
  /** \deprecated Use: int8_t readDir(dir_t* dir);
   * \param[out] dir The dir_t struct that will receive the data.
   * \return bytes read for success zero for eof or -1 for failure.
   */
  int8_t readDir(dir_t& dir, char* longFilename) {return readDir(&dir, longFilename);}  // NOLINT
  /** \deprecated Use:
   * static uint8_t remove(SdBaseFile* dirFile, const char* path);
   * \param[in] dirFile The directory that contains the file.
   * \param[in] path The name of the file to be removed.
   * \return true for success or false for failure.
   */
  static bool remove(SdBaseFile& dirFile, const char* path) {  // NOLINT
    return remove(&dirFile, path);
  }
//------------------------------------------------------------------------------
// rest are private
 private:
  static void (*oldDateTime_)(uint16_t& date, uint16_t& time);  // NOLINT
  static void oldToNew(uint16_t* date, uint16_t* time) {
    uint16_t d;
    uint16_t t;
    oldDateTime_(d, t);
    *date = d;
    *time = t;
  }
#endif  // ALLOW_DEPRECATED_FUNCTIONS
}
