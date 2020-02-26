#pragma once
#include "Matrix.h"
#include "ModelInfo.h"
#include "InterfaceVT.h"
#include "Color.h"
#include <Windows.h>

class IClientNetworkable;
enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
class CBaseTrace
{
public:
	bool func1();
	bool func2();
	bool func3();
	bool func4();
	bool func5();
public:
	Vector startpos;
	Vector endpos;
	cplane_t plane;
	float fraction;
	int contents;
	unsigned short dispFlags;
	bool  allsolid;
	bool startsolid;
};

class IClientMode {

};

class CGameEventListener {

};

class IBaseInterface
{

};

class IAppSystem
{

};
class IInput {

};

struct player_info_t
{
	char Name[32];
	char PAD2[0x200];
};


struct Ray_t
{

	__declspec(align(16)) Vector m_Start;

	__declspec(align(16)) Vector m_Delta;

	__declspec(align(16)) Vector m_StartOffset;

	__declspec(align(16)) Vector m_Extents;
	//without your matrix3x4
	bool m_IsRay;
	bool m_IsSwept;

	void Init(Vector& vecStart, Vector& vecEnd)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;

		m_IsRay = true;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = vecStart;
	}
};





class CUserCmd {
public:
	int		m_cmd_nr;
	int		m_tick_count;
	Vector	m_viewangles;
	float	m_forwardmove;
	float	m_sidemove;
	float	m_upmove;
	int		m_buttons;
	int		m_impulse;
	int		m_weaponselect;
	int		m_weaponsubtype;
	int		m_random_seed;
	short	m_mousedx;
	short	m_mousedy;
	bool	m_predicted;
};


class IEngineClient
{
public:

	void GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int&, int&);
		return getvfunc<OriginalFn>(this, 5)(this, width, height);
	}
	// GetPlayerInfo index 8
	bool GetPlayerInfo(int entNum, player_info_t* pinfo)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, int, player_info_t*);
		return getvfunc<OriginalFn>(this, 8)(this, entNum, pinfo);
	}
	bool Con_IsVisible(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 11)(this);
	}
	int GetLocalPlayer(void)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 12)(this);
	}
	float GetLastTimeStamp(void)
	{
		typedef float(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 14)(this);
	}
	int GetMaxClients(void)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 20)(this);
	}
	bool IsInGame(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 26)(this);
	}
	bool IsConnected(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 27)(this);
	}
	bool IsDrawingLoadingImage(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 28)(this);
	}
	void Con_NPrintf(int idx, char const* fmt, ...)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int idx, char const* fmt);
		return getvfunc<OriginalFn>(this, 30)(this, idx, fmt);
	}
	const matrix3x4_t& WorldToScreenMatrix()
	{
		typedef const matrix3x4_t& (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 36)(this);
	}
	const char* GetLevelName(void)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 52)(this);
	}
	const char* GetLevelNameShort(void)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 53)(this);
	}
	DWORD* GetNetChannelInfo(void)
	{
		typedef DWORD* (__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 75)(this);
	}
	bool IsTakingScreenshot(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 85)(this);
	}
	void ExecuteClientCmd(const char* szCmdString)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*);
		return getvfunc<OriginalFn>(this, 107)(this, szCmdString);
	}
	void ClientCmd_Unrestricted(const char* chCommandString)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*);
		return getvfunc<OriginalFn>(this, 113)(this, chCommandString);
	}

};


class IClientThinkable
{
public:
	virtual ~IClientThinkable() {};
};

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}

	virtual void SetRefEHandle() = 0;
	virtual void GetRefEHandle() const = 0;
};

class ICollideable
{
public:
	// Gets at the entity handle associated with the collideable
	virtual IHandleEntity * GetEntityHandle() = 0;

	// These methods return the bounds of an OBB measured in "collision" space
	// which can be retreived through the CollisionToWorldTransform or
	// GetCollisionOrigin/GetCollisionAngles methods
	virtual const Vector& OBBMinsPreScaled() const = 0;
	virtual const Vector& OBBMaxsPreScaled() const = 0;
	virtual const Vector& OBBMins() const = 0;
	virtual const Vector& OBBMaxs() const = 0;

};

class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable* GetCollideable() = 0;
};


struct model_t
{
	char name[255];
};

class IPVSNotify
{
public:
	virtual void OnPVSStatusChanged(bool bInPVS) = 0;
};

class IClientRenderable
{
public:
	virtual void* GetIClientUnknown() = 0;
	virtual void* const& GetRenderOrigin(void) = 0;
	virtual void* const& GetRenderAngles(void) = 0;
	virtual bool			    ShouldDraw(void) = 0;
	virtual bool			    IsTransparent(void) = 0;
	virtual bool			    UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool			    UsesFullFrameBufferTexture() = 0;
	virtual unsigned short	    GetShadowHandle() const = 0;
	virtual unsigned short& RenderHandle() = 0;
	virtual const model_t* GetModel() const = 0;
	virtual int				    DrawModel(int flags) = 0;
	virtual int				    GetBody() = 0;
	virtual void			    ComputeFxBlend() = 0;
	virtual int				    GetFxBlend(void) = 0;
	virtual void			    GetColorModulation(float* color) = 0;
	virtual bool			    LODTest() = 0;
	virtual bool			    SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void			    SetupWeights(const void* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void			    DoAnimationEvents(void) = 0;
	virtual IPVSNotify* GetPVSNotifyInterface() = 0;
	virtual void			    GetRenderBounds(void*& mins, void*& maxs) = 0;
	virtual void			    GetRenderBoundsWorldspace(void*& mins, void*& maxs) = 0;
	virtual void			    GetShadowRenderBounds(void*& mins, void*& maxs, unsigned short shadowType) = 0;
	virtual bool			    ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool			    GetShadowCastDistance(float* pDist, unsigned short shadowType) const = 0;
	virtual bool			    GetShadowCastDirection(void** pDirection, unsigned short shadowType) const = 0;
	virtual bool			    IsShadowDirty() = 0;
	virtual void			    MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable* GetShadowParent() = 0;
	virtual IClientRenderable* FirstShadowChild() = 0;
	virtual IClientRenderable* NextShadowPeer() = 0;
	virtual unsigned short		ShadowCastType() = 0;
	virtual void				CreateModelInstance() = 0;
	virtual unsigned short		GetModelInstance() = 0;
	virtual const void* RenderableToWorldTransform() = 0;
	virtual int					LookupAttachment(const char* pAttachmentName) = 0;
	virtual	bool				GetAttachment(int number, void* origin, void* angles) = 0;
	virtual bool				GetAttachment(int number, void* matrix) = 0;
	virtual float* GetRenderClipPlane(void) = 0;
	virtual int					GetSkin() = 0;
	virtual bool				IsTwoPass(void) = 0;
	virtual void				OnThreadedDrawSetup() = 0;
	virtual bool				UsesFlexDelayedWeights() = 0;
	virtual void				RecordToolMessage() = 0;
	virtual bool				IgnoresZBuffer(void) const = 0;
};

class ClientClass
{
public:
	void* m_pCreateFn;
	void* m_pCreateEventFn;
	char* m_pNetworkName;
	void* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};

class IClientNetworkable
{
public:
	virtual void* GetIClientUnknown() = 0;
	virtual void			Release() = 0;
	virtual ClientClass* GetClientClass() = 0;// FOR NETVARS FIND YOURSELF ClientClass* stuffs
	virtual void			NotifyShouldTransmit( /* ShouldTransmitState_t state*/) = 0;
	virtual void			OnPreDataChanged( /*DataUpdateType_t updateType*/) = 0;
	virtual void			OnDataChanged( /*DataUpdateType_t updateType*/) = 0;
	virtual void			PreDataUpdate( /*DataUpdateType_t*/ int updateType) = 0;
	virtual void			PostDataUpdate( /*DataUpdateType_t updateType*/) = 0;
	virtual bool			IsDormant(void) = 0;
	virtual int				GetIndex(void) const = 0;
	virtual void			ReceiveMessage(int classID /*, bf_read &msg*/) = 0;
	virtual void* GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities(void) = 0;
	virtual void			OnDataUnchangedInPVS() = 0;
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual ~IClientEntity();

	int GetHealth() { return *(int*)(((uintptr_t)this + 0x90)); }

	Vector GetOrigin() { return *(Vector*)(((uintptr_t)this + 0x260)); }

};

class IVModelClient : public IVModelInfo
{
public:

};


class IClientEntityList
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual IClientEntity* GetClientEntity(int i); //index of entity, returns ptr to entity base
	virtual IClientEntity* GetClientEntityFromHandle(HANDLE hEnt); //eg for obtaining weapons from handles
	virtual int NumberOfEntities(bool bIncludeNonNetworkable);
	virtual int GetHighestEntityIndex(void);
	virtual void SetMaxEntities(int n);
	virtual int GetMaxEntities();
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(void* pEntity, int contentsMask) = 0;
	virtual TraceType_t GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	CTraceFilter(void* pSkip)
	{
		pSkipEnt = pSkip;
	}

	bool ShouldHitEntity(void* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkipEnt);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkipEnt;
};
class IBaseClientDLL
{
	public:
	// Called once when the client DLL is loaded
	virtual int				Init(/*CreateInterfaceFn appSystemFactory,
									CreateInterfaceFn physicsFactory,
									void * pGlobals*/) = 0;

	virtual void			PostInit() = 0;

	// Called once when the client DLL is being unloaded
	virtual void			Shutdown(void) = 0;

	// Called once the client is initialized to setup client-side replay interface pointers
	virtual bool			ReplayInit(/*CreateInterfaceFn replayFactory*/) = 0;
	virtual bool			ReplayPostInit() = 0;

	// Called at the start of each level change
	virtual void			LevelInitPreEntity(char const* pMapName) = 0;
	// Called at the start of a new level, after the entities have been received and created
	virtual void			LevelInitPostEntity() = 0;
	// Called at the end of a level
	virtual void			LevelShutdown(void) = 0;

	// Request a pointer to the list of client datatable classes
	virtual ClientClass* GetAllClasses(void) = 0;

	// Called once per level to re-initialize any hud element drawing stuff
	virtual int				HudVidInit(void) = 0;
	// Called by the engine when gathering user input
	virtual void			HudProcessInput(bool bActive) = 0;
	// Called oncer per frame to allow the hud elements to think
	virtual void			HudUpdate(bool bActive) = 0;
	// Reset the hud elements to their initial states
	virtual void			HudReset(void) = 0;
	// Display a hud text message
	virtual void			HudText(const char* message) = 0;

	// Mouse Input Interfaces
	// Activate the mouse (hides the cursor and locks it to the center of the screen)
	virtual void			IN_ActivateMouse(void) = 0;
	// Deactivates the mouse (shows the cursor and unlocks it)
	virtual void			IN_DeactivateMouse(void) = 0;
	// This is only called during extra sound updates and just accumulates mouse x, y offets and recenters the mouse.
	//  This call is used to try to prevent the mouse from appearing out of the side of a windowed version of the engine if 
	//  rendering or other processing is taking too long
	virtual void			IN_Accumulate(void) = 0;
	// Reset all key and mouse states to their initial, unpressed state
	virtual void			IN_ClearStates(void) = 0;
	// If key is found by name, returns whether it's being held down in isdown, otherwise function returns false
	virtual bool			IN_IsKeyDown(const char* name, bool& isdown) = 0;
	// Notify the client that the mouse was wheeled while in game - called prior to executing any bound commands.
	virtual void			IN_OnMouseWheeled(int nDelta) = 0;
	// Raw keyboard signal, if the client .dll returns 1, the engine processes the key as usual, otherwise,
	//  if the client .dll returns 0, the key is swallowed.
	virtual int				IN_KeyEvent(int eventcode, void* keynum, const char* pszCurrentBinding) = 0;

	// This function is called once per tick to create the player CUserCmd (used for prediction/physics simulation of the player)
	// Because the mouse can be sampled at greater than the tick interval, there is a separate input_sample_frametime, which
	//  specifies how much additional mouse / keyboard simulation to perform.
	virtual void			CreateMove(
								int sequence_number,			// sequence_number of this cmd
								float input_sample_frametime,	// Frametime for mouse input sampling
								bool active) = 0;				// True if the player is active (not paused)

	// If the game is running faster than the tick_interval framerate, then we do extra mouse sampling to avoid jittery input
	//  This code path is much like the normal move creation code, except no move is created
	virtual void			ExtraMouseSample(float frametime, bool active) = 0;

	// Encode the delta (changes) between the CUserCmd in slot from vs the one in slot to.  The game code will have
	//  matching logic to read the delta.
	virtual bool			WriteUsercmdDeltaToBuffer(void* buf, int from, int to, bool isnewcommand) = 0;
	// Demos need to be able to encode/decode CUserCmds to memory buffers, so these functions wrap that
	virtual void			EncodeUserCmdToBuffer(void* buf, int slot) = 0;
	virtual void			DecodeUserCmdFromBuffer(void* buf, int slot) = 0;

	// Set up and render one or more views (e.g., rear view window, etc.).  This called into RenderView below
	virtual void			View_Render(void* rect) = 0;

	// Allow engine to expressly render a view (e.g., during timerefresh)
	// See IVRenderView.h, PushViewFlags_t for nFlags values
	virtual void			RenderView(const void* view, int nClearFlags, int whatToDraw) = 0;

	// Apply screen fade directly from engine
	virtual void			View_Fade(void* pSF) = 0;

	// The engine has parsed a crosshair angle message, this function is called to dispatch the new crosshair angle
	virtual void			SetCrosshairAngle(const QAngle& angle) = 0;

	// Sprite (.spr) model handling code
	// Load a .spr file by name
	virtual void			InitSprite(void* pSprite, const char* loadname) = 0;
	// Shutdown a .spr file
	virtual void			ShutdownSprite(void* pSprite) = 0;
	// Returns sizeof( CEngineSprite ) so the engine can allocate appropriate memory
	virtual int				GetSpriteSize(void) const = 0;

	// Called when a player starts or stops talking.
	// entindex is -1 to represent the local client talking (before the data comes back from the server). 
	// entindex is -2 to represent the local client's voice being acked by the server.
	// entindex is GetPlayer() when the server acknowledges that the local client is talking.
	virtual void			VoiceStatus(int entindex, void* bTalking) = 0;

	// Networked string table definitions have arrived, allow client .dll to 
	//  hook string changes with a callback function ( see INetworkStringTableClient.h )
	virtual void			InstallStringTableCallback(char const* tableName) = 0;

	// Notification that we're moving into another stage during the frame.
	virtual void			FrameStageNotify(void* curStage) = 0;

	// The engine has received the specified user message, this code is used to dispatch the message handler
	virtual bool			DispatchUserMessage(int msg_type, void* msg_data) = 0;

	// Save/restore system hooks
	virtual void* SaveInit(int size) = 0;
	virtual void			SaveWriteFields(void*, const char*, void*, void*, void*, int) = 0;
	virtual void			SaveReadFields(void*, const char*, void*, void*, void*, int) = 0;
	virtual void			PreSave(void*) = 0;
	virtual void			Save(void*) = 0;
	virtual void			WriteSaveHeaders(void*) = 0;
	virtual void			ReadRestoreHeaders(void*) = 0;
	virtual void			Restore(void*, bool) = 0;
	virtual void			DispatchOnRestore() = 0;

	// Hand over the StandardRecvProxies in the client DLL's module.
	virtual void* GetStandardRecvProxies() = 0;

	// save game screenshot writing
	virtual void			WriteSaveGameScreenshot(const char* pFilename) = 0;

	// Given a list of "S(wavname) S(wavname2)" tokens, look up the localized text and emit
	//  the appropriate close caption if running with closecaption = 1
	virtual void			EmitSentenceCloseCaption(char const* tokenstream) = 0;
	// Emits a regular close caption by token name
	virtual void			EmitCloseCaption(char const* captionname, float duration) = 0;

	// Returns true if the client can start recording a demo now.  If the client returns false,
	// an error message of up to length bytes should be returned in errorMsg.
	virtual bool			CanRecordDemo(char* errorMsg, int length) const = 0;

	// Give the Client a chance to do setup/cleanup.
	virtual void			OnDemoRecordStart(char const* pDemoBaseName) = 0;
	virtual void			OnDemoRecordStop() = 0;
	virtual void			OnDemoPlaybackStart(char const* pDemoBaseName) = 0;
	virtual void			OnDemoPlaybackStop() = 0;

	// Draw the console overlay?
	virtual bool			ShouldDrawDropdownConsole() = 0;

	// Get client screen dimensions
	virtual int				GetScreenWidth() = 0;
	virtual int				GetScreenHeight() = 0;

	// Added interface

	// save game screenshot writing
	virtual void			WriteSaveGameScreenshotOfSize(const char* pFilename, int width, int height, bool bCreatePowerOf2Padded = false, bool bWriteVTF = false) = 0;

	// Gets the current view
	virtual bool			GetPlayerView(void* playerView) = 0;

	// Matchmaking
	virtual void			SetupGameProperties(void* contexts, void* properties) = 0;
	virtual void*			GetPresenceID(const char* pIDName) = 0;
	virtual const char* GetPropertyIdString(const void* id) = 0;
	virtual void			GetPropertyDisplayString(void* id, void* value, char* pOutput, int nBytes) = 0;

#ifdef WIN32
	virtual void			StartStatsReporting(HANDLE handle, bool bArbitrated) = 0;
#endif

	virtual void			InvalidateMdlCache() = 0;

	virtual void			IN_SetSampleTime(float frametime) = 0;


	// For sv_pure mode. The filesystem figures out which files the client needs to reload to be "pure" ala the server's preferences.
	virtual void			ReloadFilesInList(void* pFilesToReload) = 0;
#ifdef POSIX
	// AR: Same as above win32 defn but down here at the end of the vtable for back compat
	virtual void			StartStatsReporting(HANDLE handle, bool bArbitrated) = 0;
#endif

	// Let the client handle UI toggle - if this function returns false, the UI will toggle, otherwise it will not.
	virtual bool			HandleUiToggle() = 0;

	// Allow the console to be shown?
	virtual bool			ShouldAllowConsole() = 0;

	// Get renamed recv tables
	virtual void* GetRenamedRecvTableInfos() = 0;

	// Get the mouthinfo for the sound being played inside UI panels
	virtual void* GetClientUIMouthInfo() = 0;

	// Notify the client that a file has been received from the game server
	virtual void			FileReceived(const char* fileName, unsigned int transferID) = 0;

	virtual const char* TranslateEffectForVisionFilter(const char* pchEffectType, const char* pchEffectName) = 0;

	// Give the client a chance to modify sound settings however they want before the sound plays. This is used for
	// things like adjusting pitch of voice lines in Pyroland in TF2.
	virtual void			ClientAdjustStartSoundParams(struct StartSoundParams_t& params) = 0;

	// Returns true if the disconnect command has been handled by the client
	virtual bool DisconnectAttempt(void) = 0;

	virtual bool IsConnectedUserInfoChangeAllowed(void* pCvar) = 0;
};




class CHLClient : public IBaseClientDLL
{
public:
	CHLClient();

	virtual int						Init(void* appSystemFactory, void* physicsFactory, void* pGlobals);

	virtual void					PostInit();
	virtual void					Shutdown(void);

	virtual bool					ReplayInit(void* fnReplayFactory);
	virtual bool					ReplayPostInit();

	virtual void					LevelInitPreEntity(const char* pMapName);
	virtual void					LevelInitPostEntity();
	virtual void					LevelShutdown(void);

	virtual ClientClass* GetAllClasses(void);

	virtual int						HudVidInit(void);
	virtual void					HudProcessInput(bool bActive);
	virtual void					HudUpdate(bool bActive);
	virtual void					HudReset(void);
	virtual void					HudText(const char* message);

	// Mouse Input Interfaces
	virtual void					IN_ActivateMouse(void);
	virtual void					IN_DeactivateMouse(void);
	virtual void					IN_Accumulate(void);
	virtual void					IN_ClearStates(void);
	virtual bool					IN_IsKeyDown(const char* name, bool& isdown);
	virtual void					IN_OnMouseWheeled(int nDelta);
	// Raw signal
	virtual int						IN_KeyEvent(int eventcode, void* keynum, const char* pszCurrentBinding);
	virtual void					IN_SetSampleTime(float frametime);
	// Create movement command
	virtual void					CreateMove(int sequence_number, float input_sample_frametime, bool active);
	virtual void					ExtraMouseSample(float frametime, bool active);
	virtual bool					WriteUsercmdDeltaToBuffer(void* buf, int from, int to, bool isnewcommand);
	virtual void					EncodeUserCmdToBuffer(void* buf, int slot);
	virtual void					DecodeUserCmdFromBuffer(void* buf, int slot);


	virtual void					View_Render(void* rect);
	virtual void					RenderView(const void* view, int nClearFlags, int whatToDraw);
	virtual void					View_Fade(void* pSF);

	virtual void					SetCrosshairAngle(const QAngle& angle);

	virtual void					InitSprite(void* pSprite, const char* loadname);
	virtual void					ShutdownSprite(void* pSprite);

	virtual int						GetSpriteSize(void) const;

	virtual void					VoiceStatus(int entindex, void* bTalking);

	virtual void					InstallStringTableCallback(const char* tableName);

	virtual void					FrameStageNotify(void* curStage);

	virtual bool					DispatchUserMessage(int msg_type, void* msg_data);

	// Save/restore system hooks
	virtual void* SaveInit(int size);
	virtual void			SaveWriteFields(void*, const char*, void*, void*, void*, int);
	virtual void			SaveReadFields(void*, const char*, void*, void*, void*, int);
	virtual void			PreSave(void*);
	virtual void			Save(void*);
	virtual void			WriteSaveHeaders(void*);
	virtual void			ReadRestoreHeaders(void*);
	virtual void			Restore(void*, bool);
	virtual void			DispatchOnRestore();
	virtual void			WriteSaveGameScreenshot(const char* pFilename);

	// Given a list of "S(wavname) S(wavname2)" tokens, look up the localized text and emit
	//  the appropriate close caption if running with closecaption = 1
	virtual void			EmitSentenceCloseCaption(char const* tokenstream);
	virtual void			EmitCloseCaption(char const* captionname, float duration);

	virtual void* GetStandardRecvProxies();

	virtual bool			CanRecordDemo(char* errorMsg, int length) const;

	virtual void			OnDemoRecordStart(char const* pDemoBaseName);
	virtual void			OnDemoRecordStop();
	virtual void			OnDemoPlaybackStart(char const* pDemoBaseName);
	virtual void			OnDemoPlaybackStop();

	virtual bool			ShouldDrawDropdownConsole();

	// Get client screen dimensions
	virtual int				GetScreenWidth();
	virtual int				GetScreenHeight();

	// save game screenshot writing
	virtual void			WriteSaveGameScreenshotOfSize(const char* pFilename, int width, int height, bool bCreatePowerOf2Padded/*=false*/, bool bWriteVTF/*=false*/);

	// Gets the location of the player viewpoint
	virtual bool			GetPlayerView(void* playerView);

	// Matchmaking
	virtual void			SetupGameProperties(void* contexts, void* properties);
	virtual void* GetPresenceID(const char* pIDName);
	virtual const char* GetPropertyIdString(const void* id);
	virtual void			GetPropertyDisplayString(void* id, void* value, char* pOutput, int nBytes);
	virtual void			StartStatsReporting(HANDLE handle, bool bArbitrated);

	virtual void			InvalidateMdlCache();

	virtual void			ReloadFilesInList(void* pFilesToReload);

	// Let the client handle UI toggle - if this function returns false, the UI will toggle, otherwise it will not.
	virtual bool			HandleUiToggle();

	// Allow the console to be shown?
	virtual bool			ShouldAllowConsole();

	// Get renamed recv tables
	virtual void* GetRenamedRecvTableInfos();

	// Get the mouthinfo for the sound being played inside UI panels
	virtual void* GetClientUIMouthInfo();

	// Notify the client that a file has been received from the game server
	virtual void			FileReceived(const char* fileName, unsigned int transferID);

	virtual const char* TranslateEffectForVisionFilter(const char* pchEffectType, const char* pchEffectName);

	virtual void			ClientAdjustStartSoundParams(struct StartSoundParams_t& params);

	// Returns true if the disconnect command has been handled by the client
	virtual bool DisconnectAttempt(void);
public:
	void PrecacheMaterial(const char* pMaterialName);

	virtual bool IsConnectedUserInfoChangeAllowed(void* pCvar);

private:
	void UncacheAllMaterials();
	void ResetStringTablePointers();

	void* m_CachedMaterials;
};

class ClientModeShared : public IClientMode, public CGameEventListener
{
	// IClientMode overrides.
public:
	virtual void* DECLARE_CLASS_NOBASE(ClientModeShared);

	ClientModeShared();
	virtual			~ClientModeShared();

	virtual void	Init();
	virtual void	InitViewport();
	virtual void	VGui_Shutdown();
	virtual void	Shutdown();

	virtual void	LevelInit(const char* newmap);
	virtual void	LevelShutdown(void);

	virtual void	Enable();
	virtual void	Disable();
	virtual void	Layout();

	virtual void	ReloadScheme(void);
	virtual void	OverrideView(void* pSetup);
	virtual bool	ShouldDrawDetailObjects();
	virtual bool	ShouldDrawEntity(void* pEnt);
	virtual bool	ShouldDrawLocalPlayer(void* pPlayer);
	virtual bool	ShouldDrawViewModel();
	virtual bool	ShouldDrawParticles();
	virtual bool	ShouldDrawCrosshair(void);
	virtual bool	ShouldBlackoutAroundHUD();
	virtual void* ShouldOverrideHeadtrackControl();
	virtual void	AdjustEngineViewport(int& x, int& y, int& width, int& height);
	virtual void	PreRender(void* pSetup);
	virtual void	PostRender();
	virtual void	PostRenderVGui();
	virtual void	ProcessInput(bool bActive);
	virtual bool	CreateMove(float flInputSampleTime, CUserCmd* cmd);
	virtual void	Update();

	// Input
	virtual int		KeyInput(int down, void* keynum, const char* pszCurrentBinding);
	virtual int		HudElementKeyInput(int down, void* keynum, const char* pszCurrentBinding);
	virtual void	OverrideMouseInput(float* x, float* y);
	virtual void	StartMessageMode(int iMessageModeType);
	virtual void* GetMessagePanel();

	virtual void	ActivateInGameVGuiContext(void* pPanel);
	virtual void	DeactivateInGameVGuiContext();

	// The mode can choose to not draw fog
	virtual bool	ShouldDrawFog(void);

	virtual float	GetViewModelFOV(void);
	virtual void* GetViewport() { return m_pViewport; }
	// Gets at the viewports vgui panel animation controller, if there is one...
	virtual void* GetViewportAnimationController()
	{
		return GetMessagePanel();
	}

	virtual void FireGameEvent(void* event);

	virtual bool CanRecordDemo(char* errorMsg, int length) const { return true; }

	virtual int HandleSpectatorKeyInput(int down, void* keynum, const char* pszCurrentBinding);

	virtual void	ComputeVguiResConditions(void* pkvConditions);

	//=============================================================================
	// HPE_BEGIN:
	// [menglish] Save server information shown to the client in a persistent place
	//=============================================================================

	virtual wchar_t* GetServerName() { return NULL; }
	virtual void SetServerName(wchar_t* name) {};
	virtual wchar_t* GetMapName() { return NULL; }
	virtual void SetMapName(wchar_t* name) {};

	//=============================================================================
	// HPE_END
	//=============================================================================

	virtual bool	DoPostScreenSpaceEffects(const void* pSetup);

	virtual void	DisplayReplayMessage(const char* pLocalizeName, float flDuration, bool bUrgent,
		const char* pSound, bool bDlg);

	virtual bool	IsInfoPanelAllowed() { return true; }
	virtual void	InfoPanelDisplayed() { }
	virtual bool	IsHTMLInfoPanelAllowed() { return true; }

protected:
	void* m_pViewport;

	void			DisplayReplayReminder();

private:
	virtual void	UpdateReplayMessages();

	void			ClearReplayMessageList();

#if defined( REPLAY_ENABLED )
	float					m_flReplayStartRecordTime;
	float					m_flReplayStopRecordTime;
	CReplayReminderPanel* m_pReplayReminderPanel;
#endif

	// Message mode handling
	// All modes share a common chat interface
	void* m_pChatElement;
	void*			m_CursorNone;
	void* m_pWeaponSelection;
	int						m_nRootSize[2];
};


class IPanel : public IBaseInterface
{
public:
	virtual void Init(unsigned int vguiPanel, void* panel) = 0;

	// methods
	virtual void SetPos(unsigned int vguiPanel, int x, int y) = 0;
	virtual void GetPos(unsigned int vguiPanel, int& x, int& y) = 0;
	virtual void SetSize(unsigned int vguiPanel, int wide, int tall) = 0;
	virtual void GetSize(unsigned int vguiPanel, int& wide, int& tall) = 0;
	virtual void SetMinimumSize(unsigned int vguiPanel, int wide, int tall) = 0;
	virtual void GetMinimumSize(unsigned int vguiPanel, int& wide, int& tall) = 0;
	virtual void SetZPos(unsigned int vguiPanel, int z) = 0;
	virtual int  GetZPos(unsigned int vguiPanel) = 0;

	virtual void GetAbsPos(unsigned int vguiPanel, int& x, int& y) = 0;
	virtual void GetClipRect(unsigned int vguiPanel, int& x0, int& y0, int& x1, int& y1) = 0;
	virtual void SetInset(unsigned int vguiPanel, int left, int top, int right, int bottom) = 0;
	virtual void GetInset(unsigned int vguiPanel, int& left, int& top, int& right, int& bottom) = 0;

	virtual void SetVisible(unsigned int vguiPanel, bool state) = 0;
	virtual bool IsVisible(unsigned int vguiPanel) = 0;
	virtual void SetParent(unsigned int vguiPanel, unsigned int newParent) = 0;
	virtual int GetChildCount(unsigned int vguiPanel) = 0;
	virtual unsigned int GetChild(unsigned int vguiPanel, int index) = 0;
	virtual void*& GetChildren(unsigned int vguiPanel) = 0;
	virtual unsigned int GetParent(unsigned int vguiPanel) = 0;
	virtual void MoveToFront(unsigned int vguiPanel) = 0;
	virtual void MoveToBack(unsigned int vguiPanel) = 0;
	virtual bool HasParent(unsigned int vguiPanel, unsigned int potentialParent) = 0;
	virtual bool IsPopup(unsigned int vguiPanel) = 0;
	virtual void SetPopup(unsigned int vguiPanel, bool state) = 0;
	virtual bool IsFullyVisible(unsigned int vguiPanel) = 0;

	// gets the scheme this panel uses
	virtual void* GetScheme(unsigned int vguiPanel) = 0;
	// gets whether or not this panel should scale with screen resolution
	virtual bool IsProportional(unsigned int vguiPanel) = 0;
	// returns true if auto-deletion flag is set
	virtual bool IsAutoDeleteSet(unsigned int vguiPanel) = 0;
	// deletes the Panel * associated with the unsigned int
	virtual void DeletePanel(unsigned int vguiPanel) = 0;

	// input interest
	virtual void SetKeyBoardInputEnabled(unsigned int vguiPanel, bool state) = 0;
	virtual void SetMouseInputEnabled(unsigned int vguiPanel, bool state) = 0;
	virtual bool IsKeyBoardInputEnabled(unsigned int vguiPanel) = 0;
	virtual bool IsMouseInputEnabled(unsigned int vguiPanel) = 0;

	// calculates the panels current position within the hierarchy
	virtual void Solve(unsigned int vguiPanel) = 0;

	// gets names of the object (for debugging purposes)
	virtual const char* GetName(unsigned int vguiPanel) = 0;
	virtual const char* GetClassName(unsigned int vguiPanel) = 0;

	// delivers a message to the panel
	virtual void SendMessage(unsigned int vguiPanel, void* params, unsigned int ifromPanel) = 0;

	// these pass through to the IClientPanel
	virtual void Think(unsigned int vguiPanel) = 0;
	virtual void PerformApplySchemeSettings(unsigned int vguiPanel) = 0;
	virtual void PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce = true) = 0;
	virtual void Repaint(unsigned int vguiPanel) = 0;
	virtual unsigned int IsWithinTraverse(unsigned int vguiPanel, int x, int y, bool traversePopups) = 0;
	virtual void OnChildAdded(unsigned int vguiPanel, unsigned int child) = 0;
	virtual void OnSizeChanged(unsigned int vguiPanel, int newWide, int newTall) = 0;

	virtual void InternalFocusChanged(unsigned int vguiPanel, bool lost) = 0;
	virtual bool RequestInfo(unsigned int vguiPanel, void* outputData) = 0;
	virtual void RequestFocus(unsigned int vguiPanel, int direction = 0) = 0;
	virtual bool RequestFocusPrev(unsigned int vguiPanel, unsigned int existingPanel) = 0;
	virtual bool RequestFocusNext(unsigned int vguiPanel, unsigned int existingPanel) = 0;
	virtual unsigned int GetCurrentKeyFocus(unsigned int vguiPanel) = 0;
	virtual int GetTabPosition(unsigned int vguiPanel) = 0;

	// used by ISurface to store platform-specific data
	virtual void* Plat(unsigned int vguiPanel) = 0;
	virtual void SetPlat(unsigned int vguiPanel, void* Plat) = 0;

	// returns a pointer to the vgui controls baseclass Panel *
	// destinationModule needs to be passed in to verify that the returned Panel * is from the same module
	// it must be from the same module since Panel * vtbl may be different in each module
	virtual void* GetPanel(unsigned int vguiPanel, const char* destinationModule) = 0;

	virtual bool IsEnabled(unsigned int vguiPanel) = 0;
	virtual void SetEnabled(unsigned int vguiPanel, bool state) = 0;

	// Used by the drag/drop manager to always draw on top
	virtual bool IsTopmostPopup(unsigned int vguiPanel) = 0;
	virtual void SetTopmostPopup(unsigned int vguiPanel, bool state) = 0;

	// sibling pins
	virtual void SetSiblingPin(unsigned int vguiPanel, unsigned int newSibling, byte iMyCornerToPin = 0, byte iSiblingCornerToPinTo = 0) = 0;

	const char* GetName2(unsigned int vguiPanel)
	{
		typedef const char* (__thiscall* Fn)(PVOID, unsigned int);
		return getvfunc<Fn>(this, 36)(this, vguiPanel); //  Name of panel is at index 36
	}
};

struct Vertex_t
{
	

	void*	m_Position;
	void*	m_TexCoord;
};
// Refactor these two
struct CharRenderInfo
{
	// Text pos
	int				x, y;
	// Top left and bottom right
	// This is now a pointer to an array maintained by the surface, to avoid copying the data on the 360
	Vertex_t* verts;
	int				textureId;
	int				abcA;
	int				abcB;
	int				abcC;
	int				fontTall;
	void*			currentFont;
	// In:
	void*	drawType;
	wchar_t			ch;

	// Out
	bool			valid;
	// In/Out (true by default)
	bool			shouldclip;
};

class ISurface : public IAppSystem
{
public:
	// call to Shutdown surface; surface can no longer be used after this is called
	virtual void		Shutdown() = 0;

	// frame
	virtual void		RunFrame() = 0;

	// hierarchy root
	virtual unsigned int* GetEmbeddedPanel() = 0;
	virtual void		SetEmbeddedPanel(unsigned int* pPanel) = 0;

	// drawing context
	virtual void		PushMakeCurrent(unsigned int* panel, bool useInsets) = 0;
	virtual void		PopMakeCurrent(unsigned int* panel) = 0;

	// rendering functions
	virtual void		DrawSetColor(int r, int g, int b, int a) = 0;
	virtual void		DrawSetColor(Color col) = 0;

	virtual void		DrawFilledRect(int x0, int y0, int x1, int y1) = 0;
	virtual void		DrawFilledRectArray(void* pRects, int numRects) = 0;
	virtual void		DrawOutlinedRect(int x0, int y0, int x1, int y1) = 0;

	virtual void		DrawLine(int x0, int y0, int x1, int y1) = 0;
	virtual void		DrawPolyLine(int* px, int* py, int numPoints) = 0;

	virtual void		DrawSetTextFont(int font) = 0;
	virtual void		DrawSetTextColor(int r, int g, int b, int a) = 0;
	virtual void		DrawSetTextColor(Color col) = 0;
	virtual void		DrawSetTextPos(int x, int y) = 0;
	virtual void		DrawGetTextPos(int& x, int& y) = 0;
	virtual void		DrawPrintText(const wchar_t* text, int textLen, void* drawType = 0) = 0;
	virtual void		DrawUnicodeChar(wchar_t wch, void* drawType = 0) = 0;

	virtual void		DrawFlushText() = 0;		// flushes any buffered text (for rendering optimizations)
	virtual void* CreateHTMLWindow(void* events, unsigned int* context) = 0;
	virtual void		Nothing__00(void*) = 0;
	virtual void		Nothing__01(void*) = 0;

	enum ETextureFormat
	{
		eTextureFormat_RGBA,
		eTextureFormat_BGRA,
		eTextureFormat_BGRA_Opaque, // bgra format but alpha is always 255, CEF does this, we can use this fact for better perf on win32 gdi
	};
	virtual int			DrawGetTextureId(char const* filename) = 0;
	virtual bool		DrawGetTextureFile(int id, char* filename, int maxlen) = 0;
	virtual void		DrawSetTextureFile(int id, const char* filename, int hardwareFilter, bool forceReload) = 0;
	virtual void		DrawSetTextureRGBA(int id, const unsigned char* rgba, int wide, int tall, int hardwareFilter, bool forceReload) = 0;
	virtual void		DrawSetTexture(int id) = 0;
	virtual void		DrawGetTextureSize(int id, int& wide, int& tall) = 0;
	virtual void		DrawTexturedRect(int x0, int y0, int x1, int y1) = 0;
	virtual bool		IsTextureIDValid(int id) = 0;
	virtual bool		DeleteTextureByID(int id) = 0;

	virtual int			CreateNewTextureID(bool procedural = false) = 0;

	virtual void		GetScreenSize(int& wide, int& tall) = 0;
	virtual void		Nothing__02() = 0;
	virtual void		BringToFront(unsigned int* panel) = 0;
	virtual void		SetForegroundWindow(unsigned int* panel) = 0;
	virtual void		Nothing__03() = 0;
	virtual void		SetMinimized(unsigned int* panel, bool state) = 0;
	virtual bool		IsMinimized(unsigned int* panel) = 0;
	virtual void		Nothing__04() = 0;
	virtual void		SetTitle(unsigned int* panel, const wchar_t* title) = 0;
	virtual void		Nothing__05() = 0;

	// windows stuff
	virtual void		CreatePopup(unsigned int* panel, bool minimised, bool showTaskbarIcon = true, bool disabled = false, bool mouseInput = true, bool kbInput = true) = 0;
	virtual void		SwapBuffers(unsigned int* panel) = 0;
	virtual void		Invalidate(unsigned int* panel) = 0;
	virtual void		SetCursor(void* cursor) = 0;
	virtual void		SetCursorAlwaysVisible(bool visible) = 0;
	virtual bool		IsCursorVisible() = 0;
	virtual void		Nothing__08() = 0;
	virtual bool		IsWithin(int x, int y) = 0;
	virtual bool		HasFocus() = 0;

	// returns true if the surface supports minimize & maximize capabilities
	enum SurfaceFeature_e
	{
		ANTIALIASED_FONTS = 1,
		DROPSHADOW_FONTS = 2,
		ESCAPE_KEY = 3,
		OPENING_NEW_HTML_WINDOWS = 4,
		FRAME_MINIMIZE_MAXIMIZE = 5,
		OUTLINE_FONTS = 6,
		DIRECT_HWND_RENDER = 7,
	};
	virtual bool		SupportsFeature(SurfaceFeature_e feature) = 0;

	// restricts what gets drawn to one panel and it's children
	// currently only works in the game
	virtual void		RestrictPaintToSinglePanel(unsigned int panel) = 0;
	virtual void		Nothing__09() = 0;
	virtual void		Nothing__10() = 0;

	virtual void		UnlockCursor() = 0;
	virtual void		LockCursor() = 0;
	virtual void		Nothing__11() = 0;
	virtual void		Nothing__12() = 0;
	virtual void		SetTopLevelFocus(unsigned int panel) = 0;
	virtual int			ISCreateFont() = 0;
	virtual bool		SetFontGlyphSet(int font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0) = 0;
	virtual bool		SetFontGlyphSet_Extended() = 0; // just use above lol.

	// adds a custom font file (only supports true type font files (.ttf) for now)
	virtual bool		AddCustomFontFile(const char* fontName, const char* fontFileName) = 0;

	// returns the details about the font
	virtual int			GetFontTall(int font) = 0;
	virtual int			GetFontTallRequested(int font) = 0;
	virtual int			GetFontAscent(int font, wchar_t wch) = 0;
	virtual bool		IsFontAdditive(int font) = 0;
	virtual void		GetCharABCwide(int font, int ch, int& a, int& b, int& c) = 0;
	virtual int			GetCharacterWidth(int font, int ch) = 0;
	virtual void		GetTextSize(int font, const wchar_t* text, int& wide, int& tall) = 0;

	virtual void		Nothing__13() = 0;
	virtual void		Nothing__14() = 0;

	// plays a sound
	virtual void		ISPlaySound(const char* fileName) = 0;


	//!! these functions should not be accessed directly, but only through other vgui items
	//!! need to move these to seperate interface
	virtual int			GetPopupCount() = 0;
	virtual unsigned int* GetPopup(int index) = 0;
	virtual bool		ShouldPaintChildPanel(unsigned int* childPanel) = 0;
	virtual bool		RecreateContext(unsigned int* panel) = 0;
	virtual void		AddPanel(unsigned int* panel) = 0;
	virtual void		ReleasePanel(unsigned int* panel) = 0;
	virtual void		MovePopupToFront(unsigned int* panel) = 0;
	virtual void		MovePopupToBack(unsigned int* panel) = 0;

	virtual void		SolveTraverse(unsigned int* panel, bool forceApplySchemeSettings = false) = 0;
	virtual void		PaintTraverse(unsigned int* panel) = 0;

	virtual void		EnableMouseCapture(unsigned int* panel, bool state) = 0;

	// returns the size of the workspace
	virtual void		GetWorkspaceBounds(int& x, int& y, int& wide, int& tall) = 0;

	// gets the absolute coordinates of the screen (in windows space)
	virtual void		GetAbsoluteWindowBounds(int& x, int& y, int& wide, int& tall) = 0;

	// gets the base resolution used in proportional mode
	virtual void		GetProportionalBase(int& width, int& height) = 0;

	virtual void		CalculateMouseVisible() = 0;
	virtual bool		NeedKBInput() = 0;

	virtual void		Nothing__15() = 0;

	virtual void		SurfaceGetCursorPos(int& x, int& y) = 0;
	virtual void		SurfaceSetCursorPos(int x, int y) = 0;

	// SRC only functions!!!
	virtual void		DrawTexturedLine(const Vertex_t& a, const Vertex_t& b) = 0;
	virtual void		DrawOutlinedCircle(int x, int y, int radius, int segments) = 0;
	virtual void		DrawTexturedPolyLine(const Vertex_t* p, int n) = 0; // (Note: this connects the first and last points).
	virtual void		DrawTexturedSubRect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
	virtual void		DrawTexturedPolygon(int n, Vertex_t* pVertice, bool bClipVertices = true) = 0;
	virtual const wchar_t* GetTitle(unsigned int panel) = 0;
	virtual bool		IsCursorLocked(void) const = 0;
	virtual void		SetWorkspaceInsets(int left, int top, int right, int bottom) = 0;
	// Lower level char drawing code, call DrawGet then pass in info to DrawRender
	virtual bool		DrawGetUnicodeCharRenderInfo(wchar_t ch, CharRenderInfo& info) = 0;
	virtual void		DrawRenderCharFromInfo(const CharRenderInfo& info) = 0;

	// global alpha setting functions
	// affect all subsequent draw calls - shouldn't normally be used directly, only in Panel::PaintTraverse()
	virtual void		DrawSetAlphaMultiplier(float alpha /* [0..1] */) = 0;
	virtual float		DrawGetAlphaMultiplier() = 0;

	// web browser
	virtual void		SetAllowHTMLJavaScript(bool state) = 0;

	// video mode changing
	virtual void		OnScreenSizeChanged(int nOldWidth, int nOldHeight) = 0;

	virtual void		Nothing__16() = 0;

	// create IVguiMatInfo object ( IMaterial wrapper in VguiMatSurface, NULL in CWin32Surface )
	virtual void* DrawGetTextureMatInfoFactory(int id) = 0;

	virtual void		PaintTraverseEx(unsigned int panel, bool paintPopups = false) = 0;
	virtual float		GetZPos() const = 0;

	// From the Xbox
	virtual void		SetPanelForInput(unsigned int vpanel) = 0;
	virtual void		DrawFilledRectFastFade(int x0, int y0, int x1, int y1, int fadeStartPt, int fadeEndPt, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) = 0;
	virtual void		DrawFilledRectFade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) = 0;
	virtual void		DrawSetTextureRGBAEx(int id, const unsigned char* rgba, int wide, int tall, void* imageFormat) = 0;
	virtual void		DrawSetTextScale(float sx, float sy) = 0;
	virtual bool		SetBitmapFontGlyphSet(int font, const char* windowsFontName, float scalex, float scaley, int flags) = 0;

	// adds a bitmap font file
	virtual bool		AddBitmapFontFile(const char* fontFileName) = 0;
	// sets a symbol for the bitmap font
	virtual void		SetBitmapFontName(const char* pName, const char* pFontFilename) = 0;
	// gets the bitmap font filename
	virtual const char* GetBitmapFontName(const char* pName) = 0;
	virtual void		ClearTemporaryFontCache(void) = 0;
	virtual void* GetIconImageForFullPath(char const* pFullPath) = 0;
	virtual void		DrawUnicodeString(const wchar_t* pwString, void* drawType = 0) = 0;
	virtual void		PrecacheFontCharacters(int font, const wchar_t* pCharacters) = 0;
	// Console-only.  Get the string to use for the current video mode for layout files.
	virtual const char* GetResolutionKey(void) const = 0;
	virtual const char* GetFontName(int font) = 0;
	virtual const char* GetFontFamilyName(int font) = 0;
	virtual void		GetKernedCharWidth(int font, wchar_t ch, wchar_t chBefore, wchar_t chAfter, float& wide, float& abcA) = 0;
	virtual bool		ForceScreenSizeOverride(bool bState, int wide, int tall) = 0;
	// LocalToScreen, ParentLocalToScreen fixups for explicit PaintTraverse calls on Panels not at 0, 0 position
	virtual bool		ForceScreenPosOffset(bool bState, int x, int y) = 0;
	virtual void		OffsetAbsPos(int& x, int& y) = 0;

	// Causes fonts to get reloaded, etc.
	virtual void		ResetFontCaches() = 0;

	virtual int			GetTextureNumFrames(int id) = 0;
	virtual void		DrawSetTextureFrame(int id, int nFrame, unsigned int* pFrameCache) = 0;
	virtual bool		IsScreenSizeOverrideActive(void) = 0;
	virtual bool		IsScreenPosOverrideActive(void) = 0;

	virtual void		DestroyTextureID(int id) = 0;

	virtual void		DrawUpdateRegionTextureRGBA(int nTextureID, int x, int y, const unsigned char* pchData, int wide, int tall, void* imageFormat) = 0;

	virtual void		Nothing__17() = 0;

	virtual const char* GetWebkitHTMLUserAgentString() = 0;

	virtual void* AccessChromeHTMLController() = 0;

	// the origin of the viewport on the framebuffer (Which might not be 0,0 for stereo)
	virtual void		SetFullscreenViewport(int x, int y, int w, int h) = 0; // this uses NULL for the render target.
	virtual void		GetFullscreenViewport(int& x, int& y, int& w, int& h) = 0;
	virtual void		PushFullscreenViewport() = 0;
	virtual void		PopFullscreenViewport() = 0;

	// handles support for software cursors
	virtual void		SetSoftwareCursor(bool bUseSoftwareCursor) = 0;
	virtual void		PaintSoftwareCursor() = 0;


	void DrawSetColor2(int r, int g, int b, int a)
	{
		typedef void(__thiscall* fn)(void*, int, int, int, int);
		return getvfunc<fn>(this, 11)(this, r, g, b, a);
	}
	void DrawFilledRect2(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fn)(void*, int, int, int, int);
		return getvfunc<fn>(this, 12)(this, x0, y0, x1, y1);
	}
	void DrawOutlineRect2(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fn)(void*, int, int, int, int);
		return getvfunc<fn>(this, 14)(this, x0, y0, x1, y1);
	}
	void DrawLine2(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fn)(void*, int, int, int, int);
		return getvfunc<fn>(this, 15)(this, x0, y0, x1, y1);
	}
	void DrawSetTextFont2(unsigned long HFont)
	{
		typedef void(__thiscall* fn)(void*, unsigned long);
		return getvfunc<fn>(this, 17)(this, HFont);
	}
	void DrawSetTextColor2(Color col)
	{
		typedef void(__thiscall* fn)(void*, Color);
		return getvfunc<fn>(this, 18)(this, col);
	}
	void DrawSetTextPos2(int x, int y)
	{
		typedef void(__thiscall* fn)(void*, int, int);
		return getvfunc<fn>(this, 20)(this, x, y);
	}
	void DrawPrintText2(const wchar_t* text, int textLen)
	{
		typedef void(__thiscall* fn)(void*, const wchar_t*, int, int);
		return getvfunc<fn>(this, 22)(this, text, textLen, 0);
	}
	unsigned long FontCreate2()
	{
		typedef unsigned long(__thiscall* fn)(void*);
		return getvfunc<fn>(this, 66)(this);
	}
	void SetGlpyhSet2(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* fn)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
		return getvfunc<fn>(this, 67)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
};

struct csurface_t
{
	const char* name;
	short surfaceProps;
	unsigned short  flags;
};


class trace_t : public CBaseTrace
{
public:
	bool DidHitWorld();
	bool DidHitNonWorldEntity();
	int GetEntityIndex();
	bool DidHit();
public:
	float fractionleftsolid;
	csurface_t surface;
	int hitgroup;
	short physicsbone;
	unsigned short worldSurfaceIndex;
	void* m_pEnt;
	int hitbox;
};

class IEngineTrace
{
public:
	void TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace)
	{
		typedef void(__thiscall* fnTraceRay)(void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
		getvfunc<fnTraceRay>(this, 4)(this, ray, fMask, pTraceFilter, pTrace);
	}
};

class CInput : public IInput
{
	// Interface
public:
	CInput(void);
	~CInput(void);

	
	

};
