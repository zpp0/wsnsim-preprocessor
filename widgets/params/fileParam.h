/**
 *
 * File: fileParam.h
 * Description: module param with file type
 * Author: Alexander Yarygin <yarygin.alexander@gmail.com>
 *
 **/

#ifndef FILEPARAM_H
#define FILEPARAM_H

#include "generalParam.h"

namespace Ui {
    class FileParam;
}

class ModuleParamFile : protected ModuleParamGeneral
{
    Q_OBJECT

public:
    ModuleParamFile(ModuleDescriptionRaw* module, ModuleParamRaw* paramRaw);
    virtual ~ModuleParamFile();

    void setParam(ModuleParam param);
    ModuleParam getParam();

protected:
    Ui::FileParam *m_ui;

private slots:
    void browseFile();
};

#endif // FILEPARAM_H
