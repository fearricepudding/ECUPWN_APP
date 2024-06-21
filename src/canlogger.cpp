#include "canlogger.h"
#include "../ui/ui_canlogger.h"

CanLogger::CanLogger(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CanLogger)
{
    ui->setupUi(this);

    connect(ui->stateToggle, SIGNAL(clicked()), this, SLOT(addTest()));

    this->counter = 0;
    this->scrollLimit = 200;
}

void CanLogger::addTest(){
    if(this->canMessages.size() > this->scrollLimit){
        this->canMessages.erase(this->canMessages.begin(), this->canMessages.end()-this->scrollLimit);
    };
    std::string current = std::to_string(this->counter);
    this->canMessages.push_back("test: "+current);
    this->counter++;
    this->renderCanLogs();
}

void CanLogger::renderCanLogs(){
    qDeleteAll(ui->log_container->widget()->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    for (auto const& message : this->canMessages){
        QLabel *newLabel = new QLabel();
        newLabel->setText(message.c_str());
        ui->log_container->widget()->layout()->addWidget(newLabel);
    }
    int count = this->canMessages.size();
    ui->can_count->setText(QString::number(count));
    ui->log_container->scroll(9999, 0);
}

void CanLogger::newData(QString newString){
    if(this->canMessages.size() > this->scrollLimit){
        this->canMessages.erase(this->canMessages.begin(), this->canMessages.end()-this->scrollLimit);
    };

    this->canMessages.push_back(newString.toStdString());
    this->renderCanLogs();
}

CanLogger::~CanLogger()
{
    delete ui;
}
