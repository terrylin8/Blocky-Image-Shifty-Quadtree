#include "stats.h"

stats::stats(PNG &im)
{
    /* Your code here!! */

    //allocate memory for the vector
    int w = (int)im.width();
    int h = (int)im.height();

    sumRed = vector<vector<long>>(w, vector<long>(h));
    sumGreen = vector<vector<long>>(w, vector<long>(h));
    sumBlue = vector<vector<long>>(w, vector<long>(h));
    sumsqRed = vector<vector<long>>(w, vector<long>(h));
    sumsqGreen = vector<vector<long>>(w, vector<long>(h));
    sumsqBlue = vector<vector<long>>(w, vector<long>(h));

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            RGBAPixel *curr = im.getPixel(x, y);
            long r = (long)curr->r;
            long g = (long)curr->g;
            long b = (long)curr->b;

            if (x == 0 && y == 0)
            {
                sumRed[x][y] = r;
                sumGreen[x][y] = g;
                sumBlue[x][y] = b;
                sumsqRed[x][y] = r * r;
                sumsqGreen[x][y] = g * g;
                sumsqBlue[x][y] = b * b;
            }
            else if (x == 0)
            {
                sumRed[x][y] = sumRed[x][y - 1] + r;
                sumGreen[x][y] = sumGreen[x][y - 1] + g;
                sumBlue[x][y] = sumBlue[x][y - 1] + b;
                sumsqRed[x][y] = sumsqRed[x][y - 1] + r * r;
                sumsqGreen[x][y] = sumsqGreen[x][y - 1] + g * g;
                sumsqBlue[x][y] = sumsqBlue[x][y - 1] + b * b;
            }
            else if (y == 0)
            {
                sumRed[x][y] = sumRed[x - 1][y] + r;
                sumGreen[x][y] = sumGreen[x - 1][y] + g;
                sumBlue[x][y] = sumBlue[x - 1][y] + b;
                sumsqRed[x][y] = sumsqRed[x - 1][y] + r * r;
                sumsqGreen[x][y] = sumsqGreen[x - 1][y] + g * g;
                sumsqBlue[x][y] = sumsqBlue[x - 1][y] + b * b;
            }
            else
            {
                sumRed[x][y] =
                    sumRed[x - 1][y] + sumRed[x][y - 1] - sumRed[x - 1][y - 1] + r;
                sumGreen[x][y] = sumGreen[x - 1][y] + sumGreen[x][y - 1] -
                                 sumGreen[x - 1][y - 1] + g;
                sumBlue[x][y] =
                    sumBlue[x - 1][y] + sumBlue[x][y - 1] - sumBlue[x - 1][y - 1] + b;
                sumsqRed[x][y] = sumsqRed[x - 1][y] + sumsqRed[x][y - 1] -
                                 sumsqRed[x - 1][y - 1] + r * r;
                sumsqGreen[x][y] = sumsqGreen[x - 1][y] + sumsqGreen[x][y - 1] -
                                   sumsqGreen[x - 1][y - 1] + g * g;
                sumsqBlue[x][y] = sumsqBlue[x - 1][y] + sumsqBlue[x][y - 1] -
                                  sumsqBlue[x - 1][y - 1] + b * b;
            }
        }
    }
}

long stats::getSum(char channel, pair<int, int> ul, int w, int h)
{
    /* Your code here!! */
    long ret = 0;
    pair<int, int> lr;
    lr = make_pair(ul.first + w - 1, ul.second + h - 1);

    if (channel == 'r')
    {
        //the rect is upper left
        if (ul.first == 0 && ul.second == 0)
        {
            ret = sumRed[lr.first][lr.second];
        } //the rect is top row but to the right
        else if (ul.first > 0 && ul.second == 0)
        {
            ret = sumRed[lr.first][lr.second] - sumRed[ul.first - 1][lr.second];
        } //the rect is left col but to the buttom
        else if (ul.first == 0 && ul.second > 0)
        {
            ret = sumRed[lr.first][lr.second] - sumRed[lr.first][ul.second - 1];
        } //the rect has all three rects to the top, left, top left
        else
        {
            ret = sumRed[lr.first][lr.second] - sumRed[ul.first - 1][lr.second] - sumRed[lr.first][ul.second - 1] + sumRed[ul.first - 1][ul.second - 1];
        }
    }
    if (channel == 'g')
    {
        //the rect is upper left
        if (ul.first == 0 && ul.second == 0)
        {
            ret = sumGreen[lr.first][lr.second];
        } //the rect is top row but to the right
        else if (ul.first > 0 && ul.second == 0)
        {
            ret = sumGreen[lr.first][lr.second] - sumGreen[ul.first - 1][lr.second];
        } //the rect is left col but to the buttom
        else if (ul.first == 0 && ul.second > 0)
        {
            ret = sumGreen[lr.first][lr.second] - sumGreen[lr.first][ul.second - 1];
        } //the rect has all three rects to the top, left, top left
        else
        {
            ret = sumGreen[lr.first][lr.second] - sumGreen[ul.first - 1][lr.second] - sumGreen[lr.first][ul.second - 1] + sumGreen[ul.first - 1][ul.second - 1];
        }
    }
    if (channel == 'b')
    {
        //the rect is upper left
        if (ul.first == 0 && ul.second == 0)
        {
            ret = sumBlue[lr.first][lr.second];
        } //the rect is top row but to the right
        else if (ul.first > 0 && ul.second == 0)
        {
            ret = sumBlue[lr.first][lr.second] - sumBlue[ul.first - 1][lr.second];
        } //the rect is left col but to the buttom
        else if (ul.first == 0 && ul.second > 0)
        {
            ret = sumBlue[lr.first][lr.second] - sumBlue[lr.first][ul.second - 1];
        } //the rect has all three rects to the top, left, top left
        else
        {
            ret = sumBlue[lr.first][lr.second] - sumBlue[ul.first - 1][lr.second] - sumBlue[lr.first][ul.second - 1] + sumBlue[ul.first - 1][ul.second - 1];
        }
    }
    return ret;
}

long stats::getSumSq(char channel, pair<int, int> ul, int w, int h)
{
    /* Your code here!! */
    long ret = 0;
    pair<int, int> lr;
    lr = make_pair(ul.first + w - 1, ul.second + h - 1);

    if (channel == 'r')
    {
        //the rect is upper left
        if (ul.first == 0 && ul.second == 0)
        {
            ret = sumsqRed[lr.first][lr.second];
        } //the rect is top row but to the right
        else if (ul.first > 0 && ul.second == 0)
        {
            ret = sumsqRed[lr.first][lr.second] - sumsqRed[ul.first - 1][lr.second];
        } //the rect is left col but to the buttom
        else if (ul.first == 0 && ul.second > 0)
        {
            ret = sumsqRed[lr.first][lr.second] - sumsqRed[lr.first][ul.second - 1];
        } //the rect has all three rects to the top, left, top left
        else
        {
            ret = sumsqRed[lr.first][lr.second] - sumsqRed[ul.first - 1][lr.second] - sumsqRed[lr.first][ul.second - 1] + sumsqRed[ul.first - 1][ul.second - 1];
        }
    }
    if (channel == 'g')
    {
        //the rect is upper left
        if (ul.first == 0 && ul.second == 0)
        {
            ret = sumsqGreen[lr.first][lr.second];
        } //the rect is top row but to the right
        else if (ul.first > 0 && ul.second == 0)
        {
            ret = sumsqGreen[lr.first][lr.second] - sumsqGreen[ul.first - 1][lr.second];
        } //the rect is left col but to the buttom
        else if (ul.first == 0 && ul.second > 0)
        {
            ret = sumsqGreen[lr.first][lr.second] - sumsqGreen[lr.first][ul.second - 1];
        } //the rect has all three rects to the top, left, top left
        else
        {
            ret = sumsqGreen[lr.first][lr.second] - sumsqGreen[ul.first - 1][lr.second] - sumsqGreen[lr.first][ul.second - 1] + sumsqGreen[ul.first - 1][ul.second - 1];
        }
    }
    if (channel == 'b')
    {
        //the rect is upper left
        if (ul.first == 0 && ul.second == 0)
        {
            ret = sumsqBlue[lr.first][lr.second];
        } //the rect is top row but to the right
        else if (ul.first > 0 && ul.second == 0)
        {
            ret = sumsqBlue[lr.first][lr.second] - sumsqBlue[ul.first - 1][lr.second];
        } //the rect is left col but to the buttom
        else if (ul.first == 0 && ul.second > 0)
        {
            ret = sumsqBlue[lr.first][lr.second] - sumsqBlue[lr.first][ul.second - 1];
        } //the rect has all three rects to the top, left, top left
        else
        {
            ret = sumsqBlue[lr.first][lr.second] - sumsqBlue[ul.first - 1][lr.second] - sumsqBlue[lr.first][ul.second - 1] + sumsqBlue[ul.first - 1][ul.second - 1];
        }
    }
    return ret;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int w, int h)
{
    /* Your code here!! */
    if (w * h == 0)
    {
        return 0;
    }
    else
    { //sum of square - (sum)^2/area
        double r = getSumSq('r', ul, w, h) -
                   getSum('r', ul, w, h) * getSum('r', ul, w, h) / (double)(w * h);
        double g = getSumSq('g', ul, w, h) -
                   getSum('g', ul, w, h) * getSum('g', ul, w, h) / (double)(w * h);
        double b = getSumSq('b', ul, w, h) -
                   getSum('b', ul, w, h) * getSum('b', ul, w, h) / (double)(w * h);
        return (double)(r + g + b);
    }
}

RGBAPixel stats::getAvg(pair<int, int> ul, int w, int h)
{
    /* Your code here!! */
    if (w * h == 0)
    {
        return RGBAPixel(0, 0, 0);
    }
    else
    {
        //getSum of rect/area to get avg
        int r = (int)(getSum('r', ul, w, h)) / (w * h);
        int g = (int)(getSum('g', ul, w, h)) / (w * h);
        int b = (int)(getSum('b', ul, w, h)) / (w * h);
        return RGBAPixel(r, g, b);
    }
}