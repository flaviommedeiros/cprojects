class PointerWrap
{
    // This makes it a compile error if you forget to define DoState() on non-POD.
    // Which also can be a problem, for example struct tm is non-POD on linux, for whatever reason...
#ifdef _MSC_VER
    template<typename T, bool isPOD = std::is_pod<T>::value, bool isPointer = std::is_pointer<T>::value>
#else
    template<typename T, bool isPOD = __is_pod(T), bool isPointer = std::is_pointer<T>::value>
#endif
    struct DoHelper
    {
        static void DoArray(PointerWrap *p, T *x, int count)
        {
            for (int i = 0; i < count; ++i)
                p->Do(x[i]);
        }

        static void Do(PointerWrap *p, T &x)
        {
            p->DoClass(x);
        }
    };

    template<typename T>
    struct DoHelper<T, true, false>
    {
        static void DoArray(PointerWrap *p, T *x, int count)
        {
            p->DoVoid((void *)x, sizeof(T) * count);
        }

        static void Do(PointerWrap *p, T &x)
        {
            p->DoVoid((void *)&x, sizeof(x));
        }
    };

public:
    enum Mode {
        MODE_READ = 1, // load
        MODE_WRITE, // save
        MODE_MEASURE, // calculate size
        MODE_VERIFY, // compare
    };

    enum Error {
        ERROR_NONE = 0,
        ERROR_WARNING = 1,
        ERROR_FAILURE = 2,
    };

    u8 **ptr;
    Mode mode;
    Error error;

public:
    PointerWrap(u8 **ptr_, Mode mode_) : ptr(ptr_), mode(mode_), error(ERROR_NONE) {}
    PointerWrap(unsigned char **ptr_, int mode_) : ptr((u8**)ptr_), mode((Mode)mode_), error(ERROR_NONE) {}

    PointerWrapSection Section(const char *title, int ver) {
        return Section(title, ver, ver);
    }

    // The returned object can be compared against the version that was loaded.
    // This can be used to support versions as old as minVer.
    // Version = 0 means the section was not found.
    PointerWrapSection Section(const char *title, int minVer, int ver) {
        char marker[16] = {0};
        int foundVersion = ver;

        strncpy(marker, title, sizeof(marker));
        if (!ExpectVoid(marker, sizeof(marker)))
        {
            // Might be before we added name markers for safety.
            if (foundVersion == 1 && ExpectVoid(&foundVersion, sizeof(foundVersion)))
                DoMarker(title);
            // Wasn't found, but maybe we can still load the state.
            else
                foundVersion = 0;
        }
        else
            Do(foundVersion);

        if (error == ERROR_FAILURE || foundVersion < minVer || foundVersion > ver) {
            LOG_ERROR(Common, "Savestate failure: wrong version %d found for %s", foundVersion, title);
            SetError(ERROR_FAILURE);
            return PointerWrapSection(*this, -1, title);
        }
        return PointerWrapSection(*this, foundVersion, title);
    }

    void SetMode(Mode mode_) {mode = mode_;}
    Mode GetMode() const {return mode;}
    u8 **GetPPtr() {return ptr;}
    void SetError(Error error_)
    {
        if (error < error_)
            error = error_;
        if (error > ERROR_WARNING)
            mode = PointerWrap::MODE_MEASURE;
    }

    bool ExpectVoid(void *data, int size)
    {
        switch (mode) {
        case MODE_READ:    if (memcmp(data, *ptr, size) != 0) return false; break;
        case MODE_WRITE: memcpy(*ptr, data, size); break;
        case MODE_MEASURE: break;  // MODE_MEASURE - don't need to do anything
        case MODE_VERIFY:
            for (int i = 0; i < size; i++) {
                DEBUG_ASSERT_MSG(((u8*)data)[i] == (*ptr)[i],
                    "Savestate verification failure: %d (0x%X) (at %p) != %d (0x%X) (at %p).\n",
                    ((u8*)data)[i], ((u8*)data)[i], &((u8*)data)[i],
                    (*ptr)[i], (*ptr)[i], &(*ptr)[i]);
            }
            break;
        default: break;  // throw an error?
        }
        (*ptr) += size;
        return true;
    }

    void DoVoid(void *data, int size)
    {
        switch (mode) {
        case MODE_READ:    memcpy(data, *ptr, size); break;
        case MODE_WRITE: memcpy(*ptr, data, size); break;
        case MODE_MEASURE: break;  // MODE_MEASURE - don't need to do anything
        case MODE_VERIFY:
            for (int i = 0; i < size; i++) {
                DEBUG_ASSERT_MSG(((u8*)data)[i] == (*ptr)[i],
                    "Savestate verification failure: %d (0x%X) (at %p) != %d (0x%X) (at %p).\n",
                    ((u8*)data)[i], ((u8*)data)[i], &((u8*)data)[i],
                    (*ptr)[i], (*ptr)[i], &(*ptr)[i]);
            }
            break;
        default: break;  // throw an error?
        }
        (*ptr) += size;
    }

    template<class K, class T>
    void Do(std::map<K, T *> &x)
    {
        if (mode == MODE_READ)
        {
            for (auto it = x.begin(), end = x.end(); it != end; ++it)
            {
                if (it->second != nullptr)
                    delete it->second;
            }
        }
        T *dv = nullptr;
        DoMap(x, dv);
    }
