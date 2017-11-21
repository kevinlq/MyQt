# MyQt
[TOP]

My Qt demo  
Qt:4.8.6    
**编译时均取消影子构建**

## 1. MThreadTest
多线程实例测试

继承自QObject，通过信号与槽形式触发通信，在主线程中使用moveTothread()方法创建了多线程

外部添加了定时器，定时发送信号给obj，这样实现了循环处理数据

## 2. LBaiduMapTest
Qt 和百度地图进行交互demo  

Qt:4.8.6    
javascript:2.0  

主要实现Qt和js双向数据交互

* 1. 数据经纬度信息后可以在地图中添加一个标记(marker)
* 2. 点击对应的marker可以获取该标记的经纬度信息；


## 3. LDataTransTool
数据转换工具

## 4. LUIFrame
界面封装库  
Qt:4.8.6  
<center>
<img src="/screen/luiframe_project.png" width="50%" height="50%" />
</center>

工具栏： 
<center>
<img src="/screen/luiframe.png" width="50%" height="50%" />
</center>


横排工具栏 ： 
<center>
<img src="/screen/luiframe2.png" width="50%" height="50%" />
</center>

## 5. TableView嵌入CheckBox

TableView嵌入CheckBox，采用自定义委托和模型

**实现的主要功能：**
1. 动态插入数据；
2. 动态删除数据；
3. 支持多选/全部选中对数据进行删除；
4. 对数据进行动态修改(**待完成**)

<center>
<img src="/screen/tableview.png" width="50%" height="50%" />
</center>

<center>
<img src="/screen/tableview2.png" width="50%" height="50%" />
</center>


## 6. 串口助手  
<center>
<img src="/screen/serialTool.png" width="50%" height="50%" />
</center>

## 7. 饼状图雏形

| OS   | W7 64b    |
| --- | --- |
|  Qt   | 4.8.6    |
| 编译器 | mingw32 |

...待完善   

<center>
<img src="/screen/pieChartDemo.png" width="50%" height="50%" />
</center>

<center>
<img src="/screen/pieChartDemo2.png" width="50%" height="50%" />
</center>

![](/screen/pieChartDemo3.png)

## 8. LXmlDemo

- XML文件操作demo

## 9. SVGPicOperator

- SVG图片操作

## 10.[LMThreadOP](/LMThreadOP/)

- 多线程操作，加快计算速度

使用QQueue创建了一个消息队列，消费者线程从中读取数据，处理后通过信号将结果发送出去.

![](/screen/thread.png)

[参考文章地址](https://segmentfault.com/a/1190000010261721)

## 11.[LQImageOP](/LQImageOP)

>QImage操作图像像素

![示例](/screen/LQImageOP.png)

## 12. [LListWidgetPaging](/LListWidgetPaging)

QListWidget元素进行分页展示
![LListWidgetPaging](/screen/LListWidgetPaging.png)

```C++
分页存储过程或者页面分页中的分页算法:

int pagesize // 每页记录数

int recordcount // 总记录数

int pagecount // 总页数

pagecount=(recordcount+pagesize-1)/pagesize

此方法得出的结果为实际页码

pagecount=(recordcount-1)/pagesize

此方法得出的结果为实际页码-1
```

# change log

- V0.0.6 添加python和Qt混合编程demo(PythonQtDemo);
- V0.0.7 添加XML操作demo
- V0.0.8 添加SVG图片属性值修改demo
- V0.0.9 添加多线程demo
- V0.1.0 添加QImage操作图像素
- V0.1.1 添加QListWidget分页排序
