#include "existingconnection.h"
#include "../ui/ui_existingconnection.h"
#include "../candy/src/candy.h"
#include "../include/json.hpp"

#include <iostream>
#include <QThread>

ExistingConnection::ExistingConnection(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExistingConnection)
{
    ui->setupUi(this);
    connect(ui->connectBtn, SIGNAL(clicked()), this, SLOT(connectButtonClicked()));
}

void ExistingConnection::connectButtonClicked() {
    emit(startConnect(this->connection));
}

ExistingConnection::~ExistingConnection()
{
    delete ui;
}

void ExistingConnection::updateStatus(char* status){
}

void ExistingConnection::updateConnectionData(nlohmann::json data) {
    this->connection = data;
    std::string connectionIp = "NULL";
    std::string connectionPort = "NULL";
    try{
        connectionIp = data["ip"];
        connectionPort = data["port"];
    } catch(std::exception &e) {
        std::cout << "No connections found" << std::endl;
        std::cout << e.what() << std::endl;
    };

    ui->ip->setText(QString::fromStdString(connectionIp));
    ui->port->setText(QString::fromStdString(connectionPort));
};