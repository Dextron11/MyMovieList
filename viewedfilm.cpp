#include "viewedfilm.h"
ViewedFilm::ViewedFilm(){}
void ViewedFilm::setOpinion(QString opinion){
    _opinion=opinion;
}
void ViewedFilm::setRating(int rating){
    _rating=rating;
}

int ViewedFilm::getRating(){return _rating;}

QString ViewedFilm::getOpinion(){return _opinion;}
