#ifndef WATCHFILM_H
#define WATCHFILM_H
#include <QString>
#include <QDate>
class WatchFilm
{
public:
    WatchFilm();

    WatchFilm(QString,QString,QString,QDate);

    QString getGanre();

    QString getAgeRaiting();

    QString getCountry();

    QDate getRelease();

    void setGanre(QString);

    void setAgeRaiting(QString);

    void setCountry(QString);

    void setRelease(QDate);

private:

    QString _ganre;

    QString _ageRaiting;

    QString _country;

    QDate _release;

};

#endif // WATCHFILM_H
