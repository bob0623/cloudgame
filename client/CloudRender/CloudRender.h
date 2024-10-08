#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CloudRender.h"

class CloudRender : public QMainWindow
{
    Q_OBJECT

public:
    CloudRender(QWidget *parent = nullptr);
    ~CloudRender();

private:
    Ui::CloudRenderClass ui;
};
