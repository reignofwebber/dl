#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}
