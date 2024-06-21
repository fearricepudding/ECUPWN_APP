#ifndef SPLASH_H
#define SPLASH_H

#include <QMainWindow>
#include "canworker.h"
#include "connectionsettings.h"

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
    void connect_settings();
    void connection_thread(int);

public:
    Splash(QWidget *parent = nullptr);
    ~Splash();

private:
    Ui::Splash *ui;
    QThread *thread;
    /**
     * @brief Object which contains methods that should be runned in another thread
     */
    CanWorker *worker; 

};
#endif // SPLASH_H
