#include "splash.h"
#include "./codelookup.h"
#include "../ui/ui_splash.h"
#include "./canlogger.h"
#include "./connectionsettings.h"
#include "../candy/src/candy.h"
#include <QThread>

Splash::Splash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Splash)
{
    ui->setupUi(this);

    thread = new QThread();
    worker = new CanWorker();
    worker->moveToThread(thread);


    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);

    connect(ui->exit, SIGNAL(clicked()), this, SLOT(exit_app()));
    connect(ui->codeLookup, SIGNAL(clicked()), this, SLOT(lookup_code()));
    connect(ui->canLogger, SIGNAL(clicked()), this, SLOT(can_logger()));
    connect(ui->connectBtn, SIGNAL(clicked()), this, SLOT(connect_settings()));
}

Splash::~Splash()
{
    delete ui;
}


void Splash::exit_app()
{
    QApplication::exit();
}

void Splash::lookup_code(){
    CodeLookup *lookupWindow = new CodeLookup;
    lookupWindow->show();
}

void Splash::can_logger(){
    CanLogger *canLogger = new CanLogger;
    connect(worker, SIGNAL(valueChanged(QString)), canLogger, SLOT(newData(QString)));
    canLogger->show();
}

void Splash::connect_settings(){

    ConnectionSettings *connectionSettings = new ConnectionSettings();

    connect(connectionSettings, SIGNAL(startCanThread(int)), this, SLOT(connection_thread(int)));
    connectionSettings->show();
}

void Splash::connection_thread(int bitrate){
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    worker->requestWork();
}
