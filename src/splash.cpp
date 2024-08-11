#include "splash.h"
#include "./codelookup.h"
#include "../ui/ui_splash.h"
#include "./canlogger.h"
#include "./connectionsettings.h"
#include "../candy/src/candy.h"
#include <QThread>
#include <QTreeWidgetItem>
#include <QTreeView>

Splash::Splash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Splash)
{
    ui->setupUi(this);

    thread = new QThread();
    worker = new CanWorker();
    worker->moveToThread(thread);
    
//    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);

    connect(ui->exit, SIGNAL(clicked()), this, SLOT(exit_app()));
    connect(ui->codeLookup, SIGNAL(clicked()), this, SLOT(lookup_code()));
    connect(ui->canLogger, SIGNAL(clicked()), this, SLOT(can_logger()));

    this->setupPages();

    // Connect nav panel to pages
}


Splash::~Splash()
{
    delete ui;
}

void Splash::setupPages(){

    ConnectionSettings* connPage = new ConnectionSettings;
    ui->stackedWidget->addWidget(connPage);
    ui->stackedWidget->setCurrentIndex(2);

}

void Splash::exit_app()
{
    this->worker->shutdown();
    QApplication::exit();
}

void Splash::lookup_code(){
    CodeLookup *lookupWindow = new CodeLookup;
    lookupWindow->show();
}

void Splash::can_logger(){
    CanLogger *canLogger = new CanLogger;
    //connect(worker, SIGNAL(valueChanged(QString)), canLogger, SLOT(newData(QString)));
    connect(canLogger, SIGNAL(startLog()), this, SLOT(testLog()));
    canLogger->show();
}

void Splash::testLog(){
    thread->start();
}

void Splash::connectToCan(){
    int result = worker->joinCanNetwork();
    if(result != 0){
        ui->connectBtn->setText("ERROR");
        return;
    };
    ui->connectBtn->setText("CONNECTED");
    ui->connectBtn->setProperty("connected", "1");
    ui->connectBtn->style()->unpolish(ui->connectBtn);
    ui->connectBtn->style()->polish(ui->connectBtn);
};

void Splash::connection_thread(int bitrate){
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    worker->requestWork();
}
