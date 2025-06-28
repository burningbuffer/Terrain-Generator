#include "Array2d.hpp"
#include <iostream>

Array2d::Array2d()
{
}

Array2d::~Array2d()
{
    free(m_pData);
}

void Array2d::InitArray(int width, int depth, void *pData)
{
    m_Width = width;
    m_Depth = depth;

    if(m_pData)
    {
        free(m_pData);
    }

    m_pData = (float*)pData;
}

void Array2d::InitArray(int width, int depth, float data)
{
    m_Width = width;
    m_Depth = depth;

    if(m_pData)
    {
        free(m_pData);
    }

    m_pData = (float*)malloc(width * depth * sizeof(float));

    for (int i = 0 ; i < width * depth ; i++) 
    {
        m_pData[i] = data;
    }
}

void Array2d::Delete()
{
    free(m_pData);
}

float Array2d::Get(int x, int y) const
{
    return m_pData[(x*m_Width)+y];
}

void Array2d::Set(float val, int x, int y)
{   
    m_pData[(x*m_Width)+y] = val;
}

void Array2d::Normalize(float minRange, float maxRange)
{
    float min = m_pData[0];
    float max = m_pData[0];

    for (int i = 1 ; i < m_Width * m_Depth ; i++) {
        if (m_pData[i] < min) {
            min = m_pData[i];
        }

        if (m_pData[i] > max) {
            max = m_pData[i];
        }
    }

    if (max <= min) {
        return;
    }

    float minMaxDelta = max - min;
    float minMaxRange = maxRange - minRange;

    for (int i = 0 ; i < m_Width * m_Depth; i++) 
    {
        m_pData[i] = ((m_pData[i] - min)/minMaxDelta) * minMaxRange + minRange;
    }
}

void Array2d::PrintArray()
{
    size_t size = m_Width * m_Depth - 1;
    for (int i = 0 ; i < size; i++) 
    {
        std::cout <<  m_pData[i] << " ";
    }
}
