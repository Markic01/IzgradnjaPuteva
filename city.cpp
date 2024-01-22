#include "city.h"

City::City() {}

void City::fromQVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();

    _x = map.value("x").toDouble();
    _y = map.value("y").toDouble();
    _name = map.value("name").toString();
    _visited = false;
}

QString City::toQString() const
{
    QString x(_name + " ---> (" + QString::number(_x) + ", " + QString::number(_y) + ")");
    return x;
}

double City::dist(City *other) const
{
    return sqrt((_x - other->getX())*(_x - other->getX()) + (_y - other->getY())*(_y - other->getY()));
}

double City::getX() const
{
    return _x;
}

double City::getY() const
{
    return _y;
}

QString City::getName() const
{
    return _name;
}

bool City::getVisited() const
{
    return _visited;
}

void City::setVisited()
{
    _visited = true;
}
