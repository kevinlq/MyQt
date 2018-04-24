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
