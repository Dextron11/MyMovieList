#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPixmap>
#include <QMainWindow>
#include<QDebug>
#include <QMap>
#include "viewedfilm.h"
#include "watchfilm.h"
#include <functional>
#include <initializer_list>
#include <iostream>
#include <algorithm>

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButtonAccept_clicked();

    void on_pushButtonNewWatch_clicked();

    void on_pushButtonNewViewed_clicked();

    void on_pushButtonViewedTransfer_clicked();

    void on_listWidgeWatch_clicked(const QModelIndex &index);

    void on_pushButtonEdit_clicked();

    void on_listWidgetViewed_clicked(const QModelIndex &index);


    void on_pushButtonDeleteWatch_clicked();

    void on_pushButtonDeleteViewed_clicked();

private:
    Ui::MainWindow *ui;

    void onOffReadOnly(bool onOff);

    void clearRigntZone();

    void onOffEnableRightZone(bool onOff);

    void onOffViewedZone(bool onOff);

    void createIcon();

    void addWatch();

    void addViewed();

    void transfer();

    void editWatch();

    void editViewed();

    void deleteWatch();

    void deleteViewed();

    std::map<QString,WatchFilm> _watch;

    std::map<QString,ViewedFilm> _viewed;
};

template<typename T>

inline void general_switch(T&& target, std::initializer_list<std::pair<T,std::function<void(void)>>>&& list){
    auto iter = std::find_if(list.begin(), list.end(), [&](const auto& item){return item.first == target;});
    iter->second.operator()();
}



#endif // MAINWINDOW_H
