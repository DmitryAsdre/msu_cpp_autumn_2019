#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <exception>
#include <algorithm>

using namespace std;

const size_t maxBuf = 1024 * 1024;

void copy(const string& nameIn, const string& nameOut)
{
    uint64_t * buf = new uint64_t[maxBuf];
    ifstream in(nameIn, ios::binary);
    ofstream out(nameOut, ios::binary);

    while(!in.eof())
    {
        in.read((char*) buf, maxBuf);
        if(in.gcount())
            out.write((char*) buf, in.gcount());
    }
    out.close();
    in.close();
    delete[] buf; 
}
void mergeTwoFiles(const string& name1, const string& name2, const string& output)
{
    ifstream in1(name1, ios::binary);
    ifstream in2(name2, ios::binary);
    ofstream out(output, ios::binary);

    uint64_t c1, c2;
    bool first = true;

    while(true)
    {
        if(first)
        {
            in1.read((char*)&c1, sizeof(uint64_t));
            if(in1.eof())
                break;
            in2.read((char*)&c2, sizeof(uint64_t));
            if(in2.eof())
                break;
            first = false;
        }

        if(c1 <= c2)
        {
            out.write((char*)&c1, sizeof(uint64_t));
            in1.read((char*)&c1, sizeof(uint64_t));
            if(in1.eof())
            {
                out.write((char*)&c2, sizeof(uint64_t));
                break;
            }
        }
        else 
        {
            out.write((char*)&c2, sizeof(uint64_t));
            in2.read((char*)&c2, sizeof(uint64_t));
            if(in2.eof())
            {
                out.write((char*)&c1, sizeof(uint64_t));
                break;
            }
        }
    }
    ifstream& notEmpty = (in1.eof() ? in2 : in1);
    while(true)
    {
        notEmpty.read((char*)&c1, sizeof(uint64_t));
        if(notEmpty.eof())
            break;
        out.write((char*)&c1, sizeof(uint64_t));
    }
    out.close();
    in1.close();
    in2.close();
}
void merge3(const vector<string>& names)
{
    copy(names[0], "temp" + to_string(0) + ".temp");
    remove(names[0].c_str());
    for(size_t i = 1; i < names.size() - 1; i++)
    {
        if(i < names.size() - 2)
            mergeTwoFiles("temp" + to_string(i - 1) + ".temp", names[i], "temp" + to_string(i) + ".temp");
        else 
            mergeTwoFiles("temp" + to_string(i - 1) + ".temp", names[i], "sorted.bin");
        remove(("temp" + to_string(i - 1) + ".temp").c_str());
        remove(names[i].c_str());
    }
}
void writeRandomFile(const string& name, size_t size)
{
    ofstream out(name, ios::binary);
    for (size_t i = 0; i < size; i++) {
        uint64_t rand_num = rand() % 100000000;
        out.write((char *) &rand_num, sizeof(uint64_t));
    }
    out.close();
}
void writeSortedFile(const string& name, uint64_t l, uint64_t r, uint64_t add)
{
    ofstream out(name, ios::binary);
    for(uint64_t i = l; i < r; i += add)
        out.write((char*)&i, sizeof(uint64_t));
    out.close();
}
int main(int argc, char** argv){
    size_t len(5);
    srand(time(NULL));
    if(argc != 1)
        len = stoi(argv[1]);
    writeRandomFile("input", maxBuf*len);
    vector<string> names;
    uint64_t *buf = new uint64_t [1024 * 1024];
    ifstream in("input", ios::binary);
    ofstream out;

    for (size_t i = 0; !in.eof(); i++){
        string name = "output" + std::to_string(i) + ".bin";
        names.push_back(name);

        in.read((char*) buf, 1024 * 1024 * sizeof(uint64_t));
        size_t cnt = in.gcount();

        if(cnt){
            size_t read_ = cnt / (2 * sizeof(uint64_t));

            thread th1([buf, read_]() {
                sort(buf, buf + read_);
            });

            thread th2([buf, read_]() {
                sort(buf + read_, buf + 2 * read_);
            });

            th1.join();
            th2.join();

            out.open(name, std::ios::binary);
            if(!out.is_open()){
                delete[] buf;
                throw runtime_error("can't open file");
                return 1;
            }
            out.write((char*) buf, read_ * sizeof(uint64_t));
            out.close();
            ++i;

            name = "output" + to_string(i) + ".bin";
            names.push_back(name);
            out.open(name, ios::binary);
            if(!out.is_open()){
                delete[] buf;
                throw runtime_error("can't open file");
                return 1;
            }
            out.write((char*) (buf + read_), cnt - read_ * sizeof(uint64_t));
            out.close();
        }
    }
    merge3(names);
    in.close();
    delete[] buf;
    return 0;
}