//#ifndef QMLLANGUAGE_H
//#define QMLLANGUAGE_H
#pragma once
#include <QObject>
#include <QTranslator>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QVariant>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>

class QmlLanguage : public QObject
{
    Q_OBJECT
public:
    QmlLanguage(QGuiApplication& app, QQmlApplicationEngine &engine);

    Q_INVOKABLE void setLanguage(QString languageId);

private:
    QGuiApplication *m_app;
    QQmlApplicationEngine *m_engine;
};
//#endif // QMLLANGUAGE_H
