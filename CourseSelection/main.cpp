import std;
import registrar;
int main()
{
        auto&& system = Registrar::getInstance();
        system.exec();
        return 0;
}
