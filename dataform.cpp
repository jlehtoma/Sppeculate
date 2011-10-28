#include "dataform.h"
#include "ui_dataform.h"

DataForm::DataForm(QWidget *parent, QSqlRelationalTableModel *model) :
    QWidget(parent),
    ui(new Ui::DataForm)
{
    ui->setupUi(this);

    mapper = new QDataWidgetMapper;
    mapper->setModel(model);
    mapper->addMapping(ui->sciLineEdit, 0);
    mapper->addMapping(ui->comLineEdit, 1);
    mapper->toFirst();
}

DataForm::~DataForm()
{
    delete ui;
}
