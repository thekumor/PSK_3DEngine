#pragma once

#include <vector>
#include <functional>
#include <string>
#include <unordered_map>
#include <any>
#include <cstdint>

namespace eng
{

	// A type for event, an alternative for strings.
	enum class EventType : std::int32_t
	{
		Invalid = -1,
		Update,
	};

	// This is data that is provided when event occurs.
	struct EventData
	{
		EventData(const std::any& data);
		EventData() = default;

		// Actual data.
		std::any Data = {};
	};

	// This literally 'hooks' into an event.
	// It has a callback, so any time an event occurs,
	// the callback will be run.
	struct Hook
	{
		Hook(const std::string& name, const std::function<void(const EventData&)>& callback);
		Hook() = default;

		// Identifier
		std::string Name = "";

		// Function that is run when event happens.
		std::function<void(const EventData&)> Callback = {};
	};

	// This is how events are layed out.
	struct Event
	{
		Event(EventType type, const Hook& hook);
		Event() = default;

		// Type associated with event.
		EventType Type = EventType::Invalid;

		// All the hooks that are pinned into event.
		std::vector<Hook> Hooks = {};
	};

	// Base class for event related classes.
	class EventBase
	{
	public:
		EventBase() = default;
	};

	// Any time an event occurs, this class will be informed
	// about it along with being provided with event's data.
	class EventReceiver : public EventBase
	{
	public:
		friend class EventSource;

		EventReceiver() = default;

		// Adds a new hook that will be run when event occurs.
		void AddHook(EventType type, const Hook& hook);
	private:
		// All the events this class listens to.
		std::unordered_map<EventType, Event> m_Events = {};
	};

	// You can run events with this class.
	// You have to provide it with receivers.
	class EventSource : public EventBase
	{
	public:
		EventSource() = default;

		// Adds a receiver so that it listens to this source.
		EventReceiver& AddReceiver(const EventReceiver& rec);

		// Fires an event with given data.
		void CallEvent(EventType type, const EventData& data);
	private:
		// All the receivers that are listening to this source.
		std::vector<EventReceiver> m_Receivers = {};
	};

}