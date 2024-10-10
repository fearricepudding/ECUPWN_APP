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
    
}

ExistingConnection::~ExistingConnection()
{
    delete ui;

}

void ExistingConnection::updateStatus(char* status){
}

void ExistingConnection::updateConnectionData(nlohmann::json data) {
    std::string connectionIp = "NULL";
    try{
        connectionIp = data["ip"];
    } catch(std::exception &e) {
        std::cout << "No connections found" << std::endl;
        std::cout << e.what() << std::endl;
    };

    std::cout << connectionIp << std::endl;
};