// dungeongenerator.cpp - Dungeon Escape
// ©2020 Squaregames Limited
//
// https://squaregames.info
// tim@squaregames.info
//
using namespace std;
#include <string.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
const int x_length = 128;
const int z_length = 128;
bool tiles[x_length][z_length];
bool randomPattern[12] = {true, false, false, true, false, true,
                          false, true, true, false, true, false};
int smoothFactor = 4;
int RandomFillMap(int offset)
{
    for (int z = 0; z < z_length; z++)
    {
        for (int x = 0; x < x_length; x++)
        {
            int randomSelection = rand() % 12;
            tiles[x][z] = randomPattern[(randomSelection + offset) % 12];
        }
    }
    return(0);
}
int NeighbouringWalls(int x, int z)
{
    int wallCount = 0;
    for (int neighbourZ = z - 1; neighbourZ <= z + 1; neighbourZ ++)
    {
        for (int neighbourX = x - 1; neighbourX <= x + 1; neighbourX ++)
        {
            if (neighbourX >= 0 && neighbourX < x_length && neighbourZ >= 0 && neighbourZ < z_length)
            {
                if (neighbourX != x || neighbourZ != z)
                {
                    if (tiles[neighbourX][neighbourZ])
                    {
                        wallCount ++;
                    }
                }
            }
            else
            {
                wallCount ++;
            }
        }
    }
    return (wallCount);
}
void SmoothMap(int smoothFactor)
{
    for (int factor = 0; factor < smoothFactor; factor++)
    {
        for (int z = 0; z < z_length; z++)
        {
            for (int x = 0; x < x_length; x++)
            {
                int neighbouringWallTiles = NeighbouringWalls(x , z);
                if (neighbouringWallTiles < smoothFactor)
                {
                    tiles[x][z] = false;
                }
                else
                if (neighbouringWallTiles > smoothFactor)
                {
                    tiles[x][z] = true;
                }
            }
        }
    }
}
void PlotMap()
{
    for (int z = 0; z < z_length; z++)
    {
        for (int x = 0; x < x_length; x++)
        {
            if (tiles[x][z])
            {
                cout << "0";
            }
            else
            {
                cout << "1";
            }
        }
        cout << endl;
    }
}
void PlotMapXtimes2()
{
    for (int z = 0; z < z_length; z++)
    {
        for (int x = 0; x < x_length; x++)
        {
            if (tiles[x][z])
            {
                cout << "##";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}
int main()
{
    int offset;
    cout << "Dungeon Escape: Caverns Generator" << endl;
    while (!false)
    {
        srand(unsigned (0));
        cout << "Enter 0-11 to offset for random factor" << endl << "?";
        cin >> offset;
        cout << endl;
        RandomFillMap(offset);
        SmoothMap(4);
        PlotMap();
        cout << endl;
        PlotMapXtimes2();
        cout << endl;
        cout << "Generated. - Random factor offset: " << offset << endl;
        cout << endl;
        cout << "Another cavern?" << endl;
    }
    return(0);
}
