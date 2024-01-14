#pragma once

#include <Engine/events.h>

#define ENG_ADD_RECEIVER(obj) eng::g_EventSource.AddReceiver(&obj.GetReceiver())
#define ENG_ADD_RECEIVER_PTR(obj) eng::g_EventSource.AddReceiver(&obj->GetReceiver())

#define ENG_ADD_HOOK(obj, ev, hook) obj.GetReceiver().AddHook(ev, hook)
#define ENG_ADD_HOOK_PTR(obj, ev, hook) obj->GetReceiver().AddHook(ev, hook)

namespace eng
{

	extern EventSource g_EventSource;

}
