#include "canlogger.h"
#include "../../ui/ui_canlogger.h"
#include <QDebug>
#include <sstream>
#include <iostream>
#include <list>
#include <iomanip>

CanLogger::CanLogger(CanQueue *canData)
    : QDialog(nullptr)
    , ui(new Ui::CanLogger)
{
    ui->setupUi(this);

    this->canData = canData;

    connect(ui->stateToggle, SIGNAL(clicked()), this, SLOT(remoteStartLog()));

    this->counter = 0;
    this->scrollLimit = 100;
}

void CanLogger::remoteStartLog(){
    qDebug()<<"Sending startLog";
    emit startLog();
}

void CanLogger::addTest(){
    if(this->canMessages.size() > this->scrollLimit){
        this->canMessages.erase(this->canMessages.begin(), this->canMessages.end()-this->scrollLimit);
    };
    std::string current = std::to_string(this->counter);
    this->canMessages.push_back("test: "+current);
    this->counter++;
}

std::string uint8_to_hex_string(const uint8_t *v, const size_t s) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < s; i++) {
        ss << std::hex << std::setw(2) << static_cast<int>(v[i]) << " ";
    };
    return ss.str();
}

void CanLogger::renderCanLogs(){
    qDeleteAll(ui->log_container->widget()->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    
    std::list<can_frame> copy = this->canData->getQueue();

    for (can_frame &frame : copy) {
        std::stringstream frameString;
        frameString << std::hex << std::setw(2) << frame.can_id << " = ";
        frameString << uint8_to_hex_string(frame.data, 8);
           
        std::string framestdString = frameString.str();
        std::cout << framestdString << std::endl;
        QString frameQ = QString::fromStdString(framestdString);
        QLabel *newLabel = new QLabel();
        newLabel->setText(frameQ);
        ui->log_container->widget()->layout()->addWidget(newLabel);
    };
    int count = this->canMessages.size();
    ui->can_count->setText(QString::number(count));
    ui->log_container->scroll(9999, 0);
}

void CanLogger::newData(QString newString){
    if(this->canMessages.size() > this->scrollLimit){
        this->canMessages.erase(this->canMessages.begin(), this->canMessages.end()-this->scrollLimit);
    };
    this->canMessages.push_back(newString.toStdString());
}

void CanLogger::updateLogWindow() {
    this->addTest();
    this->renderCanLogs();
}

CanLogger::~CanLogger()
{
    delete ui;
}
