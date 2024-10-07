#pragma once

#include <QDialog>

namespace Ui {
class ExistingConnection;
}

class ExistingConnection : public QDialog
{
    Q_OBJECT
private slots:

signals:

public:
    explicit ExistingConnection(QWidget *parent = nullptr);
    ~ExistingConnection();
    void updateStatus(char*);

private:
    Ui::ExistingConnection *ui;
};


