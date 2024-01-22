#ifndef CITYTHREAD_H
#define CITYTHREAD_H

#include "city.h"
#include <QThread>
#include <QMutex>

class CityThread : public QThread
{
    Q_OBJECT
public:
    CityThread(QVector<City*> cities, int index, QMutex *mutex);

signals:
    void foundClosestCity(int index, int other);

protected:
    void run() override;
private:

    int _index;
    QVector<City*> _cities;
    QMutex *_mutex;
};

#endif // CITYTHREAD_H
