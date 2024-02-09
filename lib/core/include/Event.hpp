#ifndef BNS_EVENT_HPP

#define BNS_EVENT_HPP

#include <vector>
#include "bns_types.hpp"

namespace bns
{
    enum class EventType
    {
        /// @brief Event is not set. This is used for initialization.
        None, 

        /// @brief The window is to be closed.
        WindowClose,

        /// @brief The window is resized.
        WindowResize,

        /// @brief The keyboard key is pressed.
        KeyDown,
    };

    union EventData
    {
        u32 U32;
        i32 I32;

        u32 Vec2u[2];
        i32 Vec2i[2];
        
        EventData() = default;

        /// @brief Sets the u32 value.
        /// @param u32 The u32 value.
        EventData(u32 u32);
    };

    class Event
    {
    private:
        EventType m_type;
        EventData m_data;

    public:
        Event() = default;
        Event(EventType type, EventData data = 0);

        /// @brief Gets the event type.
        /// @return The event type.
        inline EventType GetType() const { return m_type; }

        /// @brief Gets the event data.
        /// @return The event data.
        inline EventData GetData() const { return m_data; }
    };

    /// @brief The event collection which is used to store events during a frame.
    class Events
    {
    private:
        std::vector<Event> m_events;

    public:
        /// @brief Add an event.
        /// @param event The event to add.
        void AddEvent(Event event);

        /// @brief Adds an event according to the type.
        /// @param type The event type.
        /// @param data The event data.
        void AddEvent(EventType type, EventData data = 0);

        /// @brief Get the events.
        /// @return The events.
        inline const std::vector<Event> &GetEvents() { return m_events; }

        /// @brief Clear the events.
        void ClearEvents();

        /// @brief Check if an event exists in collection.
        /// @param type The event type.
        /// @param outEvent The event if found.
        /// @return True if event exists, false otherwise.
        bool HasEvent(EventType type, Event *outEvent = nullptr);
    };
}

#endif