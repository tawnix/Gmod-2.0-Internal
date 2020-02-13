#pragma once
#include <Windows.h>
#include "InterfaceVT.h"
#include "Matrix.h"
#include "ModelInfo.h"

class IClientNetworkable;


typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);

class IClientMode {

};

class CGameEventListener {

};

/*class CUserCmd
{
public:
	virtual ~CUserCmd() {};
	CUserCmd()
	{
		reset();
	}

	void reset()
	{
		i_command_number = 0;
		i_tick_count = 0;
		viewangles.Init();
		fl_forward_move = 0.0f;
		fl_side_move = 0.0f;
		fl_up_move = 0.0f;
		i_buttons = 0;
		impulse = 0;
		i_weapon_select = 0;
		i_weapon_sub_type = 0;
		random_seed = 0;
		mousedx = 0;
		mousedy = 0;
		headangles.Init();
		headoffset.Init();

		b_has_been_predicted = false;
	}

	CUserCmd& operator =(const CUserCmd& src)
	{
		if (this == &src)
			return *this;

		i_command_number = src.i_command_number;
		i_tick_count = src.i_tick_count;
		viewangles = src.viewangles;
		fl_forward_move = src.fl_forward_move;
		fl_side_move = src.fl_side_move;
		fl_up_move = src.fl_up_move;
		i_buttons = src.i_buttons;
		impulse = src.impulse;
		i_weapon_select = src.i_weapon_select;
		i_weapon_sub_type = src.i_weapon_sub_type;
		random_seed = src.random_seed;
		mousedx = src.mousedx;
		mousedy = src.mousedy;

		b_has_been_predicted = src.b_has_been_predicted;
		headangles = src.headangles;
		headoffset = src.headoffset;
		return *this;
	}

	CUserCmd(const CUserCmd& src)
	{
		*this = src;
	}

	int i_command_number;
	int i_tick_count;
	Vector viewangles;
	Vector aimdirection;
	float fl_forward_move;
	float fl_side_move;
	float fl_up_move;
	int  i_buttons;
	BYTE impulse;
	int  i_weapon_select;
	int  i_weapon_sub_type;
	int  random_seed;
	short mousedx;
	short mousedy;
	bool b_has_been_predicted;
	Vector headangles;
	Vector headoffset;
};
*/

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
		return getvfunc<OriginalFn>(this, 89)(this);
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
	virtual IHandleEntity* GetEntityHandle() = 0;
	virtual const void*& OBBMinsPreScaled() const = 0;
	virtual const void*& OBBMaxsPreScaled() const = 0;
	virtual const void*& OBBMins() const = 0;
	virtual const void*& OBBMaxs() const = 0;
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

	int GetHealth() {
		return *(int*)(this + 0x90);
	}

	Vector GetOrigin() {
		Vector CurrOrigin;
		return *(Vector*)(this + 0x260);
	}

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