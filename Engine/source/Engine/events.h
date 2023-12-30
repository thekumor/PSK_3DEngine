#pragma once

#include <vector>
#include <functional>
#include <string>
#include <unordered_map>
#include <any>
#include <cstdint>

#include <Engine/BaseClass.h>

namespace eng
{

	// Enumerator zdarzeń.
	enum class EventType : std::uint32_t
	{
		Invalid = 0,
		Update,
		KeyPress,
		MousePress,
		MouseWheel
	};

	// Dane dla zdarzenia.
	struct EventData
	{
		EventData(const std::any& data);
		EventData() = default;

		// Dane właściwe.
		std::any Data = {};
	};

	// 'Haczyk' dla zdarzeń. Posiada funkcję zwrotną,
	// która jest uruchamiana gdy wydarzenie jest
	// uruchamiane.
	struct Hook
	{
		Hook(const std::string& name, const std::function<void(const EventData&)>& callback);
		Hook() = default;

		// Identyfikator dla haczyka.
		std::string Name = "";

		// Funkcja zwrotna.
		std::function<void(const EventData&)> Callback = {};
	};

	// Zdarzenie, posiada haczyki.
	struct Event
	{
		Event(EventType type, const Hook& hook);
		Event() = default;

		// Typ zdarzenia.
		EventType Type = EventType::Invalid;

		// Wszystkie haczyki.
		std::vector<Hook> Hooks = {};
	};

	// Klasa bazowa dla klas zdarzeniowych.
	class EventBase : public BaseClass
	{
	public:
		EventBase() = default;
	};

	// Za każdym razem, gdy uruchamiane jest
	// wydarzenie, ta klasa (musi być przypięta pod źródło)
	// reaguje i uruchamia funkcje zwrotne haczyków.
	class EventReceiver : public EventBase
	{
	public:
		friend class EventSource;

		EventReceiver() = default;

		// Dodaje nowy haczyk.
		void AddHook(EventType type, const Hook& hook);
	private:
		// Wszystkie zdarzenia na które nasłuchuje ten odbiornik.
		std::unordered_map<EventType, Event> m_Events = {};
	};

	// Z pomocą tej klasy można uruchamiać zdarzenia.
	// Posiada odbiorniki, które z kolei posiadają
	// haczyki, które uruchamiają kod.
	class EventSource : public EventBase
	{
	public:
		EventSource() = default;

		// Dodaje odbiornik który od teraz będzie nasłuchiwać tego źródła.
		EventReceiver* AddReceiver(EventReceiver* rec);

		// Uruchamia zdarzenie z podanymi wartościami.
		void CallEvent(EventType type, const EventData& data);
	private:
		// Wszystkie odbiorniki które nasłuchują tego źródła.
		std::vector<EventReceiver*> m_Receivers = {};
	};

}