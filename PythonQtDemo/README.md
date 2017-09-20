# Qt Python 测试工程

- Qt:5.7 32b
- Mingw 5.3
- Python2.7
- OS:windows7 64b

## 构建步骤

打开PythonQtDemo.pro.然后取消影子构建目录，编程成功后会在当前工程目录下bin/下生成对应版本的可执行文件，其中`test_python.py`文件用来进行测试,必须和可执行文件在同一目录下.

--- 

主要代码:
```C++
#include <QCoreApplication>
#include <Python.h>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //初始化python模块
    Py_Initialize();
    if ( !Py_IsInitialized() )
    {
        return -1;
    }
    //导入test.py模块
    PyObject* pModule = PyImport_ImportModule("test_python");
    if (!pModule) {
        printf("Cant open python file!\n");
        return -1;
    }
    //获取test模块中的hello函数
    PyObject* pFunhello = PyObject_GetAttrString(pModule,"helloworld");

    if( !pFunhello){
        cout<<"Get function helloworld failed"<<endl;
        return -1;
    }
    //调用hello函数
    PyObject_CallFunction(pFunhello,NULL);
    //结束，释放python
    Py_Finalize();
    return a.exec();

}

```

工程结构为:

![工程结构](/screen/PythonQtDemo/screen/screen.png)
