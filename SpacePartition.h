#ifndef SPACEPARTITION_H
#define SPACEPARTITION_H

#include <vector>
#include <Leap.h>

class SpacePartition
{
public:
    SpacePartition()
    {
        SpacePartition(xIntervals, yIntervals, zIntervals,
                       xMin, xMax, yMin, yMax, zMin, zMax);
    }

    SpacePartition(int xIntervals, int yIntervals, int zIntervals)
    {
        SpacePartition(xIntervals, yIntervals, zIntervals,
                       xMin, xMax, yMin, yMax, zMin, zMax);
    }

    SpacePartition(int xIntervals, int yIntervals, int zIntervals,
                   float xMin, float xMax, float yMin, float yMax,
                   float zMin, float zMax)
    {
        this->xIntervals = xIntervals;
        this->yIntervals = yIntervals;
        this->zIntervals = zIntervals;

        this->xMin = xMin;
        this->yMin = yMin;
        this->zMin = zMin;

        this->xMax = xMax;
        this->yMax = yMax;
        this->zMax = zMax;

        xPartition.reserve(xIntervals);
        yPartition.reserve(yIntervals);
        zPartition.reserve(zIntervals);

        float delta_x = (xMax - xMin) / (float)xIntervals;
        float delta_y = (yMax - yMin) / (float)yIntervals;
        float delta_z = (zMax - zMin) / (float)zIntervals;

        for (int i = 0; i <= xIntervals; ++i)
        {
            xPartition.push_back(xMin + (float)(delta_x * i));
        }
        for (int j = 0; j <= yIntervals; ++j)
        {
            yPartition.push_back(yMin + (float)(delta_y * j));
        }
        for (int k = 0; k <= zIntervals; ++k)
        {
            zPartition.push_back(zMin + (float)(delta_z * k));
        }
    }

    ~SpacePartition() {}

    int getXIndexFromFrame(Leap::Frame &frame, bool useRightHand)
    {
        for (auto hand : frame.hands())
        {
            if ((useRightHand) ? hand.isRight() :
                                 hand.isLeft())
            {
                float pos = hand.palmPosition().x;
                return findX(pos);
            }
        }
    }

    int getYIndexFromFrame(Leap::Frame &frame, bool useRightHand)
    {
        for (auto hand : frame.hands())
        {
            if ((useRightHand) ? hand.isRight() :
                                 hand.isLeft())
            {
                float pos = hand.palmPosition().y;
                return findY(pos);
            }
        }
    }

    int getZIndexFromFrame(Leap::Frame &frame, bool useRightHand)
    {
        for (auto hand : frame.hands())
        {
            if ((useRightHand) ? hand.isRight() :
                                 hand.isLeft())
            {
                float pos = hand.palmPosition().z;
                return findZ(pos);
            }
        }
    }

    int findX(float xPos)
    {
        int middle = (int)(xPartition.size() / 2);
        bool done = false;

        while (!done)
        {
            if (xPos > xPartition[middle] && xPos <= xPartition[middle + 1])
            {
                done = true;
            }
            else if (xPos > xPartition[middle] && xPos > xPartition[middle + 1])
            {
                middle = (int)((middle + xPartition.size()) / 2);
            }
            else if (xPos < xPartition[middle] && xPos < xPartition[middle - 1])
            {
                middle = (int)(middle / 2);
            }
            else if (xPos <= xPartition[middle] && xPos > xPartition[middle - 1])
            {
                done = true;
            }
            else if (xPos == xPartition[middle])
            {
                done = true;
            }
            else
            {
                done = true;
            }
        }

        return middle;
    }

    int findY(float yPos)
    {
        int middle = (int)(yPartition.size() / 2);
        bool done = false;

        while (!done)
        {
            if (yPos > yPartition[middle] && yPos <= yPartition[middle + 1])
            {
                done = true;
            }
            else if (yPos > yPartition[middle] && yPos > yPartition[middle + 1])
            {
                middle = (int)((middle + zPartition.size()) / 2);
            }
            else if (yPos < yPartition[middle] && yPos < yPartition[middle - 1])
            {
                middle = (int)(middle / 2);
            }
            else if (yPos <= yPartition[middle] && yPos > yPartition[middle - 1])
            {
                done = true;
            }
            else if (yPos == yPartition[middle])
            {
                done = true;
            }
            else
            {
                done = true;
            }
        }

        return middle;
    }

    int findZ(float zPos)
    {
        int middle = (int)(zPartition.size() / 2);
        bool done = false;

        while (!done)
        {
            if (zPos > zPartition[middle] && zPos <= zPartition[middle + 1])
            {
                done = true;
            }
            else if (zPos > zPartition[middle] && zPos > zPartition[middle + 1])
            {
                middle = (int)((middle + zPartition.size()) / 2);
            }
            else if (zPos < zPartition[middle] && zPos < zPartition[middle - 1])
            {
                middle = (int)(middle / 2);
            }
            else if (zPos <= zPartition[middle] && zPos > zPartition[middle - 1])
            {
                done = true;
            }
            else if (zPos == zPartition[middle])
            {
                done = true;
            }
            else
            {
                done = true;
            }
        }

        return middle;
    }
private:
    float yMin = 0;
    float yMax = 500;
    float xMin = -300;
    float xMax = 300;
    float zMin = -300;
    float zMax = 300;

    int yIntervals = 64;
    int xIntervals = 64;
    int zIntervals = 64;

    std::vector<float> yPartition;
    std::vector<float> xPartition;
    std::vector<float> zPartition;
};

#endif /* end of include guard: SPACEPARTITION_H */
