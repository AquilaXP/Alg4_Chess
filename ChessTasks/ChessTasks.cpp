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
            throw std::runtime_error( "fail test 1745.1.Сборка и разборка i = " + std::to_string( i ) );

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

void Test5_COUNTER_HALFMOVE( const fs::path& dir )
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

        updateHalfMove( fenIn, step );
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

void Test6_STEP_FIGURE( const fs::path& dir )
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

        actionStep( fenIn, step );

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

void Test7_P_TRANSFORM( const fs::path& dir )
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

        actionStep( fenIn, step );

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

void Test8_GET_IN_PASS( const fs::path& dir )
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

        enPassant( fenIn, step );
        actionStep( fenIn, step );

        FEN fenOut;
        std::ifstream ifs( fullPathOut.string() );
        std::string out;
        std::getline( ifs, out );

        fenOut = FenFromStirng( out );
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
        Test1_FEN( R"(Chess-Tasks\1743.1.FEN - ASCII)" );
        Test2_FEN_BITS( R"(Chess-Tasks\1744.1.FEN - BITS _)" );
        Test3_FEN_SAVELOAD( R"(Chess-Tasks\1745.1.Сборка и разборка)" );
        Test4_COUNTER_FULLSTEP( R"(Chess-Tasks\1746.1.Счётчик ходов)" );
        Test5_COUNTER_HALFMOVE( R"(Chess-Tasks\3694.1.Счётчик полуходов)" );
        Test6_STEP_FIGURE( R"(Chess-Tasks\3711.1.Перемещение фигуры)" );
        Test7_P_TRANSFORM( R"(Chess-Tasks\3713.1.Превращение пешки)" );
        Test8_GET_IN_PASS( R"(Chess-Tasks\3714.1.Взятие на проходе)" );
    }
    catch( const std::exception& err )
    {
        std::cerr << err.what() << '\n';
        return 1;
    }

    return 0;
}
