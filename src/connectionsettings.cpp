#include "connectionsettings.h"
#include "../ui/ui_connectionsettings.h"
#include "../candy/src/candy.h"
#include <iostream>
#include <QThread>

ConnectionSettings::ConnectionSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectionSettings)
{
    ui->setupUi(this);
    
    connect(ui->test, SIGNAL(clicked()), this, SLOT(test()));
}

ConnectionSettings::~ConnectionSettings()
{
    delete ui;

}

void ConnectionSettings::test(){
    emit startCanThread(10000);
}
