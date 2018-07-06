#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QHash"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->horizontalSliderRating,SIGNAL(valueChanged(int)),ui->labelRating,SLOT(setNum(int)));
    createIcon();
    onOffReadOnly(false);
    onOffEnableRightZone(false);
    clearRigntZone();
}

MainWindow::~MainWindow()
{
}

 void MainWindow::addViewed(){
     std::map<QString,ViewedFilm>::iterator it;
     QString name=ui->lineEditNameFilm->text();
     if (name !=""){
         if(_viewed.find(name)==_viewed.end()){
    _viewed[ui->lineEditNameFilm->text()]=ViewedFilm(ui->comboBoxGenre->currentText(),
                                                     ui->comboBoxAge->currentText(),
                                                     ui->lineEditCountry->text(),
                                                     ui->dateEditRelease->date(),
                                                     ui->horizontalSliderRating->value(),
                                                     ui->textEditOpinion->toPlainText());
    ui->listWidgetViewed->addItem(ui->lineEditNameFilm->text());
    ui->listWidgetViewed->scrollToBottom();
    QApplication::processEvents();
    ui->statusBar->showMessage("Ready add");
     }else {
         ui->statusBar->showMessage("It's not possible to create, such a film already exists");
     }
     }else {
         ui->statusBar->showMessage("Missing movie title");
     }
}

 void MainWindow::addWatch(){
     std::map<QString,WatchFilm>::iterator it;
     QString name=ui->lineEditNameFilm->text();
     if (name !=""){
     if(_watch.find(name)==_watch.end()){
    _watch[ui->lineEditNameFilm->text()]=WatchFilm(ui->comboBoxGenre->currentText(),
                                                   ui->comboBoxAge->currentText(),
                                                   ui->lineEditCountry->text(),
                                                   ui->dateEditRelease->date());

    ui->listWidgeWatch->addItem(ui->lineEditNameFilm->text());
    ui->listWidgeWatch->scrollToBottom();
    QApplication::processEvents();
    ui->statusBar->showMessage("Ready add");
 }else {
     ui->statusBar->showMessage("It's not possible to create, such a film already exists");
 }
     }else {
              ui->statusBar->showMessage("Missing movie title");
          }

 }

 void MainWindow::transfer(){
     std::map<QString,ViewedFilm>::iterator it;
     QString name=ui->listWidgeWatch->item(ui->listWidgeWatch->currentRow())->text();
     if(_viewed.find(name)!=_viewed.end()){
         _watch.erase(name);
         ui->listWidgeWatch->removeItemWidget(ui->listWidgeWatch->takeItem(ui->listWidgeWatch->currentRow()));
         QApplication::processEvents();
         ui->statusBar->showMessage("This movie already exists in the views and has been removed from the to watch");
     }else{
     WatchFilm film=_watch[name];
     _viewed[name]=ViewedFilm(film.getGanre(),film.getAgeRaiting(),
                              film.getCountry(),film.getRelease(),
                              ui->horizontalSliderRating->value(),
                              ui->textEditOpinion->toPlainText());
     ui->listWidgetViewed->addItem(name);
     _watch.erase(name);
     ui->statusBar->showMessage("Ready transfer");
     ui->listWidgeWatch->removeItemWidget(ui->listWidgeWatch->takeItem(ui->listWidgeWatch->currentRow()));
     QApplication::processEvents();

    }
 }

void MainWindow::editWatch(){
     QString name=ui->listWidgeWatch->item(ui->listWidgeWatch->currentRow())->text();
     _watch[name].setAgeRaiting(ui->comboBoxAge->currentText());
     _watch[name].setCountry(ui->lineEditCountry->text());
     _watch[name].setGanre(ui->comboBoxGenre->currentText());
     _watch[name].setRelease(ui->dateEditRelease->date());
     if(name!=ui->lineEditNameFilm->text()){
        std::map<QString,WatchFilm>::iterator it;
        if(_watch.find(ui->lineEditNameFilm->text())==_watch.end()){
         _watch[ui->lineEditNameFilm->text()]=_watch[name];
         _watch.erase(name);
         ui->listWidgeWatch->addItem(ui->lineEditNameFilm->text());
         ui->listWidgeWatch->removeItemWidget(ui->listWidgeWatch->takeItem(ui->listWidgeWatch->currentRow()));
         ui->statusBar->showMessage("Ready edit");
         ui->listWidgeWatch->scrollToBottom();
         QApplication::processEvents();
        }else {
            ui->statusBar->showMessage("It is not possible to rename, such a film already exists");

        }
     }else{
         ui->statusBar->showMessage("Ready edit");
     }


 }
 void MainWindow::editViewed(){
     QString name=ui->listWidgetViewed->item(ui->listWidgetViewed->currentRow())->text();
     _viewed[name].setAgeRaiting(ui->comboBoxAge->currentText());
     _viewed[name].setCountry(ui->lineEditCountry->text());
     _viewed[name].setGanre(ui->comboBoxGenre->currentText());
     _viewed[name].setRelease(ui->dateEditRelease->date());
     _viewed[name].setRating(ui->horizontalSliderRating->value());
     _viewed[name].setOpinion(ui->textEditOpinion->toPlainText());
     if(name!=ui->lineEditNameFilm->text()){
         std::map<QString,ViewedFilm>::iterator it;
         if(_viewed.find(ui->lineEditNameFilm->text())==_viewed.end()){
         _viewed[ui->lineEditNameFilm->text()]=_viewed[name];
         _viewed.erase(name);
         ui->listWidgetViewed->addItem(ui->lineEditNameFilm->text());
         ui->listWidgetViewed->removeItemWidget(ui->listWidgetViewed->takeItem(ui->listWidgetViewed->currentRow()));
         ui->listWidgetViewed->scrollToBottom();
         ui->statusBar->showMessage("Ready edit");
         QApplication::processEvents();
     }else {
         ui->statusBar->showMessage("It is not possible to rename, such a film already exists");
     }
  }else{
      ui->statusBar->showMessage("Ready edit");
  }
}
 void MainWindow::deleteViewed(){
     QString name=ui->listWidgetViewed->item(ui->listWidgetViewed->currentRow())->text();
     _viewed.erase(name);
     ui->listWidgetViewed->removeItemWidget(ui->listWidgetViewed->takeItem(ui->listWidgetViewed->currentRow()));
     ui->listWidgetViewed->scrollToBottom();
     QApplication::processEvents();
     ui->statusBar->showMessage("Ready delete");
 }

 void MainWindow::deleteWatch(){
     QString name=ui->listWidgeWatch->item(ui->listWidgeWatch->currentRow())->text();
     _watch.erase(name);
     ui->listWidgeWatch->removeItemWidget(ui->listWidgeWatch->takeItem(ui->listWidgeWatch->currentRow()));
     ui->listWidgeWatch->scrollToBottom();
     QApplication::processEvents();
     ui->statusBar->showMessage("Ready delete");
 }

void MainWindow::createIcon(){
    QPixmap pixmap(":/new/prefix1/index.png");
    QIcon ButtonIcon(pixmap);
    ui->pushButtonNewWatch->setIcon(ButtonIcon);

    QPixmap pixmap2(":/new/prefix1/index.png");
    QIcon ButtonIcon2(pixmap2);
    ui->pushButtonNewViewed->setIcon(ButtonIcon2);

    QPixmap pixmap3(":/new/prefix1/circled-down.png");
    QIcon ButtonIcon3(pixmap3);
    ui->pushButtonViewedTransfer->setIcon(ButtonIcon3);

    QPixmap pixmap4(":/new/prefix1/delete-ticket.png");
    QIcon ButtonIcon4(pixmap4);
    ui->pushButtonDeleteWatch->setIcon(ButtonIcon4);

    QPixmap pixmap5(":/new/prefix1/delete-ticket.png");
    QIcon ButtonIcon5(pixmap5);
    ui->pushButtonDeleteViewed->setIcon(ButtonIcon5);


}
void MainWindow::onOffReadOnly(bool onOff){
    ui->lineEditNameFilm->setReadOnly(onOff);
    ui->lineEditCountry->setReadOnly(onOff);
    ui->dateEditRelease->setReadOnly(onOff);
    ui->textEditOpinion->setReadOnly(onOff);
    if(onOff){
        ui->label_genre->show();
        ui->label_Age->show();
        ui->comboBoxAge->hide();
        ui->comboBoxGenre->hide();
    }else{
        ui->label_genre->hide();
        ui->label_Age->hide();
        ui->comboBoxAge->show();
        ui->comboBoxGenre->show();
    }
}

void MainWindow::clearRigntZone(){
    ui->comboBoxGenre->setCurrentIndex(0);
    ui->lineEditNameFilm->clear();
    ui->lineEditCountry->clear();
    ui->dateEditRelease->clear();
    ui->comboBoxAge->setCurrentIndex(0);
    ui->horizontalSliderRating->setSliderPosition(6);
    ui->textEditOpinion->clear();
}

void MainWindow::onOffEnableRightZone(bool onOff){
    ui->labelMode->setText("Mode: expectation");
    ui->comboBoxGenre->setEnabled(onOff);
    ui->label_3->setEnabled(onOff);
    ui->lineEditNameFilm->setEnabled(onOff);
    ui->lineEditCountry->setEnabled(onOff);
    ui->label_4->setEnabled(onOff);
    ui->dateEditRelease->setEnabled(onOff);
    ui->comboBoxAge->setEnabled(onOff);
    ui->pushButtonAccept->setEnabled(onOff);
    ui->horizontalSliderRating->setEnabled(onOff);
    ui->label_8->setEnabled(onOff);
    ui->label_7->setEnabled(onOff);
    ui->textEditOpinion->setEnabled(onOff);
    ui->label_5->setEnabled(onOff);
    ui->labelRating->setEnabled(onOff);
    ui->label_Age->setEnabled(onOff);
    ui->label_genre->setEnabled(onOff);
    if (onOff){
        ui->pushButtonEdit->show();
        ui->pushButtonAccept->show();
    }else
    {
        ui->pushButtonEdit->hide();
        ui->pushButtonAccept->hide();
    }
}
void MainWindow::onOffViewedZone(bool onOff){

    ui->horizontalSliderRating->setEnabled(onOff);
    ui->label_8->setEnabled(onOff);
    ui->label_7->setEnabled(onOff);
    ui->textEditOpinion->setEnabled(onOff);
    ui->label_5->setEnabled(onOff);
    ui->labelRating->setEnabled(onOff);
}


void MainWindow::on_pushButtonAccept_clicked()
{

    general_switch<QString>(
        ui->pushButtonAccept->text(),
        {
                    {"Add a new \"to Watch\"", std::bind(&MainWindow::addWatch, this)},
                    {"Add a new \"Viewed\"",std::bind(&MainWindow::addViewed, this)},
                    {"Transfer",std::bind(&MainWindow::transfer, this)},
                    {"Accept changes \"to Watch\"",std::bind(&MainWindow::editWatch, this)},
                    {"Accept changes \"Viewed\" ",std::bind(&MainWindow::editViewed, this)},
                    {"Delete \"Viewed\"",std::bind(&MainWindow::deleteViewed, this)},
                    {"Delete \"to Watch\"",std::bind(&MainWindow::deleteWatch, this)}
        }
    );

    clearRigntZone();
    onOffEnableRightZone(false);
    onOffReadOnly(false);
    onOffViewedZone(false);
    ui->pushButtonEdit->hide();
    ui->pushButtonAccept->hide();
    ui->labelMode->setText("Mode: expectation");

}


void MainWindow::on_pushButtonNewWatch_clicked()
{
    clearRigntZone();
    onOffEnableRightZone(true);
    onOffViewedZone(false);
    onOffReadOnly(false);
    ui->labelMode->setText("Mode: Сreating a new \"to Watch\" ");
    ui->pushButtonAccept->setText("Add a new \"to Watch\"");
    ui->pushButtonEdit->hide();
}

void MainWindow::on_pushButtonNewViewed_clicked()
{
    clearRigntZone();
    onOffEnableRightZone(true);
    onOffReadOnly(false);
    ui->labelMode->setText("Mode: Сreating a new \"Viewed\" ");
    ui->pushButtonEdit->hide();
    ui->pushButtonAccept->setText("Add a new \"Viewed\"");
}


void MainWindow::on_pushButtonViewedTransfer_clicked()
{
    if ((ui->lineEditNameFilm->text())!=""){
   onOffEnableRightZone(false);
   onOffReadOnly(true);
   onOffViewedZone(true);
   ui->textEditOpinion->setReadOnly(false);
   ui->labelMode->setText("Mode: Transfer to \"Viewed\"");
   ui->label_3->setEnabled(false);
   ui->pushButtonAccept->show();
   ui->pushButtonAccept->setText("Transfer");
   ui->pushButtonAccept->setEnabled(true);
   ui->pushButtonEdit->hide();
    }else{
        ui->labelMode->setText("Mode: Error: No movie selected");
    }

}


void MainWindow::on_listWidgeWatch_clicked(const QModelIndex &index)
{
    clearRigntZone();
    onOffEnableRightZone(true);
    onOffViewedZone(false);
    onOffReadOnly(true);
    ui->labelMode->setText("Mode: More info \"to Watch\" ");
    ui->pushButtonAccept->hide();
    ui->pushButtonEdit->show();
    ui->pushButtonEdit->setText("Edit \"to Watch\"");

    QString keyFilm=ui->listWidgeWatch->item(ui->listWidgeWatch->currentRow())->text();
    WatchFilm film =_watch[keyFilm];
    ui->lineEditNameFilm->setText(keyFilm);
    ui->lineEditCountry->setText(film.getCountry());
    ui->comboBoxGenre->setCurrentIndex(ui->comboBoxGenre->findText(film.getGanre()));
    ui->comboBoxAge->setCurrentIndex(ui->comboBoxAge->findText(film.getAgeRaiting()));
    ui->dateEditRelease->setDate(film.getRelease());
    ui->label_Age->setText("Age rating:       "+film.getAgeRaiting());
    ui->label_genre->setText("Genre:              "+film.getGanre());
}

void MainWindow::on_pushButtonEdit_clicked()
{
    ui->pushButtonAccept->show();
    ui->pushButtonAccept->setEnabled(true);
    onOffReadOnly(false);
    ui->pushButtonEdit->hide();

    if(ui->pushButtonEdit->text()=="Edit \"to Watch\""){
        ui->pushButtonAccept->setText("Accept changes \"to Watch\"");
        ui->labelMode->setText("Mode:Edit \"to Watch\" ");
    }else {
        ui->pushButtonAccept->setText("Accept changes \"Viewed\" ");
        ui->horizontalSliderRating->setEnabled(true);
        ui->labelMode->setText("Mode:Edit \"Viewed\"");
    }

}

void MainWindow::on_listWidgetViewed_clicked(const QModelIndex &index)
{
    clearRigntZone();
    onOffEnableRightZone(true);
    onOffReadOnly(true);
    ui->labelMode->setText("Mode: More info \"Viewed\" ");
    ui->pushButtonAccept->hide();
    ui->pushButtonEdit->show();
    ui->pushButtonEdit->setText("Edit \"Viewed\"");

    QString keyFilm=ui->listWidgetViewed->item(ui->listWidgetViewed->currentRow())->text();
    ViewedFilm film =_viewed[keyFilm];
    ui->lineEditNameFilm->setText(keyFilm);
    ui->lineEditCountry->setText(film.getCountry());
    ui->dateEditRelease->setDate(film.getRelease());
    ui->label_Age->setText(film.getAgeRaiting());
    ui->comboBoxGenre->setCurrentIndex(ui->comboBoxGenre->findText(film.getGanre()));
    qDebug()<<ui->comboBoxGenre->findText(film.getGanre());
    ui->comboBoxAge->setCurrentIndex(ui->comboBoxAge->findText(film.getAgeRaiting()));
    ui->label_genre->setText(film.getGanre());
    ui->horizontalSliderRating->setSliderPosition(film.getRating());
    ui->textEditOpinion->setText(film.getOpinion());
    ui->horizontalSliderRating->setEnabled(false);

}

void MainWindow::on_pushButtonDeleteWatch_clicked()
{
    if ((ui->lineEditNameFilm->text())!=""){
    ui->pushButtonEdit->hide();
    ui->pushButtonAccept->show();
    ui->labelMode->setText("Mode:Delete");
    ui->pushButtonAccept->setText("Delete \"to Watch\"");
    ui->pushButtonAccept->setEnabled(true);
    }else{
       ui->labelMode->setText("Mode: Error: No movie selected");
    }
}

void MainWindow::on_pushButtonDeleteViewed_clicked()
{
    if ((ui->lineEditNameFilm->text())!=""){
    ui->pushButtonEdit->hide();
    ui->pushButtonAccept->show();
    ui->labelMode->setText("Mode:Delete");
    ui->pushButtonAccept->setText("Delete \"Viewed\"");
    ui->pushButtonAccept->setEnabled(true);
    }else{
       ui->labelMode->setText("Mode: Error: No movie selected");
    }
}
