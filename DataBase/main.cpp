#include <libpq-fe.h>
import DataBase;
import std;

int main()
{
        std::cout << "------------- test ----------------" << std::endl;
        DataBroker db;
        // RES
        auto res = db.executeSQL("SELECT * FROM students");
        db.selectPrint(res);
        PQclear(res);
        // END RES

}
