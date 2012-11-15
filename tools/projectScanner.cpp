    // QDir myDir(QDir::currentPath());
    // QStringList projectLib = myDir.entryList(QStringList() << "*projectData.so" << "*projectData.dll");
    // // QStringList projectLib = myDir.entryList(QStringList() << "*.so" << "*.dll");

    // QLibrary projectDataLib(QDir::currentPath() + "/" + projectLib[0]);
    // // QLibrary projectDataLib("./libprojectData");
    // projectDataLib.load();

    // if(!projectDataLib.isLoaded()) {
    //     // TODO: throw good exception
    //     qDebug() << "Error load library";
    //     throw;
    //     // return projectParams;
    // }

    // // FIXME: make it easy
    // typedef ProjectParams(*projectDataLoad) (QString& projectFileName, QString* errorMessage);
    // projectDataLoad pd = (projectDataLoad) projectDataLib.resolve("load");

    // QString errorMessage;
    // QString projectFile;

    // ProjectParams projectParams = pd(m_projectFileName, &errorMessage);

    // m_simulatorParams->setParams(projectParams.simulatorParams);
    // m_project->setParams(projectParams.projectInfo);
    // foreach(ModuleParams moduleParams, projectParams.modulesParams)
    //     m_paramsPages[moduleParams.moduleName]->setParams(moduleParams.params);

    // m_logs.erase(m_logs.begin(), m_logs.end());

    // foreach(LogFileInfo logInfo, projectParams.logFiles)
    //     m_logs += logInfo["name"];
