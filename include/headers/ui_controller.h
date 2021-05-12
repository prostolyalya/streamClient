#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H
#pragma once

#include <QObject>
#include <qqml.h>

class UiController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uiText READ getText WRITE setText NOTIFY textServerChanged)
    Q_PROPERTY(QString playerFilePath READ getVideoFilePath NOTIFY playerFilePathChanged)
    Q_PROPERTY(
        QString uiError READ getErrorText WRITE setErrorText NOTIFY errorTextChanged)
    Q_PROPERTY(QStringList uiListFiles READ getListFiles WRITE setListFiles NOTIFY
                   listFilesChanged)
    Q_PROPERTY(QStringList uiListPublicFiles READ getListPublicFiles WRITE
                   setListPublicFiles NOTIFY listPublicFilesChanged)
public:
    UiController(QObject *parent = nullptr);
    ~UiController();

    QString getText() const;

    void setText(const QString &value);

    QStringList getListFiles() const;

    void setListFiles(const QStringList &value);
    QString getFileName(int index);
    int getFilesSize() const;
    QString getErrorText() const;
    void setErrorText(const QString &value);

    QStringList getListPublicFiles() const;
    void setListPublicFiles(const QStringList &value);

    QString getVideoFilePath() const;
    void setVideoFilePath(const QString &value);

public slots:
    void addText(QString text);
    void responceFileList(QStringList list, QStringList listPub);
    void registrationComplete();
    void loginError(QString error);
    void fileReceived(QString path);

signals:
    void playerFilePathChanged();
    void textServerChanged();
    void errorTextChanged();
    void listFilesChanged();
    void listPublicFilesChanged();
    void sendTextAllUsers(QString text);
    void sendText(QString text);
    void sendFile(QString path, bool isPrivate);
    void requestFile(QString fileName);
    void requestFileList();
    void init(QString login, QString pass);
    void login(QString login, QString pass);
    void registration(QString login, QString pass);

private:
    QString textServer;
    QString videoFilePath;
    QString errorText = "";
    QStringList listFiles { "Downloading..." };
    QStringList listPublicFiles { "Downloading..." };
};

#endif // UI_CONTROLLER_H
