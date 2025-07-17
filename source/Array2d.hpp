#pragma once

struct Array2d
{
public:
    Array2d();
    ~Array2d();
    void InitArray(int width, int depth, void* pData);
    void InitArray(int width, int depth);
    float Get(int x, int z) const;
    void Set(float val, int x, int z);
    void Normalize(float MinRange, float MaxRange);
    void PrintArray();

private:
    int m_Width    = 0;
    int m_Depth    = 0;
    float* m_pData = nullptr;
};