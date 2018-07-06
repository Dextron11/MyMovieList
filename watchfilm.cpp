#include "watchfilm.h"
WatchFilm::WatchFilm(){}
WatchFilm::WatchFilm(QString _ganre,QString _ageRaiting,
                     QString _country,QDate _release):
                    _ganre(_ganre),_ageRaiting(_ageRaiting),_country(_country),_release(_release){};

void WatchFilm::setAgeRaiting(QString age){
    _ageRaiting=age;
}

void WatchFilm::setGanre(QString ganre){
    _ganre=ganre;
}
void WatchFilm::setCountry(QString country){
    _country=country;
}
void WatchFilm::setRelease(QDate release){
    _release=release;
}
QString WatchFilm::getAgeRaiting() {return _ageRaiting;}

QString WatchFilm::getGanre() {return _ganre;}

QString WatchFilm::getCountry() {return _country;}

QDate WatchFilm::getRelease() {return _release;}
