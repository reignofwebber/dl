#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtWidgets>

#include "ui_settings_dialog.h"

class SettingsDialog : public QDialog, public Ui::SettingsDialog
{
public:
    SettingsDialog(QWidget *parent = 0);
};

#endif // SETTINGSDIALOG_H
