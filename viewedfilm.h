#ifndef VIEWEDFILM_H
#define VIEWEDFILM_H

#include <QString>
#include<QDate>
#include "watchfilm.h"

class ViewedFilm: public WatchFilm
{
public:
    ViewedFilm();
    ViewedFilm(QString _ganre,QString _ageRaiting, QString _country, QDate _release, int rating, QString opinion):
                WatchFilm(_ganre,_ageRaiting,_country,_release){
        _rating=rating;
        _opinion=opinion;
    }

    void setRating(int);

    void setOpinion(QString);

    int getRating();

    QString getOpinion();

private:

    int _rating;

    QString _opinion;
};

#endif // VIEWEDFILM_H
