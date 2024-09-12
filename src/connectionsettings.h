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
    void startConnect();

signals:
    void joinCanNetwork();

public:
    explicit ConnectionSettings(QWidget *parent = nullptr);
    ~ConnectionSettings();
    void updateStatus(char*);

private:
    Ui::ConnectionSettings *ui;
};

#endif // CONNECTIONSETTINGS_H
