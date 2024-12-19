#ifndef CONNECTIONSETTINGS_H
#define CONNECTIONSETTINGS_H

#include <QDialog>

namespace Ui {
class ConnectionSettings;
}

class ConnectionSettings : public QDialog
{
    Q_OBJECT
private slots:
    void createConnection();

signals:
    void createConnection(std::string, std::string);

public:
    explicit ConnectionSettings();
    ~ConnectionSettings();
    void updateStatus(char*);

private:
    Ui::ConnectionSettings *ui;
};

#endif // CONNECTIONSETTINGS_H
