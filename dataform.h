#ifndef DATAFORM_H
#define DATAFORM_H

#include <QDataWidgetMapper>
#include <QtSql/QSqlRelationalTableModel>
#include <QWidget>

namespace Ui {
    class DataForm;
}

class DataForm : public QWidget
{
    Q_OBJECT

public:
    explicit DataForm(QWidget *parent,
                      QSqlRelationalTableModel *model);
    ~DataForm();

private:
    Ui::DataForm *ui;

    QDataWidgetMapper *mapper;
    QSqlRelationalTableModel *model;
};

#endif // DATAFORM_H
