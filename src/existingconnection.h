#pragma once

#include <QDialog>
#include "../include/json.hpp"

namespace Ui {
class ExistingConnection;
}

class ExistingConnection : public QDialog
{
    Q_OBJECT
private slots:
    void updateConnectionData(nlohmann::json);

signals:

public:
    explicit ExistingConnection(QWidget *parent = nullptr);
    ~ExistingConnection();
    void updateStatus(char*);

private:
    Ui::ExistingConnection *ui;
};
