#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //绑定信号与槽
    QObject::connect(ui->count,SIGNAL(clicked(bool)),this,SLOT(doprocessClicek(bool)));
    ui->btn_dex->setChecked(true);
    ui->res_lcd->setStyleSheet("border: 1px solid green; color: green; background: silver;");

}

Widget::~Widget()
{
    delete ui;
}


void Widget::doprocessClicek(bool)
{
    QString v1_text = ui->value1_le->text();
    QString v2_text = ui->value2_le->text();
    QString symbol_text = ui->symbol_cb->currentText();
    bool ok;
    //获取进制
    int radix=10;
    if(ui->btn_dex->isChecked())
    {
        radix = 10;
        ui->res_lcd->setMode(QLCDNumber::Dec);
    }
    else if(ui->btn_hex->isChecked())
    {
        radix = 16;
        ui->res_lcd->setMode(QLCDNumber::Hex);
    }
    else if(ui->btn_oct->isChecked())
    {
        radix = 8;
        ui->res_lcd->setMode(QLCDNumber::Oct);
    }

    int v1 = v1_text.toInt(&ok,radix);
    if(!ok)
    {
        return;
    }
    int v2 = v2_text.toInt(&ok,radix);
    if(!ok)
    {
        return;
    }
    int res = 0;
    //获取运算符
    if(symbol_text == '+')
    {
        res = v1 + v2;
    }
    else if(symbol_text == '-')
    {
        res = v1 - v2;
    }
    else if(symbol_text == '*')
    {
        res = v1 * v2;
    }
    else if(symbol_text == '/')
    {
        if(v2!=0)
            res = v1 / v2;
    }

    qDebug()<< res <<endl;
    //ui->res_lcd->setText(QString::number(res,radix));
    ui->res_lcd->display(res);


}




