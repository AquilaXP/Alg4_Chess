#include "ChessTable.h"



bool ChessTable::operator!=( const ChessTable& table ) const
{
    return m_table != table.m_table;
}

bool ChessTable::operator==( const ChessTable& table ) const
{
    return m_table == table.m_table;
}

ChessTable::ChessTable()
{
    for( auto& line : m_table )
    {
        line.fill( '.' );
    }
}

void ChessTable::set( std::string_view pos, char c )
{
    auto p = stringToPos( pos );
    m_table[p.second][p.first] = c;
}

void ChessTable::set( size_t x, size_t y, char c )
{
    m_table[y][x] = c;
}

char ChessTable::get( size_t x, size_t y ) const
{
    return m_table[y][x];
}

char ChessTable::get( std::string_view pos ) const
{
    auto p = stringToPos( pos );
    return m_table[p.second][p.first];
}

std::array<uint64_t, 12> ChessTable::toBitBoard() const
{
    enum
    {
        whitePawns,
        whiteKnights,
        whiteBishops,
        whiteRooks,
        whiteQueens,
        whiteKing,

        blackPawns,
        blackKnights,
        blackBishops,
        blackRooks,
        blackQueens,
        blackKing
    };

    std::map< char, size_t > char_to_enum =
    {
        { 'P', whitePawns },
        { 'N', whiteKnights },
        { 'B', whiteBishops },
        { 'R', whiteRooks },
        { 'Q', whiteQueens },
        { 'K', whiteKing },
        { 'p', blackPawns },
        { 'n', blackKnights },
        { 'b', blackBishops },
        { 'r', blackRooks },
        { 'q', blackQueens },
        { 'k', blackKing }
    };

    std::array<uint64_t, 12> res;
    res.fill( 0 );

    for( size_t r = 0; r < 8; ++r )
    {
        for( size_t c = 0; c < 8; ++c )
        {
            if( auto iter = char_to_enum.find( get( c, r ) ); iter != char_to_enum.end() )
            {
                res[iter->second] |= static_cast<uint64_t>( 1 ) << ( r * 8 + c );
            }
        }
    }

    return res;
}

std::ostream& operator<<( std::ostream& os, const ChessTable& table )
{
    os << "  +-----------------+\n";
    for( size_t r = 0; r < 8; ++r )
    {
        os << 8 - r << " | ";
        for( auto& c : table.m_table[8 - r - 1] )
        {
            os << c << ' ';
        }
        os << "|\n";
    }
    os << "  +-----------------+\n";
    os << "    a b c d e f g h  \n\n";
    return os;
}

std::istream& operator>>( std::istream& is, ChessTable& table )
{
    std::string ignoreLine;
    std::getline( is, ignoreLine );
    for( size_t r = 0; r < 8; ++r )
    {
        is.ignore( 3 );

        for( auto& c : table.m_table[8 - r - 1] )
        {
            is >> c;
        }
        std::getline( is, ignoreLine );
    }
    std::getline( is, ignoreLine );
    std::getline( is, ignoreLine );
    std::getline( is, ignoreLine );
    return is;
}

std::pair< size_t, size_t > stringToPos( std::string_view pos )
{
    return std::make_pair( pos[0] - 'a', 7 - ( '8' - pos[1] ) );
}
