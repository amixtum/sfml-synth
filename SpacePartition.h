#ifndef SPACEPARTITION_H
#define SPACEPARTITION_H

#include <vector>
#include <Leap.h>

class SpacePartition
{
public:
    SpacePartition()
    {
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

    SpacePartition(int xIntervals, int yIntervals, int zIntervals) 
    {
        this->xIntervals = xIntervals;
        this->yIntervals = yIntervals;
        this->zIntervals = zIntervals;

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

        std::cout << yPartition.size();
    }


    int getXSubintervals()
    {
        return xPartition.size();
    }

    int getYSubintervals()
    {
        return yPartition.size();
    }

    int getZSubintervals()
    {
        return zPartition.size();
    }

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

        return -1; //error
    }

    int getYIndexFromFrame(Leap::Frame &frame, bool useRightHand)
    {
        for (Leap::Hand hand : frame.hands())
        {
            if ((useRightHand) ? hand.isRight() :
                                 hand.isLeft())
            {
                float pos = hand.palmPosition().y;
                return findY(pos);
            }
        }

        return -1; //error
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

        return -1; //error
    }

    int findX(float xPos)
    {
        return find(xPos, 0, xPartition.size() - 1, xPartition, xMin, xMax);
    }
    
    int findY(float yPos)
    {
        return find(yPos, 0, yPartition.size() - 1, yPartition, yMin, yMax);
    }

    int findZ(float zPos)
    {
        return find(zPos, 0, zPartition.size() - 1, zPartition, zMin, zMax);
    }


    int find(float pos, int first, int last, std::vector<float> &part, float min, float max)
    {
        int index = (int)((first + last) / 2);
        if (pos < min || pos >= max)
        {
            return -1;
        }
        else if (pos >= part[index] && pos < part[index + 1])
        {
            return index;
        }
        else if (pos > part[index] && pos > part[index + 1])
        {
            return find(pos, index + 1, last, part, min, max); 
        }
        else if (pos < part[index])
        {
            return find(pos, first, index - 1, part, min, max);
        }
        else
        {
            return -1;
        }

    } 
private:
    float yMin = 50;
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
