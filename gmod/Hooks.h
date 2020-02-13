#pragma once
#include "SDK Stuff.h"
#include "Interface.h"
#include "Aimbot.h"
#include <Windows.h>


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


VmtHook* v_hook;


bool __fastcall CreateMoveFn(void* ecx, void* edx, float SampleTime, CUserCmd* cmd)
{
    oCreateMove = (createMove_t)v_hook->GetOriginalFunction(21);

    oCreateMove(ecx, SampleTime, cmd);

	CUserCmd* m_Cmd = cmd;

    if (!cmd->m_cmd_nr)
        return true;

    if (CInterfaces::pEngine->IsInGame())
    {
        aimbot oAim;
        if(GetAsyncKeyState(VK_XBUTTON2))
        {
            oAim.StartAim();

            m_Cmd->m_viewangles = oAim.toAim;
        }
    }

	return true;
}


void GrabClientModeShared()
{
	ClientModeShared* ClientShared = **reinterpret_cast<ClientModeShared***>((*reinterpret_cast<uintptr_t**>(CInterfaces::pClient))[10] + 5);

    v_hook = new VmtHook(reinterpret_cast<void*>(ClientShared));

    (createMove_t)v_hook->HookFunction(static_cast<void*>(CreateMoveFn), 21);

}


