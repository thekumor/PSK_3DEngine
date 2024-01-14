#pragma once

#include <Engine/events.h>

#define ENG_ADD_RECEIVER(obj) eng::g_EventSource.AddReceiver(&obj.GetReceiver())
#define ENG_ADD_RECEIVER_PTR(obj) eng::g_EventSource.AddReceiver(&obj->GetReceiver())

namespace eng
{

	extern EventSource g_EventSource;

}
