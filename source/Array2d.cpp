#include "Array2d.hpp"
#include <iostream>

Array2d::Array2d()
{
}

Array2d::~Array2d()
{
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