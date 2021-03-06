#include <iostream>

#include "ocilib.hpp"

using namespace ocilib;

int main(void)
{
    try
    {
        Environment::Initialize();

        Connection con("db", "usr", "pwd");

        Statement st(con);

        st.SetFetchMode(Statement::FetchScrollable);
        st.Execute("select table_name from all_tables where rownum < 10 ");

        Resultset rs = st.GetResultset();

        rs.Last();
        std::cout << "Total rows : " << rs.GetCount() << std::endl;

        rs.First();
        std::cout << "table " << rs.Get<ostring>(1) << std::endl;

        while (rs.Next())
        {
            std::cout << "table " << rs.Get<ostring>(1) << std::endl;
        }

        while (rs.Prev())
        {
            std::cout << "table " << rs.Get<ostring>(1) << std::endl;
        }

        rs.Seek(Resultset::SeekRelative, 6);
        std::cout << "table " << rs.Get<ostring>(1) << std::endl;

        while (rs.Next())
        {
            std::cout << "table " << rs.Get<ostring>(1) << std::endl;
        }

        rs.Seek(Resultset::SeekRelative, -3);
        std::cout << "table " << rs.Get<ostring>(1) << std::endl;
    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    Environment::Cleanup();

    return EXIT_SUCCESS;
}
