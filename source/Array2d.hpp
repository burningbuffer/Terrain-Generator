#pragma once

struct Array2d
{
public:
    Array2d();
    ~Array2d();
    void InitArray(int width, int depth, void* pData);
    void Delete();
    float Get(int x, int y) const;
    void Set(float val, int x, int y);
private:
    int m_Width = 0;
    int m_Depth = 0;
    float* m_pData = nullptr;

};