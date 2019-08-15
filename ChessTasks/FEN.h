#pragma once

#include <string>

#include "Step.h"
#include "ChessTable.h"

struct FEN
{
    ChessTable m_chess_table;       ///< ��������� �����
    std::string m_castling;         ///< ���������
    std::string m_en_passant;       ///< ������ ����� �� +2 �������  
    char m_active_color = 'w';      ///< ��� ���
    size_t m_full_move = 1;         ///< ����� ������ �����
    size_t m_half_move = 0;         ///< ����� ��������� ��� ��������� ����� �����
};

bool operator == ( const FEN& lhs, const FEN& rhs );
bool operator != ( const FEN& lhs, const FEN& rhs );

FEN FenFromStirng( const std::string& strFen );
std::istream& operator >> ( std::istream& is, FEN& fen );

std::string FenToString( const FEN& fen );
std::ostream& operator << ( std::ostream& os, const FEN& fen );

bool isPawn( char c );
bool isKnight( char c );
bool isBishop( char c );
bool isRook( char c );
bool isQueen( char c );
bool isKing( char c );
bool isWhite( char c );
bool isBlack( char c );
char getColor( char c );

FEN updateActiveAndFullMove( const FEN& fen, const Step& step );
void updateActiveAndFullMove( FEN& fen, const Step& step );
FEN updateHalfMove( const FEN& fen, const Step& step );
void updateHalfMove( FEN& fen, const Step& step );
FEN actionStep( const FEN& fen, const Step& step );
void actionStep( FEN& fen, const Step& step );
FEN enPassant( const FEN& fen, const Step& step );
void enPassant( FEN& fen, const Step& step );
