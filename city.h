#ifndef CITY_H
#define CITY_H

#include <QObject>
#include <QVariant>

class City : public QObject
{
    Q_OBJECT
public:
    City();
    void fromQVariant(const QVariant &variant);
    QString toQString() const;

    double dist(City *other) const;
    double getX() const;
    double getY() const;
    QString getName() const;
    bool getVisited() const;
    void setVisited();

private:
    QString _name;
    double _x,_y;
    bool _visited;
};

#endif // CITY_H
