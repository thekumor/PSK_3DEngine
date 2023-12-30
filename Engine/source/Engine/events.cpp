#include "events.h"

namespace eng
{

	void EventReceiver::AddHook(EventType type, const Hook& hook)
	{
		auto finder = m_Events.find(type);

		if (finder != m_Events.end())
			finder->second.Hooks.emplace_back(hook);
		else
			m_Events[type] = Event(type, hook);
	}

	Event::Event(EventType type, const Hook& hook)
		: Type(type)
	{
		Hooks.emplace_back(hook);
	}

	EventReceiver* EventSource::AddReceiver(EventReceiver* rec)
	{
		return m_Receivers.emplace_back(rec);
	}

	void EventSource::CallEvent(EventType type, const EventData& data)
	{
		for (auto& r : m_Receivers)
		{
			auto finder = r->m_Events.find(type);

			if (finder != r->m_Events.end())
				for (auto& h : finder->second.Hooks)
					h.Callback(data);
		}
	}

	Hook::Hook(const std::string& name, const std::function<void(const EventData&)>& callback)
		: Name(name), Callback(callback)
	{
	}

	EventData::EventData(const std::any& data)
		: Data(data)
	{
	}

}