/**
 *
 * File: settings.h
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtGui>

namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    Settings();
    virtual ~Settings();

private slots:
    void buttonClicked(QAbstractButton *button);
    void browseDirectory();

    void showCurrentSettings();
    void saveSettings();
private:
    QString setRelativeDirectory(QString directory);

    Ui::Settings* m_ui;
};

#endif // SETTINGS_H
