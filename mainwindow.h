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
    void onSelToggled(bool checked);

private:

};

#endif // MAINWINDOW_H
