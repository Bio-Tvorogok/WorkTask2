#ifndef CONTEXT_MENU_H
#define CONTEXT_MENU_H

#include<QtGui>
#include<QMenu>
#include<QTextEdit>

class Context_Menu : public QTextEdit
{
    Q_OBJECT

private:
    QMenu* menu;

public:
    Context_Menu();
};

#endif // CONTEXT_MENU_H
