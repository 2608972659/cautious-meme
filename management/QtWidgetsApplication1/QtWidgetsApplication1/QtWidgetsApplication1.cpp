#include "widget.h"
#include "ui_widget.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    loadData("C:\\Users\\1chen\\Desktop\\2\\data.txt");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadData(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    QTextStream stream(&file);
    m_fields = stream.readLine().split("\t");
    while (!stream.atEnd())
    {
        auto lineData = stream.readLine().split("\t");
        auto  s = new class pdata;
        s->name = lineData[0];

        s->number1 = lineData[1];
        s->number2 = lineData[2];
        s->number3 = lineData[3];
        m_data.push_back(s);

        qInfo() << lineData;

    }
}



void Widget::on_lookbtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->lookpage);
    //list显示到表格
    ui->looktablewidget->setColumnCount(m_fields.count());
    ui->looktablewidget->setHorizontalHeaderLabels(m_fields);
    for (auto s : m_data)
    {   //获取行号
        int row = ui->looktablewidget->rowCount();
        //添加空行
        //可添加
        ui->looktablewidget->insertRow(row);
        ui->looktablewidget->setItem(row, 0, new QTableWidgetItem(s->name));
        ui->looktablewidget->setItem(row, 1, new QTableWidgetItem(s->number1));
        ui->looktablewidget->setItem(row, 2, new QTableWidgetItem(s->number2));
        ui->looktablewidget->setItem(row, 3, new QTableWidgetItem(s->number3));

    }

}

void Widget::on_statbtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->statpage);

}

void Widget::on_quitbtn_released()
{
    close();
}

void Widget::on_pushButton_released()
{
    close();
}

void Widget::on_addbtn_released()
{
    //添加新行在最下面
    ui->looktablewidget->insertRow(ui->looktablewidget->rowCount());
    ui->looktablewidget->scrollToBottom();
}

void Widget::on_savebtn_released()
{
    for (int i=0;i<ui->)
}
