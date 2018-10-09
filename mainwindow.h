#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include "ui_mainwindow.h"

enum Type
{
    LINK,
    TEXT,
    IMAGE,
    MUSIC,
    VIDEO
};
Q_DECLARE_METATYPE(Type)

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:





    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:

private slots:
    void on_sel_all_toggled(bool checked);

    void on_sel_music_toggled(bool checked);

private:

};

#endif // MAINWINDOW_H
