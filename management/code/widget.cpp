#include "widget.h"
#include "ui_widget.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QMessageBox>
#include<QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    loadData("C:\\Users\\1chen\\Desktop\\2\\data.txt");
    setWindowTitle("management system");

//    searchLineEdit = new QLineEdit(this);
//    connect (searchLineEdit, &QLineEdit::textChanged, this, [this]() {
//        QString searchTerm = searchLineEdit->text();
//    });
    searchLineEdit = findChild<QLineEdit*>("searchLineEdit");
    connect(searchLineEdit, &QLineEdit::textChanged, this, &Widget::on_lineEdit_editingFinished);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        ui->stackedWidget->setCurrentWidget(ui->menupage);
    }
}

void Widget::loadData(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
       return;
    }
    QTextStream stream(&file);
    m_fields=stream.readLine().split("\t");
    while(!stream.atEnd())
    {
        auto lineData=stream.readLine().split("\t");
        auto  s = new class pdata;
        s->name=lineData[0];
        s->number1=lineData[1];
        s->number2=lineData[2];
        s->number3=lineData[3];
        m_data.push_back(s);

        qInfo() << lineData;

    }
}

void Widget::saveData(const QString &filename)
{
    QFile file(filename);
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
         qWarning() << "Failed to open file for writing: " << filename;
         return;
     }

     QTextStream stream(&file);
     // 写入字段行
     stream << m_fields.join("\t") << "\n";

     // 写入数据行
     for (const auto data : m_data)
     {
         stream << data->name << "\t"
                << data->number1 << "\t"
                << data->number2 << "\t"
                << data->number3 << "\n";
     }

     file.close();
}

void Widget::sortDataByName()
{
    // 使用 Qt 的算法对 m_data 进行排序
        std::sort(m_data.begin(), m_data.end(), [](const pdata* a, const pdata* b) {
            return a->name < b->name;
        });

        // 更新表格中的显示顺序
        ui->looktablewidget->clearContents();
        for (int row = 0; row < m_data.size(); ++row)
        {
            auto s = m_data[row];
            ui->looktablewidget->setItem(row, 0, new QTableWidgetItem(s->name));
            ui->looktablewidget->setItem(row, 1, new QTableWidgetItem(s->number1));
            ui->looktablewidget->setItem(row, 2, new QTableWidgetItem(s->number2));
            ui->looktablewidget->setItem(row, 3, new QTableWidgetItem(s->number3));
        }
}

void Widget::deleteSelectedRow()
{
    // 获取选中的行
    QList<QTableWidgetItem*> selectedItems = ui->looktablewidget->selectedItems();
    QList<int> selectedRows;

    // 提取选中行的索引
    for (QTableWidgetItem* item : selectedItems) {
        int row = item->row();
        if (!selectedRows.contains(row)) {
            selectedRows.append(row);
        }
    }

    // 根据索引删除数据和表格行
    std::sort(selectedRows.begin(), selectedRows.end(), std::greater<int>());
    for (int row : selectedRows) {
        // 从 m_data 中删除对应的数据
        delete m_data[row];
        m_data.removeAt(row);

        // 从表格中删除对应的行
        ui->looktablewidget->removeRow(row);
    }
}

void Widget::searchContact(const QString &searchTerm)
{
    // 清空表格中的旧数据
        ui->looktablewidget->clearContents();
        ui->looktablewidget->setRowCount(0);

        // 遍历联系人数据，查找匹配项
        for (auto s : m_data)
        {
            // 判断姓名或电话号码是否包含搜索关键词
            if (s->name.contains(searchTerm, Qt::CaseInsensitive) ||
                s->number1.contains(searchTerm, Qt::CaseInsensitive) ||
                s->number2.contains(searchTerm, Qt::CaseInsensitive) ||
                s->number3.contains(searchTerm, Qt::CaseInsensitive))
            {
                int row = ui->looktablewidget->rowCount();
                ui->looktablewidget->insertRow(row);

                ui->looktablewidget->setItem(row, 0, new QTableWidgetItem(s->name));
                ui->looktablewidget->setItem(row, 1, new QTableWidgetItem(s->number1));
                ui->looktablewidget->setItem(row, 2, new QTableWidgetItem(s->number2));
                ui->looktablewidget->setItem(row, 3, new QTableWidgetItem(s->number3));
            }
        }
}




void Widget::on_lookbtn_released()
{
    ui->stackedWidget->setCurrentWidget(ui->lookpage);

    // 清空表格中的旧数据
        ui->looktablewidget->clearContents();
        ui->looktablewidget->setRowCount(0);
    //list显示到表格
    ui->looktablewidget->setColumnCount(m_fields.count());
    ui->looktablewidget->setHorizontalHeaderLabels(m_fields);
    for (auto s : m_data)
    {   //获取行号
        int row = ui->looktablewidget->rowCount();
        //添加空行
        ui->looktablewidget->insertRow(row);

        ui->looktablewidget->setItem(row, 0, new QTableWidgetItem(s->name));
        ui->looktablewidget->setItem(row, 1, new QTableWidgetItem(s->number1));
        ui->looktablewidget->setItem(row, 2, new QTableWidgetItem(s->number2));
        ui->looktablewidget->setItem(row, 3, new QTableWidgetItem(s->number3));

    }

}

void Widget::on_statbtn_released()
{
    sortDataByName();
    QMessageBox::information(this,"排序提示","排序成功");



}

void Widget::on_quitbtn_released()
{
    saveData("C:\\Users\\1chen\\Desktop\\2\\data.txt");
    close();

}


void Widget::on_addbtn_released()
{
    //添加新行在最下面
     ui->looktablewidget->insertRow(ui->looktablewidget->rowCount());
     //跳转到最下面
     ui->looktablewidget->scrollToBottom();
     //创建一个联系人
     m_data.push_back(new pdata);

}

void Widget::on_savebtn_released()
{
    for (int i = 0; i<ui->looktablewidget->rowCount(); i++)
    {

        m_data[i]->name = ui->looktablewidget->item(i,0)->text();
        m_data[i]->number1 = ui->looktablewidget->item(i,1)->text();
        m_data[i]->number2 = ui->looktablewidget->item(i,2)->text();
        m_data[i]->number3 = ui->looktablewidget->item(i,3)->text();
    }
    QMessageBox::information(this,"保存提示","保存成功");
}

void Widget::on_delbtn_released()
{
    deleteSelectedRow();
}

void Widget::on_lineEdit_editingFinished()
{

    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());  // 获取发送信号的对象
        if (lineEdit)
        {
            QString searchTerm = lineEdit->text();
            searchContact(searchTerm);
        }
}
