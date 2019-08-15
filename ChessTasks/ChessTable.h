#pragma once

#include <array>
#include <ostream>
#include <istream>
#include <string>
#include <map>

class ChessTable
{
public:
    ChessTable();

    bool operator == ( const ChessTable& table ) const;
    bool operator != ( const ChessTable& table ) const;

    void set( size_t x, size_t y, char c );
    void set( const std::string& pos, char c );
    char get( size_t x, size_t y ) const;

    friend std::ostream& operator << ( std::ostream& os, const ChessTable& table );
    friend std::istream& operator >> ( std::istream& is, ChessTable& table );

    std::array<uint64_t, 12> toBitBoard() const;
private:
    static std::pair< size_t, size_t > from_string( const std::string& pos );

    std::array< std::array< char, 8 >, 8 > m_table;
};