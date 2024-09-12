#include "splash.h"
#include "./codelookup.h"
#include "../ui/ui_splash.h"
#include "./canlogger.h"
#include "./connectionsettings.h"
#include "../candy/src/candy.h"
#include "ConnectionManager.h"
#include <QThread>
#include <QTreeWidgetItem>
#include <QTreeView>

Splash::Splash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Splash)
{
    ui->setupUi(this);

    this->conManager = new ConnectionManager();

    connect(ui->exit, SIGNAL(clicked()), this, SLOT(exit_app()));
    connect(ui->codeLookup, SIGNAL(clicked()), this, SLOT(lookup_code()));
    connect(ui->canLogger, SIGNAL(clicked()), this, SLOT(can_logger()));


    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *,int)), this, SLOT(treeItemClicked()));

    this->setupPages();
}

void Splash::addPage(std::string name, int index) {

}

void Splash::treeItemClicked() {
    qDebug() << "Tree item clicked \n";
}

Splash::~Splash()
{
    delete ui;
}

void Splash::setupPages(){
    QTreeWidget * tree = ui->treeWidget;

    QTreeWidgetItem * topLevel = new QTreeWidgetItem();
    topLevel->setText(0, "ECUPWN");

    ConnectionSettings* connPage = new ConnectionSettings;
    ui->stackedWidget->addWidget(connPage);
    ui->stackedWidget->setCurrentIndex(1);

    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setText(0,"Connection settings");
    topLevel->addChild(item);

    tree->addTopLevelItem(topLevel); 
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
    //connect(worker, SIGNAL(valueChanged(QString)), canLogger, SLOT(newData(QString)));
    connect(canLogger, SIGNAL(startLog()), this, SLOT(testLog()));
    canLogger->show();
}
