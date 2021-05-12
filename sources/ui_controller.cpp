#include "ui_controller.h"

UiController::UiController(QObject *parent)
    : QObject(parent)
{
}

UiController::~UiController()
{
}

void UiController::addText(QString text)
{
    textServer += text + '\n';
    emit textServerChanged();
}

void UiController::responceFileList(QStringList list, QStringList listPub)
{
    listFiles.clear();
    listFiles = list;
    emit listFilesChanged();

    listPublicFiles.clear();
    listPublicFiles = listPub;
    emit listPublicFilesChanged();
}

void UiController::registrationComplete()
{
    errorText = "y";
    emit errorTextChanged();
}

void UiController::loginError(QString error)
{
    errorText = error;
    emit errorTextChanged();
}

void UiController::fileReceived(QString path)
{
    setVideoFilePath(path);
}

QString UiController::getVideoFilePath() const
{
    return videoFilePath;
}

void UiController::setVideoFilePath(const QString &value)
{
    videoFilePath = value;
    emit playerFilePathChanged();
}

QStringList UiController::getListPublicFiles() const
{
    return listPublicFiles;
}

void UiController::setListPublicFiles(const QStringList &value)
{
    listPublicFiles = value;
}

QString UiController::getErrorText() const
{
    return errorText;
}

void UiController::setErrorText(const QString &value)
{
    errorText = value;
}

QString UiController::getText() const
{
    return textServer;
}

void UiController::setText(const QString &value)
{
    textServer = value;
}

QStringList UiController::getListFiles() const
{
    return listFiles;
}

void UiController::setListFiles(const QStringList &value)
{
    listFiles = value;
}

QString UiController::getFileName(int index)
{
    return listFiles.at(index);
}

int UiController::getFilesSize() const
{
    return listFiles.size();
}
