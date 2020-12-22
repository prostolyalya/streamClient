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

QString UiController::getText() const
{
    return textServer;
}

void UiController::setText(const QString &value)
{
    textServer = value;
}

