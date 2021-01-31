#include "Exceptions.h"

#include <utility>

namespace Exception
{
    RaytracingException::RaytracingException(std::string prefix, std::string message)
        : std::runtime_error(message),
          m_prefix(std::move(prefix)),
          m_message(std::move(message))
    {
        m_what = "[" + m_prefix + "] " + m_message;
    }

    RaytracingException::RaytracingException(std::string prefix, std::string message, std::string secondaryMessage)
        : std::runtime_error(message),
          m_prefix(std::move(prefix)),
          m_message(std::move(message)),
          m_secondaryMessage(std::move(secondaryMessage))
    {
        if (!m_secondaryMessage.empty())
            m_what = "[" + m_prefix + "] " + m_message + " -- " + m_secondaryMessage;
        else
            m_what = "[" + m_prefix + "] " + m_message;
    }
} // namespace Exception
