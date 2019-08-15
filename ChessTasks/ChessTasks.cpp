#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ChessTable.h"
#include "FEN.h"

namespace fs = std::filesystem;

const std::string mainName = "test.";
const std::string extensionIn = ".in";
const std::string extensionOut = ".out";

std::string makeNameTestIn( size_t i )
{
    return mainName + std::to_string( i ) + extensionIn;
}

std::string makeNameTestOut( size_t i )
{
    return mainName + std::to_string( i ) + extensionOut;
}

void Test1_FEN( const fs::path& dir )
{
    size_t i = 0;
    while( true )
    {
        fs::path fullPathIn = dir / makeNameTestIn( i );
        if( fs::exists( fullPathIn ) == false )
            break;

        fs::path fullPathOut = dir / makeNameTestOut( i );
        if( fs::exists( fullPathOut ) == false )
            break;

        FEN fenIn;
        std::ifstream infs( fullPathIn.string() );
        infs >> fenIn;

        std::ifstream ifs( fullPathOut.string() );
        ChessTable etalonChessTable;
        ifs >> etalonChessTable;

        if( fenIn.m_chess_table != etalonChessTable )
            throw std::runtime_error( "fail test i = " + std::to_string( i ) );

        ++i;
    }
    std::cout << dir << " - completed = " << i << '\n';
}

void Test2_FEN_BITS( const fs::path& dir )
{
    size_t i = 0;
    while( true )
    {
        fs::path fullPathIn = dir / makeNameTestIn( i );
        if( fs::exists( fullPathIn ) == false )
            break;

        fs::path fullPathOut = dir / makeNameTestOut( i );
        if( fs::exists( fullPathOut ) == false )
            break;

        FEN fenIn;
        std::ifstream infs( fullPathIn.string() );
        infs >> fenIn;

        auto res = fenIn.m_chess_table.toBitBoard();

        std::ifstream ifs( fullPathOut.string() );
        std::array<uint64_t, 12 > etalon;
        for( auto& e : etalon )
            ifs >> e;

        if( etalon != res )
            throw std::runtime_error( "fail test 1744.1.FEN - BITS _ i = " + std::to_string( i ) );

        ++i;
    }
    std::cout << dir << " - completed = " << i << '\n';
}

void Test3_FEN_SAVELOAD( const fs::path& dir )
{
    size_t i = 0;
    while( true )
    {
        fs::path fullPathIn = dir / makeNameTestIn( i );
        if( fs::exists( fullPathIn ) == false )
            break;

        fs::path fullPathOut = dir / makeNameTestOut( i );
        if( fs::exists( fullPathOut ) == false )
            break;

        FEN fenIn;
        std::ifstream infs( fullPathIn.string() );
        infs >> fenIn;
        
        std::ifstream ifs( fullPathOut.string() );
        std::string out;
        std::getline( ifs, out );

        std::string in = FenToString(fenIn);
        if( in != out )
        {
            throw std::runtime_error( "fail test 1745.1.Сборка и разборка i = " + std::to_string( i ) );
        }

        ++i;
    }
    std::cout << dir << " - completed = " << i << '\n';
}

void Test4_COUNTER_FULLSTEP( const fs::path& dir )
{
    size_t i = 0;
    while( true )
    {
        fs::path fullPathIn = dir / makeNameTestIn( i );
        if( fs::exists( fullPathIn ) == false )
            break;

        fs::path fullPathOut = dir / makeNameTestOut( i );
        if( fs::exists( fullPathOut ) == false )
            break;

        FEN fenIn;
        std::ifstream infs( fullPathIn.string() );
        infs >> fenIn;

        Step step;
        infs >> step.m_step;

        updateActiveAndFullMove( fenIn, step );

        std::ifstream ifs( fullPathOut.string() );
        std::string out;
        std::getline( ifs, out );

        std::string in = FenToString( fenIn );
        if( in != out )
            throw std::runtime_error( "fail test " + dir.string() + " i = " + std::to_string( i ) );

        ++i;
    }
    std::cout << dir << " - completed = " << i << '\n';
}
 

int main()
{
    try
    {
        Test1_FEN( R"(2019-08-12_Chess-Tasks\1743.1.FEN - ASCII)" );
        Test2_FEN_BITS( R"(2019-08-12_Chess-Tasks\1744.1.FEN - BITS _)" );
        Test3_FEN_SAVELOAD( R"(2019-08-12_Chess-Tasks\1745.1.Сборка и разборка)" );
        Test4_COUNTER_FULLSTEP( R"(2019-08-12_Chess-Tasks\1746.1.Счётчик ходов)" );
    }
    catch( const std::exception& err )
    {
        std::cerr << err.what() << '\n';
        return 1;
    }

    return 0;
}
