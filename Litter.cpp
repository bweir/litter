#include "Litter.h"

#include "ui_Litter.h"

#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QProcess>
#include <QTextStream>
#include <QTextDocumentWriter>

Litter::Litter(QWidget *parent): QMainWindow(parent)
{
    Ui::Litter ui;
    ui.setupUi(this);

    editor = new LitEditor();
    setCentralWidget(editor);

    connect(editor->ui.litEdit,SIGNAL(textChanged()),this,SLOT(textChanged()));
    connect(ui.actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui.actionSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui.actionAs,SIGNAL(triggered()),this,SLOT(saveAs()));
    connect(ui.actionNew,SIGNAL(triggered()),this,SLOT(newFile()));

    newFile();
}

Litter::~Litter()
{
    delete editor;
}

void Litter::writeFile(const QString & text, const QString & name)
{
    QFile file(name);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << text;
    }
}

void Litter::open()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Open file..."),
            QString(), tr("Lit files (*.lit);;All Files (*)"));
    if (!fn.isEmpty())
        openFile(fn);
}

void Litter::openFile(const QString & name)
{
    updateFilename(name);

    QFile lit(filename);
    lit.open(QIODevice::ReadOnly);
    editor->ui.litEdit->setPlainText(lit.readAll());
    lit.close();

    updateView();
}

void Litter::updateView()
{
    QFileInfo fi(tmpfile);
    QString codename = fi.completeBaseName();
    QString docname = codename + ".html";

    QFile code(codename);
    QFile doc(docname);

    code.open(QIODevice::ReadOnly);
    doc.open(QIODevice::ReadOnly);

    editor->ui.codeEdit->setPlainText(code.readAll());
    editor->ui.docEdit->setHtml(doc.readAll());

    code.close();
    doc.close();

    editor->ui.codeFile->setText(codename);
    editor->ui.docFile->setText(docname);
}

void Litter::save()
{
    if (filename.isEmpty())
        saveAs();
    else
        saveFile(filename);
}

void Litter::saveAs()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Save as..."),
            QString(), tr("Lit files (*.lit);;All Files (*)"));

    if (fn.isEmpty())
        return;

    updateFilename(fn);
    updateView();
    saveFile(fn);
}

void Litter::saveFile(const QString & name)
{
    writeFile(editor->ui.litEdit->toPlainText(), name);
    qDebug() << "SAVE" << name;
}

void Litter::updateFilename(const QString & name)
{
    this->filename = name;
    QFileInfo fi(filename);
    QString base = fi.fileName();
    QDir dir = fi.dir();
    tmpfile = dir.filePath("."+base);

    setWindowFilePath(filename);
    editor->ui.litFile->setText(fi.fileName());
    qDebug() << "FILENAME" << fi.fileName();
}

void Litter::newFile()
{
    updateFilename("Untitled.spin.lit");
    editor->ui.litEdit->clear();
    updateView();
}

void Litter::textChanged()
{
    writeFile(editor->ui.litEdit->toPlainText(), tmpfile);
    QProcess * proc = new QProcess();
    proc->start("lit",QStringList() << "-c" << "-h" << tmpfile);
    proc->waitForFinished();
    updateView();
}
