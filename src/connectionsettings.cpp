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
    
    connect(ui->connectBtn, SIGNAL(clicked()), this, SLOT(test()));
}

ConnectionSettings::~ConnectionSettings()
{
    delete ui;

}

void ConnectionSettings::updateStatus(char* status){
    ui->status->setText(status);
}

void ConnectionSettings::test(){
    ui->status->setText("Connecting...");
    //emit startCanThread(10000);
    emit joinCanNetwork();
}
