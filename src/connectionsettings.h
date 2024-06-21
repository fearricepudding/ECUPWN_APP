#ifndef CONNECTIONSETTINGS_H
#define CONNECTIONSETTINGS_H

#include <QDialog>
#include "canworker.h"

namespace Ui {
class ConnectionSettings;
}

class ConnectionSettings : public QDialog
{
    Q_OBJECT
private slots:
    void test();

signals:
    void startCanThread(int);

public:
    explicit ConnectionSettings(QWidget *parent = nullptr);
    ~ConnectionSettings();

private:
    Ui::ConnectionSettings *ui;
};

#endif // CONNECTIONSETTINGS_H
