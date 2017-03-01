#include "myqlineedit.h"

#include <QMouseEvent>

myQLineEdit::myQLineEdit(QWidget *parent)
{

}

void myQLineEdit::mouseReleaseEvent(QMouseEvent *e)
{
 if (e->MouseButtonDblClick) {
     emit(dobleclick());
 }
}
