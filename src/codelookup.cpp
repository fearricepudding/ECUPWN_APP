#include "codelookup.h"
#include "../ui/ui_codelookup.h"
#include "./lookup.hpp"

CodeLookup::CodeLookup(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CodeLookup)
{
    ui->setupUi(this);

    connect(ui->lookupBtn, SIGNAL(clicked()), this, SLOT(lookupCode()));
}

CodeLookup::~CodeLookup()
{
    delete ui;
}

void CodeLookup::exit_app()
{
    this->close();
}

void CodeLookup::lookupCode(){
    QString code = ui->codeInput->text();
    Lookup *lookup = new Lookup();
    if(lookup->getStatus() != 0){
        ui->output->setText("DTC database not found! Try updating local database");
        return;
    };
    std::string result = lookup->findCode(code.toStdString());
    QString resultQ = QString::fromUtf8(result.c_str());
    ui->output->setText("[*] "+code+" - "+resultQ);
};
