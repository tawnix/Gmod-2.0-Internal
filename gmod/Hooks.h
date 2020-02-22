#pragma once
#include "SDK Stuff.h"
#include "Aimbot.h"
#include <Windows.h>
#include "ESP.h"




class VmtHook {
    std::uintptr_t** baseclass_ = nullptr;
    std::unique_ptr<std::uintptr_t[]> current_vft_ = nullptr;
    std::uintptr_t* original_vft_ = nullptr;
    std::size_t total_functions_ = 0;
public:
    VmtHook() = default;

    explicit VmtHook(void* baseclass) {
        this->baseclass_ = static_cast<std::uintptr_t**>(baseclass);

        while (static_cast<std::uintptr_t*>(*this->baseclass_)[this->total_functions_])
            ++this->total_functions_;

        const auto tableSize = this->total_functions_ * sizeof(std::uintptr_t);

        this->original_vft_ = *this->baseclass_;
        this->current_vft_ = std::make_unique<std::uintptr_t[]>(this->total_functions_);

        std::memcpy(this->current_vft_.get(), this->original_vft_, tableSize);

        *this->baseclass_ = this->current_vft_.get();
    };

    ~VmtHook() {
        *this->baseclass_ = this->original_vft_;
    };

    template <typename Fn = void*>
    Fn GetOriginalFunction(const std::size_t functionIndex)
    {
        return reinterpret_cast<Fn>(this->original_vft_[functionIndex]);
    }

    bool HookFunction(void* newFunction, const std::size_t functionIndex) const
    {
        if (functionIndex > this->total_functions_)
            return false;

        this->current_vft_[functionIndex] = reinterpret_cast<std::uintptr_t>(newFunction);

        return true;
    }

    [[nodiscard]] bool UnhookFunction(const std::size_t functionIndex) const
    {
        if (functionIndex > this->total_functions_)
            return false;

        this->current_vft_[functionIndex] = this->original_vft_[functionIndex];

        return true;
    }

    [[nodiscard]] std::size_t GetTotalFunctions() const
    {
        return this->total_functions_;
    }
};



typedef bool(__thiscall* createMove_t)(void*, float, CUserCmd*);
createMove_t oCreateMove;

typedef void(__thiscall* paintTraverse_t)(void*, unsigned int, bool, bool);
paintTraverse_t oPaintTraverse;

VmtHook* v_hook;
VmtHook* v_hook2;

void __fastcall PaintTraverseFn(void* ecx, void* edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
    oPaintTraverse = (paintTraverse_t)v_hook2->GetOriginalFunction(41);
    oPaintTraverse(ecx, vguiPanel, forceRepaint, allowForce);



    if (CInterfaces::pEngine->IsInGame())
    {
        static unsigned int drawPanel;

        PCHAR pannelName = (PCHAR)CInterfaces::pPanel->GetName2(vguiPanel);
        //check to see if pannel name is MatSystemTopPanel
        if (strstr(pannelName, "FocusOverlayPanel"))//MatSystemTopPanel
            drawPanel = vguiPanel;

        if (vguiPanel != drawPanel)
        {
            return;
        }

        if (CInterfaces::pEngine->IsTakingScreenshot())
            return;

        ESP oESP;
        oESP.DrawText2();
        oESP.DrawName();
        oESP.DrawBox();
        oESP.DrawHealthValue();
    }
}

bool __fastcall CreateMoveFn(void* ecx, void* edx, float SampleTime, CUserCmd* cmd)
{
    oCreateMove = (createMove_t)v_hook->GetOriginalFunction(21);
    oCreateMove(ecx, SampleTime, cmd);

    CUserCmd* m_Cmd = cmd;

    if (!cmd->m_cmd_nr)
        return true;

    if (CInterfaces::pEngine->IsInGame())
    {
        if (GetAsyncKeyState(VK_XBUTTON2))
        {


            aimbot oAim;
            oAim.StartAim(m_Cmd);


            m_Cmd->m_viewangles = oAim.toAim;
        }
    }
    return true;
}



void InitaliseHooks()
{
	ClientModeShared* ClientShared = **reinterpret_cast<ClientModeShared***>((*reinterpret_cast<uintptr_t**>(CInterfaces::pClient))[10] + 5);

    v_hook = new VmtHook(reinterpret_cast<void*>(ClientShared));

    (createMove_t)v_hook->HookFunction(static_cast<void*>(CreateMoveFn), 21);
    
    v_hook2 = new VmtHook(reinterpret_cast<void*>(CInterfaces::pPanel));

    CInterfaces::pSurface->FontCreate2();

    (paintTraverse_t)v_hook2->HookFunction(static_cast<void*>(PaintTraverseFn), 41);

    
}




/*

 CInterfaces::pSurface->DrawLine2((width / 2), ((height / 2) - 15), (width/2), ((height/2) + 15));
 CInterfaces::pSurface->DrawLine2((width / 2) - 15, (height / 2), (width / 2) + 15, (height / 2));
*/