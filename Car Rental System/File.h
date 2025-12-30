#ifndef FILE_H
#define FILE_H
using namespace std;

template <typename T>
class File
{
public:
    void readFromFile(const string &filename, vector<T> &temp);
    void appendToFile(const string &filename, const T &temp);
    void saveToFile(const string &filename, vector<T> &temp);
};

#endif