#include "myqmdiarea.h"

MyQmdiArea *MyQmdiArea::pInstance = 0;

MyQmdiArea::MyQmdiArea(QWidget *parent) : QMdiArea(parent)
{

}

MyQmdiArea *MyQmdiArea::Instance(QWidget *parent){
    if (pInstance == 0){
        pInstance = new MyQmdiArea(parent);
        //atexit(&DestroyMe);
    }

    return pInstance;
}
