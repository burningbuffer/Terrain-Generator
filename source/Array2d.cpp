#include "Array2d.hpp"
#include <iostream>
#include <assert.h>

Array2d::Array2d(){}

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

float Array2d::Get(int x, int z) const
{
    int index = (x * m_Depth) + z;

    if(index < 0 || index > (m_Width * m_Depth) - 1)
    {
        assert("ERROR: Array2d - Get Index out of bounds bro");
    }
    
    return m_pData[index];
}

void Array2d::Set(float val, int x, int z)
{   
    int index = (x * m_Depth) + z;

    if(index < 0 || index > (m_Width * m_Depth) - 1)
    {
        assert("ERROR: Array2d - Set Index out of bounds bro");
    }
    
    m_pData[index] = val;
}

void Array2d::Normalize(float minRange, float maxRange)
{
    float Max = m_pData[0];
    float Min = m_pData[0];

    for (int i = 1 ; i < m_Width * m_Depth ; i++) {
        if (m_pData[i] < Min) {
            Min = m_pData[i];
        }

        if (m_pData[i] > Max) {
            Max = m_pData[i];
        }
    }

    if (Max <= Min) {
        return;
    }

    float minMaxDelta = Max - Min;
    float minMaxRange = maxRange - minRange;

    for (int i = 0 ; i < m_Width * m_Depth; i++) 
    {
        m_pData[i] = ((m_pData[i] - Min)/minMaxDelta) * minMaxRange + minRange;
    }
}

void Array2d::PrintArray()
{
    for (int i = 0 ; i < m_Width * m_Depth; i++) 
    {
        std::cout <<  m_pData[i] << " ";
    }
}
