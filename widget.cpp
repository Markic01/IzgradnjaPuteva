#include "widget.h"
#include "ui_widget.h"
#include "citythread.h"

#include <QFileDialog>
#include <QJsonDocument>
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pbLoad, &QPushButton::clicked, this, &Widget::loadJSON);
    connect(ui->pbBuild, &QPushButton::clicked, this, &Widget::build);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadJSON()
{
    QString filepath = QFileDialog::getOpenFileName(this,"caption","", "*.json");
    QFile f(filepath);
    if (!f.open(QFile::ReadOnly)) {
        return;
    }

    for (const auto x: _cities) {
        delete x;
    }

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();
    QVariantList v = doc.toVariant().toList();

    for (QVariant x : v){
        City *city = new City();
        city->fromQVariant(x);
        _cities.push_back(city);
    }

    for(const auto x: _cities) {
        ui->listCities->addItem(x->toQString());
    }
}

void Widget::build()
{
    if (_cities.empty()) {
        return;
    }
    CityThread *t = new CityThread(_cities,0,&_mutex);
    connect(t,&QThread::finished, t, &QObject::deleteLater);
    connect(t, &CityThread::foundClosestCity, this, &Widget::foundClosestCity);
    t->start();
}

void Widget::foundClosestCity(int i, int j)
{
    QString first = _cities[i]->getName();
    QString second = _cities[j]->getName();

    ui->teBuild->append("Added a new road from " + first + " to " + second);
    for (int i = _cities.size() - 1 ; i>=0; --i) {

        if(!_cities[i]->getVisited()) {
            CityThread *t = new CityThread(_cities,i,&_mutex);
            connect(t,&QThread::finished, t, &QObject::deleteLater);
            connect(t, &CityThread::foundClosestCity, this, &Widget::foundClosestCity);
            t->start();
            return;
        }
    }
    ui->teBuild->append("========================");
    ui->teBuild->append("All roads have been built!");
}
