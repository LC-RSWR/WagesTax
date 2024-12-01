#ifndef SQLMANAGER_H
#define SQLMANAGER_H

// 包含 QObject 类定义，Qt 的所有类都继承自 QObject 类，提供对象间信号和槽机制
#include <QObject>

// SqlManager 类负责与数据库的交互，包含创建数据库、增删改查员工信息等功能
class SqlManager
{
public:
    // 构造函数，用于初始化 SqlManager 对象
    SqlManager();

    // createSql 函数用于创建数据库及相关表格
    // 该函数会检查数据库是否存在，如果不存在则创建数据库
    void createSql();

    // addEmployee 函数用于向数据库中添加一名员工的信息
    // 参数:
    //   - name: 员工的姓名
    //   - salary: 员工的工资
    void addEmployee(const QString& name, double salary);

    // updateEmployee 函数用于更新数据库中指定员工的相关信息
    // 参数:
    //   - id: 员工的唯一标识符（通常是员工的 ID）
    //   - name: 员工的新姓名
    //   - salary: 员工的新工资
    void updateEmployee(int id, const QString& name, double salary);

    // deleteEmployee 函数用于从数据库中删除指定员工的信息
    // 参数:
    //   - id: 要删除的员工的唯一标识符
    void deleteEmployee(int id);

    // queryEmployees 函数用于查询数据库中所有员工的基本信息
    // 返回值：一个包含员工 ID 和姓名的 vector 对象
    std::vector<std::pair<int, QString>> queryEmployees();

    // queryEmployeeByIdOrName 函数用于通过员工 ID 或姓名来查询员工信息
    // 参数:
    //   - id: 员工的唯一标识符
    //   - name: 员工的姓名
    // 返回值：一个包含员工 ID 和姓名的 vector 对象
    std::vector<std::pair<int, QString>> queryEmployeeByIdOrName(int id, const QString& name);

    // queryEmployeeByIdOrName 函数重载，用于通过员工 ID 查询员工的详细信息
    // 参数:
    //   - id: 员工的唯一标识符
    // 返回值：一个包含员工 ID、姓名和工资的 vector 对象
    std::vector<std::tuple<int, QString, double>> queryEmployeeByIdOrName(int id);
};

#endif // SQLMANAGER_H
