extern void FVTrans(FontViewBase *fv,SplineChar *sc,real transform[6],uint8 *sel,
	enum fvtrans_flags);
extern void FVTransFunc(void *_fv,real transform[6],int otype, BVTFunc *bvts,
	enum fvtrans_flags );
extern void FVReencode(FontViewBase *fv,Encoding *enc);
extern void FVOverlap(FontViewBase *fv,enum overlap_type ot);
extern void FVAddExtrema(FontViewBase *fv, int force_adding);
extern void FVCorrectDir(FontViewBase *fv);
extern void FVRound2Int(FontViewBase *fv,real factor);
extern void FVCanonicalStart(FontViewBase *fv);
extern void FVCanonicalContours(FontViewBase *fv);
extern void FVCluster(FontViewBase *fv);
extern void CIDSetEncMap(FontViewBase *fv, SplineFont *new );
extern void FVInsertInCID(FontViewBase *fv,SplineFont *sf);

extern void FVAutoHint(FontViewBase *fv);
extern void FVAutoHintSubs(FontViewBase *fv);
extern void FVAutoCounter(FontViewBase *fv);
extern void FVDontAutoHint(FontViewBase *fv);
extern void FVAutoInstr(FontViewBase *fv);
extern void FVClearInstrs(FontViewBase *fv);
extern void FVClearHints(FontViewBase *fv);
extern void SCAutoTrace(SplineChar *sc,int layer, int ask);
extern const char *FindAutoTraceName(void);
extern void *GetAutoTraceArgs(void);
extern void SetAutoTraceArgs(void *a);
extern const char *FindMFName(void);
extern char *ProgramExists(const char *prog,char *buffer);
extern void MfArgsInit(void);
extern void FVAutoTrace(FontViewBase *fv,int ask);
extern void FVAddEncodingSlot(FontViewBase *fv,int gid);
extern int FVImportMult(FontViewBase *fv, char *filename,int toback,int bf);
extern int FVImportBDF(FontViewBase *fv, char *filename,int ispk, int toback);
extern void MergeFont(FontViewBase *fv,SplineFont *other,int preserveCrossFontKerning);
extern int FVImportImages(FontViewBase *fv,char *path,int isimage,int toback,int flags);
extern int FVImportImageTemplate(FontViewBase *fv,char *path,int isimage,int toback,int flags);
extern void ScriptPrint(FontViewBase *fv,int type,int32 *pointsizes,char *samplefile,
	unichar_t *sample, char *outputfile);
extern int FVBParseSelectByPST(FontViewBase *fv,struct lookup_subtable *sub,
	int search_type);
extern int SFScaleToEm(SplineFont *sf, int ascent, int descent);
extern void TransHints(StemInfo *stem,real mul1, real off1, real mul2, real off2, int round_to_int );
extern void TransDStemHints(DStemInfo *ds,real xmul, real xoff, real ymul, real yoff, int round_to_int );
extern void VrTrans(struct vr *vr,real transform[6]);
extern int SFNLTrans(FontViewBase *fv,char *x_expr,char *y_expr);
extern int SSNLTrans(SplineSet *ss,char *x_expr,char *y_expr);
extern int SCNLTrans(SplineChar *sc, int layer,char *x_expr,char *y_expr);
extern void FVPointOfView(FontViewBase *fv,struct pov_data *);
extern void FVStrokeItScript(void *fv, StrokeInfo *si,int pointless);
extern void FVOutline(struct fontviewbase *fv, real width);
extern void FVInline(struct fontviewbase *fv, real width, real inset);
extern void FVShadow(struct fontviewbase *fv,real angle, real outline_width,
	real shadow_length,int wireframe);
extern void CI_Init(struct counterinfo *ci,SplineFont *sf);
extern void FVEmbolden(struct fontviewbase *fv,enum embolden_type type,struct lcg_zones *zones);
extern void FVCondenseExtend(struct fontviewbase *fv,struct counterinfo *ci);
extern void ScriptSCCondenseExtend(SplineChar *sc,struct counterinfo *ci);

struct smallcaps {
    double lc_stem_width, uc_stem_width;
    double stem_factor, v_stem_factor;
    double xheight, scheight, capheight;
    double vscale, hscale;
    char *extension_for_letters, *extension_for_symbols;
    int dosymbols;
    SplineFont *sf;
    int layer;
    double italic_angle, tan_ia;
};

extern void SmallCapsFindConstants(struct smallcaps *small, SplineFont *sf,
	int layer );

enum glyphchange_type { gc_generic, gc_smallcaps, gc_subsuper, gc_max };

struct position_maps {
    double current  , desired;
    double cur_width, des_width;
    int overlap_index;
};

struct fixed_maps {
    int cnt;
    struct position_maps *maps;
};

struct genericchange {
    enum glyphchange_type gc;
    uint32 feature_tag;
    char *glyph_extension;
    char *extension_for_letters, *extension_for_symbols;
    double stem_height_scale, stem_width_scale;
    double stem_height_add  , stem_width_add  ;
    double stem_threshold;
    double serif_height_scale, serif_width_scale;
    double serif_height_add  , serif_width_add  ;
    double hcounter_scale, hcounter_add;
    double lsb_scale, lsb_add;
    double rsb_scale, rsb_add;
    uint8 center_in_hor_advance;
    uint8 use_vert_mapping;
    uint8 do_smallcap_symbols;
    uint8 petite;				/* generate petite caps rather than smallcaps */
    double vcounter_scale, vcounter_add;	/* If not using mapping */
    double v_scale;				/* If using mapping */
    struct fixed_maps m;
    struct fixed_maps g;			/* Adjusted for each glyph */
    double vertical_offset;
    unsigned int dstem_control, serif_control;
    struct smallcaps *small;
/* Filled in by called routine */
    SplineFont *sf;
    int layer;
    double italic_angle, tan_ia;
};

extern void FVAddSmallCaps(FontViewBase *fv,struct genericchange *genchange);
extern void FVGenericChange(FontViewBase *fv,struct genericchange *genchange);
extern void CVGenericChange(CharViewBase *cv,struct genericchange *genchange);

struct xheightinfo {
    double xheight_current, xheight_desired;
    double serif_height;
};

extern void InitXHeightInfo(SplineFont *sf, int layer, struct xheightinfo *xi);
extern void ChangeXHeight(FontViewBase *fv,CharViewBase *cv, struct xheightinfo *xi);
extern SplineSet *SSControlStems(SplineSet *ss,
	double stemwidthscale, double stemheightscale,
	double hscale, double vscale, double xheight);
extern void MakeItalic(FontViewBase *fv,CharViewBase *cv,ItalicInfo *ii);
extern int FVReplaceAll( FontViewBase *fv, SplineSet *find, SplineSet *rpl, double fudge, int flags );
extern void FVBReplaceOutlineWithReference( FontViewBase *fv, double fudge );
extern void FVCorrectReferences(FontViewBase *fv);
extern void _FVSimplify(FontViewBase *fv,struct simplifyinfo *smpl);
extern void UnlinkThisReference(FontViewBase *fv,SplineChar *sc,int layer);
extern FontViewBase *ViewPostScriptFont(const char *filename,int openflags);
extern void FVBuildAccent(FontViewBase *fv,int onlyaccents);
extern void FVRemoveKerns(FontViewBase *fv);
extern void FVRemoveVKerns(FontViewBase *fv);
extern void FVVKernFromHKern(FontViewBase *fv);
extern void FVAddUnencoded(FontViewBase *fv, int cnt);
extern void FVRemoveUnused(FontViewBase *fv);
extern void FVCompact(FontViewBase *fv);
extern void FVDetachGlyphs(FontViewBase *fv);
extern void FVDetachAndRemoveGlyphs(FontViewBase *fv);
extern int AutoWidthScript(FontViewBase *fv,int spacing);
extern int AutoKernScript(FontViewBase *fv,int spacing, int threshold,
	struct lookup_subtable *sub, char *kernfile);

#ifndef _NO_FFSCRIPT
extern void DictionaryFree(struct dictionary *dica);
#endif

extern void BCTrans(BDFFont *bdf,BDFChar *bc,BVTFunc *bvts,FontViewBase *fv );
extern void BCSetPoint(BDFChar *bc, int x, int y, int color);
extern void BCTransFunc(BDFChar *bc,enum bvtools type,int xoff,int yoff);
extern void skewselect(BVTFunc *bvtf,real t);

extern BDFFloat *BDFFloatCreate(BDFChar *bc,int xmin,int xmax,int ymin,int ymax, int clear);
extern BDFFloat *BDFFloatCopy(BDFFloat *sel);
extern BDFFloat *BDFFloatConvert(BDFFloat *sel,int newdepth, int olddepth);
extern void BDFFloatFree(BDFFloat *sel);

extern void BCMergeReferences(BDFChar *base,BDFChar *cur,int8 xoff,int8 yoff);
extern BDFChar *BDFGetMergedChar(BDFChar *bc) ;
extern void BCUnlinkThisReference(struct fontviewbase *fv,BDFChar *bc);

extern int CVLayer(CharViewBase *cv);
extern Undoes *CVPreserveStateHints(CharViewBase *cv);
extern Undoes *CVPreserveState(CharViewBase *cv);
extern Undoes *_CVPreserveTState(CharViewBase *cv,PressedOn *);
extern Undoes *CVPreserveWidth(CharViewBase *cv,int width);
extern Undoes *CVPreserveVWidth(CharViewBase *cv,int vwidth);
extern void CVDoRedo(CharViewBase *cv);
extern void CVDoUndo(CharViewBase *cv);
extern void _CVRestoreTOriginalState(CharViewBase *cv,PressedOn *p);
extern void _CVUndoCleanup(CharViewBase *cv,PressedOn *p);
extern void CVRemoveTopUndo(CharViewBase *cv);
extern void CopySelected(CharViewBase *cv,int doanchors);
extern void CVCopyGridFit(CharViewBase *cv);
extern void CopyWidth(CharViewBase *cv,enum undotype);
extern void PasteToCV(CharViewBase *cv);
extern void CVYPerspective(CharViewBase *cv,bigreal x_vanish, bigreal y_vanish);
extern void ScriptSCEmbolden(SplineChar *sc,int layer,enum embolden_type type,struct lcg_zones *zones);
extern void CVEmbolden(CharViewBase *cv,enum embolden_type type,struct lcg_zones *zones);
extern void SCCondenseExtend(struct counterinfo *ci,SplineChar *sc, int layer,
	int do_undoes);
extern void SCClearSelPt(SplineChar *sc);
extern void SC_MoreLayers(SplineChar *,Layer *old);
extern void SCLayersChange(SplineChar *sc);
extern void SFLayerChange(SplineFont *sf);
extern void SCTile(SplineChar *sc,int layer);
extern void _CVMenuMakeLine(CharViewBase *cv,int do_arc,int ellipse_to_back);
    /* Ellipse to back is a debugging flag and adds the generated ellipse to */
    /*  the background layer so we can look at it. I thought it might actually*/
    /*  be useful, so I left it in. Activated with the Alt key in the menu */

extern void MVCopyChar(FontViewBase *fv, BDFFont *bdf, SplineChar *sc, enum fvcopy_type fullcopy);
extern void PasteIntoMV(FontViewBase *fv, BDFFont *bdf,SplineChar *sc, int doclear);

extern void ExecuteScriptFile(FontViewBase *fv, SplineChar *sc, char *filename);

enum search_flags { sv_reverse = 0x1, sv_flips = 0x2, sv_rotate = 0x4,
	sv_scale = 0x8, sv_endpoints=0x10 };

enum flipset { flip_none = 0, flip_x, flip_y, flip_xy };

typedef struct searchdata {
    SplineChar sc_srch, sc_rpl;
    SplineSet *path, *revpath, *replacepath, *revreplace;
    int pointcnt, rpointcnt;
    real fudge;
    real fudge_percent;			/* a value of .05 here represents 5% (we don't store the integer) */
    unsigned int tryreverse: 1;
    unsigned int tryflips: 1;
    unsigned int tryrotate: 1;
    unsigned int tryscale: 1;
    unsigned int endpoints: 1;		/* Don't match endpoints, use them for direction only */
    unsigned int onlyselected: 1;
    unsigned int subpatternsearch: 1;
    unsigned int doreplace: 1;
    unsigned int replaceall: 1;
    unsigned int findall: 1;
    unsigned int searchback: 1;
    unsigned int wrap: 1;
    unsigned int wasreversed: 1;
    unsigned int replacewithref: 1;
    unsigned int already_complained: 1;	/* User has already been alerted to the fact that we've converted splines to refs and lost the instructions */
    SplineSet *matched_spl;
    SplinePoint *matched_sp, *last_sp;
    real matched_rot, matched_scale;
    real matched_x, matched_y;
    double matched_co, matched_si;		/* Precomputed sin, cos */
    enum flipset matched_flip;
    unsigned long long matched_refs;	/* Bit map of which refs in the char were matched */
    unsigned long long matched_ss;	/* Bit map of which splines in the char were matched */
				    /* In multi-path mode */
    unsigned long long matched_ss_start;/* Bit map of which splines we tried to start matches with */
    FontViewBase *fv;
    SplineChar *curchar;
    int last_gid;
} SearchData;

extern struct searchdata *SDFromContour( FontViewBase *fv, SplineSet *find, double fudge, int flags );
extern SplineChar *SDFindNext(struct searchdata *sv);

extern struct python_import_export {
    struct _object *import;	/* None becomes NULL */
    struct _object *export;	/* None becomes NULL */
    struct _object *data;	/* None stays None */
    char *name;
    char *extension;
    char *all_extensions;
} *py_ie;
extern void PyFF_SCExport(SplineChar *sc,int ie_index,char *filename,
	int layer);
extern void PyFF_SCImport(SplineChar *sc,int ie_index,char *filename,
	int layer, int clear);
extern void PyFF_InitFontHook(FontViewBase *fv);

extern void LookupInit(void);
extern int UserFeaturesDiffer(void);
extern uint32 *StdFeaturesOfScript(uint32 script);

enum byte_types { bt_instr, bt_cnt, bt_byte, bt_wordhi, bt_wordlo, bt_impliedreturn };
struct instrdata {
    uint8 *instrs;
    int instr_cnt, max;
    uint8 *bts;
    unsigned int changed: 1;
    unsigned int in_composit: 1;
    SplineFont *sf;
    SplineChar *sc;
    uint32 tag;
    struct instrdlg *id;
    struct instrdata *next;
};

extern uint8 *_IVParse(SplineFont *sf, char *text, int *len,
	void (*IVError)(void *,char *, int), void *iv);
extern char *_IVUnParseInstrs(uint8 *instrs,int instr_cnt);

extern int BitmapControl(FontViewBase *fv,int32 *sizes,int isavail,int rasterize);
extern void FVSetWidthScript(FontViewBase *fv,enum widthtype wtype,int val,int incr);
extern void FVMetricsCenter(FontViewBase *fv,int docenter);
extern void FVRevert(FontViewBase *fv);
extern void FVRevertBackup(FontViewBase *fv);
extern void FVRevertGlyph(FontViewBase *fv);
extern void FVClearSpecialData(FontViewBase *fv);
extern int   MMReblend(FontViewBase *fv, MMSet *mm);
extern FontViewBase *MMCreateBlendedFont(MMSet *mm,FontViewBase *fv,real blends[MmMax],int tonew );
extern void FVB_MakeNamelist(FontViewBase *fv, FILE *file);

/**
 * Code which wants the fontview to redraw it's title can call here to
 * have that happen.
 */
extern void FVTitleUpdate(FontViewBase *fv);

extern void AutoWidth2(FontViewBase *fv,int separation,int min_side,int max_side,
	int chunk_height, int loop_cnt);
extern void GuessOpticalOffset(SplineChar *sc,int layer,real *_loff, real *_roff,
	int chunk_height );
extern void AutoKern2(SplineFont *sf, int layer,SplineChar **left,SplineChar **right,
	struct lookup_subtable *into,
	int separation, int min_kern, int from_closest_approach, int only_closer,
	int chunk_height,
	void (*addkp)(void *data,SplineChar *left,SplineChar *r,int off),
	void *data);
extern void AutoKern2NewClass(SplineFont *sf,int layer,char **leftnames, char **rightnames,
	int lcnt, int rcnt,
	void (*kcAddOffset)(void *data,int left_index, int right_index,int offset), void *data,
	int separation, int min_kern, int from_closest_approach, int only_closer,
	int chunk_height);
extern void AutoKern2BuildClasses(SplineFont *sf,int layer,
	SplineChar **leftglyphs,SplineChar **rightglyphs,
	struct lookup_subtable *sub,
	int separation, int min_kern, int touching, int only_closer,
	int autokern,
	real good_enough);

extern void MVSelectFirstKerningTable(struct metricsview *mv);

extern float joinsnap;
