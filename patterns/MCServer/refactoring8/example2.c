class cChunkDesc
{
public:
	// tolua_end

	/** The datatype used to represent the entire chunk worth of shape.
	0 = air
	1 = solid
	Indexed as [y + 256 * x + 256 * 16 * z]. */
	typedef Byte Shape[256 * 16 * 16];
	
	/** Uncompressed block metas, 1 meta per byte */
	typedef NIBBLETYPE BlockNibbleBytes[cChunkDef::NumBlocks];
	

	cChunkDesc(int a_ChunkX, int a_ChunkZ);
	~cChunkDesc();

	void SetChunkCoords(int a_ChunkX, int a_ChunkZ);
	
	// tolua_begin

	int GetChunkX(void) const { return m_ChunkX; }
	int GetChunkZ(void) const { return m_ChunkZ; }
	
	void       FillBlocks(BLOCKTYPE a_BlockType, NIBBLETYPE a_BlockMeta);
	void       SetBlockTypeMeta(int a_RelX, int a_RelY, int a_RelZ, BLOCKTYPE a_BlockType, NIBBLETYPE a_BlockMeta);
	void       GetBlockTypeMeta(int a_RelX, int a_RelY, int a_RelZ, BLOCKTYPE & a_BlockType, NIBBLETYPE & a_BlockMeta);

	void       SetBlockType(int a_RelX, int a_RelY, int a_RelZ, BLOCKTYPE a_BlockType);
	BLOCKTYPE  GetBlockType(int a_RelX, int a_RelY, int a_RelZ);
	
	void       SetBlockMeta(int a_RelX, int a_RelY, int a_RelZ, NIBBLETYPE a_BlockMeta);
	NIBBLETYPE GetBlockMeta(int a_RelX, int a_RelY, int a_RelZ);

	void       SetBiome(int a_RelX, int a_RelZ, EMCSBiome a_BiomeID);
	EMCSBiome  GetBiome(int a_RelX, int a_RelZ);

	// These operate on the heightmap, so they could get out of sync with the data
	// Use UpdateHeightmap() to re-calculate heightmap from the block data
	void       SetHeight(int a_RelX, int a_RelZ, HEIGHTTYPE a_Height);
	HEIGHTTYPE GetHeight(int a_RelX, int a_RelZ);

	// tolua_end

	/** Sets the heightmap to match the given shape data.
	Note that this ignores overhangs; the method is mostly used by old composition generators. */
	void SetHeightFromShape(const Shape & a_Shape);

	/** Sets the shape in a_Shape to match the heightmap stored currently in m_HeightMap. */
	void GetShapeFromHeight(Shape & a_Shape) const;

	// tolua_begin

	// Default generation:
	void SetUseDefaultBiomes(bool a_bUseDefaultBiomes);
	bool IsUsingDefaultBiomes(void) const;
	void SetUseDefaultHeight(bool a_bUseDefaultHeight);
	bool IsUsingDefaultHeight(void) const;
	void SetUseDefaultComposition(bool a_bUseDefaultComposition);
	bool IsUsingDefaultComposition(void) const;
	void SetUseDefaultFinish(bool a_bUseDefaultFinish);
	bool IsUsingDefaultFinish(void) const;

	/** Writes the block area into the chunk, with its origin set at the specified relative coords. Area's data overwrite everything in the chunk. */
	void WriteBlockArea(const cBlockArea & a_BlockArea, int a_RelX, int a_RelY, int a_RelZ, cBlockArea::eMergeStrategy a_MergeStrategy = cBlockArea::msOverwrite);

	/** Reads an area from the chunk into a cBlockArea, blocktypes and blockmetas */
	void ReadBlockArea(cBlockArea & a_Dest, int a_MinRelX, int a_MaxRelX, int a_MinRelY, int a_MaxRelY, int a_MinRelZ, int a_MaxRelZ);

	/** Returns the maximum height value in the heightmap. */
	HEIGHTTYPE GetMaxHeight(void) const;

	/** Returns the minimum height value in the heightmap. */
	HEIGHTTYPE GetMinHeight(void) const;
	
	/** Fills the relative cuboid with specified block; allows cuboid out of range of this chunk */
	void FillRelCuboid(
		int a_MinX, int a_MaxX,
		int a_MinY, int a_MaxY,
		int a_MinZ, int a_MaxZ,
		BLOCKTYPE a_BlockType, NIBBLETYPE a_BlockMeta
	);
	
	/** Fills the relative cuboid with specified block; allows cuboid out of range of this chunk */
	void FillRelCuboid(const cCuboid & a_RelCuboid, BLOCKTYPE a_BlockType, NIBBLETYPE a_BlockMeta)
	{
		FillRelCuboid(
			a_RelCuboid.p1.x, a_RelCuboid.p2.x,
			a_RelCuboid.p1.y, a_RelCuboid.p2.y,
			a_RelCuboid.p1.z, a_RelCuboid.p2.z,
			a_BlockType, a_BlockMeta
		);
	}
	
	/** Replaces the specified src blocks in the cuboid by the dst blocks; allows cuboid out of range of this chunk */
	void ReplaceRelCuboid(
		int a_MinX, int a_MaxX,
		int a_MinY, int a_MaxY,
		int a_MinZ, int a_MaxZ,
		BLOCKTYPE a_SrcType, NIBBLETYPE a_SrcMeta,
		BLOCKTYPE a_DstType, NIBBLETYPE a_DstMeta
	);
	
	/** Replaces the specified src blocks in the cuboid by the dst blocks; allows cuboid out of range of this chunk */
	void ReplaceRelCuboid(
		const cCuboid & a_RelCuboid,
		BLOCKTYPE a_SrcType, NIBBLETYPE a_SrcMeta,
		BLOCKTYPE a_DstType, NIBBLETYPE a_DstMeta
	)
	{
		ReplaceRelCuboid(
			a_RelCuboid.p1.x, a_RelCuboid.p2.x,
			a_RelCuboid.p1.y, a_RelCuboid.p2.y,
			a_RelCuboid.p1.z, a_RelCuboid.p2.z,
			a_SrcType, a_SrcMeta,
			a_DstType, a_DstMeta
		);
	}

	/** Replaces the blocks in the cuboid by the dst blocks if they are considered non-floor (air, water); allows cuboid out of range of this chunk */
	void FloorRelCuboid(
		int a_MinX, int a_MaxX,
		int a_MinY, int a_MaxY,
		int a_MinZ, int a_MaxZ,
		BLOCKTYPE a_DstType, NIBBLETYPE a_DstMeta
	);
	
	/** Replaces the blocks in the cuboid by the dst blocks if they are considered non-floor (air, water); allows cuboid out of range of this chunk */
	void FloorRelCuboid(
		const cCuboid & a_RelCuboid,
		BLOCKTYPE a_DstType, NIBBLETYPE a_DstMeta
	)
	{
		FloorRelCuboid(
			a_RelCuboid.p1.x, a_RelCuboid.p2.x,
			a_RelCuboid.p1.y, a_RelCuboid.p2.y,
			a_RelCuboid.p1.z, a_RelCuboid.p2.z,
			a_DstType, a_DstMeta
		);
	}
	
	/** Fills the relative cuboid with specified block with a random chance; allows cuboid out of range of this chunk */
	void RandomFillRelCuboid(
		int a_MinX, int a_MaxX,
		int a_MinY, int a_MaxY,
		int a_MinZ, int a_MaxZ,
		BLOCKTYPE a_BlockType, NIBBLETYPE a_BlockMeta,
		int a_RandomSeed, int a_ChanceOutOf10k
	);
	
	/** Fills the relative cuboid with specified block with a random chance; allows cuboid out of range of this chunk */
	void RandomFillRelCuboid(
		const cCuboid & a_RelCuboid, BLOCKTYPE a_BlockType, NIBBLETYPE a_BlockMeta,
		int a_RandomSeed, int a_ChanceOutOf10k
	)
	{
		RandomFillRelCuboid(
			a_RelCuboid.p1.x, a_RelCuboid.p2.x,
			a_RelCuboid.p1.y, a_RelCuboid.p2.y,
			a_RelCuboid.p1.z, a_RelCuboid.p2.z,
			a_BlockType, a_BlockMeta,
			a_RandomSeed, a_ChanceOutOf10k
		);
	}
	
	/** Returns the block entity at the specified coords.
	If there is no block entity at those coords, tries to create one, based on the block type
	If the blocktype doesn't support a block entity, returns nullptr. */
	cBlockEntity * GetBlockEntity(int a_RelX, int a_RelY, int a_RelZ);
	
	/** Updates the heightmap to match the current contents.
	Useful for plugins when writing custom block areas into the chunk */
	void UpdateHeightmap(void);
	
	// tolua_end
	
	// Accessors used by cChunkGenerator::Generator descendants:
	inline cChunkDef::BiomeMap &     GetBiomeMap              (void) { return m_BiomeMap; }
	inline cChunkDef::BlockTypes &   GetBlockTypes            (void) { return *(reinterpret_cast<cChunkDef::BlockTypes *>(m_BlockArea.GetBlockTypes())); }
	// CANNOT, different compression!
	// inline cChunkDef::BlockNibbles & GetBlockMetas            (void) { return *((cChunkDef::BlockNibbles *)m_BlockArea.GetBlockMetas()); }
	inline BlockNibbleBytes &        GetBlockMetasUncompressed(void) { return *(reinterpret_cast<BlockNibbleBytes *>(m_BlockArea.GetBlockMetas())); }
	inline cChunkDef::HeightMap &    GetHeightMap             (void) { return m_HeightMap; }
	inline cEntityList &             GetEntities              (void) { return m_Entities; }
	inline cBlockEntityList &        GetBlockEntities         (void) { return m_BlockEntities; }
	
	/** Compresses the metas from the BlockArea format (1 meta per byte) into regular format (2 metas per byte) */
	void CompressBlockMetas(cChunkDef::BlockNibbles & a_DestMetas);
	
	#ifdef _DEBUG
	/** Verifies that the heightmap corresponds to blocktype contents; if not, asserts on that column */
	void VerifyHeightmap(void);
	#endif  // _DEBUG
	
private:
	int m_ChunkX;
	int m_ChunkZ;
	
	cChunkDef::BiomeMap     m_BiomeMap;
	cBlockArea              m_BlockArea;
	cChunkDef::HeightMap    m_HeightMap;
	cEntityList             m_Entities;       // Individual entities are NOT owned by this object!
	cBlockEntityList        m_BlockEntities;  // Individual block entities are NOT owned by this object!

	bool m_bUseDefaultBiomes;
	bool m_bUseDefaultHeight;
	bool m_bUseDefaultComposition;
	bool m_bUseDefaultFinish;
}
