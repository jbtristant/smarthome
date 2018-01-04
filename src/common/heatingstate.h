#ifndef HEATINGSTATE_H
#define HEATINGSTATE_H

#include <QObject>

class HeatingState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)


public:
    explicit HeatingState(QString name = "", QString color = "#FFFFFF", QObject *parent = nullptr);
    HeatingState(const HeatingState &other);
    HeatingState& operator =(const HeatingState &other);

    QString name() const;
    QString color() const;

signals:

    void nameChanged(QString name);
    void colorChanged(QString color);

public slots:
    void setName(QString name);
    void setColor(QString color);

private:
    QString m_name;
    QString m_color;

};

#endif // HEATINGSTATE_H
