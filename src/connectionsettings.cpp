#include "connectionsettings.h"
#include "../ui/ui_connectionsettings.h"
#include "../candy/src/candy.h"
#include <iostream>
#include <QThread>

ConnectionSettings::ConnectionSettings()
    : QDialog(nullptr)
    , ui(new Ui::ConnectionSettings)
{
    ui->setupUi(this);
    
    connect(ui->connectBtn, SIGNAL(clicked()), this, SLOT(createConnection()));
}

ConnectionSettings::~ConnectionSettings()
{
    delete ui;

}

void ConnectionSettings::updateStatus(char* status){
}

void ConnectionSettings::createConnection(){
    std::string name = ui->name->text().toStdString();
    std::string ip = ui->ip->text().toStdString();
    std::string port = ui->port->text().toStdString();
    emit(createConnection(name, ip, port));
}
