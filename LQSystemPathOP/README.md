# LQSystemPathOP

这是一个操作系统环境变量的一个工具，可以对系统环境变量进行设置。

## 由来

之前在Qt Creator中看到有可视化操作区域，所以抽时间自己写一个，这次也是为了练习QML，打算用QML编写界面，然后逻辑使用C++来实现。

![](/LQSystemPathOP/screen/1.png);

## 环境
- Qt版本:Qt4.8.6，Qt5.4.2，Qt5.7
- Mingw 5.3
- OS:windows7 64b


## log
- V0.0.1 创建一个demo


## 遇到的问题
在C++中申明了一个信号和槽函数，然后再QML中通过按下一个恶按钮进行传值，结果老是不对，
最后发现是大小写问题。

C++中定义的信号：
```C++
Q_SIGNALS:
    void pathChanged(const QString &strPath);

public Q_SLOTS:
    void slotOnSend();
```

QML中绑定调用：

```QML

    SystemPathInfo {
        id:sysObj
    }
	
	Button{
		id: showId
		text: qsTr("显示")
		width: 80; height:30
		x: 4 + txtWidth * 2; y: 4

        onClicked: {
            sysObj.slotOnSend();
        }
    }
	
    Connections {
        target: sysObj
        onPathChanged:{
            tetInfo.text = strPath
        }
    }
```

注意QML中信号关联.

C++中信号`pathChanged`首字母是消息，在QML中关联时大写`onPathChanged`,而且自动加上on