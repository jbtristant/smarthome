#include "heatingstate.h"

HeatingState::HeatingState(QString name, QString color, QObject *parent)
    : QObject(parent), m_name(name), m_color(color)
{

}

HeatingState::HeatingState(const HeatingState &other)
{
    m_name = other.name();
    m_color = other.color();
}

HeatingState &HeatingState::operator =(const HeatingState &other)
{
    if (this != &other) {
        m_name = other.name();
        m_color = other.color();
    }
    return *this;
}

QString HeatingState::name() const
{
    return m_name;
}

QString HeatingState::color() const
{
    return m_color;
}

void HeatingState::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void HeatingState::setColor(QString color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(m_color);
}
