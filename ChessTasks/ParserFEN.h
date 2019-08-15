// #pragma once
// 
// #include <map>
// #include <array>
// #include <ostream>
// #include <istream>
// #include <iostream>
// #include <string>
// #include <algorithm>
// #include <fstream>
// #include <cctype>
// // 
// // struct Position
// // {
// //     Position()
// //     {
// // 
// //     }
// //     Position( const std::string& pos ) : pos( pos )
// //     {
// //     }
// // 
// //     std::string pos;
// //     operator std::string()
// //     {
// //         return pos;
// //     }
// //     std::pair< size_t, size_t > to_pos()
// //     {
// //         return std::make_pair( 0, 0 );
// //     }
// // };
// // 
// // std::pair< size_t, size_t > from_string( const std::string& pos )
// // {
// //     return std::make_pair( pos[0] - 'a', 7 - ( '8' - pos[1] ) );
// // }
// // 
// // class Step
// // {
// // 
// // };
// // 
// // /*ChessTable step( const Step& step )
// // {
// //     return ChessTable();
// // };*/
// // 
// // class ChessTable
// // {
// // public:
// //     ChessTable()
// //     {
// //         for( auto& line : m_table )
// //         {
// //             line.fill( '.' );
// //         }
// //     }
// //     bool operator == ( const ChessTable& table ) const
// //     {
// //         return m_table == table.m_table;
// //     }
// //     bool operator != ( const ChessTable& table ) const
// //     {
// //         return m_table != table.m_table;
// //     }
// // 
// //     void set( size_t x, size_t y, char c )
// //     {
// //         m_table[y][x] = c;
// //     }
// //     void set( const std::string& pos, char c )
// //     {
// //         auto p = from_string( pos );
// //         m_table[p.second][p.first] = c;
// //     }
// //     char get( size_t x, size_t y ) const
// //     {
// //         return m_table[y][x];
// //     }
// //     friend std::ostream& operator << ( std::ostream& os, const ChessTable& table )
// //     {
// //         os << "  +-----------------+\n";
// //         for( size_t r = 0; r < 8; ++r )
// //         {
// //             os << 8 - r << " | ";
// //             for( auto& c : table.m_table[8-r-1] )
// //             {
// //                 os << c << ' ';
// //             }
// //             os << "|\n";
// //         }
// //         os << "  +-----------------+\n";
// //         os << "    a b c d e f g h  \n\n";
// //         return os;
// //     }
// //     friend std::istream& operator >> ( std::istream& is, ChessTable& table )
// //     {
// //         std::string ignoreLine;
// //         std::getline( is, ignoreLine );
// //         for( size_t r = 0; r < 8; ++r )
// //         {
// //             is.ignore( 3 );
// //             
// //             for( auto& c : table.m_table[8-r-1] )
// //             {
// //                 is >> c;
// //             }
// //             std::getline( is, ignoreLine );
// //         }
// //         std::getline( is, ignoreLine );
// //         std::getline( is, ignoreLine );
// //         std::getline( is, ignoreLine );
// //         return is;
// //     }
// // private:
// //     std::array< std::array< char, 8 >, 8 > m_table;
// // };
// // 
// 
// class FEN
// {
// public:
//     ChessTable m_Table;
//     std::string m_rokerovka;
//     std::string m_step_rooks;
//     char m_who_step = 'w';
//     size_t m_count_step = 0;
//     size_t m_count_empty_step = 0;
// };
// 
// FEN FenFromStirng( const std::string& strFen )
// {
//     FEN fen;
// 
//     ChessTable ct;
// 
//     std::istringstream ifs( strFen );
// 
//     char c = 0;
//     size_t x = 0;
//     size_t y = 0;
// 
//     while( ifs.get( c ) )
//     {
//         if( c == '/' || c == ' ' )
//         {
//             x = 0;
//             ++y;
//             if( y == 8 )
//                 break;
// 
//             continue;
//         }
// 
//         if( std::isdigit( c ) )
//         {
//             for( size_t i = 0; i < size_t( c - '0' ); ++i, ++x )
//             {
//                 ct.set( x, 7 - y, '.' );
//             }
//         }
//         else
//         {
//             ct.set( x, 7 - y, c );
//             ++x;
//         }
//     }
// 
//     fen.m_Table = ct;
// 
//     ifs >> fen.m_who_step;
//     fen.m_who_step = std::tolower( fen.m_who_step );
//     ifs >> fen.m_rokerovka;
//     std::sort( fen.m_rokerovka.begin(), fen.m_rokerovka.end() );
// 
//     ifs >> fen.m_step_rooks;
//     if( fen.m_step_rooks.size() > 1 )
//         fen.m_step_rooks[0] = std::tolower( fen.m_step_rooks[0] );
// 
//     ifs >> fen.m_count_empty_step;
//     ifs >> fen.m_count_step;
// 
//     return fen;
//     return fen;
// }
// 
// std::string FenToString( const FEN& fen )
// {
//     std::ostringstream ofs;
//     for( size_t r = 0; r < 8; ++r )
//     {
//         size_t emptyPos = 0;
//         for( size_t c = 0; c < 8; ++c )
//         {
//             if( fen.m_Table.get( c, 7 - r ) == '.' )
//             {
//                 ++emptyPos;
//                 continue;
//             }
//             else
//             {
//                 if( emptyPos != 0 )
//                 {
//                     ofs << emptyPos;
//                     emptyPos = 0;
//                 }
//                 ofs << fen.m_Table.get( c, 7 - r );
//             }
//         }
//         if( emptyPos != 0 )
//             ofs << emptyPos;
// 
//         if( r != 7 )
//             ofs << '/';
//     }
// 
//     ofs << ' ';
//     ofs << fen.m_who_step << ' ';
//     ofs << fen.m_rokerovka << ' ';
//     ofs << fen.m_step_rooks << ' ';
//     ofs << fen.m_count_empty_step << ' ';
//     ofs << fen.m_count_step;
// 
//     return ofs.str();
// }
// 
// struct Step
// {
//     std::string m_step;
// };
// 
// FEN updateWhoStepAndCounter( const FEN& fen, const Step& step )
// {
//     FEN newFen = fen;
// 
//     if( newFen.m_who_step == 'b' )
//     {
//         newFen.m_count_step += 1;
//         newFen.m_who_step = 'w';
//     }
//     else
//     {
//         newFen.m_who_step = 'b';
//     }
//     
// 
//     return newFen;
// }
// 
// class FENP
// {
// public:
//     ChessTable Load( const std::string& path )
//     {
//         ChessTable ct;
// 
//         std::ifstream ifs( path );
//         if( !ifs )
//             throw std::runtime_error( "not open file " + path );
// 
//         char c = 0;
//         size_t x = 0;
//         size_t y = 0;
// 
//         while( ifs.get( c ) )
//         {
//             if( c == '/' )
//             {
//                 continue;
//             }
// 
//             if( std::isdigit( c ) )
//             {
//                 for( size_t i = 0; i < size_t( c - '0' ); ++i, ++x )
//                 {
//                     ct.set( x, 7 - y, '.' );
//                 }
//             }
//             else
//             {
//                 ct.set( x, 7-y, c );
//                 ++x;
//             }
// 
//             if( x == 8 )
//             {
//                 x = 0;
//                 ++y;
//                 if( y == 8 )
//                     break;
//             }
//         }
// 
// 
//         return ct;
//     }
//     FEN parse( const std::string& path )
//     {
//         FEN fen;
// 
//         ChessTable ct;
// 
//         std::ifstream ifs( path );
//         if( !ifs )
//             throw std::runtime_error( "not open file " + path );
// 
//         char c = 0;
//         size_t x = 0;
//         size_t y = 0;
// 
//         while( ifs.get( c ) )
//         {
//             if( c == '/' || c == ' ' )
//             {
//                 x = 0;
//                 ++y;
//                 if( y == 8 )
//                     break;
// 
//                 continue;
//             }
// 
//             if( std::isdigit( c ) )
//             {
//                 for( size_t i = 0; i < size_t( c - '0' ); ++i, ++x )
//                 {
//                     ct.set( x, 7 - y, '.' );
//                 }
//             }
//             else
//             {
//                 ct.set( x, 7 - y, c );
//                 ++x;
//             }
//         }
// 
//         fen.m_Table = ct;
// 
//         ifs >> fen.m_who_step;
//         fen.m_who_step = std::tolower( fen.m_who_step );
//         ifs >> fen.m_rokerovka;
//         std::sort( fen.m_rokerovka.begin(), fen.m_rokerovka.end() );
// 
//         ifs >> fen.m_step_rooks;
//         if( fen.m_step_rooks.size() > 1 )
//             fen.m_step_rooks[0] = std::tolower( fen.m_step_rooks[0] );
// 
//         ifs >> fen.m_count_empty_step;
//         ifs >> fen.m_count_step;
// 
//         return fen;
//     }
// 
//     void Save( const FEN& fen, std::ostream& ofs )
//     {
// //         std::ofstream ofs( path );
// //         if( !ofs )
// //             throw std::runtime_error( "not open file: " + path );
// 
//         for( size_t r = 0; r < 8; ++r )
//         {
//             size_t emptyPos = 0;
//             for( size_t c = 0; c < 8; ++c )
//             {
//                 if( fen.m_Table.get( c, 7 - r ) == '.' )
//                 {
//                     ++emptyPos;
//                     continue;
//                 }
//                 else
//                 {
//                     if( emptyPos != 0 )
//                     {
//                         ofs << emptyPos;
//                         emptyPos = 0;
//                     }
//                     ofs << fen.m_Table.get( c, 7 - r );
//                 }
//             }
//             if( emptyPos != 0 )
//                 ofs << emptyPos;
// 
//             if( r != 7 )
//                 ofs << '/';
//         }
// 
//         ofs << ' ';
//         ofs << fen.m_who_step << ' ';
//         ofs << fen.m_rokerovka << ' ';
//         ofs << fen.m_step_rooks << ' ';
//         ofs << fen.m_count_empty_step << ' ';
//         ofs << fen.m_count_step;
//     }
// 
//     void Save( const ChessTable& chessTable, const std::string& path )
//     {
//         std::ofstream ofs( path );
//         if( !ofs )
//             throw std::runtime_error( "not open file: " + path );
// 
//         for( size_t r = 0; r < 8; ++r )
//         {
//             for( size_t c = 0; c < 8; ++c )
//             {
//                 ofs << chessTable.get( c, 7 - r );
//             }
//         }
//     }
// private:
// };
// 
// enum
// {
//     whitePawns,
//     whiteKnights,
//     whiteBishops,
//     whiteRooks,
//     whiteQueens,
//     whiteKing,
// 
//     blackPawns,
//     blackKnights,
//     blackBishops,
//     blackRooks,
//     blackQueens,
//     blackKing
// };
// 
// std::array<char, 12> enum_to_char =
// {
//     'P', 'N', 'B', 'R', 'Q', 'K',
//     'p', 'n', 'b', 'r', 'q', 'k'
// };
// 
// std::map< char, size_t > char_to_enum =
// {
//     { 'P', whitePawns },
//     { 'N', whiteKnights },
//     { 'B', whiteBishops },
//     { 'R', whiteRooks },
//     { 'Q', whiteQueens },
//     { 'K', whiteKing },
//     { 'p', blackPawns },
//     { 'n', blackKnights },
//     { 'b', blackBishops },
//     { 'r', blackRooks },
//     { 'q', blackQueens },
//     { 'k', blackKing }
// };
// 
// std::array<uint64_t, 12> fen_to_bits( const ChessTable& chessTable )
// {
//     std::array<uint64_t, 12> res;
//     res.fill( 0 );
// 
//     for( size_t r = 0; r < 8; ++r )
//     {
//         for( size_t c = 0; c < 8; ++c )
//         {
//             if( auto iter = char_to_enum.find( chessTable.get( c, r ) ); iter != char_to_enum.end() )
//             {
//                 res[iter->second] |= static_cast<uint64_t>(1) << ( r * 8 + c );
//             }
//         }
//     }
// 
//     return res;
// }
// 
// 
// 
// class Party
// {
// 
// };