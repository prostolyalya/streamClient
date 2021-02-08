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

void UiController::responceFileList(QStringList list)
{
    listFiles.clear();
    list.removeAt(0);
    listFiles = list;
    emit listFilesChanged();
}

void UiController::registrationComplete()
{

}

void UiController::loginError()
{
    errorText = "X";
    emit errorTextChanged();
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

