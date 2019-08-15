#include "FEN.h"

#include <cctype>
#include <sstream>

bool operator==( const FEN& lhs, const FEN& rhs )
{
    return lhs.m_chess_table == rhs.m_chess_table &&
        lhs.m_castling == rhs.m_castling &&
        lhs.m_en_passant == rhs.m_en_passant &&
        lhs.m_active_color == rhs.m_active_color &&
        lhs.m_full_move == rhs.m_full_move &&
        lhs.m_half_move == rhs.m_half_move;
}

bool operator!=( const FEN& lhs, const FEN& rhs )
{
    return !( lhs == rhs );
}

FEN FenFromStirng( const std::string& strFen )
{
    FEN fen;

    std::istringstream is( strFen );
    is >> fen;

    return fen;
}

std::array< bool, 256 > smb;

bool InitTableChessSymb()
{
    smb.fill( false );
    smb['/'] = true;
    smb['P'] = true;
    smb['N'] = true;
    smb['B'] = true;
    smb['R'] = true;
    smb['Q'] = true;
    smb['K'] = true;
    smb['p'] = true;
    smb['n'] = true;
    smb['b'] = true;
    smb['r'] = true;
    smb['q'] = true;
    smb['k'] = true;
    smb['0'] = true;
    smb['1'] = true;
    smb['2'] = true;
    smb['3'] = true;
    smb['4'] = true;
    smb['5'] = true;
    smb['6'] = true;
    smb['7'] = true;
    smb['8'] = true;
    smb['9'] = true;
    smb['0'] = true;
    return true;
}

bool initTableChessSymb = InitTableChessSymb();

bool isChessTableSymbol( char c )
{
    if( c < 0 )
        return false;
    return smb[uint8_t( c )];
}

std::istream& operator>>( std::istream& is, FEN& fen )
{
    ChessTable ct;

    char c = 0;
    size_t x = 0;
    size_t y = 0;

    while( is.get( c ) )
    {
        if( isChessTableSymbol( c ) == false )
            break;

        if( c == '/' )
        {
            x = 0;
            ++y;
        }else if( std::isdigit( c ) )
        {
            for( size_t i = 0; i < size_t( c - '0' ); ++i, ++x )
            {
                ct.set( x, 7 - y, '.' );
            }
        }
        else
        {
            ct.set( x, 7 - y, c );
            ++x;
        }
    }

    fen.m_chess_table = ct;

    is >> fen.m_active_color;
    fen.m_active_color = std::tolower( fen.m_active_color );
    is >> fen.m_castling;
    std::sort( fen.m_castling.begin(), fen.m_castling.end() );

    is >> fen.m_en_passant;
    if( fen.m_en_passant.size() > 1 )
        fen.m_en_passant[0] = std::tolower( fen.m_en_passant[0] );

    is >> fen.m_half_move;
    is >> fen.m_full_move;

    return is;
}

std::string FenToString( const FEN& fen )
{
    std::ostringstream os;

    os << fen;

    return os.str();
}

std::ostream& operator<<( std::ostream& os, const FEN& fen )
{
    for( size_t r = 0; r < 8; ++r )
    {
        size_t emptyPos = 0;
        for( size_t c = 0; c < 8; ++c )
        {
            if( fen.m_chess_table.get( c, 7 - r ) == '.' )
            {
                ++emptyPos;
                continue;
            }
            else
            {
                if( emptyPos != 0 )
                {
                    os << emptyPos;
                    emptyPos = 0;
                }
                os << fen.m_chess_table.get( c, 7 - r );
            }
        }
        if( emptyPos != 0 )
            os << emptyPos;

        if( r != 7 )
            os << '/';
    }

    os << ' ';
    os << fen.m_active_color << ' ';
    os << fen.m_castling << ' ';
    os << fen.m_en_passant << ' ';
    os << fen.m_half_move << ' ';
    os << fen.m_full_move;

    return os;
}

FEN updateActiveAndFullMove( const FEN& fen, const Step& step )
{
    FEN newFen = fen;
    updateActiveAndFullMove( newFen, step );
    return newFen;
}

void updateActiveAndFullMove( FEN& fen, const Step& step )
{
    if( fen.m_active_color == 'b' )
    {
        fen.m_full_move += 1;
        fen.m_active_color = 'w';
    }
    else
    {
        fen.m_active_color = 'b';
    }
}
