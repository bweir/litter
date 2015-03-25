#include "LitEditor.h"

#include <QFontMetrics>

LitEditor::LitEditor(QWidget *parent): QWidget(parent)
{
    ui.setupUi(this);

    const int tabStop = 4;
    QFontMetrics metrics(ui.litEdit->font());
    ui.litEdit->setTabStopWidth(tabStop * metrics.width(' '));


    ui.docEdit->document()->setDefaultStyleSheet(
        "body { margin: auto; }"
        "h1,h2 { color: #007FFF; }"
        "table {border-collapse:collapse; border:1px solid black;}"
        "pre {white-space: pre-wrap; word-wrap: break-word;}"
    );
}
