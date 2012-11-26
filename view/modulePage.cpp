
void ModulesPage::createParamsPage(ModuleDescriptionRaw* module, ModuleData* moduleData, bool withParams)
{
    ParamsPage* paramsPage = new ParamsPage(module, moduleData, withParams);
    m_params[module] = paramsPage;

    QTreeWidgetItem* ti_paramsPage = m_projectTree->addTiWidget(module->name, m_paramsTreeElement);
    m_projectTree->addPage(ti_paramsPage, paramsPage);
}

void ModulesPage::deleteParamsPage(ModuleDescriptionRaw* module)
{
    // TODO: check if user change params
    ParamsPage* page = m_params[module];
    m_params.remove(module);

    m_projectTree->removePage(page);
}

void ModulesPage::createDependenciesPage(ModuleDescriptionRaw* module, ModuleData* moduleData, bool withDeps)
{
    DependenciesPage* page = new DependenciesPage(module, moduleData, withDeps);
    foreach(ModuleDescriptionRaw* module, m_enabledModules)
        page->moduleEnabled(module);

    m_dependencies[module] = page;

    QTreeWidgetItem* ti_page = m_projectTree->addTiWidget(module->name, m_dependenciesTreeElement);
    m_projectTree->addPage(ti_page, page);
}

void ModulesPage::deleteDependenciesPage(ModuleDescriptionRaw* module)
{
    // TODO: check if user change params
    DependenciesPage* page = m_dependencies[module];
    m_dependencies.remove(module);

    m_projectTree->removePage(page);
}


void ModulesPage::newModuleParam(ModuleData* moduleData, ModuleParam* param)
{
    ModuleDescriptionRaw* module = m_modulesPairs.key(moduleData);
    if (module) {
        ModuleParamRaw* paramRaw = NULL;
        for (int i = 0; i < module->params.size(); i++) {
            if (module->params[i].name == param->name) {
                paramRaw = &(module->params[i]);
                break;
            }
        }
        if (!paramRaw)
            return;

        ParamsPage* page = m_params[module];

        page->createParam(module, paramRaw, param);
    }
    else {
        // TODO: handle error
    }
}

void ModulesPage::newModuleDependence(ModuleData* moduleData, ModuleDependence* dependence)
{
    ModuleDescriptionRaw* module = m_modulesPairs.key(moduleData);
    if (module) {
        DependenciesPage* page = m_dependencies[module];
        page->createDependence(module, dependence);
    }
    else {
        // TODO: handle error
    }
}
