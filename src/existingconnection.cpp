#include "existingconnection.h"
#include "../ui/ui_existingconnection.h"
#include "../candy/src/candy.h"
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
