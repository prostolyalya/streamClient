#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H
#pragma once

#include <QObject>
#include <qqml.h>

class UiController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uiText READ getText WRITE setText NOTIFY textServerChanged)
    Q_PROPERTY(QStringList uiListFiles READ getListFiles WRITE setListFiles NOTIFY listFilesChanged)
public:
    UiController(QObject* parent = nullptr);
    ~UiController();

    QString getText() const;

    void setText(const QString& value);

    QStringList getListFiles() const;

    void setListFiles(const QStringList &value);
    QString getFileName(int index);
    int getFilesSize() const;
public slots:
    void addText(QString text);
    void responceFileList(QStringList list);
signals:
    void textServerChanged();
    void listFilesChanged();
    void sendTextAllUsers(QString text);
    void sendText(QString text);
    void sendFile(QString path);
    void requestFile(QString fileName);
    void requestFileList();
    void init(QString login, QString pass);
private:
    QString textServer;
    QStringList listFiles {"Downloading..."};
};

#endif // UI_CONTROLLER_H
