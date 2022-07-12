#include "QmlLanguage.h"
//#include <QDebug>

QmlLanguage::QmlLanguage(QGuiApplication &app, QQmlApplicationEngine& engine)
{
    m_app = &app;
    m_engine = &engine;
}

void QmlLanguage::setLanguage(QString languageId)
{
    QTranslator translator;

    QFile config("config/UserDefine.json");
    config.open(QIODevice::ReadOnly);
    QJsonDocument qDoc = QJsonDocument::fromJson(config.readAll());
    config.close();
    QJsonArray qjsonArray = (qDoc.object().value("settings")).toArray();
    QJsonArray langConfig;
    foreach(QJsonValue item , qjsonArray)
    {
        if(item.toObject().value("sectionId").toString() == "language")
        {
            langConfig = item.\
                    toObject().value("method").\
                    toObject().value("page_data").\
                    toObject().value("language").\
                    toArray();
            break;
        }
    }

    if(langConfig.count() == 0)
        return;


    foreach(QJsonValue item , langConfig)
    {
        if(item.toObject().value("lang_id").toString() == languageId)
        {
            QString fileName;
            fileName = item.\
                    toObject().value("file_name").\
                    toString();

            translator.load("language/"+fileName+".qm");

            m_app->installTranslator(&translator);
            m_engine->retranslate();
            break;
        }
    }

//    if (nLanguage == 0)
//    {
//        translator.load(":/en_US.qm");
//    }else{
//        translator.load(":/zh_CN.qm");
//    }
//    m_app->installTranslator(&translator);
//    m_engine->retranslate();
}
