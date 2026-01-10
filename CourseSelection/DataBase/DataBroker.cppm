module;
#include<libpq-fe.h>

export module DataBase:DataBroker;


import std;
using std::string;

// 这个是设置的全局默认连接参数 就是我们这次会使用到的数据库
static string configuration = "host=localhost dbname=school_system user=ousuc password=A port=5432";

export class DataBroker{
public:
    explicit DataBroker(const std::string& connInfo = "");
    virtual ~DataBroker();

    void connect(const std::string& connInfo);

    void disconnect();

    void beginTransaction();

    void commit();

    void rollback(); //可能不会使用也不会实现

    // 新增 SQL 打印
    void selectPrint(PGresult* res);

    void clear(PGresult* res);

    PGresult* executeSQL(const std::string& sql);


    DataBroker(const DataBroker&) = delete;
    DataBroker& operator=(const DataBroker&) = delete;
private:
    PGconn* connection;
    bool transactionActive;
};

void DataBroker::clear(PGresult* res)
{
    PQclear(res);
}

// SQL查询结果打印
void DataBroker::selectPrint(PGresult* res)
{
    for (int row = 0; row < PQntuples(res); row++) {
            for (int col = 1; col < PQnfields(res); col++) {
                    const char* value = PQgetvalue(res, row, col);
                    printf("%s  ", value);
            }
            printf("\n");
    }
}

// 默认不开启事物，如果有连接参数那么就直接连接 无参数默认连接
DataBroker::DataBroker(const std::string& connInfo)
    : transactionActive(false)
{
    connect("");
    if (!connInfo.empty()) {
        connect(connInfo);
    }
}

// 析构函数 断开连接
DataBroker::~DataBroker(){
    disconnect();
}

// 连接函数
void DataBroker::connect(const std::string& connInfo){

    connection = PQconnectdb(connInfo.empty() ? configuration.c_str() : connInfo.c_str());

    if (PQstatus(connection) != CONNECTION_OK) {
        disconnect();
        throw std::runtime_error("连接失败");
    }
    std::println("连接成功");
}

// 断开连接
void DataBroker::disconnect() {
    if (connection) {
        // 如果事务正在进行，尝试回滚

        if (transactionActive) {
            PGresult* res = PQexec(connection, "ROLLBACK");
            PQclear(res);
            transactionActive = false;
        }

        PQfinish(connection);
        connection = nullptr;
        std::println("断开连接成功");
    } else {
        std::println("未建立连接，无需断开连接");
    }
}

void DataBroker::beginTransaction() {
    if (!connection) {
        throw std::runtime_error("连接未建立事物无法开启");
    }

    PGresult* res = PQexec(connection, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        throw std::runtime_error("开启事物失败");
    }

    PQclear(res);
    transactionActive = true;
}

void DataBroker::commit() {
    if (!connection) {
        throw std::runtime_error("没有建立连接无法提交");
    }
    if (!transactionActive) {
        throw std::runtime_error("没有开启事物无法提交");
    }

    PGresult* res = PQexec(connection, "COMMIT");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        throw std::runtime_error("提交失败");
    }

    PQclear(res);
    transactionActive = false;
}

PGresult* DataBroker::executeSQL(const std::string& sql) {
    std::println("执行sql语句");
    if (!connection) {
        throw std::runtime_error("没有建立连接无法执行sql语句");
    }

    PGresult* res = PQexec(connection, sql.c_str());

    // 检查执行状态
    ExecStatusType status = PQresultStatus(res);
    if (status != PGRES_COMMAND_OK && status != PGRES_TUPLES_OK && status != PGRES_EMPTY_QUERY) {
    // 核心：获取PostgreSQL的具体报错信息，这是排查问题的关键
       std::string errorMsg = PQerrorMessage(connection); // conn是你的数据库连接（PGconn*类型）
       PQclear(res);
       // 抛出异常时携带具体错误信息，而非仅“SQL 执行失败”
       throw std::runtime_error("SQL 执行失败：" + errorMsg);
    }

    return res;
}

// 回滚事务
void DataBroker::rollback() {
    if (!connection) {
        throw std::runtime_error("没有建立连接无法回滚");
    }


    if (!transactionActive) {
        throw std::runtime_error("无法进行回滚，没有这个事物");
    }

    PGresult* res = PQexec(connection, "ROLLBACK");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        throw std::runtime_error("回滚事物失败");
    }

    PQclear(res);
    transactionActive = false;
}
