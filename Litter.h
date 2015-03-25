#pragma once

#include <QWidget>
#include <QDebug>
#include <QColor>
#include <Qt>
#include <QMainWindow>
#include <QString>

#include "LitEditor.h"

class Litter : public QMainWindow
{
    Q_OBJECT

private:
    LitEditor * editor;
    QString filename;
    QString tmpfile;

public:
    explicit Litter(QWidget *parent = 0);
    ~Litter();

    void writeFile(const QString & text, const QString & name);
    void openFile(const QString & name);
    void saveFile(const QString & name);

public slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void updateView();
    void updateFilename(const QString & name);
    void textChanged();
};

