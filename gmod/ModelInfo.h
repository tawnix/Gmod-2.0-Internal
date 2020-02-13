#pragma once
#include <Windows.h>
#include "Vector.h"
#include "Matrix.h"
#include "QAngle.h"

struct mstudiobbox_t
{
	int					bone;
	int					group;				// intersection group
	Vector				bbmin;				// bounding box
	Vector				bbmax;
	int					szhitboxnameindex;	// offset to the name of the hitbox.
	int					unused[8];

	const char* pszHitboxName()
	{
		if (szhitboxnameindex == 0)
			return "";

		return ((char*)this) + szhitboxnameindex;
	}

	mstudiobbox_t() {}

private:
	mstudiobbox_t(const mstudiobbox_t& vOther);
};

class RadianEuler
{
public:
	inline RadianEuler(void)
	{ }

	inline RadianEuler(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	//inline RadianEuler(Quaternion const& q); // evil auto type promotion!!!
	//inline RadianEuler(QAngle const& angles); // evil auto type promotion!!!
											  // Initialization
	inline void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
	{
		x = ix;
		y = iy;
		z = iz;
	}

	//	conversion to qangle
	QAngle ToQAngle(void) const;
	bool IsValid() const;
	void Invalidate();

	inline float* Base()
	{
		return &x;
	}

	inline const float* Base() const
	{
		return &x;
	}

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	float x, y, z;
};

class Quaternion // same data-layout as engine's vec4_t,
{ //		which is a float[4]
public:
	inline Quaternion(void)
	{}

	inline Quaternion(float ix, float iy, float iz, float iw)
		: x(ix),
		y(iy),
		z(iz),
		w(iw)
	{ }

	inline Quaternion(RadianEuler const& angle); // evil auto type promotion!!!

	inline void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f, float iw = 0.0f)
	{
		x = ix;
		y = iy;
		z = iz;
		w = iw;
	}

	bool IsValid() const;
	void Invalidate();

	bool operator==(const Quaternion& src) const;
	bool operator!=(const Quaternion& src) const;

	float* Base()
	{
		return (float*)this;
	}

	const float* Base() const
	{
		return (float*)this;
	}

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	float x, y, z, w;
};

struct mstudiobone_t
{
	int					sznameindex;
	inline char* const pszName(void) const { return ((char*)this) + sznameindex; }
	int		 			parent;		// parent bone
	int					bonecontroller[6];	// bone controller index, -1 == none

											// default values
	Vector				pos;
	Quaternion			quat;
	Vector			rot;
	// compression scale
	Vector				posscale;
	Vector				rotscale;

	matrix3x4_t			poseToBone;
	Quaternion			qAlignment;
	int					flags;
	int					proctype;
	int					procindex;		// procedural rule
	mutable int			physicsbone;	// index into physically simulated bone
	inline void* pProcedure() const { if (procindex == 0) return NULL; else return  (void*)(((byte*)this) + procindex); };
	int					surfacepropidx;	// index into string tablefor property name
	inline char* const pszSurfaceProp(void) const { return ((char*)this) + surfacepropidx; }
	int					contents;		// See BSPFlags.h for the contents flags

	int					unused[8];		// remove as appropriate

	mstudiobone_t() {}
private:
	// No copy constructors allowed
	mstudiobone_t(const mstudiobone_t& vOther);
};

struct mstudiohitboxset_t
{
	int					sznameindex;
	inline char* const	pszName(void) const { return ((char*)this) + sznameindex; }
	int					numhitboxes;
	int					hitboxindex;
	inline mstudiobbox_t* pHitbox(int i) const { return (mstudiobbox_t*)(((byte*)this) + hitboxindex) + i; };
};

struct studiohdr_t
{
	int					id;
	int					version;
	long				checksum;		// this has to be the same in the phy and vtx files to load!
	inline const char* pszName(void) const { return name; }
	char				name[64];
	int					length;

	Vector				eyeposition;	// ideal eye position
	Vector				illumposition;	// illumination center
	Vector				hull_min;		// ideal movement hull size
	Vector				hull_max;
	Vector				view_bbmin;		// clipping bounding box
	Vector				view_bbmax;

	int					flags;
	int					numbones;			// bones
	int					boneindex;
	inline mstudiobone_t* pBone(int i) const { return (mstudiobone_t*)(((byte*)this) + boneindex) + i; };
	int					RemapSeqBone(int iSequence, int iLocalBone) const;	// maps local sequence bone to global bone
	int					RemapAnimBone(int iAnim, int iLocalBone) const;		// maps local animations bone to global bone

	int					numbonecontrollers;		// bone controllers
	int					bonecontrollerindex;
	inline void* pBonecontroller(int i) const { return  (((byte*)this) + bonecontrollerindex) + i; };

	int					numhitboxsets;
	int					hitboxsetindex;

	// Look up hitbox set by index
	mstudiohitboxset_t* pHitboxSet(int i) const
	{
		return (mstudiohitboxset_t*)(((byte*)this) + hitboxsetindex) + i;
	};

	// Calls through to hitbox to determine size of specified set
	inline mstudiobbox_t* pHitbox(int i, int set) const
	{
		mstudiohitboxset_t const* s = pHitboxSet(set);
		if (!s)
			return NULL;

		return s->pHitbox(i);
	};

	// Calls through to set to get hitbox count for set
	inline int			iHitboxCount(int set) const
	{
		mstudiohitboxset_t const* s = pHitboxSet(set);
		if (!s)
			return 0;

		return s->numhitboxes;
	};


	studiohdr_t() {}

private:
	// No copy constructors allowed
	studiohdr_t(const studiohdr_t& vOther);

	friend struct virtualmodel_t;
};
struct model_t;
struct virtualmodel_t;
struct vcollide_t;
struct cplane_t;
class CUtlBuffer;
class CPhysCollide;


class IVModelInfo
{
public:
	virtual							~IVModelInfo(void) { }
	virtual const model_t* GetModel(int modelindex) = 0;
	virtual int						GetModelIndex(const char* name) const = 0;
	virtual const char* GetModelName(const model_t* model) const = 0;
	virtual vcollide_t* GetVCollide(const model_t* model) = 0;
	virtual vcollide_t* GetVCollide(int modelindex) = 0;
	virtual void					GetModelBounds(const model_t* model, Vector& mins, Vector& maxs) const = 0;
	virtual	void					GetModelRenderBounds(const model_t* model, Vector& mins, Vector& maxs) const = 0;
	virtual int						GetModelFrameCount(const model_t* model) const = 0;
	virtual int						GetModelType(const model_t* model) const = 0;
	virtual void* GetModelExtraData(const model_t* model) = 0;
	virtual bool					ModelHasMaterialProxy(const model_t* model) const = 0;
	virtual bool					IsTranslucent(model_t const* model) const = 0;
	virtual bool					IsTranslucentTwoPass(const model_t* model) const = 0;
	virtual void					RecomputeTranslucency(const model_t* model, int nSkin, int nBody, void /*IClientRenderable*/* pClientRenderable, float fInstanceAlphaModulate = 1.0f) = 0;
	virtual int						GetModelMaterialCount(const model_t* model) const = 0;
	virtual void					GetModelMaterials(const model_t* model, int count, void** ppMaterial) = 0;
	virtual bool					IsModelVertexLit(const model_t* model) const = 0;
	virtual const char* GetModelKeyValueText(const model_t* model) = 0;
	virtual bool					GetModelKeyValue(const model_t* model, CUtlBuffer& buf) = 0;
	virtual float					GetModelRadius(const model_t* model) = 0;
	virtual const studiohdr_t* FindModel(const studiohdr_t* pStudioHdr, void** cache, const char* modelname) const = 0;
	virtual const studiohdr_t* FindModel(void* cache) const = 0;
	virtual	virtualmodel_t* GetVirtualModel(const studiohdr_t* pStudioHdr) const = 0;
	virtual byte* GetAnimBlock(const studiohdr_t* pStudioHdr, int iBlock) const = 0;
	virtual void					GetModelMaterialColorAndLighting(const model_t* model, Vector const& origin,
		QAngle const& angles, void* pTrace,
		Vector& lighting, Vector& matColor) = 0;
	virtual void					GetIlluminationPoint(const model_t* model, void* pRenderable, Vector const& origin,
		QAngle const& angles, Vector* pLightingCenter) = 0;
	virtual int						GetModelContents(int modelIndex) = 0;
	virtual studiohdr_t* GetStudioModel(const model_t* mod) = 0;
	virtual int						GetModelSpriteWidth(const model_t* model) const = 0;
	virtual int						GetModelSpriteHeight(const model_t* model) const = 0;
	virtual void					SetLevelScreenFadeRange(float flMinSize, float flMaxSize) = 0;
	virtual void					GetLevelScreenFadeRange(float* pMinArea, float* pMaxArea) const = 0;
	virtual void					SetViewScreenFadeRange(float flMinSize, float flMaxSize) = 0;
	virtual unsigned char			ComputeLevelScreenFade(const Vector& vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
	virtual unsigned char			ComputeViewScreenFade(const Vector& vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
	virtual int						GetAutoplayList(const studiohdr_t* pStudioHdr, unsigned short** pAutoplayList) const = 0;
	virtual CPhysCollide* GetCollideForVirtualTerrain(int index) = 0;
	virtual bool					IsUsingFBTexture(const model_t* model, int nSkin, int nBody, void /*IClientRenderable*/* pClientRenderable) const = 0;
	virtual const model_t* FindOrLoadModel(const char* name) { return NULL; }
	virtual void					InitDynamicModels() { }
	virtual void					ShutdownDynamicModels() { }
	virtual void					AddDynamicModel(const char* name, int nModelIndex = -1) { }
	virtual void					ReferenceModel(int modelindex) { }
	virtual void					UnreferenceModel(int modelindex) { }
	virtual void					CleanupDynamicModels(bool bForce = false) { }
	virtual unsigned short			GetCacheHandle(const model_t* model) const = 0;
	virtual int						GetBrushModelPlaneCount(const model_t* model) const = 0;
	virtual void					GetBrushModelPlane(const model_t* model, int nIndex, cplane_t& plane, Vector* pOrigin) const = 0;
	virtual int						GetSurfacepropsForVirtualTerrain(int index) = 0;
	virtual void					OnLevelChange() = 0;
	virtual int						GetModelClientSideIndex(const char* name) const = 0;
	virtual int						RegisterDynamicModel(const char* name, bool bClientSide) = 0;
	virtual bool					IsDynamicModelLoading(int modelIndex) = 0;
	virtual void					AddRefDynamicModel(int modelIndex) = 0;
	virtual void					ReleaseDynamicModel(int modelIndex) = 0;
	virtual bool					RegisterModelLoadCallback(int modelindex, void* pCallback, bool bCallImmediatelyIfLoaded = true) = 0;
	virtual void					UnregisterModelLoadCallback(int modelindex, void* pCallback) = 0;
};