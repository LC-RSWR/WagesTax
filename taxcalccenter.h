#ifndef TAXCALCCENTER_H
#define TAXCALCCENTER_H

// 引入 QObject 类头文件（尽管在当前代码中并未使用 QObject 的功能，
// 但为了支持 Qt 的信号和槽机制、属性系统或其他 Qt 特性，可能会在后续扩展中使用）
#include <QObject>

// TaxCalcCenter 类用于税务计算的中心，负责根据提供的工资计算税金
// 类中有一个静态方法 calculateTax(double salary) 用于计算税金
class TaxCalcCenter
{
public:
    // 构造函数
    // 构造函数的作用通常是初始化对象，虽然此处没有明确的成员变量需要初始化，
    // 它仍然可以用于后续的扩展（例如添加成员变量、初始化操作等）。
    TaxCalcCenter();

    // 静态方法 calculateTax，用于根据提供的工资计算应缴税款
    // 该方法是静态的，意味着无需创建类的实例即可直接调用
    // 参数 salary 是输入的工资数额，返回值是计算得出的税额
    static double calculateTax(double salary);
};

// 预处理指令的结尾，表示头文件结束
#endif // TAXCALCCENTER_H
