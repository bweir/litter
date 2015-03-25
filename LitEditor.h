#pragma once

#include <QWidget>
#include <QDebug>
#include <QColor>
#include <Qt>

#include "ui_LitEditor.h"

class LitEditor : public QWidget
{
    Q_OBJECT
public:
    explicit LitEditor(QWidget *parent = 0);

    Ui::LitEditor ui;
};

