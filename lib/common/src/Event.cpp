#include "Event.hpp"

namespace bns
{
    EventData::EventData(u32 u32) : U32(u32)
    {
    }

    Event::Event(EventType type, EventData data) : m_type(type), m_data(data)
    {
    }

    void Events::AddEvent(Event event)
    {
        m_events.push_back(event);
    }

    void Events::AddEvent(EventType type, EventData data)
    {
        m_events.push_back(Event(type));
    }

    void Events::ClearEvents()
    {
        m_events.clear();
    }

    bool Events::HasEvent(EventType type, Event* outEvent)
    {
        for (auto &event : m_events)
        {
            if (event.GetType() == type)
            {
                outEvent = &event;
                return true;
            }
        }

        return false;
    }
}