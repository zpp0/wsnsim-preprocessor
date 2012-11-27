/**
 *
 * File: settings.cpp
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#include "settings.h"
#include "ui_settings.h"

Settings::Settings()
    :m_ui(new Ui::Settings)
{
    m_ui->setupUi(this);

    showCurrentSettings();

    connect(m_ui->b_browse, SIGNAL(clicked()),
            this, SLOT(browseDirectory()));

    connect(this, SIGNAL(accepted()),
            this, SLOT(saveSettings()));

    connect(m_ui->buttonBox, SIGNAL(clicked(QAbstractButton*)),
            this, SLOT(buttonClicked(QAbstractButton*)));
}

Settings::~Settings()
{
    delete m_ui;
}

QString Settings::setRelativeDirectory(QString directory)
{
    return ("/" + QDir::current().relativeFilePath(directory) + "/");
}

void Settings::showCurrentSettings()
{
    QString directory = QSettings().value("Modules/Directory").toString();
    m_ui->le_directory->setText(directory);
}

void Settings::saveSettings()
{
    QString directory = m_ui->le_directory->text();

    QSettings().setValue("Modules/Directory", directory);
}

void Settings::buttonClicked(QAbstractButton *button)
{
    if(m_ui->buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole)
        done(QDialog::Accepted);

    else if(m_ui->buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
        done(QDialog::Rejected);
}

void Settings::browseDirectory()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                          QDir::currentPath(),
                                                          QFileDialog::ShowDirsOnly);
    directory = setRelativeDirectory(directory);

    m_ui->le_directory->setText(directory);
}
