#include "userinputfilter.h"
#include "common/unused.h"
#include "common/lazytrigger.h"
#include <QTimer>
#include <QLineEdit>

UserInputFilter::UserInputFilter(QLineEdit* lineEdit, QObject* filterHandler, const char* handlerSlot) :
    QObject(lineEdit),
    lineEdit(lineEdit)
{
    trigger = new LazyTrigger(200, this);
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(filterModified()));
    connect(trigger, SIGNAL(triggered()), this, SLOT(applyFilter()));
    connect(this, SIGNAL(applyFilter(QString)), filterHandler, handlerSlot);
}

void UserInputFilter::setDelay(int msecs)
{
    trigger->setDelay(msecs);
}

void UserInputFilter::filterModified()
{
    trigger->schedule();
}

void UserInputFilter::applyFilter()
{
    emit applyFilter(lineEdit->text());
}
