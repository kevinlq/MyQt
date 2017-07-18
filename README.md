# MyQt
[TOP]

My Qt demo  
Qt:4.8.6    
**编译时均取消影子构建**

## MThreadTest
多线程实例测试

继承自QObject，通过信号与槽形式触发通信，在主线程中使用moveTothread()方法创建了多线程

外部添加了定时器，定时发送信号给obj，这样实现了循环处理数据

## LBaiduMapTest
Qt 和百度地图进行交互demo  

Qt:4.8.6    
javascript:2.0  

主要实现Qt和js双向数据交互

* 1. 数据经纬度信息后可以在地图中添加一个标记(marker)
* 2. 点击对应的marker可以获取该标记的经纬度信息；


## LDataTransTool
数据转换工具

## LUIFrame
界面封装库  
Qt:4.8.6  

![](/screen/luiframe_project.png)

![](/screen/luiframe.png)


横排工具栏 
![](/screen/luiframe2.png)

## TableView嵌入CheckBox

TableView嵌入CheckBox，采用自定义委托和模型

**实现的主要功能：**
1. 动态插入数据；
2. 动态删除数据；
3. 支持多选/全部选中对数据进行删除；
4. 对数据进行动态修改(**待完成**)

![tableView checkbox](/screen/tableview.png);

![tableView checkbox](/screen/tableview2.png);


## 串口助手
![](/screen/serialTool.png)


