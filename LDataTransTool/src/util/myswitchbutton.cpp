#include "myswitchbutton.h"

/* 说明:自定义开关按钮控件实现文件
 * 功能:用来控制配置文件的开关设置
 */
mySwitchButton::mySwitchButton(QWidget *parent): QPushButton(parent)
{    
    setCursor(QCursor(Qt::PointingHandCursor));
    isCheck = false;

    styleOn = "border-image: url(:/image/switch/on.png); border: 0px;";
    styleOff = "border-image: url(:/image/switch/off.png); border: 0px;";

    setFixedSize(87,31);          //不允许变化大小
    setStyleSheet(styleOff);        //设置当前样式
    connect(this,SIGNAL(clicked()),this,SLOT(ChangeOnOff()));
}

void mySwitchButton::ChangeOnOff()
{
    if (isCheck){
        setStyleSheet(styleOff);
        isCheck=false;
    }else{
        setStyleSheet(styleOn);
        isCheck=true;
    }
}

//设置当前选中状态
void mySwitchButton::SetCheck(bool isCheck)
{
    if (this->isCheck!=isCheck){
        this->isCheck=!isCheck;
        ChangeOnOff();
    }
}
