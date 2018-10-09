#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);

    QStandardItemModel *model = new QStandardItemModel;
    this->urlList->setModel(model);
    
    QStringList list;
    list << "www.baidu.com" << "www.google.com";
    foreach(const QString &s , list)
    {
        auto item = new QStandardItem(QIcon(":/images/link.png"), s);
        item->setCheckable(true);
        item->setData(LINK);
        model->appendRow(item);
    }

    QStringList list1;
    list1 << "www.xxx.com" << "www.jjj.com";
    foreach(const QString &s , list1)
    {
        auto item = new QStandardItem(QIcon(":/images/image.png"), s);
        item->setCheckable(true);
        item->setData(IMAGE);
        model->appendRow(item);
    }

    QStringList list2;
    list2 << "www.xxx.com" << "www.jjj.com";
    foreach(const QString &s , list2)
    {
        auto item = new QStandardItem(QIcon(":/images/video.png"), s);
        item->setCheckable(true);
        item->setData(VIDEO);
        model->appendRow(item);
    }

    QStringList list3;
    list3 << "www.xxx.com" << "www.jjj.com";
    foreach(const QString &s , list3)
    {
        auto item = new QStandardItem(QIcon(":/images/text.png"), s);
        item->setCheckable(true);
        item->setData(TEXT);
        model->appendRow(item);
    }

    QStringList list4;
    list4 << "www.xxx.com" << "www.jjj.com";
    foreach(const QString &s , list4)
    {
        auto item = new QStandardItem(QIcon(":/images/music.png"), s);
        item->setCheckable(true);
        item->setData(MUSIC);
        model->appendRow(item);
    }
    
    connect(model, &QStandardItemModel::itemChanged, [this, model](QStandardItem *item)
    {
       const QModelIndex index = model->indexFromItem(item);
       QItemSelectionModel *selModel = this->urlList->selectionModel();
       selModel->select(QItemSelection(index, index), item->checkState() == Qt::Checked ? QItemSelectionModel::Select : QItemSelectionModel::Deselect);
    });

    connect(this->urlList->selectionModel(), &QItemSelectionModel::selectionChanged, [model](const QItemSelection &selected, const QItemSelection &deselected)
    {
        for(const QModelIndex &index : selected.indexes())
        {
            model->itemFromIndex(index)->setCheckState(Qt::Checked);
        }
        for(const QModelIndex &index : deselected.indexes())
        {
            model->itemFromIndex(index)->setCheckState(Qt::Unchecked);
        }
    });

    connect(this->fetchBtn, &QPushButton::clicked, [model]()
    {
        QStringList list4;
        list4 << "www.unknown.com" << "www.unknown.cn";
        foreach(const QString &s , list4)
        {
            auto item = new QStandardItem(QIcon(":/images/music.png"), s);
            item->setCheckable(true);
            item->setData(15);
            model->appendRow(item);
        }
    });


}

void MainWindow::on_sel_all_toggled(bool checked)
{
    if(checked)
        this->urlList->selectAll();
    else
    {
        QStandardItemModel *model = dynamic_cast<QStandardItemModel *>(this->urlList->model());
        for(int r = 0; r < model->rowCount(); ++r)
        {
            QModelIndex index = model->index(r, 0);
            QStandardItem *item = model->itemFromIndex(index);
            item->setCheckState(Qt::Unchecked);
        }
    }
}

void MainWindow::on_sel_music_toggled(bool checked)
{
    QStandardItemModel *model = dynamic_cast<QStandardItemModel *>(this->urlList->model());
    for(int r = 0; r < model->rowCount(); ++r)
    {
        QModelIndex index = model->index(r, 0);
        QStandardItem *item = model->itemFromIndex(index);
        Type t = qvariant_cast<Type>(item->data());
        if(t == MUSIC)
        {
            if(checked)
            {
                item->setCheckState(Qt::Checked);
            }
            else
            {
                item->setCheckState(Qt::Unchecked);
            }
        }
    }
}