#include <vector>

class Triangle
{
private:
    std::vector<float> triangle;
public:
    void AddTriangle(float* TriInfo);
    unsigned int GetSize();
};