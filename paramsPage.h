#ifndef PARAMSPAGE_H
#define PARAMSPAGE_H

#include <QGroupBox>
#include <QMap>
#include <QString>
#include <QLineEdit>

#include "projectParams.h"

namespace Ui {
    class ParamsPage;
}

class ParamsPage : public QGroupBox
{
    Q_OBJECT

public:
    ParamsPage();
    void setParams(QMap<QString, QString> params, QString name);
    virtual ~ParamsPage();

    ModuleParams getParams();
    void setParams(QList<ModuleParam> params);
    
private:
    QString m_name;
    QMap<QString, QLineEdit*> m_widgets;
    QMap<QString, QString> m_paramsTypes;
    Ui::ParamsPage *m_ui;
};

#endif // PARAMSPAGE_H
