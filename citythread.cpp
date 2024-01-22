#include "citythread.h"

#include <QMutexLocker>


CityThread::CityThread(QVector<City*> cities,int index, QMutex *mutex) : _index(index), _cities(cities), _mutex(mutex) {

    _cities[_index]->setVisited();
}

void CityThread::run()
{
    msleep(100);

    double min = -1;
    int minInd = -1;
    {
        QMutexLocker lock(_mutex);

        for(int i = 0; i < _cities.size(); ++i) {
            if (i == _index || _cities[i]->getVisited())
                continue;

            if (min  < 0 || _cities[_index]->dist(_cities[i]) < min) {
                min = _cities[_index]->dist(_cities[i]);
                minInd = i;
            }
        }
    }
    if(minInd !=-1)
        emit foundClosestCity(_index, minInd);
}
