// SkewbText.cpp : Defines the entry point for the console application.
//

/*
Build table row 0
Build table row 1
Build table row 2
Build table row 3
Build table row 4
Build table row 5
Build table row 6
Build table row 7
Build table row 8
Build table row 9
Build table row 10
Build table row 11
       1 combinations are  0 Moves from solved
       8 combinations are  1 Moves from solved
      48 combinations are  2 Moves from solved
     288 combinations are  3 Moves from solved
    1728 combinations are  4 Moves from solved
   10248 combinations are  5 Moves from solved
   59304 combinations are  6 Moves from solved
  315198 combinations are  7 Moves from solved
 1225483 combinations are  8 Moves from solved
 1455856 combinations are  9 Moves from solved
   81028 combinations are 10 Moves from solved
      90 combinations are 11 Moves from solved
One most moves combination is
01234567 012345 01012020
LUUUR BLLLD FUFLF FRRRD FDDDB BRBUB
    L U
     U
    U R
B L F U F R
 L   F   R
L D L F R D
    F D
     D
    D B
    B R
     B
    U B
Sequence is
D  L  B  D  L' R  D  B' L  R' L'
*/

#include <stdio.h>
#include <memory.h>
#include <conio.h>
#include <string.h>

#define NUMBER_CENTER_POSITIONS (6*5*4*3*2*1)
#define NUMBER_CORNER_POSITIONS (4*3*2*1)
#define NUMBER_ORIENTATIONS (3*3*3*3*3*3*3*3)
#define NUMBER_COMBINATIONS (NUMBER_CENTER_POSITIONS * NUMBER_CORNER_POSITIONS * NUMBER_ORIENTATIONS)

struct STableEntry
{
    unsigned char m_NumberMovesToSolved : 5;
    unsigned char m_Move : 3;
};

STableEntry g_Table[NUMBER_COMBINATIONS];

long long weight[8] = { 1, 100, 10000, 1000000, 100000000, 10000000000, 1000000000000, 100000000000000 };

void SetPiece(unsigned char* dst, unsigned char* src, unsigned long a, unsigned long b, unsigned long num)
{
    dst[a] = src[b];
    memcpy(src + b, src + b + 1, num - 1 - b);
}

struct SCube
{
    bool Init(char* s)
    {
        char* c1;
        char* c2;
        for (c1 = c2 = s; true; ++c1, ++c2)
        {
            while ((*c2 == ',') || (*c2 == ' '))
            {
                ++c2;
            }
            *c1 = *c2;
            if (*c1 == 0)
            {
                break;
            }
        }
        if ((c1 - s) != 30)
        {
            printf("Invalid cube, wrong number of pieces\n");
            return false;
        }

        char corner[8][6];
        char center[6];
        memset(corner, 0, sizeof(corner));
        memset(center, 0, sizeof(center));

        corner[0][3] = s[23];
        corner[0][4] = s[25];
        corner[0][5] = s[8];

        corner[1][3] = s[24];
        corner[1][4] = s[19];
        corner[1][5] = s[26];

        corner[2][3] = s[21];
        corner[2][4] = s[14];
        corner[2][5] = s[18];

        corner[3][3] = s[20];
        corner[3][4] = s[9];
        corner[3][5] = s[13];

        corner[4][3] = s[0];
        corner[4][4] = s[5];
        corner[4][5] = s[28];

        corner[5][3] = s[1];
        corner[5][4] = s[29];
        corner[5][5] = s[16];

        corner[6][3] = s[4];
        corner[6][4] = s[15];
        corner[6][5] = s[11];

        corner[7][3] = s[3];
        corner[7][4] = s[10];
        corner[7][5] = s[6];

        center[0] = s[22];
        center[1] = s[7];
        center[2] = s[12];
        center[3] = s[17];
        center[4] = s[27];
        center[5] = s[2];

        char d = 0;
        char b = 0;
        char l = 0;
        char r = 0;
        char u = 0;
        char f = 0;

        if ((corner[7][3] == corner[5][3]) || (corner[7][3] == corner[5][4]) || (corner[7][3] == corner[5][5]))
        {
            u = corner[7][3];
        }
        else if ((corner[7][4] == corner[5][3]) || (corner[7][4] == corner[5][4]) || (corner[7][4] == corner[5][5]))
        {
            u = corner[7][4];
        }
        else if ((corner[7][5] == corner[5][3]) || (corner[7][5] == corner[5][4]) || (corner[7][5] == corner[5][5]))
        {
            u = corner[7][5];
        }

        if ((corner[7][3] == corner[0][3]) || (corner[7][3] == corner[0][4]) || (corner[7][3] == corner[0][5]))
        {
            l = corner[7][3];
        }
        else if ((corner[7][4] == corner[0][3]) || (corner[7][4] == corner[0][4]) || (corner[7][4] == corner[0][5]))
        {
            l = corner[7][4];
        }
        else if ((corner[7][5] == corner[0][3]) || (corner[7][5] == corner[0][4]) || (corner[7][5] == corner[0][5]))
        {
            l = corner[7][5];
        }

        if ((corner[7][3] == corner[2][3]) || (corner[7][3] == corner[2][4]) || (corner[7][3] == corner[2][5]))
        {
            f = corner[7][3];
        }
        else if ((corner[7][4] == corner[2][3]) || (corner[7][4] == corner[2][4]) || (corner[7][4] == corner[2][5]))
        {
            f = corner[7][4];
        }
        else if ((corner[7][5] == corner[2][3]) || (corner[7][5] == corner[2][4]) || (corner[7][5] == corner[2][5]))
        {
            f = corner[7][5];
        }

        if ((corner[5][3] == corner[2][3]) || (corner[5][3] == corner[2][4]) || (corner[5][3] == corner[2][5]))
        {
            r = corner[5][3];
        }
        else if ((corner[5][4] == corner[2][3]) || (corner[5][4] == corner[2][4]) || (corner[5][4] == corner[2][5]))
        {
            r = corner[5][4];
        }
        else if ((corner[5][5] == corner[2][3]) || (corner[5][5] == corner[2][4]) || (corner[5][5] == corner[2][5]))
        {
            r = corner[5][5];
        }

        if ((corner[5][3] == corner[0][3]) || (corner[5][3] == corner[0][4]) || (corner[5][3] == corner[0][5]))
        {
            b = corner[5][3];
        }
        else if ((corner[5][4] == corner[0][3]) || (corner[5][4] == corner[0][4]) || (corner[5][4] == corner[0][5]))
        {
            b = corner[5][4];
        }
        else if ((corner[5][5] == corner[0][3]) || (corner[5][5] == corner[0][4]) || (corner[5][5] == corner[0][5]))
        {
            b = corner[5][5];
        }

        if ((corner[2][3] == corner[0][3]) || (corner[2][3] == corner[0][4]) || (corner[2][3] == corner[0][5]))
        {
            d = corner[2][3];
        }
        else if ((corner[2][4] == corner[0][3]) || (corner[2][4] == corner[0][4]) || (corner[2][4] == corner[0][5]))
        {
            d = corner[2][4];
        }
        else if ((corner[2][5] == corner[0][3]) || (corner[2][5] == corner[0][4]) || (corner[2][5] == corner[0][5]))
        {
            d = corner[2][5];
        }


        int i;
        for (i = 0; i < 8; )
        {
            int o;
            for (o = 0; o < 3; ++o)
            {
                if (corner[i][o + 3] == d)
                {
                    corner[i][o] = 'D';
                }
                else if (corner[i][o + 3] == b)
                {
                    corner[i][o] = 'B';
                }
                else if (corner[i][o + 3] == l)
                {
                    corner[i][o] = 'L';
                }
                else if (corner[i][o + 3] == r)
                {
                    corner[i][o] = 'R';
                }
                else if (corner[i][o + 3] == f)
                {
                    corner[i][o] = 'F';
                }
                else if (corner[i][o + 3] == u)
                {
                    corner[i][o] = 'U';
                }
            }

            if (corner[i][0] == 'D' && corner[i][2] == 'B')
            {
                if (corner[i][1] != 'R')
                {
                    printf("Invalid cube, no such piece\n");
                    return false;
                }
                m_CornerPieces[i] = 1;
                m_Orientations[i] = 0;
            }
            if (corner[i][1] == 'D' && corner[i][0] == 'B')
            {
                if (corner[i][2] != 'R')
                {
                    printf("Invalid cube, no such piece\n");
                    return false;
                }
                m_CornerPieces[i] = 1;
                m_Orientations[i] = 1;
            }
            if (corner[i][2] == 'D' && corner[i][1] == 'B')
            {
                if (corner[i][0] != 'R')
                {
                    printf("Invalid cube, no such piece\n");
                    return false;
                }
                m_CornerPieces[i] = 1;
                m_Orientations[i] = 2;
            }

            if (corner[i][0] == 'D' && corner[i][1] == 'L')
            {
                if (corner[i][2] != 'F')
                {
                    printf("Invalid cube, no such piece\n");
                    return false;
                }
                m_CornerPieces[i] = 3;
                m_Orientations[i] = 0;
            }
            if (corner[i][1] == 'D' && corner[i][2] == 'L')
            {
                if (corner[i][0] != 'F')
                {
                    printf("Invalid cube, no such piece\n");
                    return false;
                }
                m_CornerPieces[i] = 3;
                m_Orientations[i] = 1;
            }
            if (corner[i][2] == 'D' && corner[i][0] == 'L')
            {
                if (corner[i][1] != 'F')
                {
                    printf("Invalid cube, no such piece\n");
                    return false;
                }
                m_CornerPieces[i] = 3;
                m_Orientations[i] = 2;
            }

            if (corner[i][1] == 'L' && corner[i][2] == 'B')
            {
                if (corner[i][0] != 'U')
                {
                    printf("Invalid cube, no such piece\n");
                    return false;
                }
                m_CornerPieces[i] = 4;
                m_Orientations[i] = 0;
            }
            if (corner[i][2] == 'L' && corner[i][0] == 'B')
            {
                if (corner[i][1] != 'U')
                {
                    printf("Invalid cube, no such piece\n");
                    return false;
                }
                m_CornerPieces[i] = 4;
                m_Orientations[i] = 1;
            }
            if (corner[i][0] == 'L' && corner[i][1] == 'B')
            {
                if (corner[i][2] != 'U')
                {
                    printf("Invalid cube, no such piece\n");
                    return false;
                }
                m_CornerPieces[i] = 4;
                m_Orientations[i] = 2;
            }

            if (corner[i][0] == 'D' && corner[i][1] == 'B' && corner[i][2] == 'L')
            {
                m_CornerPieces[i] = 0;
                m_Orientations[i] = 0;
            }
            else if (corner[i][1] == 'D' && corner[i][2] == 'B' && corner[i][0] == 'L')
            {
                m_CornerPieces[i] = 0;
                m_Orientations[i] = 1;
            }
            else if (corner[i][2] == 'D' && corner[i][0] == 'B' && corner[i][1] == 'L')
            {
                m_CornerPieces[i] = 0;
                m_Orientations[i] = 2;
            }
            else if (corner[i][0] == 'D' && corner[i][1] == 'R' && corner[i][2] == 'B')
            {
                m_CornerPieces[i] = 1;
                m_Orientations[i] = 0;
            }
            else if (corner[i][1] == 'D' && corner[i][2] == 'R' && corner[i][0] == 'B')
            {
                m_CornerPieces[i] = 1;
                m_Orientations[i] = 1;
            }
            else if (corner[i][2] == 'D' && corner[i][0] == 'R' && corner[i][1] == 'B')
            {
                m_CornerPieces[i] = 1;
                m_Orientations[i] = 2;
            }
            else if (corner[i][0] == 'D' && corner[i][1] == 'F' && corner[i][2] == 'R')
            {
                m_CornerPieces[i] = 2;
                m_Orientations[i] = 0;
            }
            else if (corner[i][1] == 'D' && corner[i][2] == 'F' && corner[i][0] == 'R')
            {
                m_CornerPieces[i] = 2;
                m_Orientations[i] = 1;
            }
            else if (corner[i][2] == 'D' && corner[i][0] == 'F' && corner[i][1] == 'R')
            {
                m_CornerPieces[i] = 2;
                m_Orientations[i] = 2;
            }
            else if (corner[i][0] == 'D' && corner[i][1] == 'L' && corner[i][2] == 'F')
            {
                m_CornerPieces[i] = 3;
                m_Orientations[i] = 0;
            }
            else if (corner[i][1] == 'D' && corner[i][2] == 'L' && corner[i][0] == 'F')
            {
                m_CornerPieces[i] = 3;
                m_Orientations[i] = 1;
            }
            else if (corner[i][2] == 'D' && corner[i][0] == 'L' && corner[i][1] == 'F')
            {
                m_CornerPieces[i] = 3;
                m_Orientations[i] = 2;
            }
            else if (corner[i][0] == 'U' && corner[i][1] == 'L' && corner[i][2] == 'B')
            {
                m_CornerPieces[i] = 4;
                m_Orientations[i] = 0;
            }
            else if (corner[i][1] == 'U' && corner[i][2] == 'L' && corner[i][0] == 'B')
            {
                m_CornerPieces[i] = 4;
                m_Orientations[i] = 1;
            }
            else if (corner[i][2] == 'U' && corner[i][0] == 'L' && corner[i][1] == 'B')
            {
                m_CornerPieces[i] = 4;
                m_Orientations[i] = 2;
            }
            else if (corner[i][0] == 'U' && corner[i][1] == 'B' && corner[i][2] == 'R')
            {
                m_CornerPieces[i] = 5;
                m_Orientations[i] = 0;
            }
            else if (corner[i][1] == 'U' && corner[i][2] == 'B' && corner[i][0] == 'R')
            {
                m_CornerPieces[i] = 5;
                m_Orientations[i] = 1;
            }
            else if (corner[i][2] == 'U' && corner[i][0] == 'B' && corner[i][1] == 'R')
            {
                m_CornerPieces[i] = 5;
                m_Orientations[i] = 2;
            }
            else if (corner[i][0] == 'U' && corner[i][1] == 'R' && corner[i][2] == 'F')
            {
                m_CornerPieces[i] = 6;
                m_Orientations[i] = 0;
            }
            else if (corner[i][1] == 'U' && corner[i][2] == 'R' && corner[i][0] == 'F')
            {
                m_CornerPieces[i] = 6;
                m_Orientations[i] = 1;
            }
            else if (corner[i][2] == 'U' && corner[i][0] == 'R' && corner[i][1] == 'F')
            {
                m_CornerPieces[i] = 6;
                m_Orientations[i] = 2;
            }
            else if (corner[i][0] == 'U' && corner[i][1] == 'F' && corner[i][2] == 'L')
            {
                m_CornerPieces[i] = 7;
                m_Orientations[i] = 0;
            }
            else if (corner[i][1] == 'U' && corner[i][2] == 'F' && corner[i][0] == 'L')
            {
                m_CornerPieces[i] = 7;
                m_Orientations[i] = 1;
            }
            else if (corner[i][2] == 'U' && corner[i][0] == 'F' && corner[i][1] == 'L')
            {
                m_CornerPieces[i] = 7;
                m_Orientations[i] = 2;
            }
            else
            {
                printf("Invalid cube, invalid pieces\n");
                return false;
            }
            ++i;
        }

        for (i = 0; i < 6; ++i)
        {
            if (center[i] == d) m_CenterPieces[i] = 0;
            else if (center[i] == l) m_CenterPieces[i] = 1;
            else if (center[i] == f) m_CenterPieces[i] = 2;
            else if (center[i] == r) m_CenterPieces[i] = 3;
            else if (center[i] == b) m_CenterPieces[i] = 4;
            else if (center[i] == u) m_CenterPieces[i] = 5;
            else
            {
                printf("Invalid cube, invalid pieces\n");
                return false;
            }
        }
        int orientation = 0;
        for (i = 0; i < 8; ++i)
        {
            orientation += m_Orientations[i];
        }
        return true;
    }

    SCube(unsigned long lIndex)
    {
        unsigned long lOrientation1 = lIndex % NUMBER_ORIENTATIONS;
        unsigned long lOrientation = lOrientation1;
        m_Orientations[7] = (unsigned char)(lOrientation % 3);
        m_Orientations[6] = (unsigned char)((lOrientation /= 3) % 3);
        m_Orientations[5] = (unsigned char)((lOrientation /= 3) % 3);
        m_Orientations[4] = (unsigned char)((lOrientation /= 3) % 3);
        m_Orientations[3] = (unsigned char)((lOrientation /= 3) % 3);
        m_Orientations[2] = (unsigned char)((lOrientation /= 3) % 3);
        m_Orientations[1] = (unsigned char)((lOrientation /= 3) % 3);
        m_Orientations[0] = (unsigned char)(lOrientation / 3);

        unsigned char cornerpieces[8] = { 6, 4, 3, 1 };
        unsigned char order[4];

        unsigned long lCornerPosition = (lIndex / NUMBER_ORIENTATIONS) % NUMBER_CORNER_POSITIONS;

        SetPiece(order, cornerpieces, 3, lCornerPosition / (3 * 2), 4);
        SetPiece(order, cornerpieces, 2, (lCornerPosition / 2) % 3, 4);
        SetPiece(order, cornerpieces, 1, lCornerPosition % 2, 4);
        SetPiece(order, cornerpieces, 0, 0, 4);

        m_CornerPieces[0] = 0;
        m_CornerPieces[1] = order[0];
        m_CornerPieces[2] = 2;
        m_CornerPieces[3] = order[1];
        m_CornerPieces[4] = order[2];
        m_CornerPieces[5] = 5;
        m_CornerPieces[6] = order[3];
        m_CornerPieces[7] = 7;

        unsigned char centerpieces[6] = { 5, 4, 3, 2, 1, 0 };

        unsigned long lCenterPosition = lIndex / (NUMBER_ORIENTATIONS * NUMBER_CORNER_POSITIONS);

        SetPiece(m_CenterPieces, centerpieces, 5, (lCenterPosition / (5 * 4 * 3 * 2)) % 6, 6);
        SetPiece(m_CenterPieces, centerpieces, 4, (lCenterPosition / (4 * 3 * 2)) % 5, 6);
        SetPiece(m_CenterPieces, centerpieces, 3, (lCenterPosition / (3 * 2)) % 4, 6);
        SetPiece(m_CenterPieces, centerpieces, 2, (lCenterPosition / 2) % 3, 6);
        SetPiece(m_CenterPieces, centerpieces, 1, lCenterPosition % 2, 6);
        SetPiece(m_CenterPieces, centerpieces, 0, 0, 6);
    }

    unsigned long GetIndex()
    {
        unsigned long lCenterPosition = 0;
        unsigned long i;
        for (i = 5; i > 0; --i)
        {
            unsigned count = 0;
            unsigned long o;
            for (o = 0; o < i; ++o)
            {
                if (m_CenterPieces[o] > m_CenterPieces[i])
                {
                    ++count;
                }
            }
            lCenterPosition *= (i + 1);
            lCenterPosition += count;
        }

        unsigned char cornerpieces[4] = { m_CornerPieces[1], m_CornerPieces[3], m_CornerPieces[4], m_CornerPieces[6] };
        unsigned long lCornerPosition = 0;
        for (i = 3; i > 0; --i)
        {
            unsigned count = 0;
            unsigned long o;
            for (o = 0; o < i; ++o)
            {
                if (cornerpieces[o] > cornerpieces[i])
                {
                    ++count;
                }
            }
            lCornerPosition *= (i + 1);
            lCornerPosition += count;
        }

        unsigned long lOrientation = 0;
        for (i = 0; i < 8; ++i)
        {
            lOrientation *= 3;
            lOrientation += m_Orientations[i];
        }
        return ((lCenterPosition * NUMBER_CORNER_POSITIONS) + lCornerPosition) * NUMBER_ORIENTATIONS + lOrientation;
    }

    void TwistRight()
    {
        unsigned char temp;
        temp = m_CornerPieces[4];
        m_CornerPieces[4] = m_CornerPieces[6];
        m_CornerPieces[6] = m_CornerPieces[1];
        m_CornerPieces[1] = temp;

        temp = m_Orientations[4];
        m_Orientations[4] = (m_Orientations[6] + 2) % 3;
        m_Orientations[6] = (m_Orientations[1] + 2) % 3;
        m_Orientations[1] = (temp + 2) % 3;

        m_Orientations[5] = (m_Orientations[5] + 1) % 3;

        temp = m_CenterPieces[5];
        m_CenterPieces[5] = m_CenterPieces[3];
        m_CenterPieces[3] = m_CenterPieces[4];
        m_CenterPieces[4] = temp;
    }

    void TwistRightPrime()
    {
        unsigned char temp;
        temp = m_CornerPieces[4];
        m_CornerPieces[4] = m_CornerPieces[1];
        m_CornerPieces[1] = m_CornerPieces[6];
        m_CornerPieces[6] = temp;

        temp = m_Orientations[4];
        m_Orientations[4] = (m_Orientations[1] + 1) % 3;
        m_Orientations[1] = (m_Orientations[6] + 1) % 3;
        m_Orientations[6] = (temp + 1) % 3;

        m_Orientations[5] = (m_Orientations[5] + 2) % 3;

        temp = m_CenterPieces[5];
        m_CenterPieces[5] = m_CenterPieces[4];
        m_CenterPieces[4] = m_CenterPieces[3];
        m_CenterPieces[3] = temp;
    }

    void TwistLeft()
    {
        unsigned char temp;
        temp = m_CornerPieces[4];
        m_CornerPieces[4] = m_CornerPieces[3];
        m_CornerPieces[3] = m_CornerPieces[6];
        m_CornerPieces[6] = temp;

        temp = m_Orientations[4];
        m_Orientations[4] = (m_Orientations[3] + 2) % 3;
        m_Orientations[3] = (m_Orientations[6] + 2) % 3;
        m_Orientations[6] = (temp + 2) % 3;

        m_Orientations[7] = (m_Orientations[7] + 1) % 3;

        temp = m_CenterPieces[5];
        m_CenterPieces[5] = m_CenterPieces[1];
        m_CenterPieces[1] = m_CenterPieces[2];
        m_CenterPieces[2] = temp;
    }

    void TwistLeftPrime()
    {
        unsigned char temp;
        temp = m_CornerPieces[4];
        m_CornerPieces[4] = m_CornerPieces[6];
        m_CornerPieces[6] = m_CornerPieces[3];
        m_CornerPieces[3] = temp;

        temp = m_Orientations[4];
        m_Orientations[4] = (m_Orientations[6] + 1) % 3;
        m_Orientations[6] = (m_Orientations[3] + 1) % 3;
        m_Orientations[3] = (temp + 1) % 3;

        m_Orientations[7] = (m_Orientations[7] + 2) % 3;

        temp = m_CenterPieces[5];
        m_CenterPieces[5] = m_CenterPieces[2];
        m_CenterPieces[2] = m_CenterPieces[1];
        m_CenterPieces[1] = temp;
    }

    void TwistDown()
    {
        unsigned char temp;
        temp = m_CornerPieces[6];
        m_CornerPieces[6] = m_CornerPieces[3];
        m_CornerPieces[3] = m_CornerPieces[1];
        m_CornerPieces[1] = temp;

        temp = m_Orientations[6];
        m_Orientations[6] = (m_Orientations[3] + 2) % 3;
        m_Orientations[3] = (m_Orientations[1] + 2) % 3;
        m_Orientations[1] = (temp + 2) % 3;

        m_Orientations[2] = (m_Orientations[2] + 1) % 3;

        temp = m_CenterPieces[2];
        m_CenterPieces[2] = m_CenterPieces[0];
        m_CenterPieces[0] = m_CenterPieces[3];
        m_CenterPieces[3] = temp;
    }

    void TwistDownPrime()
    {
        unsigned char temp;
        temp = m_CornerPieces[6];
        m_CornerPieces[6] = m_CornerPieces[1];
        m_CornerPieces[1] = m_CornerPieces[3];
        m_CornerPieces[3] = temp;

        temp = m_Orientations[6];
        m_Orientations[6] = (m_Orientations[1] + 1) % 3;
        m_Orientations[1] = (m_Orientations[3] + 1) % 3;
        m_Orientations[3] = (temp + 1) % 3;

        m_Orientations[2] = (m_Orientations[2] + 2) % 3;

        temp = m_CenterPieces[2];
        m_CenterPieces[2] = m_CenterPieces[3];
        m_CenterPieces[3] = m_CenterPieces[0];
        m_CenterPieces[0] = temp;
    }

    void TwistBack()
    {
        unsigned char temp;
        temp = m_CornerPieces[4];
        m_CornerPieces[4] = m_CornerPieces[1];
        m_CornerPieces[1] = m_CornerPieces[3];
        m_CornerPieces[3] = temp;

        temp = m_Orientations[4];
        m_Orientations[4] = (m_Orientations[1] + 2) % 3;
        m_Orientations[1] = (m_Orientations[3] + 2) % 3;
        m_Orientations[3] = (temp + 2) % 3;

        m_Orientations[0] = (m_Orientations[0] + 1) % 3;

        temp = m_CenterPieces[4];
        m_CenterPieces[4] = m_CenterPieces[0];
        m_CenterPieces[0] = m_CenterPieces[1];
        m_CenterPieces[1] = temp;
    }

    void TwistBackPrime()
    {
        unsigned char temp;
        temp = m_CornerPieces[4];
        m_CornerPieces[4] = m_CornerPieces[3];
        m_CornerPieces[3] = m_CornerPieces[1];
        m_CornerPieces[1] = temp;

        temp = m_Orientations[4];
        m_Orientations[4] = (m_Orientations[3] + 1) % 3;
        m_Orientations[3] = (m_Orientations[1] + 1) % 3;
        m_Orientations[1] = (temp + 1) % 3;

        m_Orientations[0] = (m_Orientations[0] + 2) % 3;

        temp = m_CenterPieces[4];
        m_CenterPieces[4] = m_CenterPieces[1];
        m_CenterPieces[1] = m_CenterPieces[0];
        m_CenterPieces[0] = temp;
    }

    void Print()
    {
        char cube[14][36];
        memset(cube, ' ', sizeof(cube));
        cube[0][35] = 0;
        cube[1][35] = 0;
        cube[2][35] = 0;
        cube[3][35] = 0;
        cube[4][35] = 0;
        cube[5][35] = 0;
        cube[6][35] = 0;
        cube[7][35] = 0;
        cube[8][35] = 0;
        cube[9][35] = 0;
        cube[10][35] = 0;
        cube[11][35] = 0;
        cube[12][35] = 0;
        cube[13][35] = 0;
        unsigned char i;
        for (i = 0; i < 8; ++i)
        {
            cube[0][i] = m_CornerPieces[i] + '0';
            cube[0][16 + i] = m_Orientations[i] + '0';
            char piece[3];
            switch (m_CornerPieces[i])
            {
            case 0: piece[0] = 'D'; piece[1] = 'B'; piece[2] = 'L'; break;
            case 1: piece[0] = 'D'; piece[1] = 'R'; piece[2] = 'B'; break;
            case 2: piece[0] = 'D'; piece[1] = 'F'; piece[2] = 'R'; break;
            case 3: piece[0] = 'D'; piece[1] = 'L'; piece[2] = 'F'; break;
            case 4: piece[0] = 'U'; piece[1] = 'L'; piece[2] = 'B'; break;
            case 5: piece[0] = 'U'; piece[1] = 'B'; piece[2] = 'R'; break;
            case 6: piece[0] = 'U'; piece[1] = 'R'; piece[2] = 'F'; break;
            case 7: piece[0] = 'U'; piece[1] = 'F'; piece[2] = 'L'; break;
            }
            char temp;
            switch (m_Orientations[i])
            {
            case 0: break;
            case 1: temp = piece[0]; piece[0] = piece[2]; piece[2] = piece[1]; piece[1] = temp; break;
            case 2: temp = piece[0]; piece[0] = piece[1]; piece[1] = piece[2]; piece[2] = temp; break;
            }
            switch (i)
            {
            case 0:
                cube[1][27] = cube[10][4] = piece[0];
                cube[1][30] = cube[11][4] = piece[1];
                cube[1][9] = cube[7][0] = piece[2];
                break;
            case 1:
                cube[1][28] = cube[10][6] = piece[0];
                cube[1][22] = cube[7][10] = piece[1];
                cube[1][31] = cube[11][6] = piece[2];
                break;
            case 2:
                cube[1][25] = cube[8][6] = piece[0];
                cube[1][16] = cube[7][6] = piece[1];
                cube[1][21] = cube[7][8] = piece[2];
                break;
            case 3:
                cube[1][24] = cube[8][4] = piece[0];
                cube[1][10] = cube[7][2] = piece[1];
                cube[1][15] = cube[7][4] = piece[2];
                break;
            case 4:
                cube[1][0] = cube[2][4] = piece[0];
                cube[1][6] = cube[5][0] = piece[1];
                cube[1][33] = cube[13][4] = piece[2];
                break;
            case 5:
                cube[1][1] = cube[2][6] = piece[0];
                cube[1][34] = cube[13][6] = piece[1];
                cube[1][19] = cube[5][10] = piece[2];
                break;
            case 6:
                cube[1][4] = cube[4][6] = piece[0];
                cube[1][18] = cube[5][8] = piece[1];
                cube[1][13] = cube[5][6] = piece[2];
                break;
            case 7:
                cube[1][3] = cube[4][4] = piece[0];
                cube[1][12] = cube[5][4] = piece[1];
                cube[1][7] = cube[5][2] = piece[2];
                break;
            }
        }
        for (i = 0; i < 6; ++i)
        {
            cube[0][9 + i] = m_CenterPieces[i] + '0';
            char piece = 0;
            switch (m_CenterPieces[i])
            {
            case 0: piece = 'D'; break;
            case 1: piece = 'L'; break;
            case 2: piece = 'F'; break;
            case 3: piece = 'R'; break;
            case 4: piece = 'B'; break;
            case 5: piece = 'U'; break;
            }
            switch (i)
            {
            case 0: cube[1][26] = cube[9][5] = piece; break;
            case 1: cube[1][8] = cube[6][1] = piece; break;
            case 2: cube[1][14] = cube[6][5] = piece; break;
            case 3: cube[1][20] = cube[6][9] = piece; break;
            case 4: cube[1][32] = cube[12][5] = piece; break;
            case 5: cube[1][2] = cube[3][5] = piece; break;
            }
        }
        printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
            cube[0], cube[1], cube[2], cube[3], cube[4], cube[5], cube[6],
            cube[7], cube[8], cube[9], cube[10], cube[11], cube[12], cube[13]);
    }

    void PrintAndPlayMove(int move)
    {
        switch (move)
        {
        case 0: printf("L  "); break;
        case 1: printf("R  "); break;
        case 2: printf("B  "); break;
        case 3: printf("D  "); break;
        case 4: printf("L' "); break;
        case 5: printf("R' "); break;
        case 6: printf("B' "); break;
        case 7: printf("D' "); break;
        }
        PlayMove(move);
    }

    void PlayMove(int move)
    {
        switch (move)
        {
        case 0: TwistLeft();        break;
        case 1: TwistRight();       break;
        case 2: TwistBack();        break;
        case 3: TwistDown();        break;
        case 4: TwistLeftPrime();   break;
        case 5: TwistRightPrime();  break;
        case 6: TwistBackPrime();   break;
        case 7: TwistDownPrime();   break;
        }
    }

    unsigned char m_CornerPieces[8];
    unsigned char m_CenterPieces[6];
    unsigned char m_Orientations[8];
};

long long MoveTotal(unsigned long index)
{
    long long moveTotal = 0;
    SCube cube(index);

    while (true)
    {
        if (g_Table[index].m_NumberMovesToSolved == 0)
            break;
        cube.PlayMove(g_Table[index].m_Move);
        moveTotal += weight[g_Table[index].m_Move];

        index = cube.GetIndex();
    }
    return moveTotal;
}

void BuildTable()
{
    FILE* fp = NULL;
    //fopen_s(&fp, "Table.dat", "rb");
    //if (fp != NULL)
    //{
    //    if (fread(g_Table, sizeof(g_Table), 1, fp) == 1)
    //    {
    //        fclose(fp);
    //        return;
    //    }
    //    fclose(fp);
    //}
    memset(g_Table, 0xFF, sizeof(g_Table));
    g_Table[0].m_NumberMovesToSolved = 0;
    g_Table[0].m_Move = 0;

    unsigned short i;
    for (i = 0; true; ++i)
    {
        printf("Build table row %i\n", i);
        bool bFound = false;
        unsigned long o;
        for (o = 0; o < NUMBER_COMBINATIONS; ++o)
        {
            if (g_Table[o].m_NumberMovesToSolved == i)
            {
                long long moveTotal = MoveTotal(o);

                unsigned char move;
                for (move = 0; move < 8; ++move)
                {
                    SCube cube(o);
                    cube.PlayMove(move ^ 4);
                    unsigned long p = cube.GetIndex();

                    if (g_Table[p].m_NumberMovesToSolved == 0x1F)
                    {
                        g_Table[p].m_NumberMovesToSolved = i + 1;
                        g_Table[p].m_Move = move;
                        bFound = true;
                    }
                    else if (g_Table[p].m_NumberMovesToSolved == i + 1)
                    {
                        long long moveTotalP = MoveTotal(p);
                        if (moveTotalP > (moveTotal + weight[move]))
                        {
//                            printf("%lli %lli\n", moveTotalP, moveTotal + weight[move]);
                            g_Table[p].m_NumberMovesToSolved = i + 1;
                            g_Table[p].m_Move = move;
                            bFound = true;
                        }
                    }
                    SCube cube2(p);
                    if (memcmp(&cube2, &cube, sizeof(cube)) != 0)
                    {
                        printf("Error\n");
                    }

                }
            }
        }
        if (!bFound)
        {
            break;
        }
    }
    fp = NULL;
    fopen_s(&fp, "Table.dat", "wb");
    if (fp != NULL)
    {
        fwrite(g_Table, sizeof(g_Table), 1, fp);
        fclose(fp);
    }
}

int main(int argc, char* argv[])
{
    BuildTable();

    unsigned long max = 0;
    unsigned long i;
    unsigned long combo = 0;
    for (i = 0; i <= max; ++i)
    {
        unsigned long count = 0;
        unsigned long o;
        for (o = 0; o < NUMBER_COMBINATIONS; ++o)
        {
            if ((g_Table[o].m_NumberMovesToSolved) > max && (g_Table[o].m_NumberMovesToSolved != 31))
            {
                max = g_Table[o].m_NumberMovesToSolved;
                combo = o;
            }
            if (g_Table[o].m_NumberMovesToSolved == i)
            {
                ++count;
            }
        }
        printf("%8i combinations are %2i Moves from solved\n", count, i);
    }

    printf("One most moves combination is\n");
    {
        SCube cube(combo);
        cube.Print();
        printf("\n");

        printf("Sequence is\n");
        while (g_Table[cube.GetIndex()].m_NumberMovesToSolved != 0)
        {
            cube.PrintAndPlayMove(g_Table[cube.GetIndex()].m_Move);
        }
        printf("\n");
    }
    printf("\n");

    bool bShowAllStage = false;
    while (true)
    {
        printf("Enter cube: (or 'exit')\n");
        char s[512];
        scanf_s("%s", s, 512);
        if (_strnicmp(s, "exit", 4) == 0)
        {
            break;
        }
        if (_strnicmp(s, "show=all", 8) == 0)
        {
            bShowAllStage = true;
            continue;
        }
        if (_strnicmp(s, "show=none", 9) == 0)
        {
            bShowAllStage = false;
            continue;
        }

        SCube cube(0);
        if (!cube.Init(s))
        {
            continue;
        }
        printf("Solution\n");
        max = cube.GetIndex();
        if (bShowAllStage)
        {
            printf("   ");
            cube.Print();
            printf("\n");
        }
        i = 0;
        while (g_Table[cube.GetIndex()].m_NumberMovesToSolved != 0)
        {
            cube.PrintAndPlayMove(g_Table[cube.GetIndex()].m_Move);
            if (bShowAllStage)
            {
                cube.Print();
                printf("\n");
            }
            ++i;
        }
        printf(" Total Move = %i\n", i);
    }
    return 0;
}

