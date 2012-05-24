#include "paramsPage.h"
#include "ui_paramsPage.h"

#include <QLabel>
#include <QLineEdit>

ParamsPage::ParamsPage () :
    m_ui(new Ui::ParamsPage)
{
    m_ui->setupUi (this);
}

void ParamsPage::setParams(QMap<QString, QString> params, QString name)
{
    m_name = name;
    setTitle(name);

    foreach(QString param, params.keys()) {
        QLabel* label = new QLabel(param);
        QLineEdit* paramProvider = new QLineEdit();
        
        m_widgets[param] = paramProvider;
        
        m_paramsTypes[param] = params[param];
            
        m_ui->formLayout->addRow(label, paramProvider);
    }
}

ParamsPage::~ParamsPage ()
{
    delete m_ui;
}

ModuleParams ParamsPage::getParams()
{
    ModuleParams params;
    params.moduleName = m_name;

    foreach(QString param, m_widgets.keys()) {
        ModuleParam moduleParam;
        moduleParam.name = param;
        moduleParam.type = m_paramsTypes[param];
        moduleParam.value = m_widgets[param]->text();
        params.params += moduleParam;
    }
    
    // возвращаем результат
    return params;
}

void ParamsPage::setParams(QList<ModuleParam> params)
{
    foreach(QLineEdit* le, m_widgets.values())
        le->clear();

    foreach(ModuleParam param, params)
        m_widgets[param.name]->setText(param.value);
}
