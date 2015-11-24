class _OWLCLASS TBarDescr 
{
  public:
  	
/// Used by TBarDescr, the TGroup enum describes the following constants that define
/// the index of the entry in the GroupCount array.
    enum TGroup 
    {
      FileGroup,				///< Index of the File gadget group count
      EditGroup,				///< Index of the Edit gadget group count
      ContainerGroup,		///< Index of the Container gadget group count
      ObjectGroup,			///< Index of the Object gadget group count
      WindowGroup,			///< Index of the Window gadget group count
      HelpGroup,				///< Index of the Help gadget group count
      NumGroups					///< Total number of groups
    };
  public:
    TBarDescr(); // for internal use
    TBarDescr(TResId id, int fg, int eg, int cg, int og, int wg, int hg,
               TModule* module = &GetGlobalModule());
    TBarDescr(TResId id, TModule* module = &GetGlobalModule());
    virtual ~TBarDescr();

    TBarDescr& operator =(const TBarDescr& original);

    bool      SetBitmap(const TResId newResId, TModule* module);
    TResId  GetId() const;
    int     GetGroupCount(int group) const;
    bool    RemoveGadgets(TGadgetWindow& destWindow);
    void    SetBuilder(const TGadgetFunctor& functor);
    TGadgetFunctor* GetBuilder();

    virtual bool  Create(TGadgetWindow& destWindow);
    virtual bool  Merge(const TBarDescr& sourceBarDescr, TGadgetWindow& destWindow);
    virtual bool  Restore(TGadgetWindow& destWindow);

    // please use: SetBuilder(TGadgetFunctor& functor);
    // properties
#if 0  // deprecated
    class TGadgetBuilder{
      private:
        TBarDescr* GetParent();
      public:
        TGadgetBuilder& operator=(const TGadgetFunctor& funct)
        {
          GetParent()->SetBuilder(funct);
          return *this;
        }
    }GadgetBuilder;
#endif

  protected:
    TBarDescr(const TBarDescr& node);
    bool    ExtractGroups();

  protected_data:
    int                   GroupCount[NumGroups];  ///< An array of values indicating the number of pop-up menus in each group on the
                                                  ///< menu bar.
    TToolbarRes*          BarRes;				///< Points to the TToolbarRes object that owns this TBarDescr.
    TCelArray*            CelArray;			///< Points to the TCelArray object that owns this TBarDescr.
    TResId                Id;           ///< The resource ID for the bar. The resource ID is passed in the constructors to
                                        ///< identify the tool bar resource.
    TModule*              Module;       ///< Points to the TModule object that owns this TBarDescr.
    TGadgetFunctor*        GadgetFunctor;

  private:
    TBarDescrGdArray* Gadgets; // internal usage

  friend _OWLCFUNC(ipstream&) operator >>(ipstream& is, TBarDescr& m);
  friend _OWLCFUNC(opstream&) operator <<(opstream& os, const TBarDescr& m);
}
