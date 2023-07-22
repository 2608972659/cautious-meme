#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"pdata.h"
#include<QStringList>
#include<QList>
#include<QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //键盘退出
    void keyPressEvent(QKeyEvent* event);

    void loadData(const QString& filename);
    void saveData(const QString& filename);
    void sortDataByName();
    void deleteSelectedRow();
    void searchContact(const QString& searchTerm);





private slots:


    void on_lookbtn_released();

    void on_statbtn_released();

    void on_quitbtn_released();

    void on_addbtn_released();

    void on_savebtn_released();

    void on_delbtn_released();

    void on_lineEdit_editingFinished();

private:
    Ui::Widget *ui;
    QStringList m_fields;
    QList<pdata*> m_data;
    QLineEdit *searchLineEdit;
};
#endif // WIDGET_H
