#ifndef SPLASH_H
#define SPLASH_H

#include <QMainWindow>
#include "canworker.h"
#include "connectionsettings.h"
#include "CanQueue.h"
#include "ConnectionManager.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class Splash;
}
QT_END_NAMESPACE

class Splash : public QMainWindow
{
    Q_OBJECT

private slots:
    void exit_app();
    void lookup_code();
    void can_logger();
    void treeItemClicked();

public:
    Splash(QWidget *parent = nullptr);
    ~Splash();

private:
    Ui::Splash *ui;
    void setupPages();
    void addPage(std::string, int);
    CanQueue _canQueue;
    ConnectionManager *conManager;
};
#endif // SPLASH_H
