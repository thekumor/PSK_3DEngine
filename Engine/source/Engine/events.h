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

	/// <summary>
	/// Różne typy zdarzeń.
	/// </summary>
	enum class EventType : std::uint32_t
	{
		Invalid = 0,
		Update,
		KeyPress,
		MousePress,
		MouseWheel
	};

	/// <summary>
	/// Dane dla danego zdarzenia.
	/// </summary>
	struct EventData
	{
		EventData(const std::any& data);
		EventData() = default;

		/// <summary>
		/// Własne dane.
		/// </summary>
		std::any Data = {};
	};

	/// <summary>
	/// Haczyk dla zdarzeń. Posiada funkcję
	/// która jest uruchamiana w przypadku
	/// wywołania tego haczyka.
	/// </summary>
	struct Hook
	{
		Hook(const std::string& name, const std::function<void(const EventData&)>& callback);
		Hook() = default;

		/// <summary>
		/// Identyfikator.
		/// </summary>
		std::string Name = "";

		/// <summary>
		/// Funkcja zwrotna, callback.
		/// </summary>
		std::function<void(const EventData&)> Callback = {};
	};

	/// <summary>
	/// Zdarzenie. Posiada ono swoje haczyki.
	/// </summary>
	struct Event
	{
		Event(EventType type, const Hook& hook);
		Event() = default;

		/// <summary>
		/// Typ zdarzenia.
		/// </summary>
		EventType Type = EventType::Invalid;

		/// <summary>
		/// Wszystkie haczyki tego zdarzenia.
		/// </summary>
		std::vector<Hook> Hooks = {};
	};

	/// <summary>
	/// Klasa bazowa dla klas zdarzeniowych.
	/// </summary>
	class EventBase : public BaseClass
	{
	public:
		EventBase() = default;
	};

	/// <summary>
	/// Odbiornik zdarzeń. Uruchamia haczyki
	/// jeżeli źródło zdarzeń go o to poprosi.
	/// </summary>
	class EventReceiver : public EventBase
	{
	public:
		friend class EventSource;

		EventReceiver() = default;

		/// <summary>
		/// Dodaje nowy haczyk.
		/// </summary>
		/// <param name="type">Typ zdarzenia</param>
		/// <param name="hook">Haczyk pod zdarzenie</param>
		void AddHook(EventType type, const Hook& hook);
	private:
		/// <summary>
		/// Wszystkie zdarzenia pod dany typ.
		/// </summary>
		std::unordered_map<EventType, Event> m_Events = {};
	};

	/// <summary>
	/// Nakazuje odbiornikom wywołanie funkcji zwrotnych
	/// w przypadku, gdy programista wywoła zdarzenie.
	/// </summary>
	class EventSource : public EventBase
	{
	public:
		EventSource() = default;

		/// <summary>
		/// Odbiornik który od teraz będzie nasłuchiwać tego źródła.
		/// </summary>
		/// <param name="rec">Wskaźnik do odbiornika</param>
		/// <returns>Ten sam odbiornik, ale w wektorze</returns>
		EventReceiver* AddReceiver(EventReceiver* rec);

		/// <summary>
		/// Uruchamia zdarzenie.
		/// </summary>
		/// <param name="type">Typ zdarzenia</param>
		/// <param name="data">Dane własne</param>
		void CallEvent(EventType type, const EventData& data);
	private:
		/// <summary>
		/// Wszystkie odbiorniki, które nasłuchują tego źródła.
		/// </summary>
		std::vector<EventReceiver*> m_Receivers = {};
	};

	/// <summary>
	/// Umożliwia odbieranie i nadawanie zdarzeń klasom pochodnym.
	/// </summary>
	class EventInteractive : public EventBase
	{
	public:
		EventInteractive() = default;

		/// <summary>
		/// Zwraca odbiornik zdarzeń.
		/// </summary>
		/// <returns>Odbiornik zdarzeń</returns>
		inline EventReceiver& GetReceiver() { return m_Receiver; }

		/// <summary>
		/// Zwraca źródło zdarzeń.
		/// </summary>
		/// <returns>Źródło zdarzeń</returns>
		inline EventSource& GetSource() { return m_Source; }

	protected:
		/// <summary>
		/// Odbiornik zdarzeń.
		/// </summary>
		EventReceiver m_Receiver;

		/// <summary>
		/// Źródło zdarzeń.
		/// </summary>
		EventSource m_Source;
	};

}